/****************************************************************/
/*							      	*/
/* Copyright (C) 1988 1989 Code Farms Inc. All Rights Reserved. */
/*							  	*/
/****************************************************************/

#define ZZcplus21   // all C++ compilers today are ver.2.1 or higher
#include <stdio.h>
#define ZZ_ERROR ZZerrFLG
#include "environ.h"

#ifndef ZZint
#include "types.h"
#endif // ZZint

#ifdef SOLARIS
#define SUN3_0
#endif

#ifdef DOS

#ifdef BORLAND
#include <mem.h>
#define bzero(A,B) (void)memset((void*)(A),0,(size_t)(B))
#endif
#ifdef MICROSOFT
#include <memory.h>
#define bzero(A,B) (void)memset((void*)(A),0,(size_t)(B))
#endif
#ifdef GNUPLUS
#include <memory.h>
#define bzero(A,B) (void)memset((void*)(A),0,(size_t)(B))
#endif
#ifdef ZORTECH
#include <string.h>
#define bzero(A,B) (void)memset((void*)(A),0,(size_t)(B))
#endif

#ifndef BORLAND
#ifndef MICROSOFT
#ifndef ZORTECH
#define bzero(A,B) \
{size_t i; char *p; \
    for(i=0, p=(char *)(A); i<(B); i++, p++)*p='\0'; \
}
#endif
#endif
#endif

#endif 

#ifdef HP
#include <string.h>
#define bzero(A,B) (void)memset((void*)(A),0,(size_t)(B))
#endif

#ifdef SOLARIS
#include <string.h>
#define bzero(A,B) (void)memset((void*)(A),0,(size_t)(B))
#endif

#ifdef MAC
#include <string.h>
#define bzero(A,B) (void)memset((void*)(A),0,(size_t)(B))
#endif

/* use MICROSOFT6 for Microsoft Ver.6.0 and less, MICROSOFT for Ver.7.0, 
 MICROSOFT8 for Microsoft Ver.8.0 or more */
#ifdef MICROSOFT6
#define MICROSOFT
#endif
#ifdef MICROSOFT8
#define MICROSOFT7
#endif
#ifdef MICROSOFT7
#define MICROSOFT
#endif

#ifdef WATCOM
#define MICROSOFT
#endif

#ifdef DEC
#define SUN
#ifdef ZZcplus
#define DECPLUS
#endif
#endif

#ifdef LINUX
#define SUN
#endif

#ifdef SUN3_0
#define SUN2_1
#endif

#ifdef SUN2_1
#define SUN
#endif

#ifdef LIANT
#define UNIX
#define SUN
#endif

#ifdef SCO
#define UNIX
#endif

#ifdef ZZcplus21
#define ZZcplus
#endif

#ifdef ZZcplus
#define ZZ_INHERIT
#define ZZ_ANSI
#endif

#ifdef BORLAND
#define TURBOC
#endif

#ifdef BORLAND4
#define BORLAND3
#endif

#ifdef BORLAND3
#define TURBOC
#endif

#ifdef TURBOC
#ifndef BORLAND3
#define FLOATLINK
#endif
#endif

#ifdef AMDAHL
#define SUN
#endif

#ifdef APOLLO
#define SUN
#endif

#ifdef IBM
#define SUN
#endif

#ifdef HP
#define SUN
#endif

#ifdef MAC
#define UNIX
#define SUN
#endif

#ifdef ZZcplus
#ifdef SUN
#ifdef GNU
#define GNUPLUS
#else
#define SUNPLUS
#endif
#endif
#ifdef TURBOC
#define TURPLUS
#endif
#endif
/* ..................................................................... */
/* older UNIX versions have ZZint qsort(), all DOS C++ compilers have void */
#ifdef SUN
#ifdef GNU
#define QSORT_TYPE void
#else // GNU
#define QSORT_TYPE ZZint
#endif // GNU
#else
#define QSORT_TYPE void
#endif


#ifdef TC_HUGE
#include <alloc.h>
#endif

#ifdef SUNPLUS
#ifndef zzLIB
#include <stdlib.h>
#endif
#endif

#ifdef LINUX
#include <stdlib.h>
#endif

#ifdef MAC
#include <stdlib.h>
#endif

#ifdef ZZcalloc
#ifndef ZZcplus
#define ZZcCalloc
#endif
#endif

#ifdef COHERENT
#include "stdlib.h"
#endif

#ifdef HP
#ifdef ZZansi
#include <stdlib.h>
#endif
#endif

#ifdef ZZansi
#define ZZ_ANSI
#endif

#ifdef ZORTECH
#define MICROSOFT
#define ZZ_ANSI
#endif

#ifdef MICROSOFT
#include <stdlib.h>
#ifdef ZZcplus
#define MICPLUS
#endif
#endif

#ifdef MAC
#include <stdlib.h>
#endif

#ifdef TURBOC
#ifdef ZZcplus
#include <stdlib.h>
#endif
#endif

#ifdef TURBOC
#define VIRTUAL_BORLAND
#endif

#ifdef ZZ_ANSI
#include <string.h>
#endif

#ifdef ZZlocal
#define ZZmain
#define ZZ_LOCAL static
#else
#define ZZ_LOCAL
#endif

#ifdef ZZmain
#define ZZ_EXTERN
#else
#define ZZ_EXTERN extern
#endif

#ifndef ZZcplus
typedef struct ZZarray ZZarray;
#endif
struct ZZarray {
    ZZint num;       /* number of objects in the array */
    ZZint waterM;    /* current high water mark in objects */
    ZZint strType;   /* structure type index */
    ZZint size;      /* object size in bytes */
    ZZint incr;      /* increment if array is not large enough */
    char *array;     /* pointers to the array of objects */
    ZZint targType;  /* for arrays of pointers to objects(>=0) or strings(-1) */
                     /* -2 for arrays of values */
};
/* Negative increment to multiply, positive to add, 0 fixed size */
/* For hash tables: size is the counter of objects, always waterM=num */
/* hshType>=-1 means this is a hash table */

#ifdef UNIX

#ifdef MAC
#define ZZ_PASTE2
#else
#ifdef GNU
#define ZZ_PASTE2
#else
#ifdef HP
#ifdef ZZ_ANSI
#define ZZ_PASTE2
#else
#define ZZ_PASTE1
#endif
#else
#ifdef LIANT
#define ZZ_PASTE2
#else
#ifdef COHERENT
#define ZZ_PASTE2
#else
#ifdef IBM
#define ZZ_PASTE2
#else
#ifdef LUCID
#define ZZ_PASTE2
#else
#ifdef DECPLUS
#define ZZ_PASTE2
#else
#ifdef SUN2_1
#define ZZ_PASTE2
#else
#define ZZ_PASTE1
#endif /* SUN2_1 */
#endif /* DECPLUS */
#endif /* LUCID */
#endif /* IBM */
#endif /* COHERENT */
#endif /* LIANT */
#endif /* HP */
#endif /* GNU */
#endif /* MAC */
#endif /* UNIX */

#ifdef DOS
#define ZZ_PASTE2
#endif 

#ifdef VMS
#ifdef ZZcplus
#define ZZ_PASTE2
#else
#define ZZ_PASTE3
#endif
#endif

#ifdef APOLLO
#define ZZ_PASTE4
#undef ZZ_PASTE1
#endif

#ifdef LINUX
#define ZZ_PASTE2
#undef ZZ_PASTE1
#undef ZZ_PASTE3
#undef ZZ_PASTE4
#endif

#ifdef ZZ_PASTE1
#define ZZ_STRINGIT(A) (char*) "A"
/* form index and form type codes */
#define ZZFP(A,B) A/**/B
#define ZZFT(A,B) ZZ/**/A/**/B
#define ZZFC(A,B) ZZC/**/A/**/B
#define ZZFN(A,B) A/**/_/**/B
#endif
#ifdef ZZ_PASTE2
#define ZZ_STRINGIT(A) (char*) #A
/* form index and form type codes */
#define ZZFP(A,B) A##B
#define ZZFT(A,B) ZZ##A##B
#define ZZFC(A,B) ZZC##A##B
#define ZZFN(A,B) A##_##B
#endif
#ifdef ZZ_PASTE3
#define ZZ_STRINGIT(A) (char*) "A"
/* form index and form type codes */
#define ZZFP(A,B) A\
B
#define ZZFT(A,B) ZZ\
A\
B
#define ZZFC(A,B) ZZC\
A\
B
#define ZZFN(A,B) A\
_\
B
#endif

#ifdef ZZ_PASTE4
#define ZZ_CAT(A,B) A##B
#define ZZ_CATN(A,B) ZZ_CAT(A,B)
#define ZZ_STRINGIT(A) (char*) #A
/* form index and form type codes */
#define ZZFP(A,B) ZZ_CAT(A,B)
#define ZZFT(A,B) ZZ_CATN(ZZ_CATN(ZZ,A),B)
#define ZZFC(A,B) ZZ_CATN(ZZ_CATN(ZZC,A),B)
#define ZZFN(A,B) ZZ_CATN(ZZ_CATN(A,_),B)
#endif

#ifndef ZZ_ANSI

#ifdef ZZsaveSpecial
void zzSaveSpecial();
#endif
typedef FILE *(*ZZ_USER_OPEN)();
typedef ZZint   (*ZZ_USER_READ)();
typedef ZZint   (*ZZ_USER_WRITE)();
typedef ZZint   (*ZZ_USER_CLOSE)();
void ZZinstallUserIO();

#define ZZgalloc(A)      ZZnewObj(A,0)
#define ZZgfree(A)       ZZdelObj(A)
#define ZZFUN_galloc()   ZZnewObj()
#define ZZFUN_gfree()    ZZdelObj()
#define ZZFUN_allo()     ZZallo()
#define ZZFUN_stTime()   ZZstTime()
#define ZZFUN_gtTime()   ZZgtTime()
#define ZZFUN_readBind() ZZreadBind()
#define ZZFUN_rSRfun()   ZZrSRfun()
#define ZZFUN_ini()      ZZini()
#define ZZFUN_deal()     ZZdeal()
#define ZZFUN_formPager()  ZZformPager()
#define ZZFUN_ioPager()    ZZioPager()
#define ZZFUN_closePager() ZZclosePager()
#define ZZFUN_flushPager() ZZflushPager()
#define ZZFUN_foArr()    ZZfoArr()
#define ZZFUN_frArr()    ZZfrArr()
#define ZZFUN_upArr()    ZZupArr()
#define ZZFUN_upHeap()   ZZupHeap()
#define ZZFUN_downHeap() ZZdownHeap()
#define ZZFUN_hsh()      ZZhsh()
#define ZZFUN_swpSet()   ZZswpSet()
#define ZZFUN_saveKeys() ZZsaveKeys()
#define ZZFUN_swpFree()  ZZswpFree()
#define ZZFUN_swpFun()   ZZswpFun()
#define ZZFUN_saveAll()  ZZsaveAll()
#define ZZFUN_freeAll()  ZZfreeAll()
#define ZZFUN_objMem()   ZZobjMem()
#define ZZFUN_upHash()   ZZupHash()
#define ZZFUN_frHash()   ZZfrHash()
#define ZZFUN_pOffset()  ZZpOffset()
#define ZZFUN_getNames() ZZgetNames()
#define ZZFUN_propDelete() ZZpropDelete()
#define ZZFUN_propGet() ZZpropGet()
#define ZZFUN_wrtProperty() ZZwrtProperty()
#define ZZFUN_prSize() ZZprSize()
#define ZZFUN_propSet() ZZpropSet()
#define ZZFUN_cnvProp() ZZcnvProp()
#define ZZFUN_writeBind() ZZwriteBind()
#define ZZFUN_writeASCII() ZZwriteASCII()
#define ZZFUN_bindObj() ZZbindObj()
ZZ_LOCAL void ZZ_GENERAL_EXT();
#define ZZFUN_closeBind() ZZcloseBind()
#define ZZFUN_blastSave() ZZblastSave()
#define ZZFUN_blastOpen() ZZblastOpen()
#define ZZFUN_blastClear() ZZblastClear()
#define ZZFUN_findType() ZZfindType()
#define ZZFUN_findName() ZZfindName()
#define ZZFUN_afterOpen() ZZafterOpen()
#define ZZFUN_bindCnv() ZZbindCnv()
#define ZZFUN_bitCopy() ZZbitCopy()
#define ZZFUN_blkActive()   ZZblkActive()
#define ZZFUN_blkUtil()   ZZblkUtil()
#define ZZFUN_massAlloc()   ZZmassAlloc()
#define ZZ_DEB_PRT(A,B) {\
void ZZdebPrt(); ZZ_GENERAL_EXT(); \
ZZdebPrt((char *)(A),B,ZZstrList,ZZptrList,ZZnxtType);}
#define ZZFUN_QSORT      QSORT_TYPE qsort();
#endif

#ifdef ZZ_ANSI

#ifdef ZZsaveSpecial
void zzSaveSpecial(char *,ZZint,ZZint,char *);
#endif

#ifdef SUN
extern "C" { typedef int (*ZZTsortExt)(const void *,const void *); }
#else
typedef int (*ZZTsortExt)(const void *,const void *); 
#endif 

typedef void (*ZZTvoidFun)(void *);
typedef ZZint (*ZZTsortFun)(const void *,const void *);
typedef ZZint (*ZZTsortArr)(const void *,const void *);
typedef void (*ZZTswpFun)(char *,ZZint,ZZint,const char *);
typedef ZZint (*ZZThashKey)(char *,ZZint);
typedef ZZint (*ZZThashCmp)(char *,char *);
typedef void (*ZZTheapBck)(void *,ZZint);
typedef FILE *(*ZZ_USER_OPEN)(const char *fileName,char *mode);
typedef ZZint   (*ZZ_USER_READ)(FILE *fp,char *buff,ZZint n);
typedef ZZint   (*ZZ_USER_WRITE)(FILE *fp,char *buff,ZZint n);
typedef ZZint   (*ZZ_USER_CLOSE)(FILE *fp);
void ZZinstallUserIO(ZZ_USER_OPEN,ZZ_USER_READ,ZZ_USER_WRITE,ZZ_USER_CLOSE);

#define ZZgalloc(A)      ZZnewObj(A,0)
#define ZZgfree(A)       ZZdelObj(A)
#define ZZFUN_galloc()   ZZnewObj(ZZint i,ZZint k)
#define ZZFUN_gfree()    ZZdelObj(char *p)
#define ZZFUN_allo()     ZZallo(struct ZZstrLST *s,char **seflA,ZZint si,char *sType,\
   ZZint typeInd,ZZint num,ZZint size,ZZint mode)
#define ZZFUN_stTime()   ZZstTime(unsigned char *a)
#define ZZFUN_gtTime()   ZZgtTime(unsigned char *a,unsigned char *b)
#define ZZFUN_readBind() ZZreadBind(const char *f,ZZint n,char **p,char **t,ZZint ns)
#define ZZFUN_rSRfun()   ZZrSRfun(char *a,char *s,ZZTsortFun fun)
#define ZZFUN_ini()  ZZini(char *p,struct ZZstrLST *s,char **selfArr,\
    ZZint si,ZZint mode,ZZint typeInd,ZZint num,ZZint size)
#define ZZFUN_deal() ZZdeal(char *p,struct ZZstrLST *s,\
                     char *strType,ZZint num,ZZint size,ZZint action)
#define ZZFUN_formPager()  ZZformPager(const char *,ZZint,ZZint,ZZint)
#define ZZFUN_ioPager()    ZZioPager(ZZint,char *,ZZlong,char *,ZZint)
#define ZZFUN_closePager() ZZclosePager(char *)
#define ZZFUN_flushPager() ZZflushPager(char *)
#define ZZFUN_foArr() ZZfoArr(ZZint nm,ZZint inc,ZZint oSz,ZZint sTyp,const char *hTyp,\
                             struct ZZstrLST *s,const char *sample) 
#define ZZFUN_frArr() ZZfrArr(ZZarray *arr,char *t,struct ZZstrLST *s)
#define ZZFUN_upArr() ZZupArr(ZZarray *arr,ZZint ind,char *sample)
#define ZZFUN_upHeap()   ZZupHeap(ZZarray *a,ZZint ind,ZZTsortFun fun,\
                                  ZZTheapBck bck)
#define ZZFUN_downHeap() ZZdownHeap(ZZarray *a,ZZint ind,ZZTsortFun fun,\
                                  ZZTheapBck bck)
#define ZZFUN_hsh()      ZZhsh(char *a,ZZint n,ZZint wm,ZZint size,ZZint opt,\
                                                     char *e,ZZTsortFun fun)
#define ZZFUN_swpSet()  \
ZZswpSet(struct ZZstrLST *sL,ZZint *pC,char **v,char **t,ZZint n,ZZint array)
#define ZZFUN_saveKeys() ZZsaveKeys(const char *fileName,struct ZZstrLST *L,char **v,\
                                                           char **t,ZZint n)
#define ZZFUN_swpFree()  ZZswpFree(void)
#define ZZFUN_swpFun()   ZZswpFun(ZZTswpFun fun,const char *priv)
#define ZZFUN_saveAll()  ZZsaveAll(const char *fileName)
#define ZZFUN_freeAll()  ZZfreeAll(void)
#define ZZFUN_objMem()   ZZobjMem(ZZint c,char **p,ZZint t,struct ZZstrLST *sL)
#define ZZFUN_upHash()   ZZupHash(ZZarray *a,ZZint s,ZZint offset,ZZThashKey fun)
#define ZZFUN_frHash()   ZZfrHash(ZZarray *arr,unsigned ZZint off)
#define ZZFUN_pOffset()  ZZpOffset(char *p2,char *p1)
#define ZZFUN_getNames() ZZgetNames(FILE *fp,char **arr,ZZint num)
#define ZZFUN_propDelete() ZZpropDelete(struct ZZproperty *pp, struct ZZproperty **s)
#define ZZFUN_propGet() \
ZZpropGet(struct ZZproperty **s,char *n,char *t,char **b,ZZint *sz)
#define ZZFUN_wrtProperty() \
ZZwrtProperty(FILE *file,char *tp,char *name,char *val,ZZint num)
#define ZZFUN_prSize() ZZprSize(struct ZZproperty *pp)
#define ZZFUN_propSet() \
ZZpropSet(struct ZZproperty **start,char *t,char *n,char *b,ZZint sz)
#define ZZFUN_cnvProp() ZZcnvProp(char *code,ZZint sz,char **pt,ZZint *n)
#define ZZFUN_writeBind() \
ZZwriteBind(ZZint size,ZZint type,const char *file,char *ptr,ZZint num,ZZint key)
#define ZZFUN_writeASCII() \
ZZwriteASCII(ZZint size,ZZint type,const char *file,char *ptr,ZZint num,ZZint key)
#define ZZFUN_bindObj() ZZbindObj(char **obj,char *type)
ZZ_LOCAL void ZZ_GENERAL_EXT(void);
#define ZZFUN_closeBind() ZZcloseBind(const char *)
#define ZZFUN_blastSave() ZZblastSave(const char *,ZZint n,char **v)
#define ZZFUN_blastOpen() ZZblastOpen(const char *,ZZint n,char **v)
#define ZZFUN_blastClear() ZZblastClear(void)
#define ZZFUN_findType() ZZfindType(struct ZZstrLST *sList,char *tName)
#define ZZFUN_findName() ZZfindName(struct ZZstrLST *sList,ZZint type)
#define ZZFUN_afterOpen() ZZafterOpen(void)
#define ZZFUN_bindCnv() ZZbindCnv(char *p,ZZint *err)
#define ZZFUN_bitCopy() ZZbitCopy(ZZint sz,char *from, char *to)
#define ZZFUN_blkActive() ZZblkActive(char *bn,ZZint mode)
#define ZZFUN_blkUtil() ZZblkUtil(char *bn,void **hook,ZZint mode)
#define ZZFUN_massAlloc() ZZmassAlloc(size_t size, ZZint mode)
#define ZZ_DEB_PRT(A,B) {\
 void ZZdebPrt(char *,char *,struct ZZstrLST *,char **,ZZint *);\
 ZZ_GENERAL_EXT(); \
 ZZdebPrt((char *)(A),B,ZZstrList,ZZptrList,ZZnxtType);}

#ifdef SUNPLUS
typedef ZZint (*ZZ_SRTF)(void *,void *);
#else
typedef ZZint (*ZZ_SRTF)(void *,void *);
#endif

#ifdef ZZcplus
#define ZZFUN_QSORT
#ifndef ZORTECH
#ifndef TURPLUS
#ifndef GNUPLUS
#ifndef MAC
#ifndef HP
#ifndef IBM
#ifndef MICROSOFT
#ifndef SABERCPLUS
#ifndef LUCID
#ifdef zzLIB
#ifndef SUN2_1
#ifndef DECPLUS
extern "C" { 
    QSORT_TYPE qsort(void *,ZZint,ZZint,ZZ_SRTF);
    char *calloc(unsigned ZZint ,unsigned ZZint );
}
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#else
#ifdef BORLAND3
#define ZZFUN_QSORT 
#else
#define ZZFUN_QSORT    QSORT_TYPE qsort(void *,ZZint,ZZint,ZZ_SRTF);
#endif
#endif

#endif

#ifdef LARGE_POINTER
#define ZZptrIntType unsigned ZZlong
#define ZZsigIntType ZZlong
#else
#define ZZptrIntType unsigned ZZint
#define ZZsigIntType ZZint
#endif

#ifdef ZZmain
#ifdef ZZlocal
static ZZ_USER_OPEN ZZuserOpen = {0};
static ZZ_USER_READ ZZuserRead = {0};
static ZZ_USER_WRITE ZZuserWrite = {0};
static ZZ_USER_CLOSE ZZuserClose = {0};
static ZZint ZZdebFLG;
static ZZint ZZerrFLG;
static ZZsigIntType ZZnumObjects ={0}; /* num.of alloc.objects,incl. arrays */
static ZZsigIntType ZZbestGuess ={0}; /* guess num.of objects to be collected */
static ZZint ZZdiskIO;  /* 0=write(), 1=fwrite(); */
static ZZint ZZnTbType; /* number of ZZintegers recorded for each type */
static ZZint ZZpTbType; /* 1=list of poZZinter names, 0=no list */
static ZZint ZZcustomPtr; /* custom conversion of pointers requested */
static char *ZZmemStart={0}; /* start of the one-block memory, 0=unused */
static char *ZZmemEnd={0};  /* next address after the end of block */
static char *ZZmemPool={0};  /* beginning of the current pool */
static ZZint ZZmemSwitch={0};  /* 2=blasting, 1=big memory, 0=serialization */
static ZZint ZZioSwitch={0};  /* 0=serialization, 1=mem.blasting */
static ZZint ZZcallocFlg;  /* =1 when calloc is used for allocation */
#else
ZZ_USER_OPEN ZZuserOpen = {0};
ZZ_USER_READ ZZuserRead = {0};
ZZ_USER_WRITE ZZuserWrite = {0};
ZZ_USER_CLOSE ZZuserClose = {0};
ZZint ZZdebFLG={0};
ZZint ZZerrFLG={0};
ZZsigIntType ZZnumObjects ={0};
ZZsigIntType ZZbestGuess ={0};
ZZint ZZdiskIO={1};  /* 0=write(), 1=fwrite(); */
ZZint ZZnTbType={9}; /* number of ZZintegers recorded for each type */
ZZint ZZpTbType={1}; /* 1=list of poZZinter names, 0=no list */ 
ZZint ZZcustomPtr={0}; /* custom conversion of poZZinters requested */
char *ZZmemStart={0}; /* start of the one-block memory, 0=unused */
char *ZZmemEnd={0};  /* next address after the end of block */
char *ZZmemPool={0};  /* beginning of the current pool */
ZZint ZZmemSwitch={0};  /* 2=blasting, 1=big memory, 0=serialization */
ZZint ZZioSwitch={0};  /* 0=serialization, 1=mem.blasting */
ZZint ZZcallocFlg;  /* =1 when calloc is used for allocation */
#endif
#endif
#ifndef ZZmain
extern ZZ_USER_OPEN ZZuserOpen;
extern ZZ_USER_READ ZZuserRead;
extern ZZ_USER_WRITE ZZuserWrite;
extern ZZ_USER_CLOSE ZZuserClose;
extern ZZint ZZdebFLG;
extern ZZint ZZerrFLG;
extern ZZsigIntType ZZnumObjects;
extern ZZsigIntType ZZbestGuess;
extern ZZint ZZdiskIO;  /* 0=write(), 1=fwrite(); */
extern ZZint ZZnTbType; /* number of ZZintegers recorded for each type */
extern ZZint ZZpTbType; /* 1=list of poZZinter names, 0=no list */
extern ZZint ZZcustomPtr; /* custom conversion of poZZinters requested */
extern char *ZZmemStart; /* start of the one-block memory, 0=unused */
extern char *ZZmemEnd;  /* next address after the end of block */
extern char *ZZmemPool;  /* beginning of the current pool */
extern ZZint ZZmemSwitch;  /* 2=blasting, 1=big memory, 0=serialization */
extern ZZint ZZioSwitch;  /* 0=serialization, 1=mem.blasting */
extern ZZint ZZcallocFlg;  /* =1 when calloc is used for allocation */
#endif

#ifdef TURBOC
#define ZZstaticInt ZZint
#define ZZstaticVoid void
#define ZZstaticChar char
#define ZZstaticStruct struct
#else
#ifdef SUN
#define ZZstaticInt ZZint
#define ZZstaticVoid void
#define ZZstaticChar char
#define ZZstaticStruct struct
#else
#define ZZstaticInt static ZZint
#define ZZstaticVoid static void
#define ZZstaticChar static char
#define ZZstaticStruct static struct
#endif
#endif

#define ZZ_TYPE_NAME(A,B) {char *ZZFUN_findName(); (B)=ZZfindName(ZZsList,A);}

#ifdef LARGE_POINTER
#define ALWAYS_INT(A,B) ZZlongToInt(A,B)
#else
#define ALWAYS_INT(A,B) B
#endif

#ifdef LARGE_POINTER
#define PRT_PTR(A,B) printf("%s=%lu\n",A,(ZZlong)(B))
#else
#define PRT_PTR(A,B) printf("%s=%u\n",A,(ZZint)(B))
#endif

/*
#define ITERATE(A,B) for((B)= ++(A); (B); (B)= ++(A))
#define RETRACE(A,B) for((B)= --(A); (B); (B)= --(A))
*/
// or a more elegant version:
#define ITERATE(A,B) while((B) = ++(A))
#define RETRACE(A,B) while((B) = --(A))

/* type info defines and structures for C++ */
#ifdef ZZcplus
#define ZZgetType(A) ZZFP(ZZZI,A)()
struct zzTypeInfo {
    char *name;  // class name
    ZZint size;    // size of this class
    char *mask1; // byte=1 for virt.fun. or virt.class poZZinters
    char *mask2; // 'F' or 'C' for bytes that start v.f./v.c. poZZinters
    ZZint virt;    // bin packed:
        // 01=abstr.class,02=virt.base class,04=virt.functions present
};
#endif

#define ZZbreakLine /* breaking line for large files, needed under DOS only */

#define CHECK_ALLOC(TXT,SZ,RET) \
{\
    if(RET==NULL){\
        ZZerrFLG=ZZerrFLG|02;\
	printf("allocation failed for <%s>,\n",TXT);\
	exit(1);\
    }\
    if(ZZ_MAXU-(ZZsize)RET + 1 < SZ){\
        ZZerrFLG=ZZerrFLG|02;\
	printf("allocation beyond virt.adress space<%s>\n",TXT);\
	exit(1);\
    }\
}
