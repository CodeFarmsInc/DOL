/****************************************************************/
/*							      	*/
/*   Copyright (C) 1988 1989             			*/
/*	Code Farms Inc.,  All Rights Reserved.			*/
/*							  	*/
/****************************************************************/

/* Program to select limited features from a given zzmaster file
 *
 * Syntax: zzselect <zzmaster1> <zzmaster2> <zzmaster3>
 * where: zzmaster1 is the original (full) master file,
 *        zzmaster2 is the version with deleted functions/macros
 *        zzmaster3 is the reduced version with correct indices
 *
 * Author: Jiri Soukup, Dec.12, 1989
 */

#define ZZmain
#define mainCode
#define BELOW
#include <stdio.h>
#include "environ.h"
#ifdef MAC
#include "::zzintern.h"
#include "::lib:heading.h"
#include"::lib:buffer.h"
#else
#include "../zzintern.h"
#include "../lib/heading.h"
#include "../lib/buffer.h"
#endif

/* Global variables to remember the first zzmaster file: */
int mOrg,mPtr,mFun,mSup,mHier;
ZZorganization *XXorg;
ZZpointer *XXptr;
ZZfunction *XXfun;
ZZsupport *XXsup;
ZZhierarchy *XXhier;

#ifdef ZZ_ANSI
int main(int argc,char **argv)
{
    int getMaster(char *,int);
    void newOrg(FILE *),newPtr(FILE *),newFun(FILE *),newSup(FILE *),
         newHier(FILE *);
#else
int main(argc,argv)
int argc;
char *argv[];
{
    int getMaster();
    void newOrg(),newPtr(),newFun(),newSup(),newHier();
    FILE *fopen();
#endif
    int i,j,k;
    FILE *file3;

    if(argc!=4){ZZmsg(48); return(1);} /* wrong syntax */
    file3=fopen(argv[3],"w");
    if(!file3){ZZmsgS(0,argv[3]); return(1);} /* problem to open the file */

    /* get the first master file */
    ZZmaster=argv[1];
    getMaster("..",0);
    mOrg=nOrg;   mPtr=nPtr;   mFun=nFun;   mSup=nSup;   mHier=nHier;
    XXorg=ZZorg; XXptr=ZZptr; XXfun=ZZfun; XXsup=ZZsup; XXhier=ZZhier;

    /* get the second master file */
    ZZmaster=argv[2];
    getMaster("..",0);

    /* mark the used functions/macros */
    for(j=0;j<mFun;j++)XXfun[j].used='n';
    for(k=0;k<nFun;k++){
        for(j=0;j<mFun;j++){
            if(!strcmp(ZZfun[k].name,XXfun[j].name))break;
        }
        if(j<mFun)XXfun[j].used='u';
        else ZZmsgS(28,ZZfun[k].name);
    }
    /* from now on, we will operate only on the original (XX) set */

    /* mark the organizations and support actually used */
    for(i=0;i<mOrg;i++)XXorg[i].used='n'; /* initialize */
    for(i=0;i<mSup;i++)XXsup[i].used='n'; /* initialize */
    /* support index=0 is always used: */
    for(j=0; j>=0; j=XXsup[j].next)XXsup[j].used='u';
    for(k=0;k<mFun;k++){ /* now do the actual marking */
        if(XXfun[k].used=='u'){
            i=XXfun[k].orgInd;
            if(i>=0)XXorg[i].used='u';
            for(j=XXfun[k].sup; j>=0; j=XXsup[j].next)XXsup[j].used='u';
        }
    }

    /* record reduced index */
    for(i=k=0;i<mOrg;i++)if(XXorg[i].used=='u'){XXorg[i].ind=k; k++;}
    for(i=k=0;i<mSup;i++)if(XXsup[i].used=='u'){XXsup[i].ind=k; k++;}
    
    /* header of the master file */
    fprintf(file3,"/* ======================================== \n");
    fprintf(file3,"  master file selected from %s, %s */\n\n",argv[1],argv[2]);

    /* ZZorganization section */
    fprintf(file3,"/*  ind   organization       p1 p2 nInp */\n");
    fprintf(file3,"ZZorganization {\n");
    newOrg(file3);
    fprintf(file3,"}\n\n");

    /* ZZpointer section */
    fprintf(file3,"/* ind usedOn pointTo arraySize ptrType ptrCode */\n");
    fprintf(file3,"ZZpointer {\n");
    newPtr(file3);
    fprintf(file3,"}\n\n");

    /* ZZfunction section */
    fprintf(file3,"/* shortName  functionName  fileName   org sup create */\n");
    fprintf(file3,"ZZfunction {\n");
    newFun(file3);
    fprintf(file3,"}\n\n");

    /* ZZhierarchy section */
    fprintf(file3,"/*   parentOrg     childOrg        prefix  parameters */\n");
    fprintf(file3,"ZZhierarchy {\n");
    newHier(file3);
    fprintf(file3,"}\n\n");

    /* ZZsupport section */
    fprintf(file3,"/* ind next  fileName       */\n");
    fprintf(file3,"ZZsupport {\n");
    newSup(file3);
    fprintf(file3,"}\n\n");
    return(0);
}
/* ---------------------------------------------------------------- */
#ifdef ZZ_ANSI
void newOrg(FILE *file3)
#else
void newOrg(file3)
FILE *file3;
#endif
{
    int i,k,m,n;

    for(k=i=0, m=(-1); k<mOrg; k++){
        if(XXorg[k].used=='u'){
            n=XXorg[k].top-XXorg[k].ptrInd+1+m;
            fprintf(file3,"    %d %s %d %d %d\n",
                  i,XXorg[k].name,m+1,n,XXorg[k].nInp);
            m=n;
            i++;
        }
    }
}
/* ---------------------------------------------------------------- */
#ifdef ZZ_ANSI
void newPtr(FILE *file3)
#else
void newPtr(file3)
FILE *file3;
#endif
{
    int k,m,n;

    for(k=0, m=(-1); k<mOrg; k++){
        if(XXorg[k].used=='u'){
            for(n=XXorg[k].ptrInd;n<=XXorg[k].top;n++){
                m++;
                fprintf(file3,"    %d %d %d %d %c %s\n",
                         m,XXptr[n].strToUse,XXptr[n].strToPoint,
                         XXptr[n].aSize,XXptr[n].aType,XXptr[n].code);
            }
        }
    }
}
/* ---------------------------------------------------------------- */
#ifdef ZZ_ANSI
void newFun(FILE *file3)
#else
void newFun(file3)
FILE *file3;
#endif
{
    int i,j,k;

    for(i=0;i<mFun;i++){
        if(XXfun[i].used=='u'){
            k=XXfun[i].orgInd;
            if(k>=0)k=XXorg[k].ind;
            j=XXfun[i].sup;
            if(j>=0)j=XXsup[j].ind;
            fprintf(file3,"    %s %s %s %d %d %c\n",XXfun[i].sName,
                  XXfun[i].name,XXfun[i].fileName,k,j,XXfun[i].create);
        }
    }
}
/* ---------------------------------------------------------------- */
#ifdef ZZ_ANSI
void newSup(FILE *file3)
#else
void newSup(file3)
FILE *file3;
#endif
{
    int i,j,k;

    for(i=0;i<mSup;i++){
        if(XXsup[i].used=='u'){
            j=XXsup[i].ind;
            k=XXsup[i].next;
            if(k>=0)k=XXsup[k].ind;
            fprintf(file3,"    %d %d %s\n",j,k,XXsup[i].fileName);
        }
    }
}
/* ---------------------------------------------------------------- */
/* copy the new hierarchies only */
#ifdef ZZ_ANSI
void newHier(FILE *file3)
#else
void newHier(file3)
FILE *file3;
#endif
{
    int i;

    for(i=0;i<nHier;i++){
        fprintf(file3,"    %s %s %s %s\n",ZZhier[i].parent->name,
                    ZZhier[i].child->name,ZZhier[i].prefix,ZZhier[i].sequence);
    }
}
