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
#include "property.h"
#include "bind.h"
#include "msgs.h"

/* Borland 3.0 has a bug - does not accept local function
 * prototypes if the function is defined above */
#ifdef ZZ_ANSI
    void ZZwrPair(FILE *fp,struct ZZbinStore *b);
    static void markBitsProp(struct ZZproperty *prp, ZZint val);
#else
    void ZZwrPair();
    static void markBitsProp();
#endif

/* ----------------------------------------------------------------------- */
/* How the property is encoded:
 * Single ZZint, float, or char (options 'i','f','c') are stored
 *                                            directly in ZZaProp.cProp;
 * For a single string (option 's'), cProp contains a poZZinter to the string;
 * For an array of ZZint,float, or char (options 'I','F','C') cProp contains
 *                                     a poZZinter to the beginning of the array;
 * For an array of strings (option 'S'), cProp poZZints to an array of char*
 *                                     poZZinters, each poZZints to one name.  */
/* ----------------------------------------------------------------------- */
/* write a pair of records: the header and the record itself */
#ifdef ZZ_ANSI
void  ZZwrPair(FILE *fp,struct ZZbinStore *b)
{
    ZZint ZZwrite(FILE *fp,char *b,ZZsize n,const char *errTxt);
#else


void  ZZwrPair(fp,b)
FILE *fp; /* may hide the file handle, if write() is used */
struct ZZbinStore *b; /* prepared header for this pair */
{
    ZZint ZZwrite();
#endif
    ZZsize n; ZZint r;

    n=sizeof(struct ZZbinStore);
    r=ZZwrite(fp,(char *)b,n,"ZZbinStore");
    if(r== -1 || (ZZsize)r!=n)ZZmsg(33); /* error when dumping property header */
    r=ZZwrite(fp,(char *)(b->ptr),b->size,"property header");
    if(r== -1 || (ZZsize)r!=b->size)ZZmsgD(5,b->strInd); /* error when dumping block type .. */
    return;
}
/* ----------------------------------------------------------------------- */
/* write the whole chain of properties onto the given file */
#ifdef ZZ_ANSI
void ZZwriteProp(FILE *fp,struct ZZproperty *pp)
{
#else


void ZZwriteProp(fp,pp)
FILE *fp; /* may hide the file handle, if write() is being used */
struct ZZproperty *pp; /* poZZinter to the beginning of the chain, may be NULL */
{
#endif
    ZZint i,ii;
    char c,**s;
    struct ZZbinStore B;
    struct ZZproperty *p,*pn;

    for(p=pp;p;p=pn){
        if(p->next==pp)pn=(struct ZZproperty *)NULL; else pn=p->next;

	/* main property structure */
	B.strInd= -2;
	B.size=(ZZint)sizeof(struct ZZproperty);
	B.ptr=(char*)p;
        ZZwrPair(fp,&B);

	/* property name */
	B.strInd= -1;
	B.size=(ZZint)strlen(p->codeName)+1;
	B.ptr=p->codeName;
        c=p->codeName[0];
        ZZwrPair(fp,&B);
        
        if(c=='i' || c=='f' || c=='c')continue;

        if(c=='s'){
	    s=(char**)(p->propType.cProp);
	    B.ptr=(*s);
	    B.strInd= -1;
	    B.size=(ZZint)strlen(B.ptr)+1;
            ZZwrPair(fp,&B);
            continue;
        }

	/* array property structure */
	B.strInd= -3;
	B.size=(ZZint)sizeof(struct ZZaProp);
	B.ptr=(char*)(p->propType.arrayProp);
        ZZwrPair(fp,&B);

	/* vector of values */
        if(c=='S')B.strInd= -5;
        else if(c=='I')B.strInd= -6;
        else if(c=='F')B.strInd= -7;
	else B.strInd= -1;
	B.size=p->propType.arrayProp->size;
	B.ptr=(char*)(p->propType.arrayProp->array);
        ZZwrPair(fp,&B);

        /* for array of strings, also all strings must be recorded */
        if(c=='S'){
	    ii=(p->propType.arrayProp->size)/(ZZint)sizeof(char*);
	    s=(char**)(p->propType.arrayProp->array);
            for(i=0;i<ii;i++){
	        B.strInd= -1;
	        B.size=(ZZint)strlen(s[i])+1;
	        B.ptr=s[i];
                ZZwrPair(fp,&B);
            }
        }
    }
}
/* ----------------------------------------------------------------------- */
/* write the whole chain of properties onto an ascii file */
#ifdef ZZ_ANSI
void ZZpropASCII(FILE *fp,struct ZZproperty *pp)
{
    ZZint ZZioFunction(FILE *fp,ZZint io,ZZint type,char *p,ZZint strSz);
#else


void ZZpropASCII(fp,pp)
FILE *fp; /* file which is already open */
struct ZZproperty *pp; /* poZZinter to the beginning of the chain, may be NULL */
{
    ZZint ZZioFunction();
#endif
    ZZint i,ii,*ip,n,size;
    char c,**s,*ptr;
    float *f;
    struct ZZproperty *p,*pn;

    for(p=pp;p;p=pn){
        if(p->next==pp)pn=(struct ZZproperty *)NULL; else pn=p->next;

	/* property name must go to the file first, its first char is a key */
        size=(ZZint)strlen(p->codeName)+1;
        ptr=p->codeName;
#ifdef LARGE_POINTER
        fprintf(fp,"%lu %d %d %d\n",ptr,-1,size,1);
#else
        fprintf(fp,"%d %d %d %d\n",ptr,-1,size,1);
#endif
        (void)ZZioFunction(fp,1,-1,ptr,0);

	/* main property structure */
	size=(ZZint)sizeof(struct ZZproperty);
        ptr=(char*)p;
#ifdef LARGE_POINTER
        fprintf(fp,"%lu %d %d %d\n",ptr,-2,size,1);
#else
        fprintf(fp,"%d %d %d %d\n",ptr,-2,size,1);
#endif
        (void)ZZioFunction(fp,1,-2,ptr,0);
        
        c=p->codeName[0];
        if(c=='i' || c=='f' || c=='c')continue;

        if(c=='s'){
	    s=(char**)(p->propType.cProp);
            ptr=(*s);
            size=(ZZint)strlen(ptr)+1;
#ifdef LARGE_POINTER
            fprintf(fp,"%lu %d %d %d\n",ptr,-1,size,1);
#else
            fprintf(fp,"%d %d %d %d\n",ptr,-1,size,1);
#endif
            (void)ZZioFunction(fp,1,-1,ptr,0);
            continue;
        }

	/* array property structure */
	size=(ZZint)sizeof(struct ZZaProp);
        ptr=(char*)(p->propType.arrayProp);
#ifdef LARGE_POINTER
        fprintf(fp,"%lu %d %d %d\n",ptr,-3,size,1);
#else
        fprintf(fp,"%d %d %d %d\n",ptr,-3,size,1);
#endif
        (void)ZZioFunction(fp,1,-3,ptr,0);

	/* vector of values */
	size=p->propType.arrayProp->size;
        ptr=p->propType.arrayProp->array;
        if(c=='S'){
            n=size/(ZZint)sizeof(char *);
            s=(char **)ptr;
#ifdef LARGE_POINTER
            fprintf(fp,"%lu %d %d %d\n",ptr,-5,size,n);
            for(i=0;i<n;i++,s++)fprintf(fp,"%lu\n",*s);
#else
            fprintf(fp,"%d %d %d %d\n",ptr,-5,size,n);
            for(i=0;i<n;i++,s++)fprintf(fp,"%d\n",*s);
#endif
        }
        else if(c=='F'){
            n=size/(ZZint)sizeof(float);
            f=(float*)ptr;
#ifdef LARGE_POINTER
            fprintf(fp,"%lu %d %d %d\n",ptr,-7,size,n);
#else
            fprintf(fp,"%d %d %d %d\n",ptr,-7,size,n);
#endif
            for(i=0;i<n;i++,f++)fprintf(fp,"%f\n",*f);
        }
	else if(c=='I'){
            n=size/(ZZint)sizeof(ZZint);
            ip=(ZZint*)ptr;
#ifdef LARGE_POINTER
            fprintf(fp,"%lu %d %d %d\n",ptr,-6,size,n);
#else
            fprintf(fp,"%d %d %d %d\n",ptr,-6,size,n);
#endif
            for(i=0;i<n;i++,ip++)fprintf(fp,"%d\n",*ip);
        }
        else if(c=='C'){
#ifdef LARGE_POINTER
            fprintf(fp,"%lu %d %d %d\n",ptr,-1,size,size);
#else
            fprintf(fp,"%d %d %d %d\n",ptr,-1,size,size);
#endif
            for(i=0;i<size;i++,ptr++)fprintf(fp,"%c\n",*ptr);
        }
        else ZZmsgC(1,&c); /* wrong property type %c */

        /* for array of strings, also all strings must be recorded */
        if(c=='S'){
	    ii=(p->propType.arrayProp->size)/(ZZint)sizeof(char*);
	    s=(char**)(p->propType.arrayProp->array);
            for(i=0;i<ii;i++){
	        size=(ZZint)strlen(s[i])+1;
	        ptr=s[i];
#ifdef LARGE_POINTER
                fprintf(fp,"%lu %d %d %d\n",ptr,-1,size,1);
#else
                fprintf(fp,"%d %d %d %d\n",ptr,-1,size,1);
#endif
                (void)ZZioFunction(fp,1,-1,ptr,0);
            }
        }
    }
}
/* ----------------------------------------------------------------------- */
#ifdef ZZ_ANSI
ZZint ZZpropGet(struct ZZproperty **start,char *name,char *type,char **block,
                                                                     ZZint *size)
#else


ZZint ZZpropGet(start,name,type,block,size)
struct ZZproperty **start; /* ptrToPtr used to be consistent with ZZpropSet() */
char *name;         /* given property name */
char *type;         /* returned character code, ' ' if not found */
char **block;       /* return poZZinter to the block of values */
ZZint *size;          /* returned size of the data block, in bytes */
#endif
{
    struct ZZproperty *pp,*pn;
    ZZint ptrSize;
    ptrSize=(ZZint)sizeof(char*);

    /* search for this property name */
    for(pp= *start;pp;pp=pn){
        if(pp->next==(*start))pn=(struct ZZproperty *)NULL; else pn=pp->next;
        if(!(strcmp(name,&(pp->codeName[1]))))break;
    }
    if(!pp){
	*type=' ';
        *size=0;
	return(0); /* property not found */
    }

    *type=pp->codeName[0];

    if((*type)=='i' || (*type)=='f' || (*type)=='s'){
	*size=ptrSize;
        *block=pp->propType.cProp;
    }
    else if((*type)=='c'){
	*size=1;
        *block=pp->propType.cProp;
    }
    else {
	*size=pp->propType.arrayProp->size;
        *block=pp->propType.arrayProp->array;
    }
    return(0);
}
/* ----------------------------------------------------------------------- */
/* Add property to a linked list starting from 'start'.
 * If the property of this name already exists, just update it */
#ifdef ZZ_ANSI
ZZint ZZpropSet(struct ZZproperty **start,char *type,char *name,char *block,
                                                                      ZZint size)
{
    ZZint ZZpropMake(struct ZZproperty **start,char *c,char *name,char *b,ZZint s);
    ZZint ZZpropUpdate(struct ZZproperty *pp,char *b,ZZint s);
    ZZint ZZprSize(struct ZZproperty *pp);
    ZZint ZZpropDelete(struct ZZproperty *pp, struct ZZproperty **start);
    char *ZZtpCnv(char *s);
#else


ZZint ZZpropSet(start,type,name,block,size)
struct ZZproperty **start; /* we must be able to change the first entry */
char *type;         /* property type as a string */
char *name;         /* property name */
char *block;        /* block of the data to be stored */
ZZint size;           /* size of the block, in bytes */
/* return: 0=normal, 1=illegal propType, >1 allocation error */
{
    ZZint ZZpropMake();
    ZZint ZZpropUpdate();
    ZZint ZZprSize();
    ZZint ZZpropDelete();
    char *ZZtpCnv();
#endif
    struct ZZproperty *pp,*pn;
    char c,s,*cc,*ss;
    ZZint n,k;

    if(!strcmp("ZZint",type)){k=(ZZint)sizeof(ZZint); if(size==k)c='i'; else c='I';}
    else if(!strcmp("float",type)){k=(ZZint)sizeof(float); if(size==k)c='f'; else c='F';}
    else if(!strcmp("char",type)){k=(ZZint)sizeof(char); if(size==k)c='c'; else c='C';}
    else if(!strcmp("string",type)){k=(ZZint)sizeof(char*); if(size==k)c='s'; else c='S';}
    else {
        ZZmsgS(13,type); /* illegal property type */
	return(1);
    }
    /* search for this property name */
    for(pp= *start;pp;pp=pn){
        if(pp->next==(*start))pn=(struct ZZproperty *)NULL; else pn=pp->next;
        if(!(strcmp(name,&(pp->codeName[1]))))break;
    }
    if(!pp){ /* new property must be allocated and added */
        ZZpropMake(start,&c,name,block,size);
    }

    else { /* such property is already there */
        s=pp->codeName[0];
        n=ZZprSize(pp);

	if(c==s&&n==size&&s!='s'&&s!='S'){
            ZZpropUpdate(pp,block,size);
        }
	else {
	    if(s!='s'&&s!='S'){
	        ZZmsgS(14,name);  /* warning: non-unique use of property */
                ss=ZZtpCnv(&s); cc=ZZtpCnv(&c);
	        ZZmsgSSDD(0,ss,cc,n/k,size/k);  /* type changed */
            }
	    (void)ZZpropDelete(pp,start); /* remove the old property */
	    (void)ZZpropMake(start,&c,name,block,size);
	}
    }
    return(0); /* regular return, all other returns are error conditions */
}
/* ----------------------------------------------------------------------- */
/* derive the size of the values for a given property */
#ifdef ZZ_ANSI
ZZint ZZprSize(struct ZZproperty *pp)
#else


ZZint ZZprSize(pp)
struct ZZproperty *pp;
#endif
{
    ZZint n;
    char s;

    s=pp->codeName[0];
    switch(s) {
        case 'i': n=(ZZint)sizeof(ZZint); break;
        case 'f': n=(ZZint)sizeof(float); break;
        case 'c': n=(ZZint)sizeof(char); break;
        case 's': n=(ZZint)sizeof(char*); break;
        default:  n=pp->propType.arrayProp->size; break;
    }
    return(n);
}
/* ----------------------------------------------------------------------- */
/* convert type character ZZinto the string as used by the user */
#ifdef ZZ_ANSI
char *ZZtpCnv(char *c)
#else


char *ZZtpCnv(c)
char *c;
#endif
{
    const char *p;

    if((*c)=='i' || (*c)=='I') p="ZZint";
    else if((*c)=='s' || (*c)=='S') p="string";
    else if((*c)=='f' || (*c)=='F') p="float";
    else if((*c)=='c' || (*c)=='C') p="char";
    else p="noType";

    return((char*)p);
}
/* ----------------------------------------------------------------------- */
/* reporting error and freeing partially setup property that failed */
#ifdef ZZ_ANSI
ZZint ZZerrProp(struct ZZproperty **start,struct ZZproperty *pp,ZZint level)
{
ZZint ZZdelObj(char *p);
#else


ZZint ZZerrProp(start,pp,level)
struct ZZproperty **start;
struct ZZproperty *pp;
ZZint level;       /* depth in which the failure happened */
{
ZZint ZZdelObj();
#endif
    ZZmsgD(6,level); /* alloc.failure when setting property level */
    *start=pp->next; /* remove the new property from the list */
    if(level>=2){ ZZdelObj((char *)(pp->propType.arrayProp)); }
    if(level>=1){ ZZdelObj(pp->codeName); ZZdelObj((char *)pp); }
    return(0);
}
/* ----------------------------------------------------------------------- */
/* update values of the property that already exists, 
 * its num and type has been checked
 */
#ifdef ZZ_ANSI
ZZint ZZpropUpdate(struct ZZproperty *pp,char *block,ZZint size) 
#else


ZZint ZZpropUpdate(pp,block,size) 
struct ZZproperty *pp;     /* property to update */
char *block;        /* block of data to be stored */
ZZint size;           /* size of the block, in bytes */
#endif
{
    ZZint i;
    char c,*s;

    c=pp->codeName[0];
    if(c=='i' || c=='f' || c=='c')s= pp->propType.cProp;
    else                          s= pp->propType.arrayProp->array;
    for(i=0;i<size;i++)s[i]=block[i];
    return(0);
}
/* ----------------------------------------------------------------------- */
/* mark or unmark bits in the bitmap */
#ifdef ZZ_ANSI
static void markBitsProp(struct ZZproperty *p, ZZint val)
{
    void ZZmarkPtr(char **ptr,ZZint val);
#else


static void markBitsProp(p,val)
struct ZZproperty *p; /* property header */
ZZint val;    /* value to be marked, 0 or 1 */
{
    void ZZmarkPtr();
#endif
    char c;

    if(ZZmemSwitch==2){  /* is bitmap used? */
        ZZmarkPtr((char **)(&(p->codeName)),val); 
        ZZmarkPtr((char **)(&(p->next)),val); 
        c=p->codeName[0];
        if(c=='I'||c=='F'||c=='C'||c=='S'||c=='s'){
            ZZmarkPtr((char **)(&(p->propType.arrayProp)),val); 
            if(p->propType.arrayProp)
                ZZmarkPtr(&(p->propType.arrayProp->array),val); 
        }
    }
}
/* ----------------------------------------------------------------------- */
/* remove property pp from the list starting at start */
#ifdef ZZ_ANSI
ZZint ZZpropDelete(struct ZZproperty *pp,struct ZZproperty **start)
{
    ZZint ZZdelObj(char *p);
#else


ZZint ZZpropDelete(pp,start)
struct ZZproperty *pp,**start;
{
    ZZint ZZdelObj();
#endif
    ZZint i,size,ptrSize;
    char c,**s,*p;
    struct ZZproperty *pt,*pn;

    if(!(*start)){ /* disconnect pp from the chain of properties */
	ZZmsg(34); /* ZZinternal problems, ZZpropDelete */
	return(1);
    }
    else if(*start==pp){
        *start=pp->next;
    }
    else {
        for(pt= *start;pt;pt=pn){
            if(pt->next==(*start))pn=(struct ZZproperty *)NULL; else pn=pt->next;
            if(pt->next==pp)break;
        }
	if(!pt || pt->next!=pp){
	    ZZmsg(35); /* ZZinternal inconsistency in ZZpropDelete() */
	    return(1);
	}
	pt->next=pp->next;
    }

    /* free up the old property */
    if(ZZmemSwitch==2)markBitsProp(pp,0);
    c=pp->codeName[0];
    if(c=='s'){
        ZZdelObj((char *)(pp->propType.arrayProp));
    }
    if(c=='S'){
        ptrSize=(ZZint)sizeof(char*);
	size=(pp->propType.arrayProp->size)/(ZZint)sizeof(char*);
        p=pp->propType.arrayProp->array;
	for(i=0;i<size;i+=ptrSize,p+=ptrSize){
            s=(char**)p;
            ZZdelObj((char *)(*s));
        }
    }
    if(c=='I' || c=='F' || c=='C' || c=='S'){
	ZZdelObj((char *)(pp->propType.arrayProp->array));
	ZZdelObj((char *)(pp->propType.arrayProp));
    }
    ZZdelObj(pp->codeName);
    ZZdelObj((char *)pp);
    return(0);
}
/* ----------------------------------------------------------------------- */
#ifdef ZZ_ANSI
ZZint ZZpropMake(struct ZZproperty **start,char *c,char *name,char *block,
                                                                      ZZint size)
{
    ZZint ZZpropChk(void);
    ZZvoidS *ZZnewObj(ZZint i,ZZint ini);
#else


ZZint ZZpropMake(start,c,name,block,size)
struct ZZproperty **start; /* we must be able to change the first entry */
char *c;            /* one character code describing the type of property */
char *name;         /* property name */
char *block;        /* array of propType, treat it as characters */
ZZint size;           /* size of the block in bytes */
/* return: 0=normal, >=1 allocation error, 4=installation error */
{
    ZZint ZZpropChk();
    ZZvoidS *ZZnewObj();
#endif
    struct ZZproperty *pp;
    struct ZZaProp *ap;
    char *pName,*s,**pp1,**pp2,*p1,*p2;
    ZZint i,ptrSize;

    if(ZZpropChk())return(4);
    ptrSize=(ZZint)sizeof(char*);
    pp=(struct ZZproperty*)ZZnewObj((ZZint)sizeof(struct ZZproperty),0);
    pName=(char*)ZZnewObj((ZZint)strlen(name)+2,0);
    if(!pp || !pName){ZZerrProp(start,pp,0);return(1);}
    pp->next= *start;
    *start=pp;
    pName[0]=(*c);
    strcpy(&(pName[1]),name);
    pp->codeName=pName;

    if((*c)=='i' || (*c)=='f' || (*c)=='c' || (*c)=='s')s= pp->propType.cProp;
    else {
        ap=(struct ZZaProp*)ZZnewObj((ZZint)sizeof(struct ZZaProp),0);
	s=(char*)ZZnewObj(size,0);
        if(!ap || !s){ZZerrProp(start,pp,1);return(2);}
        pp->propType.arrayProp=ap;
        ap->size=size;
	ap->array=s;
    }

    /* for strings, make a private version of each string */
    if((*c)=='s'){
        pp1=(char**)block;
	pp2=(char**)s;
	(*pp2)=(char*)ZZnewObj((ZZint)strlen(*pp1)+1,0);
        if(!(*pp2)){ZZerrProp(start,pp,2);return(3);}
	strcpy(*pp2,*pp1);
    }
    else if((*c)=='S'){
	for(p1=block,p2=s;p1<block+size;p1+=ptrSize,p2+=ptrSize){
	    pp1=(char**)p1;
	    pp2=(char**)p2;
	    (*pp2)=(char*)ZZnewObj((ZZint)strlen(*pp1)+1,0);
            if(!(*pp2)){ZZerrProp(start,pp,2);return(3);}
	    strcpy(*pp2,*pp1);
	}
    }
    else for(i=0;i<size;i++)s[i]=block[i];

    if(ZZmemSwitch==2)markBitsProp(pp,1);

    return(0);
}
/* ----------------------------------------------------------------------- */
/* return 1 if ZZinteger, float, or char* is bigger than size of cProp */
#ifdef ZZ_ANSI
ZZint ZZpropChk(void)
#else


ZZint ZZpropChk()
#endif
{
    ZZint i;

    i=ZZ_PROP_CS;
    if(i>=(ZZint)sizeof(ZZint) && i>=(ZZint)sizeof(float) && i>=(ZZint)sizeof(char*))return(0);
    ZZmsg(36); /* installation error: larger size needed for ZZproperty.cProp */
    return(1);
}
/* ----------------------------------------------------------------------- */
/* convert ZZinternal code of property type and size ZZinto external records */
#ifdef ZZ_ANSI
ZZint ZZcnvProp(char *code,ZZint size,char **pType,ZZint *num)
#else


ZZint ZZcnvProp(code,size,pType,num)
char *code;       /* property type, one character code */
ZZint size;     /* size of the property block, in Bytes */
char **pType; /* returned property type in a form of a string */
ZZint *num;     /* returned array size, 1=single property */
#endif
{
    const char* p;
    switch(*code){
	case 'i': p="ZZint"; *num=1; break;
	case 'I': p="ZZint"; *num=size/(ZZint)sizeof(ZZint); break;
	case 'f': p="float"; *num=1; break;
	case 'F': p="float"; *num=size/(ZZint)sizeof(float); break;
	case 'c': p="char"; *num=1; break;
	case 'C': p="char"; *num=size; break;
	case 's': p="string"; *num=1; break;
	case 'S': p="string"; *num=size/(ZZint)sizeof(char*); break;
	default:  p="notFound"; *num=0; break;
    }
    *pType=(char*)p;
    return(0);
}
/* ----------------------------------------------------------------------- */
/* prZZint single/multiple property -
 * This is just a utility function to avoid differentions between all
 * those property types in the user code.
 * Output format: (property name): (value1) (value2) ...
 */
#ifdef ZZ_ANSI
ZZint ZZwrtProperty(FILE *file,char *tp,char *name,char *val,ZZint num)
#else


ZZint ZZwrtProperty(file,tp,name,val,num)
FILE *file; /* output file */
char *tp;   /* property type, as a string */
char *name; /*name of the property */
char *val;  /* block containing all the values */
ZZint num;    /* number of values */
#endif
{
    ZZint *ip,i;
    float *fp;
    char **sp;

    if(num<=0)return(0);
    fprintf(file,"%s:",name);
    if(!strcmp(tp,"ZZint")){
        ip=(ZZint*)val;for(i=0;i<num;i++)fprintf(file," %d",ip[i]);}
    else if(!strcmp(tp,"float")){
        fp=(float*)val;for(i=0;i<num;i++)fprintf(file," %f",fp[i]);}
    else if(!strcmp(tp,"char")){
        for(i=0;i<num;i++)fprintf(file," %c",val[i]);}
    else if(!strcmp(tp,"string")){
        sp=(char**)val;for(i=0;i<num;i++)fprintf(file," %s",sp[i]);}
    else ZZmsgS(13,tp); /* error: illegal property type= */
    fprintf(file,"\n");
    return(0);
}
/* ----------------------------------------------------------------------- */
