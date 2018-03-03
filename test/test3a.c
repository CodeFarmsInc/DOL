/* This program tests selfID which is used by default on all structures
 * that have zz_EXT... The selfID tag is set on all
 * structures allocated or initialized through the
 * zz-system only, so this is also test of the allocation routines.
 */
#define ZZmain
#include <stdio.h>
#ifdef ZORTECH
#include <stdlib.h>
#endif
#include "zzincl.h"

ZZ_ALL_SELF_ID;

typedef struct Apple Apple;
typedef struct Plum Plum;
typedef struct Mellon Mellon;
struct Apple {
    ZZ_EXT_Apple
    char color;
    int numSeeds;
};
struct Plum {
    ZZ_EXT_Plum
    int zone;
    float pitSize;
};
struct Mellon {
    float weight;
    float cost;
};
FILE *file1,*file2;
#ifndef ZZ_ANSI
FILE *fopen();
#endif

#ifdef ZZ_ANSI
int main(int argc,char **argv)
#else


int main(argc,argv)
int argc;
char *argv[];
#endif
{
    char *name;
    Apple a,ad[6],*ap;
    Mellon *m,mm;
    Plum *p,pp;
#ifdef ZZ_ANSI
    void report(const char *n1,char *n2);
    void *myAlloc(unsigned size); 
#else
    void report();
    void *myAlloc();
#endif

    m= &mm; ap= &a; p= &pp; /* anything to make variables meaningful */
    if(argc<=1)file1=stdin;  else file1=fopen(argv[1],"r");
    if(argc<=2)file2=stdout; else file2=fopen(argv[2],"w");

    /* try automatically allocated objects */
    fprintf(file2,"before allocation & force\n");
    ZZ_GET_SELF_ID(&a,name);
    report("a",name);
    ZZ_GET_SELF_ID(m,name);
    report("m",name);
    ZZ_GET_SELF_ID(p,name);
    report("p",name);
    ZZ_GET_SELF_ID(ap,name);
    report("ap",name);
    ZZ_GET_SELF_ID(&(ad[3]),name);
    report("ad[3]",name);

    /* allocate or set similar objects */
    fprintf(file2,"\nafter allocation & set\n");
    ZZ_SET_SELF_ID("Apple",&a,1);
    ZZ_GET_SELF_ID(&a,name);
    report("a",name);
    m=(Mellon*)myAlloc((int)sizeof(struct Mellon));
    ZZ_GET_SELF_ID(m,name);
    report("m",name);
    ZZ_ALLOCATE_AND_READ(Plum,p,(file1,"%d %f",&(p->zone),&(p->pitSize)));
    fprintf(file2,"Plum p: zone=%d pitSize=%f\n",p->zone,p->pitSize);
    ZZ_GET_SELF_ID(p,name);
    report("p",name);
    ZZ_PLAIN_ALLOC(Apple,20,ap);
    ZZ_GET_SELF_ID(&(ap[11]),name);
    report("ap[11]",name);
    ZZ_SET_SELF_ID("Apple",ad,6);
    ZZ_GET_SELF_ID(&(ad[3]),name);
    report("ad[3]",name);
    return(0);
}
/* ---------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void report(const char *n1,char *n2)
#else
void report(n1,n2)
char *n1,*n2;
#endif
{
    if(n2)fprintf(file2,"%s id=%s\n",n1,n2);
    else  fprintf(file2,"%s no id\n",n1);
}
/* ------------------------------------------------------- */
/* Different allocation in C and C++ */
#ifdef ZZ_ANSI
#ifdef ZZcplus
void *myAlloc(unsigned size)
{ return((void *)(new char[size]));}
#else

void *myAlloc(unsigned size)
{ void *malloc(unsigned size); return(malloc(size));}
#endif
#else

void *myAlloc(size)
unsigned size;
{ void *malloc(); return(malloc(size));}
#endif
#include "zzfunc.c"
