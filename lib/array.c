/****************************************************************/
/*							      	*/
/*   Copyright (C) 1988 1989             			*/
/*	Code Farms Inc.,  All Rights Reserved.			*/
/*							  	*/
/****************************************************************/

#define zzLIB
#include <stdio.h>
#include "environ.h"
#include "types.h"
#include "heading.h"
#include "array.h"
#include "bind.h"
#include "offset.h"
#include "msgs.h"

#define UNC unsigned char
extern int ZZinhFLG; /* defined in zzincl.h */

#ifdef ZZ_ANSI
typedef ZZint (*SRTFUN)(const void *p1,const void *p2);
typedef ZZint (*INDFUN)(char *p1,ZZint i);
static void ZZexHeap(UNC *,UNC *,ZZint);
static void markBitsArray(ZZarray *,ZZint);
#else
static void ZZexHeap();
static void markBitsArray();
#endif
/* ----------------------------------------------------------------------- */
/* Allocate and initialize an array, including the header */
#ifdef ZZ_ANSI
ZZarray *ZZfoArr(ZZint num,ZZint incr,ZZint objSize,ZZint strType,const char* targName,
                     struct ZZstrLST *strList,const char *sample) 
{
    ZZint ZZdelObj(char *p);
    ZZvoidS *ZZnewObj(ZZint i,ZZint ini);
    ZZint ZZfindType(ZZstrLST*,const char*);
#else


ZZarray *ZZfoArr(num,incr,objSize,strType,targName,strList,sample)
ZZint num; /* initial number of objects in the array */
ZZint incr; /* increment: 0=fixed, >0 add, <0 multiply */
ZZint objSize; /* size of one object in bytes */
ZZint strType; /* name of object type in the array */
const char *targName; /* hash target type, -2 for regular arrays */
struct ZZstrLST *strList;
char *sample; /* one sample object */
{
    ZZint ZZdelObj();
    ZZvoidS *ZZnewObj();
    ZZint ZZfindType();
#endif
    ZZint n,newTp,simple;
    UNC *p,*r,*rr;
    ZZarray *a;

    // printf("??? enter foArr num=%d incr=%d objSize=%d strType=%d targName=%s\n",num,incr,objSize,strType,targName);
    a=(ZZarray *)ZZnewObj((ZZint)sizeof(ZZarray),0);
    if(!a)return((ZZarray *)NULL);
    n=num*objSize;
    a->array=(char *)ZZnewObj(n,1);
    if(!(a->array)){ZZdelObj((char *)a); return((ZZarray *)NULL);}
    a->num=num;
    a->incr=incr;
    a->size=objSize;
    a->waterM= -1;

    /* IMPORTANT: a->strType and a->targType needed only when saving to disk */
    a->strType=newTp=strType;
    
    a->targType=ZZfindType(strList,targName);
    if(a->targType<-1)a->targType= -2; /* not a pointer array */
    // printf("??? mid foArr num=%d incr=%d objSize=%d strType=%d targType=%d\n",num,incr,objSize,a->strType,a->targType);
    
    p=(UNC *)(a->array);
    rr=p+n;
    simple=1;
#ifdef ZZcplus
    ZZint i;
    if(ZZinhFLG && a->strType>=0){ /* initialize also virt.functions */
        for(r=p;r<rr;r+=objSize){ /* replicate basic object */
            for(i=0;i<objSize;i++)r[i]=sample[i];
        }
        simple=0;
    }
#endif
    if(simple) for(r=p;r!=rr;r++)(*r)='\0';
    if(ZZmemSwitch==2)markBitsArray(a,1);
    return(a);
}
/* ----------------------------------------------------------------------- */
/* mark or unmark bits in the bitmap */
#ifdef ZZ_ANSI
static void markBitsArray(ZZarray *a, ZZint val)
{
    ZZint ZZbindPtrs(char *ptr,ZZint tp,ZZint sz,ZZint vUpd,ZZint val);
    void ZZmarkPtr(char **ptr,ZZint val);
#else


static void markBitsArray(a,val)
ZZarray *a; /* array header */
ZZint val;    /* value to be marked, 0 or 1 */
{
    ZZint ZZbindPtrs();
    void ZZmarkPtr();
#endif
    char **p;
    ZZint i,n;

    if(ZZmemSwitch==2){ /* is bitmap used? */
        ZZmarkPtr(&(a->array),val);
        if(a->strType>=0)
            ZZbindPtrs(a->array,a->strType,(a->size)*(a->num),1,val);
        p=(char **)(a->array);
        if((a->strType== -5 || a->strType== -1)&& p){ /* array of poZZinters */
            for(i=0, n=a->num; i<n; i++, p++)ZZmarkPtr(p,val);
        }
        
    }
}
/* ----------------------------------------------------------------------- */
/* Disconnect and free a hash table. This consists essentially
 * of two steps: first disconnect chains within individual slots,
 * then free the hash array */
#ifdef ZZ_ANSI
ZZarray *ZZfrHash(ZZarray *ah, unsigned ZZint offset)
{
    ZZint ZZdelObj(char *);
#else


ZZarray *ZZfrHash(ah,offset)
ZZarray *ah; /* array header */
unsigned ZZint offset; /* offset of the 'next' poZZinter within the object */
/* returns always NULL */
{
    ZZint ZZdelObj();
#endif
    ZZint i,n;
    char **p,**r,*t,*tt;

    if(ZZmemSwitch==2)markBitsArray(ah,0);

    /* disconnect the chain for each slot */
    p=(char**)(ah->array);
    n=ah->num;
    for(i=0;i<n;i++){
        for(t=p[i];t;t=tt){ /* ring of objects in the same slot */
            r=(char**)(t+offset); tt=(*r);
            *r=(char *)NULL;
            if(tt==p[i])tt=(char *)NULL;
        }
    }

    /* deallocate the array and the header */
    if(ah->array)ZZdelObj((char *)(ah->array)); 
    ZZdelObj((char *)ah); 
    return(NULL);
}
/* ----------------------------------------------------------------------- */
/* Disconnect and free an array, including the header.
 * The function checks ZZ_EXT_ for objects in the array, and does not
 * free the array if not all objects disconnected */
#ifdef ZZ_ANSI
ZZarray *ZZfrArr(ZZarray *ah,char *strType,struct ZZstrLST *strList)
{
    ZZint ZZdeal(char *a,struct ZZstrLST *s,char *t,ZZint n,ZZint z,ZZint m);
    ZZint ZZdelObj(char *p);
#else


ZZarray *ZZfrArr(ah,strType,strList)
ZZarray *ah; /* array header */
char *strType; /* type name of the object in the array */
struct ZZstrLST *strList; /* list of registered object types */
/* returns NULL if freed, returns ah and gives warning msg if not freed */
{
    ZZint ZZdeal();
    ZZint ZZdelObj();
#endif
    ZZint i;

    if(ZZmemSwitch==2)markBitsArray(ah,0);

    i=ZZdeal(ah->array,strList,strType,ah->num,ah->size,0);
    if(i)return(ah);
    ZZdelObj((char *)ah);
    return((ZZarray *)NULL);
}
/* ----------------------------------------------------------------------- */
/* increase the size of the array until the given index is included */
/* 'sample' is a sample object with NULL DOL poZZinters, and properly set */
/* virtual function poZZinters. */
/* ----------------------------------------------------------------------- */
#ifdef ZZ_ANSI
ZZint ZZupArr(ZZarray *ah,ZZint ind,char *sample)
{
    ZZvoidS *ZZnewObj(ZZint s, ZZint ini);
    ZZint ZZdelObj(char *p);
#else


ZZint ZZupArr(ah,ind,sample)
ZZarray *ah; /* array header */
ZZint ind;            /* given index to be tested */
char *sample;
/* returns: 
 *         -1=array reallocated,
 *          0=keeing old array,
 *          1=negative index, or out of range on a fixed array
 *          2=unable to allocate enough memory 
 *          3=this array has not been formed yet */
{
    ZZvoidS *ZZnewObj();
    ZZint ZZdelObj();
#endif
    ZZint k,n,objSize,objType,simple;
    UNC *p,*pp,*s;
    char *nw;

    if(!ah){
        ZZmsg(37); /* error: attempt to access array without forming it first */
        ZZerrFLG=04;
        return(3);
    }
    if(ind<0){
        ZZmsgD(7,ind); /* array error - negative index */
        ZZerrFLG=02;
        return(1);
    }
    if(ind<ah->num)return(0);
    k=ah->incr;
    if(k==0 || k==(-1)){
        ZZmsgDD(1,ah->num,ind); /* array size=.. index=.. out of range */
        ZZerrFLG=02;
        return(1);
    }
    else if(k>0){ for(n=ah->num;n<=ind;n=n+k){};}
    else {k= -k; for(n=ah->num;n<=ind;n=n*k){};}
    k=n;

    /* allocate the new array, if not enough space, try halving */
    objSize=ah->size;
    objType=ah->strType;
    for(nw=(char *)NULL; k>ind; k=ind+(k-ind)/2){
        nw=(char *)ZZnewObj(objSize*k,0);
        if(nw)break;
    }
    if(!nw){
        ZZmsgD(8,ind); /* unable to allocate array, index=.. */
        ZZerrFLG=01;
        return(2);
    }
    
    /* copy the old array ZZinto the new aray */
    n=objSize*(ah->num);
    for(p=(UNC *)nw, pp=p+n, s=(UNC *)(ah->array); p<pp; p++, s++)(*p)=(*s);
    /* previous loop leaves p at the first new object */
    n=objSize*k;
    pp=(UNC *)nw+n; /* upper limit of the new area */

    simple=1;
#ifdef ZZcplus
    { ZZint i; UNC *r;
        if(ZZinhFLG){ 
            /* copy the sample object from p up */
            for(r=p+objSize;r<pp;r+=objSize){ /* replicate basic object */
                for(i=0;i<objSize;i++)r[i]=sample[i];
            }
            simple=0;
        }
    }
#endif
    if(simple)for( ;p<pp;p++)(*p)='\0';

    /* free the old array */
    if(ZZmemSwitch==2)markBitsArray(ah,0);
    ZZdelObj((char *)(ah->array));

    /* update the header */
    ah->array=nw;
    ah->num=k;
    if(ZZmemSwitch==2)markBitsArray(ah,1);
    return(-1);
}
/* ----------------------------------------------------------------------- */
/* exchange two general objects */
#ifdef ZZ_ANSI
static void ZZexHeap(UNC *a,UNC *b,ZZint size)
#else


static void ZZexHeap(a,b,size)
UNC *a,*b; /* beginning of the two objects */
ZZint size;   /* size of the objects in bytes */
#endif
{
    UNC *aa,s;

    aa=a+size;
    for(;a<aa;a++,b++){s=(*a); (*a)=(*b); (*b)=s;}
    return;
}
/* ----------------------------------------------------------------------- */
/* array used as a binary heap: push element upward */
#ifdef ZZ_ANSI
ZZint ZZupHeap(ZZarray *ah,ZZint ind,SRTFUN sortFun,ZZTheapBck bck)
{
#else


ZZint ZZupHeap(ah,ind,sortFun,bck)
/* returns the index to which the element moves */
ZZarray *ah; /* array header for the heap */
ZZint ind; /* index of the element to be pushed */
ZZint (*sortFun)(); /* compare function to sort the heap */
void (*bck)();    /* call back function for the heap, may be NULL */
{
#endif
    ZZint i,j,ii,jj,k,size;
    char *p1,*p2,*a;

    a=ah->array;
    size=ah->size;

    k=ind;
    for(i=ind, ii=ind*size; i>0; i=j, ii=jj){
        j=(i-1)/2; jj=j*size; /* j is parent of i */
        p1= &(a[jj]);
        p2= &(a[ii]);
        if((*sortFun)(p1,p2)<=0)break;
        ZZexHeap((UNC *)p1,(UNC *)p2,size);
        if(bck) (*bck)((void*)p1,j);
        if(bck) (*bck)((void*)p2,i);
        k=j;
    }
    return(k);
}
/* ----------------------------------------------------------------------- */
/* array used as a binary heap: push element downward */
#ifdef ZZ_ANSI
ZZint ZZdownHeap(ZZarray *ah,ZZint ind,SRTFUN sortFun,ZZTheapBck bck)
{
#else


ZZint ZZdownHeap(ah,ind,sortFun,bck)
/* returns the index to which the element moves */
ZZarray *ah; /* header for the array that forms the heap */
ZZint ind; /* index of the element to be pushed */
ZZint (*sortFun)(); /* compare function to sort the heap */
void (*bck)();    /* call back function for the heap, may be NULL */
{
#endif
    ZZint i,j1,j2,ii,jj1,jj2,k,n,size;
    char *p,*c1,*c2,*a;

    a=ah->array;
    n=ah->waterM;
    size=ah->size;

    k=ind;
    for(i=ind, ii=ind*size; ; i=j1, ii=jj1){
        j1=i+i+1; j2=j1+1; /* j1 and j2 are children of i */
        if(j1>n)break;
        jj1=j1*size; jj2=jj1+size;
        p= &(a[ii]);
        c1= &(a[jj1]);
        c2= &(a[jj2]);
        if(j2<=n){ if((*sortFun)(c1,c2)>0){ c1=c2; j1=j2; jj1=jj2; } }
        /* j1 is now the smaller of the two children */
        if((*sortFun)(p,c1)<=0)break;
        ZZexHeap((UNC *)p,(UNC *)c1,size);
        if(bck) (*bck)((void*)p,i);
        if(bck) (*bck)((void*)c1,j1);
        k=j1;
    }
    return(k);
}
/* ----------------------------------------------------------------------- */
/* Reset hash table to a new size, and reload the new table.
 * If there is any problem, such as in allocation, leave the old
 * table in place, issue an error message, and set the error flag.
 */
#ifdef ZZ_ANSI
ZZint ZZupHash(ZZarray *ah,ZZint size,ZZint offset,INDFUN indF)
{
    void ZZaddSlot(char **n,ZZint k,char *t,ZZint off),*ZZnewObj(ZZint s,ZZint ini);
    ZZint ZZdelObj(char *p);
#else


ZZint ZZupHash(ah,size,offset,indF)
/* returns: 0=normal, 1=table not replaced */
ZZarray *ah;     /* array header for the current hash table */
ZZint size;        /* requested size for the new table */
ZZint offset;      /* offset to the 'next' poZZinter inside same slot */
ZZint   (*indF)(); /* gets a slot index for a given object */
{
    void ZZaddSlot(),*ZZnewObj();
    ZZint ZZdelObj();
#endif
    ZZint i,k;
    char **nw,**p,**r,*t,*tt;

    if(!ah){
        ZZmsg(38); /* cannot reset a hash table without forming it first */
        ZZerrFLG=ZZerrFLG|04;
        return(1);
    }

    /* allocate the new table */
    nw=(char**)ZZnewObj(size*(ZZint)sizeof(char *),1);
    if(!nw){
        ZZmsg(39); /* unable to allocate a new hash table, old one remains */
        ZZerrFLG=ZZerrFLG|01;
        return(1);
    }
    
    /* copy the old array ZZinto the new aray */
    p=(char**)(ah->array);
    for(i=0;i<ah->num;i++){
        for(t=p[i];t;t=tt){ /* ring of objects in the same slot */
            r=(char**)(t+offset); tt=(*r);
            k=(*indF)(t,size);
            ZZaddSlot(nw,k,t,offset);
            if(tt==p[i])tt=(char *)NULL;
        }
    }
        
    /* free the old array */
    if(ZZmemSwitch==2)markBitsArray(ah,0);
    ZZdelObj((char *)(ah->array));

    /* update the header */
    ah->array=(char *)nw;
    ah->num=size;
    if(ZZmemSwitch==2)markBitsArray(ah,1);
    return(0);
}
/* ----------------------------------------------------------------------- */
/* add a new object to index i of the hash table */
#ifdef ZZ_ANSI
void ZZaddSlot(char **a,ZZint i,char *obj,ZZint off)
#else


void ZZaddSlot(a,i,obj,off)
char *a[]; /* hash table, don't worry about its size */
ZZint i;     /* index of the slot, given */
char *obj; /* given object */
ZZint off;   /* offset of the 'next' poZZinter inside the object */
#endif
{
    char **p,**s;

    p=(char**)(obj+off);
    if(a[i]){
        s=(char**)(a[i]+off);
        *p= *s;
        *s=obj;
    }
    else {
        a[i]=obj;
        *p=obj;
    }
}
/* ----------------------------------------------------------------------- */
/* universal hash function for a string, */
/* Algorithm by Sedgwick */
/* ----------------------------------------------------------------------- */
#ifdef ZZ_ANSI
ZZint ZZhashStr(char *key,ZZint tabSize)
{
#else


ZZint ZZhashStr(key,tabSize)
char *key;   /* given string as a key */
ZZint tabSize; /* size of the hash table - total index range */
{
#endif
    ZZint i,hash,length;

    hash=0; 
    length=strlen(key);
    for(i=0; i<length; i++){
        hash=(117*hash + key[i])%tabSize;
    }
    return hash;
}

#ifdef HISTORY
/* old algorithm by Kedem, modified by golden ratio */

    static double d={0.6125423371};
    double di;
    ZZint i,j,sum;

    sum=0;
    if(key){ /* protection */
        for(i=j=0; key[i]!='\0'; i++)sum+=(key[i]* ++j); 
        /* randomize the resulting code, using the gold ratio */
        di=d*sum;
        i=(ZZint)di;
        di=di-i;
        sum=(ZZint)(di*tabSize);
    }
    return(sum);
#endif // HISTORY
/* ----------------------------------------------------------------------- */
/* universal hash function for an ZZinteger,
 * multiplicative algorithm with golden ratio (Standish, Knuth).
 * Negative ZZinteger produces the same result as its absolute value.
 */
#ifdef ZZ_ANSI
ZZint ZZhashInt(ZZint key,ZZint tabSize)
#else


ZZint ZZhashInt(key,tabSize)
ZZint key;     /* given ZZinteger as a key */
ZZint tabSize; /* size of the hash table - total index range */
#endif
{
    static double d={0.6125423371};
    double di;
    ZZint i;

    if(key<0)key= -key;
    di=d*key;
    i=(ZZint)di;
    di=di-i;
    i=(ZZint)(di*tabSize);
    return(i);
}
/* ----------------------------------------------------------------------- */
/* universal hash function for a poZZinter is the same os for an ZZinteger,
 * - see ZZhashInt() above - except the case when large poZZinters are
 * being used. Then the key must be treated as a ZZlong ZZinteger.
 */
#ifdef ZZ_ANSI
ZZint ZZhashPtr(char *key,ZZint tabSize)
#else


ZZint ZZhashPtr(key,tabSize)
char *key;     /* given ZZinteger as a key */
ZZint tabSize; /* size of the hash table - total index range */
#endif
{
    double d;
    ZZlong s,Key;
    ZZint i;
    Key=(ZZsigIntType)key;
    if(Key<0)Key= -Key;
    d=0.6125423371 * Key;
    s=(ZZlong)d;
    d=d-s;
    i=(ZZint)(d*tabSize);
    if(i>=tabSize)i--; /* round-off protection */
    return(i);
}
/* ----------------------------------------------------------------------- */
/*              ZZhashSString() = HASH SHORT STRING                        */
/* ----------------------------------------------------------------------- */
/* Another hashing function for a string - supplied by Mark Bales,
 * orig.algorithm by prof.Ousterhaut, UC Berkeley.
 * Reason for ZZintroducing this second algorithm:
 * For large tables of short strings, Kedem's algorithm
 * results in a very poor distribution (few overcrowded and many
 * unused buckets).
 * Reasons for keeping both algorithms:
 * - It is not clear which of the two algorithms is faster.
 * - Replacing ZZhashStr() by the new algorithm would make existing
 *   databases invalid (data stored on disk depend on the hashing
 *   function.
 * Note that the code includes randomization by applying the golden
 * ratio to the ZZinteger representing the string, just as in ZZhashInt
 * Coded: Jiri Soukup, Feb.27/96
 */
#ifdef ZZ_ANSI
ZZint ZZhashSStr(char *key,ZZint tabSize)
{
#else


ZZint ZZhashSStr(key,tabSize)
char *key;   /* given string as a key */
ZZint tabSize; /* size of the hash table - total index range */
{
#endif
    static double d={0.6125423371};
    double di;
    ZZint i;
    unsigned ZZint res;
    unsigned char *s;

    /* 997 is a prime number suitable to randomize 1 byte (0-255) */
    for(s=(unsigned char *)key, res=0; *s; s++){
	res=res*997 + (*s);
    }

    /* randomize the resulting code, using the gold ratio */
    di=d*res;
    i=(ZZint)di;
    di=di-i;
    i=(ZZint)(di*tabSize);
    return(i);
}
