

// #define NOT_WIN_NT
/****************************************************************/
/*							      	*/
/*   Copyright (C) 1988 1989             			*/
/*	Code Farms Inc.,  All Rights Reserved.			*/
/*							  	*/
/****************************************************************/
#define zzLIB
#include <stdio.h>
#include <stdlib.h>

#ifdef MICROSOFT
#ifdef NOT_WIN_NT
#include <dsetup.h>
#endif /* NOT_WIN_NT */
#endif /* MICROSOFT */

#include "environ.h"
#include "types.h"
#include "heading.h"
#include "bind.h"
#include "property.h"
#include "buffer.h"
#include "array.h"
#include "msgs.h"
#include "offset.h"

#include "virtarr.h"
static ZZvirtBindArr ZZbindArr; /* sorted array for pointer conversion */

static ZZlong ZZsaSize={0};   /* size of the sorted array */

#ifdef MICROSOFT
#ifdef ZZcplus
#define SORT_C_LINKAGE
#endif
#endif

#ifdef SORT_C_LINKAGE
extern "C" {
    ZZint ZZptrSort(const void*,const void*);
}

#else
#ifdef ZZ_ANSI
    ZZint ZZptrSort(const void*,const void*);
#else
    ZZint ZZptrSort();
#endif            /* END ZZ_ANSI */
#endif            /* END SORT_C_LINKAGE */

#ifdef ZZ_ANSI
#ifndef ZZcplus
#ifdef HP
#include <unistd.h>
#endif
#endif
#endif

extern char *ZZvirtCntr; /* used in msgs.c only */

/* Borland 3.0 has a bug - does not accept local function
 * prototypes if the function is defined above */
#ifdef ZZ_ANSI
    ZZint ZZpOffset(char*, char *);
    ZZint ZZbindPtrs(char *p,ZZint type,ZZint size,ZZint vUpd,ZZint val);
    ZZint ZZwrite(FILE *fp,char *buff,ZZsize n,const char *errTxt);
    ZZint ZZclose(FILE *fp);
    FILE *ZZopen(const char *fileName,const char *mode);
    void reduceVClass(ZZint type,ZZint *size);
    void zzdebBlk(char *,void *,ZZint,ZZint);
    void zzdebVObj(ZZint tp,struct ZZstrLST *sL);
#else
    ZZint ZZpOffset();
    ZZint ZZwrite();
    ZZint ZZread();
    ZZint ZZbindPtrs();
    ZZint ZZclose();
    FILE *ZZopen();
    void reduceVClass();
    void zzdebBlk();
    void zzdebVObj();
#endif
    ZZint ZZread(FILE *fp,char *buff,ZZsize n,const char *errTxt);

extern int ZZbindASCII; /* defined in zzincl.h */
extern int ZZnoLeak;    /* defined in zzincl.h, controls memory leak on SUN */
extern int ZZvClassPresent; /* defined in zzincl.h, =1 if vClass preesent */
extern int ZZinhFLG;    /* defined in zzincl.h */
extern ZZint ZZallocPtr;  /* defined in zzincl.h */
static FILE *ZZbindFile ={(FILE *)NULL};
/* Note that,when write()/read() is used, ZZbindFile may hide the file handle.
 * Because bindHandle=0 is a valid value, bindHandle= -1 is equivalent
 * to bindFile=NULL, we store (bindHandle+1) in ZZbindFile.
 */

/* main defines is zzincl.h */
extern char *ZZselfArr[];
static struct ZZstrLST *oldTypes={0};
static ZZint numSelf;

/* temporary list of the old types */
typedef struct ZZtypeList ZZtypeList;
struct ZZtypeList {
    ZZtypeList *next;
    struct ZZstrLST *type;
};

/* oldType-to-newType conversion */
typedef struct VerCntrl VerCntrl;
struct VerCntrl {
    ZZint newType;  /* index of the corresponding new type, -1 for nonexistent */
    ZZint compatible; /* 1=compatible, 0=different pointers */
};

/* structure to write/read limits of the old block */
typedef struct bigBlock bigBlock;
struct bigBlock {
    char *start;
    char *end;
    char *pool;
    ZZsigIntType offset;
};
static bigBlock bBlock;

/* offsets for the pointer list */
typedef struct PtrCntrl PtrCntrl;
struct PtrCntrl {
    ZZint offset;  /* offset in bytes from the beginning of the structure */
    ZZint oSize;   /* object size (combined array&object) in bytes */
};
#define ZZstaticVer VerCntrl
#define ZZstaticPTR PtrCntrl

/* structure for auxilliary list */
struct AuxList {
    ZZbindTBL *ptr;
    struct AuxList *next;
};

#ifdef ZZ_ANSI
static ZZint numPtrs(struct ZZstrLST *);
static void virtInit(ZZint);
void ZZsetMask(void);
static void partOf(ZZlong par,ZZlong chi);
char *ZZbindCnv(char *,ZZint *);
static void ZZwrInher(FILE *);
static void ZZwrPtrs(FILE *);
static char** ZZrdPtrs(FILE*);
static VerCntrl *ZZiCnv(FILE*,ZZint*);
static ZZint ZZbindBind(void);
static PtrCntrl *ptrOffset(struct ZZstrLST *,char**);
static void ZZtmpPerm(struct ZZbindTBL *);
static struct  ZZbindTBL *ZZtmpCnv(FILE*,ZZint,char**,ZZint,ZZint);
static void ZZshuffle(void);
static void ZZhashTab(struct ZZbindTBL *);
static void cleanHashTable(void), ZZrdInher(FILE*);
static void setBindArr(void);
static void setNewInh(void);
static void injectObj(void);
static void getNewBlock(void);
static void getNewData(FILE *,char**,char**,ZZint);
static ZZint findOffset(ZZint,ZZint,ZZint);
static void oneShuffle(char**,ZZint,ZZint,char*,ZZint);
static void ZZrdInher(FILE*);
static char *ZZselfCnv(ZZint);
static VerCntrl *ZZiCnv(FILE*,ZZint*);
static void createBlock(void);
static void setBindArr(void);
static char *ZZbArray(char*,ZZint*);
static void saveFun(char*,ZZint,ZZint,const char*);
static void freeFun(char*,ZZint,ZZint,const char*);

#else
static ZZint numPtrs();
static void virtInit();
void ZZsetMask();
static void partOf();
static void ZZwrInher();
static void ZZwrPtrs();
static char** ZZrdPtrs();
static VerCntrl *ZZiCnv();
static ZZint ZZbindBind();
static PtrCntrl *ptrOffset();
static void ZZtmpPerm();
static void ZZshuffle();
static struct  ZZbindTBL *ZZtmpCnv();
static void ZZhashTab();
char *ZZbindCnv();
static void cleanHashTable(), ZZrdInher();
static void setBindArr();
static void setNewInh();
static void injectObj();
static void getNewBlock();
static void getNewData();
static ZZint findOffset();
static void oneShuffle();
static void ZZrdInher();
static char *ZZselfCnv();
static VerCntrl *ZZiCnv();
static void createBlock();
static void setBindArr();
static char *ZZbArray();
static void saveFun();
static void freeFun();
#endif

ZZstaticChar **masks={(char **)NULL};   /* inverse mask for each type */
ZZstaticInt *ptrPtr={(ZZint *)NULL};        /* pointer conversion array */
ZZstaticVer *ic={(ZZstaticVer *)NULL};               /* type conversion array */
static struct ZZtypeHier *oldInhList={(struct ZZtypeHier *)NULL};
                                                 /* old inheritance hierarchy */
static ZZint *newInh={(ZZint *)NULL}; /* index parallel with oldInhList,
                              stores offset in the new object, -1 if not used */

#define END_MARK "ZZendMark"

/* offsets from the beginning of the structure for pointers and variables */
ZZstaticPTR *oldOff={(ZZstaticPTR *)NULL},*newOff={(ZZstaticPTR *)NULL};
static ZZint nID; /* size of the selfID array */

/* zzdebTypes are used only for debugging */
#ifdef ZZ_ANSI
void zzdebTypes(char *label,
      struct ZZstrLST *types,char **ptrs,PtrCntrl *off,struct ZZtypeHier *iList);
#else
void zzdebTypes();
#endif

/* information on possibly several output files opened at the same time */
typedef struct FileInfo FileInfo;
struct FileInfo {
    char *name; /* NULL if only file pointer/handle given */
    FILE *fp;
    FileInfo *next; /* linked list */
};
static FileInfo *allFiles={(FileInfo *)NULL};
#ifdef ZZ_ANSI
static void setFile(const char *);
static FileInfo *getFile(const char *);
static void delFile(FileInfo *);
#else
static void setFile();
static FileInfo *getFile();
static void delFile();
#endif

 static ZZint varOrg={1}; /* =0 disables variable organization */

/* ---------------------------------------------------------------- */
/* ---------------------------------------------------------------- */
/* Allocate a set of inverse masks, one for each type, and hang them
 * on the static array masks[]. Use ZZoneMask() to initialize the masks.
 */
#ifdef ZZ_ANSI
void ZZsetMask(void){
    ZZvoidS *ZZnewObj(ZZint size,ZZint ini);
    void ZZoneMask(char *obj, ZZint type);
#else

void ZZsetMask()
{
    ZZvoidS *ZZnewObj();
    void ZZoneMask();
#endif
    ZZint i,n;

    if(!ZZinhFLG || masks)return;
    for(n=0; ZZsList[n].numPtr>=0;n++)virtInit(n);
    /* n is the number of types now */

    masks=(char **)ZZnewObj(n*(ZZint)sizeof(char *),0);
    if(!masks){ZZmsgS(1,"ZZsetMask()"); return;}
    for(i=0;i<n;i++){
        masks[i]=(char *)ZZnewObj(ZZsList[i].size,0);
        if(!masks[i]){ZZmsgS(1,"ZZsetMask()"); return;}
        ZZoneMask(masks[i],i);
    }
}
/* ---------------------------------------------------------------- */
/* Compare two raw objects of this type as stored in vObj[0] and vObj[1]
 * The objects have are 0-filled except for vf and vc pointers.
 * Replace all bytes of vObj[1] by '\0', except for those bytes
 * that start a vf pointer ('F') or those that start a vc pointer ('C')
 * The size of pointers may be different for differrent compilers` 
 * and memory models. For example, some compilers may use 
 * 2Byte vf pointers, and 4Byte vc pointers. Note that Borland 3.1
 * without the option of -Vt has even vc pointers 2 Bytes.
 * This pointers represent only one half of the actual accress:
 * union { 
 *    void *trueAddress;
      ZZint half[2];
 * }u;   u.half[0] is the value stored,
 *       u.half[1] is common with the address of the object
 *        
 *
 * For situations where both pointers are the same, the algorithm
 * is simple: If the pointer points within the same object, it is
 * a vc pointer.
 * For situations where the vc pointer is twice as big, the following
 * algorithm decides on the pointer position:
 *   Proceed through the object as if array of ZZintegers.
 * Assume a1 and b1 are corresponding value in the two objects,
 * as and bs their starting addresses.
 *   if(a1!=b1){  ... vc pointer detected
 *       if(b1-a1==bs-as)  ... vc pointer starts at previous positioin
 *       else             ... vc pointer starts at this position
 *
 * Proof:
 * Consider three consequent values: a0,a1,a2 and b0,b1,b2
 * Since we reached a1, it must be a0=b0.
 * If a1!=b1, either (a0,a1) or (a1,a2) form a vc pointer
 * that points, within both objects, into the same relative position.
 * If it is (a0,a1), than it must be b1-a1=bs-as.
 * The only question is, whether there could be a confusing
 * situation that both (a0,a1) and (a1,a2) would point within
 * the same object. Assume x=max value that can be stored as ZZint
 * (typically 2**16). Then it would have to be true that
 *   (b1*x+b2)-(a1*x+a2)=bs-as
 * Substitute b1-a1=bs-as, and we get
 *   (bs-as)*x + b2 - a2 = (bs-as)
 *   (bs-as)*(x-1)=b2-a2
 * However, this cannot happen, because abs(bs-as)>2, which means
 *   abs(bs-as)*(x-1)>2x-2>x
 * while abs(bs-as)<x
 *
 * Problem on MAC - correction Aug.25/93:
 * PoZZinters start on 2B boudnary, but are 4 bytes ZZlong. This may lead
 * to situations when the pointer position is not fully determined when
 * comparing the bytes. The present algorithm assumes that vf pointers
 * are always large, i.e. that the first non-zero pair determines the lead
 * section of the pointer. This is equivalent to the assumption that,
 * on MAC, the value of all vf pointers is over 64k.
 */
#ifdef ZZ_ANSI
static void virtInit(ZZint tp)
{
#else


static void virtInit(tp)
ZZint tp; /* type index into ZZsList[] to pickup all values */
{
#endif

#ifdef MAC
#define STEP short
#else
#define STEP ZZint
#endif

    char *p1,*p2;
    ZZint i,n,fsz,csz,prev,df,bypass,justInt,ptrBdry;
    unsigned STEP *r1,*r2;
    unsigned ZZlong s1,s2,v1,v2;

    justInt=0;
#ifdef BORLAND3
#ifdef LARGE_POINTER
    justInt=1;
#endif
#endif

    n=ZZsList[tp].size;
    p1=ZZsList[tp].vObj[0];
    p2=ZZsList[tp].vObj[1];
    csz=sizeof(char *);
    fsz=sizeof(ZZint);
    ptrBdry=sizeof(STEP);
    
    if(justInt)csz=fsz;
    df=csz-fsz;

    s1=ZZptrToLong(p1);
    s2=ZZptrToLong(p2);
    if(csz!=fsz && csz!=sizeof(ZZlong)){
                                ZZerrFLG=ZZerrFLG|020; ZZmsg(62); return;}

    bypass=0; /* >0 will bypass next field and set it to 0 */
    for(i=0;i<n;i+=ptrBdry){
        if(i+ptrBdry>n){  /* fill the end of odd-sized objects */
            for(;i<n;i++)p2[i]='\0';
            break;
        }
        r1=(unsigned STEP *)(&(p1[i]));
        r2=(unsigned STEP *)(&(p2[i]));
        v1=(unsigned ZZlong)(*r1);
        v2=(unsigned ZZlong)(*r2);
        *r2=0;
        if(bypass){bypass-=fsz; continue;}
        if(v1==v2){
            if(v2){p2[i]='F'; bypass=fsz; }
        }
        else {
            if(fsz==csz || justInt){p2[i]='C'; bypass=csz;}
            else {
                prev=0; /* going back will be marked as prev=1 */
                if(v1>=v2 && s1>=s2){    if(v1-v2==s1-s2)prev=1;}
                else if(v1<v2 && s1<s2){ if(v2-v1==s2-s1)prev=1;}
                
                if(prev)p2[i-df]='C'; /* may over-write 'F' */
                else { p2[i]='C'; bypass=csz;}
            }
        }
    }
}
/* ---------------------------------------------------------------- */
/* find out number of pointers or other variables for a given type list */
#ifdef ZZ_ANSI
static ZZint numPtrs(struct ZZstrLST *s)
#else


static ZZint numPtrs(s)
struct ZZstrLST *s; /* given structure list */
#endif
{
    ZZint i;

    for(i=0;s[i].numPtr>=0;i++)continue;
    return(s[i].ptrInd);
}
    

/* ---------------------------------------------------------------- */
/* Read a file containing a complete organization and restore binding.
 * Expand previous conversion table if any, leave the new conversion
 * table in memory.
 * Open and close the file independently of ZZbindFile, which is used
 * for ZZ_WRITE_BIND() only.
 * The value of ZZbindASCII determines whether the file is ASCII or binary.
 *
 * Author: j.Soukup, June 9/88
 */
#ifdef ZZ_ANSI
ZZint ZZreadBind(const char *fileName,ZZint n,char **pp,char **type,ZZint numID)
{
    ZZvoidS *ZZnewObj(ZZint size,ZZint ini);
    char **ZZrpASCII(FILE *fp);
    ZZint ZZdelObj(char *p);
    ZZint ZZmainEntry(struct ZZbindTBL *sc,char **pp,char **type,ZZint n);
    void ZZafterOpen(void);
#else


ZZint ZZreadBind(fileName,n,pp,type,numID)
char *fileName; /* name of the file to read from */
    /* IMPORTANT: may hide (FILE *) if operating in MODE with cntrl=1 */
ZZint n;          /* number of key entries for this organization */
char **pp;      /* array of at least size n, for key pointers */
char **type;    /* array of at least size n, for types of the objects */
ZZint numID;    /* number of entries in the selfID table */
/* returns: 0=normal,1=allocation problems,2=file problems,4=strList problems */
{
    ZZvoidS *ZZnewObj();
    ZZint ZZdelObj(),ZZmainEntry();
    FILE *fopen();
    void ZZafterOpen();
#endif
    struct ZZbindTBL *sc; /* start of temporary conversion records */
    ZZint nt;  /* size of the temp conversion table */
    ZZint err; /* error count */

    ZZint i,i1,i2,j,jj,j1,j2,k,s1,s2,numOldTypes,numOldPtrs,cpTp;
    FILE *fp;
    char **oldPtrList;

    numOldTypes=numOldPtrs=0;
    /* decide on permission to handle schema migration */
    for(i=0;ZZsList[i].numPtr>=0;i++)continue;
    if(ZZallocPtr != i*numPtrs(ZZsList))varOrg=0;
    
    oldPtrList=(char **)NULL;
#ifdef ZZcplus
    if(ZZinhFLG && !masks)ZZsetMask(); /* in C++, create inverse mask by type */
#endif

    /* move selfID into a global static variable */
    numSelf=numID;
    err=0;

    /* open the file */
    if(ZZbindCntrl){
        fp=(FILE *)fileName;
    }
    else {
        if(ZZbindASCII)fp=fopen(fileName,"r");
        else           fp=ZZopen(fileName,"r");
    }
    if(!fp){
        ZZerrFLG=ZZerrFLG|0100;
	ZZmsgS(0,fileName); /* problem to open file */
        return(2);
    }

    /* read strList, compare with he current one, return index conversion */
    ic=ZZiCnv(fp,&nt);
    if(!ic)return(4);
    if(ZZpTbType){
        /* read the old list of pointers */
        oldPtrList=ZZrdPtrs(fp);
        ZZrdInher(fp);

        /* calculate offsets for old/new variables & pointers */
        oldOff=ptrOffset(oldTypes,oldPtrList);
        newOff=ptrOffset(ZZsList,ZZpList);

        /* count old pointers and types */
        for(i=0;oldTypes[i].numPtr>=0;i++)continue;
        numOldTypes=i;
        numOldPtrs=oldTypes[i].ptrInd;

        ptrPtr=(ZZint *)ZZnewObj(numOldPtrs*(ZZint)sizeof(ZZint),0);
        if(!ptrPtr){ZZmsgS(1,"ZZreadBind()"); return(4);}
 

        /* calculate pointer index conversion between old/new pointers */
        for(i1=0;i1<numOldTypes;i1++){
            i2=ic[i1].newType;
            if(i2>=0){
                s1=oldTypes[i1].ptrInd;
                s2=ZZsList[i2].ptrInd;
                jj=oldTypes[i1+1].ptrInd-oldTypes[i1].ptrInd;
                j=ZZsList[i2+1].ptrInd-ZZsList[i2].ptrInd;
                for(j1=0;j1<jj;j1++){
                    if(j1<j && !strcmp(oldPtrList[s1+j1],ZZpList[s2+j1])){
                        ptrPtr[s1+j1]=j1;
                    }
                    else{
                        ic[i1].compatible=0;
                        ptrPtr[s1+j1]=(-1);
                        for(j2=0;j2<j;j2++){
                            if(!strcmp(oldPtrList[s1+j1],ZZpList[s2+j2])){
                                ptrPtr[s1+j1]=j2;
                                break;
                            }
                        }
                    }
                }
                if(oldTypes[i1].timeIndex!=ZZsList[i2].timeIndex){
                    ic[i1].compatible=0;
                }
            }
        }
    }
    
    /* decide on the size of the selfID array */
    for(nID=0;strcmp(ZZselfArr[nID],END_MARK);nID++)continue;
    /*
zzdebTypes("old types",oldTypes,oldPtrList,oldOff,(struct ZZtypeHier *)NULL);
zzdebTypes("new types",ZZsList,ZZpList,newOff,(struct ZZtypeHier *)NULL);
    */
    for(cpTp=1, i=0; i<nt; i++){
        if(ic[i].compatible==0){cpTp=0; break;}
    }
    if(bBlock.start){  /* big block registered on the disk file */
        /* use big block only when objects compatible */
        if(cpTp){
            getNewBlock();
            getNewData(fp,pp,type,n);
            goto BIND_EXIT;
        }
    }

    /* read the rest of the file, record temporary conversion table */
    sc=ZZtmpCnv(fp,nt,oldPtrList,cpTp,n);
    if(!sc)return(4);

    /* close the file */
    if(!ZZbindCntrl){
        if(ZZbindASCII)fclose(fp);
        else (void)ZZclose(fp);
    }

    /* main entries into the organization are first n on the list */
    err=ZZmainEntry(sc,pp,type,n);

    /* setup the hash table, and avoid duplications
     * This is tricky, if one object can be a part of another */
    ZZhashTab(sc); /* array type conversion table in ZZbindTable */

    /* shuffle pointers inside objects, if the organization changed */
    for(i=k=0;i<numOldTypes;i++)if(ic[i].compatible!=1)k=1;
    if(k && !ZZbindASCII)ZZshuffle();
    /* when ASCII, shuffle is done right when reading */

    /* Up to here, everything is done flat. Now we must treat the
     * hierarchy, if injected/inherited types are used */
    if(ZZinhFLG){
        /* First prepare new offsets in newInh[] for fast processing */
        setNewInh();
        /* At this point, hash table has both the cover objects and the injected
         * objects. Next step is recursively inject (in the correct order)
         * sub-objects into their cover objects, and remove the sub-object
         * entries from the hash table */
    
        /* Prepare the array of objects sorted in the injection order */
        setBindArr();

        /* Inject the objects by repeated passes over newInh[],
         * and gradually reduce it. Mark eliminated objects by oldp=NULL */
        injectObj();

        /* the sorted array is not needed, in fact, it is invalid by now */
        ZZbindArr.clean(); ZZsaSize=0;

        /* Remove objects marked with oldp==NULL from the hash table */
        cleanHashTable();
    }

    /* Reset the key entries to the actual objects, this must
     * be done after injecting objects */
    for(i=k=0;i<n;i++){   /* k counts errors */
        pp[i]=ZZbindCnv(pp[i],&k);
    }
    if(k){err+=k; ZZmsgD(22,k);}

    /* bind the new organization */
    err=err+ZZbindBind();


BIND_EXIT:
    if(err){ ZZmsgD(11,err); return(4);} /* %d errors in binding */
    if(!ZZcustomPtr)ZZafterOpen();

    /* delete old pointer list */
    k=numPtrs(oldTypes);
    for(i=0;i<k;i++){if(oldPtrList[i])ZZdelObj((char *)oldPtrList[i]);}
    if(oldPtrList)ZZdelObj((char *)oldPtrList); oldPtrList=NULL;

    /* delete old inheritance list */
    for(i=0; oldTypes[i].numPtr>=0; i++)continue;
    i=oldTypes[i].inhInd;
    if(i>0){
        for(; i>=0; i--)ZZdelObj(oldInhList[i].name);
        ZZdelObj((char *)oldInhList);
    }

    /* delete old type tables */
    for(k=0;oldTypes[k].numPtr>=0; k++){
        if(oldTypes[k].strName)ZZdelObj(oldTypes[k].strName);
    }
    ZZdelObj((char *)oldTypes);

    return(0);
}
/* ----------------------------------------------------------------------- */
/* Find objects that are really part of another object.
 *  Copy the entire objects into their parents, and then mark
 *  the child (which has been injected into the parent) by oldp=NULL
 */

#ifdef ZZ_ANSI
static void injectObj(void)
{
#else


static void injectObj()
{
#endif
    ZZlong i,j,k,m;
    ZZint sz;
    ZZptrIntType p1,p2,pp1,pp2;

    for(i=0;i<ZZsaSize;i=k){
        p1=(ZZptrIntType)(ZZbindArr[i]->oldp);
        p1=p1+ZZbindArr[i]->arrSize;
        for(k=i+1;k<ZZsaSize;k++){
            p2=(ZZptrIntType)(ZZbindArr[k]->oldp);
            if(p2>=p1)break;
        }
        if(k>i+1){ /* i is parent of up to k-1 */
            for(j=k-1;j>i;j--){
                p2=(ZZptrIntType)(ZZbindArr[j]->oldp);
                pp2=p2+ZZbindArr[j]->arrSize;
                for(m=j-1;m>i;m--){ /* look for parent to fit into */
                    p1=(ZZptrIntType)(ZZbindArr[m]->oldp);
                    sz=ZZbindArr[m]->arrSize;
                    if(ZZvClassPresent)reduceVClass(ZZbindArr[m]->strIndex,&sz);
                    pp1=p1+sz;
                    if(p2>=p1 && pp2<=pp1)break; /* j fits into m */
                }
                partOf(m,j);
                ZZbindArr[j]->oldp=NULL; /* mark as used */
            }
        }
    }
}
/* ----------------------------------------------------------------------- */
/* Copy the entire child object from ZZbindArr[] into the parent object */
#ifdef ZZ_ANSI
static void partOf(ZZlong par,ZZlong chi)
{
#else

static void partOf(par,chi)
ZZlong par,chi; /* index of the parent and child */
{
#endif
    ZZint kk,oldChTp,newChTp,oldPaTp,newPaTp,oOff,nOff,oldPaSz,newPaSz;
    ZZint i,sz;
    char *p,*s,*m;

    oldChTp=ZZbindArr[chi]->strIndex;
    newChTp=ic[oldChTp].newType;
    oldPaTp=ZZbindArr[par]->strIndex;
    newPaTp=ic[oldPaTp].newType;
    oldPaSz=oldTypes[oldPaTp].size;
    newPaSz=ZZsList[newPaTp].size;
    if(newChTp<0 || newPaTp<0)return;

    /* we know the parent type, and the old offset.
    * This is enough information to derive which
    * parent-relation we have; from newInh[] we then have
    * the offset. The only tricky thing is that the relation
    * may include several nesting levels, and partial-size objects
    * if virtual classes are used. */
    oOff=ZZpOffset(ZZbindArr[chi]->oldp,ZZbindArr[par]->oldp);
    kk=oOff/oldPaSz;
    oOff=oOff-kk*oldPaSz;
    /* for arrays, calculate offset as for one element */
    nOff=findOffset(oldPaTp,oldChTp,oOff);
    if(nOff<0){
        ZZerrFLG=ZZerrFLG|020;
        ZZmsgDDD(1,oldChTp,oOff,oldPaTp);
        return;
    }
    nOff+=(kk*newPaSz); /* shift for the array */

    p=ZZbindArr[chi]->newp;
    s=ZZbindArr[par]->newp+nOff;
    sz=ZZsList[newChTp].size;
    if(ZZvClassPresent)reduceVClass(newChTp,&sz);
    if(ZZinhFLG){
        m=masks[newChTp];
        for(i=0;i<sz;i++,p++,s++,m++){
            if(*m)(*s)=(*p);
        }
    }
    else {
        for(i=0;i<sz;i++,p++,s++)(*s)=(*p);
    }
}
/* ----------------------------------------------------------------------- */
/* Go recursively through possibly several levels of nesting, and find
 * the new offset between parent type pType and the child type cType.
 * The old offset must match the given value - this is necessary, because
 * the same object type may be injected at different levels.
 * Return -1, if match not found. This is an ZZinternal error
 * that should never happen.
 *   The child type, cType, may not be known (given -1). In such a case
 * the offset calculation still works, using the offset only.
 */
#ifdef ZZ_ANSI
static ZZint findOffset(ZZint pType,ZZint cType,ZZint oOff)
{
#else


static ZZint findOffset(pType,cType,oOff)
ZZint pType; /* old parent type */
ZZint cType; /* old child type, may be -1 if not known */
ZZint oOff;  /* old offset calculated from pointers */
/* returns new offset, -1 if not found */
{
#endif
    ZZint i,k1,k2,k,oSt,nSt,nOff,nTp,oTp;

    if(ic[pType].compatible)return(oOff);
    if(pType==cType)return(oOff); 
    k1=oldTypes[pType].inhInd;
    k2=oldTypes[pType+1].inhInd;
    for(k=k1;k<k2;k++){
        if(cType<0 || oldInhList[k].type==cType){
            oTp=oldInhList[k].type;
            oSt=oldTypes[oTp].start; 
            nTp=ic[oTp].newType;
            nSt=ZZsList[nTp].start; 
            if(oldInhList[k].offset-oSt==oOff)return(newInh[k]-nSt);
        }
    }

    /* if not found, search recursively */
    for(k=k1;k<k2;k++){
        i=oldInhList[k].type;
        oSt=oldInhList[k].offset-oldTypes[i].start; /* start of type i */
        if(oSt<=oOff){
            nOff=findOffset(i,cType,oOff-oSt);
            if(nOff>=0){
                nTp=ic[i].newType; /* new type for child k */
                nOff=nOff+newInh[k]-ZZsList[nTp].start;
                return(nOff);
            }
        }
    }
    return(-1);
}
/* ----------------------------------------------------------------------- */
/* Prepare newInh[] parallel with oldInhList[],
 * newInh[] will contain the offset in the new environment.
 * This array is needed for the fast inserting of objects into their parents */
#ifdef ZZ_ANSI
static void setNewInh(void)
{
    ZZvoidS *ZZnewObj(ZZint size,ZZint ini);
#else


static void setNewInh()
{
    ZZvoidS *ZZnewObj();
#endif
    ZZint i,i1,i2,j,j1,j2,k,kk,m,n;

    /* find out the size and allocate newInh[] */
    for(i=0;oldTypes[i].numPtr>=0;i++)continue;
    i=oldTypes[i].inhInd;
    if(i>0){
        /* allocate the array */
        newInh=(ZZint *)ZZnewObj((i+1)*(ZZint)sizeof(ZZint),0);
        if(!newInh){ZZmsgS(1,"setNewInh()"); return;}
    }

    for(k=0;oldTypes[k].numPtr>=0;k++){
        i1=oldTypes[k].inhInd;
        i2=oldTypes[k+1].inhInd;
        kk=ic[k].newType;
        if(kk<0){  /* parent does not exist any more */
            for(i=i1;i<i2;i++)newInh[i]= -1;
        }
        else {
            j1=ZZsList[kk].inhInd;
            j2=ZZsList[kk+1].inhInd;
            for(i=i1;i<i2;i++){ /* for each old sub-object */
                m=oldInhList[i].type; /* old child type */
                n=ic[m].newType;         /* new child type */
                if(n<0)newInh[i]= -1;
                else { /* search for the same member name */
                    for(j=j1;j<j2;j++){
                        if(ZZiList[j].type==n &&
                           !strcmp(ZZiList[j].name,oldInhList[i].name))break;
                    }
                    if(j<j2)newInh[i]=ZZiList[j].offset;
                    else    newInh[i]= -1;
                }
            }
        }
    }
}
/* ----------------------------------------------------------------------- */
#ifdef ZZ_ANSI
static void cleanHashTable(void)
{
    ZZint ZZdelObj(char *p);
#else


static void cleanHashTable()
{
    ZZint ZZdelObj();
#endif
    ZZint i;
    struct ZZbindTBL *tc,*tcc;

    for(i=0;i<ZZbindSize;i++){
        tc=ZZbindTable[i];
        ZZbindTable[i]=NULL;
        for(;tc;tc=tcc){
            tcc=tc->next;
            if(tc->oldp){
                tc->next=ZZbindTable[i];
                ZZbindTable[i]=tc;
            }
            else if(ZZnoLeak){
                ZZdelObj(tc->newp);
                ZZdelObj((char *)tc);
         
            }
        }
    }
}
/* ----------------------------------------------------------------------- */
/* free all conversion-related arrays */
#ifdef ZZ_ANSI
void ZZafterOpen(void)
{
    ZZint ZZdelObj(char *p);
#else


void ZZafterOpen()
{
    ZZint ZZdelObj();
#endif
    ZZint i;
    struct ZZbindTBL *tc,*tcc;

    /* SUN must have a bug in the free() function, the following loop
     * leads to a quadratic CPU time increase */
    if(ZZnoLeak){
        /* free the whole bind table */
        for(i=0;i<ZZbindSize; i++){
            for(tc=ZZbindTable[i];tc;tc=tcc){
                tcc=tc->next;
                (void)ZZdelObj((char *)tc);
            }
        }
    }

    /* free the hash table and the array for binary search */
    if(ZZbindTable)ZZdelObj((char*)ZZbindTable);
    ZZbindTable=NULL; ZZbindSize=0;
    ZZbindArr.clean();
    if(newInh)ZZdelObj((char*)newInh);

    /* free all type & conversion arrays */
    if(ic)ZZdelObj((char *)ic);         ic=NULL;
    if(ptrPtr)ZZdelObj((char *)ptrPtr);     ptrPtr=NULL;
    if(oldOff)ZZdelObj((char *)oldOff);     oldOff=NULL;
    if(newOff)ZZdelObj((char *)newOff);     newOff=NULL;
}
/* ----------------------------------------------------------------------- */
/* allocates and creates the offset list for individual pointers and
 * variables. Note that most compilers fill in entries on even byte
 * boundaries, TURBOC is an exception.
 * The calculation uses the information stored in the variable 'name':
 * - first character a,A,g=autom.pointer,c=char,i=ZZint,f=float,s=(char*)
 * - then follows the actual variable name, until character [
 * - the end is a number specifying the array size
 */
#ifdef ZZ_ANSI
static PtrCntrl *ptrOffset(struct ZZstrLST *s,char **p)
{
    ZZvoidS *ZZnewObj(ZZint size,ZZint ini);
#else


static PtrCntrl *ptrOffset(s,p)
struct ZZstrLST *s; /* given type list */
char **p; /* corresponding pointer list */
{
    ZZvoidS *ZZnewObj();
#endif
    ZZint i,i1,i2,k,kk,kkk,n,sz;
    char c,*pp;
    PtrCntrl *r;

    n=numPtrs(s);
    r=(PtrCntrl *)ZZnewObj(n*(ZZint)sizeof(struct PtrCntrl),0);
    if(!r){ZZmsgS(1,"ptrOffset()"); return(NULL);}

    for(k=0;s[k].numPtr>=0;k++){
        i1=s[k].ptrInd;
        i2=s[k+1].ptrInd;
        for(i=i1, n=s[k].start; i<i2; i++, n+=kk){
            r[i].offset=n;
            pp=p[i];
            /* pickup the number from the end of the string */
            for(kk=kkk=0;pp[kk]!='\0';kk++)if(pp[kk]=='[')kkk=kk;
            kkk++; /* start of the number */
            sscanf(&(pp[kkk]),"%d",&sz);

            c=pp[0];
            if(c=='a'||c=='A'||c=='g'||c=='s')kk=(ZZint)sizeof(char *);
            else if(c=='i')kk=(ZZint)sizeof(ZZint);
            else if(c=='c')kk=1;
            else if(c=='f')kk=(ZZint)sizeof(float);
            else {ZZmsgS(29,p[i]); kk=(ZZint)sizeof(char *);}
            kk=kk*sz;
            r[i].oSize=kk;
/* I wonder - what is the boundary alignment in VMS ? */
#ifdef UNIX
            kkk=kk/2;
            if(kk-kkk*2>0)kk++;
#endif
        }
    }
    return(r);
}
/* ----------------------------------------------------------------------- */
/* shuffle pointers inside objects, if the organization changed */
#ifdef ZZ_ANSI
static void ZZshuffle(void)
{
#else


static void ZZshuffle()
{
#endif
    struct ZZbindTBL *tp;
    ZZint j,k1,n;
    
    for(j=0;j<ZZbindSize;j++){
        for(tp=ZZbindTable[j];tp;tp=tp->next){ /* traverse hash table */
	    k1=tp->strIndex;
            if(k1>=0 && ic[k1].compatible==0){ 
                /* re-shuffle only if not compatible */
                n=(tp->arrSize)/(oldTypes[k1].size);
                if(n<=0)n=1;
                oneShuffle(&(tp->newp),k1,n,(char *)(NULL),0);
            }
            else {
                continue;
            }
        }
    }
    return;
}
/* ----------------------------------------------------------------------- */
/* Shuffle pointers inside objects, if the organization changed */
#ifdef ZZ_ANSI
static void oneShuffle(char **newp,ZZint k1,ZZint n,char *fObj,ZZint nSize)
{
    ZZvoidS *ZZnewObj(ZZint size,ZZint ini);
    void ZZstTime(unsigned char *p);
    ZZint ZZdelObj(char *p);
#else


static void oneShuffle(newp,k1,n,fObj,nSize)
char **newp; /* pointer to the object, will be replaced */
ZZint k1; /* old type index */
ZZint n;  /* array size */
char *fObj; /* future object, if NULL, allocate a new one */
ZZint nSize; /* new larger size; =0 means use normal size */
{
    ZZvoidS *ZZnewObj();
    void ZZstTime();
    ZZint ZZdelObj();
#endif
    ZZint k2,k,kk,kp,ks,i,pz,sz,pn,ps,ss,pi,si;
    ZZint p1,p2,p3,s1,s2,s3;
    char *p,*s,**pc,**sc,***q,*newO,*pt,*st;

    if(k1>=0 && ic[k1].compatible==0){
        if(!varOrg){ZZmsg(54); return;}
        /* re-shuffle only if not compatible */
        k2=ic[k1].newType;
        if(k2<0)return; /* no action, type is not used now */
        if(nSize)pz=nSize; else pz=oldTypes[k1].size;
        sz=ZZsList[k2].size;
        pn=oldTypes[k1+1].ptrInd-oldTypes[k1].ptrInd;
        ps=oldTypes[k1].start;
        ss=ZZsList[k2].start;
        pi=oldTypes[k1].ptrInd;
        si=ZZsList[k2].ptrInd;
        k=sz*n;
        if(fObj)newO=fObj;
        else newO=(char *)ZZnewObj(k,1);
        if(!newO){ZZmsgSS(15,ZZsList[k2].strName,"ZZshuffle()");return;}

        /* repeat the same thing for all elements of the array */
        for(i=0, s=newO, p= *newp; i<n; i++, s+=sz, p+=pz){

            /* if not ASCII,copy attributes before pointers */
            if(!ZZbindASCII){
                /* copy bytes 0-p1,p2-p3 into 0-s1, s2-s3 */
                p1=ps-1; s1=ss-1;
                kp=oldTypes[k1+1].ptrInd-1;
                ks=ZZsList[k2+1].ptrInd-1;
                p2=ps+oldOff[kp].offset+oldOff[kp].oSize;
                s2=ss+newOff[ks].offset+newOff[ks].oSize;
                p3=pz-1; s3=sz-1;
                for(k=0;k<=p1 && k<=s1; k++)s[k]=p[k];
                for(kp=p2,ks=s2;kp<=p3 && ks<=s3; kp++,ks++)s[ks]=p[kp];
            }

            /* copy pointers and variables into the new block */
            for(k=0; k<pn; k++){
                s1=ptrPtr[pi+k];
                if(s1>=0){
                    for(kk=0, pt=p+oldOff[pi+k].offset, 
                                    st=s+newOff[si+s1].offset;
                                    kk<newOff[si+s1].oSize;
                                    kk++, pt++, st++){
                                       *st= *pt;
                     }
                 }
             }
             /* note, this will leave selfID unset */
    
             if(ZZsList[k2].timeIndex>=0){ /* if new object has time stamp */
                 if(oldTypes[k1].timeIndex<0){ /* make new time stamp */
                     sc=(char**)((char *)s+ss);
                     st=(char *)(sc+ZZsList[k2].timeIndex);
                     ZZstTime((unsigned char *)st);
                 }
                 else { /* copy the old time stamp */
                     sc=(char**)((char *)s+ss);
                     st=(char *)(sc+ZZsList[k2].timeIndex);
                     pc=(char**)((char *)p+ps);
                     pt=(char *)(pc+oldTypes[k1].timeIndex);
                     for(k=0;k<4;k++)(*st)=(*pt);
                 }
             }

             if(ZZsList[k2].selfIndex>=0){ /* set selfID if used */
                 for(k=0;k<nID;k++){
                     if(!strcmp(ZZselfArr[k],ZZsList[k2].strName))break;
                 }
                 if(k>=nID)ZZmsgS(15,ZZsList[k2].strName);
                 else {
                     q=(char***)s;
                     *q= &(ZZselfArr[k]);
                 }
             }
         }

         /* replace the object by a new copy */
         ZZdelObj(*newp);
         *newp=newO;
    }
    return;
}
/* ----------------------------------------------------------------------- */
/* read the list of old pointers, and deposit them in a global array, ZZpList.
 * Use binary/ASCII read depending on the value of ZZbindASCII */
#ifdef ZZ_ANSI
static char **ZZrdPtrs(FILE *fp)
{
    ZZint i,n;
    ZZvoidS *ZZnewObj(ZZint size,ZZint ini);
#else


static char **ZZrdPtrs(fp)
FILE *fp; /* file to read from - ASCII */
{
    ZZint i,n;
    ZZvoidS *ZZnewObj();
#endif
    struct ZZbinStore b;
    char **pp; char nn[ZZ_BUFS];
    if(ZZpTbType){
        /* allocate the array */
        n=numPtrs(oldTypes);
        pp=(char **)ZZnewObj(n*(ZZint)sizeof(char *),0);
        if(!pp){ZZmsgS(1,"ZZrdPtrs()"); return(NULL);}

        for(i=0;i<n;i++){
            if(ZZbindASCII){
                if(!fgets(ZZbuff,ZZ_BUFS,fp)){
                    ZZmsg(41); /* error: short beginning of the ASCII file */
                    break;
                }
                sscanf(ZZbuff,"%s",nn);
            }
            else {
                ZZread(fp,(char *)(&b),sizeof(struct ZZbinStore),"rdPtrs:1");
		ZZread(fp,nn,(ZZsize)(b.size),"rdPtrs:2");
            }
            pp[i]=(char *)ZZnewObj((ZZint)strlen(nn)+1,0);
            if(!pp[i])ZZmsgS(1,"ZZrdPtrs(), pointer name");
            strcpy(pp[i],nn);
        }
    }
    return(pp);
}
/* ----------------------------------------------------------------------- */
/* If there is any inheritance used, read the list and deposit it
 * in a global array, oldInhList.
 * Use binary/ASCII read depending on the value of ZZbindASCII */
#ifdef ZZ_ANSI
static void ZZrdInher(FILE *fp)
{
    ZZvoidS *ZZnewObj(ZZint size,ZZint ini);
#else


static void ZZrdInher(fp)
FILE *fp; /* file to read from - ASCII */
{
    ZZvoidS *ZZnewObj();
#endif
    struct ZZbinStore b;
    ZZint i,j,j1,j2,k;
    char name[ZZ_BUFS];

    /* check that any inheritance is used */
    for(i=0;oldTypes[i].numPtr>=0;i++)continue;
    i=oldTypes[i].inhInd;
    if(i>0){
        /* allocate the array */
        oldInhList= (struct ZZtypeHier *)ZZnewObj(
                  (i+1)*(ZZint)sizeof(struct ZZtypeHier),0);
        if(!oldInhList){ZZmsgS(1,"ZZrdInher()"); return;}

        for(i=0;;i++){
            if(ZZbindASCII){
                if(!fgets(ZZbuff,ZZ_BUFS,fp)){
                    ZZmsg(41); /* error: short beginning of the ASCII file */
                    break;
                }
#ifdef Windows64
                sscanf(ZZbuff,"%I64d %I64d %I64d %s",&(oldInhList[i].type),
#else
                sscanf(ZZbuff,"%d %d %d %s",&(oldInhList[i].type),
#endif
                            &(oldInhList[i].offset),&(oldInhList[i].num),name);
            }
            else {
                ZZread(fp,(char *)(&b),sizeof(struct ZZbinStore),(char*)"rdInher:1");
                ZZread(fp,(char *)(&(oldInhList[i])),b.size,"rdInher:2");
                ZZread(fp,(char *)(&b),sizeof(struct ZZbinStore),"rdInher:3");
                ZZread(fp,name,b.size,"rdInher:1");
            }
            oldInhList[i].name=(char *)ZZnewObj((ZZint)strlen(name)+1,0);
            if(!(oldInhList[i].name)){ZZmsgS(1,"ZZrdInher()"); break;}
            strcpy(oldInhList[i].name,name);
            if(oldInhList[i].type<0)break;
        }

        /* check for compatibility also in inheritance */
        for(i=0;oldTypes[i].numPtr>=0;i++){
            k=ic[i].newType;
            j1=oldTypes[i].inhInd; 
            j2=oldTypes[i+1].inhInd; 
            if(j1!=ZZsList[k].inhInd || j2!=ZZsList[k+1].inhInd)
                                                      ic[i].compatible=0;
            else {
                for(j=j1; j<j2; j++){
                    if(oldInhList[j].type != ZZiList[j].type ||
                    oldInhList[j].offset != ZZiList[j].offset ||
                    oldInhList[j].num != ZZiList[j].num ||
                    strcmp(oldInhList[j].name,ZZiList[j].name))
                                                      ic[i].compatible=0;
                }
            }
        }
    }
}
/* ----------------------------------------------------------------------- */
/* write the list of all pointers.
 * Use binary/ASCII write depending on the value of ZZbindASCII */
#ifdef ZZ_ANSI
static void ZZwrPtrs(FILE *fp)
{
    ZZint i,n;
#else


static void ZZwrPtrs(fp)
FILE *fp; /* file to write to, may hide a file handle */
{
    ZZint i,n;
#endif
    struct ZZbinStore b;

    if(ZZpTbType){
        n=numPtrs(ZZsList);
        for(i=0;i<n;i++){
            if(ZZbindASCII)fprintf(fp,"%s\n",ZZpList[i]);
            else {
                b.ptr=ZZpList[i];
                b.strInd=(-1);
                b.size=strlen(ZZpList[i])+1;
                ZZwrite(fp,(char *)(&b),sizeof(struct ZZbinStore),"wrPtrs:ZZbinStore");
                ZZwrite(fp,ZZpList[i],b.size,"pList[i]");
            }
        }
    }
    return;
}
/* ----------------------------------------------------------------------- */
/* write the inheritance list
 * Use binary/ASCII write depending on the value of ZZbindASCII */
#ifdef ZZ_ANSI
static void ZZwrInher(FILE *fp)
{
#else


static void ZZwrInher(fp)
FILE *fp; /* file to write to, may hide a file handle */
{
#endif
    struct ZZbinStore b;
    ZZint i;

    /* check that any inheritance is used */
    for(i=0;ZZsList[i].numPtr>=0;i++)continue;
    if(ZZsList[i].inhInd>0){
        for(i=0;;i++){
            if(ZZbindASCII)fprintf(fp,"%d %d %d %s\n",
              ZZiList[i].type,ZZiList[i].offset,ZZiList[i].num,ZZiList[i].name);
            else {
                b.ptr= (char *)(&(ZZiList[i]));
                b.strInd=(-1);
                b.size=sizeof(struct ZZtypeHier);
                ZZwrite(fp,(char *)(&b),sizeof(struct ZZbinStore),"wrInherit:1");
                ZZwrite(fp,b.ptr,b.size,"wrInherit:2");
                b.ptr=ZZiList[i].name;
                b.strInd=(-1);
                b.size=(ZZint)strlen(ZZiList[i].name)+1;
                ZZwrite(fp,(char *)(&b),(ZZint)sizeof(struct ZZbinStore),"wrInherit:3");
                ZZwrite(fp,ZZiList[i].name,b.size,"wrInherit::4");
            }
            if(ZZiList[i].type<0)break;
        }
    }
    return;
}
/* ----------------------------------------------------------------------- */
/* main entries into the organization are first n on the list,
 * Record only ZZbindTBL entries, pointer to the object may change
 * later, if a re-shuffle is needed */
#ifdef ZZ_ANSI
ZZint ZZmainEntry(struct ZZbindTBL *start,char **pp,char **type,ZZint n)
{
#else


ZZint ZZmainEntry(start,pp,type,n)
struct ZZbindTBL *start; /* list of recorded objects */
char *pp[];   /* array of first n main entries, to be filled */
char *type[]; /* array of types corresponding to pp, to be filled */
ZZint n;        /* given size of pp[] and type[] */
{
#endif
    struct ZZbindTBL *tc,*tp;
    ZZint i,j,k,err,arrFlg;

    err=arrFlg=0;
    for(i=0,tc=start;i<n && tc;tc=tc->next){
        /* in case of a duplication, refer to the first instance */
        for(tp=start;tp->oldp!=tc->oldp;tp=tp->next)continue;
        pp[i]=tp->oldp;
	k=tc->strIndex;
        if(k<0)j=0; else j=ic[k].newType;
        if(j>=0){ /* the old type is present in the new setup */
	    if(k<0)type[i]=NULL;
	    else   type[i]=ZZsList[ic[k].newType].strName;
            /* skip property,property array,array header,or array after it*/
            if(k!= -1 && k!= -2 && k!= -3 && k!= -4 && arrFlg==0)i++;
            if(k==-4)arrFlg=1; else arrFlg=0;
        }
        else {
            pp[i]=NULL;
            type[i]=NULL;
            i++;
        }
    }
    return(err);
}
/* ---------------------------------------------------------------- */
/* Convert one block to new pointers. For hierarchical types,
 * this is a recursive process, except for memSwitch==2 in C++, when
 * it is only an initialization, which is recurse automatically
 * through constructors/destructors.
 * All pointers are already in new positions, this is merely a process
 * of resetting the pointers.
 */
#ifdef ZZ_ANSI
ZZint ZZbindPtrs(char *obj,ZZint newTp,ZZint newSize,ZZint vUpd,ZZint val)
{
    void ZZsetVirt(char *obj, char **mast,ZZint type,ZZint blst);
    void ZZmarkPtr(char **,ZZint);
#else


ZZint ZZbindPtrs(obj,newTp,newSize,vUpd,val)
char *obj;   /* new(!!) start of the object */
ZZint newTp;   /* new type */
ZZint newSize; /* size of the new object, may indicate an array */
ZZint vUpd;    /* 1 update virt.pointers, 0 do not update */
ZZint val;   /* value to mark bitmap, 0 or 1 */
/* returns number of binding errors */
{
    void ZZsetVirt();
    ZZint ZZbindPtrs();
    void ZZmarkPtr();
#endif
    ZZint i,ii,k,k1,k2,err,state,strt,sz,msz;
    char c,*p,*s,**pp,*ss;
    struct ZZproperty *prp;
    struct ZZaProp *pap;
    ZZarray *aa;

#ifndef ZZcplus
    vUpd=0;
#endif
    if(vUpd && ZZinhFLG && newTp>=0){
        sz=ZZsList[newTp].size;
        for(p=obj, i=0; i<newSize; p+=sz, i+=sz){
            ZZsetVirt(p,ZZsList[newTp].vObj,newTp,val);
        }
    }
    err=0;
    if(newTp>=0){  /* object with ZZ_EXT, or an array of such objects */
        msz=newSize;
	ii=ZZsList[newTp].numPtr;
	strt=ZZsList[newTp].start;
        for(sz=0; sz<msz; sz+=ZZsList[newTp].size){
	    pp=(char**)(obj+strt+sz);
	    for(i=0;i<ii;i++,pp++){
	        if(i==ZZsList[newTp].selfIndex){
                    if(ZZmemSwitch==2)ZZmarkPtr(pp,val);
                    if(ZZbindASCII<2) (*pp)=ZZselfCnv(newTp);
                }
	        else {
                   state=err; ss= *pp;
                   if(ZZmemSwitch==2)ZZmarkPtr(pp,val);
                   if(ZZbindASCII<2)  (*pp)=ZZbindCnv(*pp,&err);
                   if(state!=err)ZZmsgSSD(0,ZZsList[newTp].strName,ss,
                               ZZptrToInt((char*)pp)-ZZptrToInt(obj));
                }
	    }
        }
    }
    else if(newTp== -2){            /* ZZproperty */
	prp=(struct ZZproperty*)obj;
        if(ZZmemSwitch==2){
            ZZmarkPtr(&(prp->codeName),val);
            ZZmarkPtr((char **)(&(prp->next)),val);
        }
	if(ZZbindASCII<2){
            prp->codeName=ZZbindCnv(prp->codeName,&err);
	    prp->next=(struct ZZproperty*)ZZbindCnv((char*)(prp->next),&err);
        }
	c=prp->codeName[0];
	if(c!='i' && c!='f' && c!='c'){
            if(ZZmemSwitch==2)ZZmarkPtr((char **)(&(prp->propType.arrayProp)),val);
            if(ZZbindASCII<2) prp->propType.arrayProp=(struct ZZaProp*)ZZbindCnv(
                                         (char*)(prp->propType.arrayProp),&err);
        }
    }
    else if(newTp== -3){            /* ZZaProp */
	pap=(struct ZZaProp*)obj;
        if(ZZmemSwitch==2)ZZmarkPtr(&(pap->array),val);
	if(ZZbindASCII<2) pap->array=ZZbindCnv(pap->array,&err);
    }
    else if(newTp== -4){            /* array header */
        aa=(ZZarray*)obj;
        if(ZZmemSwitch==2)ZZmarkPtr(&(aa->array),val);
        if(ZZbindASCII<2) aa->array=ZZbindCnv(aa->array,&err);
    }
    else if(newTp== -5){  /* char* pointer, or an array of these */
        msz=newSize/(ZZint)sizeof(char *);  /* size of the whole block */
        for(pp=(char**)obj, i=0; i<msz; pp++, i++){
            if(ZZmemSwitch==2)ZZmarkPtr(pp,val);
	    if(ZZbindASCII<2) (*pp)=ZZbindCnv(*pp,&err);
        }
    }
    /* -1=plain block, -5 char*, -6=ZZint, -7=float: do nothing */

    /* recursively, process all inherited or injected objects */
    /* in normal C++, constructors/destructors provide this */
    if(ZZinhFLG && newTp>=0){
        msz=newSize;
	ii=ZZsList[newTp].size;
        k1=ZZsList[newTp].inhInd;
        k2=ZZsList[newTp+1].inhInd;
        for(sz=0, s=obj; sz<msz; sz+=ii, s+=ii){
            for(k=k1;k<k2;k++){
                i=ZZiList[k].type;
                p=s+ZZiList[k].offset-ZZsList[i].start;
                (void)ZZbindPtrs(p,i,ZZsList[i].size,0,val);
            }
        }
    }
    return(err);
}
/* ---------------------------------------------------------------- */
/* Traverse the hash table, and for each object, bind the pointers.
 * At this point, the objects have the pointers in right positions
 * (For compatible types there was no change), for incompatible
 * types, the shuffle and possible re-allocation has been done).
 * Algorithm:
 * Traverse all objects recorded at the hash table, and convert the
 * pointers by calling ZZbindPtrs().
 */
#ifdef ZZ_ANSI
static ZZint ZZbindBind(void)
{
#else


static ZZint ZZbindBind()
/* returns number of errors in binding */
{
#endif
    ZZint j,err,oldTp,newTp,arrSize,good;
    struct ZZbindTBL *tp;

    err=0;
    for(j=0;j<ZZbindSize;j++){
        for(tp=ZZbindTable[j];tp;tp=tp->next){
            good=1;
            oldTp=tp->strIndex;
            arrSize=tp->arrSize;
            if(oldTp>=0){
                newTp=ic[oldTp].newType;
                if(newTp<0){
                    ZZmsgS(11,"not eliminating old type object"); /* ZZinter.err*/
                    err++;
                    good=0;
                }
                else arrSize=(arrSize/oldTypes[oldTp].size)*ZZsList[newTp].size;
            }
            else newTp=oldTp;
            if(good)err=err+ZZbindPtrs(tp->newp,newTp,arrSize,1,0);
        }
    }
    return(err);
}
/* ---------------------------------------------------------------- */
/* convert ZZsList[] index into selfID pointer, both arrays in the
 * new environment */
#ifdef ZZ_ANSI
static char *ZZselfCnv(ZZint ind)
#else


static char *ZZselfCnv(ind)
ZZint ind; /* given index into ZZsList[] */
#endif
/* returns the selfID pointer */
{
    char **p,*s;
    ZZint i;

    s=ZZsList[ind].strName;
    for(i=0,p=ZZselfArr;i<numSelf;i++,p++){
	if(!strcmp(*p,s))return((char*)p);
    }
    ZZmsgS(17,s); /* error in recovering selfID for %s */
    return(NULL);
}
/* ---------------------------------------------------------------- */
/* Use the ZZinternal list of objects, and hook it up into a hash table.
 * At the same time, remove duplicate objects and objects that do not
 * exist in the new organization.
 */
#ifdef ZZ_ANSI
static void ZZhashTab(struct ZZbindTBL *start)
{
    ZZvoidS *ZZnewObj(ZZint size,ZZint ini);
    ZZint ZZhashPtr(char *key,ZZint size),ZZdelObj(char *p);
#else


static void ZZhashTab(start)
struct ZZbindTBL *start; /* linked list of conversion records */
{
    ZZvoidS *ZZnewObj();
    ZZint ZZhashPtr(),ZZdelObj();
#endif
    ZZlong ii;
    ZZint i,typeRem;
    struct ZZbindTBL *tc,*tcc,*tp,*nxt;

    /* count the number of temp.structures */
    for(tc=start,ii=0; tc;tc=tc->next,ii++)continue;
    /* decide about the size of the hash table */
    ZZbindSize=(ZZint)ii;
    
    /* allocate the hash table */
    ZZbindTable=(struct ZZbindTBL**)ZZnewObj(ZZbindSize*(ZZint)sizeof(char *),1);
    if(!ZZbindTable){ZZmsgS(1,"ZZhashTab()"); return;} /* allocation problem */

    /* load the hash table */
    for(tc=start;tc;tc=tcc){
        tcc=tc->next;
        /* load only objects that have an equivalent in the new organization */
        if(tc->strIndex<0 || ic[tc->strIndex].newType>=0){ 
            i=ZZhashPtr(tc->oldp,ZZbindSize);
            /* check for duplicate entries */
            for(tp=ZZbindTable[i];tp;tp=tp->next){
                /* if the same size, use external(older)type, but ZZinternal data */
                if(tp->oldp==tc->oldp && tp->arrSize==tc->arrSize)break;
            }
            if(tp){ /* duplicate entry, remove tp by copying tc over it */
                typeRem=tp->strIndex; /* remember the external type */
                nxt=tp->next; /* remember the next pointer for the chain */
                if(ZZnoLeak)ZZdelObj(tp->newp); /* tp will be destroyed */
                (*tp)=(*tc);  /* copy tp over tc */
                tp->strIndex=typeRem; /* return to the old type */
                tp->next=nxt; /* reset the next pointer for the chain */
                if(ZZnoLeak)ZZdelObj((char *)tc);
                continue;
            }
            else { /* add it to the hash table */
                tc->next=ZZbindTable[i];
                ZZbindTable[i]=tc;
            }
        }
    }
    return;
}
/* ---------------------------------------------------------------- */
/* sort array by increasing start, and by decreasing end
 * In ZORTECH/MICROSOFT C++ use the C linkage
 */

#ifdef SORT_C_LINKAGE
extern "C" {
ZZint ZZptrSort(const void *p1,const void *p2)
{
    ZZptrIntType i1,i2;
    i1=(ZZptrIntType)((*((struct ZZbindTBL **)(p1)))->oldp);
    i2=(ZZptrIntType)((*((struct ZZbindTBL **)(p2)))->oldp);
    if(i1<i2)return(-1);
    if(i1>i2)return(1);
    i1=i1+(*((struct ZZbindTBL **)(p1)))->arrSize;
    i2=i2+(*((struct ZZbindTBL **)(p2)))->arrSize;
    if(i1<i2)return(1); /* now reversed order */
    if(i1>i2)return(-1);
    return(0);
}
}
#else
#ifdef ZZ_ANSI
ZZint ZZptrSort(const void *p1,const void *p2)
#else
ZZint ZZptrSort(p1,p2)
void *p1,*p2;
#endif
{
    ZZptrIntType i1,i2;
    i1=(ZZptrIntType)((*((struct ZZbindTBL **)(p1)))->oldp);
    i2=(ZZptrIntType)((*((struct ZZbindTBL **)(p2)))->oldp);
    if(i1<i2)return(-1);
    if(i1>i2)return(1);
    i1=i1+(*((struct ZZbindTBL **)(p1)))->arrSize;
    i2=i2+(*((struct ZZbindTBL **)(p2)))->arrSize;
    if(i1<i2)return(1); /* now reversed order */
    if(i1>i2)return(-1);
    return(0);
}
#endif
/* ---------------------------------------------------------------- */
#ifdef ZZ_ANSI
ZZint ZZppSort(const void *p1,const void *p2)
#else
ZZint ZZppSort(p1,p2)
void *p1,*p2;
#endif
{
    ZZptrIntType i1,i2;
    i1=(ZZptrIntType)(((struct AuxList *)(p1))->ptr->oldp);
    i2=(ZZptrIntType)(((struct AuxList *)(p2))->ptr->oldp);
    if(i1<i2)return(-1);
    if(i1>i2)return(1);
    i1=((struct AuxList *)(p1))->ptr->arrSize;
    i2=((struct AuxList *)(p2))->ptr->arrSize;
    if(i1<i2)return(1); /* now reversed order */
    if(i1>i2)return(-1);
    return(0);
}
/* ---------------------------------------------------------------- */
/* read the first part of the bind file, compare the old and new structure
 * records, and create the index conversion array.
 *
 * In the process, construct the array of the old types. Because we
 * do not know their number ahead of time, we have to collect them as
 * a linked list first, and then convert the list into an array.
 */
#ifdef ZZ_ANSI
static VerCntrl *ZZiCnv(FILE *fp,ZZint *n)
{
    ZZint ZZdelObj(char *p);
    ZZvoidS *ZZnewObj(ZZint size,ZZint ini);
#else


static VerCntrl *ZZiCnv(fp,n)
FILE *fp; /* file to read from, in case of ASCII format */
ZZint *n;   /* size of the returned index array */
/* returns pointer to the beginning of the index array, NULL if error */
{
    ZZint ZZdelObj();
    ZZvoidS *ZZnewObj();
#endif
    ZZint i,k,m,nSize,sSize,r,err,bb,np,space;
    char nn[ZZ_BUFS];
    struct ZZstrLST *str,*tp;
    ZZtypeList *start,*sn,*sp;
    err=0;
    sSize=(ZZint)sizeof(struct ZZstrLST);
    start=NULL;
    np=0;
    for((*n)=0;;(*n)++){ /* count number of old types, as you read */
        str=(struct ZZstrLST*)ZZnewObj(sSize,0);
        sp=(ZZtypeList*)ZZnewObj((ZZint)sizeof(struct ZZtypeList),0);
        if(!str || !sp){
	    ZZmsgS(1,"old type table, readBind()"); /* allocation problem */
	    return(NULL);
        }
        sp->type=str;
        sp->next=start; /* old types will be in the reversed order */
        start=sp;  

        if(ZZbindASCII){
            if(!fgets(ZZbuff,ZZ_BUFS,fp)){
                ZZmsg(41); /* error: short beginning of the ASCII file */
                break;
            }
            if(ZZnTbType==9){
#ifdef Windows64
            sscanf(ZZbuff,"%s %I64d %I64d %I64d %I64d %I64d %I64d %I64d %I64d %I64d %I64d", nn,&(str->start),
#else
            sscanf(ZZbuff,"%s %d %d %d %d %d %d %d %d %d %d", nn,&(str->start),
#endif
                &(str->size),&(str->numPtr),&(str->selfIndex),&(str->propIndex),
                &(str->timeIndex),&(str->arrayIndex),&(str->ptrInd),
                &(str->inhInd),&(str->vPtr));
                str->vObj[0]=NULL;
            }
            else if(ZZnTbType==8){
#ifdef Windows64
            sscanf(ZZbuff,"%s %I64d %I64d %I64d %I64d %I64d %I64d %I64d %I64d", nn,&(str->start),
#else
            sscanf(ZZbuff,"%s %d %d %d %d %d %d %d %d", nn,&(str->start),
#endif
                &(str->size),&(str->numPtr),&(str->selfIndex),&(str->propIndex),
                &(str->timeIndex),&(str->arrayIndex),&(str->ptrInd));
                str->vObj[0]=NULL;
                str->vPtr=0;
                str->inhInd= -1;
            }
            else if(ZZnTbType==7){
#ifdef Windows64
            sscanf(ZZbuff,"%s %I64d %I64d %I64d %I64d %I64d %I64d %I64d", nn,&(str->start),
#else
            sscanf(ZZbuff,"%s %d %d %d %d %d %d %d", nn,&(str->start),
#endif
                &(str->size),&(str->numPtr),&(str->selfIndex),&(str->propIndex),
                &(str->timeIndex),&(str->arrayIndex));
                str->vObj[0]=NULL;
                str->vPtr=0;
                str->inhInd= -1;
                str->ptrInd=np;
            }
            else ZZmsgDD(5,ZZnTbType,ZZpTbType);
        }
        else {
            if     (ZZnTbType==9)bb=sSize;
            else if(ZZnTbType==8)bb=sSize-2*(ZZint)sizeof(char *);
            else if(ZZnTbType==7)bb=sSize-3*(ZZint)sizeof(char *);
            else ZZmsgDD(5,ZZnTbType,ZZpTbType);

            r=ZZread(fp,(char *)(str),bb,"iCnv:1");
            if(bb!=r){
                ZZmsgD(12,r);/* wrong beginning of the bindary file */
                break;
            }
            if(ZZnTbType<9)str->inhInd= -1;
            if(ZZnTbType<8)str->ptrInd=np;
            nSize=ZZptrToInt(str->strName);
            r=ZZread(fp,nn,nSize,"iCnv:2");
            if(nSize!=r)ZZmsgD(13,r); /* wrong records on the bind file */
        }
        np+=str->numPtr;
        str->strName=(char *)ZZnewObj((ZZint)strlen(nn)+1,0);
        if(!(str->strName)){
	    ZZmsgS(1,"old type name, readBind()"); /* allocation problem */
	    return(NULL);
        }
        strcpy(str->strName,nn);

	if(str->numPtr<0)break;
        /* compare the object size with the space needed for the pointers */
        space=str->start + ((str->numPtr) * (ZZint)sizeof(char *));
        if(str->timeIndex>=0)space+=4;
        if(space>str->size){
            if(ZZbindASCII)while(space>str->size)(str->size)+=(2*(str->numPtr));
            else {ZZmsgS(35,nn); err++;}
        }
    }
    if(str->start==0){ /* flags data from a big memory block */
        if(ZZbindASCII){
            if(!fgets(ZZbuff,ZZ_BUFS,fp)){
                ZZmsg(41); /* error: short beginning of the ASCII file */
            }
#ifdef LARGE_POINTER
            sscanf(ZZbuff,"%lu %lu %lu",
#else
            sscanf(ZZbuff,"%u %u %u",
#endif
                               &(bBlock.start),&(bBlock.end),&(bBlock.pool));
        }
        else {
            r=ZZread(fp,(char *)(&(bBlock)),sizeof(struct bigBlock),"iCnv:3");
            if(r!=(ZZint)sizeof(struct bigBlock))ZZmsgD(13,r);
        }
        ZZmsgSS(21,bBlock.start,bBlock.pool);
    }
    else bBlock.start=bBlock.end=bBlock.pool=NULL;
        


    /* prepare the oldTypes array, and the conversion array */
    oldTypes=(struct ZZstrLST*)ZZnewObj(((*n)+1)*(ZZint)sizeof(struct ZZstrLST),0);
    ic=(VerCntrl*)ZZnewObj(((*n)+1)*(ZZint)sizeof(struct VerCntrl),0);
    if(!oldTypes || !ic){
	ZZmsgS(1,"readBind(), array ic"); /* allocation problem */
	return(NULL);
    }
    for(i=0;i<(*n);i++){
        ic[i].newType= -1;
        ic[i].compatible=0;
    }
    for(sp=start, i=(*n); sp; sp=sp->next, i--) oldTypes[i]=(*(sp->type));

    /* setup the conversion list */
    for(m=0;ZZsList[m].numPtr>=0;m++)continue; /* count new types */
    for(i=0, tp=oldTypes;tp[i].numPtr>=0;i++){
        /* test first for the most frequent case */
        ic[i].newType=(-1);
	if(i<m && !strcmp(tp[i].strName,ZZsList[i].strName))ic[i].newType=i;
	else {
	    for(k=0;k<m;k++){
                if(!strcmp(tp[i].strName,ZZsList[k].strName))break;
            }
	    if(k<m)ic[i].newType=k;
	    else if(!varOrg) {
		err++;
		ZZmsgS(18,tp[i].strName); /* %s not in the new organization */
	    }
	}
	k=ic[i].newType;
	if(k>=0){
            /* first, rough check */
	    if(tp[i].numPtr==ZZsList[k].numPtr &&
               tp[i].start==ZZsList[k].start &&
               tp[i].size==ZZsList[k].size &&
               tp[i].selfIndex==ZZsList[k].selfIndex)ic[i].compatible=1;
            if(!varOrg){
                if(ic[i].compatible==0){
		    ZZmsgSDDD(0,tp[i].strName,ZZsList[k].start,
                                      ZZsList[k].numPtr,ZZsList[k].selfIndex);
		    /* error for %s, start=%d numPtr=%d selfIndex=%d */
		    err++;
	        }
	    }
        }
    }

    /* release the linked list, which is not needed any more, but keep names */
    for(sp=start; sp; sp=sn){
        sn=sp->next;
        if(!strcmp("ZZendMark",sp->type->strName))ZZdelObj(sp->type->strName);
        ZZdelObj((char *)(sp->type));
        ZZdelObj((char *)sp);
    }

    if(err>0){
	ZZmsgD(14,err); /* %d errors between the old and new organizations */
	ZZdelObj((char *)ic);
	ic=NULL;
    }
    return(ic);
}
/* ---------------------------------------------------------------- */
/* Adjust/Create a new big-block of memory for the new data */
#ifdef ZZ_ANSI
static void getNewBlock(void)
{
#else


static void getNewBlock()
{
#endif
    ZZptrIntType start,pool,dSize,oSize;
    ZZint oldS,newS;

    start=(ZZptrIntType)(bBlock.start);
    pool =(ZZptrIntType)(bBlock.pool);
    dSize=pool-start;
    
    if(ZZmemSwitch==0)createBlock(); /* if no current block create a new one */
    else {    /* there is an active big block of memory */
        oSize=(ZZptrIntType)ZZmemEnd - (ZZptrIntType)ZZmemPool;
        if(oSize>=dSize){
            bBlock.offset=(ZZsigIntType)(ZZmemPool)-(ZZsigIntType)(start);
            ZZmemPool=ZZmemPool+dSize;
            ZZmemSwitch=1;
        }
        else { /* old block not big enough, discard it and create a new one */
            newS=ZZptrToInt((char *)dSize);
            oldS=ZZptrToInt((char *)oSize);
            ZZmsgDD(6,oldS,newS);
            createBlock();
        }
    }
}
/* ---------------------------------------------------------------- */
/* Create a new big-block of memory without any checking */
#ifdef ZZ_ANSI
static void createBlock(void)
{
    ZZvoidS *ZZnewObj(ZZint size,ZZint ini);
#else


static void createBlock()
{
    ZZvoidS *ZZnewObj();
#endif
    ZZptrIntType start,end,pool,nSize,dSize;
    ZZint sz;
    char **p;

    ZZmemSwitch=0; /* disable active block, if any - important for newObj() */

    start=(ZZptrIntType)(bBlock.start);
    end  =(ZZptrIntType)(bBlock.end);
    pool =(ZZptrIntType)(bBlock.pool);
    nSize=end-start;
    dSize=pool-start;
    p=(char **)(&nSize);

    sz=ZZptrToInt(*p); /* this is really a conversion of nSize into sz */
    ZZmemStart=(char *)ZZnewObj(sz,0);
    if(ZZmemStart)ZZmemSwitch=1;
    else {
        nSize=dSize;
        sz=ZZptrToInt(*p);
        ZZmsgD(24,sz);
        ZZmemStart=(char *)ZZnewObj(sz,0);
        if(ZZmemStart)ZZmemSwitch=1;
        else ZZmsgD(25,sz);
    }

    if(ZZmemSwitch==1){
        ZZmemEnd=ZZmemStart+nSize;
        ZZmemPool=ZZmemStart+dSize;
        bBlock.offset=(ZZsigIntType)(ZZmemStart)-(ZZsigIntType)(start);
    }
}
/* ---------------------------------------------------------------- */
/* read the rest of the file, record temporary conversion table.
 * Note that the order of records in the table is the same as
 * the records on the file. This will be later important to recover
 * the main entries to the organization, which are n first.
 * fp may hide the file handle, if write()/read() are used.
 */
#ifdef ZZ_ANSI
static struct ZZbindTBL *ZZtmpCnv(FILE *fp,ZZint n,char **oldPtrList,
ZZint allCompat,ZZint numKeys)
{
    void ZZgetPtrs(FILE *fp,char *p,struct ZZstrLST *s,ZZint t,char **pList);
    ZZint ZZioFunction(FILE *fp,ZZint mode,ZZint type,char *p,ZZint strSize);
    ZZint ZZfindSize(struct ZZstrLST *,ZZint);
    ZZvoidS *ZZnewObj(ZZint size,ZZint ini);
#else


static struct ZZbindTBL *ZZtmpCnv(fp,n,oldPtrList,allCompat,numKeys)
FILE *fp; /* ASCII file to read from, already open */
ZZint n;    /* size of table ic[] */
char **oldPtrList; /* list of old pointer names */
ZZint allCompat; /* 1 if all types are compatible, 0 otherwise */
ZZint numKeys;   /* number of keys */
/* returns start of the temp.conversion table, NULL if problems */
{
    void ZZgetPtrs();
    ZZint ZZioFunction();
    ZZint ZZfindSize();
    ZZvoidS *ZZnewObj();
#endif
    ZZptrIntType x1,x2; /* old range of the last allocated object */
    ZZptrIntType y1,y2; /* old range of the next object, as read from disk */
    char *lastObj;      /* last allocated object, new address */
    ZZint lastType;       /* type of the last object */
    ZZint justUpdate; /* =1 merge into existing object possible, =0 otherwise */

    ZZint nk,kk,num,bSize,size,type,k,err,ts,cpTp,fSize,fType,delType,ki,nfs;
    ZZint newSize,nSize,lastSz,strSz;
    char *newp,*p,*pp,*fObj;
    struct ZZbindTBL *sc,*tc,*last;
    struct ZZbinStore bs;
    struct ZZarray *ap;

    fSize=0;
    err=justUpdate=kk=lastType=newSize=0;
    x1=x2=0;
    lastObj=NULL;
    bSize=(ZZint)sizeof(struct ZZbinStore);
    sc=last=NULL;
    for(nk=0;;nk++){ /* loop ends on negative size header */
        if(ZZbindASCII){
          if(!fgets(ZZbuff,ZZ_BUFS,fp))break;
#ifdef LARGE_POINTER
#ifdef Windows64
          sscanf(ZZbuff,"%I64u %I64d %I64d %I64d",&(bs.ptr),&(bs.strInd),&(bs.size),&num);
#else 
          sscanf(ZZbuff,"%lu %d %d %d",&(bs.ptr),&(bs.strInd),&(bs.size),&num);
#endif
#else
          sscanf(ZZbuff,"%u %d %d %d",&(bs.ptr),&(bs.strInd),&(bs.size),&num);
#endif
	
        }
        else {
          if(ZZread(fp,(char *)(&bs),bSize,"cmpCnv1") != bSize)break;
        }

	if(bs.strInd==(-1))strSz=bs.size; else strSz=0;

        if(bs.size<0)break; /* marks of the last record */
        newSize=bs.size*num;
        if(bs.strInd==(-1) || bs.strInd<-5)newSize=bs.size;
        if(bs.strInd==(-5))newSize=num*(ZZint)sizeof(char *);
    
        justUpdate=0;
        if(allCompat && nk>numKeys && lastType>=0 && bs.strInd>=0){
            y1=(ZZptrIntType)(bs.ptr);
            y2=y1+newSize;
            if(y1>=x1 && y2<=x2 && y1<x2){
                newp=(char *)((ZZptrIntType)lastObj+(y1-x1));
                justUpdate=1;
            }
        }

        if(ZZbindASCII){
            type=bs.strInd;
            size=ZZfindSize(oldTypes,type);

            /* when transferring to a larger memory model, adjust size */
            /* For more details, see comments at ZZgetPtrs() */
            if(type>=0)nSize=
                oldTypes[type].start+(oldTypes[type].numPtr)*sizeof(char *);
            else nSize=0;
            if(nSize>size){size=nSize;} else nSize=0;
            kk=size*num;
            if(bs.strInd==(-1) || bs.strInd<-5)kk=bs.size;
            if(bs.strInd==(-5))kk=num*(ZZint)sizeof(char *);
            
            if(!justUpdate){
#ifdef LARGE_POINTER
                if(ZZmemSwitch==1)newp=(char *)((ZZlong)(bs.ptr)+bBlock.offset);
#else
                if(ZZmemSwitch==1)newp=bs.ptr+bBlock.offset; /* big block */
#endif
                else {
	                // temporarily,string may include also endofline character
		            if(type==(-1))newp=(char *)ZZnewObj(kk+1,0);
		            else          newp=(char *)ZZnewObj(kk,0);
		        }

                x1=(ZZptrIntType)(bs.ptr);
                x2=x1+kk;
                lastObj=newp;
		lastSz=kk;
                lastType=bs.strInd;
            }
            if(!newp){
	        ZZmsgD(15,kk);/* allocation problem bs.size= in readBind */
	        return(NULL);
            }
            if(bs.strInd!=(-4))bs.size=kk; /* if condition added May 19/95 */
                        /* object treated as having this possibly new size */
            nfs=kk; /* will be replaced if the new size needed */

            if(type<0)cpTp=1;
            else if(ic[type].compatible)cpTp=1;
            else cpTp=0;

            /* when types not compatible, allocate future object now */
            if(type<0)fType=type; else fType=ic[type].newType;
            if(type>=0 && fType<0)delType=1; else delType=0;
            if(!cpTp && !delType){
	        fSize=ZZsList[fType].size;
                nfs=num*fSize;
	        fObj=(char*)ZZnewObj(nfs,0);
                if(!fObj){
	            ZZmsgS(1,"ZZtmpCnv()"); /* allocation problem in ZZtmpCnv */
	            return(NULL);
                }
            }
            else fObj=NULL;

            /* initialize the object: NULL pointers for non-compatible types,
             * virtual pointers from the master in C++ */
            if(fType>=0)p=ZZsList[fType].vObj[0]; else p=NULL;
            if(fObj)pp=fObj; else pp=newp;
            if(fType>=0 && p){
                for(k=kk=0;k<nfs;k++){ /* k=byte index, kk=object index */
                    pp[k]=p[kk];
                    kk++;
                    if(kk>=ZZsList[fType].size)kk=0;
                }
            }
            else if(fObj)for(k=0;k<nfs;k++)fObj[k]=0;

            for(k=kk=0, p=newp, pp=fObj; k<num; k++, p+=size){
                /* For incompatible types, getPtrs reads pointers into old type,
                 * next call to ZZioFunction reads attributes into new type,
                 * call to oneShuffle() will merge them later.
                 * For compatible types, ZZioFunction does it all. */
                if(delType){
                    /* if type had pointers, skip pointer record */
                    if(oldTypes[type].numPtr>0){
                        fgets(ZZbuff,ZZ_BUFS,fp);
                    }

                    /* if no pointers, there must be attributes */
                    if(oldTypes[type].numPtr<=0){
                        fgets(ZZbuff,ZZ_BUFS,fp);
                    }
                    else { /* no attributes if pointers cover the whole type */
                        ki=oldTypes[type+1].ptrInd - 1;
                        if(oldTypes[type].start>0 ||
                        oldTypes[type].size>oldOff[ki].offset+oldOff[ki].oSize){
                            fgets(ZZbuff,ZZ_BUFS,fp);
                        }
                    }
                }
                else if(cpTp){
                    if(ZZioFunction(fp,0,fType,p,strSz)){ kk=1; break; }
                }
                else {
                    if(oldTypes[type].numPtr>0) /* avoid when no pointers */
                        ZZgetPtrs(fp,p,oldTypes,type,oldPtrList);
                    if(ZZioFunction(fp,2,fType,pp,strSz)){ kk=1; break; }
                }
                if(pp)pp=pp+fSize;
            }
            if(kk){
                ZZmsgSD(12,p,type); /* error1 in ASCII format when readBind() */
                err++;
                break;
            }
            if(!cpTp){
                oneShuffle(&newp,type,num,fObj,nSize);
            }
        }        /* end of the ASCII case */

        else {   /* binary case */
            if(!justUpdate){
#ifdef LARGE_POINTER
                if(ZZmemSwitch==1)newp=(char *)((ZZlong)(bs.ptr)+bBlock.offset);
#else
                if(ZZmemSwitch==1)newp=bs.ptr+bBlock.offset; /* big memory block */
#endif
	        else newp=(char *)ZZnewObj(bs.size,0);
                x1=(ZZptrIntType)(bs.ptr);
                x2=x1+kk;
                lastObj=newp;
                lastType=bs.strInd;
            }
            if(!newp){
	        ZZmsgD(15,bs.size);/* allocation problem bs.size= in readBind */
	        return(NULL);
            }

            if(ZZread(fp,newp,bs.size,"tmpCnv:2")!=bs.size){
                ZZmsg(44); /* error in binary format when readBind() */
                err++;
                break;
            }
        }

        /* type reference in array headers may need conversion */
        if(bs.strInd==(-4) && ic){
            ap=(ZZarray *)newp;
            if(ap->strType>=0)ap->strType=ic[ap->strType].newType;
            if(ap->targType>=0)ap->targType=ic[ap->targType].newType;
        }

        if(bs.strInd<0){} /* plain block is OK */
	else if(bs.strInd>=n||ic[bs.strInd].newType<0){
            if(!varOrg){
                err++;
                ZZmsgD(17,bs.strInd); /* wrong structure index in readBind() */
            }
            continue; /* skip unused object types */
        }

        if(!justUpdate){
	    ts=(ZZint)sizeof(struct ZZbindTBL);
	    tc=(struct ZZbindTBL*)ZZnewObj(ts,0);
            if(!tc){
	        ZZmsgD(16,ts); /* allocation problem ZZbindTBL=%d in readBind */
	        return(NULL);
            }
            if(last)last->next=tc;
            if(!sc)sc=tc;
            last=tc;
	    tc->next=NULL; /* new object at the end of the chain */
	    tc->oldp=bs.ptr;
	    tc->newp=newp;
	    tc->strIndex=bs.strInd;
	    tc->arrSize=bs.size;
        }
    }
    return(sc);
}
/* ---------------------------------------------------------------- */
/* Read data that was originally in the same block of memory.
 * The new block for this data has been set up already, and is
 * available with offset bBlock.offset
 */
#ifdef ZZ_ANSI
static void getNewData(FILE *fp,char **pp,char **tp,ZZint n)
{
    ZZint ZZioFunction(FILE *fp,ZZint mode,ZZint type,char *p,ZZint strSz);
    ZZint ZZfindSize(struct ZZstrLST *,ZZint);
    ZZvoidS *ZZnewObj(ZZint size,ZZint ini);
#else


static void getNewData(fp,pp,tp,n)
FILE *fp; /* file to read from, already open */
char *pp[]; /* array to record key entries */
char *tp[]; /* array to record types of key entries */
ZZint n;    /* size of table ic[] */
{
    ZZint  ZZioFunction(), ZZfindSize();
    ZZvoidS *ZZnewObj();
#endif
    struct ZZbinStore bs;
    ZZint i,k,kk,size,type,fType,num,err,bSize,strSz;
    char *newp,*p;

    err=0;
    bSize=(ZZint)sizeof(struct ZZbinStore);
    for(i=0;;){ /* i counts key entries, loop ends on negative size header */
        if(ZZbindASCII){
          if(!fgets(ZZbuff,ZZ_BUFS,fp))break;
#ifdef LARGE_POINTER
          sscanf(ZZbuff,"%lu %d %d %d",&(bs.ptr),&(bs.strInd),&(bs.size),&num);
#else
          sscanf(ZZbuff,"%u %d %d %d",&(bs.ptr),&(bs.strInd),&(bs.size),&num);
#endif
        }
        else {
          if(ZZread(fp,(char *)(&bs),bSize,"getNewData:1")!=bSize)break;
        }
	if(bs.strInd==(-1))strSz=bs.size; else strSz=0;

        if(bs.size<0)break; /* marks of the last record */
        type=bs.strInd;
        size=ZZfindSize(oldTypes,type);

        if(ZZbindASCII){

#ifdef LARGE_POINTER
            if(ZZmemSwitch==1)newp=(char *)((ZZlong)(bs.ptr)+bBlock.offset);
#else
            if(ZZmemSwitch==1)newp=bs.ptr+bBlock.offset; /* big memory block */
#endif
            else newp=(char *)ZZnewObj(bs.size,0);
            if(!newp){
	        ZZmsgD(15,bs.size);/* allocation problem bs.size= in readBind */
	        return;
            }

            if(type<0)fType=type; else fType=ic[type].newType;

            for(k=kk=0, p=newp; k<num; k++, p+=size){
                if(ZZioFunction(fp,0,fType,p,strSz)){
                    kk=1;
                    break;
                }
            }
            if(kk){
                ZZmsgSD(17,p,type); /* error2 in ASCII format when readBind() */
                err++;
                break;
            }
        }
        else {
#ifdef LARGE_POINTER
            if(ZZmemSwitch==1)newp=(char *)((ZZlong)(bs.ptr)+bBlock.offset);
#else
            if(ZZmemSwitch==1)newp=bs.ptr+bBlock.offset; /* big memory block */
#endif
	    else newp=(char *)ZZnewObj(bs.size,0);
            if(!newp){
	        ZZmsgD(15,bs.size);/* allocation problem bs.size= in readBind */
	        return;
            }

            if(ZZread(fp,newp,bs.size,"getNewData:2")!=bs.size){
                ZZmsg(44); /* error in binary format when readBind() */
                err++;
                break;
            }
            if(type<0)fType=type; else fType=ic[type].newType;
        }

        /* convert all ZZinternal pointers to the new location */
        ZZbindPtrs(newp,fType,bs.size,1,0);

        if(fType>=0 && i<n){ /* is this a candidate for the key entry? */
            for(k=0;k<i;k++){ /* is this entry already recorded ? */
                if(pp[k]==newp)break;
            }
            if(k>=i){
                pp[i]=newp;
                tp[i]=ZZsList[fType].strName;
                i++;
            }
        }
    }
}
/* ---------------------------------------------------------------- */
/* For a given object, reset virtual function pointers.
 *
 * Originally, this was done by by calling ZZvSet() located in zzfunc.c,
 * which is a neat programming trick. For most compilers, the new()
 * operator does not modify the given piece of memory, except for
 * inserting the appropriate v.f. and v.c. pointers.
 * Prior to this call, ZZvirtCntr was set to the object
 * pointer, which triggered the use of old object, instead of
 * allocating a new one in ZZmassAlloc().
 *
 * A neat trick was recommended by James Coplien, and I had hard time
 * to get it work. The critical step is to make special constructors
 * dependent on the same type(!) of constructors in zzincl.h
 *
 * For ZZmemSwitch=2, also mark the pointers in the bitmap.
 * That is done by using vObj, essentially as the mask
 * where everything is 0 except for vf. and vc. pointers.
 * [Jiri Soukup, July 3/92]
 */
#ifdef ZZ_ANSI
void ZZsetVirt(char *obj,char **mst,ZZint type,ZZint val)
{
    void ZZmarkPtr(char **,ZZint);
    void ZZvSet(ZZint);
#else
void ZZsetVirt(obj,mst,type,val)
char *obj; /* pointer to the object */
char **mst; /* pointer to the master with correct virtual pointers */
ZZint type;  /* type index */
ZZint val; /* 0 or 1, value to mark bitmap, only when ZZmemSwitch=2 */
{
    void ZZmarkPtr();
    void ZZvSet();
#endif
    ZZint i,sc,sz,justInt;
    char **p1,**p2;
#define NEAT_TRICK
#ifndef NEAT_TRICK
    ZZint *i1,*i2;
    char *s1,*s2,*t;
    ZZptrIntType *c1,*c2;
    union {
        char *p;
        ZZint i[2];
    }uo,um;
#endif


    justInt=0;
#ifdef BORLAND3
#ifdef LARGE_POINTER
    justInt=1;
#endif
#endif
    justInt=justInt; /* avoid compiler warnings */

    sc=(ZZint)sizeof(char *);
    sz=ZZsList[type].size;
    if(type<0)return; /* just to be on the safe side */

#ifdef NEAT_TRICK
    ZZvirtCntr=obj;
    if(type>=0)ZZvSet((ZZint)type); /* sets vf. and vc. pointers */
#else
    for(i=0, s1=mst[0], s2=mst[1], t=obj; i<sz; i++, s1++, s2++, t++){
        if(*s2=='\0')continue;
        else if(*s2=='F'){
            i1=(ZZint *)s1;
            i2=(ZZint *)t;
            *i2=(*i1);
        }
        else if(*s2=='C'){
            if(justInt){
                i1=(ZZint *)s1;
                i2=(ZZint *)t;
                uo.p=obj;
                um.p=mst[0];
                *i2=uo.i[0] + ((*i1) - um.i[0]);
            }
            else {
                c1=(ZZptrIntType *)s1;
                c2=(ZZptrIntType *)t;
                *c2=(ZZptrIntType)obj + ((*c1) - (ZZptrIntType)(mst[0]));
            }
        }
    }
#endif

    /* this loop works only when sizeof(char *)==sizeof(ZZint) */
    if(ZZmemSwitch==2){ /* record vf. and vc. pointers in bitmap */
        for(i=0, p1=(char **)(mst[0]), p2=(char **)obj; i<sz; p1++, p2++, i+=sc){
            if(*p1){ /* vfunc.ptr or vclass.ptr */
                ZZmarkPtr((char **)p2,val);
            }
        }
    }
}
/* ---------------------------------------------------------------- */
/* For a given new object
 *  - initializes all pointers on the object as 1
 *  - sets all bytes for virt pointers as 0
 *
 * The function uses vObj[1] where all vf pointers are marked
 * by 'F' in the leading character, and all vc pointers
 * by 'C' in the leading character (all other characters are '\0').
 * [Jiri Soukup, Aug 21/92]
 */
#ifdef ZZ_ANSI
void ZZoneMask(char *m,ZZint type)
{
#else
void ZZoneMask(m,type)
char *m; /* pointer to the mask */
ZZint type;  /* type index */
{
#endif
    ZZint i,k,sz,n,fsz,csz,ptrBndry;
    char *v;

    if(type<0)return; /* just to be on the safe side */
    n=ZZsList[type].size;
    v=ZZsList[type].vObj[1];
    for(i=0;i<n;i++)m[i]=1;

    ptrBndry=fsz=sizeof(ZZint);
    csz=sizeof(char *);
#ifdef BORLAND3
    csz=fsz;
#endif
#ifdef MAC
    ptrBndry=sizeof(short);
#endif

    for(i=0;i<n;i+=ptrBndry){
        if(v[i]=='F')sz=fsz;
        else if(v[i]=='C')sz=csz;
        else sz=0;
        if(sz){
            for(k=0;k<sz;k++)m[i+k]=0;
        }
    }
}
/* ---------------------------------------------------------------- */
/* PoZZinter conversion using binary search.
 * This function handles some special situations that cannot be converted
 * with the hash table:
 * - PoZZinter which leads into an existing array must be replaced by
 * a pointer leading into the same relative position.
 * - In C++, pointer leading inside an object bust be replaced 
 * by a pointer to the same subclass which, for Intelligent Database,
 * may have a different offset.
 *
 * This function returns pointer into the middle of the nearest lower
 * object, using the appropriate offset. 
 */
#ifdef ZZ_ANSI
static char *ZZbArray(char *p,ZZint *err)
{
#else


static char *ZZbArray(p,err)
char *p;   /* old pointer to be found */
ZZint *err;  /* add 1 to the count, if error encountered */
/* returns the new pointer, NULL if error */
{
#endif
    ZZint ind,oOff,nOff,oSz,nSz,oTp,nTp;
    ZZlong i1,i2,k;
    char *ret;
    ZZptrIntType pk,pp;

    if(!p || ZZbindArr.size()<=0)return(NULL); /* additional protection */

    ret=NULL;
    /* k=-2 NULL pointer, =-1 cannot find, k>=0 index found */
    if(!p){k= -2; goto CNV_EXIT;}
    k= -1;
    i1=0;
    i2=ZZsaSize-1;
    pp=(ZZptrIntType)p;

    pk=(ZZptrIntType)(ZZbindArr[i1]->oldp);
    if(pk>pp)goto CNV_EXIT;
    if(ZZbindArr[i1]->oldp==p){k=i1; goto CNV_EXIT;}

    pk=(ZZptrIntType)(ZZbindArr[i2]->oldp);
    if(pk<=pp){
        if(pk+ZZbindArr[i2]->arrSize>pp)k=i2;
        goto CNV_EXIT;
    }

    k=(i1+i2)/2;
    while(k>i1){
        pk=(ZZptrIntType)(ZZbindArr[k]->oldp);
        if(pk>pp)i2=k;
	else if(pk<pp)i1=k;
	else goto CNV_EXIT;
	k=(i1+i2)/2;
    }
    if(i1<i2){
        k=i1;
        pk=(ZZptrIntType)(ZZbindArr[k]->oldp);
    }
CNV_EXIT:
    if(k<0){
        if(k== -1)(*err)++;
    }
    else {
        /* pointer must hit an object, not in between */
        if(pk+ZZbindArr[k]->arrSize>pp){
            oTp=ZZbindArr[k]->strIndex; /* old type */
            nTp=ic[oTp].newType;        /* new type */
            oSz=oldTypes[oTp].size; /* old size for this type */
            nSz=ZZsList[nTp].size; /* new size for this type */

            /* if pointing into an array, derive index */
            if(oSz){
                ind=((ZZint)(pp-pk))/oSz;
                pk=pk+(ind*oSz);
            }
            else ind=0;
            if(pk==pp){ /* just hitting middle of array */
                ret=ZZbindArr[k]->newp+(ind*nSz);
            }
                
            if(!ret && ZZinhFLG){ /* In C++ or if member objects used in C */
                /* find the new offset for the old offset of (pp-pk) */
                oOff=ZZpOffset((char *)pp, (char *)pk);
                nOff=findOffset(ZZbindArr[k]->strIndex,-1,oOff);
                if(nOff>=0)ret=ZZbindArr[k]->newp+(ind*nSz)+nOff;
            }
        }
    }
    return(ret);
}
/* ---------------------------------------------------------------- */
/* Set up an array sorted by increasing old starting address and
 * (as the second priority) the decreasing object size. 
 * This time it must be sorted by the beginning of the object */
static void setBindArr(void)
{
    char *ZZrSRfun(char *rPtr,char *tail, ZZTsortFun fun);
    ZZvoidS *ZZnewObj(ZZint size,ZZint ini);
    ZZint ZZdelObj(char *p);
    ZZlong i,n;
    struct ZZbindTBL *tc;
    struct AuxList *ax,*an,*axTail;

    /* traverse the hash table, create indirectly linked ring */
    for(i=0,n=0, axTail=NULL;i<ZZbindSize; i++){
        for(tc=ZZbindTable[i];tc;tc=tc->next){
            ax=(struct AuxList *)ZZnewObj(sizeof(struct AuxList),0);
            if(!ax){ZZmsgS(1,"auxilliary list"); return;};
            ax->ptr=tc;
            if(axTail){ ax->next=axTail->next; axTail->next=ax;}
            else      { axTail=ax; ax->next=ax;}
            n++;
        }
    }
    ZZsaSize=n;



    /* sort the ring */
    axTail=(struct AuxList *)
           ZZrSRfun((char*)(&(axTail->next)),(char*)axTail,ZZppSort);

    /* establish a virtual array */
    ZZbindArr.reset(n);
    if(ZZbindArr.size()!=n){ZZmsgS(1,"virt.array of oldp"); return;}
    /* load the pointers into virt.array, discard the list */
    ax=axTail->next;
    axTail->next=NULL;
    for(i=0;ax;ax=an, i++){
        an=ax->next;
        ZZbindArr[i]=ax->ptr;
        (void)ZZdelObj((char*)ax);
    }
    axTail=NULL;
}
/* ---------------------------------------------------------------- */
// Debugging function which prints the pointer conversion table
// organized by bucket:
void debugCnv(){
    int i,k; char *p; 
    struct ZZbindTBL *tc;
    printf("CONVERSION TABLE ZZbindTBL:");
    for(i=0;i<ZZbindSize; i++){
        printf("i=%d\n",i);
        for(tc=ZZbindTable[i];tc;tc=tc->next){
            printf("old=%d new=%d\n",tc->oldp,tc->newp);
        }
    }
}
    
/* ---------------------------------------------------------------- */
/* Conversion of an old pointer to the new pointer, which is done
 * as a hash table search through the list of old/new pointer pairs
 */
#ifdef ZZ_ANSI
char *ZZbindCnv(char *p,ZZint *err)
{
    ZZint ZZhashPtr(char *p,ZZint size); 
#else


char *ZZbindCnv(p,err)
char *p;   /* old pointer to be found */
ZZint *err;  /* error counter, add 1 in case of conversion error */
/* returns the new pointer, NULL if unsuccessful */
{
    ZZint ZZhashPtr(); 
#endif
    char *ret;
    ZZint i;
    struct ZZbindTBL *tc;
    ret=NULL;
    if(p){
#ifdef LARGE_POINTER
        if(ZZmemSwitch==1)return((char *)((ZZlong)p+bBlock.offset));
#else
        if(ZZmemSwitch==1)return(p+bBlock.offset); /* block memory, offset only */
#endif
        i=ZZhashPtr(p,ZZbindSize);
        for(tc=ZZbindTable[i];tc;tc=tc->next){
            if(tc->oldp==p)break;
        }
        if(tc){ret=tc->newp;
        }
        else {
            ret=NULL;
        }

        /* In rare cases, pointer may lead inside an array or,
         * in C++, into a subclass inside the object */
        if(!ret){
            if(ZZbindArr.size()<=0)setBindArr(); /* first time, setup ZZbindArr */
            ret=ZZbArray(p,err); /* binary search as the last resort */
        }
        
        if(!ret)(*err)++;
    }
    return(ret);
}
/* ---------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZwriteASCII(ZZint strSize,ZZint typeInd,const char *fileName,char *pp,
                  ZZint num,ZZint key)
{
    ZZint ZZioFunction(FILE *fp,ZZint mode,ZZint type,char *p,ZZint strSz);
    void ZZpropASCII(FILE *fp,struct ZZproperty *pp);
    ZZvoidS *ZZnewObj(ZZint size,ZZint ini);
#ifndef ZZcplus
#ifndef MICROSOFT
    FILE *fopen(const char *fn,const char *md);
#endif
#endif
#else


void ZZwriteASCII(strSize,typeInd,fileName,pp,num,key)
ZZint strSize;        /* structure size in bytes */
ZZint typeInd;        /* index of the type, -1 for char string or binary block */
char *fileName;     /* file name for output */
char *pp; /* pointer to the block to be saved */
ZZint num; /* number of elements in the array to be saved */
ZZint key; /* key=1 when key entry, key=0 for writing out an object,
            key= -1 for a sub-object */
{
    ZZint ZZioFunction();
    FILE *fopen();
    void ZZpropASCII(),*ZZnewObj();
#endif
    ZZint i,ii,j,k,kk,m,mm,m1,m2,it,sz,pSize;
    char *t,**tt,*inj;
    struct ZZstrLST s;
    struct ZZproperty **r;
    ZZarray *pArr;
    FileInfo *fi;

    static ZZint level={0}; /* keeps level of the object, 1=parent */
    pSize=sizeof(char*);

    if(pp==NULL)return;
    level++;

    /* derive strSize if a character string */
    if(typeInd== -1 && num==0){num=1; strSize=(ZZint)strlen(pp)+1;}

    /* if the first call, write all the structure records */
    if(!getFile(fileName)){
        if(ZZbindCntrl)ZZbindFile=(FILE *)fileName;
        else ZZbindFile=fopen(fileName,"w");
        if(ZZbindFile) {
            setFile(fileName);
            fi=getFile(fileName);
            ZZbindName=fi->name;
            for(i=0;;i++){
                s=ZZsList[i];
                /* record if the big memory block is being used */
	        if(s.numPtr<0 && ZZmemSwitch && ZZmemStart)s.start=0;

                if(ZZnTbType==9){
#ifdef Windows64
                    fprintf(ZZbindFile,"%s %I64d %I64d %I64d %I64d %I64d %I64d %I64d %I64d %I64d %I64d\n",
#else
                    fprintf(ZZbindFile,"%s %d %d %d %d %d %d %d %d %d %d\n",
#endif
                        s.strName,s.start,s.size,s.numPtr,s.selfIndex,
                        s.propIndex,s.timeIndex,s.arrayIndex,s.ptrInd,s.inhInd,
                        s.vPtr);
                }
                else if(ZZnTbType==8){
#ifdef Windows64
                    fprintf(ZZbindFile,"%s %I64d %I64d %I64d %I64d %I64d %I64d %I64d %I64d\n",
#else
                    fprintf(ZZbindFile,"%s %d %d %d %d %d %d %d %d\n",
#endif
                        s.strName,s.start,s.size,s.numPtr,s.selfIndex,
                        s.propIndex,s.timeIndex,s.arrayIndex,s.ptrInd);
                }
                else if(ZZnTbType==7){
#ifdef Windows64
                    fprintf(ZZbindFile,"%s %I64d %I64d %I64d %I64d %I64d %I64d %I64d\n",
#else
                    fprintf(ZZbindFile,"%s %d %d %d %d %d %d %d\n",
#endif
                        s.strName,s.start,s.size,s.numPtr,s.selfIndex,
                        s.propIndex,s.timeIndex,s.arrayIndex);
                }
                else ZZmsgDD(5,ZZnTbType,ZZpTbType);

	        if(ZZsList[i].numPtr<0)break;
	    }
            if(ZZmemSwitch && ZZmemStart){
#ifdef LARGE_POINTER

#ifdef Windows64
              fprintf(ZZbindFile,"%I64u %I64u %I64u\n",ZZmemStart,ZZmemEnd,ZZmemPool);
#else
              fprintf(ZZbindFile,"%lu %lu %lu\n",ZZmemStart,ZZmemEnd,ZZmemPool);
#endif

#else
              fprintf(ZZbindFile,"%u %u %u\n",ZZmemStart,ZZmemEnd,ZZmemPool);
#endif
            }
            if(ZZpTbType)ZZwrPtrs(ZZbindFile);
            ZZwrInher(ZZbindFile); /* decides by itself whether to print */
        }
    }

    if(ZZbindFile){
        /* write the object itself */
        kk=num*strSize;
#ifdef LARGE_POINTER
#ifdef Windows64
        fprintf(ZZbindFile,"%I64u %I64d %I64d %I64d\n",pp,typeInd,kk,num);
#else
        fprintf(ZZbindFile,"%lu %d %d %d\n",pp,typeInd,kk,num);
#endif
#else
        fprintf(ZZbindFile,"%u %d %d %d\n",pp,typeInd,kk,num);
#endif
        for(i=0, t=pp;i<num;i++, t+=strSize){
            ZZioFunction(ZZbindFile,1,typeInd,t,0);
        }
        if(key==1){ level--; return;}

        /* write out all inherited or injected sub-objects */
        if(ZZiList && typeInd>=0){
            for(i=0, t=pp;i<num;i++, t+=strSize){
                m1=ZZsList[typeInd].inhInd;
                m2=ZZsList[typeInd+1].inhInd;
                for(ii=m1;ii<m2;ii++){
                   if(!strcmp("ZZvirtual",ZZiList[ii].name) 
                                            && level!=1)continue;
                   j=ZZiList[ii].type; /* type of the inserted object */
                   /* inj will be the start of the injected object */
                   inj=t+ZZiList[ii].offset-ZZsList[j].start;
                   it=ZZiList[ii].num; /* is 0 for inherited objects */
                   if(it<=0)it=1;

                   sz=ZZsList[j].size;
                   if(ZZvClassPresent) reduceVClass(j,&sz);
                   ZZwriteASCII(sz,j,fileName,inj,it,-1);
                }
            }
        }

        /* for an array header, write out the whole array */
        if(typeInd== -4){
            pArr=(ZZarray*)pp;
            k=pArr->strType;
            ZZwriteASCII(pArr->size,k,fileName,pArr->array,pArr->num,-1);
        }
    
        /* write out properties and arrays for all members of the array */
        else if(typeInd>=0){
	    m=ZZsList[typeInd].propIndex;
	    mm=ZZsList[typeInd].start;
            m1=ZZsList[typeInd].arrayIndex;
            m2=ZZsList[typeInd].numPtr;
            if(m2>0 && (m>=0 || m1>=0)){
	        for(k=0,t=pp;k<num;k++,t+=strSize){
                    /* selfID will be recovered from strList[] index */
                    if(m>=0){
	                r=(struct ZZproperty **)(t+mm); 
	                ZZpropASCII(ZZbindFile,r[m]);
                                                    /* dump all properties*/
                    }
                    if(m1>=0){
                        for(i=m1, tt=(char**)(t+mm+m1*pSize); i<m2; i++, tt++){
                         ZZwriteASCII((ZZint)sizeof(ZZarray),-4,fileName,*tt,1,-1);
                        }
                    }
                }
	    }
        }
    }
    else ZZmsgSS(8,"ZZwriteASCII",ZZbindName); 
    level--;
    return;
}
/* ----------------------------------------------------------------------- */
/* reduce the given size by the sizes of all contained virtual classes
 * and return the offset of the beginning of the object
 */
#ifdef ZZ_ANSI
void reduceVClass(ZZint type, ZZint *size)
#else
void reduceVClass(type,size)
ZZint type; /* type to recursively process */
ZZint *size; /* size to reduce */
#endif
{
    ZZint n1,n2,n,tp;
    char *nm;

    n1=ZZsList[type].inhInd;
    n2=ZZsList[type+1].inhInd;
    for(n=n1;n<n2;n++){
        tp=ZZiList[n].type;
        nm=ZZiList[n].name;
        if(!strcmp(nm,"ZZrefer") || !strcmp(nm,"ZZvirtual"))
              (*size)=(*size)-ZZsList[tp].size;
    }
}
/* ----------------------------------------------------------------------- */
/* save the whole organization in one command, using a recorded sweap array */
#ifdef ZZ_ANSI
typedef void (*SAFUN)(char *ptr,ZZint type,ZZint size,const char* priv);
ZZint ZZsaveAll(const char *file)
{
    void ZZswpFun(SAFUN saveFun,const char *file);
#else


ZZint ZZsaveAll(file)
char *file; /* file name of where to save */
{
    void ZZswpFun();
#endif
#ifdef MICROSOFT
#ifdef NOT_WIN_NT
    if((020000000000 & GetVersion())==0){
        printf("sorry - this free binary version does not work under WinNT\n");
        return 0;
    }
#endif /* NOT_WIN_NT */
#endif /* MICROSOFT */
    ZZswpFun(saveFun,file);
    return(0);
}
/* ----------------------------------------------------------------------- */
/* free the whole organization in one command, using a recorded sweap array */
#ifdef ZZ_ANSI
ZZint ZZfreeAll(void)
{
    void ZZswpFun(SAFUN,const char *file);
#else


ZZint ZZfreeAll()
{
    void ZZswpFun();
#endif

    ZZswpFun(freeFun,NULL);
    return(0);
}
/* ----------------------------------------------------------------------- */
#ifdef ZZ_ANSI
static void saveFun(char *ptr,ZZint type,ZZint size,const char *priv)
{
    void ZZwriteBind(ZZint size,ZZint type,const char *priv,char *ptr,ZZint num,ZZint key);
#else


static void saveFun(ptr,type,size,priv)
char *ptr;  /* pointer to the object */
ZZint type;   /* name of the structure */
ZZint size;   /* size of the object */
char *priv; /* private information, here file name */
{
    void ZZwriteBind();
#endif
    ZZint num;

    num=1;
    if(size<=0){
        /* treat all unknown objects as character strings */
        type= -1;
        size=(ZZint)strlen(ptr)+1;
        num=0;
    }
    if(ZZbindASCII){
         ZZwriteASCII(size,type,priv,ptr,num,0);
    }
    else ZZwriteBind(size,type,priv,ptr,num,0);
    return;
} 
/* ----------------------------------------------------------------------- */
/* except for ptr, dummy parameters in this case */
#ifdef ZZ_ANSI
static void freeFun(char *ptr,ZZint type,ZZint size,const char *priv)
{
    ZZint ZZdelObj(char *p);
#else


static void freeFun(ptr,type,size,priv)
char *ptr;
ZZint type;
ZZint size; 
char *priv;
{
    ZZint ZZdelObj();
#endif
    ZZarray *a;
    ZZint i,j,k;
    struct ZZproperty *p,*pn,**r;

    k=type;

    /* if array header, remove also the array */
    if(k==(-4)){
        a=(ZZarray*)ptr;
        if(a->array)ZZdelObj(a->array);
    };

    /* if it has properties, remove them also */
    if(k>=0){
        i=ZZsList[k].propIndex;
        j=ZZsList[k].start;
        if(i>=0){
	    r=(struct ZZproperty **)((char*)ptr+j); 
            for(p=r[i];p;p=pn){
                if(p->next==r[i])pn=NULL; else pn=p->next;
                ZZdelObj((char *)p);
            }
        }
    }

    ZZdelObj(ptr);
    priv=priv; size=size; /* shut up compiler messages */
} 
/* ----------------------------------------------------------------------- */
/* save the key entries */
#ifdef ZZ_ANSI
ZZint ZZsaveKeys(const char *fileName,struct ZZstrLST *sL,char **v,char **t,ZZint n)
{
    void ZZwriteBind(ZZint size,ZZint type,const char *priv,char *ptr,ZZint num,ZZint key);
#else


ZZint ZZsaveKeys(fileName,sL,v,t,n)
char *fileName;
struct ZZstrLST *sL; /* ZZstrList[] */
char **v; /* list of the key entries into the organization */
char **t; /* list of types for the key entries */
ZZint n;    /* number of key entries */
/* returns number of entries actually saved */
{
    void ZZwriteBind();
#endif
    ZZint i,j,k;

    ZZsList=sL;
    j=0; /* number of entries actually saved */
    for(i=0;i<n;i++){ 
        for(k=0;ZZsList[k].numPtr>=0;k++){
                         if(!strcmp(ZZsList[k].strName,t[i]))break;
        }
        if(ZZsList[k].numPtr<0){
            ZZmsgS(21,t[i]); /* error in type for the key entry in SAVE: %s */
        }
        else if(v[i]){
            j++;
            if(ZZbindASCII){
                 ZZwriteASCII(ZZsList[k].size,k,fileName,v[i],1,1);
            }
            else ZZwriteBind(ZZsList[k].size,k,fileName,v[i],1,1);
        }
    }
    return(j);
}
/* --------------------------------------------------------------------- */
/* close the output file for SAVE by a header with size= -1 */
#ifdef ZZ_ANSI
void ZZcloseBind(const char * fileName)
{
#else


void ZZcloseBind(fileName)
char *fileName;
{
#endif
    ZZint ZZFUN_gfree();
    struct ZZbinStore b;
    FileInfo *fi;

    fi=getFile(fileName);
    if(!fi){
        if(ZZbindCntrl)ZZmsgD(26,ZZptrToInt(fileName));
        else           ZZmsgS(40,fileName);
        return;
    }
    delFile(fi);
    if(ZZbindASCII){
        fprintf(ZZbindFile,"0 -1 -1 0\n");
        if(!ZZbindCntrl)fclose(ZZbindFile);
    }
    else {
        b.size= -1; b.ptr=NULL; b.strInd= -1;
        ZZwrite(ZZbindFile,(char *)(&b),(ZZint)sizeof(struct ZZbinStore),"in close bind");
        if(!ZZbindCntrl)(void)ZZclose(ZZbindFile);
    }
    ZZbindFile=NULL;
    ZZbindName=NULL;
}
/* --------------------------------------------------------------------- */
/* add a new output file to the ZZinternal list of currently open files */
/* The new file pointer/handle is supposed to be already in ZZbindFile */
#ifdef ZZ_ANSI
static void setFile(const char *fileName)
{
    ZZvoidS *ZZnewObj(ZZint size,ZZint ini);
#else
static void setFile(fileName)
char *fileName;
{
    ZZvoidS *ZZnewObj();
#endif
    FileInfo *fi;
    const char *fn;

    fi=(FileInfo *)ZZnewObj((ZZint)sizeof(struct FileInfo),0);
    if(!fi){ ZZerrFLG=ZZerrFLG|01; ZZmsgS(1,"setFile"); return; }
    fi->next=allFiles;
    allFiles=fi;
    fi->fp=ZZbindFile;
    if(ZZbindCntrl)fn="outsideControl";
    else           fn=fileName;
    fi->name=(char *)ZZnewObj((ZZint)strlen(fn)+1,0);
    if(!(fi->name)){ZZerrFLG=ZZerrFLG|01; ZZmsgS(1,"setFile"); return;}
    strcpy(fi->name,fn);
}
/* --------------------------------------------------------------------- */
/* get an output file from the ZZinternal list 
 * Return file to the FileInfo structure, NULL if file not there.
 * Check both file names and file pointers */
#ifdef ZZ_ANSI
static FileInfo *getFile(const char *fileName)
{
#else
static FileInfo *getFile(fileName)
char *fileName;
{
#endif
    FileInfo *fi;

    for(fi=allFiles;fi;fi=fi->next){
        if(ZZbindCntrl){
            if(fi->fp==((FILE *)fileName))break;
        }
        else {
            if(!strcmp(fileName,fi->name))break;
        }
    }
    if(fi){
        ZZbindFile=fi->fp;
        ZZbindName=fi->name;
    }
    else {
        ZZbindFile=(FILE *)NULL;
        ZZbindName=NULL;
    }
    return(fi);
}
/* --------------------------------------------------------------------- */
/* delete a file from the ZZinternal list of currently open files */
#ifdef ZZ_ANSI
static void delFile(FileInfo *fi)
{
    ZZint ZZdelObj(char *);
#else
static void delFile(fi)
FileInfo *fi;
{
    ZZint ZZdelObj();
#endif
    FileInfo *ff;

    if(!fi)return;
    if(allFiles==fi)allFiles=fi->next;
    else {
        for(ff=allFiles; ff; ff=ff->next){
            if(ff->next==fi){ff->next=fi->next; break;}
        }
    }
    ZZdelObj(fi->name);
    ZZdelObj((char *)fi);
}
/* --------------------------------------------------------------------- */
/* For an old-type object, read in pointers and other registered variables.
 * This task has two potential problems: The old object may have pointers
 * starting on the address which is an illegal word boundary in the new
 * environment - for example at address 14 on MAC, while under SUN-UNIX
 * a pointer must start on a multiple of 4 bytes, otherwise it core dumps.
 * The second problem is that, when converting from shorter pointers to
 * ZZlonger pointers (for example from the DOS medium memory model to UNIX
 * or the large memory model, the old image may not have enough space
 * for the new pointers or, in more complex objects, pointers may mutually
 * overlap.
 *
 * The first problem is solved by copying pointers byte-by-byte
 * into the desired position.
 * The second problem is solved by allocating larger objects when needed,
 * which is done at the beginning of ZZtmpCnv(), and requires a cooperation
 * with function oneShuffle(). ZZtmpCnv() gives it the possibly a larger
 * size (needed for arrays).
 *                    Jiri Soukup, Feb.12/93
 */

#ifdef ZZ_ANSI
void ZZgetPtrs(FILE *fp,char *p,struct ZZstrLST *s,ZZint t,char **pList)
#else


void ZZgetPtrs(fp,p,s,t,pList)
FILE *fp;           /* file to read the next line from */
char *p;            /* start of the object, already allocated */
struct ZZstrLST *s; /* the old type list */
ZZint t;              /* type, index into s[] */
char **pList;       /* old list of pointers and registered variables */
#endif
/* note that the offsets for the individual pointers are globally available
 * from oldOff[] */
{
    ZZint i,i1,i2,k,kk,kd,kc,x;
    char *a,*b,*c,*w;
    static char bb=' ';
    union ZZUNI u;

    if(s[t].numPtr<=0)return;
    if(!fgets(ZZbuff,ZZ_BUFS,fp)){
        ZZmsgS(1,"ZZgetPtrs()"); /* allocation error */
        return;
    }
    i1=s[t].ptrInd;
    i2=s[t+1].ptrInd;
    a=ZZbuff;           /* next number to read */
    for(i=i1; i<i2; i++){
        b=p+oldOff[i].offset; /* starting byte for the next field */
        c=pList[i];
        kk=oldOff[i].oSize;
        for(k=0;k<kk;k+=kd, b+=kd){
            if(i>i1){ /* skip to the next number */
                if(*a==bb)for(;*a==bb;a++)continue;
                for(;*a!=bb;a++)continue;
                for(;*a==bb;a++)continue;
            }
            /* read the value into a temporary storage - union */
            if(c[0]=='i')      {sscanf(a,"%d",&(u.i)); kd=(ZZint)sizeof(ZZint);}
            else if(c[0]=='f') {sscanf(a,"%f",&(u.f)); kd=(ZZint)sizeof(float);}
            else if(c[0]=='c') {sscanf(a,"%d",&x); u.c=x; kd=(ZZint)sizeof(char);}
#ifdef LARGE_POINTER
            else               {sscanf(a,"%lu",&(u.p)); kd=(ZZint)sizeof(char *);}
#else
            else               {sscanf(a,"%u",&(u.p)); kd=(ZZint)sizeof(char *);}
#endif
            /* copy by byte, to avoid problems with the word boundary */
            for(kc=0, w=(char *)(&(u.p));kc<kd;kc++)b[kc]=w[kc];
        }
    }
    return;
}
/* ---------------------------------------------------------------- */
/* save a given structure or an array of structures on the disk,
 * strName="char" and num=0 means a character string, for which
 * strSize must be derived.
 * strName="char" and num>0 means a block of bytes.
 * Important: this function saves properties and all arrays with the object.
 * For properties, this is simply done by a call to ZZwriteProp(). For
 * the arrays, this is much more complicated (2-level recursion).
 * First all pointers to all headers are detected and headers stored,
 * then for each header, the array itself is stored. However, the array
 * can have arrays associated with it, and so on.
 *   I left all the recursion related to arrays in this one function.
 * Breaking it into smaller functions would only hide the recursion;
 * the smaller functions would call themselves in a circle.
 */
void ZZwriteBind(ZZint strSize,ZZint typeInd,const char *fileName,char *pp,ZZint num,ZZint key)
// ZZint strSize;         structure size in bytes
// ZZint typeInd;         type index, -1 for a char string or binary block
// char *fileName;      file name for output
// // char *pp;  pointer to the block to be saved
// ZZint num;  number of elements in the array to be saved
// ZZint key;  key=1 for key entry, key=0 for writing out regular object
{
    ZZvoidS *ZZnewObj(ZZint size,ZZint ini);
    void ZZsubPropArr(ZZint typeInd, char *t,const char *fileName,ZZint key,
                                      ZZint strSize,ZZint num);

    ZZint i,ii,j,n,nn;
    struct ZZbinStore b;
    struct ZZstrLST s;
    ZZarray *pArr;
    FileInfo *fi;

    if(pp==NULL)return;

    /* derive strSize if a character string */
    if(typeInd== -1 && num==0){num=1; strSize=(ZZint)strlen(pp)+1;}

    /* if the first call, write all the structure records */
    if(!getFile(fileName)){ /* first operation on this file */
        if(ZZbindCntrl)ZZbindFile=(FILE *)fileName;
        else ZZbindFile=ZZopen(fileName,"w");
        if(ZZbindFile){
            setFile(fileName);
            fi=getFile(fileName);
            ZZbindName=fi->name;
            for(i=0;;i++){
                s=ZZsList[i];
                /* use the name pointer to pass the size of the next record */
                ii=(ZZint)strlen(ZZsList[i].strName)+1;
                s.strName=ZZintToPtr(ii);
                n=(ZZint)sizeof(struct ZZstrLST);

                if(ZZnTbType==9)nn=n;
                else if(ZZnTbType==8)nn=n-(ZZint)sizeof(char *);
                else if(ZZnTbType==7)nn=n-2*(ZZint)sizeof(char *);
                else ZZmsgDD(5,ZZnTbType,ZZpTbType);

                /* record if the big memory block is being used */
	        if(s.numPtr<0 && ZZmemSwitch && ZZmemStart)s.start=0;

                ZZwrite(ZZbindFile,(char *)(&s),nn,"writeBind:1");
                ZZwrite(ZZbindFile,ZZsList[i].strName,ii,"writeBind:2");
	        if(ZZsList[i].numPtr<0)break;
	    }
            if(ZZmemSwitch && ZZmemStart){
                bBlock.start=ZZmemStart;
                bBlock.end=ZZmemEnd;
                bBlock.pool=ZZmemPool;
                bBlock.offset=0;
                ZZwrite(ZZbindFile,(char *)(&bBlock),(ZZint)sizeof(struct bigBlock),"writeBind:3");
            }
            if(ZZpTbType)ZZwrPtrs(ZZbindFile);
            ZZwrInher(ZZbindFile); /* decides by itself whether to print */
        }
    }

    if(ZZbindFile){
        /* write the object itself */
        b.ptr=pp;
        b.strInd=typeInd;
        b.size=num*strSize;
        n=(ZZint)sizeof(struct ZZbinStore);
        ZZwrite(ZZbindFile,(char *)(&b),n,"writeBind:4");
        ZZwrite(ZZbindFile,pp,b.size,"writeBind:5");
        if(key)return;

        /* inherited or injected sub-objects do not have to be written out */

        /* for an array header, write out the whole array */
        if(typeInd== -4){
            pArr=(ZZarray*)pp;
            j=pArr->strType;
            ZZwriteBind(pArr->size,j,fileName,pArr->array,pArr->num,key);
        }
    
        /* write out properties and arrays for all members of the array */
        /* This must be done hierarchically for all base classes */
        else if(typeInd>=0){
            ZZsubPropArr(typeInd,pp,fileName,key,strSize,num);
        }
    }
    else ZZmsgSS(8,"ZZwriteBind",ZZbindName);
    return;
}
/* --------------------------------------------------------------------- */
// Write out properties and arrays for one given object & subclass.
// This function is recursive through all sub-types, but works only 
// with properties and arrays.
/* --------------------------------------------------------------------- */
void ZZsubPropArr(ZZint typeInd, char *pp,const char *fileName,ZZint key,
                         ZZint strSize,ZZint num){
    ZZint i,ii,j,k,m,mm,m1,m2,pSize,sz,it;
    char *t,**tt,*inj;
    struct ZZproperty **r;
    void ZZwriteProp(FILE *,struct ZZproperty *);
    void ZZwriteBind(ZZint,ZZint,const char *,char *,ZZint,ZZint);

    static ZZint level={0}; /* keeps level of the object, 1=parent */
    pSize=sizeof(char*);

    m=ZZsList[typeInd].propIndex;
    mm=ZZsList[typeInd].start;
    m1=ZZsList[typeInd].arrayIndex;
    m2=ZZsList[typeInd].numPtr;
    if(m2>0 && (m>=0 || m1>=0)){
	for(k=0,t=pp;k<num;k++,t+=strSize){
            /* selfID will be recovered from strList[] index */
            if(m>=0){
	        r=(struct ZZproperty **)(t+mm); 
	        ZZwriteProp(ZZbindFile,r[m]); /* dump all properties*/
             }
             if(m1>=0){
                 for(i=m1, tt=(char**)(t+mm+m1*pSize); i<m2; i++, tt++){
       ZZwriteBind((ZZint)sizeof(struct ZZarray),-4,fileName,*tt,1,key);
                 }
             }
         }
    }
    // now proceed through all inherited classes
    if(ZZiList){
        m1=ZZsList[typeInd].inhInd;
        m2=ZZsList[typeInd+1].inhInd;
        for(ii=m1;ii<m2;ii++){
            if(!strcmp("ZZvirtual",ZZiList[ii].name) 
                                            && level!=1)continue;
            j=ZZiList[ii].type; // type of the inserted object
            // inj will be the start of the injected object 
            inj=pp+ZZiList[ii].offset-ZZsList[j].start;
            it=ZZiList[ii].num; // is 0 for inherited objects 
            if(it<=0)it=1;

            sz=ZZsList[j].size;
            ZZsubPropArr(j,inj,fileName,key,sz,num);
        }
    }
}
/* --------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* hex debugging print of a string or buffer */
#ifdef ZZ_ANSI
void zzdebHex(char *ms,char *bf,ZZint n)
#else


void zzdebHex(ms,bf,n)
char *ms;    /* starting message */
char bf[];   /* buffer to be printed */
ZZint n;       /* number of characters to print */
#endif
{
    ZZint i,k;

    printf("%s ",ms);
    for(i=0;i<n;i++){
        k=(unsigned)(bf[i]);
        printf("%x ",k);
    }
    printf("\n");
    return;
}
/* ----------------------------------------------------------------------- */
/* debugging print of pointers associated with the given object */
#ifdef ZZ_ANSI
void zzdebPtrs(char *p,ZZint i,struct ZZstrLST *types)
#else


void zzdebPtrs(p,i,types)
char *p;  /* pointer to the object */
ZZint i;    /* index into the type table, -1 means no pointers */
struct ZZstrLST *types; /* type table */
#endif
{
    char **s;
    ZZint k,n;

    printf("object=%d,",p);
    if(i<0)printf(" no pointers\n");
    else {
        n=types[i].numPtr;
        for(k=0, s=(char**)((char*)p+types[i].start); k<n; k++, s++)
                                                            printf(" %d",*s);
        printf("\n");
    }
    return;
}
/* ----------------------------------------------------------------------- */
/* print type table and (optional) pointer names */
#ifdef ZZ_ANSI
void zzdebTypes(char *label,struct ZZstrLST *types,char **ptrs,PtrCntrl *off,
                                                     struct ZZtypeHier *iList)
#else


void zzdebTypes(label,types,ptrs,off,iList)
char *label; /* label for the printout */
struct ZZstrLST *types; /* type table */
char **ptrs; /* list of pointer names, if NULL, don't print them */
PtrCntrl *off; /* pointer offsets, if NULL, don't print them */
struct ZZtypeHier *iList; /* inheritance list */
#endif
{
    ZZint i,j;

    printf("%s\n",label);
    for(i=j=0;types[i].numPtr>=0;i++){
        printf("%d=%s start=%d numPtr=%d ptrInd=(%d,%d) size=%d\n",
             i,types[i].strName,types[i].start,types[i].numPtr,types[i].ptrInd,
                                         types[i+1].ptrInd,types[i].size);
        if(ptrs){
            for(j=types[i].ptrInd;j<types[i+1].ptrInd;j++){
                printf(" %s",ptrs[j]);
                if(off)printf("(%d,%d)",off[j].offset,off[j].oSize);
            }
            printf("\n");
        }
        if(iList && iList[0].type>=0){
            for(j=types[i].inhInd;j<types[i+1].inhInd;j++){
               printf(" (%d,%d,%d)",iList[j].type,iList[j].offset,iList[j].num);
            }
            printf("\n");
        }
    }
    return;
}
/* ----------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void zzdebBlk(char *label, void *obj, ZZint size, ZZint type)
#else
void zzdebBlk(label,obj,size,type)
char* label;
void *obj;
ZZint size;
ZZint type; /* given only as info to display, any value will work */
#endif
{
    ZZint sp,si,i;
    short *ip;
    char *p,**pp;

    sp=sizeof(char *);
    si=sizeof(short);

    if(sp==si)printf("%s obj=%u type=%d sz=%d:",label,obj,type,size);
    else printf("%s obj=%lu type=%d sz=%d:",label,obj,type,size);
    for(p=(char *)obj,i=0; i<size; p+=si, i+=si){
        printf("(%d,",i);
        if(sp!=si){
            pp=(char **)p;
            printf("%lu ",*pp);
        }
        ip=(short *)p;
        printf("%u)",(ZZint)(*ip));
    }
    printf("\n");
}
/* ----------------------------------------------------------------------- */
/* debug function for ZZstrList.vObj */
#ifdef ZZ_ANSI
void zzdebVObj(ZZint tp,struct ZZstrLST *sL)
#else

void zzdebVObj(tp,sL)
ZZint tp;
struct ZZstrLST *sL;
#endif
{
    ZZint i,sz; char *p1,*p2;
    sz=sL[tp].size; p1=sL[tp].vObj[0]; p2=sL[tp].vObj[1];
    printf("tp=%d sz=%d vObj[0]=",tp,sz);
    for(i=0;i<sz;i++)printf("%X,",p1[i]);
    printf("\n              vObj[1]=");
    for(i=0;i<sz;i++)printf("%X,",p2[i]);
    printf("\n");
}
