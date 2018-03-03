/* This is a very simple test to demonstrate the basic features
 * of INTELLIGENT PROGRAMMING. The task is to read a set or records
 * and print it twice, each time sorted by a different key.
 *  Similar problems occur in the processing connectivity netlists for
 * electrical circuits, where 'instance', 'formalTerminal', and 'net'
 * are represented by a name or by a pointer, not by an integer
 * as in this simplified example.
 */
#define ZZmain
#include <stdio.h>
#include "zzincl.h"

typedef struct ActTerm ActTerm;
struct ActTerm{
    ZZ_EXT_ActTerm
    int inst;
    int fTerm;
    int net;
};
ZZ_ORG_SINGLE_RING(ring,ActTerm);

#ifdef ZZ_ANSI
int main(int argc,char **argv)
#else


int main(argc,argv)
int argc;
char *argv[];
#endif
{
    FILE *file1,*file2;
    ActTerm *at,*aa;
#ifdef ZZ_ANSI
    ZZint iSort(const void*,const void*),nSort(const void*,const void*);
#else
    FILE *fopen();
    int iSort(),nSort();
#endif

    if(argc<=1)file1=stdin;  else file1=fopen(argv[1],"r");
    if(argc<=2)file2=stdout; else file2=fopen(argv[2],"w");

    at=NULL;
    for(;;){
        ZZ_ALLOCATE_AND_READ(ActTerm,
	        aa,(file1,"%d %d %d",&(aa->inst),&(aa->fTerm),&(aa->net)));
	if(!aa)break;
	ZZ_ADD_SINGLE_RING(ring,at,aa);
    }

    /* print netlist organized by instance */
    ZZ_SORT_SINGLE_RING(ring,iSort,at);
    fprintf(file2,"netlist by instance:\n");
    ZZ_A_TRAVERSE_SINGLE_RING(ring,at,aa){
       fprintf(
	   file2,"inst=%d fTerm=%d net=%d\n",aa->inst,aa->fTerm,aa->net);
    }ZZ_A_END;

    /* print netlist organized by instance */
    fprintf(file2,"\nnetlist by net:\n");
    ZZ_SORT_SINGLE_RING(ring,nSort,at);
    ZZ_A_TRAVERSE_SINGLE_RING(ring,at,aa){
       fprintf(
	   file2,"inst=%d fTerm=%d net=%d\n",aa->inst,aa->fTerm,aa->net);
    }ZZ_A_END;
    return(0);
}
/* ------------------------------------------------------------------- */
/* sort functions by instance and by net */
#ifdef ZZ_ANSI
ZZint iSort(const void *p1,const void *p2)
#else
ZZint iSort(p1,p2)
void *p1,*p2;
#endif
{
    ActTerm *a1,*a2;

    a1=(ActTerm *)p1;
    a2=(ActTerm *)p2;
    if(a1->inst<a2->inst)return(-1);
    if(a1->inst>a2->inst)return(1);
    return(0);
}
/* ------------------------------------------------------------------- */
#ifdef ZZ_ANSI
ZZint nSort(const void *p1,const void *p2)
#else
ZZint nSort(p1,p2)
void *p1,*p2;
#endif
{
    ActTerm *a1,*a2;

    a1=(ActTerm *)p1;
    a2=(ActTerm *)p2;
    if(a1->net<a2->net)return(-1);
    if(a1->net>a2->net)return(1);
    return(0);
}

#include "zzfunc.c"
