// Un-comment the following line in order to block the use of memory
// blasting under WinNT. This option was typically used in free-binary versions
// compiled and ZZintended for Win98, but is'n used any more.
// #define NOT_WIN_NT
// -----------------------------------------------------------------
/* Before this entire library was converted to Windows64, this section
 * (memory blasting) was based on the assumption that 
 * sizeof(char *) == sizeof(int). This assumption was tested,
 * and any improper use (for example with the large memory model
 * under DOS) was blocked, and an appropriate error message was issued.
 *
 * This version gets around this problem by using ZZint and ZZlong instead of int and long,
 * where these are defined in lib\types.h in such a way that 
 *  sizeof(char*) == sizeof(ZZint) == sizeof(ZZlong) regardless whether we work
 * under 32 or 64 bit Windows.
 */

#define zzLIB
#include <stdio.h>

#ifdef NOT_WIN_NT
#include <dsetup.h>
#endif /* NOT_WIN_NT */

#include "environ.h"
#include "types.h"
#include "heading.h"
#include "bind.h"
#include "msgs.h"
#include "offset.h"

typedef struct BlastInfo BlastInfo;
struct BlastInfo {
    ZZint numKeys; /* number of key entries */
    ZZptrIntType selfStart,selfEnd; /* limits of the selfID array */
    ZZptrIntType virtStart,virtEnd; /* limits of the virtFun pointers */
    char *memStart; /* three arrays describing pages */
    char *memEnd;
    char *memPool;
    ZZsize blastSize; /* array size */
    ZZsize lowInd; // starting low index for blastStart[] and blastMap[]
    ZZsize blastFirst; /* first used entry in the array */
    ZZsize blastNum;  /* reduced size, actually used */
    ZZsize ptrSize;
    ZZsize mapSize;
    ZZsize pageSize;
    ZZint mapShift; /* number of bits defining the page size */
    ZZsize maskUp;
    ZZsize maskDown;
};
typedef struct VirtTable VirtTable;
struct VirtTable {
    ZZsize oldAddr;
    ZZsize newAddr;
};

#ifdef ZZ_ANSI
void ZZdebugMBarrays(const char *label,int style, ZZsize newInd, ZZsize ind2);
    ZZint ZZpOffset(char *,char *);
    ZZvoidS ZZrecordPage(char *start);
    ZZsize ZZstartBit(void);
    ZZvoidS *ZZmassAlloc(size_t sz, ZZint ini);
    ZZvoidS ZZmassFree(void *);
    ZZvoidS *ZZnewObj(ZZint size);
    ZZint ZZwrite(FILE *fp,char *bf,ZZsize n,const char *errTxt);
    FILE *ZZopen(const char *file,const char *mode);
    ZZint ZZclose(FILE *f);
    void ZZgetVirtRange(ZZsize *low,ZZsize *hi);
    ZZvoidS runThrough(char**,char **,char **,BlastInfo *);
    ZZint ZZread(FILE *fp,char *bf,ZZsize n,const char *errTxt);
    static void debMap(void);
    static void debStart(void);
    static void debInfo(BlastInfo *bp);
    static void debClassDescriptions(ZZstrLST *lst,char *label);
    static ZZsize* setVirtTable(ZZsize *virtOffset,ZZsize *minAdrr);
    static void debVirtTable(VirtTable *vTab,int sz);

#else
void ZZdebugMBarrays();
    ZZint ZZpOffset();
    ZZvoidS  ZZrecordPage();
    ZZsize ZZstartBit();
    ZZvoidS *ZZmassAlloc();
    ZZvoidS ZZmassFree();
    ZZvoidS *ZZnewObj();
    ZZint ZZwrite();
    FILE *ZZopen();
    ZZint ZZclose();
    void ZZgetVirtRange();
    ZZvoidS runThrough();
    ZZint ZZread();
    static void debMap();
    static void debStart();
    static void debInfo();
    static void debClassDescriptions();
    static ZZsize* setVirtTable();
    static void debVirtTable();
#endif

static ZZsize blastSize={0}; /* size of blastStart and blastMap */
static ZZsize lowInd={0}; // starting low index for blastStart[] and blastMap[]
static char **blastStart; /* start of each memory block */
static char **blastMap;   /* start of each bitmap */
static ZZint ptrSize; /* size of a pointer in bits */
static ZZsize mapSize; /* size of one bitmap in bytes */
static ZZsize pageSize; /* size of one memory page in bytes */
static ZZint mapShift; /* number of bits to shift, to get the index */
static ZZsize maskUp; /* mask of the upper address */
static ZZsize maskDown; /* mask of the lower address */
static char* firstPage={NULL}; /* mask of the lower address */
static char* firstMap={NULL}; /* mask of the lower address */

static unsigned char bit8[8]={01,02,04,010,020,040,0100,0200};
static unsigned char bitR[8]={0376,0375,0373,0367,0357,0337,0277,0177};

extern char *ZZselfArr[]; /* declared in zzincl.h */
#define END_MARK "ZZendMark"

/* P is the given pointer, OFF is the resulting ZZint offset */
#define REGULAR_OFFSET(P,OFF) \
{ ZZsize I,X;\
    if(P){\
        X=(ZZptrIntType)(P);\
        I=(X & maskUp) >> mapShift;\
        if(I >= blastSize){\
	    ZZgrowArrays(I); /* may exit if impossible to grow */\
        }\
	if(lowInd > I)ZZgrowArrays(I);\
        if(blastStart[I-lowInd]==NULL || (ZZsize)(blastStart[I-lowInd])>X)(I)--;\
        (OFF)=ZZpOffset(newStart[I-lowInd],blastStart[I-lowInd]);\
    }\
    else (OFF)=0;\
}


/* test whether pointer P leads into this BLOCK, ANSW=1 for yes */
#define ADDRESS_CHECK(P,BLOCK,ANSW) \
{ ZZsigIntType I,X;\
    (ANSW)=0;\
    if(P){\
        X=(ZZsigIntType)(P);\
        I=(X & (BLOCK)->maskUp) >> (BLOCK)->mapShift;\
        if(I < (BLOCK)->blastSize){\
            if((BLOCK)->blastStart[I-lowInd]==NULL ||  \
                         (ZZsize)((BLOCK)->blastStart[I-lowInd])>X)(I)--;\
	    if((BLOCK)->blastStart[I-lowInd] &&  \
                         (ZZsize)((BLOCK)->blastStart[I-lowInd])<=X){\
               if(X-(ZZsize)((BLOCK)->blastStart[I-lowInd]) < \
                                            (BLOCK)->pageSize)ANSW=1;\
	    }\
        }\
    }\
}

typedef struct BlockRec BlockRec;
struct BlockRec { /* record of passive blocks */
    BlockRec *next; /* makes the list of passive blocks */
    char *name;
    ZZint used; /* 1=actually used, 0=leftover record */
    char **blastStart;
    char **blastMap;
    char *memStart;
    char *memEnd;
    char *memPool;
    ZZsize blastSize;
    ZZsize lowInd;
    ZZsize ptrSize;
    ZZsize mapSize;
    ZZsize pageSize;
    ZZsize mapShift;
    ZZsize maskUp;
    ZZsize maskDown;
    void *util; /* storage field for arbitrary user data */
};
static BlockRec *passive={0}; /* ZZinternal list of passive blocks */

/* -------------------------------------------------------------
 * For a given pointer, get the page to which it points.
   ------------------------------------------------------------- */
ZZsize ZZgetPage(void *ptr){
    ZZsize u,page,bs;

    u=(ZZsize)ptr;
    page=(maskUp & u) >> mapShift;

    if(lowInd > page || page > blastSize){
        ZZerrFLG=ZZerrFLG|020;
        ZZmsgSSS(6,"getPage",(char *)page,(char *)blastSize);
	debStart();
        exit(1);
    }
    else if(page==blastSize) page--;
    else if(page>lowInd){
	bs=(ZZsize)(blastStart[page-lowInd]);
	if(bs==0 || bs>u) page--;
    }
	
    return page;
}

/* -------------------------------------------------------------
 * Currently, arrays blastStart[] and blastMap[] serve indexes for
 * lowInd to (blastSize-1). Now it is requested to expand this range
 * to include newInd. 
 * First we test whether we could just change lowInd and re-assign the pages
 * rather than to re-allocate the arrays. 
 * Only if that fails, we will reallocate the arrays to fit the new range.
 *
 * When growing the array in some direction, we increase the overall range
 * of indexes by 50% in order to prevent calling this function often.
 * ---------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZgrowArrays(ZZsize newInd)


#else
void ZZgrowArrays(newInd)
    ZZsize newInd;
#endif
{
    ZZsize ind1; // new lowInd
    ZZsize ind2; // new highest index, or new (blastSize-1)
    ZZsize used1; // the lowest  k for which blastStart[k]!=NULL;
    ZZsize used2; // the highest k for which blastStart[k]!=NULL;

    ZZsize i,k,iMax,pSz,dif,numPgs,kk;
    char **newStart,**newMap;

    used1=used2=0;
    for(i=lowInd; i<blastSize; i++){
	if(blastStart[i-lowInd]){
	    if(!used1)used1=i;
	    used2=i;
	}
    }

    // check whether the problem can be solved by adjusting lowInd or blastSize
    if(newInd<lowInd){
	if(used2-newInd<=blastSize-1-lowInd){ // just change lowInd and blastSize
	    for(k=used2, i=blastSize-1; k>=used1; k--, i--){
		    blastStart[i-lowInd]=blastStart[k-lowInd];
		    blastMap[i-lowInd]=blastMap[k-lowInd];
            }
	    for( ; i>=lowInd; k--, i--){
	        blastStart[i-lowInd]=NULL;
	        blastMap[i-lowInd]=NULL;
	    }
	    lowInd=k+1;
	    blastSize=used2+1;
	    return;
	}
	// will pass through and reallocate the arrays
    } 
    else if(newInd>=blastSize){
	if(newInd-used1<=blastSize-1-lowInd){ // just change lowInd and blastSize
	    for(k=used1, i=lowInd; k<=used2; k++, i++){
	        if(k<=used2){
		    blastStart[i-lowInd]=blastStart[k-lowInd];
		    blastMap[i-lowInd]=blastMap[k-lowInd];
		}
	    }
	    for( ; i<blastSize; k++, i++){
	        blastStart[i-lowInd]=NULL;
	        blastMap[i-lowInd]=NULL;
	    }
	    lowInd=used1;
	    blastSize=k;
	    return;
	}
	// will pass through and reallocate the arrays
    }
    else return; // there is nothing to do, the page fits to what we have

    // We have to re-allocate and copy arrays blastStart[] and blastMap[]
    numPgs=blastSize-lowInd;
    // expand by 50% of the existing size
    dif=(numPgs+1)/2; // current size, +1 for rounding up

    if(newInd<lowInd){
	if(newInd<dif)ind1=0; 
	else ind1=newInd-dif;
	ind2=blastSize-1;
    }
    if(newInd>=blastSize){
	if(blastSize+dif<blastSize)ind2=newInd; // for safety, cannot happen
	else ind2=newInd+dif;
	ind1=lowInd;
    }

    // max possible index for the page of this size
    pSz=sizeof(char *); 
    ptrSize=8*pSz;
    iMax=1;
    for(i=0; i<ptrSize; i++){
        if(i<=mapShift) iMax=iMax*2;
    }
    if(ind2>=iMax){ ZZmsgSS(38,(char*)ind2,(char*)iMax); exit(3); }

    kk=ind2-ind1+1; // will be the new size of the arrays
    
    newStart=(char **)ZZmassAlloc(kk*pSz,1); // 1 will initialize to 0
    CHECK_ALLOC("newStart",kk*pSz,newStart); // may trigger exit()

    newMap=(char **)ZZmassAlloc(kk*pSz,1); // 1 will initialize to 0
    CHECK_ALLOC("newMap",kk*pSz,newMap);   // may trigger exit()

    // copy old parts into it
    for(i=lowInd; i<blastSize; i++){
        newStart[i-ind1]=blastStart[i-lowInd];
        newMap[i-ind1]=blastMap[i-lowInd];
    }


    ZZmassFree((void *)blastStart);
    ZZmassFree((void *)blastMap);
    blastStart=newStart;
    blastMap=newMap;
    lowInd=ind1;
    blastSize=ind2+1;
}

/* -------------------------------------------------------------- */
/* Cleanup the old pages and arrays if they are there, and reuse 
 * them if possible. If not possible to reuse them, create a new set.
 * The new arrays should be empty and able to support the range
 * of indexes <ind1,ind2>, including both ends.
 * If the old range is bigger, adjust ends differently for Windows and 
 * UNIX/Linux */
/* -------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZresetArrays(ZZsize ind1,ZZsize ind2)


#else
void ZZresetArrays(ind1,ind2)
    ZZsize ind1;
    ZZsize ind2;
#endif
{
    ZZsize i,k,arrSz,pSz;

    // free all pages used so far
    for(i=lowInd; i<blastSize; i++){
	k=i-lowInd;
	if(blastStart[k]){
	    ZZmassFree((void *)(blastStart[k]));
            blastStart[k]=NULL;
        }
	if(blastMap[k]){
	    ZZmassFree((void *)(blastMap[k]));
            blastMap[k]=NULL;
        }
    }
    
    // If the range did not increase, just reset lowInd and blastSize
    if(ind2-ind1 <= blastSize-1-lowInd){
	arrSz=blastSize-lowInd; // existing array size
	// in case of Unix, the addresses of future pages will likely be lower
#ifdef UNIX
        if(blastSize>=arrSz){
	    blastSize=ind2+1;
	    lowInd=blastSize-arrSz;
        }
        else {
            lowInd=0;
            blastSize=arrSz;
        }
	// in other cases, typically under Windows, they will likely be higher
#else
	lowInd=ind1;
	blastSize=lowInd+arrSz;
#endif
        return;
    }
   
    // re-allocate both arrays exactly for the given range
    pSz=sizeof(char *); 
    arrSz=ind2-ind1+1;
    blastStart=(char **)ZZmassAlloc(arrSz*pSz,1); // 1 will initialize to 0
    CHECK_ALLOC("blastStart",arrSz*pSz,blastStart); // may trigger exit()

    blastMap=(char **)ZZmassAlloc(arrSz*pSz,1); // 1 will initialize to 0
    CHECK_ALLOC("blastMap",arrSz*pSz,blastMap);   // may trigger exit()

    lowInd=ind1;
    blastSize=ind2+1;
}


/* ------------------------------------------------------------- */
/* Important: 
 * Pointers inside the new objects must be recorded in the bitmap.
 * This is done in the following way:
 * Macros such as ZZ_PLAIN_ALLOC(), ZZ_INITIAL(), ZZ_OBJECT_ALLOC(),
 * ZZ_PLAIN_FREE() or ZZ_OBJECT_FREE() call the following
 * functions: ZZallo(), ZZdeal(), or ZZini(), where 
 * ZZallo() calls always ZZini().
 * ZZini() or ZZdeal(), in case that ZZmemSwitch==2, call
 *   ZZbindPtrs(obj,type,size,1,val); for val=1 or 0,
 * and that marks the  pointers in the bitmap.
 *
 */
/* ------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZblkActive(char *name,ZZint mode)

#else
void ZZblkActive(name,mode)
char *name; /* name of the block, or an address */
ZZint mode; /* 1=make the block active, 0=make it passive,
	     2=make it active, but use 'name' as an address, not as a name */
#endif
{
    BlockRec *bp;
    char *np;
    ZZptrIntType address;
    ZZint answer;
    ZZsize kk;

    if(mode>0){ /* make the block active */
        // if(ZZmemEnd || blastSize){ZZmsgS(41,name); return;}

        if(mode==1){
            for(bp=passive;bp;bp=bp->next){ /* search for the given name */
                if(!strcmp(name,bp->name) && bp->used)break;
            }
            if(!bp){ZZmsgS(42,name); return;}
	}
        else if(mode==2){
	    address=(ZZptrIntType)name;
            for(bp=passive;bp;bp=bp->next){ /* search for the given name */
                ADDRESS_CHECK(address,bp,answer);
	        if(answer)break;
            }
            if(!bp){ZZmsgS(45,name); return;}
	}
	else {ZZmsgD(30,mode); return;}

        /* copy the passive record ZZinto the active memory */
        ZZmemStart=bp->memStart;
        ZZmemEnd=bp->memEnd;
        ZZmemPool=bp->memPool;
        blastSize=bp->blastSize;
        lowInd=bp->lowInd;
        blastStart=bp->blastStart;
        blastMap=bp->blastMap;
        ptrSize=bp->ptrSize;
        mapSize=bp->mapSize;
        pageSize=bp->pageSize;
        mapShift=bp->mapShift;
        maskUp=bp->maskUp;
        maskDown=bp->maskDown;

        bp->used=0; /* mark the passive record as unused */
    }
    else {  /* make the current block passive */
        for(bp=passive;bp;bp=bp->next){ /* search for the given name */
            if(!strcmp(name,bp->name) && bp->used)break;
        }
        if(bp && bp->used){ZZmsgS(43,name); return;};
        if(!bp){ /* no record with this name, create a new record */

	    kk=sizeof(struct BlockRec);
            bp=(BlockRec *)ZZmassAlloc(kk,0);
            CHECK_ALLOC("BlockRec",kk,bp); // may trigger return

	    kk=strlen(name)+1;
            np=(char *)ZZmassAlloc(kk,0);
            CHECK_ALLOC("ZZmemStart",kk,np); // may trigger return

            if(!bp || !np){ZZmsgS(1,"passive block record"); return;}
            strcpy(np,name);
            bp->name=np;
            bp->next=passive; /* add bp to the linked list */
            passive=bp;
        }

        /* copy active parameters into the passive list */
        bp->memStart=ZZmemStart;
        bp->memEnd=ZZmemEnd;
        bp->memPool=ZZmemPool;
        bp->blastSize=blastSize;
        bp->lowInd=lowInd;
        bp->blastStart=blastStart;
        bp->blastMap=blastMap;
        bp->ptrSize=ptrSize;
        bp->mapSize=mapSize;
        bp->pageSize=pageSize;
        bp->mapShift=mapShift;
        bp->maskUp=maskUp;
        bp->maskDown=maskDown;

        bp->used=1; /* make the passive record used */
        ZZmemEnd=NULL; /* set record for no active block */
        blastSize=0;
	lowInd=0;
    }
}
/* ------------------------------------------------------------- */
/* This function controls special 'hooks' that the user can assign
 * to each block of memory in memory blasting. For example, when
 * each block represents one design view, the utility hook may be
 * the key entry for this view.
 * The function allows both setting/search for this special hook.
 * Regardless of the mode, the function returns the name of the
 * identified block.
 * Important: The block must be on the ZZinternal list, it means
 * it had to be made passive at least once before using this function.
 */
#ifdef ZZ_ANSI
char *ZZblkUtil(char *name,void **hook,ZZint mode)

#else
char *ZZblkUtil(name,hook,mode)
char *name; /* name of the block, or an address */
void **hook; /* utility hook - user given */
ZZint mode; /* 0=assign given hook to a block given by the name,
	     1=assign given hook to a block given by its ZZinternal address,
	     2=retrieve hook for a block given by its name,
	     3=retrieve hook for a block identified by an ZZinternal address. */
#endif
{
    BlockRec *bp;
    ZZptrIntType address;
    ZZint answer;

    if(mode==0 || mode==2){
        for(bp=passive;bp;bp=bp->next){ /* search for the given name */
            if(!strcmp(name,bp->name) && bp->used)break;
        }
        if(!bp){ZZmsgS(42,name); return(NULL);}
    }
    else {  /* block identified by an address */
	address=(ZZptrIntType)name;
        for(bp=passive;bp;bp=bp->next){ /* search for the given name */
            ADDRESS_CHECK(address,bp,answer);
	    if(answer)break;
        }
        if(!bp){ZZmsgS(45,name); return(NULL);}
    }
    if(mode<=1)bp->util=(*hook);
    else       *hook=bp->util;
    return(bp->name);
}
/* ------------------------------------------------------------- */
/* "START BITMAP" = allocation method for multiple memory blocks and bitmap */
/* The initial number of pages (blastSize) is estimated from allocating one
 * firstPage and firstMap, then adding in both directions 1.5-times 
 * the specified space.
 * If later the resulting values of lowInd and blastSize do not suffice,
 * they can be adjusted and the arrays blastStart[] and blastMap[] can be
 * approprietly reallocated.
 *
 * pageSize must be bigger than the largest object in your program,
 * and for practical purposes we set its lower limit as 2**8=256B.
 *
 * The expected memory size is passed from BLOCK_ALLOC through ZZmemPool
 */
#ifdef ZZ_ANSI
ZZsize ZZstartBit(void)

#else
ZZsize ZZstartBit()
#endif
{
    ZZsize i,ii,kk,n,ind1,aSz;
    char *ca;

    /* temporarily, blasting limited to 'normal' environments like UNIX */
    i=sizeof(char *);
    ii=sizeof(ZZint);
    if(i!=ii){ZZmsg(61); return(0);}
    if(mapShift<8){
        ZZmsg(72);
        mapShift=8;
    }

    ptrSize=8*sizeof(char *);
    blastSize=pageSize=1; /* will be the limit for the number of pages */
    maskUp=maskDown=0;
    for(n=1, i=0; i<ptrSize; i++, n=n*2){
        if(i<mapShift){
            pageSize=pageSize*2;
            maskDown=maskDown|n;
        }
        else {
            blastSize=blastSize*2;
            maskUp=maskUp|n;
        }
    }
    mapSize=pageSize/(sizeof(char *)*8); /* bit for each pointer */
    blastSize++; // add one for safety

    n=(ZZsize)(ZZmemPool); /* temporary stored the max.memory size */
    if(n>0 && (n/pageSize)<blastSize){
        aSz=n/pageSize;
	kk=aSz*0.1; //safety for blastMap from the same pool as blastStart
	if(kk==0)kk=1;
	aSz=aSz+kk;
    }
    else aSz=blastSize;

    // ------------------------------------------------------------
    kk=aSz*sizeof(char *); 

    blastStart=(char **)ZZmassAlloc(kk,1);
    CHECK_ALLOC("blastStart[]",kk,blastStart); // may trigger exit

    blastMap  =(char **)ZZmassAlloc(kk,1);
    CHECK_ALLOC("blastMap[]",kk,blastMap); // may trigger exit
    // ------------------------------------------------------------
    firstPage=(char*)ZZmassAlloc(pageSize,0); /* current heap address */
    CHECK_ALLOC("firstPage",pageSize,firstPage);


    firstMap=(char*)ZZmassAlloc(mapSize,1); /* current heap address */
    CHECK_ALLOC("firstMap allocated",mapSize,firstMap); //may trigger return
    // WARNING: The map is significantly smaller than the page,
    //      and the OS often allocates them from different pools of memory.
    //      Their relative position is of no use here! 
    // ------------------------------------------------------------
    
    ind1=(ZZsize)firstPage/pageSize; // index of the first page

#ifdef UNIX
    // UNIX style allocation: addresses of large blocks decrease
    if(ind1<=aSz-1){ lowInd=0; blastSize=aSz; }
    else           { lowInd=ind1-aSz+1; blastSize=lowInd+aSz; }
#else
// DOS style allocation: addresses of large blocks increase
    lowInd=ind1;
    blastSize=ind1+aSz;
#endif

    ZZmemPool=firstPage;
    ZZmemEnd=firstPage+pageSize;
   

    n=(ZZsize)firstPage/pageSize;
    blastStart[n-lowInd]=firstPage;
    blastMap[n-lowInd]=firstMap;

    return(pageSize);
}
/* --------------------------------------------------------------------- */
/* when new page is allocated, record it in the bitmap scheme */
#ifdef ZZ_ANSI
ZZvoidS ZZrecordPage(char *start)

#else
ZZvoidS ZZrecordPage(start)
char *start; /* start of the new page */
#endif
{
    ZZsize n;

    n=((ZZsize)start & maskUp) >> mapShift;
    if(n>=blastSize){
	ZZgrowArrays(n); // may trigger exit
    }
    else if(n<lowInd){
	ZZgrowArrays(n); // may trigger exit
    }
    if(blastStart[n-lowInd]){
	ZZmsgSSS(7,blastStart[n-lowInd],start,(char*)n);
	exit(2);
    }
    blastStart[n-lowInd]=start;
    blastMap[n-lowInd]=(char *)NULL;

    if(blastMap[n-lowInd]==NULL){
	blastMap[n-lowInd]=(char *)ZZmassAlloc(mapSize,1);
        CHECK_ALLOC("blastMap[]",mapSize,blastMap[n-lowInd]); // may trigger return
    }
    
}
/* --------------------------------------------------------------------- */
/* For a given pointer, mark the corresponding bit in the bitmap.
 * If the bitmap for the particular block does not exist yet,
 * allocate and initialize it.
 */
#ifdef ZZ_ANSI
void ZZmarkPtr(char **ptr,ZZint val)

#else
void ZZmarkPtr(ptr,val)
char **ptr; /* pointer to mark */
ZZint val; /* value to mark, 0 or 1 */
#endif
{
    ZZsize k,j,u,page;
    char *p;

    u=(ZZsize)ptr;
    page=ZZgetPage(ptr);
    if(page<lowInd || page>=blastSize){
	ZZmsgSD(51,(char*)ptr,1); // case 1
	return; // not in the allocated area, should this be an error ?
    }
    if ((ZZsize)(blastStart[page-lowInd]) + pageSize <= u){
	ZZmsgSD(51,(char*)ptr,2); // case 2
	return; // not in the allocated area, should this be an error ?
    }

    u=(u-(ZZsize)(blastStart[page-lowInd]))/sizeof(char *);
    j=u;
    k=j/8;
    p= &(blastMap[page-lowInd])[k];
    j=j-k*8;
    if(val)(*p)=(*p)|bit8[j];
    else   (*p)=(*p)&bitR[j];
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
ZZvoidS *ZZnewBit(ZZsize size) 

#else
ZZvoidS *ZZnewBit(size) 
unsigned ZZsize size;
#endif
{
    char *ptr;
    ZZsize n,k;
    int kk;

    k=sizeof(char *);
    size=k*((size+k-1)/k); /* rounds up size to multiple of sizeof(char *) */

    /* ZZmemEnd=0 happens only when setting up a new bitmap data -
     see macro ZZ_BLOCK_ALLOC(). In this case, ZZmemStart is used
     * temporarily just to pass the number of bits from ZZ_BLOCK_ALLOC()
     * to this function, which sets up ZZinternal memory blasting data */
    if(!ZZmemEnd){
        mapShift=ZZptrToSize(ZZmemStart); /* temporary storage */
	ZZmemStart=NULL; // keeping the temporary value here causes problems
        pageSize=ZZstartBit();
    }

    if(size > pageSize){
        ZZerrFLG=ZZerrFLG|01;
        ZZmsgSS(37,(char*)size,(char*)pageSize);
        exit(1);
    }
    n=ZZptrToSize(ZZmemPool)+size;
    if(n>(ZZsize)ZZmemEnd){


        ZZmemStart=ZZmemPool=(char *)ZZmassAlloc(pageSize,1);
        CHECK_ALLOC("new page",pageSize,ZZmemStart); // may trigger exit(1)

        ZZmemEnd=ZZmemStart+pageSize;
        ZZrecordPage(ZZmemStart);
    }
    ptr=ZZmemPool;

    ZZmemPool=ZZmemPool+size;
    return((ZZvoidS *)ptr);
}

/* ---------------------------------------------------------------------
 * Read the descriptions of old classes, store it in ZZoList[],
 * exit(2) with an error message, if there is a problem.
 * --------------------------------------------------------------------- */
void ZZreadClassDescriptions (FILE *fp){
    int i,objSz,nameSz,numC;

    // read number of classes
    ZZread(fp,(char*)(&numC), sizeof(int),"numC");
    // allocate ZZoList[] with the last entry as the endmark only
    ZZoList=(ZZstrLST*)ZZmassAlloc((numC+1)*sizeof(ZZstrLST),2);
    if(ZZoList<=0){ZZmsg(75); exit(1);}

    // read array ZZoList[] including the name and master objects
    for(i=0; ; i++){
	// read class info
        ZZread(fp,(char*)(&(ZZoList[i])), sizeof(ZZstrLST),"one ZZstrLST");
	if(ZZoList[i].numPtr<0)break;
	
	// read the size of the name 
        ZZread(fp,(char*)(&nameSz), sizeof(int),"nameSz");
	objSz=ZZoList[i].size;
	// allocate space for the name and for the master objects
        ZZoList[i].strName=(char*)ZZmassAlloc(nameSz+1,2);
        ZZoList[i].vObj[0]=(char*)ZZmassAlloc(objSz,2);
        ZZoList[i].vObj[1]=(char*)ZZmassAlloc(objSz,2);

	// read name and the two master objects
        ZZread(fp,ZZoList[i].strName, nameSz+1,"class name");
        ZZread(fp,ZZoList[i].vObj[0],objSz,"vPrt[0]");
        ZZread(fp,ZZoList[i].vObj[1],objSz,"vPrt[1]");
    }
}

/* --------------------------------------------------------------------- 
 * Write ZZsList[] including the class names and vObj[1) and vObj[2],
 * exit(2) with an error message, if there is a problem.
 * --------------------------------------------------------------------- */
void ZZwriteClassDescriptions (FILE *fp){
    int i,objSz,nameSz,numC;

    // write number of classes
    for(i=0; ZZsList[i].numPtr>=0; i++){ continue; }
    numC=i;
    ZZwrite(fp,(char*)(&numC), sizeof(int),"numC");

    // write array ZZsList[] including the name and master objects
    for(i=0; ; i++){
	// write class info
        ZZwrite(fp,(char*)(&(ZZsList[i])), sizeof(ZZstrLST),"one ZZstrLST");
	if(ZZsList[i].numPtr<0)break;
	
	objSz=ZZsList[i].size;
	nameSz=strlen(ZZsList[i].strName);
	// write the size of the name
        ZZwrite(fp,(char*)(&nameSz), sizeof(int),"nameSz");

	// write name and the two master objects
        ZZwrite(fp,ZZsList[i].strName,nameSz+1,"clas Name");
        ZZwrite(fp,ZZsList[i].vObj[0],objSz,"vPtr[0]");
        ZZwrite(fp,ZZsList[i].vObj[1],objSz,"vPtr[1]");
    }
}



/* --------------------------------------------------------------------- */
/* Blast all the used memory to disk */
/* Algorithm:
 *  - Fill in blast info
 *  - write blast info
 *  - write key entries
 *  - write blastStart[]
 *  - Repeat for all used memory blocks:
 *     write memory block
 *     write bitmap
 * The end of file does not have to be marked as in other cases,
 * because we know how many entries there are.
 *
 * For the current page, write only the actual size of data.
 */
#ifdef ZZ_ANSI
void ZZblastSave(const char *fileName,ZZint n,char **obj)

#else
void ZZblastSave(fileName,n,obj)
char *fileName;
ZZint n; /* number of key entries */
char *obj[]; /* array of given n key entries */
#endif
{
    BlastInfo bi;
    ZZint i,bNum,first;
    ZZsize pgSize,mpSize;
    FILE *fp;
    unsigned ZZint kk;
#ifdef NOT_WIN_NT
    if((020000000000 & GetVersion())==0){
        printf("sorry - this free binary version does not work under WinNT\n");
        return;
    }
#endif /* NOT_WIN_NT */

    bi.numKeys=n;
    bi.pageSize=pageSize;
    bi.mapSize=mapSize;
    bi.blastSize=blastSize;
    bi.lowInd=lowInd;
    for(i=lowInd, bNum=1, first= -1; i<blastSize; i++){
        if(blastStart[i-lowInd]){
	    bNum=i+1;
            if(first<0)first=i;
	}
    }
    if(first<0){printf("internal error, first<0\n"); exit(1);}
    bi.blastNum=bNum;
    bi.blastFirst=first;
    bi.maskUp=maskUp; 
    bi.maskDown=maskDown;
    bi.mapShift=mapShift;
    bi.ptrSize=ptrSize;
    bi.memStart=ZZmemStart;
    bi.memPool=ZZmemPool;
    bi.memEnd=ZZmemEnd;
    bi.selfStart=(ZZptrIntType)ZZselfArr;

    for(i=0; strcmp(ZZselfArr[i],END_MARK);i++)continue;
    bi.selfEnd= (ZZptrIntType)(&(ZZselfArr[i]));
    ZZgetVirtRange((ZZsize*)&(bi.virtStart),(ZZsize*)&(bi.virtEnd));

    if(ZZbindCntrl)fp=(FILE*)fileName;
    else fp=ZZopen(fileName,"w");
    if(!fp)return;

    /* write the blast info */
    ZZwrite(fp,(char *)(&bi),(ZZint)sizeof(struct BlastInfo),"BlastInfo");

    /* write the description of all classes */
    ZZwriteClassDescriptions(fp); // may exit 
    /* write key entries */
    ZZwrite(fp,(char *)obj,n*(ZZint)sizeof(char *),"key entries");

    /* write only the used part of blastStart[] */
    ZZwrite(fp,(char *)(&(blastStart[first-lowInd])),(bNum-first)*sizeof(char *),"blastStart[]");


    for(i=first;i<bNum;i++){
        if(blastStart[i-lowInd]){
            /* blast whole page, except for current page */
            if(blastStart[i-lowInd]==ZZmemStart){
                 pgSize=(ZZptrIntType)ZZmemPool-(ZZptrIntType)ZZmemStart;
                 mpSize=(pgSize-1)/32 + 1;
	    }
            else {
	        pgSize=pageSize; 
		mpSize=mapSize;
	    }
            if(pgSize<4)pgSize=4;
            if(mpSize<4)mpSize=4;

            ZZwrite(fp,blastStart[i-lowInd],pgSize,"blastStart[i]"); /* page */
            ZZwrite(fp,blastMap[i-lowInd],mpSize,"blastMap[i]"); /* bitmap */
        }
    }
    ZZclose(fp);
}
/* --------------------------------------------------------------------- */
/* Get the range of all virtual function pointers, 
 * vf pointers are marked by 'F' in their first byte in vObj[1]
 * This function works correctly for any compiler
 */
#ifdef ZZ_ANSI
void ZZgetVirtRange(ZZsize *start, ZZsize *end)

#else
void ZZgetVirtRange(start,end)
ZZsize *start; /* returned lower range */
ZZsize *end; /* returned upper range */
#endif
{
    ZZsize i,k,sz,n,*ip;
    char *v0,*v1;
    
    sz=sizeof(ZZsize);
    /* run through all classes to get all virtual pointers */
    (*start)=0; (*end)=0;
    for(i=0; ZZsList[i].numPtr>=0; i++){
        v0=ZZsList[i].vObj[0];
        v1=ZZsList[i].vObj[1];
        if(v0){
            n=ZZsList[i].size;
            for(k=0;k<n;k+=sz){
                if(v1[k]=='F'){ /* vf pointer detected */
                    ip=(ZZsize *)(&(v0[k]));
                    if(!(*start) || (*start)>(*ip))*start=(*ip);
                    if((*end)<(*ip))*end=(*ip);
                }
            }
        }
    }
}
/* --------------------------------------------------------------------- */
/* Blast content of the disk to the memory */
/* Algorithm:
 * Read data in the same sequence as in ZZblastSave().
 * Convert all pointers in key entries, and 'start' in blastArray
 * Then convert all the pointers marked in the bitmaps.
 * This has 3 parts:
 * (a) Normal pointers with value from within the memory block will only
 *     be shifted. Note, that these pointers include virtual class
 *     pointers in C++.
 * (b) SelfID pointers (fall within a special given range)
 *     must be converted. This is only a different shift.
 * (c) Virtual function pointers (fall within a special given range)
 *     must be converted. We assume that the compiler generates
 *     virtFunPointers always with the same relative offset.
 * IMPORTANT: After resetting all pointers, blastArray must be
 * reshuffled to reflect new locations. This applies to both
 * the 'start' and 'bitmap' pointers. The start pointer determines
 * the location.
 *
 * For the current page, read only the actual size of data.
 */
#ifdef ZZ_ANSI
void ZZblastOpen(const char *fileName,ZZint n,char **obj)

#else
void ZZblastOpen(fileName,n,obj)
char *fileName;
ZZint n; /* number of key entries */
char *obj[]; /* array of given n key entries */
#endif
{
    FILE *fp;
    BlastInfo bi;
    char **newStart,**newMap;
    ZZint i,offset,bNum,first;
    ZZsize kk,newLow,newHigh,u,pgSize,mpSize,oldLow,oldSize,mx; 


    if(ZZbindCntrl)fp=(FILE*)fileName;
    else fp=ZZopen(fileName,"r");
    if(!fp)return;

    /* read the blast info */
    ZZread(fp,(char *)(&bi),(ZZint)sizeof(struct BlastInfo),"BlastInfo");

    pageSize=bi.pageSize;
    mapSize=bi.mapSize;
    blastSize=bi.blastSize;
    lowInd=bi.lowInd;
    bNum=bi.blastNum;
    first=bi.blastFirst;
    maskUp=bi.maskUp; 
    maskDown=bi.maskDown;

    mapShift=bi.mapShift;
    ptrSize=bi.ptrSize;
    ZZmemStart=bi.memStart;
    ZZmemPool=bi.memPool;
    ZZmemEnd=bi.memEnd;


    /* read the description of all the classes */
    ZZreadClassDescriptions(fp); // may exit 
    
    if(n!=bi.numKeys)ZZmsg(59);
    /* read key entries */
    ZZread(fp,(char *)obj,n*(ZZint)sizeof(char *),"key entries");

    /* read newStart[] and prepare newMap[], and blastMap[] */
    kk=(blastSize-lowInd)*sizeof(char *);
    blastStart=(char **)ZZmassAlloc(kk,2); // initial with 0
    CHECK_ALLOC("blastStart",kk,blastStart); // may trigger return

    blastMap=(char **)ZZmassAlloc(kk,2);
    CHECK_ALLOC("blastMap",kk,blastMap); // may trigger return

    newStart=(char **)ZZmassAlloc(kk,2);
    CHECK_ALLOC("newStart",kk,newStart); // may trigger return

    newMap=(char **)ZZmassAlloc(kk,2);
    CHECK_ALLOC("newStart",kk,newStart); // may trigger return

    // read only the used part of the array
    ZZread(fp,(char *)(&(blastStart[first-lowInd])),(bNum-first)*sizeof(char *),
		    "ZZblastOpen():blastStart[]");

    for(i=first;i<bNum;i++){
        if(blastStart[i-lowInd]){
            newStart[i-lowInd]=(char *)ZZmassAlloc(pageSize,2);
            CHECK_ALLOC("newStart[i]",pageSize,newStart[i-lowInd]); // may trigger exit()
	
            newMap[i-lowInd]=(char *)ZZmassAlloc(mapSize,2);
            CHECK_ALLOC("newMap[i]",mapSize,newMap[i-lowInd]); // may trigger exit()

            if(!newStart[i-lowInd] || !newMap[i-lowInd]){
		ZZmsg(73);
		exit(1);
	    }

            /* read full page, except for the current page */
            if(blastStart[i-lowInd]==ZZmemStart){ // last, incomplete page
                 pgSize=(ZZsize)ZZmemPool-(ZZsize)ZZmemStart;
                 mpSize=(pgSize-1)/32 + 1;
            }
            else {
		pgSize=pageSize;
		mpSize=mapSize;
	    }
            if(mpSize<4)mpSize=4;
            if(pgSize<=0)pgSize=4;

            // read page and map
            ZZread(fp,newStart[i-lowInd],pgSize,"newStart[i]"); /* read the page */
            ZZread(fp,newMap[i-lowInd],mpSize,"newMap[i]"); /* read the bitmap */
        }
    }
    ZZclose(fp);


    /* run through all objects on the pages and convert them */
    // do this before converting ZZmemPool, because we need the old ZZmemPool
    runThrough(blastStart,newStart,newMap,&bi);

    /* convert key entries */
    for(i=0;i<bi.numKeys;i++){
        REGULAR_OFFSET(obj[i],offset);
        obj[i]=obj[i]+offset;
    }

    /* convert ZZmemStart, ZZmemPool, ZZmemEnd */
    REGULAR_OFFSET(ZZmemStart,offset); ZZmemStart=ZZmemStart+offset;
    REGULAR_OFFSET(ZZmemPool,offset); ZZmemPool=ZZmemPool+offset;
    REGULAR_OFFSET(ZZmemEnd,offset); ZZmemEnd=ZZmemEnd+offset;


    /* move all blocks into new positions */
    for(i=lowInd;i<blastSize;i++)blastStart[i-lowInd]=NULL;

    // figure the range of idexes after the pages has been re-allocated
    mx=(unsigned)(-1); // largest possible number
    newLow=newHigh=mx; // this is a very large positive number
    for(i=lowInd;i<blastSize;i++){
        if(newStart[i-lowInd]){
            u=((ZZsize)(newStart[i-lowInd]) & maskUp) >> mapShift;
	    if(newLow==mx){ newLow=u; newHigh=u; }
	    else {
                if(u>=newHigh) newHigh=u;
	        if(u<newLow) newLow=u;
            }
        }
    }
    oldLow=lowInd;
    oldSize=blastSize;
    if(newLow<lowInd || newHigh>=blastSize){ ZZresetArrays(newLow,newHigh); }


    // update the arrays
    for(i=oldLow;i<oldSize;i++){
        if(newStart[i-oldLow]){
            u=((ZZsize)(newStart[i-oldLow]) & maskUp) >> mapShift;
            blastStart[u-lowInd]=newStart[i-oldLow];
            blastMap[u-lowInd]=newMap[i-oldLow];
        }
    }
    ZZmassFree((void *)newStart);
    ZZmassFree((void *)newMap);
}
/* -------------------------------------------------------------- */
/* Run through all pointers and convert them,
 * using temporary arrays newStart[] and newMap[].
 * Arrays blastStart[] and blastMap[] are global.
 * On the entry, blastStart[] contains the old starts,
 * newStart[] contains the new starts, and newMap[] contains the maps.
 * 
 * Processing may change blastStart[] and blastMap[], but neither
 * newStart[] nor newMap[].
 *
 * PERFORMANCE OPTIMIZATION:
 * When there is only one active page, all regular pointers move
 * by the same offset. 
 */
#ifdef ZZ_ANSI
ZZvoidS runThrough(char **blastStart,char **newStart,char **newMap,BlastInfo *bi)

#else
ZZvoidS runThrough(newStart,newMap,bi)
char *newStart[]; /* new place where the pages allocated */
char *newMap[];  /* new place where the maps are allocated */
BlastInfo *bi; /* blast info as read in from the file */
#endif
{
    ZZsize i,j,m,selfOffset,offset,cap,pgSz,pool,uniOff;
    ZZsize s1,s2,v1,v2,pv,k;
    ZZint pIncr,sIncr,szCp,active; 
    char **pp,*s,**p2;
#ifdef ZZcplus
    ZZsize virtOffset,minAddr;
    ZZsize *sTab; // table of old and new virtual addresses
    ZZint  indexing;   // =0 same offset for all v.f.pointers, =1 indexing in  
#endif

    /* find all offsets */
    s1=bi->selfStart;
    s2=bi->selfEnd;
    v1=bi->virtStart;
    v2=bi->virtEnd;
#ifdef TURBOC
    v1=v1; v2=v2; /* Borland 3.0 issues unjustified warning otherwise */
#endif
    selfOffset=ZZpOffset((char *)ZZselfArr,(char *)(bi->selfStart));
#ifdef ZZcplus
    sTab=setVirtTable(&virtOffset,&minAddr);
#endif

    // decide whether there is one active page or more
    uniOff=0; // initial uniform offset, will be used only when one active page
    for(active=0, i=lowInd; i<blastSize; i++){
	    if(newStart[i-lowInd]==NULL)continue;
	    if(active==0)j=i-lowInd;
	    active++;
	    if(active>1)break;
    }
    if(active==1){ // there is only one active page, and has index j
	uniOff=(ZZsize)(newStart[j])-(ZZsize)(blastStart[j]);
    }   // valid even for negative offset, these are all unsigned   

    /* run through all pointers and convert them */
    szCp=sizeof(char*);
    sIncr=sizeof(char*); pIncr=szCp*szCp*8;
    pgSz=bi->pageSize;
    pool=(ZZsize)(bi->memPool);

    for(i=lowInd;i<blastSize;i++){
        pp=(char **)(newStart[i-lowInd]);
        s=(char *)(newMap[i-lowInd]);
        if(pp && s){
            // Is this is the last page to which pool falls?
	    if((ZZsize)(bi->memStart) == (ZZsize)(blastStart[i-lowInd])){
                cap=(ZZsize)(bi->memPool)-(ZZsize)(blastStart[i-lowInd]);
	    }
	    else cap=bi->pageSize;
	    cap=cap+(ZZsize)pp;

            for(k=0 ; k<mapSize; k++, s++){
		if(k%szCp == 0 && k+szCp<=mapSize){
		    p2=(char **)s;
		    if(*p2==0){
			pp=pp+szCp*8;
			s=s+szCp-1; // main loop will add 1
			k=k+szCp-1; // main loop will add 1
			if((ZZsize)pp>cap)break;
		       	continue;
		    }
		}

                j=(*s);
                if(j==0)pp+=8;
                else {

                    for(m=0;m<8;m++,pp++){
                        if(j&1){ /* update pointer */
                            pv=(ZZsize)(*pp);
                            if(pv>=s1 && pv<=s2)offset=selfOffset;
#ifdef ZZcplus
                            else if(pv>=v1 && pv<=v2){
                                    if(sTab==NULL)offset=virtOffset;
	                            else  offset=sTab[(pv-minAddr)/virtOffset];
			    }
#endif
                            else { 
			        if(active==1){offset=uniOff;}
			        else {REGULAR_OFFSET(pv,offset);}
			    }

                            (*pp)=(*pp)+offset;

                        }
                        j=j >> 1;
		        if((ZZsize)pp>cap)break;
	            }
                }
            }
        }
    }
}
/* --------------------------------------------------------------- */
/* remove all the data plus structure blasting tables/bitmaps from memory */
/* proceed backward in the order as created, in order to help
 * to recover the allocation space */
#ifdef ZZ_ANSI
ZZvoidS ZZblastClear(void)

#else
ZZvoidS ZZblastClear()
#endif
{
    ZZint i;

    if(!blastStart || !blastMap)return;
    for(i=lowInd; i<blastSize; i++){
        if(blastStart[i-lowInd])ZZmassFree((void *)(blastStart[i-lowInd]));
        if(blastMap[i-lowInd])ZZmassFree((void *)(blastMap[i-lowInd]));
    }
    ZZmassFree((void *)(blastMap));
    ZZmassFree((void *)(blastStart));
    blastStart=(char **)NULL;
    blastMap=(char **)NULL;
    blastSize=0;
    lowInd=0;
    ZZmemEnd=NULL; // Important: Marks no arrays blastStart[] and blastMap[]
}

static int cmpVirt(const void *v1,const void *v2){
    VirtTable *vt1,*vt2;
    vt1=(VirtTable*)v1;
    vt2=(VirtTable*)v2;
    if(vt1->oldAddr < vt2->oldAddr)return -1;
    if(vt1->oldAddr > vt2->oldAddr)return 1;
    return 0;
}

/* ---------------------------------------------------------- 
 * For all classes, collect values of virtual function pointers 
 * in the old/new sets, and decide whether they all differ only by the same
 * offset, or whether their order in the internal table is diffferent and 
 * their offsets are different. When the offsets are not the same, prepare
 * a special sparse table sTab[] which finds the the offset between the old 
 * and new address by simple indexing.
 *
 * POSSIBLE RETURNS:
 * (1) Return NULL: All virtual function pointers convert by the same offset,
 *     which is returned as parameter 'virtOffset'.
 * (2) Returns sTab[], the sparse table, virtOffset which returns the minimum
 *     step between adjacent old addresses, and minAddr, the minimum old address.
 *     The table provides instant access to the offset requried for a given
 *     old address, oldAddress:
 *         offset=sTab[(oldAddress-minAddr)/virtOffset].
 *
 * NOTES:
 * - No checking for index overflow or underflow is required.
 * - Even though virtOffset is ZZsize, which means unsigned, it can store
 *   negative numbers, which work correctly when added to another ZZsize number.
 * - Unused entries of sTab[] are set to 0.
 *
 * HISTORICAL NOTE:
 * Since the inception of C++ in early 1990's, v.f.table for a given
 * program always remained constant, except for a uniform offset, and
 * this was true under DOS, UNIX and other operating systems.
 * Microsoft Visual Studio 2010 has the first compiler where this is not 
 * true: Program with the same *.h files and classes, may have different
 * configuration of these tables in different runs.
 * The new persistent systems must now compare v.f.pointers individually
 * for every class.
 *                            Jiri Soukup, August 2012
   ---------------------------------------------------------- */
static ZZsize *setVirtTable(ZZsize *virtOffset,ZZsize *minAddr){
    ZZint i,k,n,sz; VirtTable *vt; char *p; ZZsize num,*ip,*sTab,vOff;

    // count number of virt.fun. pointers (i.e. hidden pointers)
    // in all classes, including the duplications.
    for(i=n=0; ZZoList[i].numPtr>=0; i++){
        sz=ZZoList[i].size;
	for(k=0; k<sz; k++){
	    p=ZZoList[i].vObj[1];
	    if(*(p+k)=='F')n++;
	}
    }
    if(n<=0){ *virtOffset=0; *minAddr=0; return NULL;}

    // allocate the table, and fill - there still may be duplications
    vt=(VirtTable*)ZZmassAlloc(n*sizeof(VirtTable),0);
    if( !vt ){ZZmsg(76); exit(2); }
    for(i=0; ZZoList[i].numPtr>=0; i++){
        sz=ZZoList[i].size;
	for(k=0; k<sz; k++){
	    p=ZZoList[i].vObj[1];
	    if(*(p+k)=='F'){
	        p=ZZoList[i].vObj[0];
		ip=(ZZsize*)(p+k);
		vt[i].oldAddr= *ip;
	        p=ZZsList[i].vObj[0];
		ip=(ZZsize*)(p+k);
		vt[i].newAddr= *ip;
	    }
	}
    }

    // see whether all pointers are different by the same offset
    vOff=vt[0].newAddr - vt[0].oldAddr;
    for(i=1; i<n; i++){
	if(vOff!=vt[i].newAddr - vt[i].oldAddr)break;
    }
    if(i==n){ // all pointers convert by the same offset
	*virtOffset=vOff;
	*minAddr=0;
        ZZmassFree(vt);
	return NULL;
    }

    // -------------------------------------------------------------------
    // We are left with the complex case where we will have to search vt[]
    // -------------------------------------------------------------------

    // sort the table by increasing 
    qsort(vt,n,sizeof(VirtTable),cmpVirt);

    // eliminate duplications
    for(i=1,k=0; i<n; i++){
	if(vt[i].oldAddr==vt[k].oldAddr)continue;
	k++;
	vt[k].oldAddr=vt[i].oldAddr;
	vt[k].newAddr=vt[i].newAddr;
    }

    // find the minimum difference between all the adjacent old addresses
    vOff=vt[1].oldAddr - vt[0].oldAddr;
    for(i=2; i<n; i++){
	k=vt[i].oldAddr - vt[i-1].oldAddr;
	if(vOff>k)vOff=k;
    }

    // set the sparse table
    sz=(vt[n-1].oldAddr-vt[0].oldAddr)/vOff+1;
    sTab=(ZZsize*)ZZmassAlloc(sz*sizeof(ZZsize),2); // 2=initial with zeros
    if( !sTab ){ZZmsg(76); exit(2); }
    for(i=0;i<n;i++){
	k=(vt[i].oldAddr - vt[0].oldAddr)/vOff;
	sTab[k]=vt[i].newAddr - vt[i].oldAddr;
    }

    *minAddr=vt[0].oldAddr;
    ZZmassFree(vt);
    *virtOffset=vOff;
    return sTab;
}

/* ---------------------------------------------------------- */
/* ---------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZdebugMBarrays(const char *label,int style, ZZsize newInd, ZZsize ind2)
#else
void ZZdebugMBarrays(label,style,newInd, ZZsize ind2)
    const char *label; int style; ZZsize newInd,ind2;
#endif
{
    ZZsize i;
    printf("===================================\n");
    printf("%s: lowInd=%u blastSize=%u pagSize=%u ",
		                   label, lowInd, blastSize,pageSize);
    if(style==1) printf(" newInd=%u\n",newInd);
    else         printf("ind1=%u ind2=%u\n",newInd,ind2);

    for(i=lowInd; i<blastSize; i++){
	if(blastStart[i-lowInd]==NULL)continue;
	printf("%u blastStart[%u]=%u blastMap[%u]=%u\n",
	i,i-lowInd,blastStart[i-lowInd], i-lowInd,blastMap[i-lowInd]);
    }
    printf("===================================\n");
}
/* ---------------------------------------------------------- */

#ifdef ZZ_ANSI
static void debStart(void)

/* -------------------------------------------------------------
 * Debugging function which prints tables of internal arrays
 * blastStart[] and blastMap[] which are pivotal in all the memory 
 * blasting code and algorithms.
   ------------------------------------------------------------- */
#else
static void debStart()
#endif
{
    ZZsize i;
    
    printf("memory blasting debugging printout:\n");
    printf("blastSize=%u lowInd=%u ptrSize=%u mapSize=%u pageSize=%u\n",
            blastSize,lowInd,ptrSize,mapSize,pageSize);
    printf("mapShift=%u maskUp=%o maskDown=%o\n\n",
            mapShift,maskUp,maskDown);
    printf("ZZmemStart=%u ZZmemPool=%u ZZmemEnd=%u\n\n",
            ZZmemStart,ZZmemPool, ZZmemEnd);
    for(i=lowInd;i<blastSize;i++){
        if(blastStart[i-lowInd])printf(" i=%d  block=%u,%u bitmap=%u,%u\n",
            i, blastStart[i-lowInd],blastStart[i-lowInd]+pageSize-1,
            blastMap[i-lowInd],blastMap[i-lowInd]+mapSize-1);
    }
}
/* ---------------------------------------------------------- */
#ifdef ZZ_ANSI
static void debMap(void)

#else
static void debMap()
#endif
{
    ZZint i,j,k,n;
    char **p;
    
    printf("pointers recorded in the bitmap:\n");
    for(j=lowInd;j<blastSize;j++){
        if(blastMap[j-lowInd]){
            printf("  page=%u block=%u map=%u\n",j,blastStart[j-lowInd],blastMap[j-lowInd]);
            for(i=n=0;i<mapSize;i++){
                for(k=0;k<8;k++,n++){
                    if((blastMap[j-lowInd])[i]&bit8[k]){
                        p= (char **)(blastStart[j-lowInd]+n*sizeof(char *));
                        printf("    bit=%u ptr=%u *ptr=%u\n",n,p,*p);
                    }
                }
            }
        }
    }
}
/* ---------------------------------------------------------- */
#ifdef ZZ_ANSI
static void debInfo(BlastInfo *bp)

#else
static void debInfo(bp)
BlastInfo *bp;
#endif
{
    printf("blast info:\n");
    printf("  numKeys=%d\n",bp->numKeys);
    PRT_PTR("  selfStart",bp->selfStart);
    PRT_PTR("  selfEnd",bp->selfEnd);
    PRT_PTR("  virtStart",bp->virtStart);
    PRT_PTR("  virtEnd",bp->virtEnd);
    PRT_PTR("  memStart",bp->memStart);
    PRT_PTR("  memEnd",bp->memEnd);
    PRT_PTR("  memPool",bp->memPool);
    PRT_PTR("  blastSize",bp->blastSize);
    PRT_PTR("  lowInd",bp->lowInd);
    PRT_PTR("  blastNum",bp->blastNum);
    printf("  ptrSize=%d\n",ptrSize);
    PRT_PTR("  mapSize",bp->mapSize);
    PRT_PTR("  pageSize",bp->pageSize);
    printf("  mapShift=%d\n",mapShift);
    PRT_PTR("  maskUp",bp->maskUp);
    PRT_PTR("  maskDown",bp->maskDown);
}

/* --------------------------------------------------------------------- 
 * Debugging printout of the description of all classes.
 * As the input, provide either ZZsList or ZZoList.
 * --------------------------------------------------------------------- */
static void debClassDescriptions(ZZstrLST *lst,char *label){
    ZZint i,k,sz; ZZsize *up; char c;

    printf("DESCRIPTION OF CLASSES(%s):\n",label);
    for(i=0; lst[i].numPtr>=0; i++){
	sz=lst[i].size;
	printf("%d name=%s size=%d\n",i,lst[i].strName,sz);
	printf("  vObj[0]=");
	for(k=0; k<sz; k=k+sizeof(char*)){
	    printf("%u ",*(ZZsize*)(lst[i].vObj[0]+k));
	}
	printf("\n  vObj[1]=");
	for(k=0; k<sz; k++){
	    c= *(lst[i].vObj[1]+k);
	    if(c==0)printf("0 "); else printf("%c ",c);
	    if(k%4==3)printf(" ");
	}
	printf("\n");
    }
}

/* --------------------------------------------------------------------- 
 * Debugging printout of table which compares the old and new virt.pointers.
 * These are only the values, without relation to the classes and 
 * the positions inside the objects.
 * --------------------------------------------------------------------- */
static void debVirtTable(VirtTable *vTab,int sz){
    int i;
    printf("VIRTUAL POINTERS:\n");
    printf("old \t new\n");
    for(i=0;i<sz;i++){
	printf("%u \t %u\n",vTab[i].oldAddr,vTab[i].newAddr);
    }
}

