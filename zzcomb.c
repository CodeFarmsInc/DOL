/****************************************************************/
/*							      	*/
/*   Copyright (C) 1988 1989             			*/
/*	Code Farms Inc.,  All Rights Reserved.			*/
/*							  	*/
/****************************************************************/
#define mainCode
#define ZZmain
#include <stdio.h>
#include "zzintern.h"
#ifdef MAC
#include ":lib:heading.h"
#include ":lib:buffer.h"
#else
#include "lib/heading.h"
#include "lib/buffer.h"
#endif

/* functions in file zzcomb.c */
/* ------------------------------------------------ */
#ifdef ZZ_ANSI
int shortDef(FILE *outFile);
int allMacros(FILE *outFile);

#else
int shortDef();
int allMacros();
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
int ZZioFunction(FILE *fp,int mode,int type,char *p);
int ZZbindPtrs(char *obj,int newTp,int newSize,int vUpd,int blast);
void *ZZnewBit(unsigned int size) ;
void ZZstTime(unsigned char *c);
void ZZgtTime(unsigned char *i,unsigned char *e);

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
int ZZioFunction();
int ZZbindPtrs();
void *ZZnewBit();
void ZZstTime();
void ZZgtTime();
#endif


/* zzcomb -
 * combine all macros and include files into one file zzcomb.h
 *
 * Algorithm::
 * (1) Read file zzmaster with the table of all organizations and functions.
 * (2) Print the first line - comment with the date and time
 * (3) Form the output file - typically zzcomb.h:
 *     - copy all the Function macros from the individual files
 *     - create 'define' statement for all short macros used
 *
 * Typical use:
 *               zzcomb
 *
 * Author: Jiri Soukup, Sept. 5, 1988 (for Turbo C)
 */

#ifdef ZZ_ANSI
int main(void)

#else
int main()
#endif
{
    FILE *outFile,*ff;
    unsigned char s[4],c[6];

#ifdef DOS
    printf("... the generation of file zzcomb.h takes typically 15 sec\n");
#else
    printf("... the generation of file zzcomb.h takes typically 15 sec\n");
#endif
    /* (1) read file macro/zzmaster with all function- and file references */
    /* -------------------------------------------------------------------- */
    ZZmaster=(char*)"zzmaster";
    if(getMaster((char*)PATH_HERE,1))return(7);

    if((outFile=myopen((char*)"zzcomb.h","w"))==NULL){
        ZZmsgS(0,"zzcomb.h"); /* cannot open file zzcomb.h */
        return(1);
    }

    /* (2) print first comment line with the date and time */
    ZZstTime(s);
    ZZgtTime(s,c);
    fprintf(outFile,"/* %d %d %d %d %d %d */\n",c[0],c[1],c[2],c[3],c[4],c[5]);

    /* put Copyright and general headings into the include file */
#ifdef MAC
    if((ff=myopen(":lib:types.h","r"))==NULL){
        ZZmsgS(0,":lib:types.h"); /* cannot open the file */
        return(2);
    }
#else
    if((ff=myopen((char*)"lib/types.h","r"))==NULL){
        ZZmsgS(0,"lib/types.h"); /* cannot open the file */
        return(2);
    }
#endif
    cpFile(ff,outFile,NULL);
    fclose(ff);

#ifdef MAC
    if((ff=myopen(":lib:heading.h","r"))==NULL){
        ZZmsgS(0,":lib:heading.h"); /* cannot open the file */
        return(2);
    }
#else
    if((ff=myopen((char*)"lib/heading.h","r"))==NULL){
        ZZmsgS(0,"lib/heading.h"); /* cannot open the file */
        return(2);
    }
#endif
    cpFile(ff,outFile,NULL);
    fclose(ff);

    /* (3) copy macros and *.h files */
    /* ----------------------------- */
    if(allMacros(outFile))return(3); /* copy all macro files */
    shortDef(outFile);                /* create 'defines' for short names */
    fclose(outFile);
    printf("\nzzcomb.h is ready\n");
    return(0);
}
/* ---------------------------------------------------------------------- */
/* Create 'define' conversion statements for those macros that are used
 * either in the short form only, or in both forms. 
 */
#ifdef ZZ_ANSI
int shortDef(FILE *outFile)

#else
int shortDef(outFile)
FILE *outFile;  /* output file, typically ZZinclude.h */
#endif
{
    int i;

    fprintf(outFile,"\n");
    for(i=0;i<nFun;i++){
	fprintf(outFile,"#define %s %s\n",ZZfun[i].sName,ZZfun[i].name);
    }
    return(0);
}
/* ---------------------------------------------------------------------- */
/* Copy all macros onto the output file, filter out the documentation part */
#ifdef ZZ_ANSI
int allMacros(FILE *outFile)

#else
int allMacros(outFile)
FILE *outFile; /* output file */
/* returns number of errors */
#endif
{
    FILE *ff;
    int i,ii,k,eCount,done,m;
    char *oldName;

    printf("0                 25                  ");
    printf("50                  75                100\r");
    for(i=eCount=0;i<nFun;i++){
#ifdef MAC
	strcpy(buff,":macro:");
#else
	strcpy(buff,"macro/");
#endif
	strcat(buff,ZZfun[i].fileName);
	/* 1 means automatic detection of encrypted files */
	jsCrypt(buff,(char*)"ZZdecryp",'d',(char*)ZZcryptKey,1,1);
        if((ff=myopen((char*)"ZZdecryp","r"))==NULL){
	    eCount++;
	    ZZmsgS(3,ZZfun[i].name); /* cannot open ZZdecrypt for macro ... */
	}
	else {
            /* avoid writing the same file twice */
            for(ii=0;ii<i;ii++){
                if(!strcmp(ZZfun[i].fileName,ZZfun[ii].fileName))break;
            }
            if(ii==i){
	        cpFile(ff,outFile,NULL);
            }
	    fclose(ff);
	    if(strcmp(ZZcryptKey,"*"))delFile((char*)"ZZdecryp");
	}
        done=(80*i)/nFun;
        for(m=0;m<done;m++)printf("*");
        printf("\r");
    }

    /* There may be multiple references to the same support file in ZZsup[];
     * sort the list to avoid duplications */
    for(i=0;ZZsup[i].used!='e';i++)continue; /* i=count of entries */
    ZZoffset=(int)(&(ZZsup->fileName))-(int)ZZsup;
    qsort(ZZsup,i,sizeof(struct ZZsupport),genSortFun);
    /* copy all the support code */
    oldName=(char*)" ";
    for(i=0;ZZsup[i].used!='e';i++){
	if(strcmp(oldName,ZZsup[i].fileName)){
	    oldName=ZZsup[i].fileName;
#ifdef MAC
	    strcpy(buff,":lib:");
#else
	    strcpy(buff,"lib/");
#endif
	    strcat(buff,ZZsup[i].fileName);
	    /* 1 means automatic detection of encrypted files */
	    jsCrypt(buff,(char*)"ZZdecryp",'d',(char*)ZZcryptKey,1,1);
            ff=myopen((char*)"ZZdecryp","r");
            if(!ff){
	        eCount++;
	        ZZmsgS(3,ZZsup[i].fileName); /*cannot open ZZdecrypt for macro*/
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
