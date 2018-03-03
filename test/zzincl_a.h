#ifndef zzinclUsed
#define zzinclUsed
#ifdef ZZmain
char *ZZorgcVersion={(char*)"Version 9.7"};
#else
extern char *ZZorgcVersion;
#endif
#include "environ.h"
#ifndef FILE
#include <stdio.h>
#endif
#include "..\zzcomb.h"
#include "..\lib\msgs.h"

class ZZZiClass{};
#ifndef ZZmain
extern
#endif

ZZ_LOCAL char *ZZselfArr[1]
#ifdef ZZmain
={
(char*)"ZZendMark"}
#endif
;
#define ZZnID 1

#define ZZ_EXT_A2 \
friend class ZZHA1_A2_links;\
\
public:\
    void *zzThisIs(ZZint *type){*type=0; return((void*)this);};\
    void ZZinitSet(void){if(ZZnumObjects>0)ZZnumObjects--; ZZSS_A2(this)};\
   ~A2(){ZZ_CHECK(A2);};\
    A2(ZZZiClass *);\
    void * operator new(size_t size);\
    void operator delete(void *ptr);\
    static A2 *newObj(void){A2 *p; ZZ_OBJECT_NEW(A2,p); return p;}\
    static void delObj(A2 *p){ZZ_OBJECT_FREE(A2,p);}


#define ZZ_EXT_A1 \
friend class ZZHA1_A2_links;\
    A2 *ZZfA1_A2_links;\
public:\
    void *zzThisIs(ZZint *type){*type=1; return((void*)this);};\
    void ZZinitSet(void){if(ZZnumObjects>0)ZZnumObjects--; ZZSS_A1(this)};\
   ~A1(){ZZ_CHECK(A1);};\
    A1(ZZZiClass *);\
    void * operator new(size_t size);\
    void operator delete(void *ptr);\
    static A1 *newObj(void){A1 *p; ZZ_OBJECT_NEW(A1,p); return p;}\
    static void delObj(A1 *p){ZZ_OBJECT_FREE(A1,p);}

#define ZZIA2 0
#define ZZJA2 -1
#define ZZIA1 1
#define ZZJA1 -1
#define ZZIint   -6
#define ZZIfloat -7
#define ZZIchar  -1


static ZZ_LOCAL char *ZZptrList[]={
    (char*)"aZZfA1_A2_links[1"
};

static ZZ_LOCAL struct ZZstrLST ZZstrList[3]={
  {(char*)"A2", 0, 0, 0, -1, -1, -1, -1, 0, 0, {0,0}, 0}, 
  {(char*)"A1", 0, 0, 1, -1, -1, -1, -1, 0, 0, {0,0}, 0}, 
  {(char*)"ZZendMark", -1, -1, -1, -1, -1, -1, -1, 1, 0, {0, 0}, 0}};


static ZZ_LOCAL ZZint ZZnxtType[1]={
 0
};

static ZZ_LOCAL struct ZZtypeHier ZZinhList[1]={
 {-1, -1, -1, (char*)"ZZendMark"}
};
#define ZZstrNum 2
#define ZZSS_A2(P) {\
 ZZstrList[0].start=0;\
 ZZstrList[0].size=(int)sizeof(A2);}

#define ZZS_A2 ZZSS_A2(this)

#define ZZSS_A1(P) {A1 *ZZp; ZZsigIntType ZZi;\
 ZZp=P; ZZp=ZZp;\
ZZi=(ZZsigIntType)ZZp;\
ZZstrList[1].start=ZZptrToInt((char *)((ZZsigIntType)(&(ZZp->ZZfA1_A2_links))-ZZi));\
 ZZstrList[1].size=(int)sizeof(A1);}

#define ZZS_A1 ZZSS_A1(this)
#define A1_A2_links_class ZZHA1_A2_links
#define ZZ1A1_A2_links A1
#define ZZX1A1_A2_links "A1"
#define ZZH1A1_A2_links "A1"
#define ZZW1A1_A2_links 1
#define ZZ2A1_A2_links A2
#define ZZX2A1_A2_links "A2"
#define ZZH2A1_A2_links "A2"
#define ZZW2A1_A2_links 0
#define ZZVA1_A2_links  



#ifdef ZZmain
ZZ_LOCAL int ZZbindASCII={0};
#ifdef SUN
ZZ_LOCAL int ZZnoLeak={0};
#else
ZZ_LOCAL int ZZnoLeak={1};
#endif
ZZ_LOCAL int ZZinhFLG={1};
ZZ_LOCAL int ZZvClassPresent={0};
ZZ_LOCAL ZZint ZZallocPtr={2};
#endif
#ifndef ZZmain
extern int ZZbindASCII;
extern int ZZnoLeak;
extern int ZZinhFLG;
extern int ZZvClassPresent;
extern ZZint ZZallocPtr;
#endif
#ifdef ZZ_ANSI
#ifdef ZZmain
ZZ_LOCAL ZZint ZZioFunction(FILE *fp,ZZint io,ZZint type,char *p,ZZint strSz){
fp=fp; io=io; type=type; p=p; return(0);}
#endif
#else
#ifdef ZZmain
ZZ_LOCAL ZZint ZZioFunction(fp,(ZZint)io,(ZZint)type,p,strSz)
FILE *fp;int io; int type;char *p;ZZint strSz;{
fp=fp; io=io; type=type; p=p; return(0);}
#endif
#endif
class A2;
class A1;
#ifdef ZZmultiProj
/* dummy function to prevent compiler warnings */
#ifdef ZZ_ANSI
static void *ZZnoWarnings(void){
#else
static void *ZZnoWarnings(){
#endif
    void *p;
    p=(void *)ZZstrList; p=(void *)ZZptrList;
    p=(void *)ZZnxtType; p=(void *)ZZinhList;
    return(p);
}
#endif
#endif
