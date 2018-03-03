/****************************************************************/
/*							      	*/
/*   Copyright (C) 1988 1989             			*/
/*	Code Farms Inc.,  All Rights Reserved.			*/
/*							  	*/
/****************************************************************/

/* Program to merge two zzmaster files - typically the standard OrgC
 * library with a private user library
 *
 * Syntax: zzmerge <zzmaster1> <zzmaster2> <zzmaster3>
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
    FILE *file3,*fopen(const char*,const char*);
    int crossOrg(void),getMaster(char *,int);
    void newOrg(FILE *),newPtr(FILE *),newFun(FILE *),newSup(FILE *),
         newHier(FILE *),elimSup(void);
#else
int main(argc,argv)
int argc;
char *argv[];
{
    FILE *file3,*fopen();
    int crossOrg(),getMaster();
    void newOrg(),newPtr(),newFun(),newSup(),newHier(),elimSup();
#endif

    if(argc!=4){ZZmsg(32); return(1);} /* wrong syntax */
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

    /* cross-reference and cross-check organizations */
    if(crossOrg())return(1); /* in case of error, no sense to continue */

    /* eliminate unused support and support duplications */
    elimSup();
                     
    /* header of the master file */
    fprintf(file3,"/* ======================================== \n");
    fprintf(file3,"  master file merged from %s and %s */\n\n",argv[1],argv[2]);

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
/* Eliminate unused support entries, and duplications.
 * Internal coding:
 *   ZZsup[].used='n' for entry not used;
 *               ='u' for entry used with index ZZsup[].ind;
 *               ='t' for transfer to XXsup[ZZsup[].ind]
 */
#ifdef ZZ_ANSI
void elimSup(void)
#else
void elimSup()
#endif
{
    int i,ii,j,jj,k;

    for(i=0;i<nSup;i++){
        ZZsup[i].ind=(-1); /* mark as not transferable */
        ZZsup[i].used='n'; /* mark as unused */
    }

    for(k=0;k<nFun;k++){
        i=ZZfun[k].sup;
        if(i>=0){
            for(j=0;j<mSup;j++){ /* try all matches in the first set */
                if(!strcmp(XXsup[j].fileName,ZZsup[i].fileName)){
                    /* now try the whole sequence */
                    for(jj=j, ii=i; jj>=0 && ii>=0;
                                    jj=XXsup[jj].next, ii=ZZsup[ii].next){
                        if(strcmp(XXsup[jj].fileName,ZZsup[ii].fileName))break;
                    }
                    if(jj<0 && ii<0){ /* both sequences match */
                        ZZsup[i].ind=j;
                        ZZsup[i].used='t';
                        break;
                    }
                    else {
                        for(ii=i; ii>=0; ii=ZZsup[ii].next)ZZsup[ii].used='u';
                    }
                 }
             }
         }
     }

    /* establish new indexing */
    for(i=k=0;i<nSup;i++){
        if(ZZsup[i].used=='u'){ ZZsup[i].ind=k; k++; }
    }
}
/* ---------------------------------------------------------------- */
/* cross-check and cross-reference organizations */
#ifdef ZZ_ANSI
int crossOrg(void)
#else
int crossOrg()
#endif
/* return 0 if no errors, set ZZorg[].ind to new index, negative for 
 * the cross-reference for identical organizations */
{
    int j,err,i1,i2,k1,k2;

    err=0;
    j=mOrg; /* new index in the second group */
    for(i2=0;i2<nOrg;i2++){
        for(i1=0;i1<mOrg;i1++){
            if(!strcmp(ZZorg[i2].name,XXorg[i1].name))break;
        }
        if(i1<mOrg){ /* identical organizations found */
            /* check that the pointers are identical */
            if(ZZorg[i2].top-ZZorg[i2].ptrInd!=XXorg[i1].top-XXorg[i1].ptrInd){
                ZZmsgS(10,ZZorg[i2].name);
                err++;
            }
            else {
                for(k2=ZZorg[i2].ptrInd, k1=XXorg[i1].ptrInd; k2<=ZZorg[i2].top;
                                                                  k2++,k1++){
                    if(ZZptr[k2].strToUse!=XXptr[k1].strToUse ||
                       ZZptr[k2].strToPoint!=XXptr[k1].strToPoint ||
                       ZZptr[k2].aSize!=XXptr[k1].aSize ||
                       ZZptr[k2].aType!=XXptr[k1].aType ||
                       strcmp(ZZptr[k2].code,XXptr[k1].code)){

                        ZZmsgS(10,ZZorg[i2].name);
                        err++;
                    }
                }
            }
            if(err==0){ZZorg[i2].ind=(-i1); ZZorg[i2].used='t';}
            else ZZorg[i2].used='n';
        }
        else {
            ZZorg[i2].ind=j;
            j++;
            ZZorg[i2].used='u';
        }
    }
    return(err);
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

    for(i=0;i<mOrg;i++){
        fprintf(file3,"    %d %s %d %d %d\n",
                  i,XXorg[i].name,XXorg[i].ptrInd,XXorg[i].top,XXorg[i].nInp);
        m=XXorg[i].top; /* remember the last pointer index */
    }

    for(k=0;k<nOrg;k++){
        if(ZZorg[k].used=='u'){
            if(ZZorg[k].ind!=i)ZZmsgS(11,"newOrg");
            else {
                n=ZZorg[k].top-ZZorg[k].ptrInd+1+m;
                fprintf(file3,"    %d %s %d %d %d\n",
                  i,ZZorg[k].name,m+1,n,ZZorg[k].nInp);
                m=n;
                i++;
            }
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
    int i,k,m,n;

    for(i=0;i<mOrg;i++){
        for(k=XXorg[i].ptrInd;k<=XXorg[i].top;k++){
            fprintf(file3,"    %d %d %d %d %c %s\n",k,XXptr[k].strToUse,
            XXptr[k].strToPoint,XXptr[k].aSize,XXptr[k].aType,XXptr[k].code);
        }
        m=XXorg[i].top; /* remember the last pointer index */
    }

    for(k=0;k<nOrg;k++){
        if(ZZorg[k].used=='u'){
            for(n=ZZorg[k].ptrInd;n<=ZZorg[k].top;n++){
                m++;
                fprintf(file3,"    %d %d %d %d %c %s\n",
                         m,ZZptr[n].strToUse,ZZptr[n].strToPoint,
                         ZZptr[n].aSize,ZZptr[n].aType,ZZptr[n].code);
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
    int i,j,jj,k,n,m;

    for(i=0;i<mFun;i++){
        k=XXfun[i].orgInd; /* first master file no change */
        fprintf(file3,"    %s %s %s %d %d %c\n",XXfun[i].sName,XXfun[i].name,
                           XXfun[i].fileName,k,XXfun[i].sup,XXfun[i].create);
    }

    for(i=0;i<nFun;i++){
        /* avoid doubly copy of any function */
        for(k=0;k<mFun;k++){
            n=m=0;
            if(!strcmp(ZZfun[i].sName,XXfun[k].sName))n++;
            if(!strcmp(ZZfun[i].name,XXfun[k].name))n++;
            if(!strcmp(ZZfun[i].fileName,XXfun[k].fileName))n++;
            if(ZZfun[i].sup==XXfun[k].sup)m++;
            if(ZZfun[i].create==XXfun[k].create)m++;
            if(n>0){
                if(n+m<5)ZZmsgS(12,ZZfun[i].name);
                else break;
            }
        }
        if(k>=mFun){
           k=ZZfun[i].orgInd; /* first master file no change */
           if(k>=0){ k=ZZorg[k].ind; if(k<0)k=(-k);}
           j=ZZfun[i].sup;
           if(j>=0){
               jj=j; /* remember original index */
               j=ZZsup[j].ind;
               if(ZZsup[jj].used!='t')j+=mSup;
           }
           fprintf(file3,"    %s %s %s %d %d %c\n",ZZfun[i].sName,ZZfun[i].name,
                        ZZfun[i].fileName,k,j,ZZfun[i].create);
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
    int i,k,kk,n;

    for(i=0;i<mSup;i++){
        fprintf(file3,"    %d %d %s\n",i,XXsup[i].next,XXsup[i].fileName);
    }

    for(k=0;k<nSup;k++){
        if(ZZsup[k].used=='u'){
            kk=ZZsup[k].ind;
            n=ZZsup[k].next;
            if(n>=0)n=i+ZZsup[n].ind;
            fprintf(file3,"    %d %d %s\n",i+kk,n,ZZsup[k].fileName);
        }
    }
}
/* ---------------------------------------------------------------- */
#ifdef ZZ_ANSI
void newHier(FILE *file3)
#else
void newHier(file3)
FILE *file3;
#endif
{
    int i,k;

    for(i=0;i<mHier;i++){
        fprintf(file3,"    %s %s %s %s\n",XXhier[i].parent->name,
                    ZZhier[i].child->name,XXhier[i].prefix,XXhier[i].sequence);
    }

    for(i=0;i<nHier;i++){
        for(k=0;k<mHier;k++){ /* avoid duplications */
            if(!strcmp(ZZhier[i].parent->name,XXhier[k].parent->name) &&
               !strcmp(ZZhier[i].child->name,XXhier[k].child->name))break;
        }
        if(k>=mHier)fprintf(file3,"    %s %s %s %s\n",ZZhier[i].parent->name,
                    ZZhier[i].child->name,ZZhier[i].prefix,ZZhier[i].sequence);
    }
}
