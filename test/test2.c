/* This is a more realistic example of processing netlists.
 * All entities are represented by their names (text strings).
 * The program extracts two lists, one for instances and one for nets,
 * and then it sets fast access chains, so that terminals associated
 * with any instance or net can be immediately accessed.
 * This is the basic organizations used in most existing VLSI design systems.
 *  Note that two independent organizations of the same kind are being
 * used on structure ActTerm, and that storage space for all names that are 
 * being read in is automatically allocated.
 *  This test is also using a mixture of short/full macro names,
 * even for the same organization pair.
 *
 * Compare the new approach with a manually coded organization:
 * struct Instance{
 *     char *name;
 *     ActTerm *at;
 * };
 * struct Net{
 *     char *name;
 *     ActTerm *at;
 * };
 * struct ActTerm {
 *     char *fTerm;
 *     Instance *inst;
 *     Net *net;
 *     ActTerm *nextOnInst;
 *     ActTerm *nextOnNet;
 * };
 */
#define ZZmain
#include <stdio.h>
#include "zzincl.h"

typedef struct Instance Instance;
typedef struct Net Net;
typedef struct ActTerm ActTerm;
struct Instance{
    ZZ_EXT_Instance
    char *name;
};
ZZ_ORG_SINGLE_RING(iRing,Instance);

struct Net{
    ZZ_EXT_Net
    char *name;
};
ZZ_ORG_SINGLE_RING(nRing,Net);

struct ActTerm{
    ZZ_EXT_ActTerm
    char *fTerm;
};
ZZ_ORG_SINGLE_TRIANGLE(byInst,Instance,ActTerm);
ZZ_ORG_SINGLE_TRIANGLE(byNet,Net,ActTerm);

#ifdef ZZ_ANSI
int main(int argc,char **argv)
#else


int main(argc,argv)
int argc;
char *argv[];
#endif
{
    FILE *file1,*file2;
#ifndef ZZ_ANSI
    FILE *fopen();
#endif
    ActTerm *at;
    char *ir[3]; /* input record */
    Instance *ip,*is;
    Net *np,*ns;

    if(argc<=1)file1=stdin;  else file1=fopen(argv[1],"r");
    if(argc<=2)file2=stdout; else file2=fopen(argv[2],"w");

    is=(Instance *)NULL; /* start with no instances */
    ns=(Net *)NULL; /* start with no nets */
    for(;;){
        ZZ_INPUT_NAMES(file1,ir,3);
	if(!ir[0])break;
	ZZ_PLAIN_ALLOC(ActTerm,1,at);
	at->fTerm=ir[1];

        ZZ_A_TRAVERSE_SINGLE_RING(iRing,is,ip){
	    if(!strcmp(ip->name,ir[0]))break;
	}ZZAend;
	if(!ip) {
	    ZZalloc(Instance,1,ip);
	    ZZ_ADD_SINGLE_RING(iRing,is,ip);
	    ip->name=ir[0];
	}
	ZZ_ADD_SINGLE_TRIANGLE(byInst,ip,at);

        ZZ_A_TRAVERSE_SINGLE_RING(nRing,ns,np){
	    if(!strcmp(np->name,ir[2]))break;
	}ZZAend;
	if(!np) {
	    ZZ_PLAIN_ALLOC(Net,1,np);
	    ZZadd1R(nRing,ns,np);
	    np->name=ir[2];
	}
	ZZ_ADD_SINGLE_TRIANGLE(byNet,np,at);
    }

    /* print the whole organization by instance */
    ZZ_A_TRAVERSE_SINGLE_RING(iRing,is,ip){
	fprintf(file2,"inst=%s\n",ip->name);
        ZZ_A_TRAVERSE_SINGLE_TRIANGLE(byInst,ip,at){
	    ZZ_PARENT_SINGLE_TRIANGLE(byNet,at,np);
	    fprintf(file2,"   fTerm=%s net=%s\n",at->fTerm,np->name);
	}ZZ_A_END;
    }ZZ_A_END;

    /* print the whole organization by net */
    ZZ_A_TRAVERSE_SINGLE_RING(nRing,ns,np){
	fprintf(file2,"net=%s\n",np->name);
        ZZ_A_TRAVERSE_SINGLE_TRIANGLE(byNet,np,at){
	    ZZ_PARENT_SINGLE_TRIANGLE(byInst,at,ip);
	    fprintf(file2,"   fTerm=%s inst=%s\n",at->fTerm,ip->name);
	}ZZ_A_END;
    }ZZ_A_END;
    return(0);
}
#include "zzfunc.c"
