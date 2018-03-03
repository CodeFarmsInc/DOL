#ifndef zzinclUsed
#define zzinclUsed
#ifdef ZZmain
char *ZZorgcVersion={(char*)"Version 9.1"};
#else
extern char *ZZorgcVersion;
#endif
#include "c:\orgc\lib\environ.h"
#ifndef FILE
#include <stdio.h>
#endif
#include "c:\orgc\zzcomb.h"
#include "c:\orgc\lib\msgs.h"

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

#define ZZ_EXT_Author \
friend class ZZHauthors;\
friend class ZZHtoAuthor;\
friend class ZZHauthName;\
    char *ZZnauthName;\
    Author *ZZsauthors;\
public:\
    void *zzThisIs(ZZint *type){*type=0; return((void*)this);};\
    void ZZinitSet(void){if(ZZnumObjects>0)ZZnumObjects--; ZZS_Author};\
   ~Author(){ZZ_CHECK(Author);};\
    Author(ZZZiClass *);\
    void * operator new(size_t size);\
    void operator delete(void *ptr);\
    int zz_inp_Author(FILE *,Author *);\
    int zz_out_Author(FILE *,Author *);\
    void zz_ipt_Author(Author *);\
    void zz_opt_Author(FILE *,Author *);


#define ZZ_EXT_Book \
friend class ZZHallBooks;\
friend class ZZHtoAuthor;\
friend class ZZHbookName;\
    char *ZZnbookName;\
    Author *ZZftoAuthor;\
    Book *ZZfallBooks;\
public:\
    void *zzThisIs(ZZint *type){*type=1; return((void*)this);};\
    void ZZinitSet(void){if(ZZnumObjects>0)ZZnumObjects--; ZZS_Book};\
   ~Book(){ZZ_CHECK(Book);};\
    Book(ZZZiClass *x);\
    void * operator new(size_t size);\
    void operator delete(void *ptr);\
    int zz_inp_Book(FILE *,Book *);\
    int zz_out_Book(FILE *,Book *);\
    void zz_ipt_Book(Book *);\
    void zz_opt_Book(FILE *,Book *);


#define ZZ_EXT_Publication \
friend class ZZHpublications;\
    Publication *ZZspublications;\
public:\
    void *zzThisIs(ZZint *type){*type=2; return((void*)this);};\
    void ZZinitSet(void){if(ZZnumObjects>0)ZZnumObjects--; ZZS_Publication};\
    Publication(){};\
   ~Publication(){ZZ_CHECK(Publication);};\
    Publication(ZZZiClass *);\
    void * operator new(size_t size);\
    void operator delete(void *ptr);\
    int zz_inp_Publication(FILE *,Publication *);\
    int zz_out_Publication(FILE *,Publication *);\
    void zz_ipt_Publication(Publication *);\
    void zz_opt_Publication(FILE *,Publication *);


#define ZZ_EXT_Library \
friend class ZZHpublications;\
friend class ZZHallBooks;\
friend class ZZHauthors;\
    Author *ZZcauthors;\
    Publication *ZZcpublications;\
    ZZarray *ZZaallBooks;\
public:\
    void *zzThisIs(ZZint *type){*type=3; return((void*)this);};\
    void ZZinitSet(void){if(ZZnumObjects>0)ZZnumObjects--; ZZS_Library};\
   ~Library(){ZZ_CHECK(Library);};\
    Library(ZZZiClass *);\
    void * operator new(size_t size);\
    void operator delete(void *ptr);\
    int zz_inp_Library(FILE *,Library *);\
    int zz_out_Library(FILE *,Library *);\
    void zz_ipt_Library(Library *);\
    void zz_opt_Library(FILE *,Library *);

#define ZZIAuthor ZZZIAuthor()
ZZ_LOCAL int ZZZIAuthor(void);
#define ZZJAuthor ZZZJAuthor()
ZZ_LOCAL int ZZZJAuthor(void);
#define ZZIBook ZZZIBook()
ZZ_LOCAL int ZZZIBook(void);
#define ZZJBook ZZZJBook()
ZZ_LOCAL int ZZZJBook(void);
#define ZZIPublication ZZZIPublication()
ZZ_LOCAL int ZZZIPublication(void);
#define ZZJPublication ZZZJPublication()
ZZ_LOCAL int ZZZJPublication(void);
#define ZZILibrary ZZZILibrary()
ZZ_LOCAL int ZZZILibrary(void);
#define ZZJLibrary ZZZJLibrary()
ZZ_LOCAL int ZZZJLibrary(void);
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
    (char*)"aZZnauthName[1",
    (char*)"aZZsauthors[1",
    (char*)"aZZnbookName[1",
    (char*)"aZZftoAuthor[1",
    (char*)"aZZfallBooks[1",
    (char*)"aZZspublications[1",
    (char*)"aZZcauthors[1",
    (char*)"aZZcpublications[1",
    (char*)"AZZaallBooks[1"
};

ZZ_LOCAL struct ZZstrLST ZZstrList[5]={
  {(char*)"Author", 0, 0, 2, -1, -1, -1, -1, 0, 0, {0,0}, 0}, 
  {(char*)"Book", 0, 0, 3, -1, -1, -1, -1, 2, 0, {0,0}, 0}, 
  {(char*)"Publication", 0, 0, 1, -1, -1, -1, -1, 5, 1, {0,0}, 0}, 
  {(char*)"Library", 0, 0, 3, -1, -1, -1, 2, 6, 1, {0,0}, 0}, 
  {(char*)"ZZendMark", -1, -1, -1, -1, -1, -1, -1, 9, 1, {0, 0}, 0}};


ZZ_LOCAL ZZint ZZnxtType[9]={
 -1,0,
 -1,0,1,
 2,
 0,2,-4
};

ZZ_LOCAL struct ZZtypeHier ZZinhList[2]={
 {2, -1, 0, (char*)"ZZinherit"},
 {-1, -1, -1, (char*)"ZZendMark"}
};
#else
extern char *ZZptrList[];
extern struct ZZstrLST ZZstrList[];
extern ZZint ZZnxtType[];
extern struct ZZtypeHier ZZinhList[];
#endif
#define ZZstrNum 4

#define ZZS_Author {Author *ZZp; ZZsigIntType ZZi;\
 ZZp=this; ZZp=ZZp;\
ZZi=(ZZsigIntType)ZZp;\
ZZstrList[0].start=ZZptrToInt((char *)((ZZsigIntType)(&(ZZp->ZZnauthName))-ZZi));\
 ZZstrList[0].size=(int)sizeof(Author);}

#define ZZS_Book {Book *ZZp; ZZsigIntType ZZi;\
 ZZp=this; ZZp=ZZp;\
ZZi=(ZZsigIntType)ZZp;\
ZZstrList[1].start=ZZptrToInt((char *)((ZZsigIntType)(&(ZZp->ZZnbookName))-ZZi));\
  ZZinhList[0].offset=ZZstrList[2].start;\
 ZZstrList[1].size=(int)sizeof(Book);}

#define ZZS_Publication {Publication *ZZp; ZZsigIntType ZZi;\
 ZZp=this; ZZp=ZZp;\
ZZi=(ZZsigIntType)ZZp;\
ZZstrList[2].start=ZZptrToInt((char *)((ZZsigIntType)(&(ZZp->ZZspublications))-ZZi));\
 ZZstrList[2].size=(int)sizeof(Publication);}

#define ZZS_Library {Library *ZZp; ZZsigIntType ZZi;\
 ZZp=this; ZZp=ZZp;\
ZZi=(ZZsigIntType)ZZp;\
ZZstrList[3].start=ZZptrToInt((char *)((ZZsigIntType)(&(ZZp->ZZcauthors))-ZZi));\
 ZZstrList[3].size=(int)sizeof(Library);}
#define authName_class ZZHauthName
#define ZZ1authName Author
#define ZZX1authName "Author"
#define ZZW1authName 0
#define ZZVauthName  
#define bookName_class ZZHbookName
#define ZZ1bookName Book
#define ZZX1bookName "Book"
#define ZZW1bookName 1
#define ZZVbookName  
#define toAuthor_class ZZHtoAuthor
#define ZZ1toAuthor Book
#define ZZX1toAuthor "Book"
#define ZZW1toAuthor 1
#define ZZ2toAuthor Author
#define ZZX2toAuthor "Author"
#define ZZW2toAuthor 0
#define ZZVtoAuthor  
#define authors_class ZZHauthors
#define ZZ1authors Library
#define ZZX1authors "Library"
#define ZZW1authors 3
#define ZZ2authors Author
#define ZZX2authors "Author"
#define ZZW2authors 0
#define ZZVauthors  
#define allBooks_class ZZHallBooks
#define ZZ1allBooks Library
#define ZZX1allBooks "Library"
#define ZZW1allBooks 3
#define ZZ2allBooks Book
#define ZZX2allBooks "Book"
#define ZZW2allBooks 1
#define ZZVallBooks  
#define publications_class ZZHpublications
#define ZZ1publications Library
#define ZZX1publications "Library"
#define ZZW1publications 3
#define ZZ2publications Publication
#define ZZX2publications "Publication"
#define ZZW2publications 2
#define ZZVpublications  



#ifdef ZZmain
ZZ_LOCAL int ZZbindASCII={1};
#ifdef SUN
ZZ_LOCAL int ZZnoLeak={0};
#else
ZZ_LOCAL int ZZnoLeak={1};
#endif
ZZ_LOCAL int ZZinhFLG={1};
ZZ_LOCAL int ZZvClassPresent={0};
ZZ_LOCAL ZZint ZZallocPtr={36};
#endif
#ifndef ZZmain
extern int ZZbindASCII;
extern int ZZnoLeak;
extern int ZZinhFLG;
extern int ZZvClassPresent;
extern ZZint ZZallocPtr;
#endif
class Author;
class Book;
class Publication;
class Library;
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
