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

#define ZZ_EXT_B2 \
friend class ZZHB1_B2_links;\
\
public:\
    void *zzThisIs(ZZint *type){*type=0; return((void*)this);};\
    void ZZinitSet(void){if(ZZnumObjects>0)ZZnumObjects--; ZZSS_B2(this)};\
   ~B2(){ZZ_CHECK(B2);};\
    B2(ZZZiClass *);\
    void * operator new(size_t size);\
    void operator delete(void *ptr);\
    static B2 *newObj(void){B2 *p; ZZ_OBJECT_NEW(B2,p); return p;}\
    static void delObj(B2 *p){ZZ_OBJECT_FREE(B2,p);}


#define ZZ_EXT_B1 \
friend class ZZHB1_B2_links;\
    B2 *ZZfB1_B2_links;\
public:\
    void *zzThisIs(ZZint *type){*type=1; return((void*)this);};\
    void ZZinitSet(void){if(ZZnumObjects>0)ZZnumObjects--; ZZSS_B1(this)};\
   ~B1(){ZZ_CHECK(B1);};\
    B1(ZZZiClass *);\
    void * operator new(size_t size);\
    void operator delete(void *ptr);\
    static B1 *newObj(void){B1 *p; ZZ_OBJECT_NEW(B1,p); return p;}\
    static void delObj(B1 *p){ZZ_OBJECT_FREE(B1,p);}

#define ZZIB2 0
#define ZZJB2 -1
#define ZZIB1 1
#define ZZJB1 -1
#define ZZIint   -6
#define ZZIfloat -7
#define ZZIchar  -1


static ZZ_LOCAL char *ZZptrList[]={
    (char*)"aZZfB1_B2_links[1"
};

static ZZ_LOCAL struct ZZstrLST ZZstrList[3]={
  {(char*)"B2", 0, 0, 0, -1, -1, -1, -1, 0, 0, {0,0}, 0}, 
  {(char*)"B1", 0, 0, 1, -1, -1, -1, -1, 0, 0, {0,0}, 0}, 
  {(char*)"ZZendMark", -1, -1, -1, -1, -1, -1, -1, 1, 0, {0, 0}, 0}};


static ZZ_LOCAL ZZint ZZnxtType[1]={
 0
};

static ZZ_LOCAL struct ZZtypeHier ZZinhList[1]={
 {-1, -1, -1, (char*)"ZZendMark"}
};
#define ZZstrNum 2
#define ZZSS_B2(P) {\
 ZZstrList[0].start=0;\
 ZZstrList[0].size=(int)sizeof(B2);}

#define ZZS_B2 ZZSS_B2(this)

#define ZZSS_B1(P) {B1 *ZZp; ZZsigIntType ZZi;\
 ZZp=P; ZZp=ZZp;\
ZZi=(ZZsigIntType)ZZp;\
ZZstrList[1].start=ZZptrToInt((char *)((ZZsigIntType)(&(ZZp->ZZfB1_B2_links))-ZZi));\
 ZZstrList[1].size=(int)sizeof(B1);}

#define ZZS_B1 ZZSS_B1(this)
#define B1_B2_links_class ZZHB1_B2_links
#define ZZ1B1_B2_links B1
#define ZZX1B1_B2_links "B1"
#define ZZH1B1_B2_links "B1"
#define ZZW1B1_B2_links 1
#define ZZ2B1_B2_links B2
#define ZZX2B1_B2_links "B2"
#define ZZH2B1_B2_links "B2"
#define ZZW2B1_B2_links 0
#define ZZVB1_B2_links  



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
class B2;
class B1;
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
