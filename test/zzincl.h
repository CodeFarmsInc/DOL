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
#define ZZIint ZZZIint()
ZZ_LOCAL int ZZZIint(void);
#define ZZIfloat ZZZIfloat()
ZZ_LOCAL int ZZZIfloat(void);
#define ZZIchar ZZZIchar()
ZZ_LOCAL int ZZZIchar(void);
#ifdef ZZmain
ZZ_LOCAL int ZZZIint(void){return(-6);}
ZZ_LOCAL int ZZZIfloat(void){return(-7);}
ZZ_LOCAL int ZZZIchar(void){return(-1);}

#endif
#ifdef ZZmain

ZZ_LOCAL char *ZZptrList[]={
""
};

ZZ_LOCAL struct ZZstrLST ZZstrList[1]={
  {(char*)"ZZendMark", -1, -1, -1, -1, -1, -1, -1, 0, 0, {0, 0}, 0}};


ZZ_LOCAL ZZint ZZnxtType[1]={
0
};

ZZ_LOCAL struct ZZtypeHier ZZinhList[1]={
 {-1, -1, -1, (char*)"ZZendMark"}
};
#else
extern char *ZZptrList[];
extern struct ZZstrLST ZZstrList[];
extern ZZint ZZnxtType[];
extern struct ZZtypeHier ZZinhList[];
#endif
#define ZZstrNum 0



#ifdef ZZmain
ZZ_LOCAL int ZZbindASCII={0};
#ifdef SUN
ZZ_LOCAL int ZZnoLeak={0};
#else
ZZ_LOCAL int ZZnoLeak={1};
#endif
ZZ_LOCAL int ZZinhFLG={1};
ZZ_LOCAL int ZZvClassPresent={0};
ZZ_LOCAL ZZint ZZallocPtr={0};
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
