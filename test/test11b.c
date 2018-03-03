/* Test of ASCII ZZ_SAVE() for LINKs and NAME with
 * some very short names (which is a difficult condition).
 * The results and the way to run the program is just as for test11a.
 */

#include <stdio.h>
#define ZZascii
#define ZZmain
#define ZZnoDestr
#include "zzincl.h"

typedef struct Source Source;
typedef struct Target Target;

struct Source {
    ZZ_EXT_Source
#ifdef ZZcplus
    Source(){}
#endif
};

struct Target {
    ZZ_EXT_Target
#ifdef ZZcplus
    Target(){}
#endif
};

ZZ_ORG_SINGLE_RING(ring,Source);
ZZ_ORG_SINGLE_LINK(link,Source,Target);
ZZ_ORG_NAME(aName,Source);
ZZ_ORG_NAME(bName,Target);

static char *aa[3]={"AA22","","A0"};
static char *bb[3]={"C","BB1",""};

#ifdef ZZ_ANSI
int main(void)
#else
int main()
#endif
{
    Source a[3],*ap,*as,*start;
    Target b[3],*bp;
    int i;
    char *an[3],*bn[3],*v[1],*t[1],*n1,*n2;

    /* orgC must deal with data, not program constants! */
    for(i=0;i<3;i++){
	ZZ_STRING_ALLOC(aa[i],an[i]);
	ZZ_STRING_ALLOC(bb[i],bn[i]);
    }
    
    /* create the organization */
    as=(Source *)NULL;
    for(i=0;i<3;i++){
        ap= &(a[i]);
        bp= &(b[i]);
        ZZ_INITIAL(Source,0,1,ap);
        ZZ_INITIAL(Target,0,1,bp);
        ZZ_ADD(ring,as,ap);
        ZZ_ADD(aName,ap,an[i]);
        ZZ_ADD(bName,bp,bn[i]);
        ZZ_ADD(link,ap,bp);
    }

    /* save it on file sfile */
    v[0]=(char*)as;
    t[0]="Source";
    ZZ_SAVE("sfile",1,v,t);
    v[0]=(char *)NULL; /* just as a precaution */

    /* restore the organization */
    ZZ_OPEN("sfile",1,v,t);
    start=(Source*)v[0]; /* new main entry */

    /* print the new organization */
    ZZ_A_TRAVERSE(ring,start,ap){
        ZZ_FORWARD(link,ap,bp);
        ZZ_FORWARD(aName,ap,n1);
        ZZ_FORWARD(bName,bp,n2);
        printf("-%s- links to -%s-\n",n1,n2);
    }ZZ_A_END;
    return(0);
}
/* ===================================================== */
#include "zzfunc.c"
#ifdef ZZ_ANSI
int zz_out_Source(FILE *fp,Source *p) { fp=fp; p=p; return(0); }
int zz_out_Target(FILE *fp,Target *p) { fp=fp; p=p; return(0); }
int zz_inp_Source(FILE *fp,Source *p) { fp=fp; p=p; return(0); }
int zz_inp_Target(FILE *fp,Target *p) { fp=fp; p=p; return(0); }
#else
int zz_out_Source(fp,p) FILE *fp; Source *p; { fp=fp; p=p; return(0); }
int zz_out_Target(fp,p) FILE *fp; Target *p; { fp=fp; p=p; return(0); }
int zz_inp_Source(fp,p) FILE *fp; Source *p; { fp=fp; p=p; return(0); }
int zz_inp_Target(fp,p) FILE *fp; Target *p; { fp=fp; p=p; return(0); }
#endif
