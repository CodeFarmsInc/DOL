/****************************************************************/
/*							      	*/
/*   Copyright (C) 2001-2011                  			*/
/*	Code Farms Inc.,  All Rights Reserved.			*/
/*							  	*/
/****************************************************************/


// Ver. 8.5 passed all the testsunder Visual Studio 2010,
// under both Windows XP and Windows 7/64 bits.
// Everything worked without change on pure XP 32 bit system.

// Ver. 8.6  after of an extensive overview and testing with Petr Machacek
// - Pager: comand addr() removed, io() returns number of characters moved.
//     test62 (directory) was added to the regression tests, it tests
//     PAGER, GRAPH, TREE, and also the UML diagram (Layout).
// - First ASCII save, later memory blasting within the same run did not run
//   and required extensive corrections with ZZmemSwitch and ZZbindASCII.
// - The previous versions required "lib/types.h" to be included, and
//   this requirement has been removed.
// - Hash table now has two optional loops: traversing objects in the
//   same bucket, or traversing the entire hash table.
// Ver. 9.0 Underwent a complete review of memory blasting which caused
//   crashes on Machacek's benchmark.h over 1 million books, and the times
//   began to grow exponencially for large numbers - now they are linear.
//   Improvements of performance: Processing bitmap in bigger chunks of 0's,
//   Storing only the used section of the last page, reducing the size of
//   internal arrays by cutting away the lower (unused) part of the array.
//   The problem now can freely grow over the originally estimated size with
//   a very little overhead.
// Ver.9.1 has a better conversion of virt.fun.pointers, it works even
//   when the compiler does not keep exactly the same table.
//   The error that caused crash in clear() for memory blasting was corrected.
//   - Also, there is a performance optimization when memory blasting has
//   only a single active page. In that situation all regular pointers
//   simply move by the same offset.
//   - Big block feature (ZZmemSwitch=1) is now disabled, it is superseeded
//   by memmory blasting with one page, which is more efficient and does not
//   lead to problems if the data exceeds the originally anticipated space.
//   Documentation has been properly updated. (Jiri Soukup, Sept.3, 2012)
// Ver.9.2 has improvements and fixes related to the testing and sample
//   code related to Jiri's new book (Serialization and Persistent Objects).
//   - Functions newObj() and delObje() that support free lists by class
//   and are important especially in mem.blasting are now automatically 
//   provided under ZZ_EXT...
//   - Change of schema has been properly organized and documented, 
//   when done in 3 stages, it has almost unlimited capabilities.
//   - Controls have been added so that the user can save/open in
//   binary or save mode while allocating memory in the mem.blasting style.
//   This is a key step for removing objects (and especially discarded strings)
//   in mem.blasting, and was accidentally removed when removing option
//   of ZZmemSwitch=1 in Ver.9.1
// Ver.9.3: The compatibility with Linux has been renewed. We somehow lost it 
//   in several previous versions.
// Ver.9.4: Linux enabled again.
// Ver.9.5: Improvements related to Soukup/Machacek book, mostly
//          in memory blasting however, the Linux version broke down.
// Ver.9.6: Linux compatibility was restored, but test23f did not run on Linux
//          and test60d did not run on Windows.
// Ver.9.7: After a thorough revision of memory blasting, all tests run
//          under Windows and Linux. Also the testing set was expanded
//          to include on both sides the tests which were, originally, only
//          in msftregr.bat or in lgregr.   (June 10, 2014)

#define VERSION "9.7" 

#include "environ.h"
#ifdef ZZansi
#define ZZ_ANSI
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef BORLAND3
#ifdef ZZ_ANSI
/* this happens only for BORLAND 3.1 */
#include <string.h>
#include <stdlib.h>
#include <alloc.h>
#endif
#endif

#ifdef MICROSOFT
#ifdef ZZ_ANSI
/* this happens only for BORLAND 3.1 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#endif
#endif

/* This is the main include for the automatic organization preprocessor
 * called ZZprep */

#ifdef IBM
#define SUN
#endif

#ifdef MAC
#define UNIX
#define SUN
#endif

/* define DOS_NETWORK should be used in especially compiled versions only.
 * It gives a blank card for the use of orgC to anybody on the network,
 * and protects only that it is not installed in more than one place */

/* encryption key for the macros and support files,
 * files starting with /_* =_=_=_=_=_=_= ... remove _,
 * are automatically recognized as not being encrypted */
#define ZZcryptKey "sixthV"

/* some characters and values for easy coding */
#define AST '*'
#define END '\0'
#define BLANK ' '
#define TAB '\t'
#define CONT '\\'
#define LINE '\n'
#define CARET '\r'
#define USED 'u'
#define SHORT_NAME 's'
#define LONG_NAME 'l'
#define BOTH_NAMES 'b'

#ifdef VMS
#define MACRO_PATH ".macro]"
#define LIB_PATH ".lib]"
#define PATH_HERE "["
#else
#ifdef MAC
#define MACRO_PATH ":macro:"
#define LIB_PATH ":lib:"
#define PATH_HERE ""
#else
#define MACRO_PATH "/macro/"
#define LIB_PATH "/lib/"
#define PATH_HERE "."
#endif
#endif

/* end mark for chains that are not a ring, NULL reserved for loose objects */
#define ZZendMARK -1

/* range of characters to check for documentation marking lines */
#define RANGE1 4
#define RANGE2 9

/* global buffers for any I/O */

#define BUFSIZE 1024
extern char buff[BUFSIZE];
#ifdef mainCode
char buff[BUFSIZE];
#endif

#define BSIZE 80
extern char sBuff[BSIZE];
extern char fBuff[BSIZE];
#ifdef mainCode
char sBuff[BSIZE];
char fBuff[BSIZE];
#endif

typedef struct ZZorganization ZZorganization;
typedef struct ZZhierarchy ZZhierarchy;
typedef struct ZZpointer ZZpointer;
typedef struct ZZfunction ZZfunction;
typedef struct ZZextention ZZextention;
typedef struct ZZextPtr ZZextPtr;
typedef struct ZZsupport ZZsupport;
typedef struct ZZptrCode ZZptrCode;
typedef struct ZZorgInst ZZorgInst;
typedef struct ZZstrType ZZstrType;
typedef struct ZZgeneric ZZgeneric;
typedef struct ZZfunInst ZZfunInst;
typedef struct ZZnameList ZZnameList;
typedef struct ZZuml ZZuml;

struct ZZuml {
    char *name;     /* ZZ_name */
    char *dispName; /* name to be displayed, *=same as name, ?=not to display */
    char *code;     /* multiplicity code as required for the layout program */
    char *order;    /* order code for complex organizations such as M-TO_N */
    ZZuml *next;    /* NULL ending list of the registry entries */
};

struct ZZorganization {
    int ind;    /* record index: 0,1,2,... */
    char *name; /* name of this organization */
    int ptrInd; /* index to pointer specs for this organization */
    int top;    /* top poiner index */
    int nInp;   /* number of parameters used for this organ. in all macros */
    char used;  /* USED if organization used, BLANK if not used */
};
/* note that if maxid=0, pointers for this organization do not need indexing */

struct ZZhierarchy {
    ZZfunction *parent;
    ZZfunction *child;
    char *prefix;
    char *sequence;
};

struct ZZpointer {
    int ind;        /* record index: 0,1,2,... */
    int strToUse;   /* index of the structure to use this pointer */
    int strToPoint; /* index of structure to which this pointer will point */
    int aSize;      /* array size */
    char aType; /* a=aut.ptr,A=array,g=gen.link,i=int,f=float,c=char,s=string */
    char *code;     /* unique short code for the internal pointer name */
};

struct ZZfunction {
    char *sName;    /* short name, example: ZZ1travR */
    char *name;     /* example: ZZ_TRAVERSE_SINGLE_RING */
    char *fileName; /* file where this macro is stored */
    int orgInd;     /* index of the organization */
    int sup;        /* start index into the list of supports, ZZsupport */
    ZZfunInst *inst;/* list of instances, for functions only */
    char used;      /* 's'=short used,'l'=long,'b'=both, ' '=not used,'e'=end */
    char create;    /* 'o'=organize,'s'=getSelf,'r'=regular,'n'=none,'f'=func */
};

struct ZZfunInst {
    ZZorgInst *orgInst;   /* gives id and other info */
    ZZextention *ext;     /* gives extention for special functions */
    ZZfunInst *next;      /* list for the same function */
    ZZfunInst *nxt;       /* list for the same extension */
    ZZfunction *parent;   /* back to the function */
};
/* note that always one of 'orgInst' or 'ext' is NULL */
    

struct ZZsupport {
    int ind;        /* record index 0,1,2,... for convenience */
    int next;       /* next support needed for the same function, -1 for end */
    char *fileName; /* file where code stored, "" if this entry not used */
    char used;      /* 'u'=used in the user program, ' '=not used, 'e'=end */
};
/* note support chain starting from ind=0 will always be used */

#define ABSTR_CLASS 01
#define VIRT_BASE_CLASS 02

struct ZZextention{
    char *name;
    ZZextPtr *ptr;     /* to all pointers for this expansion */
    ZZextention *next; /* links extentions together with zero end */
    ZZextention *prev; /* reverse link, RING */
    char inCode;       /* marker to be used for cross-checking */
    char virt;         /* 'v' when virt.function present, ' ' otherwise */
    char vcPres;       /* packed ABSTR_CLASS or VIRT_BASE_CLASS */
    char style;        /* 'c' for ZZ_CLASS, 'r' regular */
    char *format;      /* format for zz_inp..() or zz_out..() */
    ZZextention *aClass; /* abstr.class link if used, NULL otherwise */
    struct ZZnameList *fList; /* list of variable names for the format */
    struct ZZinhList *iList;  /* list of extentions included in this one */
    int ind;           /* order index */
    ZZfunInst *fun;    /* object assigned HYPER_OBJECT function list */
    char isClass;      /* 'c'=is a class, 's'=is a struct */
    char hasConstr;    /* 'y'=it has a constructor, 'n'=has not */
    char hasDestr;     /* 'y'=it has a destructor, 'n'=has not */
    char used;         /* temp. flag for virt.base clases printout*/
};

struct ZZextPtr {
    char *bName;    /* base name for the pointer, same as ZZpointer.code */
    ZZextPtr *next; /* links pointers of one Organization, with zero end */
    int orgInd;     /* index to the Organization */
    ZZptrCode *ptrCode; /* to list of pointer name/code conversions */
    ZZpointer *masterP; /* master of this pointer */
    int count;      /* number of pointers of this type */
};

struct ZZptrCode {
    char *pName;     /* name of the pointer, combined ptrName+org.instance */
    char *pointTo;   /* name of structure to which the pointer points */
    ZZptrCode *next; /* next on list */
    int used;        /* 0=not assigned, 1=not used, 2=used */
    ZZpointer *masterP; /* master of this pointer */
};

/* organizations declared by the user */
struct ZZorgInst {
    char *ident;      /* identifier given by the user */
    int orgInd;       /* index of the organization */
    ZZstrType *sType; /* start of types used for this instance */
    ZZstrType *lType; /* last type on the chain starting at sType */
    ZZorgInst *next;  /* all declared organizations, last NULL */
    char *partOf;     /* when 'local', where this is. For ex. A::B::C */
};

/* structure types used for ZZorgInst */
struct ZZstrType {
    char *name;  /* structure type actually declared */
    int ptrInd;  /* index into ZZptr */
    ZZstrType *next; /* all types for one ZZorgInst, NULL end */
};

/* record of conversion for generic functions */
struct ZZgeneric {
    ZZgeneric *next; /* linked list of all the conversions */
    char *funInst;   /* instance of the function, e.g. ZZ_ADD_bChain */
    char *funMaster; /* master of the function, e.g. SINGLE_CHAIN */
    ZZfunction *fp;  /* to the generic function this belongs to */
};
/* funMaster stores first just the plain id, only later it is fully set */

/* temporary list of pointers from all extensions */
struct ZZnameList {
    ZZnameList *next;
    char *name;
    char *cast; /* used only for special formats like enum */
    int formatCode; /* 0 means normal format, >0 index of char->int conversion */
};

/* Inheritance list: extentions included in a given extention */
struct ZZinhList {
    struct ZZinhList *next;
    struct ZZinhList *prevTemp; /* previous - used temporarily in some places */
    char *name; /* ZZinherit,ZZvirtual,ZZrefer */
    ZZextention *ext;
    /* int offset has to be determined in the runtime */
    int num; /* 0=inheritance, 1=single object, >1 array, -1 unused */
    int ind; /* integer order index */
};

/* global variables and arrays */
#ifdef mainCode
ZZorganization *ZZorg; /* array of all organizations */
ZZhierarchy *ZZhier;   /* hierarchy of organizations */
ZZpointer *ZZptr;      /* array of pointers for organizations */
ZZfunction *ZZfun;     /* array of all functions */
ZZsupport *ZZsup;      /* array of support functions for the functions */
ZZorgInst *ZZinst;     /* chain of organizations declared by the user */
ZZgeneric *ZZgen;      /* list of conversions for used generic functions */
int nOrg;           /* number of organizations */
int nHier;          /* number of hierarchical relations */
int nPtr;           /* number of Org. poointers */
int nFun;           /* number of functions */
int nSup;           /* number of support records */
int ascii;          /* 1=ascii IO requested, 0=not requested */
int noLeak;         /* 1=no leak requested for SUN, 0=not requested */
int noCheck;        /* 1=no checking requested, 0=full checking */
int noDestr;        /* 1=to disable autom self checking destructors */
int vClassPresent;  /* set to 1 if virt.class is present */
int ansi;           /* 1=ANSI declarations requested, 0=not requested */
int cPlus;          /* 0=C code, 1=C++ 2.0 or before, 2= C++ 2.1 */
int friends;        /* 0=do not print friends, 1=print them */
int uFormat;        /* 1=ZZ_FORMAT used somewhere, 0=not used at all */
int saveSpecial;    /* 1=generate special saving function */
#endif
extern ZZorganization *ZZorg; /* array of all organizations */
extern ZZhierarchy *ZZhier;   /* hierarchy of organizations */
extern ZZpointer *ZZptr;      /* array of pointers for organizations */
extern ZZfunction *ZZfun;     /* array of all functions */
extern ZZsupport *ZZsup;      /* array of support functions for the functions */
extern ZZorgInst *ZZinst;      /* chain of organizations declared by the user */
extern int nOrg;           /* number of organizations */
extern int nHier;          /* number of hierarchical relations */
extern int nPtr;           /* number of Org. poointers */
extern int nFun;           /* number of functions */
extern int nSup;           /* number of support records */
extern int ascii;          /* 1=ascii IO requested, 0=not requested */
extern int noLeak;         /* 1=no leak requested for SUN, 0=not requested */
extern int noCheck;        /* 1=no checking requested, 0=full checking */
extern int noDestr;        /* 1=to disable autom self checking destructors */
extern int vClassPresent;  /* set to 1 if virt.class is present */
extern int ansi;           /* 1=ANSI declarations requested, 0=not requested */
extern int cPlus;          /* 1=C++ code, 0=C code */
extern int friends;        /* 0=do not print friends, 1=print them */
extern int uFormat;        /* 1=ZZ_FORMAT used somewhere, 0=not used at all */
extern int saveSpecial;    /* 1=generate special saving function */

#ifdef mainCode
ZZextention *ZZext; /* start of all extentions */
int ZZerror;        /* error counter */
int ZZoffset;       /* offset inside the current structure, mainly for sort */
char *ZZpath;       /* full path to this directory */
char *ZZmaster;     /* full path to the zzmaster file */
#endif
extern ZZextention *ZZext; /* start of all extentions */
extern int ZZerror;        /* error counter */
extern int ZZoffset;       /* offset inside the current structure, mainly for sort */
extern char *ZZpath;       /* full path to this directory */
extern char *ZZmaster;     /* full path to the zzmaster file */

/* variables and defines to control the selfIdent operation */
#define SELFID_PTR_NAME "ZZselfID"
#define SELFID_ORG_NAME "SELF_ID"
#define ALL_SELF "ZZ_ALL_SELF_ID"
#define ZZ_IMPLICIT "ZZimplicit"
#define ZZ_SELECT_MACROS "ZZselectMacros"
#ifdef mainCode
int inherit;     /* 1=inheritance or member objects, 0=only top objects */
int inheritAll;  /* 1=all classes virt. functions, 0=only selected ones */
int multiProj;   /* 1=multi project (static tables), 0=normal(global)tables */
int allSelfUsed;    /* 1=used, 0=not used */
int orgSelfUsed;    /* 1=used, 0=not used */
int selectMacros;   /* 1=select, 0=use all */
int selectFunctions;/* 1=select, 0=none used */
int implicit;       /* 1=all generics, 0=only those used */
int simpleAlloc;    /* 1=allocation by calloc only, 0=initialization needed */
                    /* =0 if ZZ_INHERIT, Block_memory, selfID, or timeStamp */
#endif
extern int inherit;    /* 1=inheritance or member objects, 0=only top objects */
extern int inheritAll; /* 1=all classes virt. functions, 0=only selected ones */
extern int multiProj;/* 1=multiProject(static tables), 0=normal(global)tables */
extern int allSelfUsed;    /* 1=used, 0=not used */
extern int orgSelfUsed;    /* 1=used, 0=not used */
extern int selectMacros;   /* 1=select, 0=use all */
extern int selectFunctions;/* 1=select, 0=none used */
extern int implicit;       /* 1=all generics, 0=only those used */

/* defines for the timeStamp */
#define TIME_STAMP_NAME "ZZtimeStamp"

/* property is also a special type of operation */
#define PROPERTY_PTR_NAME "ZZprop"
#define PROPERTY_NAME "struct ZZproperty"

#define ZZ_BUCK 41
extern int ZZbucket[ZZ_BUCK];  /* buckets speed up access to Function names */
#ifdef mainCode
int ZZbucket[ZZ_BUCK];  /* buckets speed up access to Function names */
#endif

/* some useful macros */
#define NEXT_WORD(P) {for(;*(P)!=END;(P)++)continue; (P)++;}  

#define PRINT_WORDS(P,N) {\
int I; char *S; \
printf("  ");\
for(I=0,S=(P);I<(N);I++){printf("%s",S);NEXT_WORD(S);}\
printf("\n");\
}

#define MAX(A,B) ((A)>(B)?(A):(B))

#define EXCHANGE(type,A,B) {type C;C=(A);(A)=(B);(B)=C;}

/* cascaded insertion works differently on some compilers */
#ifdef BELOW
#ifdef DOS
#include "..\lib\types.h"
#include "..\lib\msgs.h"
#endif 
#ifdef UNIX
#ifdef MAC
#include "::lib:types.h"
#include "::lib:msgs.h"
#else
#ifdef COHERENT
#include "../lib/types.h"
#include "../lib/msgs.h"
#else
#include "lib/types.h"
#include "lib/msgs.h"
#endif
#endif
#endif
#ifdef VMS
#include "../lib/types.h"
#include "../lib/msgs.h"
#endif

#else
#ifdef DOS
#include "lib\types.h"
#include "lib\msgs.h"
#endif 
#ifdef UNIX
#ifdef MAC
#include ":lib:types.h"
#include ":lib:msgs.h"
#else
#include "lib/types.h"
#include "lib/msgs.h"
#endif
#endif
#ifdef VMS
#include "lib/types.h"
#include "lib/msgs.h"
#endif
#endif

/* objects for management of default directories */
typedef struct DirObj DirObj;
typedef struct FilObj FilObj;
struct DirObj {
    DirObj *next;
    FilObj *file;
    char *name;
};
struct FilObj {
    FilObj *next;
    char *name;
};
