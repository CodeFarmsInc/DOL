/* 116 4 15 12 13 50 */
#ifndef ZZint

#ifdef Windows64
#define ZZlong long long
#define ZZint long long
#define ZZfloat long double
#define ZZsize unsigned long long
#else
#define ZZlong long
#define ZZint int
#define ZZfloat float
#define ZZsize unsigned long 
#endif

ZZint ZZlongToInt(char *,ZZlong);
unsigned ZZlong ZZptrToLong(char *);
char *ZZintToPtr(ZZint);
ZZint ZZptrToInt(const char *);
ZZsize ZZptrToSize(char *);
char *ZZsizeToPtr(ZZsize);

#define ZZ_MAXU ((ZZsize)(-1) - 1)

#endif // ZZint

#ifdef AMDAHL
#define ZZvoidS ZZint
#else
#define ZZvoidS void
#endif
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
#define ZZ_FORM_PAGER(id,obj,fName,pgSz,nPgs,ini)\
ZZZ_FORM_PAGER(id,ZZFP(ZZh,id),obj,fName,pgSz,nPgs,ini)

#define ZZZ_FORM_PAGER(id,hPtr,obj,fName,pgSz,nPgs,ini)\
{ char *ZZFUN_formPager();\
    (obj)->hPtr=ZZformPager(fName,pgSz,nPgs,ini);\
}
#define ZZ_IO_PAGER(id,obj,ind,buff,n,mode)\
ZZZ_IO_PAGER(id,ZZFP(ZZh,id),obj,ind,buff,n,mode)

#define ZZZ_IO_PAGER(id,hPtr,obj,ind,buff,n,mode)\
{ ZZint ZZFUN_ioPager();\
    return ZZioPager(mode,(obj)->hPtr,ind,buff,n);\
}
#define ZZ_CLOSE_PAGER(id,obj)\
ZZZ_CLOSE_PAGER(ZZFP(ZZh,id),obj)

#define ZZZ_CLOSE_PAGER(hPtr,obj)\
{ void ZZFUN_closePager();\
    if((obj)->hPtr)ZZclosePager((obj)->hPtr);\
    (obj)->hPtr=NULL;\
}
#define ZZ_ADDRESS_PAGER(id,obj,ind,ptr)\
ZZZ_ADDRESS_PAGER(id,ZZFP(ZZh,id),obj,ind,ptr)

#define ZZZ_ADDRESS_PAGER(id,hPtr,obj,ind,ptr)\
{ char *ZZFUN_ioPager();\
    (ptr)=ZZioPager(0,(obj)->hPtr,ind,NULL,1);\
}
#define ZZ_ORG_PAGER(id,strType) /* ZZ_ORG_PAGER */
#define ZZ_HYPER_PAGER(id,hType) \
ZZ_BASIC_PAGER(id,hType,ZZ_EXTERN,id) 

#define ZZ_LOCAL_PAGER(id,hType,where) \
ZZ_BASIC_PAGER(id,hType,static,where :: id) 

#define ZZ_BASIC_PAGER(id,hType,scope,where) \
class ZZFP(ZZH,id) { \
    friend class hType;\
public: \
    void form(hType *hp,const char *fName,ZZint pgSz,ZZint nPgs,ZZint ini){\
             ZZ_FORM_PAGER(id,hp,fName,pgSz,nPgs,ini);}\
    ZZint io(hType *hp,ZZlong ind,char *buff,ZZint n,ZZint mode){\
             ZZ_IO_PAGER(id,hp,ind,buff,n,mode);}\
    void close(hType *hp){ZZ_CLOSE_PAGER(id,hp);}\
    void flush(hType *hp) {\
       void ZZflushPager(char*); ZZflushPager((char*)(hp->ZZFP(ZZh,id)));}\
    ZZlong fill(hType *hp) {\
       ZZlong ZZfillPager(char*); return ZZfillPager((char*)(hp->ZZFP(ZZh,id)));}\
};\
scope ZZFP(ZZH,id) id
#define ZZ_BIND_POINTER(oldP,newP) \
{char *ZZFUN_bindCnv(),**ZZp; ZZint ZZe;\
    if(ZZbindTable){\
        ZZp=(char**)(&(newP));\
        *ZZp=ZZbindCnv((char *)(oldP),&ZZe);\
        if(ZZe)ZZerrFLG=ZZerrFLG|040;\
    }\
    else ZZerrFLG=ZZerrFLG|04;\
}
#define ZZ_KEEP_TABLES() \
ZZcustomPtr=1;
#define ZZ_FREE_TABLES() \
{void ZZFUN_afterOpen(); ZZafterOpen();}
#ifdef VMS
#define ZZ_FORMAT(type,format) unsigned char ZZFORMAT##type
#else
#define ZZ_FORMAT(type,format) /* ZZ_FORMAT */
#endif
#define ZZ_UPD_DOUBLE(tp2,fwp,bwp,obj) \
{tp2 *ZZp,*ZZs;\
    if(obj){\
        for(ZZp=(obj),ZZs=(obj)->fwp; ; ZZp=ZZs, ZZs=ZZs->fwp){\
            ZZs->bwp=ZZp;\
            if(ZZs==(obj))break;\
        }\
    }\
}
#define ZZ_MERGE_SINGLE_RING(id,obj1,obj2,par) \
ZZZ_MERGE_SINGLE_RING(id,ZZFT(1,id),ZZFP(ZZf,id),obj1,obj2,par)

#define ZZZ_MERGE_SINGLE_RING(id,strType,fwp,obj1,obj2,par) \
{strType *ZZp,*ZZi;\
    ZZi=(par);\
    if(!(obj1) || !(obj2))ZZi++;\
    else {\
        if(!((obj1)->fwp) || !((obj2)->fwp))ZZi++;\
        else if((obj1)!=(obj2)){\
            ZZp=(obj2)->fwp; \
            (obj2)->fwp=(obj1)->fwp;\
            (obj1)->fwp=ZZp;\
        }\
    }\
    if(ZZi)ZZmsgS(33,ZZ_STRINGIT(id));\
}
#define ZZ_MERGE_DOUBLE_RING(id,obj1,obj2,par) \
ZZZ_MERGE_DOUBLE_RING(id,ZZFT(1,id),ZZFP(ZZf,id),ZZFP(ZZb,id),obj1,obj2,par)

#define ZZZ_MERGE_DOUBLE_RING(id,strType,fwp,bwp,obj1,obj2,par) \
{strType *ZZp,*ZZi;\
    ZZi=par;\
    if(!(obj1) || !(obj2))ZZi++;\
    else {\
        if(!((obj1)->fwp) || !((obj2)->fwp))ZZi++;\
        else if((obj1)!=(obj2)){\
            ZZp=(obj2)->fwp; \
            (obj1)->fwp->bwp=(obj2);\
            ZZp->bwp=(obj1);\
            (obj2)->fwp=(obj1)->fwp;\
            (obj1)->fwp=ZZp;\
        }\
    }\
    if(ZZi)ZZmsgS(33,ZZ_STRINGIT(id));\
}
#define ZZ_MERGE_SINGLE_TRIANGLE(id,obj1,obj2,par) \
ZZZ_MERGE_SINGLE_TRIANGLE\
(id,ZZFT(1,id),ZZFT(2,id),ZZFP(ZZs,id),ZZFP(ZZp,id),ZZFP(ZZc,id),obj1,obj2,par)

#define ZZZ_MERGE_SINGLE_TRIANGLE(id,tp1,tp2,sib,par,chi,obj1,obj2,nPar) \
{tp2 *ZZp; tp1 *ZZs; ZZint ZZi;\
    ZZi=0; ZZs=(nPar);\
    if(!(obj1) || !(obj2))ZZi=1;\
    else {\
        if(!((obj1)->sib) || !((obj2)->sib))ZZi=1;\
        else if((obj1)->par==(obj2)->par && ZZs->chi)ZZi=1;\
        else if((obj1)->par!=(obj2)->par && !(ZZs->chi))ZZi=1;\
        else if(obj1!=obj2){\
            ZZp=(obj2)->sib; \
            (obj2)->sib=(obj1)->sib;\
            (obj1)->sib=ZZp;\
        }\
    }\
    if(ZZi)ZZmsgS(33,ZZ_STRINGIT(id));\
    else {\
        if((obj1)->par==(obj2)->par){\
            for(ZZp=(obj2);ZZp->sib!=(obj2);ZZp=ZZp->sib)ZZp->par=ZZs;\
            ZZp->par=ZZs;\
            ZZs->chi=ZZp;\
        }\
        else {\
            (obj2)->par->chi=NULL;\
            ZZs=(obj1)->par;\
            for(ZZp=(obj1);ZZp!=(obj2);ZZp=ZZp->sib)ZZp->par=ZZs;\
            (obj2)->par=ZZs;\
        }\
    }\
}
#define ZZ_MERGE(id,obj1,obj2,par) \
ZZFN(ZZ_MERGE,id)(id,obj1,obj2,par)

#define ZZ_ALLOCATE_AND_READ(strType,ptr,FORMT) \
{\
    ZZ_PLAIN_ALLOC(strType,1,ptr);\
    if(ptr){\
        if(EOF==fscanf FORMT ){\
	    ZZ_PLAIN_FREE(strType,1,ptr);\
	    (ptr)=NULL;\
        }\
    }\
}

#define ZZ_SWEEP_SET(n,obj,type) \
{ZZint ZZFUN_swpSet(); \
ZZ_GENERAL_EXT(); \
return ZZswpSet(ZZstrList,ZZnxtType,(char **)(obj),type,n,0);}

#define ZZ_SWEEP_FREE \
{ZZint ZZFUN_swpFree(); ZZswpFree();}

#define ZZ_SWEEP_FUNCTION(fun,priv) \
{void ZZFUN_swpFun(); ZZswpFun(fun,priv); }

#define ZZ_SAVE(fileName,n,obj,type) \
{ZZint ZZFUN_swpSet();\
 ZZint ZZFUN_saveKeys(); \
 ZZint ZZFUN_saveAll();\
 ZZint ZZFUN_swpFree();\
 void ZZFUN_closeBind();\
 void ZZFUN_blastSave(); \
    ZZ_GENERAL_EXT(); \
    if(ZZerrFLG){ZZmsgD(31,ZZerrFLG); ZZerrFLG=0;}\
    if(ZZioSwitch==1 && ZZmemSwitch==2)ZZblastSave(fileName,n,(char **)(obj));\
    else {\
        ZZswpSet(ZZstrList,ZZnxtType,(char **)(obj),type,n,0);\
        if(!ZZerrFLG){\
            ZZsaveKeys(fileName,ZZstrList,(char **)(obj),type,n);\
            ZZsaveAll(fileName);\
            ZZswpFree();\
            if(ZZbindCntrl!=2)ZZcloseBind(fileName);\
        }\
    }\
}
#define ZZ_DEEP(fileName,obj,type) \
{ZZint ZZFUN_swpSet();\
 ZZint ZZFUN_saveAll();\
 ZZint ZZFUN_swpFree();\
    ZZ_GENERAL_EXT(); \
    ZZswpSet(ZZstrList,ZZnxtType,(char **)(&(obj)),&(type),1,0);\
    ZZsaveAll(fileName);\
    ZZswpFree();\
}

#define ZZ_MODE_SAVE(ascii,diskIO,version,cntrl) \
{ZZint ZZv;\
 ZZbindASCII=(ascii);ZZdiskIO=(diskIO);ZZv=(version);ZZbindCntrl=(cntrl);\
 if(ascii<2)ZZioSwitch=0; else ZZioSwitch=1; \
 if((ZZdiskIO)==2){\
    if(!((ZZuserOpen && ZZuserClose) || (ZZuserRead && ZZuserWrite))){\
        ZZmsg(65);\
    }\
 }\
 if     (ZZv==0  ){ZZnTbType=9; ZZpTbType=1;}\
 else if(ZZv< 150){ZZnTbType=7; ZZpTbType=0;}\
 else if(ZZv<=164){ZZnTbType=8; ZZpTbType=0;}\
 else if(ZZv==165){ZZnTbType=8; ZZpTbType=1;}\
 else             {ZZnTbType=9; ZZpTbType=1;}\
}

#define ZZ_CLEAR(n,obj,type) \
{ZZint ZZFUN_swpSet();\
 ZZint ZZFUN_freeAll();\
 ZZint ZZFUN_swpFree(); \
 void ZZFUN_blastClear(); \
        ZZ_GENERAL_EXT(); \
        if(ZZmemSwitch==2)ZZblastClear();\
        else {\
            ZZswpSet(ZZstrList,ZZnxtType,(char **)(obj),type,n,1); \
            if(!ZZerrFLG){\
                ZZfreeAll();\
                ZZswpFree();\
            } \
            else printf("internal error in swpSet()\n"); \
        }\
}

#define ZZ_HYPER_UTILITIES(id)  \
class ZZFP(ZZH,id) { \
public: \
    char * strAlloc(const char *s){char *p; ZZ_STRING_ALLOC(s,p); return(p);}\
    char * strAlloc(ZZint sz);\
    void strFree(char *p){ZZ_STRING_FREE(p);}\
    ZZint error(void){return(ZZerror);}\
    void ok(void){ZZerror=0;}\
    void guess(long g){ZZbestGuess=(ZZsigIntType)g;}\
    void save(const char *file,ZZint n,void **v, char **t){save(file,n,(char**)v,t);}\
    void save(const char *file,ZZint n,char **v, char **t);\
    void deep(const char *file,void *v, char *t);\
    void open(const char *file,ZZint n,void **v, char **t){open(file,n,(char**)v,t);}\
    void open(const char *file,ZZint n,char **v, char **t);\
    void clear(ZZint n,void **v, char **t){clear(n,(char**)v,t);}\
    void clear(ZZint n,char **v, char **t);\
    ZZint swpSet(ZZint n,char **v, char **t){ZZ_SWEEP_SET(n,v,t);}\
    void swpFun(ZZTswpFun myFun,const char *par){ZZ_SWEEP_FUNCTION(myFun,par);}\
    void swpFree(void){ZZ_SWEEP_FREE;}\
    void keepTbl(void){ZZ_KEEP_TABLES();}\
    void freeTbl(void){ZZ_FREE_TABLES();}\
    void debug(void *p,char *tp){ZZ_DEB_PRT(p,tp);}\
    void blkAlloc(unsigned ZZint memLim,ZZint bits){ZZ_BLOCK_ALLOC(memLim,bits);}\
    void blkActive(char *blkName,ZZint act){ZZ_BLOCK_ACTIVE(blkName,act);}\
    char *blkUtil(char *blkName,void **hook,ZZint mode){char *name; void *hk;\
    hk=(*hook); ZZ_BLOCK_UTIL(blkName,hk,mode,name); *hook=hk; return(name);}\
    void blkFree(ZZint m);\
    void objClear(void){ZZ_OBJECT_CLEAR();}\
    void mode(ZZint i,ZZint j,ZZint k,ZZint m){ZZ_MODE_SAVE(i,j,k,m);}\
    char *type(ZZint i){char *p; ZZ_TYPE_NAME(i,p); return(p);}\
    void close(const char *fileName){ZZ_CLOSE_BIND(fileName);}\
    char *getID(char *p);\
    char *bind(char *p){char *s; ZZ_BIND_POINTER(p,s); return(s);}\
    void prtProp(FILE *fp,char *tp,char *label,char *val,ZZint num){\
                                 ZZ_PRINT_PROPERTY(fp,tp,label,val,num);} \
    ZZint getNumObjects(){return ZZnumObjects;}\
};\
ZZ_EXTERN ZZFP(ZZH,id) id; 
#define ZZ_HYPER_TYPE(id)  \
class ZZFP(ZZH,id) { \
public: \
    ZZint num(void);\
    void trueType(void **p,ZZint *t){void *ZZtopType(void*,ZZint,ZZint *);\
              *p=ZZtopType(*p,*t,t);}\
    void info(ZZint tp,zzTypeInfo *ip);\
    void virtRange(void *low,void *high){\
        void ZZgetVirtRange(ZZptrIntType*,ZZptrIntType*);\
        ZZgetVirtRange((ZZptrIntType*)low,(ZZptrIntType*)high);}\
    ZZFP(ZZH,id)(){ZZ_GENERAL_EXT();}\
};\
ZZ_EXTERN ZZFP(ZZH,id) id;\
class ZZFN(id,iterator){ \
   ZZint i,ii;\
public:\
   ZZFN(id,iterator)(ZZint tp){start(tp);}\
   ZZFN(id,iterator)(){i=ii=0;}\
   void start(ZZint tp);\
   ZZint operator++(){ZZint k; i++; if(i>=ii)k=(-1); else k=ZZinhList[i].type;\
                                               return(k);}\
   char *name(void){char *p=ZZinhList[i].name;\
       if(!strncmp(p,"ZZ",2))return(p+2); else return(p);}\
};\
class ZZFN(id,pointers){ \
   ZZint i,ii; char *v;\
public:\
   ZZFN(id,pointers)(void *vp,ZZint tp){start(vp,tp);}\
   ZZFN(id,pointers)(){i=ii=0;}\
   void start(void *vp,ZZint tp);\
   void ** operator++(){i++; if(i>=ii)v=NULL; else v=v+sizeof(char *);\
                        return((void **)v);}\
   ZZint nxtType(void){return(ZZnxtType[i]);}\
}

#define ZZ_GET_SELF_ID(ptr,strName) \
{\
char ***ZZp;\
ZZint ZZi,ZZFUN_pOffset();\
    ZZp=(char***)(ptr);\
    ZZi=ZZpOffset((char*)(*ZZp),(char*)ZZselfArr);\
    if(ZZi<0 || ZZi>=ZZnID*(int)sizeof(char *)) (strName)=NULL;\
    else (strName)= **ZZp;\
}

#define ZZ_SET_SELF_ID(strType,ptr,num) \
{\
ZZint ZZi,ZZk;\
    for(ZZi=0;ZZi<ZZnID;ZZi++){\
	if(!strcmp(ZZselfArr[ZZi],strType))break;\
    }\
    if(ZZi>=ZZnID){\
        ZZmsgS(22,strType);\
        ZZerrFLG=ZZerrFLG|040;\
    }\
    else for(ZZk=0;ZZk<num;ZZk++)(ptr)[ZZk].ZZselfID= (char*)(&(ZZselfArr[ZZi]));\
}
#define ZZ_ORG_SINGLE_RING(id,strType) /* ZZ_ORG_SINGLE_RING */
#define ZZ_HYPER_SINGLE_RING(id,link)  \
ZZ_BASIC_SINGLE_RING(id,link,ZZ_EXTERN,id)

#define ZZ_LOCAL_SINGLE_RING(id,link,where)  \
ZZ_BASIC_SINGLE_RING(id,link,static,where :: id)

#define ZZ_BASIC_SINGLE_RING(id,link,scope,where)\
class ZZFP(ZZH,id) { \
public: \
    link * fwd(link *s){link *p; ZZ_FORWARD_SINGLE_RING(id,s,p); return(p);} \
    link * sort(ZZTsortFun cmpF,link *p);\
    link * add(link *s,link *p);\
    link * del(link *s,link *p);\
    link * merge(link *s,link *p);\
};\
scope ZZFP(ZZH,id) id; \
class ZZFN(id,iterator){ \
   link *beg;\
   link *nxt;\
public:\
   ZZFN(id,iterator)(link *p){start(p);}\
   ZZFN(id,iterator)(){beg=nxt=NULL;}\
   void start(link *p){if(p)nxt=where.fwd(p); else nxt=NULL; beg=p;}\
   link* operator++(){link *p;\
      p=nxt; if(p==beg)nxt=beg=NULL; else nxt=where.fwd(p); return(p);}\
}
#define ZZ_ADD_SINGLE_RING(id,entry,pp) \
ZZZ_ADD_SINGLE_RING(id,ZZFP(ZZf,id),entry,pp)

#ifdef ZZnoCheck
#define ZZZ_ADD_SINGLE_RING(id,fwp,entry,pp) \
{\
        if(entry){(pp)->fwp=(entry)->fwp; (entry)->fwp=(pp);}\
        else {(entry)=(pp); (pp)->fwp=(pp);}\
}
#else
#define ZZZ_ADD_SINGLE_RING(id,fwp,entry,pp) \
{\
    if((pp)->fwp){\
        ZZmsgSS(23,ZZ_STRINGIT(id),(char *)(pp));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else {\
        if(entry){(pp)->fwp=(entry)->fwp; (entry)->fwp=(pp);}\
        else {(entry)=(pp); (pp)->fwp=(pp);}\
    }\
}
#endif
#define ZZ_DELETE_SINGLE_RING(id,entry,pp) \
ZZZ_DELETE_SINGLE_RING(ZZFP(ZZf,id),ZZFT(1,id),entry,pp) 

#define ZZZ_DELETE_SINGLE_RING(fwp,strType,entry,pp) \
{\
strType *ZZp,*ZZs;\
    ZZs=(pp); \
    if(ZZs){\
	if(ZZs->fwp){\
            for(ZZp=(entry);ZZp->fwp!=ZZs;ZZp=ZZp->fwp)continue;\
	    if(ZZp==ZZs)(entry)=NULL;\
	    else {\
	        if(ZZs==(entry))(entry)=ZZp;\
	        ZZp->fwp=ZZs->fwp;\
	    };\
	    ZZs->fwp=NULL;\
	}\
    }\
}
#define ZZ_A_TRAVERSE_SINGLE_RING(id,start,pp) \
ZZZ_A_TRAVERSE_SINGLE_RING(id,ZZFP(ZZf,id),ZZFT(1,id),start,pp)

#define ZZZ_A_TRAVERSE_SINGLE_RING(id,fwp,strType,start,pp) \
{strType *ZZt;\
    if(start)(pp)=(start)->fwp; else (pp)=NULL;\
    for(;(pp);(pp)=ZZt){ \
	ZZt=(pp)->fwp; if((pp)==(start))ZZt=NULL;
#define ZZ_SORT_SINGLE_RING(id,sortFun,start) \
ZZZ_SORT_SINGLE_RING(ZZFP(ZZf,id),ZZFT(1,id),sortFun,start) 

#define ZZZ_SORT_SINGLE_RING(fwp,strType,sortFun,start) \
{ char *ZZFUN_rSRfun();\
    (start)=(strType *)ZZrSRfun((char*)(&((start)->fwp)),(char*)(start),sortFun);\
}
#define ZZ_FORWARD_SINGLE_RING(id,pp,next) \
ZZZ_FORWARD_SINGLE_RING(ZZFP(ZZf,id),pp,next)

#define ZZZ_FORWARD_SINGLE_RING(fwd,pp,next) \
{(next)=(pp)->fwd;}
#define ZZ_ORG_DOUBLE_RING(id,strType) /* ZZ_ORG_DOUBLE_RING */
#define ZZ_HYPER_DOUBLE_RING(id,link)  \
ZZ_BASIC_DOUBLE_RING(id,link,ZZ_EXTERN,id)

#define ZZ_LOCAL_DOUBLE_RING(id,link,where)  \
ZZ_BASIC_DOUBLE_RING(id,link,static,where :: id) 

#define ZZ_BASIC_DOUBLE_RING(id,link,scope,where)  \
class ZZFP(ZZH,id) { \
    friend class link;\
    link *start,*nxt;\
public: \
    link * fwd(link *s){link *p; ZZ_FORWARD_DOUBLE_RING(id,s,p); return(p);} \
    link * bwd(link *s){link *p; ZZ_BACKWARD_DOUBLE_RING(id,s,p); return(p);}\
    link * sort(ZZTsortFun cmpF,link *p);\
    link * add(link *s,link *p);\
    link * ins(link *s,link *p);\
    link * del(link *s,link *p);\
    link * merge(link *s,link *p);\
};\
scope ZZFP(ZZH,id) id; \
class ZZFN(id,iterator){ \
   link *beg;\
   link *nxt;\
public:\
   ZZFN(id,iterator)(link *p){start(p);}\
   ZZFN(id,iterator)(){beg=nxt=NULL;}\
   void start(link *p){beg=p; nxt=NULL;}\
   link* operator++(){link *p;\
      if(nxt)p=nxt; else if(beg)p=where.fwd(beg); else p=NULL;\
      if(p==beg)nxt=beg=NULL; else nxt=where.fwd(p); return(p);}\
   link* operator--(){link *p;\
      if(nxt==beg){p=nxt; nxt=beg=NULL;}\
      else {if(nxt)p=nxt; else {p=beg; beg=where.fwd(beg);} nxt=where.bwd(p);};\
      return(p);}\
}
#define ZZ_ADD_DOUBLE_RING(id,entry,pp) \
ZZZ_ADD_DOUBLE_RING(id,ZZFP(ZZf,id),ZZFP(ZZb,id),entry,pp)

#ifdef ZZnoCheck
#define ZZZ_ADD_DOUBLE_RING(id,fwp,bwp,entry,pp) \
{\
        if(entry){(entry)->fwp->bwp=(pp);  (pp)->bwp=(entry);\
                  (pp)->fwp=(entry)->fwp; (entry)->fwp=(pp);}\
        else {(entry)=(pp); (pp)->fwp=(pp)->bwp=(pp);}\
}
#else
#define ZZZ_ADD_DOUBLE_RING(id,fwp,bwp,entry,pp) \
{\
    if((pp)->fwp || (pp)->bwp){\
        ZZmsgSS(23,ZZ_STRINGIT(id),(char *)(pp));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else {\
        if(entry){(entry)->fwp->bwp=(pp);  (pp)->bwp=(entry);\
                  (pp)->fwp=(entry)->fwp; (entry)->fwp=(pp);}\
        else {(entry)=(pp); (pp)->fwp=(pp)->bwp=(pp);}\
    }\
}
#endif
#define ZZ_INSERT_DOUBLE_RING(id,entry,pp) \
ZZZ_INSERT_DOUBLE_RING(id,ZZFP(ZZf,id),ZZFP(ZZb,id),entry,pp)

#define ZZZ_INSERT_DOUBLE_RING(id,fwp,bwp,entry,pp) \
/* organization id is automatically converted into fwp,bwp */ \
{\
    if((pp)->fwp){\
        ZZmsgSS(24,ZZ_STRINGIT(id),(char *)(pp));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else if(entry){(entry)->bwp->fwp=(pp);  (pp)->fwp=(entry);\
              (pp)->bwp=(entry)->bwp; (entry)->bwp=(pp);}\
    else {(entry)=(pp); (pp)->fwp=(pp)->bwp=(pp);}\
}
#define ZZ_DELETE_DOUBLE_RING(id,entry,pp) \
ZZZ_DELETE_DOUBLE_RING(ZZFP(ZZf,id),ZZFP(ZZb,id),entry,pp) 

#define ZZZ_DELETE_DOUBLE_RING(fwp,bwp,entry,pp) \
{\
    if(pp){\
	if((pp)->fwp){\
	    if((pp)->fwp==(pp))(entry)=NULL;\
	    else {\
	        if((pp)==(entry))(entry)=(pp)->bwp;\
	        (pp)->bwp->fwp=(pp)->fwp;\
	        (pp)->fwp->bwp=(pp)->bwp;\
	    }\
	    (pp)->fwp=NULL;\
	    (pp)->bwp=NULL;\
	}\
    }\
}
#define ZZ_A_TRAVERSE_DOUBLE_RING(id,start,pp) \
ZZZ_A_TRAVERSE_DOUBLE_RING(id,ZZFP(ZZf,id),ZZFT(1,id),start,pp)

#define ZZZ_A_TRAVERSE_DOUBLE_RING(id,fwp,strType,start,pp) \
{strType *ZZt;\
    if(start)(pp)=(start)->fwp; else (pp)=NULL;\
    for(;(pp);(pp)=ZZt){ \
	ZZt=(pp)->fwp; if((pp)==(start))ZZt=NULL;
#define ZZ_A_RETRACE_DOUBLE_RING(id,start,pp) \
ZZZ_A_RETRACE_DOUBLE_RING(id,ZZFP(ZZb,id),ZZFT(1,id),start,pp)

#define ZZZ_A_RETRACE_DOUBLE_RING(id,bwp,strType,start,pp) \
{strType *ZZt;\
    for((pp)=(start);(pp);(pp)=ZZt){ \
	ZZt=(pp)->bwp; if(ZZt==(start))ZZt=NULL;
#define ZZ_SORT_DOUBLE_RING(id,sortFun,start) \
ZZZ_SORT_DOUBLE_RING(ZZFP(ZZf,id),ZZFP(ZZb,id),ZZFT(1,id),sortFun,start) 

#define ZZZ_SORT_DOUBLE_RING(fwp,bwp,strType,sortFun,start) \
{\
    char *ZZFUN_rSRfun();\
    (start)=(strType *)ZZrSRfun((char*)(&((start)->fwp)),(char*)(start),sortFun);\
    ZZ_UPD_DOUBLE(strType,fwp,bwp,start);\
}
#define ZZ_FORWARD_DOUBLE_RING(id,pp,next) \
ZZZ_FORWARD_DOUBLE_RING(ZZFP(ZZf,id),pp,next)

#define ZZZ_FORWARD_DOUBLE_RING(fwd,pp,next) \
{(next)=(pp)->fwd;}
#define ZZ_BACKWARD_DOUBLE_RING(id,pp,next) \
ZZZ_BACKWARD_DOUBLE_RING(ZZFP(ZZb,id),pp,next)

#define ZZZ_BACKWARD_DOUBLE_RING(bwd,pp,next) \
{(next)=(pp)->bwd;}

#define ZZ_STRING_ALLOC(str,ptr) \
{void *ZZFUN_galloc();\
(ptr)=(char*)ZZgalloc((int)strlen(str)+1);\
if(ptr)strcpy(ptr,str);\
else {ZZmsgS(7,"ZZ_STRING_ALLOC()"); ZZerrFLG=ZZerrFLG|01;}\
}

#define ZZ_STRING_FREE(ptr) \
{ int ZZFUN_gfree(); if(ptr)ZZgfree(ptr); }
#ifdef ZZ_SIMPLE
#define ZZ_PLAIN_ALLOC(strType,num,ptr) \
{ ZZvoidS *ZZFUN_massAlloc(); ZZFN(ZZS,strType) \
  (ptr)= (strType *)ZZmassAlloc(((size_t)num)*sizeof(strType),1); }
#else
#define ZZ_PLAIN_ALLOC(strType,num,ptr) \
{char *ZZFUN_allo();\
    ZZFN(ZZS,strType) \
    (ptr)= (strType *)ZZallo(ZZstrList,(char **)ZZselfArr,ZZFP(ZZJ,strType),\
       ZZ_STRINGIT(strType),ZZFP(ZZI,strType),num,(int)sizeof(strType),1);\
}
#endif
#define ZZ_PLAIN_NEW(strType,sz,ptr) \
{ static strType s; char *ZZFUN_allo(); void ZZFUN_bitCopy();\
    ZZFN(ZZS,strType) \
    (ptr)= (strType *)ZZallo(ZZstrList,(char **)ZZselfArr,ZZFP(ZZJ,strType),\
        ZZ_STRINGIT(strType),ZZFP(ZZI,strType),sz,(int)sizeof(strType),0);\
    if(ptr)ZZbitCopy((int)sizeof(strType),(char*)(&s),(char*)(ptr));\
}

#ifdef ZZ_ANSI
#ifdef ZZcplus
#define ZZ_BLOCK_ALLOC(blkSize,bits) \
{ ZZvoidS *ZZFUN_massAlloc(); int ZZi;\
    ZZ_GENERAL_EXT();\
    ZZi=bits;\
    if(ZZmemSwitch==2 && ZZmemEnd){ZZmsg(60); ZZerror=ZZerror|01;}\
    else if(ZZi==0){\
      if(blkSize==0){ ZZerror=ZZerror|01; ZZmsg(70); exit(1);} \
      ZZmemStart=ZZmemPool=(char *)ZZmassAlloc((size_t)blkSize,(ZZint)ZZcallocFlg);\
      if(ZZmemStart){ ZZmemSwitch=1; ZZmemEnd=ZZmemStart+(blkSize);}\
      else { ZZerror=ZZerror|01; ZZmsgD(24,blkSize);}\
    }\
    else {ZZmemSwitch=2; ZZioSwitch=1; ZZmemStart=ZZintToPtr(bits); \
          ZZmemEnd=(char *)NULL; ZZmemPool=ZZintToPtr(blkSize);}\
          /* temp.use: ZZmemStart pass to ZZnewBit, ZZmemPool to startBit() */\
}
#else // not C++
#define ZZ_BLOCK_ALLOC(blkSize,bits) \
{ZZvoidS *ZZFUN_massAlloc(); int ZZi;\
    ZZ_GENERAL_EXT();\
    ZZi=bits;\
    if(ZZmemSwitch==2 && ZZmemEnd){ZZmsg(60); ZZerror=ZZerror|01;}\
    else if(ZZi==0){\
        if(blkSize==0){ZZerror=ZZerror|01;  ZZmsg(70); exit(1);} \
        ZZmemStart=ZZmemPool=(char *)ZZmassAlloc((size_t)blkSize,(ZZint)ZZcallocFlg);\
        if(ZZmemStart){ ZZmemSwitch=1; ZZmemEnd=ZZmemStart+(blkSize);}\
        else { ZZerror=ZZerror|01; ZZmsgD(24,blkSize);}\
    }\
    else {ZZmemSwitch=2; ZZioSwitch=1; ZZmemStart=ZZpowerOf2(bits);\
          ZZmemEnd=(char *)NULL; ZZmemPool=ZZintToPtr(blkSize);}\
}
#endif
#else // not ANSII
#define ZZ_BLOCK_ALLOC(blkSize,bits) \
{ZZvoidS *ZZFUN_massAlloc(); ZZint ZZi;\
    ZZ_GENERAL_EXT();\
    ZZi=bits;\
    if(ZZmemSwitch==2 && ZZmemEnd){ZZmsg(60); ZZerror=ZZerror|01;}\
    else if(ZZi==0){\
        if(blkSize==0){ ZZerror=ZZerror|01; ZZmsg(70); exit(1);} \
        ZZmemStart=ZZmemPool=(char *)ZZmassAlloc((size_t)blkSize,(ZZint)ZZcallocFlg);\
        if(ZZmemStart){ ZZmemSwitch=1; ZZmemEnd=ZZmemStart+(blkSize);}\
        else { ZZerror=ZZerror|01; ZZmsgD(24,blkSize);}\
    }\
    else {ZZmemSwitch=2; ZZmemSwitch=1;  ZZmemStart=ZZpowerOf2(bits);\
          ZZmemEnd=(char *)NULL; ZZmemPool=ZZintToPtr(blkSize);}\
    if(ZZmemSwitch==1){ZZmsg(78); exit(1);}\
}
#endif

#define ZZ_BLOCK_ACTIVE(blkName,active) \
{void ZZFUN_blkActive(); ZZmemSwitch=2; ZZblkActive(blkName,active);}

#define ZZ_BLOCK_UTIL(blkName,hook,mode,name) \
{char* ZZFUN_blkUtil(); name=ZZblkUtil(blkName,&hook,mode);}

#ifdef ZZ_ANSI
#ifdef ZZcplus

#ifdef SUN3_0
#define ZZ_BLOCK_FREE(mode) \
{ ZZint ZZm; void ZZFUN_blastClear();\
  ZZm=mode;\
  if(ZZm==0){\
      if(ZZmemSwitch==2)ZZblastClear();\
      else if(ZZmemStart) {\
	  delete ZZmemStart;\
	  0; /* This hack is necessary due to a Sun 3.0.1 C++ compiler bug */\
      }\
      ZZmemStart=NULL;\
      ZZmemSwitch=0;\
  }\
  else ZZmemSwitch=ZZm-1;\
}
#else
#define ZZ_BLOCK_FREE(mode) \
{ int ZZm; void ZZFUN_blastClear();\
  ZZm=mode;\
  if(ZZm==0){\
      if(ZZmemSwitch==2)ZZblastClear();\
      else if(ZZmemStart) delete ZZmemStart;\
      ZZmemStart=NULL;\
      ZZmemSwitch=0;\
  }\
  else ZZmemSwitch=ZZm-1;\
}
#endif

#else
#define ZZ_BLOCK_FREE(mode) \
{ int ZZm; void ZZFUN_blastClear();\
  void free(void *p);\
  ZZm=mode;\
  if(ZZm==0){\
      if(ZZmemSwitch==2)ZZblastClear();\
      else if(ZZmemStart)free(ZZmemStart);\
      ZZmemStart=NULL;\
      ZZmemSwitch=0;\
  }\
  else ZZmemSwitch=ZZm-1;\
}
#endif
#else
#define ZZ_BLOCK_FREE(mode) \
{ int ZZm; void ZZFUN_blastClear();\
  void free();\
  ZZm=mode;\
  if(ZZm==0){\
      if(ZZmemSwitch==2)ZZblastClear();\
      else if(ZZmemStart)free(ZZmemStart);\
      ZZmemStart=NULL;\
      ZZmemSwitch=0;\
  }\
  else ZZmemSwitch=ZZm-1;\
}
#endif

#define ZZ_CHECK_FREE(strType,num,ptr) \
{\
strType *P; ZZint ZZFUN_deal();\
 ZZFN(ZZS,strType) \
 P=(ptr);\
 ZZdeal((char *)P,ZZstrList,ZZ_STRINGIT(strType),num,(ZZint)sizeof(strType),1);\
}
#define ZZ_CHECK(strType) ZZ_CHECK_FREE(strType,1,this)


#define ZZ_PLAIN_FREE(strType,num,ptr) \
{\
 strType *ZZp; ZZint ZZFUN_deal();\
 ZZFN(ZZS,strType) \
 ZZp=(ptr);\
 if(ZZmemSwitch!=2) ZZdeal( \
  (char *)ZZp,ZZstrList,ZZ_STRINGIT(strType),num,(int)sizeof(strType),0);\
}
#define ZZ_OBJECT_ALLOC(strType,ptr) \
{char *ZZFUN_allo();\
    (ptr)= (strType *)ZZallo(ZZstrList,(char **)ZZselfArr,ZZFP(ZZJ,strType),\
        ZZ_STRINGIT(strType),ZZFP(ZZI,strType),0,(int)sizeof(strType),2);\
}
#define ZZ_OBJECT_NEW(strType,ptr) \
{ static strType s; char *ZZFUN_allo(); void ZZFUN_bitCopy(); ZZint mode;\
    if(ZZmemSwitch==2)mode=2; else mode=0; \
    (ptr)= (strType *)ZZallo(ZZstrList,(char **)ZZselfArr,ZZFP(ZZJ,strType),\
       ZZ_STRINGIT(strType),ZZFP(ZZI,strType),0,(ZZint)sizeof(strType),mode);\
    if(ptr){ \
        strType *pptr=ptr; /* pptr used inside ZZSS... */\
        /* next line is generated in zzincl.h, and it sets for this type:  */\
        /* ZZstrList[type].start ... offset of ZZ_EXT inside the object,   */\
        /* ZZstrList[type].size  ... overall size of the object.           */\
        /* which are preset as 0 in ZZstrList[] defined in the beginning   */\
        /* of zzincl.h. The definition of struct ZZstrLST is in lib/bind.h */\
        /* This line was introduced in Ver.9.2, where methods newObj() and */\
        /* are automatically under every ZZ_EXT. ZZFN(ZZSS,p) is expansion */\
        /* of ZZFN(ZZS,p), and is (probably) needed in ony in some memory  */\
        /* memory management modes (also introducedin Ver.9.2              */\
        /*    Commented when debugging later on by Jiri Feb.20, 2014       */\
        ZZFN(ZZSS,strType) (((strType*)ptr));  \
        if(ZZmemSwitch!=2){ \
	      ZZbitCopy((int)sizeof(strType),(char*)(&s),(char*)(ptr));\
        } \
    } \
}

#define ZZ_OBJECT_FREE(strType,ptr) \
{\
strType *ZZp; ZZint ZZFUN_deal();\
 ZZp=(ptr);\
 ZZdeal((char *)ZZp,ZZstrList,ZZ_STRINGIT(strType),0,(int)sizeof(strType),0);\
}

#define ZZ_OBJECT_CLEAR() \
{ char *ZZp; void ZZFUN_objMem(); ZZobjMem(2,&ZZp,0,ZZstrList); }
#define ZZ_ADD_SINGLE_TRIANGLE(id,par,pp) \
ZZZ_ADD_SINGLE_TRIANGLE\
(id,ZZFP(ZZp,id),ZZFP(ZZs,id),ZZFP(ZZc,id),par,pp)

#ifdef ZZnoCheck
#define ZZZ_ADD_SINGLE_TRIANGLE(id,parent,sibling,child,par,pp) \
{\
        if((par)->child==NULL){\
            (par)->child=(pp);\
            (pp)->parent=(par);\
            (pp)->sibling=(pp);\
        }\
	else {\
            (pp)->sibling=((par)->child)->sibling;\
            ((par)->child)->sibling=(pp);\
            (pp)->parent=(par);\
        }\
}
#else
#define ZZZ_ADD_SINGLE_TRIANGLE(id,parent,sibling,child,par,pp) \
{\
    if((pp)->parent!=NULL || (pp)->sibling!=NULL){\
        ZZmsgSS(23,ZZ_STRINGIT(id),(char *)(pp));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else {\
        if((par)->child==NULL){\
            (par)->child=(pp);\
            (pp)->parent=(par);\
            (pp)->sibling=(pp);\
        }\
	else {\
            (pp)->sibling=((par)->child)->sibling;\
            ((par)->child)->sibling=(pp);\
            (pp)->parent=(par);\
        }\
    }\
}
#endif
#define ZZ_FORWARD_SINGLE_TRIANGLE(id,pp,fwd) \
ZZZ_FORWARD_SINGLE_TRIANGLE(ZZFP(ZZs,id),pp,fwd)

#define ZZZ_FORWARD_SINGLE_TRIANGLE(sibling,pp,fwd) {(fwd)=(pp)->sibling;}
#define ZZ_CHILD_SINGLE_TRIANGLE(id,pp,chi) \
ZZZ_CHILD_SINGLE_TRIANGLE(ZZFP(ZZc,id),ZZFP(ZZs,id),pp,chi)

#define ZZZ_CHILD_SINGLE_TRIANGLE(child,sibling,pp,chi) \
{if((pp)->child)(chi)=(pp)->child->sibling; else (chi)=NULL;}
#ifndef ZZ_ANSI
#define ZZF_ADD_SINGLE_TRIANGLE(id,par,pp) \
{ZZFT(1,id) *ZZFP(ZZF_ADD_SINGLE_TRIANGLE,id)();\
 (par)=ZZFP(ZZF_ADD_SINGLE_TRIANGLE,id)(par,pp);}
#endif
#ifdef ZZ_ANSI
#define ZZF_ADD_SINGLE_TRIANGLE(id,par,pp) \
{ZZFT(1,id) *ZZFP(ZZF_ADD_SINGLE_TRIANGLE,id)(ZZFT(1,id) *e,ZZFT(2,id) *p);\
 (par)=ZZFP(ZZF_ADD_SINGLE_TRIANGLE,id)(par,pp);}
#endif

#define ZZ_DELETE_SINGLE_TRIANGLE(id,entry,pp) \
ZZZ_DELETE_SINGLE_TRIANGLE\
(id,ZZFT(1,id),ZZFT(2,id),ZZFP(ZZp,id),ZZFP(ZZs,id),ZZFP(ZZc,id),entry,pp)

#define ZZZ_DELETE_SINGLE_TRIANGLE(id,sTop,sBot,parent,sibling,child,entry,pp) \
{sBot *ZZv,*ZZc; sTop *ZZp;\
    if((pp) && (pp)->parent){\
        ZZp=(pp)->parent; ZZc=ZZp->child; if(!ZZc)ZZc=(pp); \
        if((pp)->sibling==(pp))ZZp->child=NULL;\
        else { \
            for(ZZv=ZZc; ZZv->sibling!=(pp); ZZv=ZZv->sibling)continue;\
            if(ZZp->child==(pp))ZZp->child=ZZv;\
            ZZv->sibling=(pp)->sibling;\
        } \
        (pp)->sibling=NULL; (pp)->parent=NULL;\
    }\
}
#define ZZ_A_TRAVERSE_SINGLE_TRIANGLE(id,par,pp) \
ZZZ_A_TRAVERSE_SINGLE_TRIANGLE(ZZFT(2,id),ZZFP(ZZs,id),ZZFP(ZZc,id),par,pp)

#define ZZZ_A_TRAVERSE_SINGLE_TRIANGLE(strBot,sibling,child,par,pp) \
{strBot *ZZt,*ZZc;\
if(par)ZZc=(par)->child; else ZZc=NULL;\
if(ZZc)(pp)=ZZc->sibling; else (pp)=NULL;\
for(;pp;(pp)=ZZt){\
    if((pp)==ZZc)ZZt=NULL; else ZZt=(pp)->sibling;
#define ZZ_PARENT_SINGLE_TRIANGLE(id,pp,par) \
ZZZ_PARENT_SINGLE_TRIANGLE(ZZFP(ZZp,id),pp,par)

#define ZZZ_PARENT_SINGLE_TRIANGLE(parent,pp,par) {(par)=(pp)->parent;}
#define ZZ_SORT_SINGLE_TRIANGLE(id,sortFun,par) \
ZZZ_SORT_SINGLE_TRIANGLE(ZZFP(ZZs,id),ZZFP(ZZc,id),ZZFT(2,id),sortFun,par) 

#define ZZZ_SORT_SINGLE_TRIANGLE(fwp,child,str2Type,sortFun,par) \
{str2Type *ZZstart;\
    char *ZZFUN_rSRfun();\
    if(par){\
        ZZstart=(par)->child;\
        if(ZZstart){\
            (par)->child=(str2Type *)\
                ZZrSRfun((char*)(&(ZZstart->fwp)),(char*)(ZZstart),sortFun);\
        }\
    }\
}
#define ZZ_SET_SINGLE_TRIANGLE(id,par,pp) \
ZZZ_SET_SINGLE_TRIANGLE(id,ZZFP(ZZp,id),ZZFP(ZZc,id),pp)

#define ZZZ_SET_SINGLE_TRIANGLE(id,parent,child,pp) {\
    if((pp)->parent) (pp)->parent->child=(pp); }
#define ZZ_ORG_SINGLE_TRIANGLE(id,strType1,strType2) \
/* ZZ_ORG_SINGLE_TRIANGLE */

#define ZZ_ORG_SINGLE_AGGREGATE(id,strType1,strType2) \
/* ZZ_ORG_SINGLE_AGGREGATE */
#define ZZ_HYPER_SINGLE_TRIANGLE(id,pType,cType)  \
ZZ_BASIC_SINGLE_TRIANGLE(id,pType,cType,ZZ_EXTERN,id)

#define ZZ_HYPER_SINGLE_AGGREGATE(id,pType,cType)  \
ZZ_BASIC_SINGLE_TRIANGLE(id,pType,cType,ZZ_EXTERN,id)

#define ZZ_LOCAL_SINGLE_TRIANGLE(id,pType,cType,where)  \
ZZ_BASIC_SINGLE_TRIANGLE(id,pType,cType,static,where :: id)

#define ZZ_LOCAL_SINGLE_AGGREGATE(id,pType,cType,where)  \
ZZ_BASIC_SINGLE_TRIANGLE(id,pType,cType,static,where :: id)

#define ZZ_BASIC_SINGLE_TRIANGLE(id,pType,cType,scope,where)  \
class ZZFP(ZZH,id) { \
  friend class pType;\
  friend class cType;\
public: \
  pType *par(cType *s){pType *p;\
                  ZZ_PARENT_SINGLE_TRIANGLE(id,s,p); return(p);}\
  cType *child(pType *s){cType *p;\
                   ZZ_CHILD_SINGLE_TRIANGLE(id,s,p); return(p);}\
  cType *chld(pType *s){return(s->ZZFP(ZZc,id));}\
  cType * fwd(cType *s){cType *p;\
                 ZZ_FORWARD_SINGLE_TRIANGLE(id,s,p); return(p);}\
  void set(cType *t){ZZ_SET_SINGLE_TRIANGLE(id,NULL,t);}\
  void add(pType *s,cType *p);\
  void del(cType *p);\
  void merge(cType *s,cType *t,pType *p);\
  void sort(ZZTsortFun cmpF,pType *p);\
  void switchParents(pType *p1,pType *p2); \
};\
scope ZZFP(ZZH,id) id; \
class ZZFN(id,iterator){ \
   cType *beg;\
   cType *nxt;\
public:\
   ZZFN(id,iterator)(pType *p){start(p);}\
   ZZFN(id,iterator)(){beg=nxt=NULL;}\
   void start(pType *p){if(p){beg=where.chld(p);\
            if(beg)nxt=where.fwd(beg); else nxt=NULL;}\
                        else beg=nxt=NULL;} \
   cType* operator++(){cType *p;\
      p=nxt; if(p==beg)nxt=beg=NULL; else nxt=where.fwd(p);\
                                                return(p);}\
}


#define ZZ_INPUT_NAMES(file,arr,num) \
{\
    void ZZFUN_getNames();\
    ZZgetNames(file,(char **)arr,num);\
}

#define ZZ_SET_PROPERTY(propType,ptr,name,arr,num) \
{\
ZZint ZZi, ZZFUN_propSet();\
ZZpropSIZE(propType,ZZi);\
ZZpropSet(&((ptr)->ZZprop),ZZ_STRINGIT(propType),name,(char *)(arr),(num)*ZZi);\
}

#define ZZ_GET_PROPERTY(pType,ptr,name,val,num) \
{\
ZZint ZZi,ZZFUN_propGet(),ZZFUN_cnvProp();\
char ZZc;\
    (void)ZZpropGet(&((ptr)->ZZprop),name,&ZZc,(char **)(&(val)),&ZZi);\
    (void)ZZcnvProp(&ZZc,ZZi,&pType,&num);\
}

#define ZZ_DELETE_PROPERTY(ptr,name) \
{\
struct ZZproperty *ZZp,*ZZr; ZZint ZZFUN_propDelete();\
    for(ZZp=(ptr)->ZZprop;ZZp;ZZp=ZZr){\
        if(ZZp->next==((ptr)->ZZprop))ZZr=NULL; else ZZr=ZZp->next;\
	if(!strcmp(name,&(ZZp->codeName[1])))break;\
    }\
    if(ZZp)ZZpropDelete(ZZp,&((ptr)->ZZprop));\
}

#define ZZ_PRINT_PROPERTY(file,tp,name,val,num) \
{ int ZZFUN_wrtProperty();\
  ZZwrtProperty(file,tp,name,(char *)val,num);\
}

#define ZZ_A_TRAVERSE_PROPERTY(pType,ptr,name,val,num) \
{\
ZZint ZZs,ZZFUN_prSize();\
ZZint ZZFUN_cnvProp();\
char ZZC;\
struct ZZproperty *ZZP,*ZZR;\
    if(ptr)ZZP=(ptr)->ZZprop; else ZZP=NULL;\
    for(;ZZP;ZZP=ZZR){\
	if(ZZP->next==(ptr)->ZZprop)ZZR=NULL; else ZZR=ZZP->next;\
	(name)= &(ZZP->codeName[1]);\
	ZZC=ZZP->codeName[0];\
        ZZs=ZZprSize(ZZP);\
	if(ZZC=='i' || ZZC=='f' || ZZC=='c' || ZZC=='s'){\
	    (val)=ZZP->propType.cProp;\
	}\
	else {\
	    (val)=ZZP->propType.arrayProp->array;\
	};\
        (val)=(val);\
	(void)ZZcnvProp(&ZZC,ZZs,&(pType),&(num));

#define ZZ_SET_TIME_STAMP(ptr) \
{void ZZFUN_stTime(); ZZstTime((ptr)->ZZtimeStamp);}

#define ZZ_GET_TIME_STAMP(ptr,time) \
{void ZZFUN_gtTime(); ZZgtTime((ptr)->ZZtimeStamp,time); }

#define ZZ_CMP_TIME_STAMP(p1,p2,i) \
{\
ZZint ZZk; unsigned ZZint ZZj1,ZZj2;\
(i)=0;\
for(ZZk=0;ZZk<ZZtSize;ZZk++){\
    ZZj1=(p1)->ZZtimeStamp[ZZk];\
    ZZj2=(p2)->ZZtimeStamp[ZZk];\
    if(ZZj1==ZZj2)continue;\
    if(ZZj1<ZZj2){i= -1; break;}\
    else     {i=  1; break;}\
}\
}

#define ZZ_A_END \
}}

#define ZZ_A_BREAK \
{break;}

#define ZZ_INITIAL(strType,mode,num,pp) \
{void ZZFUN_ini(); strType *ZZp; ZZint ZZi;\
    ZZi=ZZFP(ZZI,strType); \
    if(ZZstrList[ZZi].size==0)ZZFN(ZZS,strType); \
    ZZp=(pp);\
    if(mode || ZZstrList[ZZi].numPtr>0) \
        ZZini((char*)ZZp,ZZstrList,ZZselfArr,ZZFP(ZZJ,strType),mode,\
             ZZi,num,(int)sizeof(strType));\
}
#define ZZ_INIT(strType) ZZ_INITIAL(strType,0,1,this)

#define ZZ_ORG_PROPERTY(strType) /* ZZ_ORG_PROPERTY */
#define ZZ_HYPER_PROPERTY(type) \
class ZZFN(type,propIterator){ \
   ZZproperty *beg;\
   ZZproperty *nxt;\
public:\
   ZZFN(type,propIterator)(void){beg=nxt=NULL;}\
   ZZFN(type,propIterator)(type *p){start(p);}\
   void start(type *p){if(p)beg=nxt=p->ZZprop;else beg=nxt=NULL;}\
   char *next(char **label,char **tp,ZZint *num);\
}
#define ZZEXTPROPERTY(type) \
    friend class ZZFN(type,propIterator);\
    void setProp(char *tp,char *label,void *val,ZZint num);\
    char *getProp(char *label,char **tp,ZZint *num);\
    void delProp(char *label);

#define ZZ_ORG_TIME_STAMP(strType) /* ZZ_ORG_TIME_STAMP */
#ifdef VMS
#define ZZ_HYPER_TIME_STAMP(type) unsigned char ZZTIMESTAMP##type
#else
#define ZZ_HYPER_TIME_STAMP(type) /* ZZ_HYPER_TIME_STAMP */
#endif
#define ZZEXTTIME_STAMP(type) \
    void getTime(unsigned char ts[6]){ZZ_GET_TIME_STAMP(this,ts);}\
    void setTime(void){ZZ_SET_TIME_STAMP(this);}\
    ZZint cmpTime(type *p);
#define ZZ_ORG_SELF_ID(strType) /* ZZ_ORG_SELF_ID */
#ifdef VMS
#define ZZ_HYPER_SELF_ID(type) unsigned char ZZSELF##type 
#else
#define ZZ_HYPER_SELF_ID(type) /* ZZ_HYPER_SELF_ID */
#endif
#define ZZEXTSELF_ID(type) \
    void setSelf(char *tp,ZZint n);

#define ZZ_OBJECT_SAVE(strType,fileName,pp,num) \
{\
    char *ZZs; ZZint ZZt,ZZn;\
    void ZZFUN_writeASCII();\
    void ZZFUN_writeBind();\
    strType *ZZp;\
    ZZ_GENERAL_EXT(); \
    ZZp=(pp);\
    ZZs=ZZ_STRINGIT(strType);\
    ZZt=ZZFP(ZZI,strType);\
    if(ZZbindASCII){\
      if(!strcmp(ZZs,"char")){\
          ZZn=num;\
          if(ZZn)ZZt= -8;\
          ZZwriteASCII(1,ZZt,fileName,(char*)ZZp,num,0);\
      }\
      else ZZwriteASCII((ZZint)sizeof(strType),ZZt,fileName,(char*)ZZp,\
                                                num,0);\
    }\
    else {\
      if(!strcmp(ZZs,"char"))ZZwriteBind(1,ZZt,fileName,(char *)ZZp,num,0);\
      else ZZwriteBind((ZZint)sizeof(strType),ZZt,fileName,(char*)ZZp,num,0);\
    }\
}
#define ZZ_KEY_SAVE(strType,fileName,pp) \
{\
    char *ZZs; ZZint ZZt;\
    void ZZFUN_writeASCII();\
    void ZZFUN_writeBind();\
    strType *ZZp;\
    ZZ_GENERAL_EXT(); \
    ZZp=(pp);\
    ZZs=ZZ_STRINGIT(strType);\
    ZZt=ZZFP(ZZI,strType);\
    if(ZZbindASCII){\
      if(!strcmp(ZZs,"char")){\
          ZZwriteASCII(1,ZZt,fileName,(char*)ZZp,1,1);\
      }\
      else ZZwriteASCII((ZZint)sizeof(strType),ZZt,fileName,(char*)ZZp,\
                                                 1,1);\
    }\
    else {\
      if(!strcmp(ZZs,"char"))ZZwriteBind(1,ZZt,fileName,(char *)ZZp,1,1);\
      else ZZwriteBind((int)sizeof(strType),ZZt,fileName,(char*)ZZp,1,1);\
    }\
}
#define ZZ_STORE(strType,fileName) ZZ_OBJECT_SAVE(strType,fileName,this,1)


#define ZZ_CLOSE_BIND(fileName) {\
void ZZFUN_closeBind(); ZZcloseBind(fileName);}

#define ZZ_OPEN(fileName,n,pp,type) \
{ZZint ZZFUN_readBind(),ZZi;\
 void ZZFUN_blastOpen();\
ZZ_GENERAL_EXT(); \
if(ZZerrFLG){ZZmsgD(32,ZZerrFLG); ZZerrFLG=0;}\
if(ZZioSwitch==1 && ZZmemSwitch==2){ZZi=0; ZZblastOpen(fileName,n,(char **)(pp));}\
else ZZi=ZZreadBind(fileName,n,(char **)(pp),type,ZZnID);\
if(ZZi==1)ZZerrFLG=ZZerrFLG|01;\
else if(ZZi==2)ZZerrFLG=ZZerrFLG|0100;\
else if(ZZi==4)ZZerrFLG=ZZerrFLG|020;\
}
#define ZZ_ORG_GENERAL_LINK(id,strType) /* ZZ_ORG_GENERAL_LINK */
#define ZZ_HYPER_GENERAL_LINK(id,sTp)  \
ZZ_BASIC_GENERAL_LINK(id,ZZFP(ZZg,id),sTp,ZZ_EXTERN,id)

#define ZZ_LOCAL_GENERAL_LINK(id,sTp,where)  \
ZZ_BASIC_GENERAL_LINK(id,ZZFP(ZZg,id),sTp,static,where :: id)

#define ZZ_BASIC_GENERAL_LINK(id,nxt,sTp,scope,where)  \
class ZZFP(ZZH,id) { \
public: \
    void * fwd(sTp *s){return((void *)(s->nxt));} \
    void add(sTp *s,void *t){ZZ_ADD_GENERAL_LINK(id,s,t); }\
    void * del(sTp *s){void *t=(void *)(s->nxt); s->nxt=NULL; return(t);}\
};\
scope ZZFP(ZZH,id) id
#define ZZ_ORG_SINGLE_LINK(id,strType1,strType2) /* ZZ_ORG_SINGLE_LINK */
#define ZZ_HYPER_SINGLE_LINK(id,sTp,tTp)  \
ZZ_BASIC_SINGLE_LINK(id,sTp,tTp,ZZ_EXTERN,id) 

#define ZZ_LOCAL_SINGLE_LINK(id,sTp,tTp,where)  \
ZZ_BASIC_SINGLE_LINK(id,sTp,tTp,static,where :: id) 

#define ZZ_BASIC_SINGLE_LINK(id,sTp,tTp,scope,where)  \
class ZZFP(ZZH,id) { \
public: \
    tTp * fwd(sTp *s){tTp *t; ZZ_FORWARD_SINGLE_LINK(id,s,t); return(t);} \
    void add(sTp *s,tTp *t){ZZ_ADD_SINGLE_LINK(id,s,t); }\
    tTp * del(sTp *s){tTp *t;ZZ_DELETE_SINGLE_LINK(id,s,t); return(t);}\
};\
scope ZZFP(ZZH,id) id
#define ZZ_ORG_DOUBLE_LINK(id,strType1,strType2) /* ZZ_ORG_DOUBLE_LINK */
#define ZZ_HYPER_DOUBLE_LINK(id,sTp,tTp)  \
ZZ_BASIC_DOUBLE_LINK(id,sTp,tTp,ZZ_EXTERN,id) 

#define ZZ_LOCAL_DOUBLE_LINK(id,sTp,tTp,where)  \
ZZ_BASIC_DOUBLE_LINK(id,sTp,tTp,static,where :: id) 

#define ZZ_BASIC_DOUBLE_LINK(id,sTp,tTp,scope,where)  \
class ZZFP(ZZH,id) { \
public: \
    tTp * fwd(sTp *s){tTp *t; ZZ_FORWARD_DOUBLE_LINK(id,s,t); return(t);} \
    sTp * bwd(tTp *t){sTp *s; ZZ_BACKWARD_DOUBLE_LINK(id,t,s); return(s);} \
    void add(sTp *s,tTp *t){ZZ_ADD_DOUBLE_LINK(id,s,t); }\
    tTp * del(sTp *s){tTp *t;ZZ_DELETE_DOUBLE_LINK(id,s,t); return(t);}\
};\
scope ZZFP(ZZH,id) id
#define ZZ_ADD_GENERAL_LINK(id,from,to) \
ZZZ_ADD_GENERAL_LINK(id,ZZFP(ZZg,id),from,to)

#ifdef ZZnoCheck
#define ZZZ_ADD_GENERAL_LINK(id,ptr,from,to) \
{ (from)->ptr=(char*)(to); }
#else
#define ZZZ_ADD_GENERAL_LINK(id,ptr,from,to) \
{if((from)->ptr){\
        ZZmsgSS(23,ZZ_STRINGIT(id),(char *)(from));\
        ZZerrFLG=ZZerrFLG|010;\
 }\
 else (from)->ptr=(char*)(to);\
}
#endif
#define ZZ_PTR_SINGLE_LINK(id) \
ZZFP(ZZf,id)
#define ZZ_ADD_SINGLE_LINK(id,from,to) \
ZZZ_ADD_SINGLE_LINK(id,ZZFP(ZZf,id),from,to)

#ifdef ZZnoCheck
#define ZZZ_ADD_SINGLE_LINK(id,ptr,from,to) {(from)->ptr=(to);}
#else
#define ZZZ_ADD_SINGLE_LINK(id,ptr,from,to) \
{if((from)->ptr){\
        ZZmsgSS(23,ZZ_STRINGIT(id),(char *)(from));\
        ZZerrFLG=ZZerrFLG|010;\
 }\
 else (from)->ptr=(to);\
}
#endif
#define ZZ_ADD_DOUBLE_LINK(id,from,to) \
ZZZ_ADD_DOUBLE_LINK(id,ZZFP(ZZf,id),ZZFP(ZZb,id),from,to)

#ifdef ZZnoCheck
#define ZZZ_ADD_DOUBLE_LINK(id,fwp,bwp,from,to) \
{(from)->fwp=(to); (to)->bwp=(from);} 
#else
#define ZZZ_ADD_DOUBLE_LINK(id,fwp,bwp,from,to) \
{if((from)->fwp || (to)->bwp){\
        ZZmsgSS(23,ZZ_STRINGIT(id),(char *)(from));\
        ZZerrFLG=ZZerrFLG|010;\
 }\
 else {(from)->fwp=(to); (to)->bwp=(from);}\
}
#endif
#define ZZ_FORWARD_GENERAL_LINK(id,given,ret) \
ZZZ_FORWARD_GENERAL_LINK(ZZFP(ZZg,id),given,ret)

#ifdef ZZcplus
#define ZZZ_FORWARD_GENERAL_LINK(ptr,given,ret) \
{char **ZZp=(char **)(&(ret)); *ZZp=(given)->ptr;}
#else
#define ZZZ_FORWARD_GENERAL_LINK(ptr,given,ret) (ret)=(void *)((given)->ptr);
#endif
#define ZZ_FORWARD_SINGLE_LINK(id,given,ret) \
ZZZ_FORWARD_SINGLE_LINK(ZZFP(ZZf,id),given,ret)

#define ZZZ_FORWARD_SINGLE_LINK(fwd,given,ret) {(ret)=(given)->fwd;}
#define ZZ_FORWARD_DOUBLE_LINK(id,given,ret) \
ZZZ_FORWARD_DOUBLE_LINK(ZZFP(ZZf,id),given,ret)

#define ZZZ_FORWARD_DOUBLE_LINK(fwp,given,ret) (ret)=(given)->fwp;
#define ZZ_BACKWARD_DOUBLE_LINK(id,given,ret) \
ZZZ_BACKWARD_DOUBLE_LINK(ZZFP(ZZb,id),given,ret)

#define ZZZ_BACKWARD_DOUBLE_LINK(bwp,given,ret) (ret)=(given)->bwp;
#define ZZ_DELETE_GENERAL_LINK(id,from,targ) \
ZZZ_DELETE_GENERAL_LINK(ZZFP(ZZg,id),from,targ)

#ifdef ZZcplus
#define ZZZ_DELETE_GENERAL_LINK(ptr,from,targ) \
{ char **ZZp=(char**)(&(targ)); *ZZp=(from)->ptr; (from)->ptr=NULL;}
#else
#define ZZZ_DELETE_GENERAL_LINK(ptr,from,targ) \
{ (targ)=(void *)((from)->ptr); (from)->ptr=NULL;}
#endif
#define ZZ_DELETE_SINGLE_LINK(id,from,targ) \
ZZZ_DELETE_SINGLE_LINK(ZZFP(ZZf,id),from,targ)

#define ZZZ_DELETE_SINGLE_LINK(fwp,from,targ) \
{(targ)=(from)->fwp; (from)->fwp=NULL;}
#define ZZ_DELETE_DOUBLE_LINK(id,from,targ) \
ZZZ_DELETE_DOUBLE_LINK(ZZFP(ZZf,id),ZZFP(ZZb,id),from,targ) 

#define ZZZ_DELETE_DOUBLE_LINK(fwp,bwp,from,targ) \
{(targ)=(from)->fwp; if((from)->fwp){(from)->fwp->bwp=NULL; (from)->fwp=NULL;} }
#define ZZ_ORG_REFERENCE(id,strType1,strType2) /* ZZ_ORG_REFERENCE */
#define ZZ_HYPER_REFERENCE(id,sTp,tTp)  \
ZZ_BASIC_REFERENCE(id,sTp,tTp,ZZ_EXTERN,id) 

#define ZZ_LOCAL_REFERENCE(id,sTp,tTp,where)  \
ZZ_BASIC_REFERENCE(id,sTp,tTp,static,where :: id) 

#define ZZ_BASIC_REFERENCE(id,sTp,tTp,scope,where)  \
class ZZFP(ZZH,id) { \
public: \
    tTp * fwd(sTp *s){tTp *t; ZZ_FORWARD_REFERENCE(id,s,t); return(t);} \
    void add(sTp *s,tTp *t){ZZ_ADD_REFERENCE(id,s,t); }\
    tTp * del(sTp *s){tTp *t;ZZ_DELETE_REFERENCE(id,s,t); return(t);}\
    void set(tTp *t,ZZint cnt){ZZ_SET_REFERENCE(id,t,cnt);}\
    ZZint get(tTp *t){ZZint cnt; ZZ_GET_REFERENCE(id,t,cnt); return(cnt);}\
};\
scope ZZFP(ZZH,id) id
#define ZZ_ADD_REFERENCE(id,from,to) \
ZZZ_ADD_REFERENCE(id,ZZFP(ZZf,id),ZZFP(ZZc,id),from,to)

#ifdef ZZnoCheck
#define ZZZ_ADD_REFERENCE(id,ptr,cnt,from,to) {\
   (from)->ptr=(to); ((to)->cnt)++;}
#else
#define ZZZ_ADD_REFERENCE(id,ptr,cnt,from,to) \
{if((from)->ptr){\
        ZZmsgSS(23,ZZ_STRINGIT(id),(char *)(from));\
        ZZerrFLG=ZZerrFLG|010;\
 }\
 else {(from)->ptr=(to); ((to)->cnt)++;}\
}
#endif
#define ZZ_DELETE_REFERENCE(id,from,targ) \
ZZZ_DELETE_REFERENCE(ZZFP(ZZf,id),ZZFP(ZZc,id),from,targ)

#define ZZZ_DELETE_REFERENCE(fwp,cnt,from,targ) \
{(targ)=(from)->fwp; (from)->fwp=NULL; if(targ)((targ)->cnt)--;}
#define ZZ_FORWARD_REFERENCE(id,given,ret) \
ZZZ_FORWARD_REFERENCE(ZZFP(ZZf,id),given,ret)

#define ZZZ_FORWARD_REFERENCE(fwd,given,ret) {(ret)=(given)->fwd;}
#define ZZ_SET_REFERENCE(id,targ,count) \
ZZZ_SET_REFERENCE(ZZFP(ZZc,id),targ,count)

#define ZZZ_SET_REFERENCE(cnt,targ,count) {(targ)->cnt=(count);}
#define ZZ_GET_REFERENCE(id,targ,count) \
ZZZ_GET_REFERENCE(ZZFP(ZZc,id),targ,count)

#define ZZZ_GET_REFERENCE(cnt,targ,count) {(count)=(targ)->cnt;}
#define ZZ_ADD(id,entry,pp) \
ZZFN(ZZ_ADD,id)(id,entry,pp)
#define ZZF_ADD(id,entry,pp) \
ZZFN(ZZF_ADD,id)(id,entry,pp)
#define ZZ_SET(id,entry,pp) \
ZZFN(ZZ_SET,id)(id,entry,pp)
#define ZZ_GET(id,entry,pp) \
ZZFN(ZZ_GET,id)(id,entry,pp)
#define ZZ_INSERT(id,entry,pp) \
ZZFN(ZZ_INSERT,id)(id,entry,pp)
#define ZZ_APPEND(id,entry,pp) \
ZZFN(ZZ_APPEND,id)(id,entry,pp)
#define ZZ_DELETE(id,entry,pp) \
ZZFN(ZZ_DELETE,id)(id,entry,pp)
#define ZZ_A_TRAVERSE(id,entry,pp) \
ZZFN(ZZ_A_TRAVERSE,id)(id,entry,pp)
#define ZZ_A_RETRACE(id,entry,pp) \
ZZFN(ZZ_A_RETRACE,id)(id,entry,pp)
#define ZZ_FORWARD(id,given,pp) \
ZZFN(ZZ_FORWARD,id)(id,given,pp)
#define ZZ_BACKWARD(id,given,pp) \
ZZFN(ZZ_BACKWARD,id)(id,given,pp)
#define ZZ_PARENT(id,given,pp) \
ZZFN(ZZ_PARENT,id)(id,given,pp)
#define ZZ_CHILD(id,given,pp) \
ZZFN(ZZ_CHILD,id)(id,given,pp)
#define ZZ_SORT(id,sortFun,start) \
ZZFN(ZZ_SORT,id)(id,sortFun,start)
#define ZZ_POP(id,entry,pp) \
ZZFN(ZZ_POP,id)(id,entry,pp)
#define ZZ_PUSH(id,entry,pp) \
ZZFN(ZZ_PUSH,id)(id,entry,pp)
#define ZZ_NODES(id,v,e) \
ZZFN(ZZ_NODES,id)(id,v,e)
#define ZZ_PTR(id) \
ZZFN(ZZ_PTR,id)(id)
#define ZZ_ADD_NAME(id,obj,name) \
ZZZ_ADD_NAME(id,ZZFP(ZZn,id),obj,name)

#ifdef ZZnoCheck
#define ZZZ_ADD_NAME(id,nPtr,obj,name) {(obj)->nPtr=name;}
#else
#define ZZZ_ADD_NAME(id,nPtr,obj,name) \
{if((obj)->nPtr){\
    ZZmsgSS(10,(obj)->nPtr,name);\
    ZZerrFLG=ZZerrFLG|010;\
 }\
 else (obj)->nPtr=name;}
#endif
#define ZZ_PTR_NAME(id) \
ZZFP(ZZn,id)
#define ZZ_DELETE_NAME(id,obj,name) \
ZZZ_DELETE_NAME(ZZFP(ZZn,id),obj,name)

#define ZZZ_DELETE_NAME(nPtr,obj,name) \
{(name)=(obj)->nPtr; (obj)->nPtr=NULL;}
#define ZZ_FORWARD_NAME(id,given,name) \
ZZZ_FORWARD_NAME(ZZFP(ZZn,id),given,name)

#define ZZZ_FORWARD_NAME(nPtr,given,name) \
{(name)=(given)->nPtr;}
#define ZZ_ORG_NAME(id,strType) /* ZZ_ORG_NAME */
#define ZZ_HYPER_NAME(id,Obj)  \
ZZ_BASIC_NAME(id,Obj,ZZ_EXTERN,id)

#define ZZ_LOCAL_NAME(id,Obj,where)  \
ZZ_BASIC_NAME(id,Obj,static,where :: id)

#define ZZ_BASIC_NAME(id,Obj,scope,where)  \
class ZZFP(ZZH,id) { \
    friend class Obj;\
public: \
    char * fwd(Obj *s){char *p; ZZ_FORWARD_NAME(id,s,p); return(p);} \
    void add(Obj *s,char *p){ZZ_ADD_NAME(id,s,p);}\
    void addNew(Obj *s,char *p){char *nn; ZZ_STRING_ALLOC(p,nn); add(s,nn);}\
    char * del(Obj *s){char *p;ZZ_DELETE_NAME(id,s,p);return(p);}\
};\
scope ZZFP(ZZH,id) id
#define ZZ_ORG_SINGLE_GRAPH(id,nodeType,edgeType) \
/* ZZ_ORG_SINGLE_GRAPH */
#define ZZ_HYPER_SINGLE_GRAPH(id,vType,eType)  \
ZZ_BASIC_SINGLE_GRAPH(id,vType,eType,ZZ_EXTERN,id)

#define ZZ_LOCAL_SINGLE_GRAPH(id,vType,eType,where)  \
ZZ_BASIC_SINGLE_GRAPH(id,vType,eType,static,where :: id)

#define ZZ_BASIC_SINGLE_GRAPH(id,vType,eType,scope,where)  \
class ZZFP(ZZH,id) { \
  friend class vType;\
  friend class eType;\
public: \
  void nodes(vType **v,eType *e){ZZ_NODES_SINGLE_GRAPH(id,v,e);}\
  eType *edge(vType *v){return(v->ZZFP(ZZe,id));}\
  eType *fwd(vType **v,eType *e);\
  void add(vType **v,eType *e);\
  void insert(vType **v,eType *e){add(v,e);\
      v[0]->ZZFP(ZZe,id)=e; v[1]->ZZFP(ZZe,id)=e;}\
  void del(eType *e);\
  void set(vType *v,eType *e);\
};\
scope ZZFP(ZZH,id) id; \
class ZZFN(id,iterator){ \
   vType *nd[2];\
   vType *ver;\
   eType *beg;\
   eType *nxt;\
public:\
   ZZFN(id,iterator)(){beg=nxt=NULL; nd[0]=NULL;}\
   ZZFN(id,iterator)(vType *v){start(v);}\
   vType *adj(){return(ver);}\
   void start(vType *v){if(v){beg=where.edge(v); nd[0]=v; if(beg)nxt=where.fwd(nd,beg); else nxt=NULL;}\
                                                 else beg=nxt=NULL;} \
   eType* operator++(){eType *e; e=nxt; ver=nd[1]; if(!ver)ver=nd[0];\
            if(e==beg)nxt=beg=NULL; else nxt=where.fwd(nd,e); return(e);};\
}
#define ZZ_ADD_SINGLE_GRAPH(id,nd,ge) \
ZZZ_ADD_SINGLE_GRAPH\
(id,ZZFT(2,id),ZZFP(ZZe,id),ZZFP(ZZx,id),ZZFP(ZZy,id),ZZFP(ZZr,id),ZZFP(ZZs,id),nd,ge)

#ifdef ZZnoCheck
#define ZZZ_ADD_SINGLE_GRAPH(id,eType,edge,node1,node2,next1,next2,nd,ge) \
{eType *ZZe;\
	(ge)->node1=(nd)[0];\
        ZZe=(nd)[0]->edge;\
        if(ZZe){\
	    if(ZZe->node1==(nd)[0]){(ge)->next1=ZZe->next1; ZZe->next1=(ge);}\
	    else                 {(ge)->next1=ZZe->next2; ZZe->next2=(ge);}\
	}\
        else {(nd)[0]->edge=(ge); (ge)->next1=(ge);}\
	if((nd)[0]!=(nd)[1]){ \
	    (ge)->node2=(nd)[1];\
            ZZe=(nd)[1]->edge;\
            if(ZZe){\
	      if(ZZe->node1==(nd)[1]){(ge)->next2=ZZe->next1; ZZe->next1=(ge);}\
	      else                 {(ge)->next2=ZZe->next2; ZZe->next2=(ge);}\
	    }\
            else {(nd)[1]->edge=(ge); (ge)->next2=(ge);}\
	}\
	else {(ge)->node2=NULL; (ge)->next2=NULL;}\
}
#else
#define ZZZ_ADD_SINGLE_GRAPH(id,eType,edge,node1,node2,next1,next2,nd,ge) \
{eType *ZZe;\
    if((ge)->node1||(ge)->node2||(ge)->next1||(ge)->next2){\
        ZZmsgSS(23,ZZ_STRINGIT(id),(char *)(ge));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else {\
	(ge)->node1=(nd)[0];\
        ZZe=(nd)[0]->edge;\
        if(ZZe){\
	    if(ZZe->node1==(nd)[0]){(ge)->next1=ZZe->next1; ZZe->next1=(ge);}\
	    else                 {(ge)->next1=ZZe->next2; ZZe->next2=(ge);}\
	}\
        else {(nd)[0]->edge=(ge); (ge)->next1=(ge);}\
	if((nd)[0]!=(nd)[1]){ \
	    (ge)->node2=(nd)[1];\
            ZZe=(nd)[1]->edge;\
            if(ZZe){\
	      if(ZZe->node1==(nd)[1]){(ge)->next2=ZZe->next1; ZZe->next1=(ge);}\
	      else                 {(ge)->next2=ZZe->next2; ZZe->next2=(ge);}\
	    }\
            else {(nd)[1]->edge=(ge); (ge)->next2=(ge);}\
	}\
	else {(ge)->node2=NULL; (ge)->next2=NULL;}\
    }\
}
#endif
#define ZZ_DELETE_SINGLE_GRAPH(id,nodes,ge) \
ZZZ_DELETE_SINGLE_GRAPH(ZZFT(1,id),ZZFT(2,id),\
ZZFP(ZZe,id),ZZFP(ZZx,id),ZZFP(ZZy,id),ZZFP(ZZr,id),ZZFP(ZZs,id),nodes,ge)

#define \
    ZZZ_DELETE_SINGLE_GRAPH(nStr,eStr,edge,node1,node2,next1,next2,nodes,ge) \
{eStr *ZZe,*ZZf; nStr *ZZa,*ZZb,**nd;\
    ZZe=(ge);\
    if(!ZZe){\
        nd=nodes;\
        ZZa=(nd)[0]; ZZb=(nd)[1]; if(ZZa==ZZb)ZZb=NULL;\
	ZZf=ZZa->edge;\
	for(ZZe=ZZf;ZZe;){\
	    if     (ZZe->node1==ZZa){if(ZZe->node2==ZZb)break; ZZe=ZZe->next1;}\
	    else if(ZZe->node2==ZZa){if(ZZe->node1==ZZb)break; ZZe=ZZe->next2;}\
	    else {\
                ZZmsg(47);\
                ZZerrFLG=ZZerrFLG|020;\
            }\
	    if(ZZe==ZZf)ZZe=NULL;\
	}\
    }\
    if(ZZe){\
	if(!(ZZe->next1))ZZe=ZZe;\
	else if(ZZe->next1==ZZe)ZZe->node1->edge=NULL;\
	else {\
	    if(ZZe->node1->edge==ZZe)ZZe->node1->edge=ZZe->next1;\
	    for(ZZf=ZZe;;){\
	        if(ZZf->node1==ZZe->node1){\
		    if(ZZf->next1==ZZe){ZZf->next1=ZZe->next1; break;}\
		    ZZf=ZZf->next1;\
		}\
	        else if(ZZf->node2==ZZe->node1){\
		    if(ZZf->next2==ZZe){ZZf->next2=ZZe->next1; break;}\
		    ZZf=ZZf->next2;\
		}\
	    }\
	}\
	if(!(ZZe->next2))ZZe=ZZe;\
	else if(ZZe->next2==ZZe)ZZe->node2->edge=NULL;\
	else {\
	    if(ZZe->node2->edge==ZZe)ZZe->node2->edge=ZZe->next2;\
	    for(ZZf=ZZe;;){\
	        if(ZZf->node1==ZZe->node2){\
		    if(ZZf->next1==ZZe){ZZf->next1=ZZe->next2; break;}\
		    ZZf=ZZf->next1;\
		}\
	        else if(ZZf->node2==ZZe->node2){\
		    if(ZZf->next2==ZZe){ZZf->next2=ZZe->next2; break;}\
		    ZZf=ZZf->next2;\
		}\
	    }\
	}\
	ZZe->next1=ZZe->next2=NULL;\
	ZZe->node1=ZZe->node2=NULL;\
    }\
}
#define ZZ_A_TRAVERSE_SINGLE_GRAPH(id,nd,ge) \
ZZZ_A_TRAVERSE_SINGLE_GRAPH\
(ZZFT(1,id),ZZFT(2,id),ZZFP(ZZe,id),ZZFP(ZZx,id),ZZFP(ZZy,id),ZZFP(ZZr,id),ZZFP(ZZs,id),nd,ge)

#define ZZZ_A_TRAVERSE_SINGLE_GRAPH(nStr,eStr,edge,node1,node2,next1,next2,nd,ge) \
{eStr *ZZtmp;\
if((nd) && (nd)[0])(ge)=(nd)[0]->edge; else (ge)=NULL;\
if(ge){\
    if     ((ge)->node1==(nd)[0])(ge)=(ge)->next1;\
    else if((ge)->node2==(nd)[0])(ge)=(ge)->next2;\
}\
for( ;(ge);(ge)=ZZtmp){\
    if     ((ge)->node1==(nd)[0]){ZZtmp=(ge)->next1; (nd)[1]=(ge)->node2;}\
    else if((ge)->node2==(nd)[0]){ZZtmp=(ge)->next2; (nd)[1]=(ge)->node1;}\
    else ZZtmp=(eStr *)NULL;\
    if((ge)==(nd)[0]->edge)ZZtmp=(eStr *)NULL;\
    if((nd)[1]==(nStr *)NULL)(nd)[1]=(nd)[0];
#define ZZ_NODES_SINGLE_GRAPH(id,nd,ge) \
ZZZ_NODES_SINGLE_GRAPH(ZZFP(ZZx,id),ZZFP(ZZy,id),nd,ge)

#define ZZZ_NODES_SINGLE_GRAPH(node1,node2,nd,ge) \
{(nd)[0]=ge->node1; (nd)[1]=ge->node2;\
if((nd)[0]==NULL && (nd)[1]!=NULL)(nd)[0]=(nd)[1];\
if((nd)[1]==NULL && (nd)[0]!=NULL)(nd)[1]=(nd)[0];}

/* edge from-to the same node has internally one node NULL */
#define ZZ_ORG_DIRECT_GRAPH(id,nodeType,edgeType) \
/* ZZ_ORG_DIRECT_GRAPH */
#define ZZ_HYPER_DIRECT_GRAPH(id,vType,eType)  \
ZZ_BASIC_DIRECT_GRAPH(id,vType,eType,ZZ_EXTERN,id)

#define ZZ_LOCAL_DIRECT_GRAPH(id,vType,eType,where)  \
ZZ_BASIC_DIRECT_GRAPH(id,vType,eType,static,where :: id)

#define ZZ_BASIC_DIRECT_GRAPH(id,vType,eType,scope,where)  \
class ZZFP(ZZH,id) { \
  friend class vType;\
  friend class eType;\
public: \
  void nodes(vType **v,eType *e){ZZ_NODES_DIRECT_GRAPH(id,v,e);}\
  eType *edge(vType *v){return(v->ZZFP(ZZe,id));}\
  eType *fwd(vType **v,eType *e){eType *t;\
      t=e->ZZFP(ZZr,id); v[1]=t->ZZFP(ZZy,id); return(t);}\
  void add(vType **v,eType *e);\
  void insert(vType **v,eType *e){add(v,e); v[0]->ZZFP(ZZe,id)=e;}\
  void del(vType **v,eType *e);\
  void set(vType *v,eType *e);\
};\
scope ZZFP(ZZH,id) id; \
class ZZFN(id,iterator){ \
   vType *nd[2];\
   vType *ver;\
   eType *beg;\
   eType *nxt;\
public:\
   ZZFN(id,iterator)(vType *v){start(v);}\
   vType *adj(){return(ver);}\
   void start(vType *v){if(v){beg=where.edge(v); nd[0]=v; if(beg)nxt=where.fwd(nd,beg); else nxt=NULL;}\
                                                 else beg=nxt=NULL;} \
   eType* operator++(){eType *e; e=nxt; ver=nd[1]; if(!ver)ver=nd[0];\
            if(e==beg)nxt=beg=NULL; else nxt=where.fwd(nd,e); return(e);}\
}
#define ZZ_ADD_DIRECT_GRAPH(id,nd,ge) \
ZZZ_ADD_DIRECT_GRAPH\
(id,ZZFT(2,id),ZZFP(ZZe,id),ZZFP(ZZy,id),ZZFP(ZZr,id),nd,ge)

#ifdef ZZnoCheck
#define ZZZ_ADD_DIRECT_GRAPH(id,eType,edge,node2,next1,nd,ge) \
{eType *ZZe;\
        ZZe=(nd)[0]->edge;\
        if(ZZe){(ge)->next1=ZZe->next1; ZZe->next1=(ge);}\
        else {(nd)[0]->edge=(ge); (ge)->next1=(ge);}\
	if((nd)[0]!=(nd)[1])(ge)->node2=(nd)[1];\
	else (ge)->node2=NULL;\
}
#else
#define ZZZ_ADD_DIRECT_GRAPH(id,eType,edge,node2,next1,nd,ge) \
{eType *ZZe;\
    if((ge)->node2||(ge)->next1){\
        ZZmsgSS(23,ZZ_STRINGIT(id),(char *)(ge));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else {\
        ZZe=(nd)[0]->edge;\
        if(ZZe){(ge)->next1=ZZe->next1; ZZe->next1=(ge);}\
        else {(nd)[0]->edge=(ge); (ge)->next1=(ge);}\
	if((nd)[0]!=(nd)[1])(ge)->node2=(nd)[1];\
	else (ge)->node2=NULL;\
    }\
}
#endif
#define ZZ_DELETE_DIRECT_GRAPH(id,nodes,ge) \
ZZZ_DELETE_DIRECT_GRAPH(ZZFT(1,id),ZZFT(2,id),\
ZZFP(ZZe,id),ZZFP(ZZy,id),ZZFP(ZZr,id),nodes,ge)

#define ZZZ_DELETE_DIRECT_GRAPH(nStr,eStr,edge,node2,next1,nodes,ge) \
{eStr *ZZe,*ZZf; nStr *ZZa,*ZZb,**nd;\
    ZZe=(ge);\
    if(nodes){\
        nd=nodes;\
        ZZa=(nd)[0]; ZZb=(nd)[1];\
    }\
    if(!ZZe && nodes){\
        if(ZZa==ZZb)ZZb=NULL;\
	ZZf=ZZa->edge;\
	for(ZZe=ZZf;ZZe;){\
	    if(ZZe->node2==ZZb)break;\
            ZZe=ZZe->next1; if(ZZe==ZZf)ZZe=NULL;\
	}\
    }\
    if(ZZe && nodes){\
	if(!(ZZe->next1))ZZe=ZZe;\
	else if(ZZe->next1==ZZe)ZZa->edge=NULL;\
	else {\
	    if(ZZa->edge == ZZe)ZZa->edge=ZZe->next1;\
	    for(ZZf=ZZe;;){\
		if(ZZf->next1==ZZe){ZZf->next1=ZZe->next1; break;}\
		ZZf=ZZf->next1;\
	    }\
	}\
	ZZe->next1=NULL;\
	ZZe->node2=NULL;\
    }\
}
#define ZZ_A_TRAVERSE_DIRECT_GRAPH(id,nd,ge) \
ZZZ_A_TRAVERSE_DIRECT_GRAPH\
(ZZFT(2,id),ZZFP(ZZe,id),ZZFP(ZZy,id),ZZFP(ZZr,id),nd,ge)

#define ZZZ_A_TRAVERSE_DIRECT_GRAPH(eStr,edge,node2,next1,nd,ge) \
{eStr *ZZtmp;\
if((nd) && (nd)[0])(ge)=(nd)[0]->edge; else (ge)=NULL;\
if(ge)(ge)=(ge)->next1;\
for( ;(ge);(ge)=ZZtmp){\
    (nd)[1]=(ge)->node2;\
    if((ge)==(nd)[0]->edge)ZZtmp=NULL; else ZZtmp=(ge)->next1;\
    if((nd)[1]==NULL)(nd)[1]=(nd)[0];
#define ZZ_NODES_DIRECT_GRAPH(id,nd,ge) \
ZZZ_NODES_DIRECT_GRAPH(ZZFP(ZZy,id),nd,ge)

#define ZZZ_NODES_DIRECT_GRAPH(node2,nd,ge) \
{ (nd)[1]=ge->node2;}
#define ZZ_ORG_FIFO(id,strType) /* ZZ_ORG_FIFO */
#define ZZ_HYPER_FIFO(id,type)  \
ZZ_BASIC_FIFO(id,type,ZZ_EXTERN,id) 

#define ZZ_LOCAL_FIFO(id,type,where)  \
ZZ_BASIC_FIFO(id,type,static,where :: id) 

#define ZZ_BASIC_FIFO(id,type,scope,where)  \
class ZZFP(ZZH,id) { \
    type *start;\
public: \
    void push(type *p);\
    type * pop(void);\
    ZZFP(ZZH,id)(){start=NULL;} \
};\
scope ZZFP(ZZH,id) id
#define ZZ_POP_FIFO(id,entry,pp) \
ZZZ_POP_FIFO(ZZFP(ZZf,id),entry,pp)

#define ZZZ_POP_FIFO(fwp,entry,pp) \
{\
    if(entry){\
        (pp)=(entry)->fwp;\
        if((entry)==(pp))(entry)=NULL; else (entry)->fwp=(pp)->fwp;\
        (pp)->fwp=NULL;}\
    else (pp)=NULL;\
}
#define ZZ_PUSH_FIFO(id,entry,pp) \
ZZZ_PUSH_FIFO(ZZFP(ZZf,id),entry,pp)

#define ZZZ_PUSH_FIFO(fwp,entry,pp) \
{\
    if((pp) && (pp)->fwp==NULL){\
        if(entry){(pp)->fwp=(entry)->fwp; (entry)->fwp=(pp);}\
        else (pp)->fwp=(pp);\
        (entry)=(pp);\
    }\
}
#define ZZ_ORG_LIFO(id,strType) /* ZZ_ORG_LIFO */
#define ZZ_HYPER_LIFO(id,type)  \
ZZ_BASIC_LIFO(id,type,ZZ_EXTERN,id) 

#define ZZ_LOCAL_LIFO(id,type,where)  \
ZZ_BASIC_LIFO(id,type,static,where :: id) 

#define ZZ_BASIC_LIFO(id,type,scope,where)  \
class ZZFP(ZZH,id) { \
    type *start;\
public: \
    void push(type *p);\
    type * pop(void);\
    ZZFP(ZZH,id)(){start=NULL;} \
};\
scope ZZFP(ZZH,id) id
#define ZZ_POP_LIFO(id,entry,pp) \
ZZZ_POP_LIFO(ZZFP(ZZf,id),entry,pp)

#define ZZZ_POP_LIFO(fwp,entry,pp) \
{\
    if(entry){\
        (pp)=(entry)->fwp;\
        if((entry)==(pp))(entry)=NULL; else (entry)->fwp=(pp)->fwp;\
        (pp)->fwp=NULL;\
    }\
    else (pp)=NULL;\
}
#define ZZ_PUSH_LIFO(id,entry,pp) \
ZZZ_PUSH_LIFO(ZZFP(ZZf,id),entry,pp)

#define ZZZ_PUSH_LIFO(fwp,entry,pp) \
{\
    if((pp) && (pp)->fwp==NULL){\
        if(entry){(pp)->fwp=(entry)->fwp; (entry)->fwp=(pp);}\
        else {(pp)->fwp=(pp); (entry)=(pp);}\
    }\
}
#define ZZ_ORG_SINGLE_TREE(id,strType) \
/* ZZ_ORG_SINGLE_TREE */
#define ZZ_HYPER_SINGLE_TREE(id,type) \
ZZ_BASIC_SINGLE_TREE(id,type,ZZ_EXTERN,id)

#define ZZ_LOCAL_SINGLE_TREE(id,type,where) \
ZZ_BASIC_SINGLE_TREE(id,type,static,where :: id)

#define ZZ_BASIC_SINGLE_TREE(id,type,scope,where) \
class ZZFP(ZZH,id) { \
public: \
  type *par(type *c){type *p;\
                  ZZ_PARENT_SINGLE_TREE(id,c,p); return(p);}\
  type *child(type *p){type *c;\
                   ZZ_CHILD_SINGLE_TREE(id,p,c); return(c);}\
  type *chld(type *p){return p->ZZFP(ZZc,id);}\
  type * fwd(type *t){type *s;\
                 ZZ_FORWARD_SINGLE_TREE(id,t,s); return(s);}\
  void set(type *c){ZZ_SET_SINGLE_TREE(id,NULL,c);}\
  void add(type *p,type *c);\
  void app(type *t,type *c);\
  void del(type *t);\
};\
scope ZZFP(ZZH,id) id; \
class ZZFN(id,iterator){ \
   type *beg;\
   type *nxt;\
public:\
   ZZFN(id,iterator)(type *p){start(p);}\
   ZZFN(id,iterator)(){beg=nxt=NULL;}\
   void start(type *p){if(p){beg=where.chld(p);\
    if(beg)nxt=where.fwd(beg); else nxt=NULL;} else beg=nxt=NULL;} \
   type* operator++(){type *p;\
      p=nxt; if(p==beg)nxt=beg=NULL; else nxt=where.fwd(p); return(p);}\
}

#define ZZ_ADD_SINGLE_TREE(id,par,pp) \
ZZZ_ADD_SINGLE_TREE\
(id,ZZFP(ZZp,id),ZZFP(ZZs,id),ZZFP(ZZc,id),par,pp)

#ifdef ZZnoCheck
#define ZZZ_ADD_SINGLE_TREE(id,parent,sibling,child,par,pp) \
{\
        if((par)->child==NULL){\
            (par)->child=(pp);\
            (pp)->parent=(par);\
            (pp)->sibling=(pp);\
        }\
	else {\
            (pp)->sibling=((par)->child)->sibling;\
            ((par)->child)->sibling=(pp);\
            (pp)->parent=(par);\
        }\
}
#else
#define ZZZ_ADD_SINGLE_TREE(id,parent,sibling,child,par,pp) \
{\
    if((pp)->parent!=NULL || (pp)->sibling!=NULL){\
        ZZmsgSS(23,ZZ_STRINGIT(id),(char *)(pp));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else {\
        if((par)->child==NULL){\
            (par)->child=(pp);\
            (pp)->parent=(par);\
            (pp)->sibling=(pp);\
        }\
	else {\
            (pp)->sibling=((par)->child)->sibling;\
            ((par)->child)->sibling=(pp);\
            (pp)->parent=(par);\
        }\
    }\
}
#endif
#define ZZ_SET_SINGLE_TREE(id,par,pp) \
ZZZ_SET_SINGLE_TREE(id,ZZFP(ZZp,id),ZZFP(ZZc,id),ZZFP(ZZs,id),par,pp)

#define ZZZ_SET_SINGLE_TREE(id,parent,child,sibling,par,pp) {\
    if((pp)->parent) (pp)->parent->child=(pp);\
}
#define ZZ_DELETE_SINGLE_TREE(id,entry,pp) \
ZZZ_DELETE_SINGLE_TREE(id,ZZFP(ZZp,id),ZZFP(ZZs,id),ZZFP(ZZc,id),pp)

/* ZZFT() is used inside the next macro instead of passing strType,
 * the reason is that the macro line was too long for DOS in some cases */

#define ZZZ_DELETE_SINGLE_TREE(id,parent,sibling,child,pp) \
{ZZFT(1,id) *ZZv,*ZZp,*ZZs,*ZZc;\
    ZZp=(pp)->parent; ZZs=(pp)->sibling; \
    if(ZZp){\
        if(ZZs==(pp))ZZp->child=NULL;\
        else { \
            ZZc=ZZp->child; if(!ZZc)ZZc=(pp); \
            for(ZZv=ZZc; ZZv->sibling!=(pp); ZZv=ZZv->sibling)continue;\
            if(ZZp->child==(pp))ZZp->child=ZZv;\
            ZZv->sibling=ZZs;\
        } \
    }\
    (pp)->sibling=NULL; (pp)->parent=NULL;\
}
#define ZZ_A_TRAVERSE_SINGLE_TREE(id,par,pp) \
ZZZ_A_TRAVERSE_SINGLE_TREE(ZZFT(1,id),ZZFP(ZZs,id),ZZFP(ZZc,id),par,pp)

#define ZZZ_A_TRAVERSE_SINGLE_TREE(strType,sibling,child,par,pp) \
{strType *ZZt,*ZZc;\
if(par)ZZc=(par)->child; else ZZc=NULL;\
if(ZZc)(pp)=ZZc->sibling; else (pp)=NULL;\
for(;pp;(pp)=ZZt){\
    if((pp)==ZZc)ZZt=NULL; else ZZt=(pp)->sibling;
#define ZZ_FORWARD_SINGLE_TREE(id,obj,next) \
ZZZ_FORWARD_SINGLE_TREE(ZZFP(ZZs,id),obj,next)

#define ZZZ_FORWARD_SINGLE_TREE(sibling,obj,next) {(next)=(obj)->sibling;}
#define ZZ_PARENT_SINGLE_TREE(id,pp,par) \
ZZZ_PARENT_SINGLE_TREE(ZZFP(ZZp,id),pp,par)

#define ZZZ_PARENT_SINGLE_TREE(parent,pp,par) {(par)=(pp)->parent;}
#define ZZ_CHILD_SINGLE_TREE(id,par,chi) \
ZZZ_CHILD_SINGLE_TREE(ZZFP(ZZc,id),ZZFP(ZZs,id),par,chi)

#define ZZZ_CHILD_SINGLE_TREE(child,sibl,par,chi) {\
  (chi)=(par)->child; if(chi)(chi)=(chi)->sibl; }
#define ZZ_APPEND_SINGLE_TREE(id,obj,pp) \
ZZZ_APPEND_SINGLE_TREE\
(id,ZZFP(ZZp,id),ZZFP(ZZs,id),obj,pp)

#define ZZZ_APPEND_SINGLE_TREE(id,parent,sibling,obj,pp) \
{\
char *ZZn;\
    ZZn=ZZ_STRINGIT(id);\
    if((pp)->parent || (pp)->sibling){\
        ZZmsgSS(25,ZZn,(char *)(pp));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else if(!((obj)->parent)){\
        ZZmsgSS(26,ZZn,(char *)(pp));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else {\
        (pp)->parent=(obj)->parent;\
        (pp)->sibling=(obj)->sibling;\
        (obj)->sibling=(pp);\
    }\
}
#define ZZ_ORG_DOUBLE_TREE(id,strType) \
/* ZZ_ORG_DOUBLE_TREE */
#define ZZ_HYPER_DOUBLE_TREE(id,type) \
ZZ_BASIC_DOUBLE_TREE(id,type,ZZ_EXTERN,id)

#define ZZ_LOCAL_DOUBLE_TREE(id,type,where) \
ZZ_BASIC_DOUBLE_TREE(id,type,static,where :: id)

#define ZZ_BASIC_DOUBLE_TREE(id,type,scope,where) \
class ZZFP(ZZH,id) { \
public: \
  type *par(type *c){type *p;\
                  ZZ_PARENT_DOUBLE_TREE(id,c,p); return(p);}\
  type *child(type *p){type *c;\
                   ZZ_CHILD_DOUBLE_TREE(id,p,c); return(c);}\
  type *chld(type *p){ return p->ZZFP(ZZc,id);}\
  type * fwd(type *t){type *s;\
                 ZZ_FORWARD_DOUBLE_TREE(id,t,s); return(s);}\
  type * bwd(type *t){type *s;\
                 ZZ_BACKWARD_DOUBLE_TREE(id,t,s); return(s);}\
  void set(type *c){ZZ_SET_DOUBLE_TREE(id,NULL,c);}\
  void add(type *p,type *c);\
  void ins(type *t,type *s);\
  void app(type *t,type *s);\
  void del(type *t);\
};\
scope ZZFP(ZZH,id) id; \
class ZZFN(id,iterator){ \
   type *beg;\
   type *nxt;\
public:\
   ZZFN(id,iterator)(type *p){start(p);}\
   ZZFN(id,iterator)(){beg=nxt=NULL;}\
   void start(type *p){if(p)beg=where.chld(p); else beg=NULL; nxt=NULL;} \
   type* operator++(){type *p;\
      if(nxt)p=nxt; else if(beg)p=where.fwd(beg); else p=NULL;\
      if(p==beg)nxt=beg=NULL; else nxt=where.fwd(p); return(p);}\
   type* operator--(){type *p;\
      if(nxt)p=nxt; else if(beg){p=beg; beg=where.fwd(beg);} else p=NULL;\
      if(p==beg)nxt=beg=NULL; else nxt=where.bwd(p); return(p);}\
}

#define ZZ_ADD_DOUBLE_TREE(id,par,pp) \
ZZZ_ADD_DOUBLE_TREE\
(id,ZZFP(ZZp,id),ZZFP(ZZs,id),ZZFP(ZZb,id),ZZFP(ZZc,id),par,pp)

#ifdef ZZnoCheck
#define ZZZ_ADD_DOUBLE_TREE(id,parent,sibling,backward,child,par,pp) \
{\
        if((par)->child==NULL){\
            (par)->child=(pp);\
            (pp)->parent=(par);\
            (pp)->sibling=(pp)->backward=(pp);\
        }\
	else {\
            (pp)->sibling=(par)->child->sibling;\
            (pp)->backward=(par)->child;\
            (pp)->parent=(par);\
            (par)->child->sibling->backward=(pp);\
            (par)->child->sibling=(pp);\
        }\
}
#else
#define ZZZ_ADD_DOUBLE_TREE(id,parent,sibling,backward,child,par,pp) \
{\
    if((pp)->parent!=NULL || (pp)->sibling!=NULL){\
        ZZmsgSS(23,ZZ_STRINGIT(id),(char *)(pp));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else {\
        if((par)->child==NULL){\
            (par)->child=(pp);\
            (pp)->parent=(par);\
            (pp)->sibling=(pp)->backward=(pp);\
        }\
	else {\
            (pp)->sibling=(par)->child->sibling;\
            (pp)->backward=(par)->child;\
            (pp)->parent=(par);\
            (par)->child->sibling->backward=(pp);\
            (par)->child->sibling=(pp);\
        }\
    }\
}
#endif
#define ZZ_SET_DOUBLE_TREE(id,par,pp) \
ZZZ_SET_DOUBLE_TREE(id,ZZFP(ZZp,id),ZZFP(ZZc,id),ZZFP(ZZb,id),par,pp)

#define ZZZ_SET_DOUBLE_TREE(id,parent,child,bwp,par,pp) {\
    if((pp)->parent) (pp)->parent->child=(pp); }
#define ZZ_DELETE_DOUBLE_TREE(id,dumb,pp) \
ZZZ_DELETE_DOUBLE_TREE(id,ZZFP(ZZp,id),ZZFP(ZZb,id),ZZFP(ZZs,id),ZZFP(ZZc,id),pp)

/* ZZFT(),ZZFP() are used inside the next macro instead of passing strType.
 * The reason is that the macro line was too long for DOS in some cases */

#define ZZZ_DELETE_DOUBLE_TREE(id,parent,backward,sibling,child,pp) \
{ZZFT(1,id) *ZZv,*ZZp,*ZZs;\
    ZZp=(pp)->parent;\
    if(ZZp){\
        ZZs=(pp)->sibling; ZZv=(pp)->backward;\
        if(ZZs==(pp))ZZp->child=NULL;\
        else { \
            if(ZZp->child==(pp))ZZp->child=ZZv;\
            ZZv->sibling=ZZs;\
            ZZs->backward=ZZv;\
        } \
    }\
    (pp)->sibling=(pp)->backward=NULL; (pp)->parent=NULL;\
}
#define ZZ_A_TRAVERSE_DOUBLE_TREE(id,par,pp) \
ZZZ_A_TRAVERSE_DOUBLE_TREE(ZZFT(1,id),ZZFP(ZZs,id),ZZFP(ZZc,id),par,pp)

#define ZZZ_A_TRAVERSE_DOUBLE_TREE(strType,sibling,child,par,pp) \
{strType *ZZt,*ZZc;\
if(par)ZZc=(par)->child; else ZZc=NULL;\
if(ZZc)(pp)=ZZc->sibling; else (pp)=NULL;\
for(;pp;(pp)=ZZt){\
    if((pp)==ZZc)ZZt=NULL; else ZZt=(pp)->sibling;
#define ZZ_FORWARD_DOUBLE_TREE(id,obj,next) \
ZZZ_FORWARD_DOUBLE_TREE(ZZFP(ZZs,id),obj,next)

#define ZZZ_FORWARD_DOUBLE_TREE(sibling,obj,next) {(next)=(obj)->sibling;}
#define ZZ_PARENT_DOUBLE_TREE(id,pp,par) \
ZZZ_PARENT_DOUBLE_TREE(ZZFP(ZZp,id),pp,par)

#define ZZZ_PARENT_DOUBLE_TREE(parent,pp,par) {(par)=(pp)->parent;}
#define ZZ_CHILD_DOUBLE_TREE(id,par,chi) \
ZZZ_CHILD_DOUBLE_TREE(ZZFP(ZZc,id),ZZFP(ZZs,id),par,chi)

#define ZZZ_CHILD_DOUBLE_TREE(child,sibl,par,chi) {\
    (chi)=(par)->child; if(chi)(chi)=(chi)->sibl; }
#define ZZ_BACKWARD_DOUBLE_TREE(id,obj,next) \
ZZZ_BACKWARD_DOUBLE_TREE(ZZFP(ZZb,id),obj,next)

#define ZZZ_BACKWARD_DOUBLE_TREE(backward,obj,next) {(next)=(obj)->backward;}
#define ZZ_A_RETRACE_DOUBLE_TREE(id,par,pp) \
ZZZ_A_RETRACE_DOUBLE_TREE(ZZFT(1,id),ZZFP(ZZb,id),ZZFP(ZZc,id),par,pp)

#define ZZZ_A_RETRACE_DOUBLE_TREE(strType,backward,child,par,pp) \
{strType *ZZt,*ZZc;\
if(par)ZZc=(par)->child; else ZZc=NULL;\
for((pp)=ZZc;pp;(pp)=ZZt){\
    if((pp)->backward==ZZc)ZZt=NULL; else ZZt=(pp)->backward;
#define ZZ_INSERT_DOUBLE_TREE(id,obj,pp) \
ZZZ_INSERT_DOUBLE_TREE\
(id,ZZFP(ZZp,id),ZZFP(ZZs,id),ZZFP(ZZb,id),obj,pp)

#define ZZZ_INSERT_DOUBLE_TREE(id,parent,sibling,backward,obj,pp) \
{\
char *ZZn;\
    ZZn=ZZ_STRINGIT(id);\
    if((pp)->parent!=NULL || (pp)->sibling!=NULL || (pp)->backward!=NULL){\
        ZZmsgSS(24,ZZn,(char *)(pp));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else if(!((obj)->parent)){\
        ZZmsgSS(27,ZZn,(char *)(pp));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else {\
        (obj)->backward->sibling=(pp);\
        (pp)->sibling=(obj);\
        (pp)->parent=(obj)->parent;\
        (pp)->backward=(obj)->backward;\
        (obj)->backward=(pp);\
    }\
}
#define ZZ_APPEND_DOUBLE_TREE(id,obj,pp) \
ZZZ_APPEND_DOUBLE_TREE\
(id,ZZFP(ZZp,id),ZZFP(ZZs,id),ZZFP(ZZb,id),obj,pp)

#define ZZZ_APPEND_DOUBLE_TREE(id,parent,sibling,backward,obj,pp) \
{\
char *ZZn;\
    ZZn=ZZ_STRINGIT(id);\
    if((pp)->parent!=NULL || (pp)->sibling!=NULL || (pp)->backward!=NULL){\
        ZZmsgSS(25,ZZn,(char *)(pp));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else if(!((obj)->parent)){\
        ZZmsgSS(26,ZZn,(char *)(pp));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else {\
        (obj)->sibling->backward=(pp);\
        (pp)->backward=(obj);\
        (pp)->parent=(obj)->parent;\
        (pp)->sibling=(obj)->sibling;\
        (obj)->sibling=(pp);\
    }\
}
#define ZZ_ORG_ARRAY(id,strType1,strType2) \
/* ZZ_ORG_ARRAY */
#ifndef ZORTECH
#define ZZ_HYPER_ARRAY(id,hType,aType) \
ZZ_BASIC_ARRAY(id,hType,aType,ZZ_EXTERN,id)

#define ZZ_LOCAL_ARRAY(id,hType,aType,where) \
ZZ_BASIC_ARRAY(id,hType,aType,static,where :: id)

#define ZZ_BASIC_ARRAY(id,hType,aType,scope,where) \
class ZZFP(ZZH,id) { \
    ZZint binSearch(ZZTsortFun cmpF,hType *hp,aType *op);\
public: \
    aType *form(hType *hp,ZZint sz,ZZint incr){aType *p;\
             ZZ_FORM_ARRAY(id,hp,sz,incr,p); return(p);}\
    void *formed(hType *hp){return (void*)(hp->ZZFP(ZZa,id));}\
    void free(hType *hp){ZZ_FREE_ARRAY(id,hp);}\
    ZZint size(hType *hp,ZZint *wMark,ZZint *incr){ZZint sz;\
             ZZ_SIZE_ARRAY(id,hp,sz,*wMark,*incr); return(sz);}\
    aType *ind(hType *hp,ZZint i){aType *p;\
             ZZ_INDEX_ARRAY(id,hp,i,p); return(p);}\
    void reset(hType *hp,ZZint wMark,ZZint incr){\
             ZZ_RESET_ARRAY(id,hp,wMark,incr);}\
    void push(hType *hp,aType *p);\
    aType *pop(hType *hp);\
    void sort(ZZTsortArr cmpF,hType *hp);\
    void inHeap(ZZTsortFun cmpF,hType *hp,aType *p,ZZTheapBck bck);\
    void outHeap(ZZTsortFun cmpF,hType *hp,aType *p,ZZTheapBck bck);\
    void updHeap(ZZTsortFun cmpF,hType *hp,ZZint i,ZZTheapBck bck);\
    void delHeap(ZZTsortFun cmpF,hType *hp,ZZint i,ZZTheapBck bck);\
    aType *head(hType *hp){ aType *p; ZZ_HEAD_ARRAY(id,hp,p); return(p);}\
    void addOrd(ZZTsortFun cmpF,hType *hp,aType *op);\
    void delOrd(ZZTsortFun cmpF,hType *hp,aType *op);\
    void delOrd(hType *hp,ZZint ind);\
    ZZint getOrd(ZZTsortFun cmpF,hType *hp,aType *op,ZZint *found);\
    void ins(hType *hp,ZZint i,aType *op);\
    ZZint getBit(hType *hp,ZZint i);\
    void setBit(hType *hp,ZZint i,ZZint val);\
};\
scope ZZFP(ZZH,id) id


#else
#define ZZ_HYPER_ARRAY(id,hType,aType) \
ZZ_BASIC_ARRAY(id,hType,aType,ZZ_EXTERN,id)

#define ZZ_LOCAL_ARRAY(id,hType,aType) \
ZZ_BASIC_ARRAY(id,hType,aType,static,where :: id)

#define ZZ_BASIC_ARRAY(id,hType,aType,scope,where) \
class ZZFP(ZZH,id) { \
    ZZint binSearch(ZZTsortFun cmpF,hType *hp,aType *op);\
public: \
    aType *form(hType *hp,ZZint sz,ZZint incr){aType *p;\
             ZZ_FORM_ARRAY(id,hp,sz,incr,p); return(p);}\
    void *formed(hType *hp){return (void*)(hp->ZZFP(ZZa,id));}\
    void free(hType *hp){ZZ_FREE_ARRAY(id,hp);}\
    ZZint size(hType *hp,ZZint *wMark,ZZint *incr){ZZint sz;\
             ZZ_SIZE_ARRAY(id,hp,sz,*wMark,*incr); return(sz);}\
    aType *ind(hType *hp,ZZint i){aType *p;\
             ZZ_INDEX_ARRAY(id,hp,i,p); return(p);}\
    void reset(hType *hp,ZZint wMark,ZZint incr){\
             ZZ_RESET_ARRAY(id,hp,wMark,incr);}\
    void push(hType *hp,aType *p);\
    aType *pop(hType *hp);\
    void sort(ZZTsortArr cmpF,hType *hp);\
    void inHeap(ZZTsortFun cmpF,hType *hp,aType *p,ZZTheapBck bck);\
    void outHeap(ZZTsortFun cmpF,hType *hp,aType *p,ZZTheapBck bck);\
    void updHeap(ZZTsortFun cmpF,hType *hp,ZZint i,ZZTheapBck bck);\
    void delHeap(ZZTsortFun cmpF,hType *hp,ZZint i,ZZTheapBck bck);\
    void sort(ZZTsortArr cmpF,hType *hp);\
    void addOrd(ZZTsortFun cmpF,hType *hp,aType *op);\
    void delOrd(ZZTsortFun cmpF,hType *hp,aType *op);\
    void delOrd(hType *hp,ZZint ind);\
    ZZint getOrd(ZZTsortFun cmpF,hType *hp,aType *op,ZZint *found);\
    void ins(hType *hp,ZZint i,aType *op);\
};\
scope ZZFP(ZZH,id) id
#endif
#define ZZ_HEAD_ARRAY(id,obj,elem) \
ZZZ_HEAD_ARRAY(id,ZZFT(2,id),ZZFP(ZZa,id),obj,elem)
 
#define ZZZ_HEAD_ARRAY(id,str2Type,aPtr,obj,elem) \
    ((elem)=(str2Type *)((obj)->aPtr->array))
#define ZZ_FORM_ARRAY(id,obj,size,incr,arr) \
ZZZ_FORM_ARRAY(id,ZZFP(ZZa,id),ZZFT(2,id),ZZFT(W2,id),ZZFT(H2,id),obj,size,incr,arr)

#define ZZZ_FORM_ARRAY(id,aPtr,objType,strType,hName,obj,size,incr,arr) \
{ ZZarray *ZZFUN_foArr();\
  ZZarray *ZZa; ZZint ZZn;\
    ZZ_GENERAL_EXT(); static objType* sample=NULL;\
    if(!sample)sample=new objType;\
    ZZn=size;\
    ZZa=(obj)->aPtr;\
    if(ZZa){\
        ZZmsgS(23,ZZ_STRINGIT(id));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else if(ZZn<=0)ZZmsgD(21,size);\
    else {\
        ZZn=(incr); if(ZZn== -1)ZZn=0;\
        (obj)->aPtr=ZZfoArr((ZZint)size,(ZZint)ZZn,(ZZint)sizeof(objType),\
                        strType,hName,ZZstrList,(char*)sample);\
        if((obj)->aPtr)(arr)=(objType *)((obj)->aPtr->array);\
        (arr)=(arr);\
    }\
}
#define ZZ_FREE_ARRAY(id,obj) \
ZZZ_FREE_ARRAY(id,ZZFP(ZZa,id),ZZFT(X2,id),obj)

#define ZZZ_FREE_ARRAY(id,aPtr,objType,obj) \
{ ZZarray *ZZFUN_frArr(); \
    (obj)->aPtr=ZZfrArr((obj)->aPtr,(char*)objType,ZZstrList);\
    if((obj)->aPtr){\
        ZZmsgSS(11,ZZ_STRINGIT(id),objType);\
        ZZerrFLG=ZZerrFLG|010;\
    }\
}
#define ZZ_SIZE_ARRAY(id,obj,number,waterMark,increment) \
ZZZ_SIZE_ARRAY(ZZFP(ZZa,id),obj,number,waterMark,increment) 

#define ZZZ_SIZE_ARRAY(aPtr,obj,number,waterMark,increment) \
{ZZarray *ZZa; \
    ZZa=(obj)->aPtr; \
    if(ZZa){(number)=ZZa->num; (waterMark)=ZZa->waterM; (increment)=ZZa->incr;}\
    else {(number)=0; (waterMark)= -1; (increment)=0;}\
}
#define ZZ_INDEX_ARRAY(id,obj,ind,elem) \
ZZZ_INDEX_ARRAY(id,ZZFT(2,id),ZZFP(ZZa,id),obj,ind,elem)

#define ZZZ_INDEX_ARRAY(id,str2Type,aPtr,obj,ind,elem) \
{ZZint ZZi,ZZFUN_upArr(); static str2Type *sample=NULL;\
 ZZarray *ZZa; \
    if(!sample)sample=new str2Type;\
    ZZa=(obj)->aPtr;\
    if(ZZupArr(ZZa,ind,(char*)sample)>0){\
        ZZmsgSS(12,ZZ_STRINGIT(id),ZZ_STRINGIT(str2Type));\
        (elem)=NULL;\
    }\
    else {\
        ZZi=(ind);\
        if(ZZa->waterM<ZZi)ZZa->waterM=ZZi;\
        (elem)=(str2Type *)(&(ZZa->array[ZZi*(ZZa->size)]));\
    }\
}
#define ZZ_INDEX_HEAP(id,obj,ind,elem,bck) \
ZZZ_INDEX_HEAP(id,ZZFT(2,id),ZZFP(ZZa,id),obj,ind,elem,bck)

#define ZZZ_INDEX_HEAP(id,str2Type,aPtr,obj,ind,elem,bck) \
{ZZint ZZi,ZZk,ZZFUN_upArr(); \
 ZZarray *ZZa; static str2Type *sample=NULL;\
    if(!sample)sample=new str2Type;\
    ZZa=(obj)->aPtr;\
    ZZk=ZZupArr(ZZa,ind,(char*)sample);\
    if(ZZk>0){\
        ZZmsgSS(12,ZZ_STRINGIT(id),ZZ_STRINGIT(str2Type));\
        (elem)=NULL;\
    }\
    else {\
        ZZi=(ind);\
        if(ZZa->waterM<ZZi)ZZa->waterM=ZZi;\
        if(ZZk<0){\
            for(ZZk=0;ZZk<ZZi;ZZk++){\
                (elem)=(str2Type *)(&(ZZa->array[ZZk*(ZZa->size)]));\
                if(bck)bck((void*)(elem),ZZk);\
            }\
        }\
        (elem)=(str2Type *)(&(ZZa->array[ZZi*(ZZa->size)]));\
    }\
}
#define ZZ_PUSH_ARRAY(id,obj,elem) \
ZZZ_PUSH_ARRAY(id,ZZFT(2,id),ZZFP(ZZa,id),obj,elem)

#define ZZZ_PUSH_ARRAY(id,str2Type,aPtr,obj,elem) \
{ str2Type *ZZs; ZZarray *ZZa;\
    ZZa=(obj)->aPtr;\
    if(ZZa){\
        ZZ_INDEX_ARRAY(id,obj,ZZa->waterM+1,ZZs);\
        if(!ZZerrFLG) (*ZZs)=(*(elem));\
    }\
    else {\
       ZZerrFLG=04;\
       ZZmsgS(24,ZZ_STRINGIT(id));\
    }\
}
#define ZZ_POP_ARRAY(id,obj,elem) \
ZZZ_POP_ARRAY(id,ZZFT(2,id),ZZFP(ZZa,id),obj,elem)

#define ZZZ_POP_ARRAY(id,str2Type,aPtr,obj,elem) \
{ ZZarray *ZZa;\
    ZZa=(obj)->aPtr;\
    if(ZZa){\
        if(ZZa->waterM>=0){\
            (elem)=(str2Type *)(&(ZZa->array[(ZZa->waterM)*(ZZa->size)]));\
            (ZZa->waterM)--;\
        }\
        else (elem)=NULL;\
    }\
    else {\
       ZZerrFLG=04;\
       ZZmsgS(24,ZZ_STRINGIT(id));\
    }\
}
#define ZZ_SORT_ARRAY(id,sortFun,obj) \
ZZZ_SORT_ARRAY(id,ZZFP(ZZa,id),ZZFT(2,id),sortFun,obj) 

#ifdef GNUPLUS
extern "C" {
    QSORT_TYPE qsort(void *,unsigned int,unsigned int,
                                 int(*)(const void *, const void *));
} 
#endif

#define ZZZ_SORT_ARRAY(id,aPtr,str2Type,sortFun,obj) \
{ ZZarray *ZZa; ZZFUN_QSORT \
    ZZa=(obj)->aPtr;\
    if(ZZa){\
      if(ZZa->waterM>0)\
            qsort(ZZa->array,ZZa->waterM+1,(ZZint)sizeof(str2Type),(ZZTsortExt)sortFun);\
    }\
    else {\
      ZZerrFLG=04;\
      ZZmsgS(24,ZZ_STRINGIT(id));\
    }\
}

#define ZZ_RESET_ARRAY(id,obj,newWater,newInc) \
{ZZarray *ZZa; \
    ZZa=(obj)->ZZFP(ZZa,id); \
    if(ZZa){ZZa->waterM=(newWater); ZZa->incr=(newInc);}\
}
#define ZZ_IN_HEAP(id,sortFun,obj,entry,bck) \
ZZZ_IN_HEAP(id,ZZFP(ZZa,id),ZZFT(2,id),sortFun,obj,entry,bck)

#define ZZZ_IN_HEAP(id,aPtr,str2Type,sortFun,obj,entry,bck) \
{ str2Type *ZZs; ZZarray *ZZa; ZZint ZZn;\
  ZZint ZZFUN_upHeap();\
    ZZa=(obj)->aPtr;\
    if(ZZa){\
        ZZn=ZZa->waterM+1;\
        ZZ_INDEX_HEAP(id,obj,ZZn,ZZs,bck);\
        if(!ZZ_ERROR){\
            (*ZZs)=(*(entry));\
            if(bck)bck((void *)ZZs,ZZn);\
            ZZupHeap(ZZa,ZZn,sortFun,bck);\
        }\
    }\
    else {\
        ZZerrFLG=04;\
        ZZmsgS(25,ZZ_STRINGIT(id));\
    }\
}
#define ZZ_OUT_HEAP(id,sortFun,obj,top,bck) \
ZZZ_OUT_HEAP(id,ZZFP(ZZa,id),ZZFT(2,id),sortFun,obj,top,bck)

#define ZZZ_OUT_HEAP(id,aPtr,str2Type,sortFun,obj,top,bck) \
{ str2Type *ZZs; ZZarray *ZZa;\
  ZZint ZZFUN_downHeap();\
    ZZa=(obj)->aPtr;\
    if(ZZa){\
        if(ZZa->waterM>=0){\
            ZZs=(str2Type *)(ZZa->array);\
            *(top)=ZZs[0];\
            if(bck)bck((void*)ZZs,-1);\
            ZZs[0]=ZZs[ZZa->waterM];\
            if(bck)bck((void*)ZZs,0);\
            (ZZa->waterM)--;\
            ZZdownHeap(ZZa,0,sortFun,bck);\
        }\
    }\
    else ZZerrFLG=04;\
}
#define ZZ_UPDATE_HEAP(id,sortFun,obj,ind,bck) \
ZZZ_UPDATE_HEAP(id,ZZFP(ZZa,id),sortFun,obj,ind,bck)

#define ZZZ_UPDATE_HEAP(id,aPtr,sortFun,obj,ind,bck) \
{ ZZarray *ZZa;\
  ZZint ZZi,ZZn,ZZFUN_upHeap();\
  ZZint ZZFUN_downHeap();\
    ZZn=ind;\
    ZZa=(obj)->aPtr;\
    if(ZZa){\
        ZZi=ZZdownHeap(ZZa,ZZn,sortFun,bck);\
        if(ZZi==ZZn)(void)ZZupHeap(ZZa,ZZn,sortFun,bck);\
    }\
    else ZZerrFLG=04;\
}
#define ZZ_DELETE_HEAP(id,sortFun,obj,ind,bck) \
ZZZ_DELETE_HEAP(id,ZZFP(ZZa,id),ZZFT(2,id),sortFun,obj,ind,bck) 

#ifdef ZZnoCheck
#define ZZZ_DELETE_HEAP(id,aPtr,str2Type,sortFun,obj,ind,bck) \
{ ZZarray *ZZa; str2Type *ZZs; int ZZw;\
    ZZw=ind;\
    ZZa=(obj)->aPtr;\
    ZZs=(str2Type *)(ZZa->array);\
    if(bck)(*bck)((void*)(&(ZZs[ZZw])),-1);\
    ZZs[ZZw]=ZZs[ZZa->waterM];\
    if(bck)(*bck)((void*)(&(ZZs[ZZw])),ZZw);\
    (ZZa->waterM)--;\
    if(ZZw<=ZZa->waterM){ZZ_UPDATE_HEAP(id,sortFun,obj,ZZw,bck);}\
}
#else
#define ZZZ_DELETE_HEAP(id,aPtr,str2Type,sortFun,obj,ind,bck) \
{ ZZarray *ZZa; str2Type *ZZs; ZZint ZZw;\
    ZZw=ind;\
    ZZa=(obj)->aPtr;\
    ZZs=(str2Type *)(ZZa->array);\
    if(ZZa){\
        if(bck)bck((void*)(&(ZZs[ZZw])),-1);\
        ZZs[ZZw]=ZZs[ZZa->waterM];\
        if(bck)bck((void*)(&(ZZs[ZZw])),ZZw);\
        (ZZa->waterM)--;\
        if(ZZw<=ZZa->waterM){ZZ_UPDATE_HEAP(id,sortFun,obj,ZZw,bck);}\
    }\
    else {\
       ZZerrFLG=04;\
       ZZmsgS(25,ZZ_STRINGIT(id));\
    }\
}
#endif
#ifdef ZZ_ANSI
#define ZZ_ORG_HASH(id,strType1,strType2) \
int ZZFP(zz_hashInd_,id)(char *, int);\
int ZZFP(zz_hashCmp_,id)(char *,char *);
#else
#define ZZ_ORG_HASH(id,strType1,strType2) \
int ZZFP(zz_hashInd_,id)();\
int ZZFP(zz_hashCmp_,id)();
#endif

#define ZZ_HYPER_HASH(id,hType,oType) \
ZZ_BASIC_HASH(id,hType,oType,ZZ_EXTERN,id)

#define ZZ_LOCAL_HASH(id,hType,oType,where) \
ZZ_BASIC_HASH(id,hType,oType,static,where :: id)

#ifdef ZZmain
#define ZZ_BASIC_HASH(id,hType,oType,scope,where) \
class ZZFP(ZZH,id) { \
public: \
    inline ZZint cmp(oType *p1,oType *p2);\
    inline ZZint hash(oType *p,ZZint size);\
    void form(hType *hp,ZZint sz);\
    void *formed(hType *hp){return (void*)(hp->ZZFP(ZZa,id));}\
    void resize(hType *hp,ZZint sz);\
    void add(hType *hp,oType *op);\
    ZZint add2(hType *hp,oType *op,ZZint sameKey);\
    void del(hType *hp,oType *op);\
    ZZint size(hType *hp,ZZint *num);\
    oType *slot(hType *hp,ZZint st);\
    void free(hType *hp);\
    oType *fwd(oType *op){ return(op->ZZFP(ZZf,id));}\
    oType *get(hType *hp,oType *op);\
    void newFun(hType *hp);\
};\
scope ZZFP(ZZH,id) id; \
ZZint ZZFP(zz_hashCmp_,id)(char *p1,char *p2){ \
                               return(id.cmp((oType *)p1,(oType *)p2));} \
ZZint ZZFP(zz_hashInd_,id)(char *p,ZZint size){return(id.hash((oType *)p,size));} \
class ZZFN(id,iterator){ \
   oType *beg;\
   oType *nxt;\
   ZZint iSlot;\
   ZZint sz;\
   hType *hRem;\
public:\
   ZZFN(id,iterator)(oType *p){start(p); }\
   ZZFN(id,iterator)(hType *h){start(h); }\
   ZZFN(id,iterator)(){}\
   void start(oType *p){iSlot= -1; if(p)nxt=where.fwd(p); else nxt=NULL; beg=p;}\
   void start(hType *h){ZZint n; oType *p; hRem=h;\
       sz=where.size(h,&n);\
       for(iSlot=0, p=NULL; iSlot<sz; iSlot++){\
           p=where.slot(h,iSlot);\
           if(p)break;\
       }\
       beg=nxt=p;\
       if(p)nxt=where.fwd(p); \
   }\
   oType* operator++(){oType *p,*s;\
      if(nxt==NULL)return NULL;\
      p=nxt;\
      if(iSlot<0){\
          if(p==beg)nxt=beg=NULL; else nxt=where.fwd(p); return(p);\
      }\
      else {\
          if(p!=beg){\
              nxt=where.fwd(p); return(p);\
          }\
          for(iSlot++, s=NULL; iSlot<sz; iSlot++){\
              s=where.slot(hRem,iSlot);\
              if(s){\
                  beg=s; nxt=where.fwd(s); return p;\
              }\
          }\
          beg=nxt=NULL; return p;\
      }\
   }\
}
#else
#define ZZ_BASIC_HASH(id,hType,oType,scope,where) \
class ZZFP(ZZH,id) { \
public: \
    inline ZZint cmp(oType *p1,oType *p2);\
    inline ZZint hash(oType *p,ZZint size);\
    void form(hType *hp,ZZint sz);\
    void *formed(hType *hp){return (void*)(hp->ZZFP(ZZa,id));}\
    void resize(hType *hp,ZZint sz);\
    void add(hType *hp,oType *op);\
    ZZint add2(hType *hp,oType *op,ZZint sameKey);\
    void del(hType *hp,oType *op);\
    ZZint size(hType *hp,ZZint *num);\
    oType *slot(hType *hp,ZZint st);\
    void free(hType *hp);\
    oType *fwd(oType *op){ return(op->ZZFP(ZZf,id));}\
    oType *get(hType *hp,oType *op);\
    void newFun(hType *hp);\
};\
scope ZZFP(ZZH,id) id; \
ZZint ZZFP(zz_hashCmp_,id)(char *p1,char *p2); \
ZZint ZZFP(zz_hashInd_,id)(char *p,ZZint size); \
class ZZFN(id,iterator){ \
   oType *beg;\
   oType *nxt;\
   ZZint iSlot;\
   ZZint sz;\
   hType *hRem;\
public:\
   ZZFN(id,iterator)(oType *p){start(p); }\
   ZZFN(id,iterator)(hType *h){start(h); }\
   ZZFN(id,iterator)(){}\
   void start(oType *p){iSlot= -1; if(p)nxt=where.fwd(p); else nxt=NULL; beg=p; }\
   void start(hType *h){ZZint n,sz; oType *p; hRem=h;\
       sz=where.size(h,&n);\
       for(iSlot=0, p=NULL; iSlot<sz; iSlot++){\
           p=where.slot(h,iSlot);\
           if(p)break;\
       }\
       beg=nxt=p;\
       if(p)nxt=where.fwd(p); \
   }\
   oType* operator++(){oType *p,*s;\
      if(nxt==NULL)return NULL;\
      p=nxt;\
      if(iSlot<0){\
          if(p==beg)nxt=beg=NULL; else nxt=where.fwd(p); return(p);\
      }\
      else {\
          if(p!=beg){\
              nxt=where.fwd(p); return(p);\
          }\
          for(iSlot++, s=NULL; iSlot<sz; iSlot++){\
              s=where.slot(hRem,iSlot);\
              if(s){\
                  beg=s; nxt=where.fwd(s); return p;\
              }\
          }\
          beg=nxt=NULL; return p;\
      }\
   }\
}
#endif
#define ZZ_FORM_HASH(id,obj,hSize) \
ZZZ_FORM_HASH(id,ZZFP(ZZa,id),ZZFT(X2,id),obj,hSize)

#define ZZZ_FORM_HASH(id,aPtr,objType,obj,hSize) \
{ ZZarray *ZZFUN_foArr(); char **ZZp; ZZint ZZi; static ZZFT(2,id)* sample=NULL;\
    if(!sample)sample=new ZZFT(2,id);\
    if((obj)->aPtr){\
        ZZmsgS(26,ZZ_STRINGIT(id));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else (obj)->aPtr=ZZfoArr(hSize,0,(int)sizeof(char *),-5,\
                              objType,ZZstrList,(char*)sample);\
    if((obj)->aPtr){\
        (obj)->aPtr->waterM=(obj)->aPtr->num;\
        for(ZZi=0,ZZp=(char**)((obj)->aPtr->array);ZZi<(hSize);ZZi++,ZZp++)\
                   *ZZp=NULL;\
    }\
}
/* array cast as (char *) is important for SAVE/OPEN operations */
#define ZZ_SIZE_HASH(id,obj,hSize,hNum) \
ZZZ_SIZE_HASH(ZZFP(ZZa,id),obj,hSize,hNum) 

#define ZZZ_SIZE_HASH(aPtr,obj,hSize,hNum) \
{ZZarray *ZZa; \
    ZZa=(obj)->aPtr; \
    if(ZZa){(hSize)=ZZa->num; (hNum)=ZZa->incr;}\
    else {(hSize)=0;      (hNum)=0;}\
}
#define ZZ_SLOT_HASH(id,obj1,slot,obj2) \
ZZZ_SLOT_HASH(id,ZZFP(ZZa,id),ZZFT(2,id),obj1,slot,obj2)

#define ZZZ_SLOT_HASH(id,aPtr,objType,obj1,slot,obj2) \
{ char **ZZs;\
  if((obj1)->aPtr){\
    if((slot)<0 || (slot)>=(obj1)->aPtr->num)(obj2)=NULL;\
    else {ZZs=(char**)((obj1)->aPtr->array); (obj2)=(objType *)ZZs[slot];}\
  }\
  else (obj2)=NULL;\
}
#define ZZ_A_TRAVERSE_HASH(id,start,pp) \
ZZZ_A_TRAVERSE_HASH(id,ZZFP(ZZf,id),ZZFT(2,id),start,pp)

#define ZZZ_A_TRAVERSE_HASH(id,fwp,strType,start,pp) \
{strType *ZZt;\
    if(start)(pp)=(start)->fwp; else (pp)=NULL;\
    for(;(pp);(pp)=ZZt){ \
	ZZt=(pp)->fwp; if((pp)==(start))ZZt=NULL;
#ifndef ZZ_ANSI
#define ZZ_RESIZE_HASH(id,obj,hSize) \
ZZZ_RESIZE_HASH(id,ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZa,id),\
ZZFP(zz_hashInd_,id),obj,hSize)

#define ZZZ_RESIZE_HASH(id,type2,fwp,aPtr,indF,obj,hSize) \
{int ZZFUN_upHash(),indF(); type2 *ZZp; union {ZZptrIntType l; ZZint i;}u;\
   ZZp=NULL; u.l=(ZZptrIntType)(&(ZZp->fwp))-(ZZptrIntType)(ZZp);\
   ZZupHash((obj)->aPtr,hSize,u.i,indF); \
}
#endif
#ifdef ZZ_ANSI
#define ZZ_RESIZE_HASH(id,obj,hSize) \
ZZZ_RESIZE_HASH(id,ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZa,id),\
ZZFP(zz_hashInd_,id),obj,hSize)

#define ZZZ_RESIZE_HASH(id,type2,fwp,aPtr,indF,obj,hSize) \
{ZZint ZZFUN_upHash(),indF(char *w,ZZint s);\
 type2 *ZZp; union {ZZptrIntType l; ZZint i;}u;\
   ZZp=NULL; u.l=(ZZptrIntType)(&(ZZp->fwp))-(ZZptrIntType)(ZZp);\
   ZZupHash((obj)->aPtr,hSize,u.i,indF); \
}
#endif
#ifndef ZZ_ANSI
#define ZZ_ADD_HASH(id,obj1,obj2) \
ZZZ_ADD_HASH(id,ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZa,id),\
ZZFP(zz_hashInd_,id),ZZFP(zz_hashCmp_,id),obj1,obj2)

#define ZZZ_ADD_HASH(id,type2,fwp,aPtr,indF,cmpF,obj1,obj2) \
{ int ZZi,indF(),cmpF(); char **ZZs; type2 *ZZp,*ZZt;\
  if(!obj1 || !(obj1->aPtr)){ZZerror=ZZerror|010;\
                              ZZmsgS(27,ZZ_STRINGIT(id));}\
  else if((obj2) && !((obj2)->fwp)){\
    ZZi=indF((char *)obj2,(obj1)->aPtr->num);\
    ZZs=(char**)((obj1)->aPtr->array);\
    ZZp=(type2 *)(ZZs[ZZi]);\
    if(ZZp){\
      for(ZZt=ZZp;ZZt;ZZt=ZZt->fwp){\
        if(!cmpF((char *)ZZt,(char *)obj2))break;\
        if(ZZt->fwp==ZZp){ZZt=NULL; break;}\
      }\
      if(!ZZt){(obj2)->fwp=ZZp->fwp; ZZp->fwp=(obj2); ((obj1)->aPtr->incr)++;}\
    }\
    else {ZZs[ZZi]=(char*)(obj2); (obj2)->fwp=(obj2); ((obj1)->aPtr->incr)++;}\
  }\
  else {ZZerror=ZZerror|010; ZZmsgSS(30,(char *)obj2,ZZ_STRINGIT(id));}\
}
#endif

#ifdef ZZ_ANSI
#ifndef ZZcplus
#define ZZ_ADD_HASH(id,obj1,obj2) \
ZZZ_ADD_HASH(id,ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZa,id),\
ZZFP(zz_hashInd_,id),ZZFP(zz_hashCmp_,id),obj1,obj2)

#define ZZZ_ADD_HASH(id,type2,fwp,aPtr,indF,cmpF,obj1,obj2) \
{ int ZZi,indF(char *p,int s),cmpF(char *p1,char *p2);\
  char **ZZs; type2 *ZZp,*ZZt;\
  if(!obj1 || !(obj1->aPtr)){ZZerror=ZZerror|010;\
                              ZZmsgS(27,ZZ_STRINGIT(id));}\
  else if((obj2) && !((obj2)->fwp)){\
    ZZi=indF((char *)(obj2),(obj1)->aPtr->num);\
    ZZs=(char**)((obj1)->aPtr->array);\
    ZZp=(type2 *)(ZZs[ZZi]);\
    if(ZZp){\
      for(ZZt=ZZp;ZZt;ZZt=ZZt->fwp){\
        if(!cmpF((char *)ZZt,(char *)(obj2)))break;\
        if(ZZt->fwp==ZZp){ZZt=NULL; break;}\
      }\
      if(!ZZt){(obj2)->fwp=ZZp->fwp; ZZp->fwp=(obj2); ((obj1)->aPtr->incr)++;}\
    }\
    else {ZZs[ZZi]=(char*)(obj2); (obj2)->fwp=(obj2); ((obj1)->aPtr->incr)++;}\
  }\
  else {ZZerror=ZZerror|010; ZZmsgSS(30,(char *)obj2,ZZ_STRINGIT(id));}\
}
#endif
#endif

#ifdef ZZcplus
#define ZZ_ADD_HASH(id,obj1,obj2) \
ZZZ_ADD_HASH(id,ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZa,id),\
ZZFP(zz_hashInd_,id),ZZFP(zz_hashCmp_,id),obj1,obj2)

#define ZZZ_ADD_HASH(id,type2,fwp,aPtr,indF,cmpF,obj1,obj2) \
{ ZZint ZZi;\
  char **ZZs; type2 *ZZp,*ZZt;\
  if(!obj1 || !(obj1->aPtr)){ZZerror=ZZerror|010;\
                              ZZmsgS(27,ZZ_STRINGIT(id));}\
  else if((obj2) && !((obj2)->fwp)){\
    ZZi=indF((char *)(obj2),(obj1)->aPtr->num);\
    ZZs=(char**)((obj1)->aPtr->array);\
    ZZp=(type2 *)(ZZs[ZZi]);\
    if(ZZp){\
      for(ZZt=ZZp;ZZt;ZZt=ZZt->fwp){\
        if(!cmpF((char *)ZZt,(char *)(obj2)))break;\
        if(ZZt->fwp==ZZp){ZZt=NULL; break;}\
      }\
      if(!ZZt){(obj2)->fwp=ZZp->fwp; ZZp->fwp=(obj2); ((obj1)->aPtr->incr)++;}\
    }\
    else {ZZs[ZZi]=(char*)(obj2); (obj2)->fwp=(obj2); ((obj1)->aPtr->incr)++;}\
  }\
  else {ZZerror=ZZerror|010; ZZmsgSS(30,(char *)obj2,ZZ_STRINGIT(id));}\
}
#endif
#ifndef ZZ_ANSI
#define ZZ_ADD2_HASH(id,obj1,obj2,sameKey,status) \
ZZZ_ADD2_HASH(id,ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZa,id),\
ZZFP(zz_hashInd_,id),ZZFP(zz_hashCmp_,id),obj1,obj2,sameKey,status)

#define ZZZ_ADD2_HASH(id,type2,fwp,aPtr,indF,cmpF,obj1,obj2,sameKey,status) \
{ int ZZi,indF(),cmpF(); char **ZZs; type2 *ZZp,*ZZt;\
  status=0; \
  if(!obj1 || !(obj1->aPtr)){ZZerror=ZZerror|010;\
                              ZZmsgS(27,ZZ_STRINGIT(id));}\
  else if((obj2) && !((obj2)->fwp)){\
    ZZi=indF((char *)obj2,(obj1)->aPtr->num);\
    ZZs=(char**)((obj1)->aPtr->array);\
    ZZp=(type2 *)(ZZs[ZZi]);\
    if(ZZp){\
      if(sameKey)ZZt=NULL; \
      else { \
          for(ZZt=ZZp;ZZt;ZZt=ZZt->fwp){\
            if(!cmpF((char *)ZZt,(char *)obj2))break;\
            if(ZZt->fwp==ZZp){ZZt=NULL; break;}\
          }\
      }\
      if(!ZZt){(obj2)->fwp=ZZp->fwp; ZZp->fwp=(obj2); ((obj1)->aPtr->incr)++;}\
      else status=1; \
    }\
    else {ZZs[ZZi]=(char*)(obj2); (obj2)->fwp=(obj2); ((obj1)->aPtr->incr)++;}\
  }\
  else {ZZerror=ZZerror|010; ZZmsgSS(30,(char *)obj2,ZZ_STRINGIT(id));};\
}
#endif

#ifdef ZZ_ANSI
#ifndef ZZcplus
#define ZZ_ADD2_HASH(id,obj1,obj2,sameKey,status) \
ZZZ_ADD2_HASH(id,ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZa,id),\
ZZFP(zz_hashInd_,id),ZZFP(zz_hashCmp_,id),obj1,obj2,sameKey,status)

#define ZZZ_ADD2_HASH(id,type2,fwp,aPtr,indF,cmpF,obj1,obj2,sameKey,status) \
{ int ZZi,indF(char *p,int s),cmpF(char *p1,char *p2);\
  char **ZZs; type2 *ZZp,*ZZt;\
  status=0; \
  if(!obj1 || !(obj1->aPtr)){ZZerror=ZZerror|010;\
                              ZZmsgS(27,ZZ_STRINGIT(id));}\
  else if((obj2) && !((obj2)->fwp)){\
    ZZi=indF((char *)(obj2),(obj1)->aPtr->num);\
    ZZs=(char**)((obj1)->aPtr->array);\
    ZZp=(type2 *)(ZZs[ZZi]);\
    if(ZZp){\
      if(sameKey)ZZt=NULL; \
      else { \
          for(ZZt=ZZp;ZZt;ZZt=ZZt->fwp){\
            if(!cmpF((char *)ZZt,(char *)(obj2)))break;\
            if(ZZt->fwp==ZZp){ZZt=NULL; break;}\
          }\
      }\
      if(!ZZt){(obj2)->fwp=ZZp->fwp; ZZp->fwp=(obj2); ((obj1)->aPtr->incr)++;}\
      else status=1; \
    }\
    else {ZZs[ZZi]=(char*)(obj2); (obj2)->fwp=(obj2); ((obj1)->aPtr->incr)++;}\
  }\
  else {ZZerror=ZZerror|010; ZZmsgSS(30,(char *)obj2,ZZ_STRINGIT(id));};\
}
#endif
#endif

#ifdef ZZcplus
#define ZZ_ADD2_HASH(id,obj1,obj2,sameKey,status) \
ZZZ_ADD2_HASH(id,ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZa,id),\
ZZFP(zz_hashInd_,id),ZZFP(zz_hashCmp_,id),obj1,obj2,sameKey,status)

#define ZZZ_ADD2_HASH(id,type2,fwp,aPtr,indF,cmpF,obj1,obj2,sameKey,status) \
{ ZZint ZZi;\
  char **ZZs; type2 *ZZp,*ZZt;\
  status=0; \
  if(!obj1 || !(obj1->aPtr)){ZZerror=ZZerror|010;\
                              ZZmsgS(27,ZZ_STRINGIT(id));}\
  else if((obj2) && !((obj2)->fwp)){\
    ZZi=indF((char *)(obj2),(obj1)->aPtr->num);\
    ZZs=(char**)((obj1)->aPtr->array);\
    ZZp=(type2 *)(ZZs[ZZi]);\
    if(ZZp){\
      if(sameKey)ZZt=NULL; \
      else { \
          for(ZZt=ZZp;ZZt;ZZt=ZZt->fwp){\
            if(!cmpF((char *)ZZt,(char *)(obj2)))break;\
            if(ZZt->fwp==ZZp){ZZt=NULL; break;}\
          }\
      }\
      if(!ZZt){(obj2)->fwp=ZZp->fwp; ZZp->fwp=(obj2); ((obj1)->aPtr->incr)++;}\
      else status=1; \
    }\
    else {ZZs[ZZi]=(char*)(obj2); (obj2)->fwp=(obj2); ((obj1)->aPtr->incr)++;}\
  }\
  else {ZZerror=ZZerror|010; ZZmsgSS(30,(char *)obj2,ZZ_STRINGIT(id));};\
}
#endif
#ifndef ZZ_ANSI
#define ZZ_DELETE_HASH(id,obj1,obj2) \
ZZZ_DELETE_HASH(id,ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZa,id),\
ZZFP(zz_hashInd_,id),obj1,obj2)

#define ZZZ_DELETE_HASH(id,type2,fwp,aPtr,indF,obj1,obj2) \
{ ZZint ZZi,indF(); char **ZZs; type2 *ZZp,*ZZt;\
  if((obj2) && (obj2)->fwp){\
    ZZi=indF(obj2,(obj1)->aPtr->num);\
    ZZs=(char**)((obj1)->aPtr->array);\
    ZZp=(type2 *)(ZZs[ZZi]);\
    if(ZZp){\
      for(ZZt=ZZp;ZZt;ZZt=ZZt->fwp){\
        if(ZZt->fwp==(obj2))break;\
        if(ZZt->fwp==ZZp){ZZt=NULL; break;}\
      }\
      if(ZZt){\
        ((obj1)->aPtr->incr)--;\
        if(ZZp==(obj2))ZZp=ZZp->fwp;\
        if(ZZp==(obj2))ZZp=NULL;\
        ZZs[ZZi]=(char *)ZZp;\
        if(ZZp)ZZt->fwp=(obj2)->fwp;\
        (obj2)->fwp=NULL;\
      }\
      else {ZZerror=ZZerror|010; ZZmsgSS(32,(char *)obj2,ZZ_STRINGIT(id));}\
    }\
    else {ZZerror=ZZerror|010; ZZmsgSS(33,(char *)obj2,ZZ_STRINGIT(id));}\
  }\
  else {ZZmsgSS(36,(char *)obj2,ZZ_STRINGIT(id));}\
}
#endif

#ifdef ZZ_ANSI
#ifndef ZZcplus
#define ZZ_DELETE_HASH(id,obj1,obj2) \
ZZZ_DELETE_HASH(id,ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZa,id),\
ZZFP(zz_hashInd_,id),obj1,obj2)

#define ZZZ_DELETE_HASH(id,type2,fwp,aPtr,indF,obj1,obj2) \
{ int ZZi,indF(char *w,int s); char **ZZs; type2 *ZZp,*ZZt;\
  if((obj2) && (obj2)->fwp){\
    ZZi=indF((char *)(obj2),(obj1)->aPtr->num);\
    ZZs=(char**)((obj1)->aPtr->array);\
    ZZp=(type2 *)(ZZs[ZZi]);\
    if(ZZp){\
      for(ZZt=ZZp;ZZt;ZZt=ZZt->fwp){\
        if(ZZt->fwp==(obj2))break;\
        if(ZZt->fwp==ZZp){ZZt=NULL; break;}\
      }\
      if(ZZt){\
        ((obj1)->aPtr->incr)--;\
        if(ZZp==(obj2))ZZp=ZZp->fwp;\
        if(ZZp==(obj2))ZZp=NULL;\
        ZZs[ZZi]=(char *)ZZp;\
        if(ZZp)ZZt->fwp=(obj2)->fwp;\
        (obj2)->fwp=NULL;\
      }\
      else {ZZerror=ZZerror|010; ZZmsgSS(32,(char *)obj2,ZZ_STRINGIT(id));}\
    }\
    else {ZZerror=ZZerror|010; ZZmsgSS(33,(char *)obj2,ZZ_STRINGIT(id));}\
  }\
  else {ZZmsgSS(36,(char *)obj2,ZZ_STRINGIT(id));}\
}
#endif
#endif

#ifdef ZZcplus
#define ZZ_DELETE_HASH(id,obj1,obj2) \
ZZZ_DELETE_HASH(id,ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZa,id),\
ZZFP(zz_hashInd_,id),obj1,obj2)

#define ZZZ_DELETE_HASH(id,type2,fwp,aPtr,indF,obj1,obj2) \
{ ZZint ZZi; char **ZZs; type2 *ZZp,*ZZt;\
  if((obj2) && (obj2)->fwp){\
    ZZi=indF((char *)(obj2),(obj1)->aPtr->num);\
    ZZs=(char**)((obj1)->aPtr->array);\
    ZZp=(type2 *)(ZZs[ZZi]);\
    if(ZZp){\
      for(ZZt=ZZp;ZZt;ZZt=ZZt->fwp){\
        if(ZZt->fwp==(obj2))break;\
        if(ZZt->fwp==ZZp){ZZt=NULL; break;}\
      }\
      if(ZZt){\
        ((obj1)->aPtr->incr)--;\
        if(ZZp==(obj2))ZZp=ZZp->fwp;\
        if(ZZp==(obj2))ZZp=NULL;\
        ZZs[ZZi]=(char *)ZZp;\
        if(ZZp)ZZt->fwp=(obj2)->fwp;\
        (obj2)->fwp=NULL;\
      }\
      else {ZZerror=ZZerror|010; ZZmsgSS(32,(char *)obj2,ZZ_STRINGIT(id));}\
    }\
    else {ZZerror=ZZerror|010; ZZmsgSS(33,(char *)obj2,ZZ_STRINGIT(id));}\
  }\
  else {ZZmsgSS(36,(char *)obj2,ZZ_STRINGIT(id));}\
}
#endif
#ifndef ZZ_ANSI
#define ZZ_GET_HASH(id,obj1,key,obj2) \
ZZZ_GET_HASH(id,ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZa,id),\
ZZFP(zz_hashCmp_,id),ZZFP(zz_hashInd_,id),obj1,key,obj2)

#define ZZZ_GET_HASH(id,type2,fwp,aPtr,cmpF,indF,obj1,key,obj2) \
{ int ZZi,indF(),cmpF(); char **ZZs; type2 *ZZp;\
  if((obj1)->aPtr){\
      ZZs=(char**)((obj1)->aPtr->array);\
      ZZi=indF(key,(obj1)->aPtr->num);\
      ZZp=(type2 *)(ZZs[ZZi]);\
      for((obj2)=ZZp;(obj2);){\
        if(!cmpF((obj2),key))break;\
        if((obj2)->fwp==ZZp)(obj2)=NULL; else (obj2)=(obj2)->fwp;\
      }\
  } \
  else {ZZmsgS(46,ZZ_STRINGIT(id)); (obj2)=NULL;}\
}
#endif

#ifdef ZZ_ANSI
#ifndef ZZcplus
#define ZZ_GET_HASH(id,obj1,key,obj2) \
ZZZ_GET_HASH(id,ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZa,id),\
ZZFP(zz_hashCmp_,id),ZZFP(zz_hashInd_,id),obj1,key,obj2)

#define ZZZ_GET_HASH(id,type2,fwp,aPtr,cmpF,indF,obj1,key,obj2) \
{int ZZi,indF(char *w,int s),cmpF(char *p1,char *p2);\
char **ZZs; type2 *ZZp;\
  if((obj1)->aPtr){\
      ZZs=(char**)((obj1)->aPtr->array);\
      ZZi=indF((char *)(key),(obj1)->aPtr->num);\
      ZZp=(type2 *)(ZZs[ZZi]);\
      for((obj2)=ZZp;(obj2);){\
        if(!cmpF((char *)(obj2),(char *)(key)))break;\
        if((obj2)->fwp==ZZp)(obj2)=NULL; else (obj2)=(obj2)->fwp;\
      }\
  } \
  else {ZZmsgS(46,ZZ_STRINGIT(id)); (obj2)=NULL;}\
}
#endif
#endif

#ifdef ZZcplus
#define ZZ_GET_HASH(id,obj1,key,obj2) \
ZZZ_GET_HASH(id,ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZa,id),\
ZZFP(zz_hashCmp_,id),ZZFP(zz_hashInd_,id),obj1,key,obj2)

#define ZZZ_GET_HASH(id,type2,fwp,aPtr,cmpF,indF,obj1,key,obj2) \
{ZZint ZZi;\
char **ZZs; type2 *ZZp;\
  if((obj1)->aPtr){\
      ZZs=(char**)((obj1)->aPtr->array);\
      ZZi=indF((char *)(key),(obj1)->aPtr->num);\
      ZZp=(type2 *)(ZZs[ZZi]);\
      for((obj2)=ZZp;(obj2);){\
        if(!cmpF((char *)(obj2),(char *)(key)))break;\
        if((obj2)->fwp==ZZp)(obj2)=NULL; else (obj2)=(obj2)->fwp;\
      }\
  } \
  else {ZZmsgS(46,ZZ_STRINGIT(id)); (obj2)=NULL;}\
}
#endif
#define ZZ_FREE_HASH(id,obj) \
ZZZ_FREE_HASH(id,ZZFT(2,id),ZZFP(ZZa,id),ZZFP(ZZf,id),obj)

#define ZZZ_FREE_HASH(id,type2,aPtr,fwp,obj) \
{ ZZarray *ZZFUN_frHash(); union{unsigned ZZlong l;unsigned ZZint i;}u; type2 *ZZp;\
    ZZp=NULL;\
    u.l= ZZptrToLong((char *)(&(ZZp->fwp))) - ZZptrToLong((char *)ZZp);\
    if((obj)->aPtr)(obj)->aPtr=ZZfrHash((obj)->aPtr,u.i);\
}
#define ZZ_ORG_1_TO_1(id,type1,type2,type3)
/* ZZ_ORG_1_TO_1 */
#define ZZ_ORG_1_TO_N(id,type1,type2,type3)
/* ZZ_ORG_1_TO_N */
#define ZZ_ORG_M_TO_1(id,type1,type2,type3)
/* ZZ_ORG_M_TO_1 */
#define ZZ_ORG_M_TO_N(id,type1,type2,type3)
/* ZZ_ORG_M_TO_N */
#define ZZ_HYPER_1_TO_1(id,sType,rType,tType) \
ZZ_BASIC_1_TO_1(id,sType,rType,tType,ZZ_EXTERN,id)

#define ZZ_LOCAL_1_TO_1(id,sType,rType,tType,where) \
ZZ_BASIC_1_TO_1(id,sType,rType,tType,static,where :: id)

#define ZZ_BASIC_1_TO_1(id,sType,rType,tType,scope,where) \
class ZZFP(ZZH,id) { \
  friend class sType;\
  friend class rType;\
  friend class tType;\
public: \
  void add(sType *s,rType *r,tType *t);\
  void del(rType *r);\
  sType *source(rType *r){sType *s; ZZ_SOURCE_1_TO_1(id,r,s); return(s);}\
  tType *target(rType *r){tType *t; ZZ_TARGET_1_TO_1(id,r,t); return(t);}\
  rType *fwd(sType *s){rType *r; ZZ_FORWARD_1_TO_1(id,s,r); return(r);}\
  rType *bwd(tType *t){rType *r; ZZ_BACKWARD_1_TO_1(id,t,r); return(r);}\
};\
scope ZZFP(ZZH,id) id
#define ZZ_HYPER_1_TO_N(id,sType,rType,tType) \
ZZ_BASIC_1_TO_N(id,sType,rType,tType,ZZ_EXTERN,id)

#define ZZ_LOCAL_1_TO_N(id,sType,rType,tType) \
ZZ_BASIC_1_TO_N(id,sType,rType,tType,static,where :: id)

#define ZZ_BASIC_1_TO_N(id,sType,rType,tType,scope,where) \
class ZZFP(ZZH,id) { \
  friend class sType;\
  friend class rType;\
  friend class tType;\
public: \
  void add(sType *s,rType *r,tType *t);\
  void del(rType *r);\
  sType *source(rType *r){sType *s; ZZ_SOURCE_1_TO_N(id,r,s); return(s);}\
  tType *target(rType *r){tType *t; ZZ_TARGET_1_TO_N(id,r,t); return(t);}\
  rType *fwd(sType *s){rType *r; ZZ_FORWARD_1_TO_N(id,s,r); return(r);}\
  rType *bwd(tType *t){rType *r; ZZ_BACKWARD_1_TO_N(id,t,r); return(r);}\
  rType *nxtOnSour(rType *r){rType *n;\
                        if(r)n=r->ZZFP(ZZs,id); else n=NULL; return(n);}\
  rType *preOnSour(rType *r){rType *n;\
                        if(r)n=r->ZZFP(ZZr,id); else n=NULL; return(n);}\
};\
scope ZZFP(ZZH,id) id; \
class ZZFN(id,iterator){ \
   rType *beg;\
   rType *nxt;\
public:\
   ZZFN(id,iterator)(sType *s){start(s);}\
   void start(sType *s){nxt=NULL; if(s)beg=where.fwd(s); else beg=NULL;}\
   rType* operator++(){rType *p;\
      if(nxt)p=nxt; else if(beg)p=where.nxtOnSour(beg); else p=NULL;\
      if(p==beg)nxt=beg=NULL; else nxt=where.nxtOnSour(p); return(p);}\
   rType* operator--(){rType *p;\
      if(nxt)p=nxt; else if(beg){p=beg; beg=where.nxtOnSour(beg);} else p=NULL;\
      if(p==beg)nxt=beg=NULL; else nxt=where.preOnSour(p); return(p);}\
}
#define ZZ_HYPER_M_TO_1(id,sType,rType,tType) \
ZZ_BASIC_M_TO_1(id,sType,rType,tType,ZZ_EXTERN,id)

#define ZZ_LOCAL_M_TO_1(id,sType,rType,tType,where) \
ZZ_BASIC_M_TO_1(id,sType,rType,tType,static,where :: id)

#define ZZ_BASIC_M_TO_1(id,sType,rType,tType,scope,where) \
class ZZFP(ZZH,id) { \
  friend class sType;\
  friend class rType;\
  friend class tType;\
public: \
  void add(sType *s,rType *r,tType *t);\
  void del(rType *r);\
  sType *source(rType *r){sType *s; ZZ_SOURCE_M_TO_1(id,r,s); return(s);}\
  tType *target(rType *r){tType *t; ZZ_TARGET_M_TO_1(id,r,t); return(t);}\
  rType *fwd(sType *s){rType *r; ZZ_FORWARD_M_TO_1(id,s,r); return(r);}\
  rType *bwd(tType *t){rType *r; ZZ_BACKWARD_M_TO_1(id,t,r); return(r);}\
  rType *nxtOnTarg(rType *r){rType *n;\
                        if(r)n=r->ZZFP(ZZs,id); else n=NULL; return(n);}\
  rType *preOnTarg(rType *r){rType *n;\
                        if(r)n=r->ZZFP(ZZr,id); else n=NULL; return(n);}\
};\
scope ZZFP(ZZH,id) id; \
class ZZFN(id,iterator){ \
   rType *beg;\
   rType *nxt;\
public:\
   ZZFN(id,iterator)(tType *t){start(t);}\
   void start(tType *t){nxt=NULL; if(t)beg=where.bwd(t); else beg=NULL;}\
   rType* operator++(){rType *p;\
      if(nxt)p=nxt; else if(beg)p=where.nxtOnTarg(beg); else p=NULL;\
      if(p==beg)nxt=beg=NULL; else nxt=where.nxtOnTarg(p); return(p);}\
   rType* operator--(){rType *p;\
      if(nxt)p=nxt; else if(beg){p=beg; beg=where.nxtOnTarg(beg);} else p=NULL;\
      if(p==beg)nxt=beg=NULL; else nxt=where.preOnTarg(p); return(p);}\
}
#define ZZ_HYPER_M_TO_N(id,sType,rType,tType) \
ZZ_BASIC_M_TO_N(id,sType,rType,tType,ZZ_EXTERN,id)

#define ZZ_LOCAL_M_TO_N(id,sType,rType,tType,where) \
ZZ_BASIC_M_TO_N(id,sType,rType,tType,static,where :: id)

#define ZZ_BASIC_M_TO_N(id,sType,rType,tType,scope,where) \
class ZZFP(ZZH,id) { \
  friend class sType;\
  friend class rType;\
  friend class tType;\
public: \
  void add(sType *s,rType *r,tType *t);\
  void del(rType *r);\
  sType *source(rType *r){sType *s; ZZ_SOURCE_M_TO_N(id,r,s); return(s);}\
  tType *target(rType *r){tType *t; ZZ_TARGET_M_TO_N(id,r,t); return(t);}\
  rType *fwd(sType *s){rType *r; ZZ_FORWARD_M_TO_N(id,s,r); return(r);}\
  rType *bwd(tType *t){rType *r; ZZ_BACKWARD_M_TO_N(id,t,r); return(r);}\
  rType *nxtOnTarg(rType *r){rType *n;\
                        if(r)n=r->ZZFP(ZZs,id); else n=NULL; return(n);}\
  rType *preOnTarg(rType *r){rType *n;\
                        if(r)n=r->ZZFP(ZZw,id); else n=NULL; return(n);}\
  rType *nxtOnSour(rType *r){rType *n;\
                        if(r)n=r->ZZFP(ZZr,id); else n=NULL; return(n);}\
  rType *preOnSour(rType *r){rType *n;\
                        if(r)n=r->ZZFP(ZZv,id); else n=NULL; return(n);}\
};\
ZZ_EXTERN ZZFP(ZZH,id) id; \
class ZZFN(id,sIterator){ \
   rType *beg;\
   rType *nxt;\
public:\
   ZZFN(id,sIterator)(){beg=nxt=NULL;}\
   ZZFN(id,sIterator)(sType *s){start(s);}\
   void start(sType *s){nxt=NULL; if(s)beg=where.fwd(s); else beg=NULL;}\
   rType* operator++(){rType *p;\
      if(nxt)p=nxt; else if(beg)p=where.nxtOnSour(beg); else p=NULL;\
      if(p==beg)nxt=beg=NULL; else nxt=where.nxtOnSour(p); return(p);}\
   rType* operator--(){rType *p;\
      if(nxt)p=nxt; else if(beg){p=beg; beg=where.nxtOnSour(beg);} else p=NULL;\
      if(p==beg)nxt=beg=NULL; else nxt=where.preOnSour(p); return(p);}\
};\
class ZZFN(id,tIterator){ \
   rType *beg;\
   rType *nxt;\
public:\
   ZZFN(id,tIterator)(){beg=nxt=NULL;}\
   ZZFN(id,tIterator)(tType *t){start(t);}\
   void start(tType *t){nxt=NULL; if(t)beg=where.bwd(t); else beg=NULL;}\
   rType* operator++(){rType *p;\
      if(nxt)p=nxt; else if(beg)p=where.nxtOnTarg(beg); else p=NULL;\
      if(p==beg)nxt=beg=NULL; else nxt=where.nxtOnTarg(p); return(p);}\
   rType* operator--(){rType *p;\
      if(nxt)p=nxt; else if(beg){p=beg; beg=where.nxtOnTarg(beg);} else p=NULL;\
      if(p==beg)nxt=beg=NULL; else nxt=where.preOnTarg(p); return(p);}\
}
#define ZZ_TARGET(id,relation,target) \
ZZFN(ZZ_TARGET,id)(id,relation,target)
#define ZZ_SOURCE(id,relation,source) \
ZZFN(ZZ_SOURCE,id)(id,relation,source)
#define ZZ_ADD_RELATION(id,source,relation,target) \
ZZFN(ZZ_ADD_RELATION,id)(id,source,relation,target)
#define ZZ_DELETE_RELATION(id,relation) \
ZZFN(ZZ_DELETE_RELATION,id)(id,relation)
#define ZZF_ADD_RELATION(id,source,relation,target) \
ZZFN(ZZF_ADD_RELATION,id)(id,source,relation,target)
#define ZZF_DELETE_RELATION(id,relation) \
ZZFN(ZZF_DELETE_RELATION,id)(id,relation)
#define ZZ_TARGET_1_TO_1(id,rel,targ) \
ZZZ_TARGET_1_TO_1(ZZFP(ZZy,id),rel,targ)

#define ZZZ_TARGET_1_TO_1(trg,rel,targ) {(targ)=(rel)->trg;}
#define ZZ_TARGET_1_TO_N(id,rel,targ) \
ZZZ_TARGET_1_TO_N(ZZFP(ZZy,id),rel,targ)

#define ZZZ_TARGET_1_TO_N(trg,rel,targ) {(targ)=(rel)->trg;}
#define ZZ_TARGET_M_TO_1(id,rel,targ) \
ZZZ_TARGET_M_TO_1(ZZFP(ZZy,id),rel,targ)

#define ZZZ_TARGET_M_TO_1(trg,rel,targ) {(targ)=(rel)->trg;}
#define ZZ_TARGET_M_TO_N(id,rel,targ) \
ZZZ_TARGET_M_TO_N(ZZFP(ZZy,id),rel,targ)

#define ZZZ_TARGET_M_TO_N(trg,rel,targ) {(targ)=(rel)->trg;}
#define ZZ_SOURCE_1_TO_1(id,rel,sour) \
ZZZ_SOURCE_1_TO_1(ZZFP(ZZx,id),rel,sour)

#define ZZZ_SOURCE_1_TO_1(src,rel,sour) {(sour)=(rel)->src;}
#define ZZ_SOURCE_1_TO_N(id,rel,sour) \
ZZZ_SOURCE_1_TO_N(ZZFP(ZZx,id),rel,sour)

#define ZZZ_SOURCE_1_TO_N(src,rel,sour) {(sour)=(rel)->src;}
#define ZZ_SOURCE_M_TO_1(id,rel,sour) \
ZZZ_SOURCE_M_TO_1(ZZFP(ZZx,id),rel,sour)

#define ZZZ_SOURCE_M_TO_1(src,rel,sour) {(sour)=(rel)->src;}
#define ZZ_SOURCE_M_TO_N(id,rel,sour) \
ZZZ_SOURCE_M_TO_N(ZZFP(ZZx,id),rel,sour)

#define ZZZ_SOURCE_M_TO_N(src,rel,sour) {(sour)=(rel)->src;}
#define ZZ_FORWARD_1_TO_1(id,sour,rel) \
ZZZ_FORWARD_1_TO_1(ZZFP(ZZf,id),sour,rel)

#define ZZZ_FORWARD_1_TO_1(nxt,sour,rel) {(rel)=(sour)->nxt;}
#define ZZ_FORWARD_1_TO_N(id,sour,rel) \
ZZZ_FORWARD_1_TO_N(ZZFP(ZZf,id),sour,rel)

#define ZZZ_FORWARD_1_TO_N(nxt,sour,rel) {(rel)=(sour)->nxt;}
#define ZZ_FORWARD_M_TO_1(id,sour,rel) \
ZZZ_FORWARD_M_TO_1(ZZFP(ZZf,id),sour,rel)

#define ZZZ_FORWARD_M_TO_1(nxt,sour,rel) {(rel)=(sour)->nxt;}
#define ZZ_FORWARD_M_TO_N(id,sour,rel) \
ZZZ_FORWARD_M_TO_N(ZZFP(ZZf,id),sour,rel)

#define ZZZ_FORWARD_M_TO_N(nxt,sour,rel) {(rel)=(sour)->nxt;}
#define ZZ_BACKWARD_1_TO_1(id,targ,rel) \
ZZZ_BACKWARD_1_TO_1(ZZFP(ZZb,id),targ,rel)

#define ZZZ_BACKWARD_1_TO_1(nxt,targ,rel) {(rel)=(targ)->nxt;}
#define ZZ_BACKWARD_1_TO_N(id,targ,rel) \
ZZZ_BACKWARD_1_TO_N(ZZFP(ZZb,id),targ,rel)

#define ZZZ_BACKWARD_1_TO_N(nxt,targ,rel) {(rel)=(targ)->nxt;}
#define ZZ_BACKWARD_M_TO_1(id,targ,rel) \
ZZZ_BACKWARD_M_TO_1(ZZFP(ZZb,id),targ,rel)

#define ZZZ_BACKWARD_M_TO_1(nxt,targ,rel) {(rel)=(targ)->nxt;}
#define ZZ_BACKWARD_M_TO_N(id,targ,rel) \
ZZZ_BACKWARD_M_TO_N(ZZFP(ZZb,id),targ,rel)

#define ZZZ_BACKWARD_M_TO_N(nxt,targ,rel) {(rel)=(targ)->nxt;}
#define ZZ_A_TRAVERSE_1_TO_1(id,sour,rel) \
ZZZ_TRAVERSE_1_TO_1(ZZFP(ZZf,id),sour,rel)

#define ZZZ_TRAVERSE_1_TO_1(nxt,sour,rel) \
{   if(sour)(rel)=(sour)->nxt; else (rel)=NULL;\
    for(;(rel);(rel)=NULL){
#define ZZ_A_TRAVERSE_1_TO_N(id,sour,rel) \
ZZZ_TRAVERSE_1_TO_N(ZZFP(ZZf,id),ZZFP(ZZs,id),ZZFT(2,id),sour,rel)

#define ZZZ_TRAVERSE_1_TO_N(nxt,sibl,strType,sour,rel) \
{strType *ZZt,*ZZs;\
    if(sour)ZZt=(sour)->nxt; else ZZt=NULL;\
    if(ZZt)(rel)=(ZZt)->sibl; else (rel)=NULL;\
    for(;(rel);(rel)=ZZs){ \
	ZZs=(rel)->sibl; if((rel)==(ZZt))ZZs=NULL;
#define ZZ_A_TRAVERSE_M_TO_1(id,sour,rel) \
ZZZ_TRAVERSE_M_TO_1(ZZFP(ZZf,id),sour,rel)

#define ZZZ_TRAVERSE_M_TO_1(nxt,sour,rel) \
{   if(sour)(rel)=(sour)->nxt; else (rel)=NULL;\
    for(;(rel);(rel)=NULL){
#define ZZ_A_TRAVERSE_M_TO_N(id,sour,rel) \
ZZZ_TRAVERSE_M_TO_N(ZZFP(ZZf,id),ZZFP(ZZr,id),ZZFT(2,id),sour,rel)

#define ZZZ_TRAVERSE_M_TO_N(nxt,sibl,strType,sour,rel) \
{strType *ZZt,*ZZs;\
    if(sour)ZZt=(sour)->nxt; else ZZt=NULL;\
    if(ZZt)(rel)=(ZZt)->sibl; else (rel)=NULL;\
    for(;(rel);(rel)=ZZs){ \
	ZZs=(rel)->sibl; if((rel)==(ZZt))ZZs=NULL;
#define ZZ_A_RETRACE_1_TO_1(id,targ,rel) \
ZZZ_RETRACE_1_TO_1(ZZFP(ZZb,id),targ,rel)

#define ZZZ_RETRACE_1_TO_1(nxt,targ,rel) \
{   if(targ)(rel)=(targ)->nxt; else (rel)=NULL;\
    for(;(rel);(rel)=NULL){
#define ZZ_A_RETRACE_1_TO_N(id,targ,rel) \
ZZZ_RETRACE_1_TO_N(ZZFP(ZZb,id),targ,rel)

#define ZZZ_RETRACE_1_TO_N(nxt,targ,rel) \
{   if(targ)(rel)=(targ)->nxt; else (rel)=NULL;\
    for(;(rel);(rel)=NULL){
#define ZZ_A_RETRACE_M_TO_1(id,targ,rel) \
ZZZ_RETRACE_M_TO_1(ZZFP(ZZb,id),ZZFP(ZZs,id),ZZFT(2,id),targ,rel)

#define ZZZ_RETRACE_M_TO_1(nxt,sibl,strType,targ,rel) \
{strType *ZZt,*ZZs;\
    if(targ)ZZt=(targ)->nxt; else ZZt=NULL;\
    if(ZZt)(rel)=(ZZt)->sibl; else (rel)=NULL;\
    for(;(rel);(rel)=ZZs){ \
	ZZs=(rel)->sibl; if((rel)==(ZZt))ZZs=NULL;
#define ZZ_A_RETRACE_M_TO_N(id,targ,rel) \
ZZZ_RETRACE_M_TO_N(ZZFP(ZZb,id),ZZFP(ZZs,id),ZZFT(2,id),targ,rel)

#define ZZZ_RETRACE_M_TO_N(nxt,sibl,strType,targ,rel) \
{strType *ZZt,*ZZs;\
    if(targ)ZZt=(targ)->nxt; else ZZt=NULL;\
    if(ZZt)(rel)=(ZZt)->sibl; else (rel)=NULL;\
    for(;(rel);(rel)=ZZs){ \
	ZZs=(rel)->sibl; if((rel)==(ZZt))ZZs=NULL;
#define ZZ_ADD_RELATION_1_TO_1(id,source,rel,target) \
ZZZ_ADD_RELATION_1_TO_1(id,ZZFP(ZZf,id),ZZFP(ZZx,id),ZZFP(ZZy,id), \
ZZFP(ZZb,id),source,rel,target)

#ifdef ZZnoCheck
#define ZZZ_ADD_RELATION_1_TO_1(id,fwd,src,trg,bwd,source,rel,target)\
{\
        (source)->fwd=(target)->bwd=(rel);\
        (rel)->src=(source); (rel)->trg=(target);\
}
#else
#define ZZZ_ADD_RELATION_1_TO_1(id,fwd,src,trg,bwd,source,rel,target)\
{\
    if((rel)->src || (rel)->trg){\
        ZZmsgSS(19,ZZ_STRINGIT(id),(char *)(rel));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else if((source)->fwd || (target)->bwd){\
        ZZmsgSS(18,ZZ_STRINGIT(id),(char *)(rel));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else {\
        (source)->fwd=(target)->bwd=(rel);\
        (rel)->src=(source); (rel)->trg=(target);\
    }\
}
#endif
#define ZZ_ADD_RELATION_1_TO_N(id,source,rel,target) \
ZZZ_ADD_RELATION_1_TO_N(id,ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZx,id),ZZFP(ZZy,id), \
ZZFP(ZZb,id),ZZFP(ZZs,id),ZZFP(ZZr,id),source,rel,target)

#ifdef ZZnoCheck
#define ZZZ_ADD_RELATION_1_TO_N(id,type2,fwd,src,trg,bwd,sib,ret,source,rel,target)\
{type2 *ZZe;\
        ZZe=(source)->fwd;\
        (target)->bwd=(rel);\
        if(ZZe){\
            ZZe->sib->ret=(rel); (rel)->ret=ZZe;\
            (rel)->sib=ZZe->sib; ZZe->sib=(rel);\
        }\
        else {((source)->fwd)=(rel)->sib=(rel)->ret=(rel);}\
        (rel)->src=(source); (rel)->trg=(target);\
}
#else
#define ZZZ_ADD_RELATION_1_TO_N(id,type2,fwd,src,trg,bwd,sib,ret,source,rel,target)\
{type2 *ZZe;\
    if((rel)->src || (rel)->trg || (rel)->sib){\
        ZZmsgSS(19,ZZ_STRINGIT(id),(char *)(rel));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else if((target)->bwd){\
        ZZmsgSS(18,ZZ_STRINGIT(id),(char *)(rel));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else {\
        ZZe=(source)->fwd;\
        (target)->bwd=(rel);\
        if(ZZe){\
            ZZe->sib->ret=(rel); (rel)->ret=ZZe;\
            (rel)->sib=ZZe->sib; ZZe->sib=(rel);\
        }\
        else {((source)->fwd)=(rel)->sib=(rel)->ret=(rel);}\
        (rel)->src=(source); (rel)->trg=(target);\
    }\
}
#endif
#define ZZ_ADD_RELATION_M_TO_1(id,source,rel,target) \
ZZZ_ADD_RELATION_M_TO_1(id,ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZx,id),ZZFP(ZZy,id), \
ZZFP(ZZb,id),ZZFP(ZZs,id),ZZFP(ZZr,id),source,rel,target)

#ifdef ZZnoCheck
#define ZZZ_ADD_RELATION_M_TO_1(id,type2,fwd,src,trg,bwd,sib,ret,source,rel,target)\
{type2 *ZZe;\
        ZZe=(target)->bwd;\
        (source)->fwd=(rel);\
        if((target)->bwd){\
            ZZe->sib->ret=(rel); (rel)->ret=ZZe;\
            (rel)->sib=ZZe->sib; ZZe->sib=(rel);\
        }\
        else {((target)->bwd)=(rel)->sib=(rel)->ret=(rel);}\
        (rel)->src=(source); (rel)->trg=(target);\
}
#else
#define ZZZ_ADD_RELATION_M_TO_1(id,type2,fwd,src,trg,bwd,sib,ret,source,rel,target)\
{type2 *ZZe;\
    if((rel)->src || (rel)->trg || (rel)->sib){\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else if((source)->fwd){\
        ZZmsgSS(18,ZZ_STRINGIT(id),(char *)(rel));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else {\
        ZZe=(target)->bwd;\
        (source)->fwd=(rel);\
        if((target)->bwd){\
            ZZe->sib->ret=(rel); (rel)->ret=ZZe;\
            (rel)->sib=ZZe->sib; ZZe->sib=(rel);\
        }\
        else {((target)->bwd)=(rel)->sib=(rel)->ret=(rel);}\
        (rel)->src=(source); (rel)->trg=(target);\
    }\
}
#endif
#define ZZ_ADD_RELATION_M_TO_N(id,source,rel,target) \
ZZZ_ADD_RELATION_M_TO_N(id,ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZx,id),ZZFP(ZZy,id), \
ZZFP(ZZb,id),ZZFP(ZZr,id),ZZFP(ZZs,id),ZZFP(ZZv,id),ZZFP(ZZw,id),\
source,rel,target)

#ifdef ZZnoCheck
#define ZZZ_ADD_RELATION_M_TO_N(id,eType,fwd,src,trg,bwd,sSib,tSib,sRet,tRet,source,rel,target)\
{eType *ZZe;\
        (rel)->src=(source); (rel)->trg=(target);\
        ZZe=(source)->fwd;\
        if(ZZe){\
            ZZe->sSib->sRet=(rel); (rel)->sSib=ZZe->sSib;\
            (rel)->sRet=ZZe; ZZe->sSib=(rel);\
        }\
        else {(source)->fwd=(rel)->sSib=(rel)->sRet=(rel);}\
        ZZe=(target)->bwd;\
        if(ZZe){\
            ZZe->tSib->tRet=(rel); (rel)->tSib=ZZe->tSib;\
            (rel)->tRet=ZZe; ZZe->tSib=(rel);\
        }\
        else {(target)->bwd=(rel)->tSib=(rel)->tRet=(rel);}\
}
#else
#define ZZZ_ADD_RELATION_M_TO_N(id,eType,fwd,src,trg,bwd,sSib,tSib,sRet,tRet,source,rel,target)\
{eType *ZZe;\
    if((rel)->src || (rel)->trg || (rel)->sSib || (rel)->tSib){\
        ZZmsgSS(19,ZZ_STRINGIT(id),(char *)(rel));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else {\
        (rel)->src=(source); (rel)->trg=(target);\
        ZZe=(source)->fwd;\
        if(ZZe){\
            ZZe->sSib->sRet=(rel); (rel)->sSib=ZZe->sSib;\
            (rel)->sRet=ZZe; ZZe->sSib=(rel);\
        }\
        else {(source)->fwd=(rel)->sSib=(rel)->sRet=(rel);}\
        ZZe=(target)->bwd;\
        if(ZZe){\
            ZZe->tSib->tRet=(rel); (rel)->tSib=ZZe->tSib;\
            (rel)->tRet=ZZe; ZZe->tSib=(rel);\
        }\
        else {(target)->bwd=(rel)->tSib=(rel)->tRet=(rel);}\
    }\
}
#endif
#define ZZ_DELETE_RELATION_1_TO_1(id,rel) \
ZZZ_DELETE_RELATION_1_TO_1(id,ZZFP(ZZf,id),ZZFP(ZZx,id),ZZFP(ZZy,id), \
ZZFP(ZZb,id),rel)

#define ZZZ_DELETE_RELATION_1_TO_1(id,fwd,src,trg,bwd,rel)\
{ if((rel)->src && (rel)->trg){\
     (rel)->src->fwd=(rel)->trg->bwd=NULL;\
     (rel)->src=NULL; (rel)->trg=NULL;\
  }\
}     
#define ZZ_DELETE_RELATION_1_TO_N(id,rel) \
ZZZ_DELETE_RELATION_1_TO_N(id,ZZFP(ZZf,id),ZZFP(ZZx,id),ZZFP(ZZy,id), \
ZZFP(ZZb,id),ZZFP(ZZs,id),ZZFP(ZZr,id),rel)

#define ZZZ_DELETE_RELATION_1_TO_N(id,fwp,src,trg,bwp,sib,ret,rel)\
{\
    if(rel){\
	if((rel)->sib && (rel)->src && (rel)->trg){\
	    if((rel)->sib==(rel))((rel)->src->fwp)=NULL;\
	    else {\
	        if((rel)==((rel)->src->fwp))((rel)->src->fwp)=(rel)->ret;\
	        (rel)->ret->sib=(rel)->sib;\
	        (rel)->sib->ret=(rel)->ret;\
	    }\
	    (rel)->sib=(rel)->ret=(rel)->trg->bwp=NULL;\
            (rel)->src=NULL; (rel)->trg=NULL;\
	}\
    }\
}
#define ZZ_DELETE_RELATION_M_TO_1(id,rel) \
ZZZ_DELETE_RELATION_M_TO_1(id,ZZFP(ZZf,id),ZZFP(ZZx,id),ZZFP(ZZy,id), \
ZZFP(ZZb,id),ZZFP(ZZs,id),ZZFP(ZZr,id),rel)

#define ZZZ_DELETE_RELATION_M_TO_1(id,fwd,src,trg,bwd,sib,ret,rel)\
{\
    if(rel){\
	if((rel)->sib && (rel)->src && (rel)->trg){\
	    if((rel)->sib==(rel))((rel)->trg->bwd)=NULL;\
	    else {\
	        if((rel)==((rel)->trg->bwd))((rel)->trg->bwd)=(rel)->ret;\
	        (rel)->ret->sib=(rel)->sib;\
	        (rel)->sib->ret=(rel)->ret;\
	    }\
	    (rel)->sib=(rel)->ret=(rel)->src->fwd=NULL;\
            (rel)->src=NULL; (rel)->trg=NULL;\
	}\
    }\
}
#define ZZ_DELETE_RELATION_M_TO_N(id,rel) \
ZZZ_DELETE_RELATION_M_TO_N(id,ZZFP(ZZf,id),ZZFP(ZZx,id),\
ZZFP(ZZy,id),ZZFP(ZZb,id),ZZFP(ZZr,id),ZZFP(ZZs,id),ZZFP(ZZv,id),\
ZZFP(ZZw,id),rel)

#define ZZZ_DELETE_RELATION_M_TO_N(id,fwp,src,trg,bwp,sSib,tSib,sRet,tRet,rel)\
{\
    if(rel){\
        if((rel)->src && (rel)->trg && (rel)->sSib && (rel)->tSib){\
	    if((rel)->sSib==(rel))((rel)->src->fwp)=NULL;\
	    else {\
	        if((rel)==((rel)->src->fwp))((rel)->src->fwp)=(rel)->sRet;\
	        (rel)->sRet->sSib=(rel)->sSib;\
	        (rel)->sSib->sRet=(rel)->sRet;\
	    }\
	    (rel)->sSib=(rel)->sRet=NULL; (rel)->src=NULL;\
	    if((rel)->tSib==(rel))(rel)->trg->bwp=NULL;\
	    else {\
	        if((rel)==((rel)->trg->bwp))(rel)->trg->bwp=(rel)->tRet;\
	        (rel)->tRet->tSib=(rel)->tSib;\
	        (rel)->tSib->tRet=(rel)->tRet;\
	    }\
	    (rel)->tSib=(rel)->tRet=NULL; (rel)->trg=NULL;\
	}\
    }\
}
#ifndef ZZ_ANSI
#define ZZF_ADD_RELATION_1_TO_1(id,source,rel,target) \
{void ZZFP(ZZF_ADD_RELATION_1_TO_1,id)();\
     ZZFP(ZZF_ADD_RELATION_1_TO_1,id)(source,rel,target);}
#endif
#ifdef ZZ_ANSI
#define ZZF_ADD_RELATION_1_TO_1(id,source,rel,target) \
{void ZZFP(ZZF_ADD_RELATION_1_TO_1,id)(ZZFT(1,id) *s,ZZFT(2,id) *r,ZZFT(3,id) *t);\
     ZZFP(ZZF_ADD_RELATION_1_TO_1,id)(source,rel,target);}
#endif

#ifndef ZZ_ANSI
#define ZZF_ADD_RELATION_1_TO_N(id,source,rel,target) \
{void ZZFP(ZZF_ADD_RELATION_1_TO_N,id)();\
      ZZFP(ZZF_ADD_RELATION_1_TO_N,id)(source,rel,target);}
#endif
#ifdef ZZ_ANSI
#define ZZF_ADD_RELATION_1_TO_N(id,source,rel,target) \
{void ZZFP(ZZF_ADD_RELATION_1_TO_N,id)(ZZFT(1,id) *s,ZZFT(2,id) *r,ZZFT(3,id) *t);\
      ZZFP(ZZF_ADD_RELATION_1_TO_N,id)(source,rel,target);}
#endif

#ifndef ZZ_ANSI
#define ZZF_ADD_RELATION_M_TO_1(id,source,rel,target) \
{void ZZFP(ZZF_ADD_RELATION_M_TO_1,id)();\
     ZZFP(ZZF_ADD_RELATION_M_TO_1,id)(source,rel,target);}
#endif
#ifdef ZZ_ANSI
#define ZZF_ADD_RELATION_M_TO_1(id,source,rel,target) \
{void ZZFP(ZZF_ADD_RELATION_M_TO_1,id)(ZZFT(1,id) *s,ZZFT(2,id) *r, ZZFT(3,id) *t);\
     ZZFP(ZZF_ADD_RELATION_M_TO_1,id)(source,rel,target);}
#endif

#ifndef ZZ_ANSI
#define ZZF_ADD_RELATION_M_TO_N(id,source,rel,target) \
{void ZZFP(ZZF_ADD_RELATION_M_TO_N,id)();\
    ZZFP(ZZF_ADD_RELATION_M_TO_N,id)(source,rel,target);}
#endif
#ifdef ZZ_ANSI
#define ZZF_ADD_RELATION_M_TO_N(id,source,rel,target) \
{void ZZFP(ZZF_ADD_RELATION_M_TO_N,id)(ZZFT(1,id) *s,ZZFT(2,id) *r,ZZFT(3,id) *t);\
    ZZFP(ZZF_ADD_RELATION_M_TO_N,id)(source,rel,target);}
#endif

#ifndef ZZ_ANSI
#define ZZF_DELETE_RELATION_1_TO_1(id,rel) \
{void ZZFP(ZZF_DELETE_RELATION_1_TO_1,id)();\
     ZZFP(ZZF_DELETE_RELATION_1_TO_1,id)(rel);}
#endif
#ifdef ZZ_ANSI
#define ZZF_DELETE_RELATION_1_TO_1(id,rel) \
{void ZZFP(ZZF_DELETE_RELATION_1_TO_1,id)(ZZFT(2,id) *r);\
     ZZFP(ZZF_DELETE_RELATION_1_TO_1,id)(rel);}
#endif

#ifndef ZZ_ANSI
#define ZZF_DELETE_RELATION_1_TO_N(id,rel) \
{void ZZFP(ZZF_DELETE_RELATION_1_TO_N,id)();\
     ZZFP(ZZF_DELETE_RELATION_1_TO_N,id)(rel);}
#endif
#ifdef ZZ_ANSI
#define ZZF_DELETE_RELATION_1_TO_N(id,rel) \
{void ZZFP(ZZF_DELETE_RELATION_1_TO_N,id)(ZZFT(2,id) *r);\
     ZZFP(ZZF_DELETE_RELATION_1_TO_N,id)(rel);}
#endif

#ifndef ZZ_ANSI
#define ZZF_DELETE_RELATION_M_TO_1(id,rel) \
{void ZZFP(ZZF_DELETE_RELATION_M_TO_1,id)();\
     ZZFP(ZZF_DELETE_RELATION_M_TO_1,id)(rel);}
#endif
#ifdef ZZ_ANSI
#define ZZF_DELETE_RELATION_M_TO_1(id,rel) \
{void ZZFP(ZZF_DELETE_RELATION_M_TO_1,id)(ZZFT(2,id) *r);\
     ZZFP(ZZF_DELETE_RELATION_M_TO_1,id)(rel);}
#endif

#ifndef ZZ_ANSI
#define ZZF_DELETE_RELATION_M_TO_N(id,rel) \
{void ZZFP(ZZF_DELETE_RELATION_M_TO_N,id)();\
    ZZFP(ZZF_DELETE_RELATION_M_TO_N,id)(rel);}
#endif
#ifdef ZZ_ANSI
#define ZZF_DELETE_RELATION_M_TO_N(id,rel) \
{void ZZFP(ZZF_DELETE_RELATION_M_TO_N,id)(ZZFT(2,id) *r);\
    ZZFP(ZZF_DELETE_RELATION_M_TO_N,id)(rel);}
#endif

#define ZZ_ADD_SINGLE_COLLECT(id,par,pp) \
ZZZ_ADD_SINGLE_COLLECT\
(id,ZZFP(ZZs,id),ZZFP(ZZc,id),par,pp)

#ifdef ZZnoCheck
#define ZZZ_ADD_SINGLE_COLLECT(id,sibling,child,par,pp) \
{\
        if((par)->child==NULL){\
            (par)->child=(pp);\
            (pp)->sibling=(pp);\
        }\
	else {\
            (pp)->sibling=((par)->child)->sibling;\
            ((par)->child)->sibling=(pp);\
        }\
}
#else
#define ZZZ_ADD_SINGLE_COLLECT(id,sibling,child,par,pp) \
{\
    if((pp)->sibling!=NULL){\
        ZZmsgSS(23,ZZ_STRINGIT(id),(char *)(pp));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else {\
        if((par)->child==NULL){\
            (par)->child=(pp);\
            (pp)->sibling=(pp);\
        }\
	else {\
            (pp)->sibling=((par)->child)->sibling;\
            ((par)->child)->sibling=(pp);\
        }\
    }\
}
#endif
#define ZZ_MERGE_SINGLE_COLLECT(id,obj1,obj2,par) \
ZZZ_MERGE_SINGLE_COLLECT\
(id,ZZFT(1,id),ZZFT(2,id),ZZFP(ZZs,id),ZZFP(ZZp,id),ZZFP(ZZc,id),obj1,obj2,par)

#define ZZZ_MERGE_SINGLE_COLLECT(id,tp1,tp2,sib,par,chi,obj1,obj2,nPar) \
{tp1 *ZZs; tp2 *ZZp; ZZint ZZi,ZZj,ZZk;\
    ZZi=0; ZZs=(nPar); ZZp=(obj1);\
    if(!ZZs)ZZi=1;\
    else if(!(obj1))ZZs->chi=(obj2);\
    else if(!(obj2))ZZs->chi=(obj1);\
    else {\
        if(!(ZZp->sib) || !((obj2)->sib))ZZi=1;\
        else if(ZZp!=(obj2)){\
            for(ZZp=(obj2)->sib,ZZk=ZZj=0;;ZZp=ZZp->sib){\
                if(ZZs->chi==ZZp)ZZk=1;\
                if(ZZp==(obj1))ZZj=1;\
                if(ZZp==(obj2))break;\
            }\
            if(ZZs->chi && ZZk || !(ZZs->chi) && ZZj){\
                ZZp=(obj2)->sib; \
                (obj2)->sib=(obj1)->sib;\
                (obj1)->sib=ZZp;\
                if(ZZs->chi)ZZs->chi=NULL;\
                else {\
                    for(ZZp=(obj2);ZZp->sib!=(obj2);ZZp=ZZp->sib)continue;\
                    ZZs->chi=ZZp;\
                }\
            }\
            else ZZi=1;\
        }\
    }\
    if(ZZi)ZZmsgS(33,ZZ_STRINGIT(id));\
}
#define ZZ_FORWARD_SINGLE_COLLECT(id,pp,fwd) \
ZZZ_FORWARD_SINGLE_COLLECT(ZZFP(ZZs,id),pp,fwd)

#define ZZZ_FORWARD_SINGLE_COLLECT(sibling,pp,fwd) {(fwd)=(pp)->sibling;}
#define ZZ_CHILD_SINGLE_COLLECT(id,pp,chi) \
ZZZ_CHILD_SINGLE_COLLECT(ZZFP(ZZc,id),ZZFP(ZZs,id),pp,chi)

#define ZZZ_CHILD_SINGLE_COLLECT(child,sibling,pp,chi) \
{if((pp)->child)(chi)=(pp)->child->sibling; else (chi)=NULL;}
#define ZZ_DELETE_SINGLE_COLLECT(id,par,child) \
ZZZ_DELETE_SINGLE_COLLECT\
(id,ZZFT(2,id),ZZFP(ZZs,id),ZZFP(ZZc,id),par,child)

#define ZZZ_DELETE_SINGLE_COLLECT(id,sBot,sibling,child,entry,pp) \
{sBot *ZZv,*ZZc; \
    if(pp) {\
      if((pp)->sibling==(pp))(entry)->child=NULL;\
      else { \
        ZZc=(entry)->child; if(!ZZc)ZZc=(pp); \
        for(ZZv=ZZc;ZZv->sibling!=(pp);ZZv=ZZv->sibling)continue;\
        if((entry)->child==(pp))(entry)->child=ZZv;\
        ZZv->sibling=(pp)->sibling;\
      } \
      (pp)->sibling=NULL;\
    }\
}
#define ZZ_A_TRAVERSE_SINGLE_COLLECT(id,par,pp) \
ZZZ_A_TRAVERSE_SINGLE_COLLECT(ZZFT(2,id),ZZFP(ZZs,id),ZZFP(ZZc,id),par,pp)

#define ZZZ_A_TRAVERSE_SINGLE_COLLECT(strBot,sibling,child,par,pp) \
{strBot *ZZt,*ZZc;\
if(par)ZZc=(par)->child; else ZZc=NULL;\
if(ZZc)(pp)=ZZc->sibling; else (pp)=NULL;\
for(;pp;(pp)=ZZt){\
    if((pp)==ZZc)ZZt=NULL; else ZZt=(pp)->sibling;
#define ZZ_SET_SINGLE_COLLECT(id,par,pp) \
ZZZ_SET_SINGLE_COLLECT(ZZFP(ZZc,id),par,pp)

#define ZZZ_SET_SINGLE_COLLECT(child,par,pp) { (par)->child=(pp); }
#define ZZ_SORT_SINGLE_COLLECT(id,sortFun,par) \
ZZZ_SORT_SINGLE_COLLECT(ZZFP(ZZs,id),ZZFP(ZZc,id),ZZFT(2,id),sortFun,par) 

#define ZZZ_SORT_SINGLE_COLLECT(fwp,child,str2Type,sortFun,par) \
{str2Type *ZZstart;\
    char *ZZFUN_rSRfun();\
    if(par){\
        ZZstart=(par)->child;\
        if(ZZstart){\
            (par)->child=(str2Type *)\
                ZZrSRfun((char*)(&(ZZstart->fwp)),(char*)(ZZstart),sortFun);\
        }\
    }\
}
#define ZZ_ORG_SINGLE_COLLECT(id,strType1,strType2) \
/* ZZ_ORG_SINGLE_COLLECT */
#define ZZ_HYPER_SINGLE_COLLECT(id,pType,cType)  \
ZZ_BASIC_SINGLE_COLLECT(id,pType,cType,ZZ_EXTERN,id)

#define ZZ_LOCAL_SINGLE_COLLECT(id,pType,cType,where)  \
ZZ_BASIC_SINGLE_COLLECT(id,pType,cType,static,where :: id)

#define ZZ_BASIC_SINGLE_COLLECT(id,pType,cType,scope,where)  \
class ZZFP(ZZH,id) { \
  friend class pType;\
  friend class cType;\
public: \
  cType *child(pType *s){cType *p;ZZ_CHILD_SINGLE_COLLECT(id,s,p);return(p);}\
  cType *chld(pType *s){return(s->ZZFP(ZZc,id));}\
  cType * fwd(cType *s){cType *p;ZZ_FORWARD_SINGLE_COLLECT(id,s,p);return(p);}\
  void set(pType *p,cType *t){ZZ_SET_SINGLE_COLLECT(id,p,t);}\
  void add(pType *s,cType *p);\
  void app(pType *p,cType *x,cType *y);\
  void del(pType *p,cType *c);\
  void merge(cType *s,cType *t,pType *p);\
  void sort(ZZTsortFun cmpF,pType *p);\
  void switchParents(pType *p1,pType *p2){ \
        if(p1 && p2){ cType* c=p2->ZZFP(ZZc,id); \
          p2->ZZFP(ZZc,id)=p1->ZZFP(ZZc,id); p1->ZZFP(ZZc,id)=c;}} \
};\
scope ZZFP(ZZH,id) id; \
class ZZFN(id,iterator){ \
   cType *beg;\
   cType *nxt;\
public:\
   ZZFN(id,iterator)(pType *p){start(p);}\
   ZZFN(id,iterator)(){beg=nxt=NULL;}\
   void start(pType *p){if(p){beg=where.chld(p); if(beg)nxt=where.fwd(beg); else nxt=NULL;}\
                                                 else beg=nxt=NULL;} \
   cType* operator++(){cType *p;\
      p=nxt; if(p==beg)nxt=beg=NULL; else nxt=where.fwd(p); return(p);}\
}

#define ZZ_ADD_DOUBLE_COLLECT(id,par,pp) \
ZZZ_ADD_DOUBLE_COLLECT\
(id,ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZb,id),ZZFP(ZZc,id),par,pp)

#ifdef ZZnoCheck
#define ZZZ_ADD_DOUBLE_COLLECT(id,type2,fwd,bwd,child,par,pp) \
{ type2 *ZZa,*ZZb;\
        if((par)->child==NULL){\
            (par)->child=(pp);\
            (pp)->fwd=(pp);\
            (pp)->bwd=(pp);\
        }\
	else {\
            ZZa=(par)->child; ZZb=ZZa->fwd;\
            (pp)->fwd=ZZb; (pp)->bwd=ZZa;\
            ZZa->fwd=(pp); ZZb->bwd=(pp);\
        }\
}
#else
#define ZZZ_ADD_DOUBLE_COLLECT(id,type2,fwd,bwd,child,par,pp) \
{ type2 *ZZa,*ZZb;\
    if((pp)->fwd!=NULL){\
        ZZmsgSS(23,ZZ_STRINGIT(id),(char *)(pp));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else {\
        if((par)->child==NULL){\
            (par)->child=(pp);\
            (pp)->fwd=(pp);\
            (pp)->bwd=(pp);\
        }\
	else {\
            ZZa=(par)->child; ZZb=ZZa->fwd;\
            (pp)->fwd=ZZb; (pp)->bwd=ZZa;\
            ZZa->fwd=(pp); ZZb->bwd=(pp);\
        }\
    }\
}
#endif
#define ZZ_INSERT_DOUBLE_COLLECT(id,chi,pp) \
ZZZ_INSERT_DOUBLE_COLLECT(id,ZZFP(ZZf,id),ZZFP(ZZb,id),chi,pp)

#define ZZZ_INSERT_DOUBLE_COLLECT(id,fwp,bwp,chi,pp) \
{\
    if((pp)->fwp){\
        ZZmsgSS(24,ZZ_STRINGIT(id),(char *)(pp));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else if(!chi){\
        ZZmsgS(44,ZZ_STRINGIT(id));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else {(chi)->bwp->fwp=(pp);  (pp)->fwp=(chi);\
              (pp)->bwp=(chi)->bwp; (chi)->bwp=(pp);}\
}
#define ZZ_MERGE_DOUBLE_COLLECT(id,obj1,obj2,par) \
ZZZ_MERGE_SINGLE_COLLECT\
(id,ZZFT(1,id),ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZp,id),ZZFP(ZZc,id),obj1,obj2,par)\
(obj2)->ZZFP(ZZb,id)=NULL;\
ZZ_UPD_DOUBLE(ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZb,id),obj1);\
if((obj2)->ZZFP(ZZb,id)==NULL)\
ZZ_UPD_DOUBLE(ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZb,id),obj2);
#define ZZ_FORWARD_DOUBLE_COLLECT(id,pp,fwd) \
ZZZ_FORWARD_DOUBLE_COLLECT(ZZFP(ZZf,id),pp,fwd)

#define ZZZ_FORWARD_DOUBLE_COLLECT(sibling,pp,fwd) {(fwd)=(pp)->sibling;}
#define ZZ_BACKWARD_DOUBLE_COLLECT(id,pp,bwd) \
ZZZ_BACKWARD_DOUBLE_COLLECT(ZZFP(ZZb,id),pp,bwd)

#define ZZZ_BACKWARD_DOUBLE_COLLECT(sibling,pp,bwd) {(bwd)=(pp)->sibling;}
#define ZZ_CHILD_DOUBLE_COLLECT(id,pp,chi) \
ZZZ_CHILD_DOUBLE_COLLECT(ZZFP(ZZc,id),ZZFP(ZZf,id),pp,chi)

#define ZZZ_CHILD_DOUBLE_COLLECT(child,sibling,pp,chi) \
{if((pp)->child)(chi)=(pp)->child->sibling; else (chi)=NULL;}
#define ZZ_DELETE_DOUBLE_COLLECT(id,par,child) \
ZZZ_DELETE_DOUBLE_COLLECT\
(id,ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZb,id),ZZFP(ZZc,id),par,child)

#define ZZZ_DELETE_DOUBLE_COLLECT(id,sBot,fwp,bwp,child,entry,pp) \
{sBot *ZZa,*ZZb; \
    if(pp) {\
        if((pp)->fwp==(pp))(entry)->child=NULL;\
        else { \
            ZZa=(pp)->bwp; ZZb=(pp)->fwp;\
            if((entry)->child==(pp))(entry)->child=ZZa;\
            ZZa->fwp=ZZb; ZZb->bwp=ZZa;\
        } \
        (pp)->fwp=(pp)->bwp=NULL;\
    }\
}
#define ZZ_A_TRAVERSE_DOUBLE_COLLECT(id,par,pp) \
ZZZ_A_TRAVERSE_DOUBLE_COLLECT(ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZc,id),par,pp)

#define ZZZ_A_TRAVERSE_DOUBLE_COLLECT(strBot,fwp,child,par,pp) \
{strBot *ZZt,*ZZc;\
if(par)ZZc=(par)->child; else ZZc=NULL;\
if(ZZc)(pp)=ZZc->fwp; else (pp)=NULL;\
for(;pp;(pp)=ZZt){\
    if((pp)==ZZc)ZZt=NULL; else ZZt=(pp)->fwp;
#define ZZ_A_RETRACE_DOUBLE_COLLECT(id,par,pp) \
ZZZ_A_RETRACE_DOUBLE_COLLECT(ZZFT(2,id),ZZFP(ZZb,id),ZZFP(ZZc,id),par,pp)

#define ZZZ_A_RETRACE_DOUBLE_COLLECT(strBot,bwp,child,par,pp) \
{strBot *ZZt,*ZZc;\
if(par)ZZc=(par)->child; else ZZc=NULL;\
if(ZZc)(pp)=ZZc; else (pp)=NULL;\
for(;pp;(pp)=ZZt){\
    ZZt=(pp)->bwp; if(ZZt==ZZc)ZZt=NULL;
#define ZZ_SET_DOUBLE_COLLECT(id,par,pp) \
ZZZ_SET_DOUBLE_COLLECT(ZZFP(ZZc,id),par,pp)

#define ZZZ_SET_DOUBLE_COLLECT(child,par,pp) { (par)->child=(pp); }
#define ZZ_SORT_DOUBLE_COLLECT(id,sortFun,par) \
ZZZ_SORT_DOUBLE_COLLECT(ZZFP(ZZf,id),ZZFP(ZZc,id),ZZFT(2,id),sortFun,par);\
ZZ_UPD_DOUBLE(ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZb,id),(par)->ZZFP(ZZc,id))

#define ZZZ_SORT_DOUBLE_COLLECT(fwp,child,str2Type,sortFun,par) \
{str2Type *ZZstart;\
    char *ZZFUN_rSRfun();\
    if(par){\
        ZZstart=(par)->child;\
        if(ZZstart){\
            (par)->child=(str2Type *)\
                ZZrSRfun((char*)(&(ZZstart->fwp)),(char*)(ZZstart),sortFun);\
        }\
    }\
}
#define ZZ_ORG_DOUBLE_COLLECT(id,strType1,strType2) \
/* ZZ_ORG_DOUBLE_COLLECT */
#define ZZ_HYPER_DOUBLE_COLLECT(id,pType,cType)  \
ZZ_BASIC_DOUBLE_COLLECT(id,pType,cType,ZZ_EXTERN,id)

#define ZZ_LOCAL_DOUBLE_COLLECT(id,pType,cType,where)  \
ZZ_BASIC_DOUBLE_COLLECT(id,pType,cType,static,where :: id)

#define ZZ_BASIC_DOUBLE_COLLECT(id,pType,cType,scope,where)  \
class ZZFN(id,iterator);\
class ZZFP(ZZH,id) { \
  friend class pType;\
  friend class cType;\
  friend class ZZFN(id,iterator);\
  ZZFN(id,iterator) *iterators;\
public: \
  ZZFP(ZZH,id)(){iterators=NULL;}\
  cType *child(pType *s){cType *p;ZZ_CHILD_DOUBLE_COLLECT(id,s,p);return(p);}\
  cType *chld(pType *s){return(s->ZZFP(ZZc,id));}\
  cType * fwd(cType *s){cType *p;ZZ_FORWARD_DOUBLE_COLLECT(id,s,p);return(p);}\
  cType * bwd(cType *s){cType *p;ZZ_BACKWARD_DOUBLE_COLLECT(id,s,p);return(p);}\
  void set(pType *p,cType *t){ZZ_SET_DOUBLE_COLLECT(id,p,t);}\
  void add(pType *s,cType *p);\
  void ins(cType *s,cType *p);\
  void del(pType *p,cType *c);\
  void merge(cType *s,cType *t,pType *p);\
  void sort(ZZTsortFun cmpF,pType *p);\
  void switchParents(pType *p1,pType *p2){ \
        if(p1 && p2){ cType* c=p2->ZZFP(ZZc,id); \
          p2->ZZFP(ZZc,id)=p1->ZZFP(ZZc,id); p1->ZZFP(ZZc,id)=c;}} \
};\
scope ZZFP(ZZH,id) id; \
class ZZFN(id,iterator){ \
   friend class ZZFP(ZZH,id);\
   pType *boss;\
   cType *nxt;\
   ZZFN(id,iterator) *fList,*bList;\
public:\
   ZZFN(id,iterator)(pType *p){start(p);\
           bList=NULL; fList=where.iterators; where.iterators=this;}\
   ZZFN(id,iterator)(){boss=NULL; nxt=NULL;\
           bList=NULL; fList=where.iterators; where.iterators=this;}\
   ~ ZZFN(id,iterator)(){ \
           if(bList)bList->fList=fList; else where.iterators=fList;\
           if(fList)fList->bList=bList;}\
   void start(pType *p){boss=p; nxt=NULL;} \
   cType* operator++(){cType *p,*beg; beg=NULL;\
      if(boss)beg=where.chld(boss);\
      if(nxt)p=nxt; else if(beg)p=where.fwd(beg); else p=NULL;\
      if(p==beg){nxt=NULL; boss=NULL;} else nxt=where.fwd(p); return(p);}\
   cType* operator--(){cType *p,*beg; beg=NULL;\
      if(boss)beg=where.chld(boss);\
      if(nxt)p=nxt; else p=beg; if(p)nxt=where.bwd(p); \
      if(nxt==beg){nxt=NULL; boss=NULL;} return p;}\
}
#define ZZ_MERGE_DOUBLE_TRIANGLE(id,obj1,obj2,par) \
ZZZ_MERGE_SINGLE_TRIANGLE\
(id,ZZFT(1,id),ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZp,id),ZZFP(ZZc,id),obj1,obj2,par)\
(obj2)->ZZFP(ZZb,id)=NULL;\
ZZ_UPD_DOUBLE(ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZb,id),obj1);\
if((obj2)->ZZFP(ZZb,id)==NULL)\
ZZ_UPD_DOUBLE(ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZb,id),obj2);
#define ZZ_ADD_DOUBLE_TRIANGLE(id,par,pp) \
ZZZ_ADD_DOUBLE_TRIANGLE\
(id,ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZb,id),ZZFP(ZZc,id),ZZFP(ZZp,id),par,pp)

#ifdef ZZnoCheck
#define ZZZ_ADD_DOUBLE_TRIANGLE(id,type2,fwd,bwd,child,parent,par,pp) \
{ type2 *ZZa,*ZZb;\
        if((par)->child==NULL){\
            (par)->child=(pp);\
            (pp)->fwd=(pp);\
            (pp)->bwd=(pp);\
        }\
	else {\
            ZZa=(par)->child; ZZb=ZZa->fwd;\
            (pp)->fwd=ZZb; (pp)->bwd=ZZa;\
            ZZa->fwd=(pp); ZZb->bwd=(pp);\
        }\
        (pp)->parent=(par);\
}
#else
#define ZZZ_ADD_DOUBLE_TRIANGLE(id,type2,fwd,bwd,child,parent,par,pp) \
{ type2 *ZZa,*ZZb;\
    if((pp)->fwd!=NULL){\
        ZZmsgSS(23,ZZ_STRINGIT(id),(char *)(pp));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else {\
        if((par)->child==NULL){\
            (par)->child=(pp);\
            (pp)->fwd=(pp);\
            (pp)->bwd=(pp);\
        }\
	else {\
            ZZa=(par)->child; ZZb=ZZa->fwd;\
            (pp)->fwd=ZZb; (pp)->bwd=ZZa;\
            ZZa->fwd=(pp); ZZb->bwd=(pp);\
        }\
        (pp)->parent=(par);\
    }\
}
#endif
#define ZZ_INSERT_DOUBLE_TRIANGLE(id,chi,pp) \
ZZZ_INSERT_DOUBLE_TRIANGLE(id,ZZFP(ZZp,id),ZZFP(ZZf,id),ZZFP(ZZb,id),chi,pp)

#define ZZZ_INSERT_DOUBLE_TRIANGLE(id,parent,fwp,bwp,chi,pp) \
{\
    if((pp)->fwp){\
        ZZmsgSS(24,ZZ_STRINGIT(id),(char *)(pp));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else if(!chi){\
        ZZmsgS(44,ZZ_STRINGIT(id));\
        ZZerrFLG=ZZerrFLG|010;\
    }\
    else {(chi)->bwp->fwp=(pp);  (pp)->fwp=(chi);\
       (pp)->bwp=(chi)->bwp; (chi)->bwp=(pp); (pp)->parent=(chi)->parent;}\
}
#define ZZ_FORWARD_DOUBLE_TRIANGLE(id,pp,fwd) \
ZZZ_FORWARD_DOUBLE_TRIANGLE(ZZFP(ZZf,id),pp,fwd)

#define ZZZ_FORWARD_DOUBLE_TRIANGLE(sibling,pp,fwd) {(fwd)=(pp)->sibling;}
#define ZZ_BACKWARD_DOUBLE_TRIANGLE(id,pp,fwd) \
ZZZ_BACKWARD_DOUBLE_TRIANGLE(ZZFP(ZZb,id),pp,fwd)

#define ZZZ_BACKWARD_DOUBLE_TRIANGLE(sibling,pp,fwd) {(fwd)=(pp)->sibling;}
#define ZZ_CHILD_DOUBLE_TRIANGLE(id,pp,chi) \
ZZZ_CHILD_DOUBLE_TRIANGLE(ZZFP(ZZc,id),ZZFP(ZZf,id),pp,chi)

#define ZZZ_CHILD_DOUBLE_TRIANGLE(child,sibling,pp,chi) \
{if((pp)->child)(chi)=(pp)->child->sibling; else (chi)=NULL;}
#define ZZ_DELETE_DOUBLE_TRIANGLE(id,entry,child) \
ZZZ_DELETE_DOUBLE_TRIANGLE\
(id,ZZFT(1,id),ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZb,id),ZZFP(ZZc,id),ZZFP(ZZp,id),child)

#define ZZZ_DELETE_DOUBLE_TRIANGLE(id,sTop,sBot,fwp,bwp,child,parent,pp) \
{sBot *ZZa,*ZZb; sTop *ZZp; \
    if((pp) && (pp)->parent ) {\
        ZZp=(pp)->parent;\
        if((pp)->fwp==(pp))ZZp->child=NULL;\
        else { \
            ZZa=(pp)->bwp; ZZb=(pp)->fwp;\
            if(ZZp->child==(pp))ZZp->child=ZZa;\
            ZZa->fwp=ZZb; ZZb->bwp=ZZa;\
        } \
        (pp)->fwp=(pp)->bwp=NULL; (pp)->parent=NULL;\
    }\
}
#define ZZ_A_TRAVERSE_DOUBLE_TRIANGLE(id,par,pp) \
ZZZ_A_TRAVERSE_DOUBLE_TRIANGLE(ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZc,id),par,pp)

#define ZZZ_A_TRAVERSE_DOUBLE_TRIANGLE(strBot,sibling,child,par,pp) \
{strBot *ZZt,*ZZc;\
if(par)ZZc=(par)->child; else ZZc=NULL;\
if(ZZc)(pp)=ZZc->sibling; else (pp)=NULL;\
for(;pp;(pp)=ZZt){\
    if((pp)==ZZc)ZZt=NULL; else ZZt=(pp)->sibling;
#define ZZ_PARENT_DOUBLE_TRIANGLE(id,pp,par) \
ZZZ_PARENT_DOUBLE_TRIANGLE(ZZFP(ZZp,id),pp,par)

#define ZZZ_PARENT_DOUBLE_TRIANGLE(parent,pp,par) {(par)=(pp)->parent;}
#define ZZ_SORT_DOUBLE_TRIANGLE(id,sortFun,par) \
ZZZ_SORT_DOUBLE_TRIANGLE(ZZFP(ZZf,id),ZZFP(ZZc,id),ZZFT(2,id),sortFun,par);\
ZZ_UPD_DOUBLE(ZZFT(2,id),ZZFP(ZZf,id),ZZFP(ZZb,id),(par)->ZZFP(ZZc,id))

#define ZZZ_SORT_DOUBLE_TRIANGLE(fwp,child,str2Type,sortFun,par) \
{str2Type *ZZstart;\
    char *ZZFUN_rSRfun();\
    if(par){\
        ZZstart=(par)->child;\
        if(ZZstart){\
            (par)->child=(str2Type *)\
                ZZrSRfun((char*)(&(ZZstart->fwp)),(char*)(ZZstart),sortFun);\
        }\
    }\
}
#define ZZ_SET_DOUBLE_TRIANGLE(id,par,pp) \
ZZZ_SET_DOUBLE_TRIANGLE(ZZFP(ZZp,id),ZZFP(ZZc,id),pp)

#define ZZZ_SET_DOUBLE_TRIANGLE(parent,child,pp) {\
    if((pp)->parent) (pp)->parent->child=(pp); }
#define ZZ_ORG_DOUBLE_TRIANGLE(id,strType1,strType2) \
/* ZZ_ORG_DOUBLE_TRIANGLE */

#define ZZ_ORG_DOUBLE_AGGREGATE(id,strType1,strType2) \
/* ZZ_ORG_DOUBLE_AGGREGATE */
#define ZZ_HYPER_DOUBLE_TRIANGLE(id,pType,cType)  \
ZZ_BASIC_DOUBLE_TRIANGLE(id,pType,cType,ZZ_EXTERN,id)

#define ZZ_HYPER_DOUBLE_AGGREGATE(id,pType,cType)  \
ZZ_BASIC_DOUBLE_TRIANGLE(id,pType,cType,ZZ_EXTERN,id)

#define ZZ_LOCAL_DOUBLE_TRIANGLE(id,pType,cType,where)  \
ZZ_BASIC_DOUBLE_TRIANGLE(id,pType,cType,static,where :: id)

#define ZZ_LOCAL_DOUBLE_AGGREGATE(id,pType,cType,where)  \
ZZ_BASIC_DOUBLE_TRIANGLE(id,pType,cType,static,where :: id)

#define ZZ_BASIC_DOUBLE_TRIANGLE(id,pType,cType,scope,where)  \
class ZZFN(id,iterator);\
class ZZFP(ZZH,id) { \
  friend class pType;\
  friend class cType;\
  friend class ZZFN(id,iterator);\
  ZZFN(id,iterator) *iterators;\
public: \
  ZZFP(ZZH,id)(){iterators=NULL;}\
  pType *par(cType *s){pType *p;\
                  ZZ_PARENT_DOUBLE_TRIANGLE(id,s,p); return(p);}\
  cType *child(pType *s){cType *p;\
                   ZZ_CHILD_DOUBLE_TRIANGLE(id,s,p); return(p);}\
  cType *chld(pType *s){return(s->ZZFP(ZZc,id));}\
  cType * fwd(cType *s){cType *p;\
                 ZZ_FORWARD_DOUBLE_TRIANGLE(id,s,p); return(p);}\
  cType * bwd(cType *s){cType *p;\
                 ZZ_BACKWARD_DOUBLE_TRIANGLE(id,s,p); return(p);}\
  void set(cType *t){ZZ_SET_DOUBLE_TRIANGLE(id,NULL,t);}\
  void add(pType *s,cType *p);\
  void ins(cType *s,cType *p);\
  void app(cType *s,cType *p){cType* t=chld(par(s)); \
      ins(fwd(s),p); if(t==s)set(p);}\
  void del(cType *p);\
  void merge(cType *s,cType *t,pType *p);\
  void sort(ZZTsortFun cmpF,pType *p);\
  void switchParents(pType *p1,pType *p2); \
};\
scope ZZFP(ZZH,id) id; \
class ZZFN(id,iterator){ \
   friend class ZZFP(ZZH,id);\
   pType *boss;\
   cType *nxt;\
   ZZFN(id,iterator) *fList,*bList;\
public:\
   ZZFN(id,iterator)(pType *p){start(p);\
           bList=NULL; fList=where.iterators; where.iterators=this;}\
   ZZFN(id,iterator)(){boss=NULL; nxt=NULL;\
           bList=NULL; fList=where.iterators; where.iterators=this;}\
   ~ ZZFN(id,iterator)(){ \
           if(bList)bList->fList=fList; else where.iterators=fList;\
           if(fList)fList->bList=bList;}\
   void start(pType *p){boss=p; nxt=NULL;} \
   cType* operator++(){cType *p,*beg; beg=NULL;\
      if(boss)beg=where.chld(boss);\
      if(nxt)p=nxt; else if(beg)p=where.fwd(beg); else p=NULL;\
      if(p==beg){nxt=NULL; boss=NULL;} else nxt=where.fwd(p); return(p);}\
   cType* operator--(){cType *p,*beg; beg=NULL;\
      if(boss)beg=where.chld(boss);\
      if(nxt)p=nxt; else p=beg; if(p)nxt=where.bwd(p); \
      if(nxt==beg){nxt=NULL; boss=NULL;} return p;}\
}

#define ZZ_HYPER_BINARY_TREE(id,type) \
ZZ_BASIC_BINARY_TREE(id,type,ZZ_EXTERN,id)

#define ZZ_LOCAL_BINARY_TREE(id,type,where) \
ZZ_BASIC_BINARY_TREE(id,type,static,where :: id)

#define ZZ_BASIC_BINARY_TREE(id,type,scope,where) \
class ZZFP(ZZH,id) { \
public: \
  type *par(type *c){return c->ZZFP(ZZp,id);} \
  type *rChild(type *c){return c->ZZFP(ZZr,id);} \
  type *lChild(type *c){return c->ZZFP(ZZl,id);} \
  ZZint isLeaf(type *c){return !(c->ZZFP(ZZl,id) || c->ZZFP(ZZr,id));} \
  void del(type *t); \
  void delSubtree(type *t); \
  void addR(type *p, type *c); \
  void addL(type *p, type *c); \
  void delSub(type *p,ZZTvoidFun dFun);\
  type *replaceByLeftSubtree(type *p,ZZint dMode,ZZTvoidFun dFun);\
  type *replaceByRightSubtree(type *p,ZZint dMode,ZZTvoidFun dFun);\
};\
scope ZZFP(ZZH,id) id; \
class ZZFN(id,iterator){ \
friend class ZZFP(ZZH,id); \
   ZZint upDown;\
   type *nxt;\
   type *stp;\
   type *next();\
public:\
   ZZFN(id,iterator)(type *p){start(p);}\
   ZZFN(id,iterator)(){start(NULL);}\
   void start(type *p){upDown=0; nxt=stp=p; if(p)stp=id.par(p);}\
   type* operator++();\
   type* operator--();\
}
// upDown=0 down, =1 up as leftChild, =2 as rightChild
// next() returns nodes in the order in which they can be safely
//    disconnected and destroyed.


#ifdef DOS
#include <fcntl.h>
#endif

#ifdef UNIX
#include <fcntl.h>
#ifndef MAC
#include <sys/types.h>
#endif
#ifdef SUN
#ifdef UPP
#include <io.h>
#else
#ifndef MAC
#include <sys/uio.h>
#endif
#endif
#endif
#endif

#ifdef VMS
#include <file.h>
#include <types.h>
#endif

/* input/output file when binding */

struct ZZstrLST {
    char *strName;  /* name of the structure */
    ZZint start;      /* offset for the start of ZZ_EXT, in bytes */
    ZZint size;       /* size of the whole structure in bytes */
    ZZint numPtr;     /* number of pointers in ZZ_EXT, -1 is the endmark */
    ZZint selfIndex;  /* order index of the selfID pointer */
    ZZint propIndex;  /* order index of the property pointer */
    ZZint timeIndex;  /* order index equivalent to start timeStamp */
    ZZint arrayIndex; /* last section of pointers are all for arrays */
    ZZint ptrInd;     /* index to ZZptrList to get type codes for all pointers */
    ZZint inhInd;     /* inheritance index ZZinto ZZtypeHier list, ZZiList */
    char *vObj[2];    /* 0= master object with correct virt. pointers */
                      /* 1= master object with byte 'F' marking virt. pointers */
    ZZint vPtr;       /* 1=virt.pointer actually used, 0=not used */
};
/* convention: entry with numPtr=-1 marks the end of the list,
 *             ptrInd for that entry gives total number of pointers and
 *             other variables,
 *             If, in the last record, start=0, it means that the big
 *             block of memory is being used.
 * vObj[0] has NULL in all positions except for vf and vc pointers
 * vObj[1] has '\0' in all bytes except for bytes that start a virtual
 *             function pointer ('F') or virtual base class pointer ('C')
 * Note that, for some compilers such as Borland, the two pointer types
 * may have different size.
 */

struct ZZbinStore {
    char *ptr;  /* pointer to the beginning of the block */
    ZZint strInd; /* structure type index ZZinto ZZstrList[] */
    ZZint size;   /* size of the block in bytes */
};

struct ZZtypeHier {
    ZZint type;   /* index ZZinto the type table, must be >=0 */
    ZZint offset; /* offset of ZZ_EXT within the parent, in bytes */
    ZZint num;    /* 0=inherited, 1=single object, >1 embedded array, -1 unused */
    char *name; /* member name, *'ZZinherit','ZZvirtual' if inheritance,
                   'ZZrefer' if v.c. involved */
};
/* Note that ZZaddress does not represent a true hierarchical
 * relation, it is used to store the offset for virtual classes
 * burried under more than one inheritance level */

/* pointer conversion table */
struct ZZbindTBL {
    char *oldp;    /* old pointer */
    char *newp;    /* new pointer */
    ZZint strIndex;  /* old structure index */
    ZZint arrSize;   /* overall size of object or array */
    struct ZZbindTBL *next; /* linking the chain */
};

#ifdef ZZmain
ZZ_LOCAL struct ZZbindTBL **ZZbindTable ={0}; /* hash table for pointer conversion */
ZZ_LOCAL ZZint ZZbindSize={0}; /* size of the hash table */
ZZ_LOCAL char *ZZbindName;  /* name of the currently opened bind file */
ZZ_LOCAL ZZint ZZbindCntrl={0};
ZZ_LOCAL struct ZZstrLST *ZZsList; /* description of classes */
ZZ_LOCAL struct ZZstrLST *ZZoList; // description of old classes */
ZZ_LOCAL struct ZZtypeHier *ZZiList={0}; /* inheritance list */
ZZ_LOCAL char **ZZpList;
#endif
#ifndef ZZmain
extern struct ZZbindTBL **ZZbindTable; /* hash table for pointer conversion */
extern ZZint ZZbindSize;
extern char *ZZbindName;  /* name of the currently opened bind file */
extern ZZint ZZbindCntrl;
extern struct ZZstrLST *ZZsList;
extern struct ZZstrLST *ZZoList;
extern struct ZZtypeHier *ZZiList;
extern char **ZZpList;
#endif



#define ZZ_BUFS 512
#ifdef ZZmain
ZZ_LOCAL char ZZbuff[ZZ_BUFS];
#else
extern char ZZbuff[ZZ_BUFS];
#endif
#ifdef ZZmain
ZZ_LOCAL int ZZptrOff; /* fwp offset */
#else
extern int ZZptrOff; /* fwp offset */
#endif

#define ZZptrRel(A) ((char**)(((A)+ZZptrOff)))

union ZZUNI {
    FILE *fp;
    void *p;
    ZZsize s;
    ZZint i;
    ZZlong l;
    unsigned ZZlong ul;
    ZZptrIntType pit;
    ZZsigIntType sit;
    char c;
    ZZfloat f;
};

#define ZZ_ALL_SELF_ID /* selfID on all ZZ_EXT_... */

#define ZZtSize 4
#define ZZ_PROP_CS 4

struct ZZaProp {
    ZZint size;     /* number of structures in the array, NOT byte size */
    char *array; /* cast as char*, it can be array of other things */
};

struct ZZproperty {
    char *codeName; /* one character propCode followed by the property name */
    struct ZZproperty *next;        /* ring of all properties on one object */
    union ZZpropType {
	char        cProp[ZZ_PROP_CS];  /* cProp[0] as one character */
	struct ZZaProp *arrayProp;  /* poZZints to the size and the array */
        ZZint iProp; /* ZZinteger value directly stored */
        float fProp; /* float value directly stored */
    }propType;
};

#define ZZpropSIZE(type,size) {\
char *P;\
P=ZZ_STRINGIT(type);\
if(!strcmp(P,"ZZint"))(size)=(ZZint)sizeof(ZZint);\
else if(!strcmp(P,"float"))(size)=(ZZint)sizeof(float);\
else if(!strcmp(P,"char"))(size)=(ZZint)sizeof(char);\
else if(!strcmp(P,"string"))(size)=(ZZint)sizeof(char*);\
else ZZmsgS(13,P);\
}

#define ZZformPg ZZ_FORM_PAGER
#define ZZioPg ZZ_IO_PAGER
#define ZZclosePg ZZ_CLOSE_PAGER
#define ZZaddrPg ZZ_ADDRESS_PAGER
#define ZZorgPg ZZ_ORG_PAGER
#define ZZhypPg ZZ_HYPER_PAGER
#define ZZlocPg ZZ_LOCAL_PAGER
#define ZZbindPtr ZZ_BIND_POINTER
#define ZZkeepTb ZZ_KEEP_TABLES
#define ZZfreeTb ZZ_FREE_TABLES
#define ZZformat ZZ_FORMAT
#define ZZupdDbl ZZ_UPD_DOUBLE
#define ZZmer1R ZZ_MERGE_SINGLE_RING
#define ZZmer2R ZZ_MERGE_DOUBLE_RING
#define ZZ3merZ ZZ_MERGE_SINGLE_TRIANGLE
#define ZZmerge ZZ_MERGE
#define ZZaRead ZZ_ALLOCATE_AND_READ
#define ZZswSet ZZ_SWEEP_SET
#define ZZswFree ZZ_SWEEP_FREE
#define ZZswFun ZZ_SWEEP_FUNCTION
#define ZZsave ZZ_SAVE
#define ZZdeep ZZ_DEEP
#define ZZmode ZZ_MODE_SAVE
#define ZZclear ZZ_CLEAR
#define ZZerror ZZ_ERROR
#define ZZhypUtil ZZ_HYPER_UTILITIES
#define ZZhypType ZZ_HYPER_TYPE
#define ZZgetID ZZ_GET_SELF_ID
#define ZZsetID ZZ_SET_SELF_ID
#define ZZorg1R ZZ_ORG_SINGLE_RING
#define ZZhyp1R ZZ_HYPER_SINGLE_RING
#define ZZloc1R ZZ_LOCAL_SINGLE_RING
#define ZZadd1R ZZ_ADD_SINGLE_RING
#define ZZdel1R ZZ_DELETE_SINGLE_RING
#define ZZAtr1R ZZ_A_TRAVERSE_SINGLE_RING
#define ZZsrt1R ZZ_SORT_SINGLE_RING
#define ZZfwd1R ZZ_FORWARD_SINGLE_RING
#define ZZorg2R ZZ_ORG_DOUBLE_RING
#define ZZhyp2R ZZ_HYPER_DOUBLE_RING
#define ZZloc2R ZZ_LOCAL_DOUBLE_RING
#define ZZadd2R ZZ_ADD_DOUBLE_RING
#define ZZins2R ZZ_INSERT_DOUBLE_RING
#define ZZdel2R ZZ_DELETE_DOUBLE_RING
#define ZZAtr2R ZZ_A_TRAVERSE_DOUBLE_RING
#define ZZArt2R ZZ_A_RETRACE_DOUBLE_RING
#define ZZsrt2R ZZ_SORT_DOUBLE_RING
#define ZZfwd2R ZZ_FORWARD_DOUBLE_RING
#define ZZbwd2R ZZ_BACKWARD_DOUBLE_RING
#define ZZstrAlloc ZZ_STRING_ALLOC
#define ZZstrFree ZZ_STRING_FREE
#define ZZalloc ZZ_PLAIN_ALLOC
#define ZZplainNew ZZ_PLAIN_NEW
#define ZZblkAlloc ZZ_BLOCK_ALLOC
#define ZZblkAct ZZ_BLOCK_ACTIVE
#define ZZblkU ZZ_BLOCK_UTIL
#define ZZblkF ZZ_BLOCK_FREE
#define ZZchk ZZ_CHECK_FREE
#define ZZcheck ZZ_CHECK
#define ZZfree ZZ_PLAIN_FREE
#define ZZobjAlloc ZZ_OBJECT_ALLOC
#define ZZobjNew ZZ_OBJECT_NEW
#define ZZobjFree ZZ_OBJECT_FREE
#define ZZobjClear ZZ_OBJECT_CLEAR
#define ZZ3addZ ZZ_ADD_SINGLE_TRIANGLE
#define ZZ3fwdZ ZZ_FORWARD_SINGLE_TRIANGLE
#define ZZ3chiZ ZZ_CHILD_SINGLE_TRIANGLE
#define ZZF3addZ ZZF_ADD_SINGLE_TRIANGLE
#define ZZ3delZ ZZ_DELETE_SINGLE_TRIANGLE
#define ZZA3travZ ZZ_A_TRAVERSE_SINGLE_TRIANGLE
#define ZZ3parZ ZZ_PARENT_SINGLE_TRIANGLE
#define ZZ3srtZ ZZ_SORT_SINGLE_TRIANGLE
#define ZZ3setZ ZZ_SET_SINGLE_TRIANGLE
#define ZZorg1Tri ZZ_ORG_SINGLE_TRIANGLE
#define ZZorg1Agr ZZ_ORG_SINGLE_AGGREGATE
#define ZZhyp1Tri ZZ_HYPER_SINGLE_TRIANGLE
#define ZZloc1Tri ZZ_LOCAL_SINGLE_TRIANGLE
#define ZZhyp1Agr ZZ_HYPER_SINGLE_AGGREGATE
#define ZZloc1Agr ZZ_LOCAL_SINGLE_AGGREGATE
#define ZZinpNames ZZ_INPUT_NAMES
#define ZZsetProp ZZ_SET_PROPERTY
#define ZZgetProp ZZ_GET_PROPERTY
#define ZZdelProp ZZ_DELETE_PROPERTY
#define ZZprtProp ZZ_PRINT_PROPERTY
#define ZZAtravP ZZ_A_TRAVERSE_PROPERTY
#define ZZsetTime ZZ_SET_TIME_STAMP
#define ZZgetTime ZZ_GET_TIME_STAMP
#define ZZcmpTime ZZ_CMP_TIME_STAMP
#define ZZAend ZZ_A_END
#define ZZAbreak ZZ_A_BREAK
#define ZZinitial ZZ_INITIAL
#define ZZinit ZZ_INIT
#define ZZorgProp ZZ_ORG_PROPERTY
#define ZZhypProp ZZ_HYPER_PROPERTY
#define ZZorgTime ZZ_ORG_TIME_STAMP
#define ZZhypTime ZZ_HYPER_TIME_STAMP
#define ZZorgSelf ZZ_ORG_SELF_ID
#define ZZhypSelf ZZ_HYPER_SELF_ID
#define ZZobjSave ZZ_OBJECT_SAVE
#define ZZkeySave ZZ_KEY_SAVE
#define ZZstore ZZ_STORE
#define ZZclBind ZZ_CLOSE_BIND
#define ZZopen ZZ_OPEN
#define ZZorgGLink ZZ_ORG_GENERAL_LINK
#define ZZhypGLink ZZ_HYPER_GENERAL_LINK
#define ZZlocGLink ZZ_LOCAL_GENERAL_LINK
#define ZZorgSLink ZZ_ORG_SINGLE_LINK
#define ZZhypSLink ZZ_HYPER_SINGLE_LINK
#define ZZlocSLink ZZ_LOCAL_SINGLE_LINK
#define ZZorgDLink ZZ_ORG_DOUBLE_LINK
#define ZZhypDLink ZZ_HYPER_DOUBLE_LINK
#define ZZlocDLink ZZ_LOCAL_DOUBLE_LINK
#define ZZaddGLink ZZ_ADD_GENERAL_LINK
#define ZZptrSLink ZZ_PTR_SINGLE_LINK
#define ZZaddSLink ZZ_ADD_SINGLE_LINK
#define ZZaddDLink ZZ_ADD_DOUBLE_LINK
#define ZZfwdGLink ZZ_FORWARD_GENERAL_LINK
#define ZZfwdSLink ZZ_FORWARD_SINGLE_LINK
#define ZZfwdDLink ZZ_FORWARD_DOUBLE_LINK
#define ZZbwdDLink ZZ_BACKWARD_DOUBLE_LINK
#define ZZdelGLink ZZ_DELETE_GENERAL_LINK
#define ZZdelSLink ZZ_DELETE_SINGLE_LINK
#define ZZdelDLink ZZ_DELETE_DOUBLE_LINK
#define ZZorgRefer ZZ_ORG_REFERENCE
#define ZZlocRefer ZZ_LOCAL_REFERENCE
#define ZZhypRefer ZZ_HYPER_REFERENCE
#define ZZaddRefer ZZ_ADD_REFERENCE
#define ZZdelRefer ZZ_DELETE_REFERENCE
#define ZZfwdRefer ZZ_FORWARD_REFERENCE
#define ZZsetRefer ZZ_SET_REFERENCE
#define ZZgetRefer ZZ_GET_REFERENCE
#define ZZadd ZZ_ADD
#define ZZFadd ZZF_ADD
#define ZZset ZZ_SET
#define ZZget ZZ_GET
#define ZZins ZZ_INSERT
#define ZZapp ZZ_APPEND
#define ZZdel ZZ_DELETE
#define ZZAtrav ZZ_A_TRAVERSE
#define ZZAretr ZZ_A_RETRACE
#define ZZfwd ZZ_FORWARD
#define ZZbwd ZZ_BACKWARD
#define ZZpar ZZ_PARENT
#define ZZchi ZZ_CHILD
#define ZZsort ZZ_SORT
#define ZZpop ZZ_POP
#define ZZpush ZZ_PUSH
#define ZZnodes ZZ_NODES
#define ZZptr ZZ_PTR
#define ZZaddName ZZ_ADD_NAME
#define ZZptrName ZZ_PTR_NAME
#define ZZdelName ZZ_DELETE_NAME
#define ZZfwdName ZZ_FORWARD_NAME
#define ZZorgName ZZ_ORG_NAME
#define ZZhypName ZZ_HYPER_NAME
#define ZZlocName ZZ_LOCAL_NAME
#define ZZorg1G ZZ_ORG_SINGLE_GRAPH
#define ZZhyp1G ZZ_HYPER_SINGLE_GRAPH
#define ZZloc1G ZZ_LOCAL_SINGLE_GRAPH
#define ZZadd1G ZZ_ADD_SINGLE_GRAPH
#define ZZdel1G ZZ_DELETE_SINGLE_GRAPH
#define ZZAtr1G ZZ_A_TRAVERSE_SINGLE_GRAPH
#define ZZnod1G ZZ_NODES_SINGLE_GRAPH
#define ZZorgdG ZZ_ORG_DIRECT_GRAPH
#define ZZhypdG ZZ_HYPER_DIRECT_GRAPH
#define ZZlocdG ZZ_LOCAL_DIRECT_GRAPH
#define ZZadddG ZZ_ADD_DIRECT_GRAPH
#define ZZdeldG ZZ_DELETE_DIRECT_GRAPH
#define ZZAtrdG ZZ_A_TRAVERSE_DIRECT_GRAPH
#define ZZnoddG ZZ_NODES_DIRECT_GRAPH
#define ZZorgFIFO ZZ_ORG_FIFO
#define ZZhypFIFO ZZ_HYPER_FIFO
#define ZZlocFIFO ZZ_LOCAL_FIFO
#define ZZpopFIFO ZZ_POP_FIFO
#define ZZpushFIFO ZZ_PUSH_FIFO
#define ZZorgLIFO ZZ_ORG_LIFO
#define ZZhypLIFO ZZ_HYPER_LIFO
#define ZZlocLIFO ZZ_LOCAL_LIFO
#define ZZpopLIFO ZZ_POP_LIFO
#define ZZpushLIFO ZZ_PUSH_LIFO
#define ZZorg1T ZZ_ORG_SINGLE_TREE
#define ZZhyp1T ZZ_HYPER_SINGLE_TREE
#define ZZloc1T ZZ_LOCAL_SINGLE_TREE
#define ZZadd1T ZZ_ADD_SINGLE_TREE
#define ZZset1T ZZ_SET_SINGLE_TREE
#define ZZdel1T ZZ_DELETE_SINGLE_TREE
#define ZZAtr1T ZZ_A_TRAVERSE_SINGLE_TREE
#define ZZfwd1T ZZ_FORWARD_SINGLE_TREE
#define ZZpar1T ZZ_PARENT_SINGLE_TREE
#define ZZchi1T ZZ_CHILD_SINGLE_TREE
#define ZZapp1T ZZ_APPEND_SINGLE_TREE
#define ZZorg2T ZZ_ORG_DOUBLE_TREE
#define ZZhyp2T ZZ_HYPER_DOUBLE_TREE
#define ZZloc2T ZZ_LOCAL_DOUBLE_TREE
#define ZZadd2T ZZ_ADD_DOUBLE_TREE
#define ZZset2T ZZ_SET_DOUBLE_TREE
#define ZZdel2T ZZ_DELETE_DOUBLE_TREE
#define ZZAtr2T ZZ_A_TRAVERSE_DOUBLE_TREE
#define ZZfwd2T ZZ_FORWARD_DOUBLE_TREE
#define ZZpar2T ZZ_PARENT_DOUBLE_TREE
#define ZZchi2T ZZ_CHILD_DOUBLE_TREE
#define ZZbwd2T ZZ_BACKWARD_DOUBLE_TREE
#define ZZArt2T ZZ_A_RETRACE_DOUBLE_TREE
#define ZZins2T ZZ_INSERT_DOUBLE_TREE
#define ZZapp2T ZZ_APPEND_DOUBLE_TREE
#define ZZorgArr ZZ_ORG_ARRAY
#define ZZhypArr ZZ_HYPER_ARRAY
#define ZZlocArr ZZ_LOCAL_ARRAY
#define ZZheadArr ZZ_HEAD_ARRAY
#define ZZformArr ZZ_FORM_ARRAY
#define ZZfreeArr ZZ_FREE_ARRAY
#define ZZsizeArr ZZ_SIZE_ARRAY
#define ZZindArr ZZ_INDEX_ARRAY
#define ZZindHeap ZZ_INDEX_HEAP
#define ZZpushArr ZZ_PUSH_ARRAY
#define ZZpopArr ZZ_POP_ARRAY
#define ZZsortArr ZZ_SORT_ARRAY
#define ZZresArr ZZ_RESET_ARRAY
#define ZZinHeap ZZ_IN_HEAP
#define ZZoutHeap ZZ_OUT_HEAP
#define ZZupdHeap ZZ_UPDATE_HEAP
#define ZZdelHeap ZZ_DELETE_HEAP
#define ZZorgHash ZZ_ORG_HASH
#define ZZhypHash ZZ_HYPER_HASH
#define ZZlocHash ZZ_LOCAL_HASH
#define ZZformHash ZZ_FORM_HASH
#define ZZsizeHash ZZ_SIZE_HASH
#define ZZslotHash ZZ_SLOT_HASH
#define ZZAtravHash ZZ_A_TRAVERSE_HASH
#define ZZresHash ZZ_RESIZE_HASH
#define ZZaddHash ZZ_ADD_HASH
#define ZZadd2Hash ZZ_ADD2_HASH
#define ZZdelHash ZZ_DELETE_HASH
#define ZZgetHash ZZ_GET_HASH
#define ZZfreeHash ZZ_FREE_HASH
#define ZZorg1to1 ZZ_ORG_1_TO_1
#define ZZorg1toN ZZ_ORG_1_TO_N
#define ZZorgMto1 ZZ_ORG_M_TO_1
#define ZZorgMtoN ZZ_ORG_M_TO_N
#define ZZhyp1to1 ZZ_HYPER_1_TO_1
#define ZZloc1to1 ZZ_LOCAL_1_TO_1
#define ZZhyp1toN ZZ_HYPER_1_TO_N
#define ZZloc1toN ZZ_LOCAL_1_TO_N
#define ZZhypMto1 ZZ_HYPER_M_TO_1
#define ZZlocMto1 ZZ_LOCAL_M_TO_1
#define ZZhypMtoN ZZ_HYPER_M_TO_N
#define ZZlocMtoN ZZ_LOCAL_M_TO_N
#define ZZtarget ZZ_TARGET
#define ZZsource ZZ_SOURCE
#define ZZaddRel ZZ_ADD_RELATION
#define ZZdelRel ZZ_DELETE_RELATION
#define ZZFaddRel ZZF_ADD_RELATION
#define ZZFdelRel ZZF_DELETE_RELATION
#define ZZtarg1to1 ZZ_TARGET_1_TO_1
#define ZZtarg1toN ZZ_TARGET_1_TO_N
#define ZZtargMto1 ZZ_TARGET_M_TO_1
#define ZZtargMtoN ZZ_TARGET_M_TO_N
#define ZZsour1to1 ZZ_SOURCE_1_TO_1
#define ZZsour1toN ZZ_SOURCE_1_TO_N
#define ZZsourMto1 ZZ_SOURCE_M_TO_1
#define ZZsourMtoN ZZ_SOURCE_M_TO_N
#define ZZfwd1to1 ZZ_FORWARD_1_TO_1
#define ZZfwd1toN ZZ_FORWARD_1_TO_N
#define ZZfwdMto1 ZZ_FORWARD_M_TO_1
#define ZZfwdMtoN ZZ_FORWARD_M_TO_N
#define ZZbwd1to1 ZZ_BACKWARD_1_TO_1
#define ZZbwd1toN ZZ_BACKWARD_1_TO_N
#define ZZbwdMto1 ZZ_BACKWARD_M_TO_1
#define ZZbwdMtoN ZZ_BACKWARD_M_TO_N
#define ZZAtrav1to1 ZZ_A_TRAVERSE_1_TO_1
#define ZZAtrav1toN ZZ_A_TRAVERSE_1_TO_N
#define ZZAtravMto1 ZZ_A_TRAVERSE_M_TO_1
#define ZZAtravMtoN ZZ_A_TRAVERSE_M_TO_N
#define ZZAretr1to1 ZZ_A_RETRACE_1_TO_1
#define ZZAretr1toN ZZ_A_RETRACE_1_TO_N
#define ZZAretrMto1 ZZ_A_RETRACE_M_TO_1
#define ZZAretrMtoN ZZ_A_RETRACE_M_TO_N
#define ZZadd1to1 ZZ_ADD_RELATION_1_TO_1
#define ZZadd1toN ZZ_ADD_RELATION_1_TO_N
#define ZZaddMto1 ZZ_ADD_RELATION_M_TO_1
#define ZZaddMtoN ZZ_ADD_RELATION_M_TO_N
#define ZZdel1to1 ZZ_DELETE_RELATION_1_TO_1
#define ZZdel1toN ZZ_DELETE_RELATION_1_TO_N
#define ZZdelMto1 ZZ_DELETE_RELATION_M_TO_1
#define ZZdelMtoN ZZ_DELETE_RELATION_M_TO_N
#define ZZFadd1to1 ZZF_ADD_RELATION_1_TO_1
#define ZZFadd1toN ZZF_ADD_RELATION_1_TO_N
#define ZZFaddMto1 ZZF_ADD_RELATION_M_TO_1
#define ZZFaddMtoN ZZF_ADD_RELATION_M_TO_N
#define ZZFdel1to1 ZZF_DELETE_RELATION_1_TO_1
#define ZZFdel1toN ZZF_DELETE_RELATION_1_TO_N
#define ZZFdelMto1 ZZF_DELETE_RELATION_M_TO_1
#define ZZFdelMtoN ZZF_DELETE_RELATION_M_TO_N
#define ZZadd1C ZZ_ADD_SINGLE_COLLECT
#define ZZmer1C ZZ_MERGE_SINGLE_COLLECT
#define ZZfwd1C ZZ_FORWARD_SINGLE_COLLECT
#define ZZchi1C ZZ_CHILD_SINGLE_COLLECT
#define ZZdel1C ZZ_DELETE_SINGLE_COLLECT
#define ZZAtrav1C ZZ_A_TRAVERSE_SINGLE_COLLECT
#define ZZset1C ZZ_SET_SINGLE_COLLECT
#define ZZsrt1C ZZ_SORT_SINGLE_COLLECT
#define ZZorg1C ZZ_ORG_SINGLE_COLLECT
#define ZZhyp1C ZZ_HYPER_SINGLE_COLLECT
#define ZZloc1C ZZ_LOCAL_SINGLE_COLLECT
#define ZZadd2C ZZ_ADD_DOUBLE_COLLECT
#define ZZins2C ZZ_INSERT_DOUBLE_COLLECT
#define ZZmer2C ZZ_MERGE_DOUBLE_COLLECT
#define ZZfwd2C ZZ_FORWARD_DOUBLE_COLLECT
#define ZZbwd2C ZZ_BACKWARD_DOUBLE_COLLECT
#define ZZchi2C ZZ_CHILD_DOUBLE_COLLECT
#define ZZdel2C ZZ_DELETE_DOUBLE_COLLECT
#define ZZAtrav2C ZZ_A_TRAVERSE_DOUBLE_COLLECT
#define ZZAretr2C ZZ_A_RETRACE_DOUBLE_COLLECT
#define ZZset2C ZZ_SET_DOUBLE_COLLECT
#define ZZsrt2C ZZ_SORT_DOUBLE_COLLECT
#define ZZorg2C ZZ_ORG_DOUBLE_COLLECT
#define ZZhyp2C ZZ_HYPER_DOUBLE_COLLECT
#define ZZloc2C ZZ_LOCAL_DOUBLE_COLLECT
#define ZZ3merD ZZ_MERGE_DOUBLE_TRIANGLE
#define ZZ3addD ZZ_ADD_DOUBLE_TRIANGLE
#define ZZ3insD ZZ_INSERT_DOUBLE_TRIANGLE
#define ZZ3fwdD ZZ_FORWARD_DOUBLE_TRIANGLE
#define ZZ3bwdD ZZ_BACKWARD_DOUBLE_TRIANGLE
#define ZZ3chiD ZZ_CHILD_DOUBLE_TRIANGLE
#define ZZ3delD ZZ_DELETE_DOUBLE_TRIANGLE
#define ZZA3travD ZZ_A_TRAVERSE_DOUBLE_TRIANGLE
#define ZZA3retrD ZZ_A_RETRACE_DOUBLE_TRIANGLE
#define ZZ3parD ZZ_PARENT_DOUBLE_TRIANGLE
#define ZZ3srtD ZZ_SORT_DOUBLE_TRIANGLE
#define ZZ3setD ZZ_SET_DOUBLE_TRIANGLE
#define ZZorg2Tri ZZ_ORG_DOUBLE_TRIANGLE
#define ZZhyp2Tri ZZ_HYPER_DOUBLE_TRIANGLE
#define ZZhyp2Agr ZZ_HYPER_DOUBLE_AGGREGATE
#define ZZloc2Tri ZZ_LOCAL_DOUBLE_TRIANGLE
#define ZZloc2Agr ZZ_LOCAL_DOUBLE_AGGREGATE
#define ZZhyp1BT ZZ_HYPER_BINARY_TREE
