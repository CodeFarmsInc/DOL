#define zzLIB
#include <stdio.h>
#include <string.h>
#include "array.h"
#include "environ.h"
#include "types.h"
#include "heading.h"
#include "bind.h"
#include "msgs.h"

// ----------------------------------------------------------------------
// Notes on the algorithm.
// ----------------------------------------------------------------------
// (1) Under Windows, maximum array size is 65535 bytes. For this reason
//     one large array or references to all objects (trueArr) is replaced
//     by an array of arrays (virtArr).
//
// (2) Currently, there are two data sets which both include all objects,
//     but their purpose is different:
//       (a) References to all application objects (array of ZZswpStr),
//       (b) Stack of objects participating in the expansion process
//           (linked list of ZZswpItem). 
//     ZZswpStr's are part of the marking mechanism which marks expanded
//     objects by storing in their first 4 bytes the index(!) of the 
//     corresponding entry in the ZZswpStr array. If this index leads
//     to an ZZswpStr with ptr poZZinting back to the object, to object
//     has already recorded. Note that the first 4 bytes deal with index,
//     so even when the ZZswpStr array is re-allocated, this still works.
//
// (3) It would make sense to consolidate the two data structures ZZinto
//     a single one, preferably the array.
//        struct ZZswpStr {
//            char *ptr; // pointer to the object
//            ZZsigIntType back;  // remembers beginning of the object
//            ZZint type; // type index, -1 general block, <-1 hardwired special
//            ZZint mode; // 1=full object, 0=sub-object
//        };
//     Considering the complexity of the processing (composed objects due
//     to inheritance (including multiple-inheritance) and sub-objects
//     including arrays, this would be a major project and I am not sure
//     whether it would be worth to do it since users working with large
//     data sets are likely to use memory blasting anyway.
//
// (4) The array would work like the stack which, after the expansion,
//     would be reduced to the array of true objects:
//        xxxxxxxxxx.....abcdefghi
//     where x are already expanded full objects, abc..i are objects waiting
//     for processing. After processing a, a would first move the the
//     and of x-section, and new entries (123) would fill the gap backwards:
//        xxxxxxxxxxa..321bcdefghi  
//     When the gap is full, new items would come at the end:
//        xxxxxxxxxxa54321bcdefghi67
//     When a is a full object, its record would remain in place, if it is not
//     it would be removed:
//        xxxxxxxxxx...321bcdefghi        or
//        xxxxxxxxxx.54321bcdefghi67
//     The next item to expand would be 3 for   xxxxxxxxxxa..321bcdefghi
//                                   or 5 for   xxxxxxxxxxa54321bcdefghi67
//
// This note was added by Jiri Soukup on Sept.30/04
// when fixing a memory leak reported by a customer.
// ----------------------------------------------------------------------

#ifdef DOS
#define SPLIT
#endif

/* max size of one subarray in Bytes */
#define MAX_ARRAY 65535 

#ifdef ZZ_ANSI
static ZZint isRecorded(char *,ZZint,ZZint *),objSize(char *,ZZint);
#else
static ZZint isRecorded(),objSize();
#endif

struct ZZswpStr {
    char *ptr;  /* pointer to the object */
    ZZsigIntType back;  /* remembers beginning of the object */
    ZZint type;   /* structure index, -1 general block, <-1 hardwired special */
};

static struct ZZswpStr **virtArr={NULL}; /* each poZZints to a smaller array */
static ZZptrIntType ZZswpSize={0};  /* array size */
static ZZptrIntType ZZswpBeg={0};   /* beginning of direct reference */
static ZZptrIntType ZZswpNum={0};   /* actually used */
static ZZptrIntType maxArray={0};   /* maxArray permitted, set dynamically */
static ZZint *pCode;
static struct ZZstrLST *sList;
extern int ZZinhFLG; /* defined in zzincl.h */

// 
struct ZZswpItem {
    char *ptr;
    ZZint type;   /* structure index, -1 general block, <-1 hardwired special */
    ZZint mode; // 1=full object, 0=sub-object
    struct ZZswpItem *next;
};
static struct ZZswpItem *ZZswpHead;
static struct ZZswpItem *ZZswpTail;
static struct ZZswpItem *ZZswpAvail;

#ifdef ZZ_ANSI
static struct ZZswpStr* arrFun(ZZsigIntType i);
static void delArr(void);
static ZZint newArr(ZZsigIntType i,ZZint mode);
static ZZsigIntType recordIt(char *,ZZint,ZZint);
#else
static struct ZZswpStr* arrFun();
static void delArr();
static ZZint newArr();
static ZZsigIntType recordIt();
#endif


#ifdef SPLIT
#define ZZswpArr(A) (*(arrFun(A)))
#else
#define ZZswpArr(A) trueArr[(ZZint)(A)]
static struct ZZswpStr *trueArr={NULL}; /* structures recording detected objects */
#endif

/* Algorithm:
 * While setting up the list of all objects, the first four bytes
 * (as a ZZsigIntType) of each object are replaced by an index ZZinto ZZswpArr[].
 * ZZswpArr[].ptr poZZints to the object, ZZswpArr[].back stores what was
 * in the few bytes originally. When the search is finished and all objects
 * are on the list, ZZswpArr[].back is moved back ZZinto the object.
 * Since we know how many objects are on the list, this is a safe and fast
 * method of keepinp track of objects that have been detected already.
 *  The only tricky situation happens with composite objects such as
 * often occur in C++. For example, if class C inherits class A,
 * A may be located at the beginning of C. The two classes share
 * the first few bytes and, potentially, both could be on the list.
 * In order to avoid this conflict, only the larger object is
 * considered at any time, setting ZZswpStr.type appropriately.
 *  For objects that are smaller than 4 bytes (very rare, usually
 * some short names or object containing just one ZZinteger under DOS)
 * this does not work, and the objects are kept at the beginning
 * of ZZswpArr[], for indices from 0 to (ZZswpBeg-1), and a linear search
 * is performed.
 * 
 * Size of the list:
 * If all application objects are allocated from the heap (using new()
 * and delete()), ZZnumObjects gives their count and provides the exact
 * size of the list.
 * However, the list may be bigger than ZZnumObjects (if automatically
 * allocated objects are also saved), or the list may be smaller if 
 * only a subset of all objects is going to be saved. In such a case,
 * ZZnumObj may far too high and ZZbestGuess!=0 allows to work with
 * a shorter initial list than ZZnumObjects.
 * The array is first allocated with size=ZZnumObjects
 * or size=ZZbestGuess, and it doubles its size any time it gets full.
 *
 * Under DOS, the maximum of any array is 64kB, and larger array must
 * split ZZinto several pieces.
 * This means that, under DOS, the processing of small objects (under
 * 4 bytes), for example structures that contain only one ZZinteger, is
 * relatively slow.
 */

/* --------------------------------------------------------------------- */
#ifdef ZZ_ANSI
static struct ZZswpStr* arrFun(ZZsigIntType i){
#else
static struct ZZswpStr* arrFun(i)ZZsigIntType i;{
#endif
    ZZsigIntType k,m;

    k=i/maxArray;
    m=i-k*maxArray;
    return(&((virtArr[k])[m]));
}
/* --------------------------------------------------------------------- */
#ifdef ZZ_ANSI
static void delArr(void){
    ZZint ZZdelObj(char *p);
#else
static void delArr(){
    ZZint ZZdelObj();
#endif

    if(ZZswpSize<=0)return;
#ifdef SPLIT
    ZZptrIntType i,k;
    for(i=k=0; i<ZZswpSize; i=i+maxArray, k++){
        if(virtArr[k])(void)ZZdelObj((char *)(virtArr[k]));
        else  ZZmsg(69); // warning, should never be NULL
    }
    (void)ZZdelObj((char *)virtArr);
    virtArr=NULL;
#else
    (void)ZZdelObj((char*)trueArr);
    trueArr=NULL;
#endif
    ZZswpSize=ZZswpNum=0;
}
/* --------------------------------------------------------------------- */
/* create new sweap array (or set of arrays under DOS), and copy the old
 * array ZZinto it if mode=1. If mode=0, do not do anything */
#ifdef ZZ_ANSI
static ZZint newArr(ZZsigIntType n,ZZint mode){
    ZZvoidS *ZZnewObj(ZZint size,ZZint ini);
    ZZint ZZdelObj(char *);
#else
static ZZint newArr(n,mode)ZZsigIntType n; ZZint mode;{
    ZZvoidS *ZZnewObj();
    ZZint ZZdelObj();
#endif

#ifdef SPLIT
    ZZptrIntType i,j,k,s,sOld;
    struct ZZswpStr **hh;

    k=(n/maxArray)+1;  /* allocate the new arrays */
    hh=(struct ZZswpStr**)ZZnewObj((ZZint)(k*sizeof(void *)),0);
    if(!hh)return(1);

    if(mode && ZZswpSize>0){ /* copy the old array ZZinto the new one */
        for(i=k=0; i<(ZZptrIntType)n; i=i+maxArray, k++){
            s=n-i;
            if(s>maxArray)s=maxArray;
            if(ZZswpSize>i)sOld=ZZswpSize-i; else sOld=0;
            if(sOld>maxArray)sOld=maxArray;
            
            if(sOld==0){ // create a new sub-array
                hh[k]=(struct ZZswpStr*)
                           ZZnewObj((ZZint)(s*sizeof(struct ZZswpStr)),0);
                if(!hh[k])return(1);
            }
            else if(sOld<s){ // replace sub-array by a bigger one
                hh[k]=(struct ZZswpStr*)
                           ZZnewObj((ZZint)(s*sizeof(struct ZZswpStr)),0);
                if(!hh[k])return(1);
                for(j=0;j<sOld;j++)(hh[k])[j]=(virtArr[k])[j];
                (void)ZZdelObj((char *)(virtArr[k]));
            }
            else { // reuse the old sub-array
                hh[k]=virtArr[k];
            }
        }
        (void)ZZdelObj((char *)virtArr);
    }
    else {    /* create all the sub-arrays */
        for(i=k=0; i<(ZZptrIntType)n; i=i+maxArray, k++){
            s=n-i;
            if(s>maxArray)s=maxArray;
            hh[k]=(struct ZZswpStr*)
                           ZZnewObj((ZZint)(s*sizeof(struct ZZswpStr)),0);
            if(!hh[k])return(1);
        }
    }
    virtArr=hh;
#else

    struct ZZswpStr *h;
    ZZsigIntType s;

    h=(struct ZZswpStr*)ZZnewObj((ZZint)(n*sizeof(struct ZZswpStr)),0);
    if(!h)return(1);
    if(mode){
        for(s=0;s<ZZswpNum; s++)h[s]=trueArr[s];
        (void)ZZdelObj((char *)trueArr);
    }
    trueArr=h;
#endif
    ZZswpSize=n;
    return(0);
}
/* --------------------------------------------------------------------- */
/* Set the list of all objects in this organization */
#ifdef ZZ_ANSI
ZZint ZZswpSet(struct ZZstrLST *sL,ZZint *pC,char **v,char **t,ZZint n,ZZint array)
#else


ZZint ZZswpSet(sL,pC,v,t,n,array)
struct ZZstrLST *sL; /* ZZstrList[] */
ZZint *pC;             /* ZZnxtType[] */
char **v; /* list of the key entries ZZinto the organization */
char **t; /* list of types for the key entries */
ZZint n;    /* number of key entries */
ZZint array; /* =1 when including arrays and their headers, =0 if not */
#endif
/* returns number of objects, <0 means problems */
{
    ZZint i;
    ZZptrIntType ii,kk;
    ZZint j,k,err;
    ZZsigIntType *p,sz;
    struct ZZswpItem *si;
#ifdef ZZ_ANSI
    ZZint ZZdelObj(char *p);
    ZZvoidS ZZswpAdd(char *,ZZint,ZZint);
    ZZint ZZswpObj(char *p,ZZint i,ZZint mode);
#else
    ZZint ZZdelObj();
    ZZvoidS ZZswpAdd();
    ZZint ZZswpObj();
#endif

    err=0;      /* count number of errors */
    maxArray=MAX_ARRAY/sizeof(struct ZZswpStr);   /* size of one array */
    sList=sL;
    pCode=pC;
    ZZsList=sList; /* pass the same list to bind.c */
    if(ZZbestGuess)sz=ZZbestGuess; else sz=ZZnumObjects;
    if(ZZswpSize<=(ZZptrIntType)(n+sz)){
        /* derive the size from the number of allocated objects */
        if(ZZswpSize>0)delArr();
        err=newArr(n+sz,0);
    }

    if(err){
        ZZerrFLG=ZZerrFLG|01;
        ZZmsgSD(15,(char*)(&sz),n); /* unable to allocate sweap table for .. */
        return(-1);
    }
    ZZswpNum=ZZswpBeg=0; /* start with an empty list */

    /* put all key entries on the stack */
    ZZswpHead=ZZswpTail=ZZswpAvail=(struct ZZswpItem *)NULL;
    for(i=0;i<n;i++){   /* record all key entries */
        for(k=0;sList[k].numPtr>=0;k++){
            if(!strcmp(sList[k].strName,t[i]))break;
        }
        if(sList[k].numPtr<0)k= -1;

        if(v[i]){
            ZZswpAdd(v[i],k,1);
        }
    }

    /* expand objects on the stack, while adding new objects to it */
    while(ZZswpHead){
        si=ZZswpHead;
        err=err+ZZswpObj(si->ptr,si->type,si->mode);
        ZZswpHead=si->next;
        if(!ZZswpHead)ZZswpTail=ZZswpHead;
        si->next=ZZswpAvail;
        ZZswpAvail=si;
    }

    /* clear the stack */
    while(ZZswpAvail){
        si=ZZswpAvail;
        ZZswpAvail=si->next;
        (void)ZZdelObj((char *)si);
    }
    if(err){
        ZZerrFLG=ZZerrFLG|020;
        ZZmsgD(18,err); /* %d errors when setting up the sweap list */
    }

    /* restore the beginning of all objects */
    for(ii=ZZswpBeg;ii<ZZswpNum;ii++){
        p=(ZZsigIntType*)(ZZswpArr(ii).ptr);
        *p=ZZswpArr(ii).back;
        j=ZZswpArr(ii).type;
        if(j>=0)ZZswpArr(ii).back=(ZZsigIntType)(sList[j].strName);
        else if(j== -4)ZZswpArr(ii).back=(ZZsigIntType)("ZZarray");
        else    ZZswpArr(ii).back=(ZZsigIntType)("char *");
    }

    /* eliminate arrays and their headers from the list, if requested */
    if(array==0){
        for(ii=ZZswpBeg, kk=ZZswpBeg;ii<ZZswpNum;ii++){
            if(ZZswpArr(ii).type!= -4){
                ZZswpArr(kk)=ZZswpArr(ii);
                kk++;
            }
        }
        ZZswpNum=kk;
    }
    return((ZZint)ZZswpNum);
}
/* --------------------------------------------------------------------- */
/* Expand one object, return number of errors detected.
 * Though this is essentially a recursive call, in order to
 * save the memory stack, it is not coded as a recursive function.
 * Instead, objects that must expand next are registered
 * in the queue ZZswpHead/ZZswpTail, which is allocated from
 * the heap.
 */
#ifdef ZZ_ANSI
ZZint ZZswpObj(char *ptr,ZZint type,ZZint mode)
#else


ZZint ZZswpObj(ptr,type,mode)
char *ptr;  /* pointer to the object to be expanded */
ZZint type;   /* structure index, -1 general block, <-1 hardwired special */
ZZint mode;   /* 0=just search new objects, do not record this one, 1=record it */
#endif
{
    ZZsigIntType back,*p,rem,newSz,off;
    char **r,*s,**t,*pp,*blk,*tmp,**strt;
    ZZint j,j1,j2,k,n,ir,err,step,num,hType,rType,start;
    ZZarray *ap;
#ifdef ZZcplus
    void *vp;
    ZZint newTp;
#endif
#ifdef ZZ_ANSI
    ZZvoidS *ZZnewObj(ZZint size,ZZint ini);
    void *ZZtopType(void*,ZZint,ZZint*),ZZswpAdd(char*,ZZint,ZZint);
    ZZint ZZdelObj(char *ptr);
#else
    ZZvoidS *ZZnewObj();
    void *ZZtopType(),ZZswpAdd();
    ZZint ZZdelObj();
#endif

    err=0;
    if(!ptr)return(0);
    ir=isRecorded(ptr,type,&rType);
    if(ir>=0){ /* object already recorded */
        if(rType==type)return(0);
        if(rType<0 || type<0)return(0);
        if(mode){
            if(ZZsList[rType].size>=ZZsList[type].size)return(0);
            else ZZswpArr(ir).type=type; 
        }
    }

#ifdef ZZcplus
    /* In C++, jump to the top level object */
    if(mode && type>=0){
        vp=ZZtopType((void *)ptr,(ZZint)type,(ZZint*)(&newTp));
        if(type!=newTp){
            ptr=(char *)vp;
            type=newTp;
    
            ir=isRecorded(ptr,type,&rType);
            if(ir>=0){ /* object already recorded */
                if(rType==type)return(0);
                if(rType<0 || type<0)return(0);
                if(ZZsList[rType].size>=ZZsList[type].size)return(0);
                else ZZswpArr(ir).type=type;
            }
        }
    }
#endif

    newSz=ZZswpSize*2; 
    if(ZZswpNum>=ZZswpSize){
        err=newArr(newSz,1); /* double size */
    }
    if(err){
        ZZerrFLG=ZZerrFLG|01;
        ZZmsgSD(15,(char*)(&newSz),0); /* unable to allocate sweap table for .. */
        return(err);
    }
    back=recordIt(ptr,type,mode); /* not record, if part of a larger recorded object */

    /* recursively, process all injected/inherited sub-objects */
    if(type>=0 && ZZinhFLG){
        j1=ZZsList[type].inhInd;
        j2=ZZsList[type+1].inhInd;
        for(j=j1;j<j2;j++){
            k=ZZiList[j].type;
            s=ptr+ZZiList[j].offset-ZZsList[k].start;
            ZZswpAdd(s,k,0);
        }
    }

    newSz=ZZswpSize*2; 
    if(ZZswpNum>=ZZswpSize)err=newArr(newSz,1);   /* size not sufficient */
    if(err){
        ZZerrFLG=ZZerrFLG|01;
        ZZmsgSD(15,(char*)(&newSz),0); /* unable to allocate sweap table for .. */
        return(err);
    }

    if(type>=0){num=1; step=0; blk=ptr;}
    else if(type==(-4)){ /* array */
        ap=(ZZarray *)ptr;
        /* beginning has been overwritten, go back for a while */
        p=(ZZsigIntType*)ptr;
        rem= *p;
        *p=back; /* there cannot be a header array with mode=0 */
        if(mode==0){ ZZerrFLG=ZZerrFLG|040; ZZmsg(56);}

        num=ap->num;
        type=ap->strType;
        hType=ap->targType;
        blk=ap->array;
        step=ap->size;

	/* Different arrays are marked in this way:
	 *  type>=0            array of objects.
	 *  type<0; htype=-2   array of values such as (int)
	 *  type<0, htype>= -1 array of pointers to hType, -1 is for char*
	 */

        *p=rem; /* this is OK even when no recording, there is no change */
        if((type<0 && hType< -1) || !ptr)return(0); /* there are no pointers */ 
    }
    else return(0);

    /* avoid running through an array that has no pointers */
    if(type>=0 && sList[type].numPtr<=0)return(0);

    err=0;
    for(n=0; n<num;n++, blk+=step){ /* visit whole array */
        if(type>=0){
            start=sList[type].start;
            s=blk+start;

            // important detail: inserted variables which are not pointers
            // e.g. the counter for the reference are at the end of the sublist
            // end are not included in count numPtr here:

            for(k=0,r=(char**)s,t=(char**)(&back);k<sList[type].numPtr;k++,r++,t++){
                if(sList[type].propIndex!=k && sList[type].selfIndex!=k){
                    j=pCode[sList[type].ptrInd+k];
                    if(-8 != j){ /* do not expand ZZinto unknown blocks */
                        off=(ZZptrIntType)r-(ZZptrIntType)ptr;
                        if(off==0)pp=(*t);
                        else if(off<sizeof(ZZsigIntType)){
                            /* large pointer with 2B offset overlaps boundary */
                            strt=(char**)blk; tmp=(*strt);
                            (*strt)=(*t); pp=(*r); (*strt)=tmp;
                        }
                        else pp=(*r);
                        ZZswpAdd(pp,j,1);
                    }
                }
            }
        }
        else if(hType>= -1){
            r=(char**)blk;
            ZZswpAdd(*r,hType,1);
        }
    }
    return(err);
}
/* --------------------------------------------------------------- */
/* record this object */
#ifdef ZZ_ANSI
static ZZsigIntType recordIt(char *ptr,ZZint type,ZZint mode)
#else


static ZZsigIntType recordIt(ptr,type,mode)
char *ptr;/* pointer to the object */
ZZint type; /* structure index, -1 general block, <-1 hardwired special */
ZZint mode; /* mode=0 for just search, no recording */
#endif
{
    ZZint size;
    ZZsigIntType back,*p;
    ZZptrIntType i,*ip;

    /* record the new object */
    size=objSize(ptr,type);
    p=(ZZsigIntType*)ptr;
    back=(*p);

    /* if overlap with another object, synchronize 'back' */
    ip=(ZZptrIntType *)ptr;
    i=(*ip);
    if(i>=ZZswpBeg && i<ZZswpNum){
        if(ZZswpArr(i).ptr==ptr)back=ZZswpArr(i).back;
    }

    /* do not record, if we know that this is already a part of a larger
     * object that has been recorded */
     if(!mode)return(back);
    
    if(size>=(ZZint)sizeof(ZZsigIntType)){  /* cross-reference can be used */
        ZZswpArr(ZZswpNum).ptr=ptr;
        ZZswpArr(ZZswpNum).type=type;
        ip=(ZZptrIntType *)ptr;
        ZZswpArr(ZZswpNum).back=back;
        *ip=ZZswpNum;
    }
    else {   /* must go ZZinto the linear list */
        if(ZZswpNum>ZZswpBeg){ /* first section refers to the linear list */
            ZZswpArr(ZZswpNum)=ZZswpArr(ZZswpBeg);
            p=(ZZsigIntType *)(ZZswpArr(ZZswpNum).ptr);
            *p=ZZswpNum;
        }
        ZZswpArr(ZZswpBeg).ptr=ptr;
        ZZswpArr(ZZswpBeg).type=type;
        ZZswpBeg++;
    }
    ZZswpNum++;
    return(back);
}
/* --------------------------------------------------------------- */
/* decide whether the object is already recorded */
#ifdef ZZ_ANSI
static ZZint isRecorded(char *ptr,ZZint type,ZZint *rType)
#else


static ZZint isRecorded(ptr,type,rType)
char *ptr; /* pointer to the object */
ZZint type;    /* structure index, -1 general block, <-1 hardwired special */
ZZint *rType; /* recorded type, if already recorded */
#endif
/* returns an index ZZinto ZZswpArr if recorded, -1 otherwise */
{
    ZZptrIntType i,t,*ip;
    ZZint size,sPtr;

    sPtr=(ZZint)sizeof(ZZsigIntType);
    size=objSize(ptr,type);
    if(size>=sPtr){      /* use the cross-reference */
        ip=(ZZptrIntType *)ptr;
        t=(*ip);
        if(t>=ZZswpBeg && t<ZZswpNum){
            if(ZZswpArr(t).ptr==ptr){ /* object already recorded */
                *rType=ZZswpArr(t).type;
                return((ZZint)t);
            }
        }
    }
    else {          /* search the beginning of the list */
        for(i=0;i<ZZswpBeg;i++){
            if(ZZswpArr(i).ptr==ptr){
                *rType=ZZswpArr(i).type;
                return((ZZint)i);
            }
        }
    }
    return(-1);
}
/* --------------------------------------------------------------- */
/* estimate the object size, depending on the type */
#ifdef ZZ_ANSI
static ZZint objSize(char *ptr,ZZint type)
#else


static ZZint objSize(ptr,type)
char *ptr; /* pointer to the object */
ZZint type;    /* structure index, -1 general block, <-1 hardwired special */
#endif
/* returns the object size in bytes */
{
    ZZint size,sPtr;

    sPtr=(ZZint)sizeof(char *);
    if(type>=0)size=sList[type].size;
    else if(type== -1){
        for(size=0;size<sPtr;size++)if(ptr[size]=='\0'){size++; break;}
    }
    else if(type== -4)size=(ZZint)sizeof(ZZarray);
    else size=sPtr;
    return(size);
}
/* --------------------------------------------------------------- */
/* free the sweap array, initialize size to empty */
#ifdef ZZ_ANSI
ZZint ZZswpFree(void) {
#else


ZZint ZZswpFree() {
#endif

    if(ZZswpSize>0)delArr();
    ZZswpNum=ZZswpBeg=ZZswpSize=0;
    return(0);
}
/* --------------------------------------------------------------- */
/* Execute a given function on all objects recorded in the sweap array.
 * The given function must have 4 arguments:
 * - pointer to the object;
 * - object type (structure name);
 * - object size;
 * - pointer to private information the function may use (file to prZZint, etc.)
 */
#ifdef ZZ_ANSI
#ifdef GNU
typedef void (*fun_ptr_t)(char *ptr,ZZint type,ZZint size, const char *priv);
void ZZswpFun(fun_ptr_t fun,const char *priv)
#else
#ifdef WATCOM
typedef void (*fun_ptr_t)(char *ptr,ZZint type,ZZint size, char *priv);
void ZZswpFun(fun_ptr_t fun,char *priv)
#else
void ZZswpFun(void (*fun)(char *ptr,ZZint type,ZZint size,const char *priv),const char *priv)
#endif
#endif
#else


void ZZswpFun(fun,priv)
char *priv; /* pointer to the private information the function may need */
void (*fun)(); /* given function */
#endif
{
    ZZint k,size;
    unsigned i;

    for(i=0;i<ZZswpNum;i++){
        k=ZZswpArr(i).type;
        if(k== -4){size=(ZZint)sizeof(ZZarray);}
        else if(k<0){size=0;}
        else   {size=sList[k].size;}
        (*fun)(ZZswpArr(i).ptr,k,size,priv);
    }
    return;
}
/* --------------------------------------------------------------- */
/* record the next call to ZZswpObj() in the ZZinternal stack */
#ifdef ZZ_ANSI
void ZZswpAdd(char *ptr, ZZint type, ZZint mode){
    ZZvoidS *ZZnewObj(ZZint size,ZZint ini);

#else
void ZZswpAdd(ptr,type,mode)
char *ptr;
ZZint type;
ZZint mode;
{
    ZZvoidS *ZZnewObj();
#endif
    struct ZZswpItem *si;
    ZZint sz;

    if(!ptr)return;
    sz=sizeof(struct ZZswpItem);
    if(ZZswpAvail){
        si=ZZswpAvail;
        ZZswpAvail=si->next;
    }
    else si=(struct ZZswpItem *)ZZnewObj(sz,0);
    if(!si){ZZerrFLG=ZZerrFLG|01; ZZmsg(63); return;}

    si->ptr=ptr; si->type=type; si->mode=mode;
    si->next=NULL;
    if(ZZswpTail)ZZswpTail->next=si; else ZZswpHead=si;
    ZZswpTail=si;
}
/* --------------------------------------------------------------- */
/* debugging prZZint of the sweap array */
#ifdef ZZ_ANSI
static void debSweap(void)
#else


static void debSweap()
#endif
{
    ZZptrIntType i;
    ZZint t,k,s;
    char *p,**pp;
 
    for(i=0;i<ZZswpNum;i++){
        t=ZZswpArr(i).type;
        p=ZZswpArr(i).ptr;
        printf("i=%d ptr=%d type=%d CONT:",i,p,t);
        if(t>=0){
            s=sList[t].size;
            for(k=0, pp=(char**)p;k<s;pp++, k+=sizeof(char*))printf(" %d",*pp);
        }
        else printf(" %s",(char *)p);
        printf("\n");
    }
}
