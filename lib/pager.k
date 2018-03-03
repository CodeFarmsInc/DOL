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

#define ZZ_EXT_Page \
friend class ZZHzz_pageHash;\
friend class ZZHzz_pages;\
    Page *ZZbzz_pages;\
    Page *ZZfzz_pages;\
    Page *ZZfzz_pageHash;\
public:\
    void *zzThisIs(ZZint *type){*type=0; return((void*)this);};\
    void ZZinitSet(void){if(ZZnumObjects>0)ZZnumObjects--; ZZSS_Page(this)};\
    Page(ZZZiClass *);\
    void * operator new(size_t size);\
    void operator delete(void *ptr);\
    static Page *newObj(void){Page *p; ZZ_OBJECT_NEW(Page,p); return p;}\
    static void delObj(Page *p){ZZ_OBJECT_FREE(Page,p);}


#define ZZ_EXT_zzHead \
friend class ZZHzz_heads;\
friend class ZZHzz_pageHash;\
friend class ZZHzz_pages;\
friend class ZZHzz_fileName;\
    char *ZZnzz_fileName;\
    Page *ZZczz_pages;\
    zzHead *ZZbzz_heads;\
    zzHead *ZZfzz_heads;\
    ZZarray *ZZazz_pageHash;\
public:\
    void *zzThisIs(ZZint *type){*type=1; return((void*)this);};\
    void ZZinitSet(void){if(ZZnumObjects>0)ZZnumObjects--; ZZSS_zzHead(this)};\
    zzHead(ZZZiClass *);\
    void * operator new(size_t size);\
    void operator delete(void *ptr);\
    static zzHead *newObj(void){zzHead *p; ZZ_OBJECT_NEW(zzHead,p); return p;}\
    static void delObj(zzHead *p){ZZ_OBJECT_FREE(zzHead,p);}

#define ZZIPage ZZZIPage()
ZZ_LOCAL int ZZZIPage(void);
#define ZZJPage ZZZJPage()
ZZ_LOCAL int ZZZJPage(void);
#define ZZIzzHead ZZZIzzHead()
ZZ_LOCAL int ZZZIzzHead(void);
#define ZZJzzHead ZZZJzzHead()
ZZ_LOCAL int ZZZJzzHead(void);
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
    (char*)"aZZbzz_pages[1",
    (char*)"aZZfzz_pages[1",
    (char*)"aZZfzz_pageHash[1",
    (char*)"aZZnzz_fileName[1",
    (char*)"aZZczz_pages[1",
    (char*)"aZZbzz_heads[1",
    (char*)"aZZfzz_heads[1",
    (char*)"AZZazz_pageHash[1"
};

ZZ_LOCAL struct ZZstrLST ZZstrList[3]={
  {(char*)"Page", 0, 0, 3, -1, -1, -1, -1, 0, 0, {0,0}, 0}, 
  {(char*)"zzHead", 0, 0, 5, -1, -1, -1, 4, 3, 0, {0,0}, 0}, 
  {(char*)"ZZendMark", -1, -1, -1, -1, -1, -1, -1, 8, 0, {0, 0}, 0}};


ZZ_LOCAL ZZint ZZnxtType[8]={
 0,0,0,
 -1,0,1,1,-4
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
#define ZZstrNum 2

#define ZZSS_Page(P) {Page *ZZp; ZZsigIntType ZZi;\
 ZZp=P; ZZp=ZZp;\
ZZi=(ZZsigIntType)ZZp;\
ZZstrList[0].start=ZZptrToInt((char *)((ZZsigIntType)(&(ZZp->ZZbzz_pages))-ZZi));\
 ZZstrList[0].size=(int)sizeof(Page);}

#define ZZS_Page ZZSS_Page(this)

#define ZZSS_zzHead(P) {zzHead *ZZp; ZZsigIntType ZZi;\
 ZZp=P; ZZp=ZZp;\
ZZi=(ZZsigIntType)ZZp;\
ZZstrList[1].start=ZZptrToInt((char *)((ZZsigIntType)(&(ZZp->ZZnzz_fileName))-ZZi));\
 ZZstrList[1].size=(int)sizeof(zzHead);}

#define ZZS_zzHead ZZSS_zzHead(this)
#define zz_fileName_class ZZHzz_fileName
#define ZZ1zz_fileName zzHead
#define ZZX1zz_fileName "zzHead"
#define ZZH1zz_fileName "zzHead"
#define ZZW1zz_fileName 1
#define ZZVzz_fileName  
#define zz_pages_class ZZHzz_pages
#define ZZ1zz_pages zzHead
#define ZZX1zz_pages "zzHead"
#define ZZH1zz_pages "zzHead"
#define ZZW1zz_pages 1
#define ZZ2zz_pages Page
#define ZZX2zz_pages "Page"
#define ZZH2zz_pages "Page"
#define ZZW2zz_pages 0
#define ZZVzz_pages  
#define zz_pageHash_class ZZHzz_pageHash
#define ZZ1zz_pageHash zzHead
#define ZZX1zz_pageHash "zzHead"
#define ZZH1zz_pageHash "zzHead"
#define ZZW1zz_pageHash 1
#define ZZ2zz_pageHash Page
#define ZZX2zz_pageHash "Page"
#define ZZH2zz_pageHash "Page"
#define ZZW2zz_pageHash 0
#define ZZVzz_pageHash  
#define zz_heads_class ZZHzz_heads
#define ZZ1zz_heads zzHead
#define ZZX1zz_heads "zzHead"
#define ZZH1zz_heads "zzHead"
#define ZZW1zz_heads 1
#define ZZVzz_heads  



#ifdef ZZmain
ZZ_LOCAL int ZZbindASCII={0};
#ifdef SUN
ZZ_LOCAL int ZZnoLeak={0};
#else
ZZ_LOCAL int ZZnoLeak={1};
#endif
ZZ_LOCAL int ZZinhFLG={1};
ZZ_LOCAL int ZZvClassPresent={0};
ZZ_LOCAL ZZint ZZallocPtr={16};
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
class Page;
class zzHead;
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
