/****************************************************************/
/*							      	*/
/*   Copyright (C) 1988 1989             			*/
/*	Code Farms Inc.,  All Rights Reserved.			*/
/*							  	*/
/****************************************************************/

#define zzLIB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "environ.h"
#include "types.h"
#include "heading.h"
#include "bind.h"
#include "buffer.h"
#include "property.h"
#include "msgs.h"
#include "offset.h"

#ifdef __VMS
#include <unixio.h>
#include <file.h>
#endif

#ifdef SABERCPLUS
#include <sysent.h>
#endif

/* ...................................................... */
#ifdef MICROSOFT
#ifdef ZZcplus
#ifndef MICROSOFT8
extern "C" {
#endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <io.h>
#ifndef ZORTECH
#include <search.h>
#endif

#ifdef ZZcplus
#ifndef MICROSOFT8
}
#endif
#endif
#endif
/* ...................................................... */
#ifdef ZORTECH
#include <io.h>
#endif
#ifdef QNX
#include <stdlib.h>
#endif

/* ................................................................. */
#ifdef UNIX
#ifndef MAC
#ifdef ZZcplus
#ifndef SABERCPLUS

extern "C" {
#ifndef UPP
    ZZint read(ZZint,char *,ZZint);
    ZZint write(ZZint,char *,ZZint);
#endif
#ifndef GNU
#ifndef HP
#ifndef IBM
#ifndef SABERCPLUS
#ifndef LUCID
#ifndef SUN2_1
#ifndef DECPLUS
    FILE *fopen(char *,char *);
#endif
#endif
#endif
#endif
#endif
#endif
#endif
    ZZint close(ZZint);
#ifndef IBM
#ifndef SABERCPLUS
    ZZint fclose(FILE *);
#endif
#endif
#ifndef HP
#ifndef IBM
#ifndef LUCID
#ifndef SUN2_1
#ifndef DECPLUS
#ifndef GNU
    ZZint open(char *,ZZint);
    ZZint creat(char *,ZZint);
#endif
#endif
#endif
#endif
#endif
#endif
#ifdef IBM
    ZZint open(const char *, ZZint, mode_t);
    ZZint creat(const char *,mode_t);
#endif
/* funny: SUN C++ does pick up these automatically:
    ZZint fwrite(char *,ZZint,ZZint,FILE *);
    ZZint fread(char *,ZZint,ZZint,FILE *);
*/
}
#endif

#else                        /* ZZcplus */

#ifdef ZZ_ANSI
#ifdef HP
    ZZint open(const char *, ZZint, ...);
    ZZint creat(const char *,mode_t);
#else
#ifndef GNUPLUS
#ifndef LUCID
    /* most UNIX systems including SUN */
    ZZint open(char *name, ZZint mode);
    ZZint creat(const char *name,ZZint mode);
#endif /* LUCID */
#endif /* GNUPLUS */
#endif /* HP */

#else /* ZZ_ANSI */
#ifndef IBM
#ifndef SUN3_0
    ZZint open();
#endif
#endif
    ZZint creat();
#endif /* ZZ_ANSI */

#endif                       /* END ZZcplus */
#endif                       /* END MAC */
#endif                       /* END UNIX */
/* ................................................................. */

#ifdef TURPLUS
extern "C" {
    ZZint _close(ZZint);
    ZZint _open(char*,ZZint);
    ZZint _creat(char*,ZZint);
    ZZint _read(ZZint,char*,ZZint);
    ZZint _write(ZZint,char*,ZZint);
    ZZint read(ZZint,char *,ZZint);
    ZZint write(ZZint,char *,ZZint);
    ZZint close(ZZint);
    ZZint fclose(FILE *);
    ZZint open(char *,ZZint);
    ZZint creat(char *,ZZint);
/* funny: Turbo C++ does pick up these automatically:
    FILE *fopen(char *,char *);
    ZZint fwrite(char *,ZZint,ZZint,FILE *);
    ZZint fread(char *,ZZint,ZZint,FILE *);
*/
}
#endif

/* Borland 3.0 has a bug - does not accept local function
 * prototypes if the function is defined above */
#ifdef ZZ_ANSI
    ZZint ZZclose(FILE *fp);
    FILE *handleToPointer(ZZint fh);
    ZZint pointerToHandle(FILE *fp);
    char *ZZfindName(struct ZZstrLST *strList,ZZint type);
    ZZint ZZfindType(struct ZZstrLST *strList,const char *strName);
    void ZZini(char *obj,struct ZZstrLST *strList,char **selfArr,
            ZZint si,ZZint mode,ZZint typeInd,ZZint num,ZZint size);
#else
    ZZint ZZclose();
    FILE *handleToPointer();
    ZZint pointerToHandle();
    char *ZZfindName();
    ZZint ZZfindType();
    ZZvoidS ZZini();
#endif

#ifndef ZORTECH
#define size_t ZZint
#endif 
#ifdef ZZ_ANSI
static void ptrDisp(FILE *,char *,ZZint,struct ZZstrLST *,char**,ZZint*);
#else
static void ptrDisp();
#endif

/* This file contains general utility functions to hide some of the
 * more complicated processing from the macros */
/* -------------------------------------------------------------- */
/* initialize selfID on a new object or an array of objects */
#ifdef ZZ_ANSI
void ZZini(char *obj,struct ZZstrLST *strList,char **selfArr,ZZint si,ZZint mode,
                                ZZint typeInd,ZZint num,ZZint size)
{
    void ZZstTime(unsigned char *p);
     ZZint ZZbindPtrs(char *ptr,ZZint tp,ZZint sz,ZZint vUpd,ZZint val);
#else


void ZZini(obj,strList,selfArr,si,mode,typeInd,num,size)
char *obj;       /* object casted as char * */
struct ZZstrLST strList[]; /* list of all ZZ_EXT structures */
char **selfArr; /* array of names for objects with the selfID tag */
ZZint si;          /* selfID index, -1 for no selfID */
ZZint mode;        /* 1=initialize whole object, 0=ZZ_EXT only,2=new aloc */
ZZint typeInd;     /* index of the type in strList */
ZZint num;         /* number of objects, 1=single object */
ZZint size;        /* size of one object in bytes */
{
    void ZZstTime();
     ZZint ZZbindPtrs();
#endif
    ZZint j,k,n;
    char *p,***q,**w;
    struct ZZstrLST *s;

    if(typeInd<0)return;
    if(ZZmemSwitch==2)ZZbindPtrs(obj,typeInd,size*num,1,1);

    s=(&(strList[typeInd]));
    /* skip initialization when calloc is used */
    if(mode!=2 || !ZZcallocFlg){
        if(mode){
            n=size;
            p=obj;
        }
        else {
            n=(s->numPtr)*(ZZint)sizeof(char*);
            p=obj+s->start;
        }
        if(n>0){
            for(k=0; k<num; k++, p+=size){
	        for(j=0; j<n; j++)p[j]='\0';
	    }
        }
    }

    if(s->timeIndex>=0){
        for(k=0,p=obj;k<num;k++,p+=size){
            w=(char**)p;
            ZZstTime((unsigned char *)(&(w[s->timeIndex])));
        }
    }


    if(si>=0){
        for(k=0,p=obj;k<num;k++,p+=size){
            q=(char***)p;
            *q= &(selfArr[si]);
        }
    }
    return;
}
/* -------------------------------------------------------------- */
/* Deallocate an object or an array of objects, while protecting
 * against freeing an object that is still linked to some registered
 * organization */
#ifdef ZZ_ANSI
ZZint ZZdeal(char *obj,struct ZZstrLST *strList,char *strType,ZZint numObj,
                                                          ZZint size,ZZint action)
{
     void ZZmemory(ZZint code,char **p,ZZint type, ZZint num);
     ZZint ZZdelObj(char *ptr);
     ZZint ZZbindPtrs(char *ptr,ZZint tp,ZZint sz,ZZint vUpd,ZZint blast);
#else


ZZint ZZdeal(obj,strList,strType,numObj,size,action)
char *obj;       /* object casted as char * */
struct ZZstrLST strList[]; /* list of all ZZ_EXT structures */
char *strType;   /* structure type name for this object */
ZZint numObj;         /* number of objects, 1=single object, 0=single to pool */
ZZint size;        /* size of one object in bytes */
ZZint action; /* 0=to deallocate the object, 1=only to check the pointers */
/* returns: 0=everything fine, 1=object not freed */
{
     void ZZmemory();
     ZZint ZZdelObj();
     ZZint ZZbindPtrs();
#endif
    ZZint i,ii,j,jj,k,m,n,num; char **c,*p;

    if(numObj>0)num=numObj; else num=1;
    for(ii=0,i= -1;strList[ii].numPtr>=0;ii++){
	if(!strcmp(strType,strList[ii].strName))i=ii;
    }
    if(i>=0){
        if(ZZmemSwitch==2)ZZbindPtrs(obj,i,size,1,0);
	k=strList[i].selfIndex;
	m=strList[i].start;
	n=strList[i].numPtr;
	for(jj=0, p=obj+m; jj<num; jj++, p+=size){
	    for(j=0;j<n;j++){
		if(j==k)continue;
	        c=(char**)p+j;
	        if(*c!=(char *)NULL){n= -1; break;}
	    }
	    if(n<0)break;
	}
    }
    else n=0;
    if(n<0){
        if(num>1)ZZmsgSDD(0,strType,jj,j);
                       /* cannot free array pointer=.. not disconnected */
        else ZZmsgSD(3,strType,j);
                       /* cannot free object pointer=.. not disconnected */
    }
    else {
        if(numObj==0 && i>=0 && size>=(ZZint)sizeof(char *))ZZmemory(1,&obj,i,ii);
        else if(action==0) ZZdelObj(obj);
    }
    if(n<0)n=1; else n=0;
    if(n)ZZerrFLG=ZZerrFLG|010;
    return(n);
}
/* -------------------------------------------------------------- */
/* allocate selfID on a new object or an array of objects */
#ifdef ZZ_ANSI
char *ZZallo(struct ZZstrLST *strList,char **selfArr,ZZint si,char *strType,ZZint type,
                                                  ZZint numObj,ZZint size,ZZint mode)
{
    ZZvoidS *ZZnewObj(ZZint s,ZZint ini);
    void ZZmemory(ZZint code,char **p,ZZint type, ZZint num);
#else


char *ZZallo(strList,selfArr,si,strType,type,numObj,size,mode)
struct ZZstrLST strList[]; /* list of all ZZ_EXT structures */
char *selfArr[]; /* array of names for objects with the selfID tag */
ZZint si;          /* selfID index, -1 for no selfID */
char *strType;   /* name of the structure type */
ZZint type;        /* type index in strList */
ZZint numObj;      /* number of objects, 1=single object, 0=from pool */
ZZint size;        /* size of one object in bytes */
ZZint mode;        /* 0=no initialization,1=intialize,2=force initialization */
{
    ZZvoidS *ZZnewObj();
    ZZvoidS ZZmemory();
#endif
    char *p;
    ZZint num;
    static ZZint i={-1};
    ZZint forceInit;

    if(i<0)for(i=0;strList[i].numPtr>=0;i++)continue;

    if(numObj>0)num=numObj; else num=1;
    if(numObj==0) ZZmemory(0,&p,type,i);
    else p=(char *)NULL;
    if(!p)p=(char *)ZZnewObj(num*size,0);
    if(!p){
        ZZmsgS(1,strType);
        ZZerrFLG=ZZerrFLG|01;
    }
    else if(mode>0){
        if(mode==2)forceInit=1; else forceInit=2;
        ZZini(p,strList,(char **)selfArr,si,forceInit,type,num,size);
    }
    return(p);
}
/* -------------------------------------------------------------- */
/* Function to hide ZZmemory and calculate the number of types on
 * the first call */
#ifdef ZZ_ANSI
void ZZobjMem(ZZint code,char **ptr,ZZint type,struct ZZstrLST *sL)
{
    void ZZmemory(ZZint code,char **ptr,ZZint type,ZZint num);
#else


void ZZobjMem(code,ptr,type,sL)
ZZint code; /* 0=new object, 1=object to the pool, 2=clear the whole pool */
char **ptr; /* given or returned object, cast as char*, size>=(ZZint)sizeof(char*) */
ZZint type; /* index of the object type */
struct ZZstrLST *sL; /* list of types */
{
    void ZZmemory();
#endif
    static ZZint num={-1};

    if(num<0)for(num=0;sL[num].numPtr>=0;num++)continue;
    ZZmemory(code,ptr,type,num);
}
/* -------------------------------------------------------------- */
/* general memory management function, using an internal static pool */
#ifdef ZZ_ANSI
void ZZmemory(ZZint code,char **ptr,ZZint type,ZZint num)
{
    ZZvoidS *ZZnewObj(ZZint size,ZZint ini);
    ZZint ZZdelObj(char *ptr);
#else


void ZZmemory(code,ptr,type,num)
ZZint code; /* 0=new object, 1=object to the pool, 2=clear the whole pool */
char **ptr; /* given or returned object, cast as char*, size>=(ZZint)sizeof(char*) */
ZZint type; /* index of the object type */
ZZint num;  /* number of orgC registered types */
{
    ZZvoidS *ZZnewObj();
    ZZint ZZdelObj();
#endif
    static char **p=(char **)NULL;
    char **s,*r,*t;
    ZZint i;

    if(type<0 || type>=num){
        ZZmsgD(20,type); /* internal error, type= out of range in ZZmemory() */
        ZZerrFLG=ZZerrFLG|020;
        return;
    }
    if(!p){ /* initialize the pointer array */
        p=(char **)ZZnewObj((ZZint)sizeof(char *)*num,1);
        if(!p){
            ZZmsg(40); /* problem to allocate small array in ZZmemory() */
            ZZerrFLG=ZZerrFLG|01;
            return;
        }
    }

    switch(code){  
        case 0: /* get new object from the pool */
                *ptr=p[type];
                if(p[type]){
                    s=(char**)p[type];
                    p[type]=(*s);
                }
                break;
        case 1: /* move used object into the pool */
                s=(char**)(*ptr);
                *s=p[type];
                p[type]=(*ptr);
                break;
        case 2: /* free the whole pool */
                for(i=0;i<num;i++){
                    for(r=p[i];r;r=t){ 
                        s=(char**)r; t=(*s);
                        ZZdelObj(r);
                    }
                    p[i]=(char *)NULL;
                }
                break;
        default:ZZmsgD(9,code); /* internal error code=%d in ZZmemory() */
                ZZerrFLG=ZZerrFLG|020;
                break;
    }

    return;
}
/* -------------------------------------------------------------- */
/* For a given type name, find the structure index:
 * For the conversion table - see the code.
 * Result>0 means it is a registered DOL class.
 * Result -9 means error, not found.
 *
 * Note that for sweap-expansion or for ASCII save, index= -8 is used for a binary
 * block, such as used in GENERAL LINK, while -1 is reserved for names only.
 */
#ifdef ZZ_ANSI
ZZint ZZfindType(struct ZZstrLST *strList,const char *strName)
#else


ZZint ZZfindType(strList,strName)
struct ZZstrLST strList[];
char *strName;
#endif
{
    ZZint i;

    for(i=0;strList[i].numPtr>=0;i++){
        if(!strcmp(strName,strList[i].strName))break;
    }
    if(strList[i].numPtr<0){
        if(!strcmp(strName,"char*") || !strcmp(strName,"char *"))     i= -1;
        else if(!strcmp(strName,"struct ZZproperty"))                 i= -2;
        else if(!strcmp(strName,"struct ZZaProp"))                    i= -3;
	else if(!strcmp(strName,"ZZarray"))                           i= -4;
        else if(!strcmp(strName,"int"))                               i= -6;
        else if(!strcmp(strName,"float"))                             i= -7;
        else if(!strcmp(strName,"char"))                              i= -8;
        else   /* typically pointer to a registered class */          i= -5;
    }
    return(i);
}
/* -------------------------------------------------------------- */
/* For a given integer type code, find the structure name -
 * this is a reverse function to ZZfindType */
#ifdef ZZ_ANSI
char *ZZfindName(struct ZZstrLST *strList,ZZint type)
#else


char *ZZfindName(strList,type)
struct ZZstrLST strList[];
ZZint type; /* integer type code */
#endif
{
    char *p;

    if(type>=0)p=strList[type].strName;
    else if(type== -1)p=(char*)"char*";
    else if(type== -2)p=(char*)"struct ZZproperty";
    else if(type== -3)p=(char*)"struct ZZaProp";
    else if(type== -4)p=(char*)"ZZarray";
    else if(type== -5)p=(char*)"char*"; /* poiner to a registered class */
    else if(type== -6)p=(char*)"int";
    else if(type== -7)p=(char*)"float";
    else if(type== -8)p=(char*)"char";
    else {p=(char*)""; ZZmsgD(10,type);} /* internal error: %d strange code type */
    return(p);
}
/* -------------------------------------------------------------- */
/* for a given integer type code, find the size of the object in bytes */ 
#ifdef ZZ_ANSI
ZZint ZZfindSize(struct ZZstrLST *strList,ZZint type)
#else


ZZint ZZfindSize(strList,type)
struct ZZstrLST *strList;
ZZint type; /* integer type code */
#endif
{
    ZZint p;

    if(type>=0)p=strList[type].size;
    else if(type== -1)p=(ZZint)sizeof(char);
    else if(type== -2)p=(ZZint)sizeof(struct ZZproperty);
    else if(type== -3)p=(ZZint)sizeof(struct ZZaProp);
    else if(type== -4)p=(ZZint)sizeof(struct ZZarray);
    else if(type== -5)p=(ZZint)sizeof(char *);
    else if(type== -6)p=(ZZint)sizeof(int);
    else if(type== -7)p=(ZZint)sizeof(float);
    else if(type== -8)p=(ZZint)sizeof(char);
    else {p=0; ZZmsgD(10,type);} /* internal error: %d strange code type */
    return(p);
}
/* --------------------------------------------------------------- */
/* Find offset (p2-p1) between two pointers and convert it to an int.
 * This arithmetic should work for any size of ptr/int words, as long
 * as the resulting offset is small enough to fit the integer.
 * WARNING: ZZpOffset(p2,p1) - note the order of the parameters
 */
#ifdef ZZ_ANSI
ZZint ZZpOffset(char *p2,char *p1)
#else


ZZint ZZpOffset(p2,p1)
char *p2,*p1; /* will calculate p2-p1 */
#endif
{
    ZZint i,n;
    union ZZUNI u1,u2;

    u1.p=p1; u2.p=p2;
    n=(ZZint)sizeof(char *);
    if(n==(ZZint)sizeof(ZZint))i=u2.i-u1.i;
    else if(n==(ZZint)sizeof(ZZlong)){u2.l=u2.l-u1.l; i=(ZZint)(u2.l);}
    // else if(n==(int)sizeof(short int)){u2.s=u2.s-u1.s; i=u2.s;}
    else { ZZmsg(50); i=0; }
    return(i);
}
/* --------------------------------------------------------------- */
/* Convert a pointer to integer, assuming the size fits */
#ifdef ZZ_ANSI
ZZint ZZptrToInt(const char *p)
#else

ZZint ZZptrToInt(p)
char *p; /* given pointer */
#endif
{
    ZZint i,n;
    union ZZUNI u;

    u.p=(char*)p;
    n=(ZZint)sizeof(char *);
    if(n==(ZZint)sizeof(ZZint))i=u.i;
    else if(n==(ZZint)sizeof(ZZlong))i=(ZZint)(u.l);
    // else if(n==(int)sizeof(short int))i=u.s;
    else { ZZmsg(50); i=0; }
    return(i);
}
/* --------------------------------------------------------------- */
/* Convert a pointer to an unsigned long integer */
#ifdef ZZ_ANSI
unsigned ZZlong ZZptrToLong(char *p)
#else

unsigned ZZlong ZZptrToLong(p)
char *p; /* given pointer */
#endif
{
    union ZZUNI u;

    u.ul=0;
    u.p=p;
    return(u.ul);
}
/* --------------------------------------------------------------- */
/* Convert a pointer to ZZsize, essentially to size_t */
#ifdef ZZ_ANSI
ZZsize ZZptrToSize(char *p)
#else

ZZsize ZZptrToSize(p)
char *p; /* given pointer */
#endif
{
    union ZZUNI u; void *v;

    v=(void*)p;

    u.s=0;
    u.p=v;
    return(u.s);
}
/* --------------------------------------------------------------- */
/* Convert ZZsize (essentially size_t) to a pointer */
#ifdef ZZ_ANSI
char *ZZsizeToPtr(ZZsize s)
#else

char *ZZsizeToPtr(s)
ZZsize s; /* given pointer */
#endif
{
    union ZZUNI u;

    u.p=NULL;
    u.s=s;
    return((char*)(u.p));
}
/* --------------------------------------------------------------- */
/* Convert an integer into a pointer - this should always work, since
 * an integer is always smaller than pointer.
 * Most compilers accept this as simply  
 * char *c; int i; c=(char *)i;
 * but ZORTECH flags this as an error.
 */
#ifdef ZZ_ANSI
char *ZZintToPtr(ZZint i)
#else

char *ZZintToPtr(i)
int i;
#endif
{
    union ZZUNI u;
    ZZint n;

    n=(ZZint)sizeof(char *);
    if(n==(ZZint)sizeof(ZZint))u.i=i;
    else if(n==(ZZint)sizeof(ZZlong))u.l=(ZZlong)i;
    // else if(n==(int)sizeof(short int))u.s=(short)i;
    else {ZZmsg(51); u.p=NULL;}
    return((char *)(u.p));
}
/* --------------------------------------------------------------- */
/* Convert a long into integer - check on size and print an error message
 * if there is a conflict
 */
#ifdef ZZ_ANSI
ZZint ZZlongToInt(char *label,ZZlong l)
#else

ZZint ZZlongToInt(label,l)
char *label; /* label to print if error occurs */
ZZlong l; /* long number to be converted */
#endif
{
    char *p,*s;
    ZZint m,n,i,r;

    m=(ZZint)sizeof(ZZint);
    n=(ZZint)sizeof(ZZlong);
    p=(char *)(&r);
    s=(char *)(&l);
    for(i=0;i<n;i++){
#ifdef DOS
        if(i<m)p[i]=s[i]; /* byte to copy */
        else if(s[i]!='\0'){ZZmsgSL(0,label,l); break;}
#else
        if(i<m)p[m-1-i]=s[n-1-i]; /* byte to copy */
        else if(s[n-1-i]!='\0'){ZZmsgSL(0,label,l); break;}
#endif
    }
    return(r);
}
/* --------------------------------------------------------------- */
/* read a set of names from the input file, and allocate space for them */
#ifdef ZZ_ANSI
void ZZgetNames(FILE *file,char **arr,ZZint num)
#else


void ZZgetNames(file,arr,num)
FILE *file; /* file from which to read */
char *arr[]; /* array of pointers to the resulting names */
ZZint num;    /* number of names to read from each line */
#endif
{
    ZZint i,n;
    char *p,*s;
    ZZvoidS *ZZFUN_galloc();

    for(i=0;i<num;i++)arr[i]=(char *)NULL;
    if(fgets(ZZbuff,ZZ_BUFS,file)){
	for(p=ZZbuff,i=0;i<num;i++,p=s+1){
            for(;*p==' ';p++)continue;
            for(s=p;*s!=' ';s++){if(*s=='\n' || *s=='\r')break;};
            *s='\0';
	    n=(int)strlen(p);
	    arr[i]=(char*)ZZgalloc(n+1);
	    strcpy(arr[i],p);
	}
    }
}
/* --------------------------------------------------------------- */
/* internal allocation for Organized C, all data taken from one large
 * chunk of memory. There is no mechanism for keeping free objects.
 * All new objects come from the common pool. */
#ifdef ZZ_ANSI
ZZvoidS *ZZnewBlock(unsigned ZZint size)
#else


ZZvoidS *ZZnewBlock(size)
unsigned ZZint size;
#endif
{
    unsigned ZZint k;
    ZZvoidS *res;

    k=sizeof(char *);
    size=k*((size+k-1)/k); /* rounds up size to (int)sizeof(char *) */
    res=(ZZvoidS *)ZZmemPool;
    ZZmemPool=ZZmemPool+size;
    if((ZZptrIntType)ZZmemPool <= (ZZptrIntType)ZZmemEnd)return(res);
    ZZmsgSS(20,ZZmemStart,ZZmemEnd);
    ZZmemSwitch=0; ZZmemStart=(char *)NULL;
    return((void *)NULL);
}
/* --------------------------------------------------------------- */
/* When running memory blasting or big-block saving, freed
 * arrays are not recycled. The free function calls ZZdelBlock() 
 * which simply does nothing.
 * Free lists of single objects by class are optional.
 * Users are adviced to keep their own garbage collection.
 */
#ifdef ZZ_ANSI
void ZZdelBlock(char *ptr) { ptr=ptr; }
#else


void ZZdelBlock(ptr) char *ptr; { ptr=ptr; }
#endif
/* --------------------------------------------------------------- */
/* interactive walk through the data. Stack objList keeps the whole
 * history of the walk, and allows to move backward.
 * Commands: type order index of the pointer, starting with 1
 *           0=exit, -1 go backward one step
 */
#ifdef ZZ_ANSI
void ZZdebPrt(char *p,char *tp,struct ZZstrLST *sL,char **pL,ZZint *pC)
{
    ZZvoidS *ZZnewObj(ZZint size,ZZint ini);
    ZZint ZZdelObj(char *ptr);
    ZZint ZZioFunction(FILE *fp,ZZint mode,ZZint type,char *p,ZZint strSz);
#else


void ZZdebPrt(p,tp,sL,pL,pC)
char *p; /* pointer to the starting object */
char *tp; /* type of the object as a string */
struct ZZstrLST *sL; /* internal type table */
char **pL; /* list of pointer names for all objects */
ZZint *pC;   /* ZZnxtType */
{
    ZZvoidS *ZZnewObj();
    ZZint ZZdelObj();
    ZZint ZZioFunction();
XXX
#endif
    struct objList {
        char *obj; /* object */
        ZZint type;  /* type index */
        struct objList *next; /* linked list, NULL end */
    };
    struct objList *start,*s;
    struct ZZarray *ap;
    char **pp,*nn;
    ZZint i,type; int ii;

    ZZdebFLG=1; /* turn on print of names in printouts */
#ifdef Windows64
    s=new objList;
#else
    s=(struct objList *)ZZnewObj((ZZint)sizeof(struct objList),0);
#endif
    if(!s){ZZmsgS(1," browser internal stack"); return;}
    s->obj=p;
    s->type=ZZfindType(sL,tp);
    s->next=(struct objList *)NULL;
    start=s;
    for(;s;){
        type=s->type;
        nn=ZZfindName(sL,type);
#ifdef LARGE_POINTE
#ifdef Windows64
        printf("\nobject=%I64u type=%s typeInd=%I64d:\n",(unsigned ZZlong)(s->obj),nn,type);
#else
        printf("\nobject=%lu type=%s typeInd=%d:\n",s->obj,nn,type);
#endif
#else
        printf("\nobject=%d type=%s typeInd=%d:\n",s->obj,nn,type);
#endif
        ptrDisp(stdout,s->obj,type,sL,pL,pC);
        if(type>=0)(void)ZZioFunction(stdout,3,type,s->obj,0);
        printf("select pointer(-n retrace n steps, 0 exit):");
        while(!fgets(ZZbuff,ZZ_BUFS,stdin))continue;
        sscanf(ZZbuff,"%d",&ii);
	i=(ZZint)0 + ii;
        if(i==0 && type!=(-4))break;

        else if(i<0){ /* go back i steps */
            for( ;i<0;i++){
                s=s->next;
                if(!s)break;
#ifdef Windows64
                delete start;
#else
                ZZdelObj((char *)start);
#endif
                start=s;
            }
        }

        else {
            if(type>=0 && sL[type].numPtr>=i){
                pp=(char **)((s->obj)+sL[type].start);
                pp+=(i-1); /* user entry starts with 1, not 0 */
                if(*pp){
#ifdef Windows64
	            s=new objList;
#else
                    s=(struct objList *)ZZnewObj((ZZint)sizeof(struct objList),0);
#endif
                    if(!s){ZZmsgS(1," browser internal stack"); return;}
                    s->obj=(*pp);
                    s->type=pC[sL[type].ptrInd+i-1];
                    s->next=start;
                    start=s;
                }
                else printf("\n***** cannot follow NULL pointer\n");
            }
            else if(type==(-4)){
                ap=(struct ZZarray *)(s->obj);
                if(!ap || !(ap->array)) printf("\n**** array not formed yet\n");
                else if(i>=0 && i<ap->num){
#ifdef Windows64
	            s=new objList;
#else
                    s=(struct objList *)ZZnewObj((ZZint)sizeof(struct objList),0);
#endif
                    if(!s){ZZmsgS(1," browser internal stack"); return;}
                    s->obj=(ap->array)+i*(ap->size);
                    s->next=start;
                    start=s;
                    if(ap->targType<0){
                        s->type=ap->strType;
                    }
                    else {
                        s->type=ap->targType;
                        pp=(char**)(s->obj);
                        if(*pp)s->obj=(*pp);
                        else printf("\n***** this slot is empty\n");
                    }
                }
                else printf("\n***** array index out of range, try again\n");
            }
            else if(type<0){
printf("negative type objects need special print\n");
            }
            else {
printf("\n***** pointer index out of range, try again\n");
            }
        }
    }
    /* clear out internal stack */
    for( ;start;start=s){
        s=start->next;
#ifdef Windows64
	delete start;
#else
        (void)ZZdelObj((char *)start);
#endif
    }
    ZZdebFLG=0;
}
/* --------------------------------------------------------------- */
/* display pointers of an object, including the labels */
#ifdef ZZ_ANSI
static void ptrDisp(FILE *fp,char *obj,ZZint type,
                                struct ZZstrLST *sL,char **pL,ZZint *pC)
#else


static void ptrDisp(fp,obj,type,sL,pL,pC)
FILE *fp;  /* file where to print */
char *obj; /* pointer to the beginning of the object */
ZZint type;  /* type of the object */
struct ZZstrLST *sL; /* internal type table */
char **pL; /* list of pointer names for all objects */
ZZint *pC;   /* ZZnxtType */
#endif
{
    char **pp,*n1,*n2;
    ZZint i,j,k,ht,tp;
    struct ZZarray *a;

    if(type>=0){
      for(i=0,pp=(char **)(obj+sL[type].start),k=sL[type].ptrInd;
                k<sL[type].numPtr && i<sL[type].numPtr  // JSfix Nov.16/00
                && ((pL[k])[0]=='a' || (pL[k])[0]=='A'); pp++,i++,k++){
        j=pC[k];
        if(j>=0){n1=(char*)"->";n2=sL[j].strName;}
        else if(j==(-1)){n1=(char*)" name=";n2= *pp;}
        else if(j==(-2)){n1=(char*)"->";n2=(char*)"property";}
        else if(j==(-4)){
            n1=(char*)"->";
            a=(struct ZZarray*)(*pp);
            if(!a)n2=(char*)"array/hash table not formed yet";
            else {
                ht=a->targType;
                if(ht<=(-2))n2=(char*)"array"; else n2=(char*)"hash";
            }
        }
        else {n1=(char*)"->";n2=(char*)"no access";}
        strcpy(ZZbuff,&((pL[k])[3]));
        for(j=0;ZZbuff[j]!='\0' && ZZbuff[j]!='[';j++)continue;
        ZZbuff[j]='\0';
        
#ifdef LARGE_POINTER
        fprintf(fp,"%d: %lu %s%s%s\n",i+1,*pp,ZZbuff,n1,n2);
#else
        fprintf(fp,"%d: %d %s%s%s\n",i+1,*pp,ZZbuff,n1,n2);
#endif
      }
    }
    else if(type== -4){
        a=(struct ZZarray *)obj;
printf("num=%d waterM=%d type=%d size=%d incr=%d hsh=%d\n",a->num,a->waterM,a->strType,a->size,a->incr,a->targType);
        fprintf(fp,"     size: %d\n",a->num);
        fprintf(fp,"increment: %d\n",a->incr);
        fprintf(fp,"waterMark: %d\n",a->waterM);
        ht=a->targType;
        if(ht<= -2)n2=(char*)"array"; else n2=(char*)"hash table";
#ifdef LARGE_POINTER
        fprintf(fp,"start: %lu %s\n",a->array,n2);
#else
        fprintf(fp,"start: %d %s\n",a->array,n2);
#endif
        if(ht<= -2)tp=a->strType; else tp=a->targType;
        if(tp<0)n2=(char*)"char*"; else n2=sL[tp].strName;
        fprintf(fp,"type: %s\n",n2);
    }
    else fprintf(fp,"this object cannot be displayed\n");
}
/* --------------------------------------------------------------- */
/* bit-wise copy of objects, from p to s */
#ifdef ZZ_ANSI
void ZZbitCopy(ZZint size,char *p,char *s)

#else
void ZZbitCopy(size,p,s)
ZZint size; /* size of the object */
char *p,*s; /* starting addresses */
#endif
{
    ZZint i;
    for(i=0; i<size; i++,p++,s++)(*s)=(*p);
}
/* --------------------------------------------------------------- */
/* system level read, write, open, and close
 * with consideration of UNIX, VMS and DOS differences */

/* ZZopen returns the file pointer (may hide file handle), NULL=error */
#ifdef ZZ_ANSI
FILE *ZZopen(const char *fileName,const char *mode)
{
#ifndef ZZcplus
#ifndef MICROSOFT
    FILE *fopen(char *fn,const char *md);
#endif
#endif
#else


FILE *ZZopen(fileName,mode)
char *fileName;
char *mode; /* can be a string w r rw */
{
    FILE *fopen();
#endif
    ZZint i,access;
    char aMode[4];
    FILE *fp;

#ifdef ZZ_ANSI
#ifdef MICROSOFT
    ZZint msfOpen(const char *fileName,ZZint access);
#ifndef ZZcplus
#ifdef MICROSOFT6
    ZZint open(char *, ZZint);
#else
    ZZint open(const char *, ZZint, ...);
#endif                      /* MICROSOFT6 */
#ifndef ZORTECH
    ZZint creat(const char *name,ZZint mode);
#endif                      /* ZORTECH */
#endif                      /* ZZcplus */
#endif                      /* MICROSOFT */
#else                       /* ZZ_ANSI */
    ZZint msfOpen();
#ifndef VMS
#ifndef SUN3_0
    ZZint creat();
    ZZint open();
#endif                      /* SUN3_0 */
#endif                      /* VMS */
#endif                      /* ZZ_ANSI */

#ifdef TURBOC
#ifdef ZZ_ANSI
#ifndef ZZcplus
    ZZint _open(char *name, ZZint mode),_creat(char *name,ZZint mode);
#endif
#else
    ZZint _open(),_creat();
#endif
#endif

    /* permit user-controlled IO */
    if(ZZdiskIO==2 && ZZuserOpen && ZZuserClose)return(ZZuserOpen(fileName,(char*)mode));

    fp=NULL;
    i=0;
    if(!strcmp(mode,"r"))access=O_RDONLY;
    else if(!strcmp(mode,"w"))access=O_WRONLY;
    else if(!strcmp(mode,"wr"))access=O_RDWR;
    else if(!strcmp(mode,"rw"))access=O_RDWR;
    else {ZZmsgS(19,mode); i= -1;} /* wrong file access mode=%s */
    if(i==0){
        if(ZZdiskIO){
            strcpy(aMode,mode);
#ifdef DOS
            strcat(aMode,"b");
#endif
#ifdef MAC
            strcat(aMode,"b");
#endif
            fp=fopen(fileName,aMode);
        }
        else {
#ifdef TURBOC
            i= _open(fileName,access);
            if(i<0 && access!=O_RDONLY) i= _creat(fileName,0);
#endif
#ifdef MICROSOFT
            i= msfOpen(fileName,access);
            if(i<0 && access!=O_RDONLY){
                i= creat(fileName,_S_IREAD | _S_IWRITE);
                if(i<0)ZZmsgS(20,fileName); /* problem to create file  */
                else {
                    fp=handleToPointer(i);
                    (void)ZZclose(fp);
                }
                /* QuickC Ver.2.0 has problem after create only */
                i= msfOpen(fileName,access);
            }
#endif
#ifndef MAC
#ifdef UNIX
            i= open(fileName,access);
            if(i<0 && access!=O_RDONLY) i= creat(fileName,0700);
#endif
#endif
#ifdef MAC
            i=open(fileName,access | O_BINARY);
            if(i<0 && access!=O_RDONLY)
                i=open(fileName,access|O_TRUNC|O_CREAT|O_BINARY);
#endif
#ifdef VMS
            i= open(fileName,access);
            if(i<0 && access!=O_RDONLY) i= creat(fileName,0700);
#endif
            fp=handleToPointer(i);
        }
    }
    if(!fp)ZZmsgS(0,fileName); /* problem to open file  */
    return(fp);
}
/* ---------------------------------------------------------------- */

#ifdef MICROSOFT
/* Microsoft and Zortech open a file differently ? */
#ifdef ZZ_ANSI
ZZint msfOpen(const char *fileName,ZZint access)
{
#ifndef ZZcplus
#ifdef MICROSOFT6
    ZZint open(char *,ZZint);
#else
    ZZint open(const char *,ZZint,...);
#endif
#endif
#else


ZZint msfOpen(fileName,access)
char *fileName;
ZZint access;
{
    ZZint open();
#endif
    ZZint i;

#ifdef ZORTECH
    i= open(fileName,access|O_CREAT);
#else
    i= open(fileName,access|O_BINARY);
#endif
    return(i);
}
#endif
/* ---------------------------------------------------------------- */

/* ZZ read returns number of bytes actually read in, -1=error, 0=end of file */
#ifdef ZZ_ANSI
ZZint ZZread(FILE *fp,char *buff,ZZsize n,const char* errTxt)
{
#ifdef TURBOC
#ifndef ZZcplus
    ZZint _read(ZZint fh,char *bf,ZZint n);
#endif
#else
#ifdef MAC
#ifndef ZZcplus
  ZZint read(ZZint,char*,unsigned ZZlong);
#endif
#else
#ifndef ZZcplus
#ifdef HP
    ssize_t read(ZZint,void *,size_t);
#else
#ifndef MICROSOFT
#ifndef GNU
    size_t fread(void *bf,size_t sz, size_t nm,FILE *fp);
    ZZint read(ZZint fh,char *bf,ZZint n);
#endif
#endif
#endif /* HP */
#endif
#endif
#endif
#else
 

ZZint ZZread(fp,buff,n,errTxt)
FILE *fp; /* may hide the file handle for write() and read() */
char *buff; /* buffer to read in */
ZZsize n;      /* number of characters to read */
char *errTxt; /* text for the error message */
{
#ifdef TURBOC
    ZZint _read();
#else
    ZZint read();
#endif
#endif
    ZZint i,fh;

    /* permit user-controlled IO */
    if(ZZdiskIO==2 && ZZuserRead && ZZuserWrite)return(ZZuserRead(fp,buff,n));
   
    if(ZZdiskIO){
        i=(ZZint)fread(buff,n,1,fp);
        /* i = number of units. In old UNIX, a unit had to be (ZZint)sizeof(char *) */
        if(i>0)i=n;
    }
    else {
        fh=pointerToHandle(fp);
#ifdef TURBOC
        i= _read(fh,buff,n);
#else
        i= read(fh,buff,n);
#endif
    }
    if(i== -1){
	ZZmsgS(52,errTxt); /* "error in binary disk read */
	ZZerrFLG=ZZerrFLG|0100;
	exit(2); // possibly trow exception later.
    }
    else if((ZZsize)i!=n){
	ZZmsgSDD(1,errTxt,n,(ZZsize)i);  /* reading %d bytes, but only %d read in */
	ZZerrFLG=0100;
	exit(2); // possibly trow exception later.
    }

    return(i);
}
/* ---------------------------------------------------------------- */
/* ZZ write returns number of bytes writen */
#ifdef ZZ_ANSI
ZZint ZZwrite(FILE *fp,char *buff,ZZsize n,const char *errTxt)
{
#ifdef TURBOC
#ifndef ZZcplus
    ZZint _write(ZZint fh,char *bf,ZZint n);
#endif
#else
#ifdef MAC
#ifndef ZZcplus
  ZZint read(ZZint,char*,unsigned ZZlong);
#endif
#else
#ifndef ZZcplus
#ifdef HP
    ssize_t write(ZZint,const void *,size_t);
#else
#ifndef MICROSOFT
#ifndef GNU
    size_t fwrite(const void *bf,size_t sz, size_t nm,FILE *fp);
    ZZint write(ZZint fh,char *bf,ZZint n);
#endif
#endif
#endif /* HP */
#endif
#endif
#endif
#else


ZZint ZZwrite(fp,buff,n,errTxt)
FILE *fp;
char *buff; /* buffer to write in */
ZZsize n;      /* number of characters to write */
char *errTxt; /* text for the error message */
{
#ifdef TURBOC
    ZZint _write();
#else
    ZZint write();
#endif
#endif
    ZZint i,fh;

    /* permit user-controlled IO */
    if(ZZdiskIO==2 && ZZuserRead && ZZuserWrite){
	i=ZZuserWrite(fp,buff,n);
    }
    else if(ZZdiskIO==1){
        i=(ZZint)fwrite(buff,n,1,fp);
        /* i = number of units. In old UNIX, a unit had to be (ZZint)sizeof(char *) */
        if(i>0)i=n;
    }
    else {
        fh=pointerToHandle(fp);
#ifdef TURBOC
        i= _write(fh,buff,n);
#else
        i= write(fh,buff,n);
#endif
    }

    if(i== -1){
	ZZmsgS(53,errTxt); /* "error in binary disk read */
	ZZerrFLG=ZZerrFLG|0100;
	exit(2); // possibly trow exception later.
    }
    else if((ZZsize)i!=n){
	ZZmsgSDD(2,errTxt,n,(ZZsize)i);  /* reading %d bytes, but only %d read in */
	ZZerrFLG=0100;
	exit(2); // possibly trow exception later.
    }
    return(i);
}
/* ---------------------------------------------------------------- */

/* ZZ close returns normally 0, -1=error */
#ifdef ZZ_ANSI
ZZint ZZclose(FILE *fp)
{
#ifdef TURBOC
#ifndef ZZcplus
    ZZint _close(ZZint fh);
#endif
#else
#ifndef SUNPLUS
#ifndef GNUPLUS
    int close(int fh);
    int fclose(FILE *fp);
#endif
#endif
#endif
#else


ZZint ZZclose(fp)
FILE *fp;
{
    ZZint fclose();
#ifdef TURBOC
    ZZint _close();
#else
    ZZint close();
#endif
#endif
    ZZint i,fh;

    /* permit user-controlled IO */
    if(ZZdiskIO==2 && ZZuserOpen && ZZuserClose)return(ZZuserClose(fp));

    if(ZZdiskIO){
        i=fclose(fp);
        if(i==EOF)i=(-1); else i=0;
    }
    else {
        fh=pointerToHandle(fp);
#ifdef TURBOC
        i= _close(fh);
#else
        i= close(fh);
#endif
    }
    if(i!=0)ZZmsg(46); /* problem to close file */
    return(i);
}
/* ----------------------------------------------------------------------- */
/* transfer of the user-defined IO functions to the library */
#ifdef ZZ_ANSI
void ZZinstallUserIO(ZZ_USER_OPEN o,ZZ_USER_READ r,ZZ_USER_WRITE w,ZZ_USER_CLOSE c)

#else 
void ZZinstallUserIO(o,r,w,c)
FILE *(*o)();
ZZint   (*r)();
ZZint   (*w)();
ZZint   (*c)();
#endif
{
    ZZuserOpen=o; ZZuserRead=r; ZZuserWrite=w; ZZuserClose=c;
}
/* ----------------------------------------------------------------------- */
#ifdef ZZ_ANSI
FILE *handleToPointer(ZZint fh)
#else


FILE *handleToPointer(fh)
ZZint fh;    /* given file handle, -1 means unassigned or error */
#endif
/* return NULL means unassigned or error */
{
    union ZZUNI u;

    u.fp=NULL;
    u.i=fh+1;
    return(u.fp);
}
/* ----------------------------------------------------------------------- */
#ifdef ZZ_ANSI
ZZint pointerToHandle(FILE *fp)
#else


ZZint pointerToHandle(fp)
FILE *fp; /* given file pointer, NULL means unassigned or error */
#endif
/* return -1 means unassigned or error */
{
    union ZZUNI u;

    u.fp=fp;
    return(u.i-1);
}
/* ----------------------------------------------------------------------- */
