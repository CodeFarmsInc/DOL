/****************************************************************/
/*							      	*/
/*   Copyright (C) 1988 1989             			*/
/*	Code Farms Inc.,  All Rights Reserved.			*/
/*							  	*/
/****************************************************************/

#include <stdio.h>
#include "environ.h"
#include "types.h"
#include "heading.h"
#include "virtarr.h"

/* some compilers do not have delete[] */
#ifdef ZORTECH
#define DELETE_ARRAY delete
#else
#define DELETE_ARRAY delete[]
#endif

#ifdef SEPARATE
static void ZZmsgS(ZZint i,char *p){prZZintf("%d, error: %s\n",i,p);}
static void ZZmsgSS(ZZint i,char *p1,char *p2){prZZintf("%d, error: %l>%l\n",i,p1,p2);}
#else
#define ZZ_ANSI
#include "msgs.h"
#endif

unsigned ZZint ZZvirtArr::oSize=sizeof(void *);
unsigned ZZint ZZvirtArr::maxSize=32768;
/* --------------------------------------------------------------------- */
vPtr& ZZvirtArr::operator[] (const ZZlong i) {
    ZZlong k,m;

    if(i<0 || i>=nTot){
        ZZmsgSS(31,(char *)nTot,(char *)i);
    }
    if(arr)return(arr[i]);
    k=i/nObj;
    m=i-k*nObj;
    return (mul[k])[m];
    
}
/* --------------------------------------------------------------------- */
void ZZvirtArr::clean(void){
    ZZint i,k;
    if(arr)DELETE_ARRAY arr;
    if(mul){
        k=(ZZint)((nTot+nObj-1)/nObj);
        for(i=0;i<k;i++)if(mul[i])DELETE_ARRAY mul[i];
        DELETE_ARRAY mul;
    }
    arr=NULL; mul=NULL;
    nTot=0;
}
/* --------------------------------------------------------------------- */
void ZZvirtArr::reset(const ZZlong size){  
    ZZlong nRem,m;
    ZZint i,j,k,r,split;
    void*** mNew;

    if(size<=nTot)return;
    split=0;
#ifdef DOS
    if(size>(ZZlong)nObj)split=1;
#endif

    if(split){
        i=(ZZint)((size+nObj-1)/nObj);
        mNew=new vvPtr[i];
        if(!mNew)ZZmsgS(1,"reset virtual array");
        nRem=nTot;
        for(k=0, m=size; k<i; k++, m=m-r, nTot=nTot-r){
            if(m<=nObj)r=(ZZint)m; else r=nObj;
            if(mul && nTot>=(ZZlong)nObj)mNew[k]=mul[k];
            else {
                mNew[k]=new vPtr[r];
                if(!(mNew[k]))ZZmsgS(1,"reset virtual sub-array");
                if(mul && nTot>0){
                    for(j=0 ;nTot>0; nTot--,j++)(mNew[k])[j]=(mul[k])[j];
                    DELETE_ARRAY mul[k];
                }
            }
        }
        if(mul)DELETE_ARRAY mul;
        mul=mNew;
        if(arr){
            for(k=0, m=0, j=0; j<nRem; k++){
                for(m=0; m<(ZZint)nObj && j<nRem; m++,j++) (mul[k])[m]=arr[j];
            }
            DELETE_ARRAY arr;
        }
    }
    else {
        void** aNew=new vPtr[size];
        if(!aNew)ZZmsgS(1,"reset single array");
        if(arr){
            for(j=0; j<nTot; j++)aNew[j]=arr[j];
            DELETE_ARRAY arr;
        }
        arr=aNew;
    }
    nTot=size;
}
