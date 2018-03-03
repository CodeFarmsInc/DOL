/****************************************************************/
/*							      	*/
/*   Copyright (C) 1988 - 2011                                  */
/*	Code Farms Inc.,  All Rights Reserved.			*/
/*							  	*/
/****************************************************************/
#define mainCode
#define ZZmain
#include <stdio.h>

#include "zzintern.h"

/* This file is used only if the input file (user program or concatenated
 * headers) contains special line with 'ZZbreakLine'.
 * This keyword triggers splitting the input into sections that are
 * processed independently. The breakpoint must not be within a class
 * or structure declaration.
 */
FILE *parseFile={0};
unsigned int breakLine={0}; /* if not changed, there is no break line */
int justOne={0};  /* toggle that allows parserRead() just one pass
                     if the parseFile is not used */

#ifdef VMS
#include "[.lib]orgctime.h"
#include "[.lib]heading.h"
#include "[.lib]buffer.h"
#else
#ifdef MAC
#include ":lib:orgctime.h"
#include ":lib:heading.h"
#include ":lib:buffer.h"
#else
#include "lib/orgctime.h"
#include "lib/heading.h"
#include "lib/buffer.h"
#endif
#endif

#define DEFDEC "#define"
int allocPtr={0};

#ifdef VMS
#define ZZreturn(A) return
#endif
#ifdef UNIX
#define ZZreturn(A) return(A)
#endif
#ifdef DOS
#define ZZreturn(A) return(A)
#endif

/* BorlandC++ 3.0 is sensitive about the order of function declarations
 * this is a bug we had to get around - Jiri Soukup, Mar.10/92 */

/* functions in file zzprep.c */
/* ---------------------------------------------------------- */
#ifdef ZZ_ANSI
unsigned int shrinkIt(char *s);
void parseWrite(char *s, unsigned int k);
unsigned int parseRead(char *s);
void parseClose(int k);
void splitLine(FILE *);
void abstrParent(void);
void recVirtBase(ZZextention *ext,int *k, FILE *fp);
int vClassUnder(ZZextention *ext);
void asciiFlag(FILE *fp);
void allGen(FILE *outFile);
void typeDef(FILE *outFile,FILE *funFile);
void allSelfID(char *p);
void createSelfID(FILE *outFile);
void sortPointers(void);
void shortDef(FILE *outFile);
int cpMacros(FILE *outFile);
void expMacros(void);
int cpFunctions(FILE *outFile);
int createExt(FILE *fp,FILE *funFile,char *outName,ZZnameList **nlp);
int createFun(FILE *fp,FILE *umlFile,int nPtr,ZZnameList *nlp);
void weedVirt(void);
int addPtr(ZZnameList **start,char *name,ZZpointer *master);
void createFriends(FILE *fp,ZZextention *ext);
void declareClasses(FILE *fp);
void addFriend(ZZnameList **fStart,char *name);
void createFormat(FILE *fp);
void createPform(FILE *fp);
void createIO(FILE *fp);
void formFormat(FILE *fp,ZZextention *ext,int io);
void prt1(FILE *fp,char *c,int num);
void zzfuncGen(FILE *fp);
void offMacro(FILE *fp,ZZextention *ext);
void sMacro(FILE *fp);
void firstName(ZZextPtr *ptr,char *name);
const char *pTypeConv(const char c);
int crossExt(char *p,FILE *outFile);
void detectLinks(ZZuml *uml,FILE *umlFile,char *p);
void detInherit(char *p);
char *classOrStruct(char *r,char *lineN);
ZZextention *findExt(char *id);
ZZextention *whichExt(char *id);
int extInd(char *id);
char *newInherit(char *id,char *r,char *lineN);
char *searchChar(char *p,char c);
char *searchEnd(char *p);
void whichName(ZZfunction *fp,char *p);
void addFunInst(ZZfunction *fp,char *id,char *lineN);
char *pParse(FILE *inpFile,FILE *envFile,DirObj *accDir);
int lineChar(int num);
ZZextention *getExtention(int create,char *sName,int style);
ZZextention *newExtention(char *extName);
int recInst(ZZfunction *fp,char *id,char **strs,int ns);
int makeExt(ZZfunction *fp,char *id,char **strs,int ns,int noMix);
char *ZZmix(char *str1,char *str2);
void checkFun(ZZfunction *fp,char *id,char *lineN);
char *nameExt(char *str);
void genRec(ZZfunction *fp,char *id);
void genDef(FILE *outFile);
DirObj *defDir(char **argv,int *argc);
void addDir(DirObj **dp,char *name);
void addFil(DirObj *d,char *fName);
void addVirtClasses(ZZextention *parent,ZZextention *ext);
void debParser(char *p);
void debFunction(void);
void debExtention(char *text);
void aFormat(ZZextention *ext);
char *testInject(char *id,char *r,int isc);
void newFormat(char *pp,char *lineN);
void genSaveSpec(FILE *);

#else
unsigned int shrinkIt();
void parseWrite();
unsigned int parseRead();
void parseClose();
void splitLine();
void abstrParent();
void recVirtBase();
int vClassUnder();
void asciiFlag();
void allGen();
void typeDef();
void allSelfID();
void createSelfID();
void sortPointers();
void shortDef();
int cpMacros();
void expMacros();
int cpFunctions();
int createExt();
int createFun();
void weedVirt();
int addPtr();
void createFriends();
void declareClasses();
void addFriend();
void createFormat();
void createPform();
void createIO();
void formFormat();
void prt1();
void zzfuncGen();
void offMacro();
void sMacro();
void firstName();
char *pTypeConv();
int crossExt();
void detectLinks();
void detInherit();
char *classOrStruct();
ZZextention *findExt();
ZZextention *whichExt();
int extInd();
char *newInherit();
char *searchChar();
char *searchEnd();
void whichName();
void addFunInst();
char *pParse();
int lineChar();
ZZextention *getExtention();
ZZextention *newExtention();
int recInst();
int makeExt();
char *ZZmix();
void checkFun();
char *nameExt();
void genRec();
void genDef();
DirObj *defDir();
void addDir();
void addFil();
void addVirtClasses();
void debParser();
void debFunction();
void debExtention();
void aFormat();
char *testInject();
void newFormat();
void genSaveSpec();
#endif

/* functions in file zzutil.c */
/* -------------------------------------------------------------- */
#ifdef ZZ_ANSI
int getMaster(char *path,int warn);
int aOrder(char *p1,char *p2);
char *binCmp(char *list,int strSize,int offset,int num,char *word);

#if defined(SUN) || defined(LINUX)
extern "C" 
#endif
int genSortFun(const void *p1,const void *p2);

int setBuckets(char *ptr,int n,int size,int offset);
int buckFun(char *p);
void jsCrypt(char *inpName,char *outName,int type,char *c,int autoFlg,int tab);
FILE *myopen(char *a,const char *b);
void mvFile(char *oldF,char *newF);
void delFile(char *name);
int cmpFiles(char *name1,char *name2);
void cpFile(FILE *inFile,FILE *outFile,char *id);
void plainCopy(char *name,FILE *outFile);
char *ZZgetPath(char *progr,char *name);
void filterOut(FILE *mFile,FILE *outFile);
ZZint ZZioFunction(FILE *fp,ZZint mode,ZZint type,char *p,ZZint strSz);
int ZZbindPtrs(char *obj,int newTp,int newSize,int vUpd,int blast);
ZZvoidS *ZZnewBit(unsigned int size) ;
int ZZwrite(FILE *fp,char *buff,ZZsize n,const char *);
int ZZread(FILE *fp,char *buff,ZZsize n,const char *);
int ZZclose(FILE *fp);
FILE *ZZopen(const char *fileName,const char *mode);

#else
int getMaster();
int aOrder();
char *binCmp();
int genSortFun();
int setBuckets();
int buckFun();
void jsCrypt();
FILE *myopen();
void mvFile();
void delFile();
int cmpFiles();
void cpFile();
void plainCopy();
char *ZZgetPath();
void filterOut();
ZZint ZZioFunction();
int ZZbindPtrs();
ZZvoidS *ZZnewBit();
int ZZwrite();
int ZZread();
int ZZclose();
FILE *ZZopen();
#endif

/* other functions */
/* -------------------------------- */
#ifdef ZZ_ANSI
int ZZpOffset(char *,char *);
#else
int ZZpOffset();
#endif

/* ZZprep -
 * the main control of the ZZpreprocessor.
 *
 * Algorithm::
 * (1) Initialize ZZerror=0 and allSelfUsed=orgSelfUsed=0.
 *     Setup: input file (default stdin)
 *            path       (default ..)
 *            ZZnewLoc temporary file for new ZZlocal.
 *     ZZnwLocal will collect all zz-references.
 * (2) Read file zzmaster with the table of all organizations and functions.
 *     Initialize and find number of organizations and functions.
 *     Resort the internal records of Functions for fast access by name.
 * (3) Partial parsing of the input file, keep in core.
 * (4) Call detectLinks() to detect used organizations and functions.
 * (5) Check new ZZnewLoc with the old ZZlocal. If these files are
 *     identical, there is no need for new zzincl.h file, exit.
 *     If the files differ, then open rename ZZnewLoc as ZZlocal,
 *     open zzincl.h (or the given output file) for writing.
 *     Copy the main headings and routine defines onto output.
 * (6) Add and organize selfID pointers:
 *     If getSelfID is called but not setSelfID, selfID pointer must be
 *     set on every ZZ_EXT_ declared.
 *     If setSelfID was used, the selfID pointers on all extention must be moved
 *     into the first position on the structure.
 * (7) Form the output file - typically zzincl.h:
 *     - write the Extention macros from the internal records;
 *     - copy in the Function macros from the individual files
 *       (only for the Functions actually used)
 *     - create 'define' statement for all short macros used
 *     - cross-check that all Extentions from zzincl.h exist in the user's
 *       code and vice versa.
 *     - write defines for types inside the organizations.
 *     - write conversion for all used generic functions
 *
 * All macros/functions are implemented in the same consistent manner
 * with one exception: selfID requires its pointer to be first on the
 * ZZ_EXT_.. list. Also, special array ZZselfArr[] and its size ZZnID
 * are stored in zzincl.h to control the identification.
 *
 * Typical use:
 *               ZZprep userProg.c zzincl.h zzmaster
 * where:
 *  userProg.c  is the user C-program,
 *  zzincl.h is the include file ZZprep will generate
 *  pathofZZdir is the path to the ZZ directory
 *  ZZlocal     is the file with all ZZ references extracted from userProg.c
 *
 * Author: Jiri Soukup, April 15, 1988
 *         Turbo C update July 27, 1988
 * By Dec.17, 1988: running on SUN, C++, Microsoft 
 */

// ---------------------------------------------------------------------------
// Get the linked list of organization records from the macro/registry file
// ---------------------------------------------------------------------------
ZZuml* getRegistry(char *path){
    char buff[256],name[80],dispName[80],code[80],order[80];
    int bsz=256;
    FILE *fp; ZZuml *u,*head,*tail;

    strcpy(buff,path);
    strcat(buff,"/macro/registry");
    fp=fopen(buff,"r");
    if(!fp){
        printf("cannot open file macro/registry, zzprep run is OK\n");
        printf("   but the UML diagram is not produced\n");
        return NULL;
    }

    head=tail=NULL;
    while(fgets(buff,bsz,fp)){
        u=(ZZuml*)malloc((int)sizeof(struct ZZuml));
        if(!head)head=u; 
        else tail->next=u;

        u->next=NULL;
        tail=u;
        
        sscanf(buff,"%s %s",name,dispName);
        u->name=(char*)malloc(strlen(name)+1);
        u->dispName=(char*)malloc(strlen(dispName)+1);
        if(u->name==NULL || u->dispName==NULL){
            printf("allocation error in getRegistry(), zzprep run is OK\n");
            printf("   but the UML diagram will not be complete\n");
            return NULL;
        }
        strcpy(u->name,name);
        strcpy(u->dispName,dispName);
              
        if(dispName[0]=='?'){
            u->code=u->order=NULL;
        }
        else {
            sscanf(buff,"%s %s %s %s",name,dispName,code,order);
            u->code=(char*)malloc(strlen(code)+1);
            u->order=(char*)malloc(strlen(order)+1);
            if(u->code==NULL || u->order==NULL){
                printf("allocation error in getRegistry(), zzprep run is OK\n");
                printf("   but the UML diagram will not be complete\n");
                return NULL;
            }
            strcpy(u->code,code);
            strcpy(u->order,order);
        }
    }
    fclose(fp);
    return head;
}

// ---------------------------------------------------------------------------
// Find the given organization in the records reflecting the registry file
// and print the record required for the layout program.
// ---------------------------------------------------------------------------
void umlPrt(FILE *umlFile,ZZuml *uml,char *txt){
    char *p,*s; char* a[100]; int sz=100; int i,k,n;
    ZZuml *u;

    // find the corresponding ZZuml record
    for(u=uml; u; u=u->next){
        if(!strcmp(txt,u->name))break;
    }
    if(!u){
        printf("Data organization=%s not in the macro/registry file\n",txt);
        printf("   zzprep run is OK, but the UML diagram is not complete\n");
        return;
    }
    if(u->dispName[0]=='?')return; // skip organizations marked by '?'

    for(p=txt, i=0; p && i<sz;){
        if(p[0]!=',' && p[0]!=')' && p[0]!='('){
            a[i]=p;
            i++;
            if(p[0]==';')break;
        }
        NEXT_WORD(p);
    }
    if(i>=sz){
        printf("code generation OK but the UML diagram failed,\n");
        printf("increase the size of array a[] in umlPrt()\n");
        return;
    }

    // place id in the correct position
    s=a[1];
    for(k=1; k<i-2; k++){
        a[k]=a[k+1];
    }
    a[i-2]=s;

    if(u->dispName[0]!='*')a[0]=u->dispName;

    fprintf(umlFile,"%s %s ",u->code,a[0]);
    for(k=1; k<i-1; k++){
        if(u->order[0]=='0')n=k; // regular case
        else n=(unsigned int)(u->order[k-1]) - (unsigned int)('0'); // re-order
        fprintf(umlFile,"%s ",a[n]);
    }
    fprintf(umlFile,"%s\n",a[i-1]);
}
// ---------------------------------------------------------------------------

#ifdef ZZ_ANSI
int main(int argc,char **argv)

#else
int main(argc,argv)
int argc;
char *argv[];
#endif
{
    FILE *inpFile,*outFile,*funFile,*envFile,*ff,*umlFile;
    int i,localEnv,nPtr;
    char *parsed,*outName,*funFileName,*envName;
    ZZextention *ext;
    DirObj *accDir; /* access to all directories */
    ZZnameList *nlp;
    ZZuml *uml;

    printf("Data Object Library Version ");
    printf("%s",VERSION);
    printf(" Copyright(c) 1989-2011 Code Farms Inc.\n");
    
    ZZerror=0;
    cPlus=allSelfUsed=orgSelfUsed=selectMacros=selectFunctions=0;
    noLeak=noCheck=noDestr=implicit=ascii=vClassPresent=0;
    uFormat=inherit=ansi=multiProj=saveSpecial=inheritAll=0;
    friends=1;
    ZZgen=NULL;

    simpleAlloc=1;
#ifdef TURBOC
    simpleAlloc=0; /* TurboC++ calloc() does not work */
#endif
#ifdef SUN
    simpleAlloc=0; /* calloc() does not work on SUN */
#endif

    /* (0) read parameters of main, eliminate -I, create directory/file list */
    accDir=defDir(argv,&argc);

    /* (1) analyze program parameters */
    /* ------------------------------ */
    ZZpath=ZZgetPath(argv[0],(char*)"zzprep");
    if(argc<=1)inpFile=stdin;
    else {
        inpFile=myopen(argv[1],"r");
        if(!inpFile){
            ZZmsgS(0,argv[1]); /* cannot open input file */
	    ZZerror++;
        }
    }
    if(argc<=3)ZZmaster=(char*)"zzmaster";
    else {
	ZZmaster=(char*)malloc(strlen(argv[3])+1);
	if(!ZZmaster){
            ZZmsgS(1,"zzmaster"); /* problem to allocate memory */
	    ZZerror++;
	}
	strcpy(ZZmaster,argv[3]);
    }
    if(argc<=4)funFileName=(char*)"zzfunc.c";
    else {
	funFileName=(char*)malloc(strlen(argv[4])+1);
	if(!funFileName){
            ZZmsgS(1,"function file name"); /* alloc problem */
	    ZZerror++;
	}
	strcpy(funFileName,argv[4]);
    }
    funFile=NULL;
    if(ZZerror)ZZreturn(ZZerror);

    /* (2) initialize and count organizations and functions */
    /* -------------------------------------------------------------------- */
    if(getMaster(ZZpath,1))ZZreturn(7);

    /* (3) partial parsing of the input file, result as string 'parsed' */
    /* ---------------------------------------------------------------- */
    /* include the environment file in the processing */
    i=strlen("/lib/environ.h")+strlen(ZZpath)+1;
    envName=(char*)malloc(i);
    if(!envName){
        ZZmsgS(1,"internal file name"); /* alloc problem */
	ZZerror++;
        ZZreturn(8);
    }
    strcpy(envName,ZZpath);
#ifdef VMS
    strcat(envName,".lib]environ.h");
#else
    strcat(envName,"/lib/environ.h");
#endif
    
    envFile=myopen((char*)"environ.h","r"); /* try first this directory */
    if(envFile) localEnv=1;
    else {localEnv=0; envFile=myopen(envName,"r");}
    if(!envFile){
        ZZmsgS(0,envName); /* cannot open input file */
	ZZerror++;
        ZZreturn(8);
    }
    
    if((parsed=pParse(inpFile,envFile,accDir))==NULL)ZZreturn(8);
    fclose(inpFile);
    fclose(envFile);

    /* (4) analyze the code both for short names and for long names */
    /* ------------------------------------------------------------ */
    ZZext=NULL;
    ZZinst=NULL;
    uml=getRegistry(ZZpath);
    umlFile=fopen("layout.inp","w");
    detectLinks(uml,umlFile,parsed);
    if(inherit){
        detInherit(parsed);
        abstrParent();
    }
    if(ZZerror){
        ZZmsgD(0,ZZerror); /* errors when creating organizations */
        ZZreturn(16);
    }
    if(inherit)for(ext=ZZext;ext;ext=ext->next)addVirtClasses(ext,ext);

    /* (5) open output file */
    /* ----------------------------------------------------------------- */
    if(argc<=2)outName=(char*)"zzincl.h";
    else       outName=argv[2];
    outFile=myopen(outName,"w");
    if(!outFile){
        ZZmsgS(0,outName); /* cannot open file */
	ZZerror++;
    }
    /* prevent multiple inclusion of zzincl.h */
    fprintf(outFile,"#ifndef zzinclUsed\n#define zzinclUsed\n");
    fprintf(outFile,
       "#ifdef ZZmain\nchar *ZZorgcVersion={(char*)\"Version %s\"};\n",VERSION);
    fprintf(outFile,"#else\nextern char *ZZorgcVersion;\n#endif\n");

    if(simpleAlloc)fprintf(outFile,"#define ZZ_SIMPLE\n");
    /* include the collection of all macros first */
    if(localEnv) fprintf(outFile,"#include \"environ.h\"\n");
#ifdef DOS
    if(!localEnv)fprintf(outFile,"#include \"%s\\lib\\environ.h\"\n",ZZpath);
    fprintf(outFile,"#ifndef FILE\n#include <stdio.h>\n#endif\n");
    if(selectMacros)fprintf(outFile,"#include \"zzcomb.h\"\n");
    else fprintf(outFile,"#include \"%s\\zzcomb.h\"\n",ZZpath);
    fprintf(outFile,"#include \"%s\\lib\\msgs.h\"\n\n",ZZpath);
#endif

#ifdef UNIX
#ifdef MAC
    if(!localEnv)fprintf(outFile,"#include \"%s:lib:environ.h\"\n\n",ZZpath);
    if(selectMacros)fprintf(outFile,"#include \"zzcomb.h\"\n");
    else fprintf(outFile,"#include \"%s:zzcomb.h\"\n",ZZpath);
    fprintf(outFile,"#include \"%s:lib:msgs.h\"\n\n",ZZpath);
#else
    if(!localEnv)fprintf(outFile,"#include \"%s/lib/environ.h\"\n\n",ZZpath);
    if(selectMacros)fprintf(outFile,"#include \"zzcomb.h\"\n");
    else fprintf(outFile,"#include \"%s/zzcomb.h\"\n",ZZpath);
    fprintf(outFile,"#include \"%s/lib/msgs.h\"\n\n",ZZpath);
#endif
#endif

#ifdef VMS
    if(!localEnv)fprintf(outFile,"#include \"%s.lib]environ.h\"\n\n",ZZpath);
    if(selectMacros)fprintf(outFile,"#include \"zzcomb.h\"\n");
    else fprintf(outFile,"#include \"%s]zzcomb.h\"\n",ZZpath);
    fprintf(outFile,"#include \"%s.lib]msgs.h\"\n\n",ZZpath);
#endif

if(cPlus)fprintf(outFile,"class ZZZiClass{};\n");

    /* (6) add & organize selfID pointers */
    /* ---------------------------------- */
    if(allSelfUsed)allSelfID(parsed);
    sortPointers(); /* always needed for arrays, int, etc */
    createSelfID(outFile); /* do this even when no selfID is used */

    /* (7) form the output file */
    /* ------------------------ */
    /* mark Extentions that have virt.class under them */
    if(vClassPresent)for(ext=ZZext;ext;ext=ext->next)vClassUnder(ext);
    /* add order index to the Extentions */
    for(i=0,ext=ZZext;ext;ext=ext->next,i++)ext->ind=i;

    /* open file for the zzfunc.c file */
    funFile=myopen(funFileName,"w");
    if(!funFile){
        ZZmsgS(0,funFileName); /* cannot open file */
	ZZerror++;
        ZZreturn(129);
    }
    nPtr=createExt(outFile,funFile,outName,&nlp);/* write internal Extentions */
    if(createFun(outFile,umlFile,nPtr,nlp))ZZreturn(64); 
                                                 /* write internal Extentions */
    if(umlFile)fclose(umlFile);

    sMacro(outFile); /* generate ZZS and ZZZSS macros */
    if(crossExt(parsed,outFile))ZZreturn(128);  /* cross-check of Ext's */

    /* open file for zzfunc.c, with ZZ_GENERAL_EXT(), io functions,
     * and all hyper-class methods */
    typeDef(outFile,funFile); /* strTypes defines */
    if(implicit)allGen(outFile); /* all generics for used organizations */
    else genDef(outFile);        /* only recorded generic conversions */
    asciiFlag(outFile);                 /* set the ascii flag properly */
    if(cPlus)declareClasses(outFile); /* make all classes known as types */

    /* add a standard tail to the zzincl.h file */
    strcpy(buff,ZZpath);
    strcat(buff,MACRO_PATH);
    strcat(buff,"tail");
    if((ff=myopen(buff,"r"))==NULL){
        ZZmsgS(0,"macro/tail");
        return(2);
    }
    cpFile(ff,outFile,NULL);
    fclose(ff);

    fprintf(outFile,"#endif\n"); /* protect multiple inclusion of zzincl.h */
    fclose(outFile);

    /* generate zzfunc.c, with ZZ_GENERAL_EXT(), io functions,
     * and all hyper-class methods */
    zzfuncGen(funFile);
    if(saveSpecial)genSaveSpec(funFile);
    fclose(funFile);

    if(selectMacros){
        if(argc<=5)outFile=myopen((char*)"zzcomb.h","w");
        else outFile=myopen(argv[5],"w");
        if(!outFile){
            ZZmsgS(0,"zzcomb.h"); /* cannot open zzcomb.h */
	    ZZerror++;
        }
        if(cpMacros(outFile))ZZreturn(32); /* copy macro files that are used */
        shortDef(outFile);                /* create 'defines' for short names */
        fclose(outFile);
    }
    ZZreturn(ZZerror);
}
/* ---------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void splitLine(FILE *fp){
#else
void splitLine(fp)FILE *fp;{
#endif
    fprintf(fp,"/* ----------------------------------------- */\n");
}
/* ---------------------------------------------------------------------- */
/* link abstract classes to their parent class */
#ifdef ZZ_ANSI
void abstrParent(void){
#else
void abstrParent(){
#endif

    ZZextention *ext,*ep;
    struct ZZinhList *ip;
    int i;

    for(i=1; i; ){ /* repeat as long as there is a change */
        i=0;
        for(ext=ZZext; ext; ext=ext->next){
            for(ip=ext->iList;ip;ip=ip->next){
                ep=ip->ext;
                if(!(ep->aClass) && ((ep->vcPres)&ABSTR_CLASS)){
                    ep->aClass=ext;
                    i=1;
                }
            }
        }
    }
}
/* ---------------------------------------------------------------------- */
/* generate a special saving function that can be used in connection
 * with the SWEEP save, and can recognize type instantly. This function
 * can be invoked by using #define ZZsaveSpecial, and requires that
 * a special Save() function be provided for each class.
 * Normally, the Save() function calls the ZZ_STORE() macro */
#ifdef ZZ_ANSI
void genSaveSpec(FILE *fp)

#else
void genSaveSpec(fp)
FILE *fp;
#endif
{
    ZZextention *ext;
    int i;
    char *nn;

    fprintf(fp,"void zzSaveSpecial(char *obj,int tp,int sz,char *fp){\n");
    fprintf(fp,"  sz=sz;\n  switch(tp){\n");
    for(ext=ZZext, i=0; ext; ext=ext->next, i++){
        nn= &(ext->name[7]);
        fprintf(fp,"    case %d: ((%s *)obj)->Save(fp); break;\n",i,nn);
    }
    fprintf(fp,"    default: printf(\"error: zzSaveSpec type=%%d\\n\",tp); break;\n");
    fprintf(fp,"  }\n}\n");
}
/* ---------------------------------------------------------------------- */
/* mark Extention that have a virt.class under their hierarchy */
#ifdef ZZ_ANSI
int vClassUnder(ZZextention *ext)

#else
int vClassUnder(ext)
ZZextention *ext;
#endif
{
    struct ZZinhList *ip;
    int i,k;

    if(ext->aClass)i=1;
    else {
        i=0;
        for(ip=ext->iList; ip; ip=ip->next){
            if(!strcmp("ZZvirtual",ip->name))i=1;
            k=vClassUnder(ip->ext);
            if(k)i=1;
        }
    }
    if(i)ext->vcPres=(ext->vcPres)|VIRT_BASE_CLASS;
    return(i);
}
/* ---------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void asciiFlag(FILE *fp)

#else
void asciiFlag(fp)
FILE *fp;
#endif
{
    fprintf(fp,"\n#ifdef ZZmain\nZZ_LOCAL int ZZbindASCII={%d};\n",ascii);
    fprintf(fp,"#ifdef SUN\nZZ_LOCAL int ZZnoLeak={%d};\n",noLeak);
    fprintf(fp,"#else\nZZ_LOCAL int ZZnoLeak={1};\n#endif\n");
    fprintf(fp,"ZZ_LOCAL int ZZinhFLG={%d};\n",inherit);
    fprintf(fp,"ZZ_LOCAL int ZZvClassPresent={%d};\n",vClassPresent);
    fprintf(fp,"ZZ_LOCAL ZZint ZZallocPtr={%d};\n#endif\n",allocPtr);
    fprintf(fp,"#ifndef ZZmain\nextern int ZZbindASCII;\n");
    fprintf(fp,"extern int ZZnoLeak;\n");
    fprintf(fp,"extern int ZZinhFLG;\n");
    fprintf(fp,"extern int ZZvClassPresent;\n");
    fprintf(fp,"extern ZZint ZZallocPtr;\n#endif\n");

    if(!ascii){
        fprintf(fp,"#ifdef ZZ_ANSI\n");
        fprintf(fp,"#ifdef ZZmain\n");
        fprintf(fp,"ZZ_LOCAL ZZint ZZioFunction(FILE *fp,ZZint io,ZZint type,char *p,ZZint strSz){\n");
        fprintf(fp,"fp=fp; io=io; type=type; p=p; return(0);}\n");
        fprintf(fp,"#endif\n#else\n");
        fprintf(fp,"#ifdef ZZmain\nZZ_LOCAL ZZint ZZioFunction(fp,(ZZint)io,(ZZint)type,p,strSz)\n");
        fprintf(fp,"FILE *fp;int io; int type;char *p;ZZint strSz;{\n");
        fprintf(fp,"fp=fp; io=io; type=type; p=p; return(0);}\n#endif\n#endif\n");
    }
}
/* ---------------------------------------------------------------------- */
/* For all instances of organizations, collect all possible generics
 * and print the conversion table */
#ifdef ZZ_ANSI
void allGen(FILE *outFile)

#else
void allGen(outFile)
FILE *outFile;
#endif
{
    int i,size;
    ZZorgInst *oi;
    struct FunList {
        char *name; /* sometimes short, sometimes long name */
        ZZfunction *fun;
    } *fList;

    /* make a list of functions with long names only */
    size=(int)sizeof(struct FunList);
    fList=(struct FunList *)malloc(nFun*size);
    if(!fList){
        ZZmsgS(1,"allGen()"); /* alloc of internal space in allGen() */
        return;
    }
    for(i=0; i<nFun; i++){     /* populate in the list */
        fList[i].name=ZZfun[i].name;
        fList[i].fun= &(ZZfun[i]);
    }

    ZZoffset=ZZpOffset((char *)(&(fList->name)),(char *)fList);
    qsort(fList,nFun,size,genSortFun);
    (void)setBuckets((char *)fList,nFun,size,ZZoffset);

    for(i=0;i<nFun;i++){
        if(ZZfun[i].create=='g' || ZZfun[i].create=='G'){ /* generic function */ 
            for(oi=ZZinst;oi;oi=oi->next){
                /* create full macro name */
                strcpy(buff,ZZfun[i].name);
                strcat(buff,"_");
                strcat(buff,ZZorg[oi->orgInd].name);
                /* check whether such macro exists */
	        if(binCmp((char *)fList,size,ZZoffset,nFun,buff)!=NULL){
	            fprintf(outFile,"#define %s_%s %s\n",
                                          ZZfun[i].name,oi->ident,buff);
                }
            }
        }
    }
    free(fList);
}
/* ---------------------------------------------------------------------- */
/* create defines for types within the given organizations */
#ifdef ZZ_ANSI
void typeDef(FILE *outFile,FILE *funFile)

#else
void typeDef(outFile,funFile)
FILE *outFile; /* default zzincl.h file */
FILE *funFile; /* default zzfunc.c file */
#endif
{
    int i,k,local,n;             /* CORR */
    char *ns,*ni;         /* CORR */
    ZZorgInst *oi;
    ZZstrType *st;
    ZZextention *ext;
    static char nstar[128];

    local=0; /* if changed, some organizations are local */
    for(oi=ZZinst;oi;oi=oi->next){
        ni=oi->ident;
        fprintf(outFile,"#define %s_class ZZH%s\n",ni,ni);
        for(st=oi->sType, i=1, local=0; st; st=st->next, i++){
            ns=st->name;
            if(i>=ZZorg[oi->orgInd].nInp && cPlus==2){
                local=1;
                fprintf(outFile,"#define ZZV%s %s::\n",ni,ns);
            }
            fprintf(outFile,"#define ZZ%d%s %s\n",i,ni,ns);
            n=strlen(ns);                                         
	    if(n>=128){ZZmsgS(54,ns); exit(1);}
	    strcpy(nstar,ns);
            if(nstar[n-1]=='*') nstar[n-1]='\0'; /* cut off '*' */ 
            fprintf(outFile,"#define ZZX%d%s \"%s\"\n",i,ni,ns);
            fprintf(outFile,"#define ZZH%d%s \"%s\"\n",i,ni,nstar);
            /* find the name on the type list */
            for(ext=ZZext, k=0; ext; ext=ext->next, k++){
                if(!strcmp(&(ext->name[7]),ns))break;
            }
            if(!ext){
		/* WARNING: The following decision tree must agree with
		 * function ZZfindType)_ in util.c */

		if(!strcmp(ns,"char*") || !strcmp(ns,"char *"))k= -1;
		else if(strlen(ns) != strlen(nstar))           k= -5;
		else if(!strcmp(ns,"int"))                     k= -6;
		else if(!strcmp(ns,"float"))                   k= -7;
		else if(!strcmp(ns,"char"))                    k= -8;
		else  /* strange entry */                      k= -9;
	    }
            fprintf(outFile,"#define ZZW%d%s %d\n",i,ni,k);
        }
        if(!local)fprintf(outFile,"#define ZZV%s  \n",ni);
    }
    fprintf(outFile,"\n");

    /* if C++ 2.1 and ZZ_LOCAL is used, static must be also in zzfunc.c */
    if(cPlus!=2)return;
    for(oi=ZZinst;oi;oi=oi->next){
        ni=oi->ident;
        for(st=oi->sType, i=1; st; st=st->next, i++){
             ns=st->name;
            if(i>=ZZorg[oi->orgInd].nInp){
                fprintf(funFile,"%s::ZZH%s %s::%s;\n",ns,ni,ns,ni);
            }
        }
    }
    fprintf(funFile,"\n");
}
/* ---------------------------------------------------------------------- */
/* analyze again all input and pick up all ZZ_EXT_...
 * and put a selfID pointer into them 
 */
#ifdef ZZ_ANSI
void allSelfID(char *parse)

#else
void allSelfID(parse)
char *parse; /* partially parsed input file */
#endif
{
    ZZextention *ext;
    ZZextPtr *ptr;
    char *p,*eName,*pName;
    int i,k;

    /* index of the selfID organizations will be needed for all pointers */
    for(i=0;i<nOrg;i++)if(!strcmp(SELFID_ORG_NAME,ZZorg[i].name))break;
    if(i>=nOrg){
	ZZerror++;
        ZZmsg(0); /* cannot find selfID organization */
	return;
    }
    k=ZZorg[i].ptrInd;

for(p=parse; parseRead(p); p=parse){
    for(;*p!=END;){
	if(strlen(p)>6){
	    if(!strncmp("ZZ_EXT_",p,7)){
                ext=whichExt(p);
		if(!ext){
		    eName=(char*)malloc(strlen(p)+1);
		    if(!eName){
			ZZerror++;
                        ZZmsgS(1,"Extention name");
			return;
		    }
		    strcpy(eName,p);
                    ext=newExtention(eName);
                    if(!ext)return;
		}
		ptr=ext->ptr;
		if(!ptr || strcmp(ptr->bName,SELFID_PTR_NAME)){
		    /* new selfID ptr is needed */
		    ptr=(ZZextPtr *)malloc((int)sizeof(struct ZZextPtr));
		    pName=(char *)malloc(strlen(SELFID_PTR_NAME)+1);
		    if(!ext || !pName){
			ZZerror++;
                        ZZmsgS(1,"ZZextPtr"); /* allocation problem */
			return;
		    }
		    strcpy(pName,SELFID_PTR_NAME);
		    ptr->bName=pName;
		    ptr->next=ext->ptr;
		    ext->ptr=ptr;
		    ptr->orgInd=i;
                    ptr->ptrCode=NULL;
                    ptr->masterP= &(ZZptr[k]);
		}
	    }
	}
	NEXT_WORD(p);
    }
}parseClose(0);
    return;
}
/* ---------------------------------------------------------------------- */
/* write onto the output file the declaration of array ZZselfArr[]
 * with the names of all structures that have selfID pointer in them.
 * Also write a define for the size of this array, ZZnID.
 *   In case that selfID is not used at all, declare:
 * char *ZZselfArr[]={"ZZendMark"};; 
 * #define ZZnID 0
 *
 * Preconditions: 
 * selfId pointer, if present, is always in the first position.
 */
#ifdef ZZ_ANSI
void createSelfID(FILE *outFile)

#else
void createSelfID(outFile)
FILE *outFile;  /* output file */
#endif
{
    int n;
    ZZextention *ext;
    ZZextPtr *p;

    /* count the number of entries */
    for(n=1, ext=ZZext; ext; ext=ext->next){
	p=ext->ptr;
	if(p && !strcmp(p->bName,SELFID_PTR_NAME))n++;
    }

    fprintf(outFile,"#ifndef ZZmain\nextern\n#endif\n");
    fprintf(outFile,"\nZZ_LOCAL char *ZZselfArr[%d]\n#ifdef ZZmain\n={\n",n);
    for(ext=ZZext;ext;ext=ext->next){
	p=ext->ptr;
	if(p && !strcmp(p->bName,SELFID_PTR_NAME)){
	    /* next line assumes standard 7-character prefix "ZZ_EXT_" */
	    fprintf(outFile,"(char*)\"%s\",\n",&(ext->name[7]));
	}
    }
    fprintf(outFile,"(char*)\"ZZendMark\"}\n#endif\n;\n#define ZZnID %d\n",n);
    return;
}
/* ---------------------------------------------------------------------- */
/* search all extentions, and if you find a selfID pointer, move it to
 * the first position on the list. Move the timeStamp field and any
 * variables that are not 'automatic pointers' to end of the list.
 * Array pointers should be at the end of the pointer section */
#ifdef ZZ_ANSI
void sortPointers(void)

#else
void sortPointers()
#endif
{
    ZZextention *ext;
    ZZextPtr *p1,*p2;
    char c;

    for(ext=ZZext;ext;ext=ext->next){
	for(p1=p2=ext->ptr;p2;p2=p2->next){
	    if(!strcmp(SELFID_PTR_NAME,p2->bName))break;
	}
	if(p2 && p2!=p1){ /* exchange p1 and p2 */
	    EXCHANGE(char *,p1->bName,p2->bName);
	    EXCHANGE(int,p1->orgInd,p2->orgInd);
	    EXCHANGE(ZZptrCode *,p1->ptrCode,p2->ptrCode);
	    EXCHANGE(ZZpointer *,p1->masterP,p2->masterP);
	    EXCHANGE(int,p1->count,p2->count);
	}

        /* resort pointers into two groups: autom.pointers, other variables */
	for(p2=ext->ptr;p2;p2=p2->next){
	    if(strcmp(SELFID_PTR_NAME,p2->bName)){ /* skip selfID */
                c=p2->masterP->aType;
                if(c!='a' && c!='g' && c!='A')break;
            }
        }
        if(p2){ /* p2 is the first entry which is not autom.pointer */
	    for(p1=p2->next;p1;p1=p1->next){
                c=p1->masterP->aType;
                if(c=='a' || c=='g' || c=='A'){
	            EXCHANGE(char *,p1->bName,p2->bName);
	            EXCHANGE(int,p1->orgInd,p2->orgInd);
	            EXCHANGE(ZZptrCode *,p1->ptrCode,p2->ptrCode);
	            EXCHANGE(ZZpointer *,p1->masterP,p2->masterP);
	            EXCHANGE(int,p1->count,p2->count);
                    p2=p2->next;
                }
            }
        }

        /* resort autom.pointers into two groups: normal and array pointers */
	for(p2=ext->ptr;p2;p2=p2->next){
	    if(strcmp(SELFID_PTR_NAME,p2->bName)){ /* skip selfID */
                c=p2->masterP->aType;
                if(c!='a' && c!='g' && c!='A'){
                    p2=NULL;
                    break;
                }
                if(c=='A')break;
            }
        }
        if(p2){ /* p2 is the first array entry */
	    for(p1=p2->next;p1;p1=p1->next){
                c=p1->masterP->aType;
                if(c!='a' && c!='g' && c!='A')break;
                if(c!='A'){
	            EXCHANGE(char *,p1->bName,p2->bName);
	            EXCHANGE(int,p1->orgInd,p2->orgInd);
	            EXCHANGE(ZZptrCode *,p1->ptrCode,p2->ptrCode);
	            EXCHANGE(ZZpointer *,p1->masterP,p2->masterP);
	            EXCHANGE(int,p1->count,p2->count);
                    p2=p2->next;
                }
            }
        }
    }
    return;
}
/* ---------------------------------------------------------------------- */
/* Create 'define' conversion statements for those macros that are used
 * either in the short form only, or in both forms. 
 */
#ifdef ZZ_ANSI
void shortDef(FILE *outFile)

#else
void shortDef(outFile)
FILE *outFile;  /* output file, typically zzincl.h */
#endif
{
    int i;

    fprintf(outFile,"\n");
    for(i=0;i<nFun;i++){
        if(ZZfun[i].used!=' ')
	    fprintf(outFile,"#define %s %s\n",ZZfun[i].sName,ZZfun[i].name);
    }
    return;
}
/* ---------------------------------------------------------------------- */
/* Copy those macros that are used in the user program onto the output file */
#ifdef ZZ_ANSI
int cpMacros(FILE *outFile)

#else
int cpMacros(outFile)
FILE *outFile; /* output file */
/* returns number of errors */
#endif
{
    FILE *ff;
    int i,k,eCount,used,propUsed;
    char *oldName;

    /* expand ZZ_ORG or ZZ_HYPER if only those are given */
    if(implicit || cPlus)expMacros();

    /* put Copyright and general headings into the file */
    strcpy(buff,ZZpath);
    strcat(buff,LIB_PATH);
    strcat(buff,"types.h");
    if((ff=myopen(buff,"r"))==NULL){
        ZZmsgS(0,"lib/types.h"); /* cannot open file lib/types.h */
        return(2);
    }

    strcpy(buff,ZZpath);
    strcat(buff,LIB_PATH);
    strcat(buff,"heading.h");
    if((ff=myopen(buff,"r"))==NULL){
        ZZmsgS(0,"lib/heading.h"); /* cannot open file lib/heading.h */
        return(2);
    }
    cpFile(ff,outFile,NULL);
    fclose(ff);

    /* monitor if property used, must be if ASCII mode */
    propUsed=0;
    eCount=0;
    for(i=0;i<nFun;i++){
	if(ZZfun[i].used!=BLANK){
            /* prevent multiple copies of the same file */
            for(k=0;k<i;k++){
                if(!strcmp(ZZfun[k].fileName,ZZfun[i].fileName))break;
            }
            if(k!=i)continue;

            /* is the function operating on property ? */
            k=ZZfun[i].orgInd;
            if(k>=0){ 
                if(!strcmp(ZZorg[k].name,"PROPERTY"))propUsed=1;
            }

	    /* mark all the support code as needed */
            for(k=ZZfun[i].sup;k>=0;k=ZZsup[k].next)ZZsup[k].used=USED;

	    strcpy(buff,ZZpath);
	    strcat(buff,MACRO_PATH);
	    strcat(buff,ZZfun[i].fileName);
            if((ff=myopen(buff,"r"))==NULL){
	        eCount++;
                ZZmsgS(3,ZZfun[i].name); /* cannot open ZZdecrypt for macro */
	    }
	    else {
		cpFile(ff,outFile,NULL);
		fclose(ff);
	        if(strcmp(ZZcryptKey,"*"))delFile((char*)"ZZdecryp");
	    }
	}
    }
    /* support include/macros that are listed from ZZsup[0] are to be
     * used every time */
    for(k=0;k>=0;k=ZZsup[k].next)ZZsup[k].used=USED;

    /* if ASCII mode, Property structure is always used in ZZioFunction() */
    if(ascii && !propUsed){
        strcpy(buff,ZZpath);
        strcat(buff,LIB_PATH);
        strcat(buff,"property.h");
        if((ff=myopen(buff,"r"))==NULL){
            ZZmsgS(0,"lib/property.h"); /* cannot open file lib/property.h */
            return(2);
        }
        cpFile(ff,outFile,NULL);
        fclose(ff);
    }

    /* There may be multiple references to the same support file in ZZsup[];
     * sort the list to avoid duplications */
    for(i=0;ZZsup[i].used!='e';i++)continue; /* i=count of entries */
    ZZoffset=ZZpOffset((char *)(&(ZZsup->fileName)),(char *)ZZsup);
    qsort(ZZsup,i,(int)sizeof(struct ZZsupport),genSortFun);
    /* copy all the support code */
    oldName=(char*)" ";
    for(i=0;ZZsup[i].used!='e';i++){
	if(strcmp(oldName,ZZsup[i].fileName))used=0;
	oldName=ZZsup[i].fileName;
	if(!used && ZZsup[i].used==USED){
	    used=1;
	    strcpy(buff,ZZpath);
	    strcat(buff,LIB_PATH);
	    strcat(buff,ZZsup[i].fileName);
	    /* 1 means automatic detection of encrypted files */
            ff=myopen(buff,"r");
            if(!ff){
	        eCount++;
                ZZmsgS(3,ZZsup[i].fileName); /* cannot open file ZZdecrypt */
	        printf("cannot open file ZZdecryp for %s\n",ZZsup[i].fileName);
	    }
	    else {
		cpFile(ff,outFile,NULL); /* nothing to filter out */
		fclose(ff);
	        if(strcmp(ZZcryptKey,"*")) delFile((char*)"ZZdecryp");
	    }
	}
    }
    return(eCount);
}
/* ---------------------------------------------------------------------- */
/* for any ZZ_ORG and ZZ_HYPER mark all its function as needed */
#ifdef ZZ_ANSI
void expMacros(void)

#else
void expMacros()
#endif
{
    int i,org;

    for(i=0;i<nFun;i++){
        org=ZZfun[i].orgInd;
        if(org<0)ZZfun[i].used=USED; /* always use utilities */
        else if(ZZorg[org].used==USED)ZZfun[i].used=USED;
    }
}
/* ---------------------------------------------------------------------- */
/* Copy functions that are actually used into file zzfunc.c. Create
 * a different instance of the function for each organization/function pair */
#ifdef ZZ_ANSI
int cpFunctions(FILE *outFile)

#else
int cpFunctions(outFile)
FILE *outFile; /* output file */
/* returns number of errors */
#endif
{
    FILE *ff;
    int i,eCount;
    ZZfunInst *fi;
    char create,*p;

    eCount=0;
    for(i=0;i<nFun;i++){
        for(fi=ZZfun[i].inst;fi;fi=fi->next){
            create=ZZfun[i].create; 
	    if(ZZfun[i].used!=BLANK && (create=='f' || 
                        create=='h' || create=='H' || create=='L')){
	        strcpy(buff,ZZpath);
	        strcat(buff,MACRO_PATH);
	        strcat(buff,ZZfun[i].fileName);
                if((ff=myopen(buff,"r"))==NULL){
	            eCount++;
                    ZZmsgS(3,ZZfun[i].name); /* problem to open ZZdecrypt for */
	        }
	        else {
		    if(fi->orgInst){
		        p=fi->orgInst->ident;
                        cpFile(ff,outFile,p);
                    }
		    else if(fi->ext){
		        p= &((fi->ext->name)[7]);
                        cpFile(ff,outFile,p);
                    }
		    fclose(ff);
	            if(strcmp(ZZcryptKey,"*"))delFile((char*)"ZZdecryp");
                    splitLine(outFile);
                }
	    }
	}
    }
    return(eCount);
}
/* ---------------------------------------------------------------------- */
/* Write the internal record of Extentions onto the output file;
 * also create ZZstrList[] with info about all expanded structures,
 * and ZZnxtType[] with the type code for all pointers in all ZZ_EXT.
 *
 * createExt() sets several variables which are later used
 * by createFun(). The reason for this arrangement is that
 * these two functions were originally one function, which
 * was divided into two smaller one, because it was too
 * big for some (Zortech3.0) compilers.
 */
#ifdef ZZ_ANSI
int createExt(FILE *fp,FILE *ff,char *outName,ZZnameList **nlp)

#else
int createExt(fp,ff,outName,nlp)
FILE *fp; /* zzincl.h file */
FILE *ff; /* zzfunc.c file */
char *outName;
ZZnameList **nlp;
/* returns number of pointers */
#endif
{
    int k,nPtr,sInd;
    char s,*nn,*nm;
    ZZextention *ext,*xx;
    ZZextPtr *ptr;
    ZZptrCode *pc;
    ZZnameList *pStart;
    struct ZZinhList *ip,*ipLast;
    ZZfunInst *fi;


    /* general includes for file zzfunc.c */
    fprintf(ff,"#include \"%s\"\n",outName);
    fprintf(ff,"#ifdef FLOATLINK\n#include <math.h>\n#endif\n");

    /* expand  all ZZ_EXT_... */
    pStart=NULL;
    nPtr=0;
    for(ext=ZZext, sInd=0;ext;ext=ext->next, sInd++){
	fprintf(fp,"\n#define %s \\\n",ext->name);
        if(cPlus)createFriends(fp,ext);
	for(ptr=ext->ptr;ptr;ptr=ptr->next){
	    /* first special organizations and non-automatic variables,
               selfId is not a special case */
            if(!strcmp(TIME_STAMP_NAME,ptr->bName)){
                fprintf(fp,"    unsigned char %s[%d]",ptr->bName,ZZtSize);
                nPtr=addPtr(&pStart,ptr->bName,ptr->masterP);
            }
	    else if(!strcmp(ptr->bName,PROPERTY_PTR_NAME)){
	        fprintf(fp,"    %s *%s",PROPERTY_NAME,ptr->bName);
                nPtr=addPtr(&pStart,ptr->bName,ptr->masterP);
            }
	    else if(ptr->ptrCode==NULL){
                fprintf(fp,"    char *%s",ptr->bName);
                nPtr=addPtr(&pStart,ptr->bName,ptr->masterP);
            }
	    else {
                for(pc=ptr->ptrCode;pc;pc=pc->next){
                    nPtr=addPtr(&pStart,pc->pName,pc->masterP);
                    s=pc->masterP->aType;
                    if(s!='a' && s!='g' && s!='A'){
                        if(pc->masterP->aSize<=1)fprintf(fp,"    %s %s",
                                      pc->pointTo,pc->pName);
                        else fprintf(fp,"    %s %s[%d]",
                                      pc->pointTo,pc->pName,pc->masterP->aSize);
                    }
                    else if(!strcmp("char*",pc->pointTo)){
	                fprintf(fp,"    char %c%s",AST,pc->pName);
                    }
                    else{
	                fprintf(fp,"    %s %c%s",pc->pointTo,AST,pc->pName);
                    }
	            if(pc->next)fprintf(fp,";\\\n");
                }
            }
	    if(ptr->next)fprintf(fp,";\\\n");
	    else         fprintf(fp,";");
	}

        /* if C++, initialization function must be declared */
        if(cPlus){
            nn=(&(ext->name[7]));
            fprintf(fp,"\\\npublic:\\\n");
            if(ext->virt=='v')fprintf(fp,"    virtual ");
            else              fprintf(fp,"    ");
            fprintf(fp,"void *zzThisIs(ZZint *type){*type=%d;",sInd);
            fprintf(fp," return((void*)this);};\\\n");
            fprintf(fp,
   "    void ZZinitSet(void){if(ZZnumObjects>0)ZZnumObjects--; ZZSS_%s(this)};",nn);
            if(ext->hasConstr=='n' && friends && inherit)
                  fprintf(fp,"\\\n    %s(){};",nn);
	    if(ext->hasDestr=='n' && friends && inherit && !noDestr && !noCheck)
	          fprintf(fp, "\\\n   %s~%s(){ZZ_CHECK(%s);};",
		         (ext->virt=='v' ? " virtual " : ""),nn,nn);

            if(ext->iList)fprintf(fp,"\\\n    %s(ZZZiClass *x);",nn);
            else fprintf(fp,"\\\n    %s(ZZZiClass *);",nn);
            if(ext->iList)fprintf(ff,"%s::%s(ZZZiClass *x)",nn,nn);
            else fprintf(ff,"%s::%s(ZZZiClass *)",nn,nn);
            /* mark all constructors as not used */
            for(xx=ZZext; xx; xx=xx->next)xx->used='N'; 
            /* prepare the reverse list, otherwise warnings under LINUX */
            for(ip=ext->iList, ipLast=NULL, k=0; ip; ip=ip->next){
                ip->prevTemp=ipLast;
                ipLast=ip;
            }
            /* now traverse in the opposite direction */
            for(ip=ipLast, k=0; ip; ip=ip->prevTemp){
                nm=ip->name;
                xx=ip->ext;
                if(!strcmp(nm,"ZZrefer")){
                    if(k==0)fprintf(ff,":"); else fprintf(ff,",");
                    fprintf(ff,"%s(x)",&(ip->ext->name[7]));
                    xx->used='Y';
                    k++;
                }
                else if(!strcmp(nm,"ZZinherit")){
                    if(k==0)fprintf(ff,":"); else fprintf(ff,",");
                    fprintf(ff,"%s(x)",&((xx->name)[7]));
                    xx->used='Y';
                    k++;
                }
                else if(strcmp(nm,"ZZvirtual")){
                    if(k==0)fprintf(ff,":"); else fprintf(ff,",");
                    fprintf(ff,"%s(x)",ip->name);
                    xx->used='Y';
                    k++;
                }
            }
            recVirtBase(ext,&k,ff); 
            for(xx=ZZext; xx; xx=xx->next)xx->used='N'; 
            fprintf(ff,"{ZZSS_%s(this)}\n",nn);

            fprintf(fp,"\\\n    void * operator new(size_t size);");
            fprintf(ff,
" void* %s::operator new(size_t size){void *ZZmassAlloc(size_t,ZZint);\n",nn);
            fprintf(ff,"  ZZnumObjects++;\n",nn);
            fprintf(ff,"  if(ZZmemSwitch){%s *p;\n",nn);
            fprintf(ff,"    ZZ_OBJECT_ALLOC(%s,p);return((void*)p);}\n",nn);
            fprintf(ff,"  else {return(ZZmassAlloc((size_t)size,(ZZint)1));}}\n");
            fprintf(fp,"\\\n    void operator delete(void *ptr);");
            fprintf(ff,
" void %s::operator delete(void *ptr){void ZZmassFree(void *);\n",nn);
            fprintf(ff,"  if(ZZnumObjects>0)ZZnumObjects--;\n");
            fprintf(ff,"  if(ZZmemSwitch)ZZ_OBJECT_FREE(%s,(%s *)ptr)\n",nn,nn);
            fprintf(ff,"  else ZZmassFree(ptr);}\n");
            fprintf(fp,"\\\n    static %s *newObj(void){%s *p; ZZ_OBJECT_NEW(%s,p); return p;}",nn,nn,nn);
            fprintf(fp,"\\\n    static void delObj(%s *p){ZZ_OBJECT_FREE(%s,p);}",nn,nn);
            /* also, with inheritance and ASCII IO declare io functions */
            if(inherit && ascii){
                fprintf(fp,"\\\n    int zz_inp_%s(FILE *,%s *);\\\n",nn,nn);
                fprintf(fp,"    int zz_out_%s(FILE *,%s *);\\\n",nn,nn);
                fprintf(fp,"    void zz_ipt_%s(%s *);\\\n",nn,nn);
                fprintf(fp,"    void zz_opt_%s(FILE *,%s *);",nn,nn);
            }
            /* for object-assigned functions such as selfId,timeStamp,
             * or property, insert functions */
            for(fi=ext->fun;fi;fi=fi->nxt){
                fprintf(fp,"\\\n    ZZEXT%s(%s)",
                           &(fi->parent->name[9]),&(ext->name[7]));
            }
        }
        else fprintf(fp,"\n");
        fprintf(fp,"\n\n");
    }
    *nlp=pStart;
    return(nPtr);
}
/* ---------------------------------------------------------------------- */
/* Create ZZI<typeName> defines for fast searches by type.
 * and         ZZJ<typeName> defines for fast setting of selfID
 */
#ifdef ZZ_ANSI
int createFun(FILE *fp, FILE *umlFile, int nPtr,ZZnameList *pStart)

#else
int createFun(fp,umlFile,nPtr,pStart)
FILE *fp; /* output file */
FILE *umlFile; /* file for the UML logic */
int nPtr; /* number of pointers detected by createExt() */
ZZnameList *pStart;
/* returns number of errors */
#endif
{
    int vrt,i,ii,k,kk,n,self,prop,time,array,ptrInd,inhInd,started;
    char c,s,*nn,*ans;
    ZZextention *ext,*xx;
    ZZextPtr *ptr;
    ZZptrCode *pc;
    ZZnameList *pn;
    struct ZZinhList *ip,*sp,*np;

    /* create ZZI<typeName> for fast searches by type name */
    /* create ZZJ<typeName> for fast searches of selfID */
    if(multiProj){ /* ZZI and ZZJ will be defines */
        for(ext=ZZext, i=k=0; ext; ext=ext->next, i++){
            fprintf(fp,"#define ZZI%s %d\n",&(ext->name[7]),i);
            kk= -1;
	    ptr=ext->ptr;
	    if(ptr && !strcmp(ptr->bName,SELFID_PTR_NAME)){
                kk=k;
                k++;
            }
            fprintf(fp,"#define ZZJ%s %d\n",&(ext->name[7]),kk);
        }
        fprintf(fp,"#define ZZIint   -6\n");
        fprintf(fp,"#define ZZIfloat -7\n");
        fprintf(fp,"#define ZZIchar  -1\n\n");
    }
    else {  /* ZZI and ZZJ will be functions */
        if(ansi)ans=(char*)"void"; else ans=(char*)" ";
        for(ext=ZZext, i=k=0; ext; ext=ext->next, i++){
            nn= &(ext->name[7]);
            fprintf(fp,"#define ZZI%s ZZZI%s()\n",nn,nn);
            fprintf(fp,"ZZ_LOCAL int ZZZI%s(%s);\n",nn,ans);
            fprintf(fp,"#define ZZJ%s ZZZJ%s()\n",nn,nn);
            fprintf(fp,"ZZ_LOCAL int ZZZJ%s(%s);\n",nn,ans);
        }
        fprintf(fp,"#define ZZIint ZZZIint()\n");
        fprintf(fp,"ZZ_LOCAL int ZZZIint(%s);\n",ans);
        fprintf(fp,"#define ZZIfloat ZZZIfloat()\n");
        fprintf(fp,"ZZ_LOCAL int ZZZIfloat(%s);\n",ans);
        fprintf(fp,"#define ZZIchar ZZZIchar()\n");
        fprintf(fp,"ZZ_LOCAL int ZZZIchar(%s);\n",ans);
        fprintf(fp,"#ifdef ZZmain\n");
        fprintf(fp,"ZZ_LOCAL int ZZZIint(%s){return(-6);}\n",ans);
        fprintf(fp,"ZZ_LOCAL int ZZZIfloat(%s){return(-7);}\n",ans);
        fprintf(fp,"ZZ_LOCAL int ZZZIchar(%s){return(-1);}\n\n",ans);
        fprintf(fp,"#endif\n");
    }

    /* For multiProjects, type tables must be static in each file.
     * For normal projects, they are global, reused by the whole system */
    if(!multiProj)fprintf(fp,"#ifdef ZZmain\n");

    /* print the list of all pointers */
    if(multiProj)fprintf(fp,"\nstatic "); else fprintf(fp,"\n");
    fprintf(fp,"ZZ_LOCAL char *ZZptrList[]={\n");
    for(pn=pStart;pn;pn=pn->next){
        fprintf(fp,"    (char*)\"%s\"",pn->name);
        if(pn->next)fprintf(fp,",\n"); else fprintf(fp,"\n");
    }
    if(!pStart)fprintf(fp,"\"\"\n"); /* default one dummy entry */
    fprintf(fp,"};\n");
    /* total number of pointers is nPtr, but they do not have to be
     * explicitely printed, they must be the total of numPtr for
     * individual types */

    /* count number of entries in ZZstrList[] including ZZendMark at the end */
    for(n=1, ext=ZZext; ext; ext=ext->next)n++;

    /* create ZZstrList[] with ZZendMark at the end */
    ii=0;
    if(multiProj)fprintf(fp,"\nstatic "); else fprintf(fp,"\n");
    fprintf(fp,"ZZ_LOCAL struct ZZstrLST ZZstrList[%d]={\n",n);
    for(ext=ZZext, ptrInd=inhInd=0; ext; ext=ext->next, ptrInd+=kk){
	self=prop=time=array= -1;
	i=kk=0;
	for(ptr=ext->ptr;ptr;ptr=ptr->next){
            s=ptr->masterP->aType;
            if(s=='i' || s=='f' || s=='c')continue;
	    else if(!strcmp(SELFID_PTR_NAME,ptr->bName))  {self=i; i++; kk++;}
	    else if(!strcmp(PROPERTY_PTR_NAME,ptr->bName)){prop=i; i++; kk++;}
	    else if(!strcmp(TIME_STAMP_NAME,ptr->bName))  {time=i; kk++;}
            else {
                kk+=(ptr->count);
                if(s=='A'){if(array<0)array=i; i+=(ptr->count);}
	        else if(s=='a' || s=='g') i+=(ptr->count);
            }
	}
        ii+=kk;

        /* vrt= bin packed
         *      01 = abstract class
         *      02 = virtual base class
         *      04 = virtual functions used
         */
        vrt=ext->vcPres;
        if(ext->virt=='v')vrt=vrt|04;

        fprintf(fp,"  {(char*)\"%s\", 0, 0, %d, %d, %d, %d, %d, %d, %d, {0,0}, %d}, \n",
                      &(ext->name[7]),i,self,prop,time,array,ptrInd,inhInd,vrt);
        allocPtr++;
        for(ip=ext->iList;ip;ip=ip->next)inhInd++;
    }
    fprintf(fp,"  {(char*)\"ZZendMark\", -1, -1, -1, -1, -1, -1, -1, %d, %d, {0, 0}, 0}};\n\n",
                                                                 ptrInd,inhInd);
    allocPtr=allocPtr*nPtr; /* before, allocPtr is total of types */

    /* create ZZnxtType[]:   -1 name,-2 special,-4 array, -8 general */
    /* IMPORTANT: ii<=0 means no organizations, no pointers used, but some
     * people want to use only the save/open feature, so we have to go on
     * and create dummy arrays ptrList[] and nxtType[].
     * Originally program returned 0 here, but that caused unfinished
     * ifdef statement in zzincl.h file */
    if(ii<1)kk=1; /* make array nxtType[] at least 1 long */
    else kk=ii;
    if(multiProj)fprintf(fp,"\nstatic "); else fprintf(fp,"\n");
    fprintf(fp,"ZZ_LOCAL ZZint ZZnxtType[%d]={\n",kk);
    c=' ';  /* blank flags the beginning of the whole record/line */
    for(ext=ZZext; ext; ext=ext->next){
        if(c!=' ')fprintf(fp,",\n");
        c=' ';
	for(ptr=ext->ptr;ptr;ptr=ptr->next){
            s=ptr->masterP->aType;
	    if     (!strcmp(SELFID_PTR_NAME,ptr->bName))prt1(fp,&c,-2);
	    else if(!strcmp(PROPERTY_PTR_NAME,ptr->bName))prt1(fp,&c,-2);
	    else if(!strcmp(TIME_STAMP_NAME,ptr->bName))prt1(fp,&c,-8);
	    else if(s=='a' || s=='g' || s=='A'){
                for(pc=ptr->ptrCode;pc;pc=pc->next){
                    for(xx=ZZext, i=0; xx; xx=xx->next, i++){
                        if(!strcmp(pc->pointTo,&(xx->name[7])))break;
                    }
                    if(xx)          k=i;
                    else if(s=='A') k= -4;
                    else if(s=='g') k= -8;
                    else            k= -1;
                    prt1(fp,&c,k);
                }
            }
	}
    }
    if(ii<1)fprintf(fp,"0");
    fprintf(fp,"\n};\n");

    /* print the inheritance list */
    /* at the same time generate the UML inheritance records */
    if(multiProj)fprintf(fp,"\nstatic "); else fprintf(fp,"\n");
    fprintf(fp,"ZZ_LOCAL struct ZZtypeHier ZZinhList[%d]={\n",inhInd+1);
    for(ext=ZZext, k=0; ext; ext=ext->next){
        /* reverse the list to restore order, essential for offsets */
        sp=NULL;
        for(ip=ext->iList;ip;ip=np){
            np=ip->next;
            ip->next=sp;
            sp=ip;
        }
        ext->iList=sp;
        /* now print the list, and set the order index */
        started=0; /* for the UML record */
        for(ip=ext->iList; ip; ip=ip->next, k++){
            ip->ind=k;
            kk=extInd(&((ip->ext->name)[7]));
            nn=ip->name;
            fprintf(fp," {%d, -1, %d, (char*)\"%s\"},\n",kk,ip->num,nn);

            /* now the UML record, possibly multiple inheritance */
            if(ip->num==0){ /* case of ZZinherit */
                if(!started) fprintf(umlFile,"Inherits %s",&((ext->name)[7]));
                fprintf(umlFile," %s",&((ip->ext->name)[7]));
                started=1;
            }
        }
        if(started)fprintf(umlFile," ;\n"); // end of the UML record
    }
    fprintf(fp," {-1, -1, -1, (char*)\"ZZendMark\"}\n};\n");
    
    if(!multiProj){
    fprintf(fp,"#else\n");
    fprintf(fp,"extern char *ZZptrList[];\n");
    fprintf(fp,"extern struct ZZstrLST ZZstrList[];\n");
    fprintf(fp,"extern ZZint ZZnxtType[];\n");
    fprintf(fp,"extern struct ZZtypeHier ZZinhList[];\n");
    fprintf(fp,"#endif\n");
    }
    fprintf(fp,"#define ZZstrNum %d\n",n-1);
    return(0);
}
/* ---------------------------------------------------------------------- */
/* recursive search for virtual base classes */
#ifdef ZZ_ANSI
void recVirtBase(ZZextention *ext,int *k, FILE *fp){

#else
void recVirtBase(ext,k,fp)
ZZextention *ext; /* given class */
int *k;  /* count of already used sub-class constructors, may change */
FILE *fp; /* file to write to */
{
    void recVirtBase();
#endif
    struct ZZinhList *ip;
    ZZextention *xx;

    for(ip=ext->iList; ip; ip=ip->next){
        xx=ip->ext;
        if(!strcmp(ip->name,"ZZvirtual") && xx->used=='N'){
            if(*k==0)fprintf(fp,":"); else fprintf(fp,",");
            fprintf(fp,"%s(x)",&((xx->name)[7]));
            xx->used='Y';
            (*k)++;
        }
        recVirtBase(ip->ext,k,fp);
    }
}
/* ---------------------------------------------------------------------- */
/* Remove virtual function flag from those extentions (classes) that inherit
 * virtual function already. This is the way C++ internally keeps pointers:
 * only the lowest classes in the inheritance tree that have virtual
 * functions keep the pointer. However, this pointer takes on a different
 * value, if the class is used within another class that also has virtual
 * function or functions. */
#ifdef ZZ_ANSI
void weedVirt(void)

#else
void weedVirt()
#endif
{
    ZZextention *ext;
    struct ZZinhList *ip;
    int k;

    for(ext=ZZext; ext; ext=ext->next)ext->inCode='1';
    for(k=1;k==1;){
        k=0;
        for(ext=ZZext; ext; ext=ext->next){
            if(ext->inCode=='1'){
                for(ip=ext->iList; ip; ip=ip->next){
                    if(ip->ext->virt=='v' || ip->ext->inCode==0)break;
                }
                if(ip){
                    ext->inCode='0';
                    ext->virt=' ';
                    k=1;
                }
            }
        }
    }
}
/* ---------------------------------------------------------------------- */
/* add new name onto the pointer list
 * Add to the end of the list, so that the order is preserved.
 * Returns number of objects on the list.
 * WARNING: The name must be permanent, no new copy of the name
 *          is created */
#ifdef ZZ_ANSI
int addPtr(ZZnameList **start,char *name,ZZpointer *master)

#else
int addPtr(start,name,master)
ZZnameList **start;
char *name;
ZZpointer *master;
#endif
{
    static ZZnameList *tail;
    static int count={0};
    ZZnameList *p;
    char *nn;
    static char tBuff[80];
    int k;

    /* form the pointer, leading character determines type, end array size */
    k=master->aSize;
    if(k<1)k=1;
    sprintf(tBuff,"%c%s[%d\0",master->aType,name,k);

    p=(ZZnameList *)malloc((int)sizeof(struct ZZnameList));
    nn=(char *)malloc(strlen(tBuff)+1);
    if(!p || !nn){ ZZmsgS(1,"internal pointer list"); return(count); }
    strcpy(nn,tBuff);
    if(*start) {tail->next=p; count++;}
    else {(*start)=p; count=1;}
    tail=p;
    p->next=NULL;
    p->name=nn;
    return(count);
}
/* ---------------------------------------------------------------------- */
/* Create friends to hyper-classes only. */
#ifdef ZZ_ANSI
void createFriends(FILE *fp,ZZextention *ext)

#else
void createFriends(fp,ext)
FILE *fp;
ZZextention *ext;
#endif
{
    ZZnameList *fStart,*fr,*ff;
    ZZorgInst *op;
    ZZstrType *st;

    fStart=NULL; /* start with an empty list */
    /* friends back to hyper-classes */
    for(op=ZZinst;op;op=op->next){
        for(st=op->sType;;st=st->next){
            if(!strcmp(st->name,&(ext->name[7]))){
                if(op->partOf){              
                    strcpy(buff,op->partOf);
                    strcat(buff," :: ");   
                    strcat(buff,"ZZH");
                }                         
                else strcpy(buff,"ZZH");
                strcat(buff,op->ident);
                addFriend(&fStart,buff);
            }
            if(st==op->lType)break;
        }
    }

    /* print all the friend declarations, and free the friend list */
    for(fr=fStart;fr;fr=ff){
        ff=fr->next;
        if(cPlus&&friends)fprintf(fp,"friend class %s;\\\n",fr->name);
        free(fr);
    }
}
/* ---------------------------------------------------------------------- */
/* Declare classes as general types */
#ifdef ZZ_ANSI
void declareClasses(FILE *fp)

#else
void declareClasses(fp)
FILE *fp;
#endif
{
    ZZextention *ext;

    for(ext=ZZext;ext;ext=ext->next){
        if(ext->isClass=='c')fprintf(fp,"class %s;\n",&(ext->name[7]));
        else            fprintf(fp,"struct %s;\n",&(ext->name[7]));
    }
}
/* ---------------------------------------------------------------------- */
/* Add a new friend to the list. Check, that each friend-class appears
 * only once on the list. Since this is only a short list, n*n checking
 * is just fine. In case of allocation problem, just issue a message
 * and do not stop the operation. */
#ifdef ZZ_ANSI
void addFriend(ZZnameList **fStart,char *name)

#else
void addFriend(fStart,name)
ZZnameList **fStart; /* start of the list, may change */
char *name; /* name of the new friend-class */
#endif
{
    ZZnameList *fr;

    /* is this class on the list already ? */
    for(fr= *fStart;fr;fr=fr->next){
        if(!strcmp(fr->name,name))return;
    }

    fr=(ZZnameList *)malloc((int)sizeof(struct ZZnameList));
    if(!fr){
        ZZmsgS(1,"friends"); /* allocation problem for friends */
        return;
    }

    /* add the new class to the list */
    fr->next= *fStart;
    fr->name=(char *)malloc(strlen(name)+1);
    if(!fr->name){
        ZZmsgS(1,"friends"); /* allocation problem for friends */
        return;
    }
    strcpy(fr->name,name);
    *fStart=fr;
}
/* ---------------------------------------------------------------------- */
/* create zz_inp_..() and zz_out_..() functions for all ZZ_FORMATS */
#ifdef ZZ_ANSI
void createFormat(FILE *fp)

#else
void createFormat(fp)
FILE *fp;
#endif
{
    ZZextention *ext;
    char *tp,*p,*pp;
    int i;
    struct ZZnameList *np;

    /* input */
    for(ext=ZZext;ext;ext=ext->next){
        if(!(ext->format))continue; /* skip EXT without FORMAT statement */
        tp= &((ext->name)[7]);
        if(ansi){
            if(cPlus&&inherit)
                fprintf(fp,"\nint %s::zz_inp_%s(FILE *fp,%s *p)\n{\n",tp,tp,tp);
            else fprintf(fp,"\nint zz_inp_%s(FILE *fp,%s *p)\n{\n",tp,tp);
        }
        else {
            fprintf(fp,"\nint zz_inp_%s(fp,p) FILE *fp; %s *p;\n{\n",tp,tp);
        }
        
        /* if %a is used, declare special variables */
        for(np=ext->fList;np;np=np->next){
            if(np->formatCode>0)fprintf(fp,"    unsigned long i%d=0;\n",np->formatCode);
        }

        if(ext->fList){
            fprintf(fp,"    if(!fgets(ZZbuff,ZZ_BUFS,fp))return(1);\n");
            fprintf(fp,"    sscanf(ZZbuff,\"%s\"",ext->format);
            for(np=ext->fList;np;np=np->next){
                if(np->formatCode)fprintf(fp,",&i%d",np->formatCode);
                else fprintf(fp,",&(p->%s)",np->name);
            }
            fprintf(fp,");\n");

            /* convert special values to characters */
            for(np=ext->fList;np;np=np->next){
                if(np->formatCode>0)fprintf(fp,"    p->%s=(%s)i%d;\n",
                         np->name,np->cast,np->formatCode);
            }
        }
        else fprintf(fp,"    fp=fp; p=p;\n");
        fprintf(fp,"    return(0);\n}\n");
        splitLine(fp);
    }
   
    /* output */
    for(ext=ZZext;ext;ext=ext->next){
        if(!(ext->format))continue; /* skip EXT without FORMAT statement */
        tp= &((ext->name)[7]);
        if(ansi){
            if(cPlus&&inherit)
                fprintf(fp,"\nint %s::zz_out_%s(FILE *fp,%s *p)\n{\n",tp,tp,tp);
            else fprintf(fp,"\nint zz_out_%s(FILE *fp,%s *p)\n{\n",tp,tp);
        }
        else {
            fprintf(fp,"\nint zz_out_%s(fp,p) FILE *fp; %s *p;\n{\n",tp,tp);
        }
        if(ext->fList){
            /* sneak variable names into the debugging format */
            fprintf(fp,"    if(ZZdebFLG)fprintf(fp,\"");
            for(np=ext->fList, pp=ext->format;np;np=np->next){
                for(p=pp;*p!='\0' && *p!='%';p++)continue; /* find next % */
                pp=p+1;
                for(i=0;*p!=' ' && *p!='\0';p++,i++)buff[i]=(*p);
                buff[i]='\0';
                fprintf(fp," %s=%s",np->name,buff); 
            }
            fprintf(fp,"\\n\"");
            for(np=ext->fList;np;np=np->next)fprintf(fp,",p->%s",np->name);
            fprintf(fp,");\n");

            /* normal output for storing on disk */
            fprintf(fp,"    else fprintf(fp,\"%s\\n\"",ext->format);
            for(np=ext->fList;np;np=np->next){
                if(np->formatCode)fprintf(fp,",(unsigned long)(p->%s)",np->name);
                else              fprintf(fp,",p->%s",np->name);
            }
            fprintf(fp,");\n");
        }
        else fprintf(fp,"    fp=fp; p=p;\n");
        fprintf(fp,"    return(0);\n}\n");
        splitLine(fp);
    }
}
/* ---------------------------------------------------------------------- */
/* create zz_ipt_..() and zz_opt_..() functions for all ZZ_EXT_ */
#ifdef ZZ_ANSI
void createPform(FILE *fp)

#else
void createPform(fp)
FILE *fp;
#endif
{
    ZZextention *ext;
    char *tp;

    /* input */
    for(ext=ZZext;ext;ext=ext->next){
        tp= &((ext->name)[7]);
        if(ansi){
            if(cPlus&&inherit)
                 fprintf(fp,"\nvoid %s::zz_ipt_%s(%s *p){\n",tp,tp,tp);
            else fprintf(fp,"\nvoid zz_ipt_%s(%s *p){\n",tp,tp);
        }
        else fprintf(fp,"\nvoid zz_ipt_%s(p)%s *p;{\n",tp,tp);
        formFormat(fp,ext,0);
        if(!(ext->ptr))fprintf(fp," p=p;\n");
        fprintf(fp,"}\n");
        splitLine(fp);
    }
   
    /* output */
    for(ext=ZZext;ext;ext=ext->next){
        tp= &((ext->name)[7]);
        if(ansi){
            if(cPlus&&inherit)
                 fprintf(fp,"\nvoid %s::zz_opt_%s(FILE *fp,%s *p){\n",tp,tp,tp);
            else fprintf(fp,"\nvoid zz_opt_%s(FILE *fp,%s *p){\n",tp,tp);
        }
        else fprintf(fp,"\nvoid zz_opt_%s(fp,p)FILE *fp;%s *p;{\n",tp,tp);
        formFormat(fp,ext,1);
        if(!(ext->ptr))fprintf(fp," fp=fp; p=p;\n");
        fprintf(fp,"}\n");
        splitLine(fp);
    }
}
/* ---------------------------------------------------------------------- */
/* Form a general function for ASCII SAVE/OPEN, which calls user given
 * macros for non-automatic attributes. For example, for structure Block,
 * the user has to supply zz_inp_Block(fp,p) and zz_out_Block(fp,p).
 */
#ifdef ZZ_ANSI
void createIO(FILE *fp)

#else
void createIO(fp)
FILE *fp; /* output file */
#endif
{
    int i;
    char *tp;
    ZZextention *ext;
    FILE *ff;

    /* declare all user-coded io functions */
    if(ansi==0){
        fprintf(fp,"\nZZint ZZioFunction(fp,(ZZint)io,(ZZint)type,p,strSz)\n");
        fprintf(fp,"FILE *fp; int io; int type; char *p;\n{\n");
        if(cPlus && inherit){} /* no prototypes */
        else {
            for(ext=ZZext, i=0;ext;ext=ext->next, i++){
                tp=(&(ext->name[7]));
                fprintf(fp,"  int zz_out_%s(),zz_inp_%s();\n",tp,tp);
                fprintf(fp,"  void zz_opt_%s(),zz_ipt_%s();\n",tp,tp);
            }
        }
    }
    else {
       fprintf(fp,"\nZZint ZZioFunction(FILE *fp,ZZint io,ZZint type,char *p,ZZint strSz)\n{\n");
       for(ext=ZZext, i=0;ext;ext=ext->next, i++){
           tp=(&(ext->name[7]));
           fprintf(fp,
             "  int zz_out_%s(FILE *f,%s *ptr),zz_inp_%s(FILE *f,%s *ptr);\n",
                                                                 tp,tp,tp,tp);
           fprintf(fp,
             "  void zz_opt_%s(FILE *f,%s *ptr),zz_ipt_%s(%s *ptr);\n",
                                                                 tp,tp,tp,tp);
        }
    }

    /* copy the precoded file for the hardwired structures */
    strcpy(buff,ZZpath);
    strcat(buff,MACRO_PATH);
    strcat(buff,"iofun");
    if((ff=myopen(buff,"r"))==NULL){
        ZZmsgS(0,"macro/iofun"); /* cannot open file macro/iofun */
        return;
    }
    cpFile(ff,fp,NULL);
    fclose(ff);

    /* create the switch statement */
    for(ext=ZZext, i=0;ext;ext=ext->next, i++){
        tp=(&(ext->name[7]));
	fprintf(fp,"\n    case %d:\n      if(io==1)",i);
        if(cPlus && inherit)fprintf(fp,"((%s *)p)->",tp);
        fprintf(fp,"zz_opt_%s(fp,(%s *)p);\n",tp,tp);
	fprintf(fp,"      if(io==1 || io==3)");
        if(cPlus && inherit)fprintf(fp,"((%s *)p)->",tp);
        fprintf(fp,"zz_out_%s(fp,(%s *)p);\n",tp,tp);
        fprintf(fp,"      else {\n");
        fprintf(fp,"          if(io==0)");
        if(cPlus && inherit)fprintf(fp,"((%s *)p)->",tp);
        fprintf(fp,"zz_ipt_%s((%s *)p);\n",tp,tp);
	fprintf(fp,"         if(");
        if(cPlus && inherit)fprintf(fp,"((%s *)p)->",tp);
	fprintf(fp,"zz_inp_%s(fp,(%s *)p))return(1);\n",tp,tp);
        fprintf(fp,"      }\n      break;\n");
    }
    fprintf(fp,
        "\n    default: printf(\"ASCII IO wrong type=%%d\\n\",type); break;\n");
    
    /* end of the function */
    fprintf(fp,"  }\nreturn(0);\n}\n");
}
/* ---------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void formFormat(FILE *fp,ZZextention *ext,int io)

#else
void formFormat(fp,ext,io)
FILE *fp;
ZZextention *ext;
int io; /* 1=output, 0=input */
#endif
{
    static char *pf[]={(char*)"%I64u",(char*)"%lu",(char*)"%d"};
    char *s,*c,r;
    int i,k,pt;
    ZZextPtr *ptr,*tPtr;
    ZZptrCode *pc;

    /* is the time stamp used ? */
    tPtr=NULL;
    for(ptr=ext->ptr;ptr;ptr=ptr->next){
        if(!strcmp(TIME_STAMP_NAME,ptr->bName)){tPtr=ptr; break;}
    }
    if(tPtr && !io)fprintf(fp,"        {int ts[%d];\n",ZZtSize);

    fprintf(fp,"#ifdef Windows64\n");
    for(pt=0; pt<3; pt++){
      if(io){
        c=(char*)"          ";
        if(ext->ptr)fprintf(fp,"        fprintf(fp,\"");
      }
      else {
        c=(char*)"          &";
        if(ext->ptr)fprintf(fp,"        sscanf(ZZbuff,\"");
      }

      /* format */
      for(ptr=ext->ptr;ptr;ptr=ptr->next){
        if(ptr==tPtr){
            for(i=0;i<ZZtSize;i++)fprintf(fp,"%%d ");/* time stamp always int */
        }
        else if(!strcmp(ptr->bName,PROPERTY_PTR_NAME))fprintf(fp,"%s",pf[pt]);
        else if(ptr->ptrCode==NULL)fprintf(fp,"%s",pf[pt]);
        else {
            for(pc=ptr->ptrCode;pc;pc=pc->next){
                r=pc->masterP->aType;
                if(r!='a' && r!='g' && r!='A'){
                    if(!strcmp(pc->pointTo,"float"))s=(char*)"%f";
                    else if(!strcmp(pc->pointTo,"char"))s=(char*)"%c";
                    else if(!strcmp(pc->pointTo,"int"))s=(char*)"%d";
                    else s=pf[pt];
                    k=pc->masterP->aSize;
                    if(k<1)k=1;
                    for(i=0;i<k;i++)fprintf(fp,"%s",s);
                }
                else fprintf(fp,"%s",pf[pt]);
                if(pc->next)fprintf(fp," ");
            }
        }
        if(ptr->next)fprintf(fp," ");
        else {
            if(io)fprintf(fp,"\\n\",\n");
            else  fprintf(fp,"\",\n");
        }
      }
      if(pt==0)fprintf(fp,"#else\n#ifdef LARGE_POINTER\n");
      else if(pt==1)fprintf(fp,"#else\n");
      else     fprintf(fp,"#endif\n#endif\n");
    }

    for(ptr=ext->ptr;ptr;ptr=ptr->next){
        if(ptr==tPtr){
             for(i=0;i<ZZtSize;i++){
                 if(io) fprintf(fp,"%s((%s *)p)->%s[%d]",
                                              c,&(ext->name[7]),tPtr->bName,i);
                 else fprintf(fp,"%s(ts[%d])",c,i);
                 if(i<ZZtSize-1)fprintf(fp,",\n");
             }
             
        }
        else if(!strcmp(ptr->bName,PROPERTY_PTR_NAME))
             fprintf(fp,"%s(((%s *)p)->%s)",c,&(ext->name[7]),ptr->bName);
        else if(ptr->ptrCode==NULL)fprintf(fp,"%s(((%s *)p)->%s)",
                                              c,&(ext->name[7]),ptr->bName);
        else {
            for(pc=ptr->ptrCode;pc;pc=pc->next){
                k=pc->masterP->aSize;
                if(k<1)k=1;
                if(k>1){
                    for(i=0;i<k;i++)fprintf(fp,"%s(((%s *)p)->%s[%d])",
                                              c,&(ext->name[7]),pc->pName,i);
                }
                else fprintf(fp,"%s(((%s *)p)->%s)",
                                              c,&(ext->name[7]),pc->pName);
                if(pc->next)fprintf(fp,",\n");
            }
        }
        if(ptr->next)fprintf(fp,",\n");
        else         fprintf(fp,");\n");
    }
    if(tPtr && !io){
        for(i=0;i<ZZtSize;i++){
            fprintf(fp,"        ((%s *)p)->%s[%d]=ts[%d];\n",
                                              &(ext->name[7]),tPtr->bName,i,i);
        }
        fprintf(fp,"        }\n");
    }
}
/* ---------------------------------------------------------------------- */
/* print one number, reset comma field */
#ifdef ZZ_ANSI
void prt1(FILE *fp,char *c,int num)

#else
void prt1(fp,c,num)
FILE *fp; /* file where to print */
char *c;  /* blank or comma before the number */
int num;  /* number to print */
#endif
{
    fprintf(fp,"%c%d",*c,num);
    *c=',';
}
/* ---------------------------------------------------------------------- */
/* Generate source code for the function that fills the type tables
 * Generate function ZZvSet() which sets vf. and vc. pointers
 * on new objects in C++>
 * Generate function ZZtopType() which, through virtual functions,
 * detects the top class pointer and type (only in C++).
 */
#ifdef ZZ_ANSI
void zzfuncGen(FILE *fp)

#else
void zzfuncGen(fp)
FILE *fp; /* default for this file is zzfunc.c file */
#endif
{
    int i,k,kk;
    char *tp,*te,*ans;
    ZZextention *ext,*ep;
    ZZextPtr *ptr;

    if(ascii)createIO(fp);  /* create io function for ASCII save */
    splitLine(fp);
    /* create format, if any ZZ_FORMAT used */
    if(uFormat&&ascii)createFormat(fp);/* create format in the same file */
    if(ascii)createPform(fp); /* create io functions for ZZ pointers */
    if(selectFunctions)cpFunctions(fp);/* create save function for ASCII */

    if(ansi)fprintf(fp,"\nZZ_LOCAL void ZZ_GENERAL_EXT(void){\n  char *p; int i;\n");
    else    fprintf(fp,"\nZZ_LOCAL void ZZ_GENERAL_EXT() {\n  char *p; int i;");
    if(cPlus)fprintf(fp,"  void ZZsetMask(void);\n");
    fprintf(fp,"  static int repeat={0};\n");
    /* Without using a float function, TurboC does not link float libraries */
    fprintf(fp,"#ifdef FLOATLINK\ndouble x; x=sin(0.0); x=x;\n#endif\n");
    fprintf(fp,"#ifdef ZORTECH\n{void dumbZortechLinker(); ");
    fprintf(fp,"dumbZortechLinker();}\n#endif\n");
    fprintf(fp,"  ZZorgcVersion=ZZorgcVersion;\n");
    fprintf(fp,"  p=NULL;\n  p=p;\n  ZZsList=ZZstrList;\n");
    fprintf(fp,"  ZZpList= &(ZZptrList[0]);\n  ZZiList= &(ZZinhList[0]);\n");
    fprintf(fp,"  if(repeat)return;else repeat=1;\n");

    /* first loop generates pointers to object prototypes for virt.functions */
    if(cPlus){
      if(ZZext)for(ext=ZZext, i=0; ext; ext=ext->next, i++){
          /* find first class that can have an instance */
          for(ep=ext;ep->aClass;ep=ep->aClass)continue;
          tp= &(ext->name[7]);
          te= &(ep->name[7]);
          fprintf(fp,"  if(!(ZZstrList[%d].vObj[0])){\n",i);
          if(ext==ep){
              fprintf(fp,
      "    ZZstrList[%d].vObj[0]=(char *)(new %s((ZZZiClass *)NULL));\n",i,tp);
              fprintf(fp,
      "    ZZstrList[%d].vObj[1]=(char *)(new %s((ZZZiClass *)NULL));\n  }\n",i,tp);
           }
          else {
               fprintf(fp,
"    ZZstrList[%d].vObj[0]=(char *)((%s *)(new %s((ZZZiClass *)NULL)));\n",
                         i,tp,te);
               fprintf(fp,
"    ZZstrList[%d].vObj[1]=(char *)((%s *)(new %s((ZZZiClass *)NULL)));\n  }\n",
                         i,tp,te);
          }
      }
    }

    /* second loop generates the list of initializing sub-macros/functions */
    fprintf(fp,"for(i=0;i<2;i++){\n");
    if(ZZext)for(ext=ZZext->prev; ; ext=ext->prev){
        tp=(&(ext->name[7]));
        if(cPlus)fprintf(fp,
        "  ((%s *)(ZZstrList[%d].vObj[0]))->ZZinitSet();\n",tp,ext->ind);
        else fprintf(fp,"  ZZSS_%s(this);\n",tp);
        if(ext==ZZext)break;
    }
    /* next call will clean master images and leave virt pointers only */
    fprintf(fp,"}\n");
    if(cPlus){
        fprintf(fp,"#ifndef ZZlocal\n");
        fprintf(fp,"ZZsetMask();\n");
        fprintf(fp,"#endif\n");
    }
    fprintf(fp,
      "#ifdef ZZcCalloc\nZZcallocFlg=1;\n#else\nZZcallocFlg=0;\n#endif\n");
    fprintf(fp,"}\n");
    splitLine(fp);

    /* third loop generates simple functions for type searches */
    if(!multiProj){ /* if multiProj, only defines are used */
        if(ansi)ans=(char*)"void"; else ans=(char*)" ";
        for(ext=ZZext, i=k=0; ext; ext=ext->next, i++){
            tp=(&(ext->name[7]));
            fprintf(fp,"ZZ_LOCAL int ZZZI%s(%s){return(%d);}\n",tp,ans,i);
            kk= -1;
	    ptr=ext->ptr;
	    if(ptr && !strcmp(ptr->bName,SELFID_PTR_NAME)){
                kk=k;
                k++;
            }
            fprintf(fp,"ZZ_LOCAL int ZZZJ%s(%s){return(%d);}\n",tp,ans,kk);
        }
    }
    splitLine(fp);

    /* generate function ZZvSet() */
    if(ansi)fprintf(fp,"ZZ_LOCAL void ZZvSet(ZZint tp){\n");
    else    fprintf(fp,"ZZ_LOCAL void ZZvSet(tp) ZZint tp; {\n");
    if(cPlus){  
        fprintf(fp,"  int i; i=ZZmemSwitch; ZZmemSwitch=0;\n");
        fprintf(fp,"  switch(tp){\n");
        for(ext=ZZext, i=0; ext; ext=ext->next, i++){
            tp=(&(ext->name[7]));
            if(!((ext->vcPres)&ABSTR_CLASS))fprintf(fp,
            "    case %d: (void)new %s((ZZZiClass *)NULL); break;\n", i,tp);
        }
        fprintf(fp,"    default: ZZmsgD(27,tp); ZZerror=ZZerror|040;\n  }\n");
        fprintf(fp,"  ZZmemSwitch=i;\n");
    }
    else fprintf(fp,"tp=tp;");
    fprintf(fp,"}\n");
    splitLine(fp);

    /* generate function ZZtopType() */
    if(ansi)fprintf(fp,"ZZ_LOCAL void *ZZtopType(void *ptr,ZZint tp,ZZint *newTp){\n");
    else fprintf(fp,
          "ZZ_LOCAL void *ZZtopType(ptr,tp,newTp)void *ptr;ZZint tp;ZZint *newTp;{\n");
    if(cPlus){  
        fprintf(fp,"  switch(tp){\n");
        for(ext=ZZext, i=0; ext; ext=ext->next, i++){
            tp=(&(ext->name[7]));
            fprintf(fp,
            "    case %d: ptr=(void *)(((%s *)ptr)->zzThisIs((ZZint*)newTp)); break;\n",
           i,tp);
        }
        fprintf(fp,"    default: ZZmsgD(27,tp); ZZerror=ZZerror|040;\n  }\n");
    }
    else fprintf(fp,"  *newTp=tp;\n");
    fprintf(fp,"  return(ptr);\n");
    fprintf(fp,"}\n");
}
/* -------------------------------------------------------------------- */
/* Generate offsets between inherited classes and member objects
 * for one extention */
#ifdef ZZ_ANSI
void offMacro(FILE *fp,ZZextention *ext)

#else
void offMacro(fp,ext)
FILE *fp; /* default for this file is zzfunc.c file */
ZZextention *ext;
#endif
{
    char *cc;
    struct ZZinhList *ip,*ii;

    /* Set the offset in the inheritance list. Note that for the true
     * inheritance (not member object) the object offset is always 0,
     * therefore the offset here is equal to the offset of the start
     * within the same class.
     * Note that, in ZZ_GENERAL_EXT, 'start' has to be set before
     * 'offset', which implies that the order in which ZZS are listed
     * must be the same as the order of classes on the input */
    if(cPlus)cc=(char*)""; else cc=(char*)"struct ";
    for(ip=ext->iList;ip;ip=ip->next){
         fprintf(fp,"  ZZinhList[%d].offset=",ip->ind);
         if(ip->num==0){
             if((ext->vcPres)&VIRT_BASE_CLASS){ 
  fprintf(fp,"ZZptrToInt((char*)((ZZsigIntType)((%s *)((%s *)ZZp))-ZZi))+",
                     &(ip->ext->name[7]),&(ext->name[7]));
             }
             else {
                 for(ii=ext->iList;ii!=ip;ii=ii->next){
                     fprintf(fp,"(int)sizeof(%s%s)+",
                                 cc,&(ii->ext->name[7]));
                 }
             }
             fprintf(fp,"ZZstrList[%d].start;\\\n",ip->ext->ind);
         }
         else {
             if(ip->num==1)fprintf(fp,
  "ZZptrToInt((char *)((ZZsigIntType)(&(ZZp->%s))-ZZi))",ip->name);
             else fprintf(fp,
  "ZZptrToInt((char *)((ZZsigIntType)(&(ZZp->%s[0]))-ZZi))",ip->name);
             if(ip->ext->ptr)fprintf(fp,
                         "+ZZstrList[%d].start;\\\n",ip->ext->ind);
             else fprintf(fp,";\\\n");
         }
    }
    return;
}
/* -------------------------------------------------------------------- */
/* Generate ZZS and ZZSS ... macros with pointers that start ZZ_EXT */
#ifdef ZZ_ANSI
void sMacro(FILE *fp)

#else
void sMacro(fp)
FILE *fp; /* default for this file is zzincl.h file */
#endif
{
    int i;
    char name[80],*nn;
    ZZextention *ext;
    ZZextPtr *ptr;

    /* the loop generates  ZZS... macros with pointers that start ZZ_EXT */
    for(ext=ZZext, i=0; ext; ext=ext->next, i++){
        nn= &(ext->name[7]);
	ptr=ext->ptr;
        firstName(ptr,name);
        if(ptr || ext->iList){
	  // macro ZZSS_ calculates the offset of ZZ_EXT within the object
          fprintf(fp,"\n#define ZZSS_%s(P) {%s %cZZp; ZZsigIntType ZZi;\\\n",nn,nn,AST);
          if(ext->isClass=='c')fprintf(fp," ZZp=P; ZZp=ZZp;\\\n");
          else fprintf(fp," ZZp=(%s *)NULL; ZZp=ZZp;\\\n",nn);
          fprintf(fp,"ZZi=(ZZsigIntType)ZZp;\\\n");

          if(ptr){
              fprintf(fp,
    "ZZstrList[%d].start=ZZptrToInt((char *)((ZZsigIntType)(&(ZZp->%s))-ZZi));\\\n",
              i,name);
          }
          else fprintf(fp," ZZi=ZZi; ZZstrList[%d].start=0;\\\n",i);
        }
        else {
            fprintf(fp,"#define ZZSS_%s(P) {\\\n",nn);
            fprintf(fp," ZZstrList[%d].start=0;\\\n",i);
        }

        offMacro(fp,ext); /* generate lines for all offset calculation */
        fprintf(fp,
            " ZZstrList[%d].size=(int)sizeof(%s);}\n",i,nn);

          fprintf(fp,"\n#define ZZS_%s ZZSS_%s(this)\n",nn,nn);
    }
    return;
}
/* ---------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void firstName(ZZextPtr *ptr,char *name)

#else
void firstName(ptr,name)
ZZextPtr *ptr; /* pointer to the first pointer in the extention */
char *name;    /* already allocated buffer for the result */
#endif
{
    ZZptrCode *pc;

    if(ptr==NULL)name[0]='\0';
    else if(!strcmp(TIME_STAMP_NAME,ptr->bName)){
       strcpy(name,ptr->bName);
       strcat(name,"[0]");
    }
    else if(!strcmp(ptr->bName,PROPERTY_PTR_NAME))strcpy(name,ptr->bName);
    else if(ptr->ptrCode==NULL)strcpy(name,ptr->bName);
    else {
        pc=ptr->ptrCode;
        strcpy(name,pc->pName);
        if(pc->masterP->aSize>1)strcat(name,"[0]");
    }
}
/* ---------------------------------------------------------------------- */
/* convert one character code for ZZpointer.aType into the full name */
#ifdef ZZ_ANSI
const char *pTypeConv(const char c)

#else
char *pTypeConv(c)
char c;
#endif
{
    switch(c){
        case 'i': return("int ");
        case 'f': return("float ");
        case 'c': return("char ");
        case 's': return("char *");
        default: ZZmsgC(0,&c); /* wrong pointer type */
    }
    return("");
}
/* ---------------------------------------------------------------------- */
/* cross-check that all ZZ_EXT_... from the user code are actually expanded,
 * and also that for every ZZ_EXT_... in the new zzincl.h, there is one
 * in the user's code. The program reacts differently to the two cases:
 * Warning: if an Extention is in the user's code but not in zzincl.h;
 * Error:  if an Extention exists in zzincl.h but not in the user's code.
 *  In case of the warning, generate a comment instead of ZZ_EXT_...
 * so that the compiler does not have a problem.
 */
#ifdef ZZ_ANSI
int crossExt(char *parse,FILE *outFile)

#else
int crossExt(parse,outFile)
char *parse;       /* partially parsed user program */
FILE *outFile; /* typically ZZiclude.h */
/* returns number of errors (warnings not included in the count) */
#endif
{
    int err;
    char *p;
    ZZextention *ext;

    err=0;
    for(ext=ZZext;ext;ext=ext->next)ext->inCode=BLANK;

for(p=parse; parseRead(p); p=parse){
    for(;*p!=END;){
	if(strlen(p)>6){
	    if(!strncmp("ZZ_EXT_",p,7)){
                for(ext=ZZext;ext;ext=ext->next){
		    if(!strcmp(p,ext->name)){
			ext->inCode=AST;
			break;
		    }
		}
		if(!ext){
                    ZZmsgS(4,p); /* warning: %s in your code but not expanded */
                    fprintf(outFile,"#define %s /* %s not needed */\n",p,p);
		}
	    }
	}
	NEXT_WORD(p);
    }
}parseClose(0);

    for(ext=ZZext;ext;ext=ext->next){
	if(ext->inCode==BLANK && ext->style=='r'){
	    err++;
            ZZmsgS(5,ext->name); /* %s needed but does not exist in your code */
	}
    }
    return(err);
}
/* ---------------------------------------------------------------------- */
/* Detect links between the user's code and the predefined macro operations.
 * Detect organizations, create Extentions, and check Functions.
 */
#ifdef ZZ_ANSI
void detectLinks(ZZuml *uml,FILE *umlFile,char *parse)

#else
void detectLinks(uml,umlFile,parse)
ZZuml *uml;  /* linked list of ZZuml objects as in file macro/registry */
FILE *umlFile; /* file to deposit the UML logic, if NULL no UML created */
char *parse; /* partially parsed code, end marked by two END characters */
#endif
{
    int i,k,nList,nPar,size;
    char create,*p,*r,*next,*third,*last,**str,*id,*lineN;
    ZZfunction *fp;
    ZZorgInst *oi;
    struct FunList {
        char *name; /* sometimes short, sometimes long name */
        ZZfunction *fun;
    } *fList,*ff;
    static const char *skipIt[]={"ZZmain","ZZlocal","ZZ_DEB_PRT","ZZ_SIMPLE","ZZcalloc",
    "ZZascii","ZZ_ANSI","ZZansi","ZZvSet","ZZcallBack","ZZ_TYPE_NAME","ZZfunc.c",
    "ZZhashInd","ZZhashStr","ZZhashSStr","ZZhashInt","ZZcplus","ZZcplus21",
    "ZZinclude.h","ZZorgcVersion","ZZgetType","ZZint","ZZlong","ZZfloat","end"};
    char **sk;

    /* make a list with entries of both short/long names */
    fList=(struct FunList *)malloc(2*nFun*(int)sizeof(struct FunList));
    if(!fList){ZZmsgS(1,"detectLinks()"); return;} /* failure to allocate */
    for(i=0, fp=ZZfun; i<nFun; i++){     /* populate in the list */
        k=i+i;
        fList[k].name=fp[i].name;
        fList[k+1].name=fp[i].sName;
        fList[k].fun=fList[k+1].fun= &(ZZfun[i]);
    }
    nList=nFun+nFun;

    ZZoffset=ZZpOffset((char *)(&(fList->name)),(char *)fList);
    qsort(fList,nList,(int)sizeof(struct FunList),genSortFun);
    (void)setBuckets((char *)fList,nList,(int)sizeof(struct FunList),ZZoffset);

  for(p=parse; parseRead(p); p=parse){
    last=(char*)"";
    size=(int)sizeof(struct FunList);
    for(next=p+1; (*p)!=END; p=r, next=r+1){
	r=p;
        third=next+1;
        if(!strncmp(p,"ZZ=",3)){ /* header for the line number */
            lineN= &(p[3]);
            NEXT_WORD(r);
        }
        /* avoid search if not ZZ.., but skip ZZC... */
	else if((*p)=='Z' && (*next)=='Z' && (*third)!='C'){
            if(!strncmp("ZZ_HYPER_",p,9)){
                if(uml && umlFile){
                    umlPrt(umlFile,uml,p+9);
                }                   
            }
	    ff=(struct FunList *)binCmp((char *)fList,size,ZZoffset,nList,p);
            if(ff){
                fp=ff->fun;
                whichName(fp,p);

                if(!aOrder(r,(char*)"ZZ_BLOCK_ALLOC") ||
                   !aOrder(r,(char*)"ZZ_ORG_SELF_ID") ||
                   !aOrder(r,(char*)"ZZ_ORG_TIME_STAMP"))simpleAlloc=0;

                /* if plain macro, no extention */
                create=fp->create;
		if(fp->orgInd<0 && create!='g' && create!='G' && create!='L'&&
                create!='h' && create!='H' && create!='F')goto END_RECORD; 

                NEXT_WORD(r);
	        if(aOrder(r,(char*)"(")){
		    ZZerror++;
		    PRINT_WORDS(p,7);
                    ZZmsgS(6,lineN); /* macro syntax error */
		    return;
	        }
	        NEXT_WORD(r);
                id=r;

                if((create=='h' || create=='H' || create=='L') 
                         && fp->orgInd<0){ /* HYPER_UTILITIES */
                    selectFunctions=1;
                    addFunInst(fp,id,lineN);
                    goto END_RECORD;
                }

                if(create=='g'){ /* generic macro */
                    if(!implicit)genRec(fp,id);
                    goto END_RECORD;
                }
                else if(create=='G'){ /* generic compiled function */
                    if(!implicit)genRec(fp,id);
                    /* find what this generic means */
                    for(oi=ZZinst;oi;oi=oi->next)if(!strcmp(oi->ident,id))break;
                    if(!oi){
                        ZZmsgSS(0,lineN,id); /* strange id */
                        goto END_RECORD;
                    }
                    strcpy(buff,fp->name); strcat(buff,"_");
                    strcat(buff,ZZorg[oi->orgInd].name);
	            ff=(struct FunList *)binCmp((char *)fList,size,ZZoffset,
                                                                  nList,buff);
                    if(ff){
                        fp=ff->fun;
                        create=fp->create;
                        if(create=='f' || create=='h' || create=='H' || 
                                                         create=='L'){
                            whichName(fp,buff);
                            selectFunctions=1;
                            addFunInst(fp,id,lineN);
                        }
                    }
                    else ZZmsgSSS(0,lineN,fp->name,buff);
                                           /* generic expanded not found */
                    goto END_RECORD;
                }
                else if(create=='F'){newFormat(r,lineN); goto END_RECORD;}
                else if(create=='f'){ /* for ZZ_HYPER must be done later */
                    selectFunctions=1;
                    addFunInst(fp,id,lineN);/* function,keep list of instances*/
                }
                /* make sure id matches with the function definition */
                for(oi=ZZinst;oi;oi=oi->next)if(!strcmp(oi->ident,id))break;
                if(oi && oi->orgInd!=fp->orgInd)ZZmsgSSS(1,lineN,p,id);
                                     /* function and organization donot match */

		nPar=ZZorg[fp->orgInd].nInp+1; /* allow one more for ZZ_LOCAL */
		if(nPar<=0)goto END_RECORD;

	        /* analyze next (nPar-1) words */
		str=(char * *)malloc((1+nPar)*(int)sizeof(char *));
		if(!str){
                    ZZmsgD(1,nPar); /* internal allocation error */
		    continue;
		}
		str[0]=(char*)"char*";
		for(k=1;k<nPar;k++){
	            NEXT_WORD(r);
	            if(aOrder(r,(char*)",")){
                        /* allow less parameters, but not for ZZ_ORG */
                        if(create!='o' && create!='h' && create!='H' &&
                           create!='L' && (!aOrder(r,(char*)")")) || k==(nPar-1))break;
		        ZZerror++;
		        PRINT_WORDS(p,7);
                        ZZmsgS(6,lineN); /* macro syntax error */
		        return;
	            }
	            NEXT_WORD(r);
                    if(!strncmp("ZZ=",r,3))NEXT_WORD(r);
		    str[k]=r;
		}
                nPar=k; /* allow reduced number of parameters */

		ZZorg[fp->orgInd].used=USED;
		if(create=='o' || create=='h' || create=='H' || create=='L'){
                    for(oi=ZZinst;oi;oi=oi->next)if(!strcmp(oi->ident,id))break;
                    if(oi)ZZmsgSS(1,lineN,id); /* multiply declared */
                    else {
                        if(nPar==1){ /* special functions (selfID,property) */
                            str[1]=id;
                            if(makeExt(fp,(char*)"",str,2,1))return;   /*return=error*/
                        }
                        else {
                            if(makeExt(fp,id,str,nPar,0))return;/*return=error*/
                        }
                    }
                }
	        else  checkFun(fp,id,lineN);

                if(create=='h' || create=='H' || create=='L'){ /* ZZ_HYPER */
                    selectFunctions=1;
                    addFunInst(fp,id,lineN);/* add to the list just as 'f' */
                }
                free(str);

END_RECORD:     NEXT_WORD(r);
	    }
	    else {
             
                if(!strcmp("ZZascii",p) && !strcmp(last,DEFDEC))ascii=1;
                else if(!strcmp("ZZansi",p) && !strcmp(last,DEFDEC))ansi=1;
                else if(!strcmp("ZZ_NOLEAK",p))noLeak=1;
                else if(!strcmp("ZZsaveSpecial",p))saveSpecial=1;
                else if(!strcmp("ZZnoCheck",p))noCheck=1;
                else if(!strcmp("ZZnoDestr",p))noDestr=1;
                else if(!strncmp("ZZerror",p,7)){}
                else if(!strcmp("ZZbreakLine",p)){}
                else if(!strcmp("ZZinstallUserIO",p)){}
                else if(!strcmp("ZZcplus",p) && !strcmp(last,DEFDEC))
                          {if(cPlus<1)cPlus=1;ansi=1;simpleAlloc=0;}
                else if(!strcmp("ZZcplus21",p) && !strcmp(last,DEFDEC))
                          {cPlus=2;ansi=1;simpleAlloc=0;}
                else if(!strcmp("ZZnoFriends",p) && !strcmp(last,DEFDEC))
                                                                     friends=0;
                else if(!strcmp(ALL_SELF,p)){allSelfUsed=1; simpleAlloc=0;}
		else if(!strncmp("ZZ_EXT_",p,7))getExtention(1,&(p[7]),0);
                else if(!strcmp(ZZ_IMPLICIT,p) && !strcmp(last,DEFDEC))
                                             {implicit=1; simpleAlloc=0;}
                else if(!strcmp(ZZ_SELECT_MACROS,p)){selectMacros=1;}
                else if(!strcmp("ZZ_INHERIT",p) && !strcmp(last,DEFDEC))
                                                                     inherit=1;
                else if(!strcmp("ZZinheritAll",p) && !strcmp(last,DEFDEC))
                                            {inherit=1; inheritAll=1;}
                else if(!strcmp("ZZmultiProj",p) && !strcmp(last,DEFDEC))
                                                                    multiProj=1;
                else {
                    for(sk=(char**)skipIt;strcmp(*sk,"end");sk++){
                        if(!strcmp(*sk,p))break;
                    }
		    if(!strcmp(*sk,"end"))ZZmsgSS(2,lineN,p);
                                               /* illegal ZZ reference */
                }
		NEXT_WORD(r);
	    }
	}
        else {
            last=r;
            NEXT_WORD(r);
        }
    }
  }
  parseClose(0);
  free(fList);
  return;
}
/* ---------------------------------------------------------------------- */
/* Walk through the input, and detect single/multiple class inheritance,
 * and structures injected into other structures (member objects).
 * Also look for keyword 'virtual' inside the class declaration.
 */
#ifdef ZZ_ANSI
void detInherit(char *parse)

#else
void detInherit(parse)
char *parse; /* starting character of the input stream */
#endif
{
    char *p,*r,*lineN;

for(p=parse; parseRead(p); p=parse){
    for(; (*p)!=END; p=r){
	r=p;
        if(!strncmp(r,"ZZ=",3)){ /* header for the line number */
            lineN=r+3;
            NEXT_WORD(r); if(*r==END)break;
            /* skip unimportant tokens */
            if(!aOrder(r,(char*)"private") || !aOrder(r,(char*)"public"))NEXT_WORD(r);
       
            /* try to detect a class */
            if(!aOrder(r,(char*)"class") || !aOrder(r,(char*)"struct"))
                            r=classOrStruct(r,lineN);
        }
        else NEXT_WORD(r);
    }
}parseClose(0);
    return;
}
/* ---------------------------------------------------------------------- */
/* process class or struct declaration */
#ifdef ZZ_ANSI
char *classOrStruct(char *r,char *lineN)

#else
char *classOrStruct(r,lineN)
char *r,*lineN;
#endif
{
    char *cp;
    
    if(!aOrder(r,(char*)"class")){
        NEXT_WORD(r);
        if(*r==END)return(r);
        cp=r;
        NEXT_WORD(r);
        if(!strncmp(r,"ZZ=",3))NEXT_WORD(r);
        if(*r==':'){
            NEXT_WORD(r);
            if(*r!=':'){
                r=newInherit(cp,r,lineN);
                r=testInject(cp,r,1);
            }
        }
        else if(*r=='{')r=testInject(cp,r,1);
    }
    else if(!aOrder(r,(char*)"struct")){
        NEXT_WORD(r); if(*r==END)return(r);
        cp=r;
        NEXT_WORD(r); if(*r==END)return(r);
        if(*r=='{')r=testInject(cp,r,0);
    }
    return(r);
}
/* ---------------------------------------------------------------------- */
/* internal record of a new io format for one ZZ_EXT */
#ifdef ZZ_ANSI
void newFormat(char *pp,char *lineN)

#else
void newFormat(pp,lineN)
char *pp;   /* points into the first argument of the command */
char *lineN; /* line where the FORMAT statement occurs */
#endif
{
    ZZextention *ext;
    char *r,*p;
    struct ZZnameList *np,*tail;
    int i;

    /* find the corresponding extention */
    ext=findExt(pp);
    if(ext){
        if(ext->format)ZZmsgS(30,lineN);
        r=pp;
        uFormat=1; /* global flag that ZZ_FORMAT is used somewhere */
        NEXT_WORD(r); /* next must '\"' */
        p=r;
        NEXT_WORD(r);
	if(*p!=',' || *r!='\"'){
            ZZerror++;
            ZZmsgS(6,lineN); /* macro syntax error */
            return;;
        }

        NEXT_WORD(r); /* format recorded as several words, ending ',' or '\"' */
        strcpy(buff,""); /* will collect the format itself */
        for(i=0;*r!=',' && *r!='\"';){
            for(;i>0;i--)strcat(buff," ");
            if(*(r+1)=='a')i=2; else i=1; /* provide space for %a format */
            strcat(buff,r);
            NEXT_WORD(r);
        }
        for(;i>1;i--)strcat(buff," ");
        ext->format=(char *)malloc(strlen(buff)+1);
        if(!(ext->format)){ZZmsgS(1,"newFormat"); return;}
        strcpy(ext->format,buff);
        if(*r=='\"')return;

        NEXT_WORD(r);
        for(tail=ext->fList;;){
            np=(struct ZZnameList *)malloc((int)sizeof(struct ZZnameList));
            if(!np){ZZmsgS(1,"newFormat"); return;}
            if(*r=='('){  /* a specific cast, typically enum */
                NEXT_WORD(r);
                strcpy(buff,""); /* will collect the cast */
                for(i=0; *r!=')'; i=1){
                    if(i)strcat(buff," ");
                    strcat(buff,r);
                    NEXT_WORD(r);
                }
                NEXT_WORD(r);
            }
            else strcpy(buff,"char");

            np->cast=(char *)malloc(strlen(buff)+1);
            if(!(np->cast)){ZZmsgS(1,"newFormat"); return;}
            strcpy(np->cast,buff); 
            np->name=(char *)malloc(strlen(r)+1);
            if(!(np->name)){ZZmsgS(1,"newFormat"); return;}
            strcpy(np->name,r); 
       
            if(tail)tail->next=np;
            else ext->fList=np;
            np->next=NULL;
            tail=np;
            NEXT_WORD(r);
            if(!aOrder(r,(char*)"\""))break;
	    if(aOrder(r,(char*)",")){
		ZZerror++;
                ZZmsgS(6,lineN); /* macro syntax error */
                break;
            }
	    NEXT_WORD(r);
        }
        aFormat(ext);
    }
    else ZZmsgSS(15,lineN,pp); /* error: FORMAT before ZZ_EXT */
}
/* ---------------------------------------------------------------------- */
/* prepare special records if special %a is used.
 * %a is for characters that store small integer values.
 * formatCode stores values 1, 2, ... for members that are declared as
 * char, but actually store a small integer.
 */
#ifdef ZZ_ANSI
void aFormat(ZZextention *ext)

#else
void aFormat(ext)
ZZextention *ext;
#endif
{
    char *p,*s;
    int i;
    struct ZZnameList *np;

    for(p=ext->format, np=ext->fList, i=0; *p!='\0' && np!=NULL; p++){
        if(*p=='%'){
            s=p+1;
            if(*s=='a'){
                *s='l'; s=p+2; *s='u';
                i++;
                np->formatCode=i;
            }
            else np->formatCode=0;
            np=np->next;
        }
    }
}
/* ---------------------------------------------------------------------- */
/* Test the inside of a class/structure declaration for injected types.
 * When the program gets to this point, r must point to '{', and it must
 * return pointer to the closing '}' on the exit.
 * When this function is called, all extention names are already recorded
 * (this is the second pass). We have to look for these names, and then
 * distinguish between a pointer to object ('*' or '&' is used),
 * injected object (no '*' or '&' used), and functions returning
 * a class by reference ( <name>(..) is used ).
 * At the same time, record the presence of keyword 'virtual' inside
 * the class declaration.
 * Addition Dec.15/92: handle additional members if separated by comma:
 *      myType a,b,c;
 */
#ifdef ZZ_ANSI
char *testInject(char *id,char *r,int isc)

#else
char *testInject(id,r,isc)
char *id; /* name of the object type with inheritance */
char *r;   /* points into the first '{' */ 
int isc; /* 1=is a class, 0=is a structure */
#endif
{
    ZZextention *ep,*ext;
    char *rr,*p,*q,*s,*ss,*lineN;
    struct ZZinhList *np;
    int i,num,dFlag;
    static char *d={(char*)"0123456789"};

    lineN=(char*)"0";
    NEXT_WORD(r);
    ext=findExt(id);
    if(ext){
        if(isc)ext->isClass='c'; else ext->isClass='s';
        while((*r!=END || *(r+1)!=END) && *r!='}'){
            if(*r=='~'){NEXT_WORD(r); dFlag=1;} else dFlag=0;
            if(!strncmp(r,"ZZ=",3))lineN=r+3;
            if(!strcmp("class",r)){r=classOrStruct(r,lineN); continue;}
            if(!strcmp("virtual",r))ext->virt='v';
            /* do not look inside sections () or {} */
            if(*r=='('){ 
                r=searchChar(r+1,')'); NEXT_WORD(r);
                if(*r=='='){rr=r; NEXT_WORD(rr);
                    if(*rr=='0')ext->vcPres=(ext->vcPres)|ABSTR_CLASS;
                }
                continue;
            }
            if(*r=='{'){r=searchChar(r+1,'}'); NEXT_WORD(r); continue;}
            ep=findExt(r);
            if(!ep){
                NEXT_WORD(r);
                continue;
            }
            else {
                /* skip pointer, friend, constructor, scope, reference */
                NEXT_WORD(r);
                while(*r!=';'){  /* several members for the same type */
                    if(*r=='}')NEXT_WORD(r);
                    if(*r==',')NEXT_WORD(r);
                    q=r;
                    NEXT_WORD(q);
                    if(!strcmp("*",r))NEXT_WORD(q);
                    if(ep==ext && *r=='('){
                        if(dFlag)ext->hasDestr='y';
                        else     ext->hasConstr='y';
                    }
                    if(*r=='&'||*r==';'||*r=='('||*r==':'||*q=='('
                                                     ||!aOrder(r,(char*)"operator")){
                        r=searchEnd(r);
                        if(*r=='}'){NEXT_WORD(r); break;}
                        if(*r==';')break;
                        continue; /* no interest, try the next member */
                    }

                    if(*r=='*'){
                        while(*r!=',' && *r!=';'){NEXT_WORD(r);}
                        continue;
                    }
                    /* is there '[' inside this word? */
                    for(p=r;*p!='[' && *p!=END;p++)continue;
                    if(*p=='['){ /* it is an array, decode count */
                        for(p++,num=0;*p!=']';p++){
                            for(i=0;i<10;i++){
                                if(*p==d[i]){
                                    num=10*num+i;
                                    break;
                                }
                            }
                        }
                    }
                    else num=1;
                        
                    np=(struct ZZinhList *)malloc((int)sizeof(struct ZZinhList));
                    if(!np){
                        ZZmsgS(1,"testInject()");
                        r=searchChar(r,'}');
                        break;
                    }
                    np->next=ext->iList;
                    ext->iList=np;
                    np->ext=ep;
                    np->num=num;
                    np->name=(char *)malloc((int)strlen(r)+1);
                    if(!(np->name)){ZZmsgS(1,"testInject()"); return(r);}
                    for(s=r, ss=np->name; *s!='[' && *s!=END; s++, ss++)*ss= *s;
                    *ss=END;
                    NEXT_WORD(r); 
                }
            }
        }                                 /* end of while-loop */
    }
    else {
        /* shift pointer to the very end of the declaration */
        r=searchChar(r,'}');
    }                                     /* end of if(ext) */
    return(r);
}
/* ---------------------------------------------------------------------- */
/* find the extention by the name of the structure, return NULL if not found */
#ifdef ZZ_ANSI
ZZextention *findExt(char *id)

#else
ZZextention *findExt(id)
char *id; /* class or structure name */
#endif
{
    ZZextention *ext;
    for(ext=ZZext; ext; ext=ext->next){
        if(!strcmp(&((ext->name)[7]),id))break;
    }
    return(ext);
}
/* ---------------------------------------------------------------------- */
/* find the extention by the name of ZZ_EXT_..., return NULL if not found */
#ifdef ZZ_ANSI
ZZextention *whichExt(char *id)

#else
ZZextention *whichExt(id)
char *id; /* class or structure name */
#endif
{
    ZZextention *ext;
    for(ext=ZZext; ext; ext=ext->next){
        if(!strcmp(ext->name,id))break;
    }
    return(ext);
}
/* ---------------------------------------------------------------------- */
/* find the extention by name, return its order index, -1 if not found */
#ifdef ZZ_ANSI
int extInd(char *id)

#else
int extInd(id)
char *id; /* class or structure name */
#endif
{
    ZZextention *ext;
    int i;

    for(ext=ZZext,i=0; ext; ext=ext->next,i++){
        if(!strcmp(&((ext->name)[7]),id))break;
    }
    if(!ext)i= -1;
    return(i);
}
/* ---------------------------------------------------------------------- */
/* Add a new inheritance record:
 * record all classes from which id is derived (skip tokens 'public' and
 * 'private'), and return pointer to '{, which opens the class declaration .
 * If any of the classes are not OrgC registered - they do not have ZZ_EXT -
 * simply skip them.
 */
#ifdef ZZ_ANSI
char *newInherit(char *id,char *r,char *lineN)

#else
char *newInherit(id,r,lineN)
char *id; /* name of the object type with inheritance */
char *r;   /* points into the first inherited argument, possibly 'public' */ 
char *lineN; /* line of the class declaration */
#endif
{
    ZZextention *ep,*ext;
    struct ZZinhList *np;
    int virtFlg;

    ext=findExt(id);
    if(ext){
        while(*r!=END || *(r+1)!=END){
            if(!strncmp(r,"ZZ=",3))NEXT_WORD(r);
            if(!aOrder(r,(char*)"virtual")) {virtFlg=1; NEXT_WORD(r);}
            else virtFlg=0;
            if(!aOrder(r,(char*)"public") || !aOrder(r,(char*)"private") ||
                                      !strncmp(r,"ZZ=",3)) NEXT_WORD(r);
            ep=findExt(r);
            if(ep){
                np=(struct ZZinhList *)malloc((int)sizeof(struct ZZinhList));
                if(!np){
                    ZZmsgS(1,"newInherit()");
                    r=searchChar(r,'{');
                    break;
                }
                np->next=ext->iList;
                ext->iList=np;
                np->ext=ep;
                np->num=0; /* 0 marks an inherited type */
                if(virtFlg){
                    np->name=(char*)"ZZvirtual";
                    vClassPresent=1;
                }
                else       np->name=(char*)"ZZinherit";
            }
            NEXT_WORD(r);
            if(!strncmp(r,"ZZ=",3))NEXT_WORD(r);
            if(*r=='{')break;
            if(*r!=','){
                ZZmsgSS(16,lineN,id);
                r=searchChar(r,'{');
                break;
            }
            NEXT_WORD(r); 
            if(!strncmp(r,"ZZ=",3))NEXT_WORD(r);
        }
    }
    else {
        /* shift pointer to the opening '{' */
        r=searchChar(r,'{');
    }
    return(r);
}
/* ---------------------------------------------------------------------- */
/* search for a given character at the same level of () or {} nesting */
#ifdef ZZ_ANSI
char *searchChar(char *p,char c)

#else
char *searchChar(p,c)
char *p; /* the character to start the search */
char c;  /* character to look for */
#endif
{
    char *s;
    int n1,n2;

    n1= n2=0;
    for(s=p+1;*p!=END || *s!=END;p++, s++){
        if(n1==0 && n2==0 && *p==c)break;
        if(*p=='(')n1++;
        else if(*p==')')n1--;
        else if(*p=='{')n2++;
        else if(*p=='}')n2--;
    }
    return(p);
}
/* ---------------------------------------------------------------------- */
/* search for ';' or ',' or '}' at the same level of nesting */
#ifdef ZZ_ANSI
char *searchEnd(char *p)
#else
char *searchEnd(p)
char *p; /* character to start the search,may be '(' or '{' */
#endif
{
    char *s,*r;
    int n1,n2;

    n1=n2=0;
    r=p; /* remember the original string */
    for(s=p+1;*p!=END || *s!=END;p++, s++){
        if(n1==0 && 
           ((n2==0 && (*p== ';' || *p==','))||(n2==1 && *p=='}')))break;
        if(*p=='(')n1++;
        else if(*p==')')n1--;
        else if(*p=='{')n2++;
        else if(*p=='}')n2--;
    }
    if(*s==END && *p==END){
        *(r-1)=(*r); *r='\0';
        for(r--; *r!='\0'; r--)continue;
        r++; ZZmsgS(50,r);
        exit(1);
    }
    return(p);
}
/* ---------------------------------------------------------------------- */
/* mark function as 'used'for long or short names */
#ifdef ZZ_ANSI
void whichName(ZZfunction *fp,char *p)

#else
void whichName(fp,p)
ZZfunction *fp; 
char *p; /* pointer to the name */
#endif
{
    if(fp->used==BOTH_NAMES){} /* nothing more can be marked */
    else if(p[2]=='_'){
        if(fp->used==SHORT_NAME) fp->used=BOTH_NAMES;
        else fp->used=LONG_NAME;
    }
    else { 
        if(fp->used==LONG_NAME)fp->used=BOTH_NAMES;
        else fp->used=SHORT_NAME;
    }
}
/* ---------------------------------------------------------------------- */
/* add function instance to the list */
#ifdef ZZ_ANSI
void addFunInst(ZZfunction *fp,char *id,char *lineN)

#else
void addFunInst(fp,id,lineN)
ZZfunction *fp; /* function pointer */
char *id;       /* ID as for orgInst */
char *lineN;    /* line number */
#endif
{
    ZZfunInst *fi;
    ZZorgInst *ip;
    char *nn;
    ZZextention *ext;
    
    for(fi=fp->inst;fi;fi=fi->next){
        if(fi->orgInst && !strcmp(id,fi->orgInst->ident))return;
        if(fi->ext && !strcmp(id,&((fi->ext->name)[7])))return;
    }
    /* getting here means this instance not used yet */
    fi=(ZZfunInst*)malloc((int)sizeof(struct ZZfunInst));
    if(!fi){
        ZZmsgS(1,"function instance"); /* problem to allocate */
        return;
    }
    /* find instances, but for special organizations find extensions */
    if(fp->orgInd>=0)nn=ZZorg[fp->orgInd].name; else nn=(char*)" ";
    if(!strcmp(nn,"TIME_STAMP")||!strcmp(nn,"SELF_ID")||!strcmp(nn,"PROPERTY")){
        for(ext=ZZext;ext;ext=ext->next){ /* for special cases, find extension*/
            if(!strcmp(id,&(ext->name[7]))){
                fi->orgInst=NULL;
                fi->ext=ext;
                fi->next=fp->inst;
                fp->inst=fi;
                fi->nxt=ext->fun;
                ext->fun=fi;
                fi->parent=fp;
                return;
            }
               
        }
    }
    else {
        for(ip=ZZinst;ip;ip=ip->next){ /* for normal cases, find instance */
            if(!strcmp(id,ip->ident)){
                fi->orgInst=ip;
                fi->ext=NULL;
                fi->next=fp->inst;
                fp->inst=fi;
                fi->nxt=NULL;
                fi->parent=fp;
                return;
            }
        }
    }

    if((fp->create=='h' || fp->create=='H' || fp->create=='L')
                                      && fp->orgInd<0){ /*HYPER_UTILITIES*/
        /* create dummy organization for the utilities */
        ip=(struct ZZorgInst *)malloc((int)sizeof(struct ZZorgInst));
        ip->ident=(char *)malloc(strlen(id)+1);
        strcpy(ip->ident,id);
        ip->orgInd= -1;
        ip->sType=ip->lType=NULL;
        ip->next=NULL;

        fi->orgInst=ip;
        fi->next=fp->inst;
        fp->inst=fi;
        return;
    }
    ZZmsgSS(3,lineN,id); /* wrong id on this line */
    return;
}
/* ---------------------------------------------------------------------- */
/* Partial parsing, only as much as needed for ZZprep:
 * blanks are removed, continuation of line extended, and the following
 * special characters are presented as separate words: (){},;:"
 *  Because all this must work also for file 'stdin', we cannot rewind
 * the inpFile. All input data is copied onto file zztemp,
 * which is then used as the second input.
 *
 * Input: Reads a user C-program,
 * Output: In-core string where all words are separated by END='\0',
 *         it ends by two END characters.
 */
#ifdef ZZ_ANSI
char *pParse(FILE *inpFile,FILE *envFile,DirObj *accDir)

#else
char *pParse(inpFile,envFile,accDir)
FILE *inpFile,*envFile;
DirObj *accDir;
/* returns the beginning of a newly allocated, partially parsed string */
#endif
{
    int i,mark,skip,nBlank,lineNum,lastBreak;
    unsigned int k,n,nLast;
    FILE *tFile,*fp;
    char *c,*p,*s,last;  /* s is the output string */
    char *del={(char*)"(){},;:=~\""};

    tFile=myopen((char*)"zztemp","w");
    if(!tFile){
        ZZmsgS(0,"zztemp"); /* problem to open file zztemp */
	return(NULL);
    }

    /* n=conservative estimate number of characters needed for the output
     * also preprocess the input into file tFile. */

    skip=lineNum=lastBreak=0;
    for(n=nLast=0,fp=envFile; fp; ){
      for(;fgets(buff,BUFSIZE,fp); nLast=n){
        if(!strncmp("ZZbreakLine",buff,10)){
            k=lineChar(lineNum);
            if(lastBreak>0)k=k-lineChar(lastBreak);
            n=k+n+3;
            if(nLast>n){ZZmsg(64); return(NULL);}
            ZZmsgD(29,(int)n);
            if(breakLine<n)breakLine=n;
            lastBreak=lineNum;
            n=nLast=0;
            lineNum++;
            fprintf(tFile,"ZZbreakLine\n");
            continue;  /* don't print line number on the breakLine */
        }
        if(fp==inpFile){
            lineNum++;
            if(accDir){ /* POTENTIAL: here check for include files */
            }
        }
	if(buff[0]!=LINE && buff[0]!=CARET){ /* skip empty lines */
	    last=BLANK;
	    i=nBlank=0;
	    for(c=buff;*c!=LINE && *c!=CARET;c++){
	        if(last=='/' && (*c)=='*'){skip=1; i--; nBlank--;}
		if(!skip){
	            if(last=='/' && (*c)=='/'){i--; break;} 
		    if(*c==TAB)*c=BLANK;
	            if(*c!=BLANK){
		        for(mark=0,p=del;*p!=END;p++){
			    if((*p)==(*c)){mark=1; break;}
		        }
		        if(mark)n+=3; else n++;
			nBlank++;
	            }
		    else if(last!=BLANK)n++;
		    buff[i]=(*c);
		    i++;
		}
	        if(last=='*' && (*c)=='/')skip=0;
		last=(*c);
	    }
	    if(i>0 && nBlank>0){
		buff[i]=LINE;
		buff[i+1]=END;
	        n++;
	        fprintf(tFile,"%d %s",lineNum,buff);
	    }
	}
	if(last!=CONT && mark==0)n++; /* normal end of line */
        /* under DOS, the size of input file may overflow n */
        if(nLast>n){ZZmsg(64); return(NULL);}
      }
      if(fp==envFile)fp=inpFile;
      else fp=NULL;
    }
    n++; /* mark end by two END characters */
    if(breakLine){
        k=lineChar(lineNum);
        if(lastBreak>0)k=k-lineChar(lastBreak);
        n=k+n;
        if(nLast>n){ZZmsg(64); return(NULL);}
        ZZmsgD(29,(int)n);
        if(breakLine<n)breakLine=n;
        n=breakLine;
    }
    else {
        n=n+lineChar(lineNum); /* add characters for the line numbers */
    }

    /* tFile has no empty lines, tabs has been replaced by blanks */
    fclose(tFile);
    tFile=myopen((char*)"zztemp","r");

    if(lastBreak)ZZmsgD(28,(int)n);
    s=(char *)malloc(n);     /* allocate space for the largest section */
    if(!s){
        ZZmsgS(1,"parser space"); /* problem to allocate parser space */
	return(NULL);
    }

    /* parse the file: This section used to skip all sections {}
     *  where ZZ was not used. The program goes inside {} now, because
     * it skipped too much in C++, where this information is required
     * for inheritance */
    for(k=0;fgets(buff,BUFSIZE,tFile);){
        if(!strncmp("ZZbreakLine",buff,10)){
            s[k]=s[k+1]=END; k+=2;
            k=shrinkIt(s);
            parseWrite(s,k);
            k=0;
            continue;
        }

        /* header for the line number */
        s[k]='Z'; s[k+1]='Z'; s[k+2]='='; k+=3;
	last=END;
	for(c=buff;*c!=LINE && *c!=CARET;c++){
	    if(*c==BLANK){if(last!=END){s[k]=END; k++; last=END;}}
	    else {
		for(mark=0,p=del;*p!=END;p++){
		    if((*p)==(*c)){mark=1; break;}
		}
		if(mark){
		    if(last!=END){s[k]=END;  k++;}
		    s[k]=(*c); k++;
		    s[k]=END;  k++;
		    last=END;
		}
		else {s[k]=(*c); k++; last= *c;}
	    }
	}
	if(last==CONT){ /* macro-type continuation */
	    for(k--; s[k]!=END && s[k]!=CONT;k--)continue;
	    k++; s[k]=END; k++;
	}
	else if(last!=END){s[k]=END; k++;}
    }
    s[k]=END; k++; /* mark end by two END characters */
    k=shrinkIt(s);
    if(parseFile)parseWrite(s,k);
    fclose(tFile);
    parseClose(1);
    if(k>n)ZZmsgDD(0,k,n); /* internal counting error in parser */
    return(s);
}
/* -------------------------------------------------------------------- */
/* reduce the internal record only to ZZ-macros and a few tokens each.
* For a class/struct declaration, keep it whole */

#ifdef ZZ_ANSI
unsigned int shrinkIt(char *s){

#else 
unsigned int shrinkIt(s)
char *s; /* given buffer text to be reduced in size */
{
#endif

    unsigned int k,kk,n,numTokens;
    int nd;
    char *c,*r,*p;

    /* count number of tokens at maximum needed for any macro */
    numTokens=0;
    for(kk=0;kk<nOrg;kk++)numTokens=MAX(numTokens,(unsigned)(ZZorg[kk].nInp));
    numTokens=(numTokens+1)*2+1;


    for(p=c=s, n=numTokens, nd=1, k=1;(*p)!=END;){
	if((*p)=='Z' && (*(p+1))=='Z'){n=0; nd=1;}
        if(!aOrder(p+3,(char*)"FORMAT"))nd=0; /* stop counting tokens until next ZZ */
        if(!aOrder(p,(char*)"class") || !aOrder(p,(char*)"struct")){
            r=searchChar(p,';');
	    for(;p!=r;p++,c++,k++)(*c)=(*p);
        }
	if(n<numTokens){
	    for(;;p++,c++,k++){(*c)=(*p); if((*p)==END)break;}
	    p++;c++;k++;
	}
	else NEXT_WORD(p);
	n+=nd;
    }
    (*c)=END;
    return(k);
}

/* ---------------------------------------------------------------------- */
/* write next block of data onto file "zzparse". If the file does not
 * exist yet (parseFile==NULL), then open the file.
 * Use binary IO, and two records: first describes the size, the second
 * contains the actual information 
 */
#ifdef ZZ_ANSI
void parseWrite(char *s,unsigned int k){

#else
void parseWrite(s,k)
char *s; /* given buffer of the text */
unsigned int k; /* size of the buffer to be stored */
{
#endif
    if(!parseFile)parseFile=ZZopen("zzparse",(char*)"w"); /* error mesage inside ZZopen */
    if(!parseFile){ZZmsgS(2,"zzparse"); return;}
    ZZwrite(parseFile,(char *)(&k),(unsigned int)sizeof(unsigned int),NULL);
    ZZwrite(parseFile,s,k,NULL);
}
/* ---------------------------------------------------------------------- */
/* read next block of data from file "zzparse", if it exists.
 * That can be found by checking whether 'breakLine!=0'. If it=0,
 * then the file does not exist. The function assumes that the size
 * of the given buffer is sufficient (this can be guaranteed in this
 * case, because the same buffer is used for write/read).
 * The function returns the number of bytes actually filled in, 
 * where 0 means end-of-file or error.
 * Use the static variable 'justOne' controlled by parseRead() and
 * parseClose() so that if the parseFile is not used, parseRead()
 * allows just one pass without changing the buffer.
 * In order to avoid error messages from the system when
 * reading beyond the end of the file, parseClose(1)
 * writes one additional ZERO record which allows a soft
 * detection of the end of information.
 */
#ifdef ZZ_ANSI
unsigned int parseRead(char *s){

#else
unsigned int parseRead(s)
char *s; /* given buffer to read in */
{
#endif
    unsigned int i,k;

    if(!breakLine){
        if(justOne)return(0);
        justOne=1;
        return(1);
    }
    if(!parseFile)parseFile=ZZopen("zzparse",(char*)"r"); /* error mesage inside ZZopen */
    if(!parseFile)return(0); 
    i=ZZread(parseFile,(char *)(&k),sizeof(unsigned int),NULL);
    if(i!=sizeof(unsigned int) || k==0)return(0);
    i=ZZread(parseFile,s,k,NULL);
    if(i!=k){ ZZmsgS(11,"parseRead()"); return(0);}
    return(i);
}
/* ---------------------------------------------------------------------- */
/* Close the parser file if it is open, and mark it as not open by
 * setting parseFile=NULL. If it s not open, do nothing. */
#ifdef ZZ_ANSI
void parseClose(int k){

#else
void parseClose(k)
int k; /* if k=1, print one end-record */
{
#endif

    unsigned int i;
    i=0;
    if(parseFile){
        if(k)ZZwrite(parseFile,(char *)(&i),(unsigned int)sizeof(unsigned int),NULL);
        ZZclose(parseFile);
    }
    parseFile=NULL;
    justOne=0;
}
    
/* ---------------------------------------------------------------------- */
/* provide the upper estimate for the number of characters needed
 * for the line numbers */
#ifdef ZZ_ANSI
int lineChar(int num)

#else
int lineChar(num)
int num; /* highest line number used */
#endif
{
    int k,n;
    
    for(k=0, n=num; n>0; k++, n=n/10)continue;
    /* k is now the maximum number of digits needed */
    return((k+4)*num); /* format:[ZZ=num ] */
}
/* ---------------------------------------------------------------------- */
/* For a given structure name, find the pointer to the extention.
 * If such extention does not exist yet, create it and set it properly.
 * If there is allocation or other problems, return NULL 
 */
#ifdef ZZ_ANSI
ZZextention *getExtention(int create,char *sName,int style)

#else
ZZextention *getExtention(create,sName,style)
int create; /* 0=just search, 1=search/create */
char *sName; /* structure name */
int style; /* 0=regular, 1=through ZZ_HYPER */
#endif
{
    char *extName;
    ZZextention *ext;

    /* find the name of this extention */
    extName=nameExt(sName);
    if(!extName)return(NULL);
    ext=whichExt(extName);
    if(create==0){
        free(extName);
        return(ext);
    }

    if(!ext){
        ext=newExtention(extName);
        if(ext){
            if(style==0)ext->style='r';
            else ext->style='c';
        }
    }
    else free(extName);
    return(ext);
}
/* ---------------------------------------------------------------------- */
/* create a new extention with a given name, and initialize it */
#ifdef ZZ_ANSI
ZZextention *newExtention(char *extName)

#else
ZZextention *newExtention(extName)
char *extName; /* given name, already allocated */
#endif
{
    ZZextention *ext;

    ext=(ZZextention*)malloc((int)sizeof(struct ZZextention));
    if(!ext){
        ZZmsgS(1,"new Extention"); /* problem to allocate new Extention */
        return(NULL);
    }
    ext->next=ZZext;
    if(ZZext){ext->prev=ZZext->prev; ZZext->prev=ext;}
    else ext->prev=ext;
    ZZext=ext;
    ext->ptr=NULL;
    ext->name=extName; /* has already been allocated inside nameExt() */
    ext->format=NULL;
    ext->fList=NULL;
    ext->iList=NULL;
    ext->fun=NULL;
    if(inheritAll){
        ext->virt='v'; /* give virtu.functions to all classes */
    }
    else {
        ext->virt=' '; /* initialize virt.functions as not present */
    }
    ext->vcPres='\0'; /* initialize virt.classes as not present */
    ext->aClass=NULL; /* initialize as not being a virt class */
    ext->isClass='s'; /* initialize as struct, not class */
    ext->hasConstr='n'; /* initialize as not having a constructor */
    ext->hasDestr='n'; /* initialize as not having a destructor */
    ext->style='r';
    return(ext);
}
/* ---------------------------------------------------------------------- */
/* record one instance of the organization as declared by the user,
 * including the data structure types actually used */
#ifdef ZZ_ANSI
int recInst(ZZfunction *fp,char *id,char **strs,int ns)

#else
int recInst(fp,id,strs,ns)
ZZfunction *fp; /* function, leads to the organization */
char *id;       /* id of this organization */
char *strs[];   /* indexed structure names , strs[0]="char*" */
int ns;         /* size of array strs */
/* return: 0=normal, >0 errors */
#endif
{
    int i,j,k;
    char *t;
    ZZorgInst *oi;
    ZZstrType *st;

    oi=(ZZorgInst *)malloc((int)sizeof(struct ZZorgInst));
    if(!oi){
        ZZmsgS(1,id); /* internal allocation problem */
        return(1);
    }
    if(fp->create=='L')oi->partOf=strs[ns-1]; else oi->partOf=NULL;
    oi->next=ZZinst; ZZinst=oi;
    oi->sType=NULL;
    oi->lType=NULL;
    oi->ident=(char*)malloc(strlen(id)+1);
    if(!(oi->ident)){
        ZZmsgS(1,"name in recInst"); /* name allocation problem recInst() */
        return(2);
    }
    strcpy(oi->ident,id);
    j=oi->orgInd=fp->orgInd;
    for(i=1, k=ZZorg[j].ptrInd; i<ns; i++, k++){
        if(strs[i])t=strs[i]; else t=(char*)"char*";
        st=(ZZstrType*)malloc((int)sizeof(struct ZZstrType));
        if(!st){
            ZZmsgS(1,id); /* type allocation problem */
            return(3);
        }
        /* keep the order, this is usually 1 or 2 types anyway */
        st->next=NULL;
        if(oi->lType){oi->lType->next=st; oi->lType=st;}
        else oi->lType=oi->sType=st;
        st->ptrInd=k;
        st->name=(char*)malloc(strlen(t)+1);
        if(!(st->name)){
            ZZmsgS(1,"second name in recInst()"); /* alloc problem for name */
            return(4);
        }
        strcpy(st->name,t);
    }
    return(0);
}
/* ---------------------------------------------------------------------- */
/* If it does not exist yet, make a new Extention. In any case,
 * add or update the appropriate pointers.
 */
#ifdef ZZ_ANSI
int makeExt(ZZfunction *fp,char *id,char **strs,int ns,int noMix)

#else
int makeExt(fp,id,strs,ns,noMix)
ZZfunction *fp; /* function, leads to the organization */
char *id;       /* id of this organization */
char *strs[];   /* indexed structure names ,strs[0]="char*" */
int ns;         /* size of array strs */
int noMix;      /* =1 if no mix code is to be stored (selfID or property) */
/* returns: 0=normal, >0 error */
#endif
{
    char *pn,*ptrName,*pointTo,*mix;
    char **newStrs,*newId;
    int n,k1,k2,k,i,j1,j2,newNs;
    ZZorganization *org;
    ZZextention *ext;
    ZZextPtr *z;
    ZZptrCode *pc;

    /* recursively, treat the whole hierarchy of organizations */
    for(i=0;i<nHier;i++)if(fp==ZZhier[i].parent){
        k=strlen(id)+strlen(ZZhier[i].prefix)+1;
        newId=(char*)malloc(k);
        newStrs=(char**)malloc(ns*(int)sizeof(char*));
        if(!newId || !newStrs){
           ZZmsgS(1,"hierarchy of organizations"); /* allocation problem */
           return(1);
        }
        strcpy(newId,ZZhier[i].prefix);
        strcat(newId,id);
        newStrs[0]=strs[0];
        for(pn=ZZhier[i].sequence, n=newNs=1; *pn!='\0' && n<ns; pn++, n++){
            if(*pn=='1'){newStrs[newNs]=strs[n]; newNs++;}
        }
        makeExt(ZZhier[i].child,newId,newStrs,newNs,noMix);
        free(newStrs);
        free(newId);
    }

    /* find index access from the Organization to its pointers */
    org= &(ZZorg[fp->orgInd]);
    k1=org->ptrInd; /* starting index */
    k2=org->top;       /* upper limit of the pointer index */

    for(k=k1;k<=k2;k++){ /* go through all pointers of this Organization */
	j1=ZZptr[k].strToUse;
	j2=ZZptr[k].strToPoint;
	if(j1<1||j1>=ns||j2<0||j2>ns){
	    ZZerror++;
            ZZmsgSDDD(0,ZZptr[k].code,j1,j2,ns); /* internal index problem */
	    continue;
	}
	ext=getExtention(1,strs[j1],0);
	if(!ext){
	    ZZerror++;
            ZZmsgSS(4,ZZptr[k].code,strs[j1]); /* problem to set pointer */
	    continue;
	}

	n=strlen(ZZptr[k].code)+1;
	ptrName=(char *)malloc(n);
	if(!ptrName){
            ZZmsgS(1,"pointer name"); /* problem to allocate pointer name */
            return(2);
        }
	strcpy(ptrName,ZZptr[k].code);

        if(ZZptr[k].aType=='a' || ZZptr[k].aType=='g' || ZZptr[k].aType=='A'){
            if(ZZptr[k].aType=='A')pn=(char*)"ZZarray";
            else pn=strs[j2];
	    n=strlen(pn)+1;
	    pointTo=(char *)malloc(n);
	    if(!pointTo){
                ZZmsgS(1,"pointTo"); /* problem to allocate pointTo */
                return(3);
            }
	    strcpy(pointTo,pn);
        }
        else pointTo=(char *)pTypeConv((const char)(ZZptr[k].aType));

	/* look for this pointer under this Extention */
	for(z=ext->ptr;z;z=z->next){ if(!strcmp(z->bName,ptrName))break;
	}
	if(!z){  /* is a new pointer needed for this Extention? */
	    z=(ZZextPtr*)malloc((int)sizeof(struct ZZextPtr));
	    if(!z){
                ZZmsgS(1,"ZZextPtr"); /* problem to allocate ZZextPtr */
                return(4);
            }
	    if(!strcmp(ptrName,SELFID_PTR_NAME))orgSelfUsed=1;
            

	    z->bName=ptrName;  /* has been allocated above */
	    z->count=0;
	    z->next=ext->ptr;
	    ext->ptr=z;
	    z->orgInd=fp->orgInd;
	    z->ptrCode=NULL;
            z->masterP= &(ZZptr[k]);
	}
	else free(ptrName);

	/* look for this pointer name */
        if(noMix)return(0);
        mix=ZZmix(z->bName,id);
        for(pc=z->ptrCode;pc;pc=pc->next)if(!strcmp(mix,pc->pName))break;
	if(pc){
	    free(mix);
            free(pointTo);
            ZZmsgSS(5,org->name,id); /* warning: multiple definition of id */
	}
        else {
            pc=(ZZptrCode*)malloc((int)sizeof(struct ZZptrCode));
            if(!pc){
                ZZmsgS(1,"ZZptrCode"); /* problem to allocate ZZptrCode */
                return(5);
            }
            pc->next=z->ptrCode;
            z->ptrCode=pc;
            pc->pName=mix;
            pc->masterP= &(ZZptr[k]);
            pc->pointTo=pointTo;
            (z->count)++;
        }
    }

    if(recInst(fp,id,strs,ns))return(6); /* return=error*/
    return(0);
}
/* ---------------------------------------------------------------------- */
/* Form a mix of two names and
 * put it into a newly allocated string, return NULL if allocation problem
 */
#ifdef ZZ_ANSI
char *ZZmix(char *str1,char *str2)

#else
char *ZZmix(str1,str2)
char *str1,*str2;
#endif
{
    char *p;
    int n;

    n=strlen(str1)+strlen(str2)+1;
    p=(char*)malloc(n);
    if(!p){
        ZZmsgD(2,n); /* problem to allocate in ZZmix() */
        return(p);
    }
    strcpy(p,str1);
    strcat(p,str2);
    return(p);
}
/* ---------------------------------------------------------------------- */
/* check that this instance has been declared */
#ifdef ZZ_ANSI
void checkFun(ZZfunction *fp,char *id,char *lineN)

#else
void checkFun(fp,id,lineN)
ZZfunction *fp; /* function, leads to the organization */
char *id;       /* organization identifier */
char *lineN;    /* line number */
#endif
{
    ZZorgInst *oi;

    /* when orgnization has only one input parameter, such as selfID
     * or property, there is always only one instance of the organization */
    if(ZZorg[fp->orgInd].nInp<=1)return;

    for(oi=ZZinst;oi;oi=oi->next)if(!strcmp(id,oi->ident))break;
    if(!oi)ZZmsgSS(6,lineN,id); /* warning: id not declared */
    return;
}
/* ---------------------------------------------------------------------- */
/* For a given structure, find the name of the Extention. */
#ifdef ZZ_ANSI
char *nameExt(char *str)

#else
char *nameExt(str)
char *str; /* structure name */
/* returns pointer to a newly allocated string, NULL if allocation problem */
#endif
{
    static char * head={(char*)"ZZ_EXT_"};
    char *name;
    int n;

    n=strlen(str)+strlen(head)+1;
    name=(char *)malloc(n);
    if(!name){
        ZZerror++;
        ZZmsgS(1,str); /* problem to allocate name of Extention */
        return(NULL);
    }
    strcpy(name,head);
    strcat(name,str);
    return(name);
}
/* ---------------------------------------------------------------------- */
/* if not recorded yet, record the next conversion for the generic function */
#ifdef ZZ_ANSI
void genRec(ZZfunction *fp,char *id)

#else
void genRec(fp,id)
ZZfunction *fp; /* pointer to the generic function */
char *id;       /* organization instance ID */
#endif
{
    int i;
    char *mix;
    ZZgeneric *gp;

    i=strlen(fp->name)+strlen(id)+2;
    mix=(char *)malloc(i);
    if(!mix){
        ZZmsgS(1,"name for generic record"); /* cannot allocate the name */
        return;
    }
    strcpy(mix,fp->name); strcat(mix,"_"); strcat(mix,id);
    for(gp=ZZgen;gp;gp=gp->next){
        if(!strcmp(gp->funInst,mix)){free(mix); return;}
    }
    gp=(ZZgeneric*)malloc((int)sizeof(struct ZZgeneric));
    if(!gp){
        ZZmsgS(1,"generic record"); /* cannot allocate generic record */
        return;
    }
    gp->funMaster=(char *)malloc(strlen(id)+1);
    if(!(gp->funMaster)){
        ZZmsgS(1,"generic id"); /* cannot allocate generic record */
        return;
    }
    strcpy(gp->funMaster,id); /* temporary storage of id */

    gp->funInst=mix;
    gp->next=ZZgen; ZZgen=gp;
    gp->fp=fp;
    return;
}
/* ---------------------------------------------------------------------- */
/* print the conversion defines for all used generic functions,
 * also look for all the master functions and mark them as used */
#ifdef ZZ_ANSI
void genDef(FILE *outFile)

#else
void genDef(outFile)
FILE *outFile;
#endif
{
    int i,size;
    ZZgeneric *gp;
    struct FunList {
        char *name; /* sometimes short, sometimes long name */
        ZZfunction *fun;
    } *fList,*fp;
    ZZorgInst *oi;

    /* replace id stored in gp->funMaster by the organization name */
    for(gp=ZZgen;gp;gp=gp->next){
        for(oi=ZZinst;oi;oi=oi->next){
            if(!strcmp(oi->ident,gp->funMaster)){
                gp->funMaster=ZZorg[oi->orgInd].name;
                break;
            }
        }
        if(!oi){
            ZZmsgSS(22,gp->funInst,gp->funMaster);
            gp->funMaster=NULL;
        }
    }

    for(gp=ZZgen;gp;gp=gp->next){
        if(gp->funMaster)fprintf(outFile,"#define %s %s_%s\n",
                                 gp->funInst,gp->fp->name,gp->funMaster);
    }
    fprintf(outFile,"\n");

    if(selectMacros){
        /* make a list of functions with long names only */
        size=(int)sizeof(struct FunList);
        fList=(struct FunList *)malloc(nFun*size);
        if(!fList){
            ZZmsgS(1,"genDef()"); /* failure to allocate in genDef() */
            return;
        }
        for(i=0; i<nFun; i++){     /* populate the list */
            fList[i].name=ZZfun[i].name;
            fList[i].fun= &(ZZfun[i]);
        }
    
        ZZoffset=ZZpOffset((char *)(&(fList->name)),(char *)fList);
        qsort(fList,nFun,size,genSortFun);
        (void)setBuckets((char *)fList,nFun,size,ZZoffset);

        for(gp=ZZgen;gp;gp=gp->next){
            strcpy(buff,gp->fp->name);
            strcat(buff,"_");
            strcat(buff,gp->funMaster);
	    fp=(struct FunList *)binCmp((char *)fList,size,ZZoffset,nFun,buff);
            if(fp!=NULL)fp->fun->used=LONG_NAME;
        }
        free(fList);
    }
}
/* ---------------------------------------------------------------------- */
/* from the parameters of the main() call, eliminate -I statements, and
 * create a list of default directories and files */
#ifdef ZZ_ANSI
DirObj *defDir(char **argv,int *argc)

#else
DirObj *defDir(argv,argc)
char **argv;
int *argc;
#endif
{
    int i,ii,k;
    DirObj *dp;

    dp=NULL;
    ii=(*argc);
    for(i=2,k=1;i<ii;i++){
        if(argv[i][0]=='-' && argv[i][1]=='I')addDir(&dp,&(argv[i][2]));
        else { k++; argv[k]=argv[i]; }
    }
    *argc=k+1;
    return(dp);
}
/* ---------------------------------------------------------------------- */
/* add new directory */
#ifdef ZZ_ANSI
void addDir(DirObj **dp,char *name)

#else
void addDir(dp,name)
DirObj **dp; /* start of directories in/out value */
char *name; /* name of the new directory */
#endif
{
    char *nn;
    DirObj *d;
    
    nn=(char *)malloc(strlen(name)+1);
    strcpy(nn,name);
    d=(DirObj *)malloc((int)sizeof(struct DirObj));
    if(!d){ZZmsgS(1,"addDir"); return;}
    d->next=(*dp);
    *dp=d;
    d->name=nn;
    d->file=NULL;

    strcpy(buff,"ls ");
    strcat(buff,nn);
    strcat(buff,">ZZfiles");
    system(buff); /* creates the list of files on file ZZfiles */

    addFil(d,(char*)"ZZfiles");
}
/* ---------------------------------------------------------------------- */
/* read file 'fName' and put all the files from there on the list under
 * directory d */
#ifdef ZZ_ANSI
void addFil(DirObj *d,char *fName)

#else
void addFil(d,fName)
DirObj *d;
char *fName;
#endif
{
    FILE *fp;
    char *nn,name[80];
    FilObj *f;

    fp=fopen(fName,"r");
    if(!fp){ZZmsgS(0,fName); return;}
    while(fgets(buff,BUFSIZE,fp)){
        sscanf(buff,"%s",name);
        nn=(char *)malloc(strlen(name)+1);
        strcpy(nn,name);
        f=(FilObj *)malloc((int)sizeof(struct FilObj));
        if(!f){ZZmsgS(1,"addFil"); return;}
        f->next=d->file;
        d->file=f;
        f->name=nn;
    }
    fclose(fp);
}
/* ---------------------------------------------------------------------- */
/* add references to virt.classes to inheritance records
 * just for easier addressing */
#ifdef ZZ_ANSI
void addVirtClasses(ZZextention *parent,ZZextention *ext)

#else
void addVirtClasses(parent,ext)
ZZextention *parent; /* parent of this whole tree */
ZZextention *ext;    /* extention of the next level */
#endif
{
    struct ZZinhList *ip,*ii;

    for(ip=ext->iList;ip;ip=ip->next){
        addVirtClasses(parent,ip->ext);
        if(strcmp("ZZvirtual",ip->name))continue;
        /* check that this relation not recorded yet */
        for(ii=parent->iList;ii;ii=ii->next){
            if(ii->ext==ip->ext)break;
        }
        if(ii)continue;

        /* add this relation as ZZrefer */
        ii=(struct ZZinhList *)malloc((int)sizeof(struct ZZinhList));
        if(!ii){ ZZmsgS(1,"addVirtClassesIO"); return;}
        ii->next=parent->iList;
        parent->iList=ii;
        ii->ext=ip->ext;
        ii->name=(char*)"ZZrefer";
        ii->num=0;
    }
            
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* debugging print of the partially parsed text */
#ifdef ZZ_ANSI
void debParser(char *p)

#else
void debParser(p)
char *p;
#endif
{
    int i;
    char *c,last;

    for(i=1,c=p,last=BLANK;;c++,i++){
        if(*c==END)printf("?"); else printf("%c",*c);
        if(last==END && *c==END)break;
        last= *c;
        if(i>=60){i=0; printf("\n");}
    }
    printf("\n");
}
/* ---------------------------------------------------------------------- */
/* debugging print of the sorted list of functions */
#ifdef ZZ_ANSI
void debFunction(void)

#else
void debFunction()
#endif
{
    int i;

    for(i=0;i<nFun;i++)
	printf("%d %s name=%s file=%s orgInd=%d used=%c create=%c\n",
	&(ZZfun[i]),ZZfun[i].sName,ZZfun[i].name,ZZfun[i].fileName,
	ZZfun[i].orgInd,ZZfun[i].used,ZZfun[i].create);
}
/* ---------------------------------------------------------------------- */
/* debugging print of extentions */
#ifdef ZZ_ANSI
void debExtention(char *text)

#else
void debExtention(text)
char *text;
#endif
{
    ZZextention *ext;
    ZZextPtr *ptr;
    ZZptrCode *pc;

    printf("%s\n",text);
    for(ext=ZZext;ext;ext=ext->next){
	printf("ext=%s\n",ext->name);
	for(ptr=ext->ptr;ptr;ptr=ptr->next){
            for(pc=ptr->ptrCode;pc;pc=pc->next){
                printf("  %s %s\n",pc->pointTo,pc->pName);
            }
        }
    }
}
