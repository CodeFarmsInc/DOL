/* This is the same test as test0a.c, except that the TRAVERSE
 * loop is replaced by CHILD & FORWARD operations for one triangle.
 * The result should be identical with test0a.c */
#include <stdio.h>
#define ZZmain
#include "zzincl.h"

typedef struct Block Block;
typedef struct Net Net;
typedef struct Pin Pin;

struct Block {
    ZZ_EXT_Block    /* let the program to hide the pointers here */
    char *name;
    int x1,y1,x2,y2; /* corners of the block */
};

struct Net {
    ZZ_EXT_Net    /* let the program to hide the pointers here */
    char *name;
};

struct Pin {
    ZZ_EXT_Pin    /* let the program to hide the pointers here */
    int x1,y1,x2,y2; /* pin, relative to the block lower-left corner  */
};

#define INF 10000
#define MAX(A,B) ((A)<(B) ? (B) : (A))
#define MIN(A,B) ((A)>(B) ? (B) : (A))

ZZ_ORG_SINGLE_RING(bChain,Block);
ZZ_ORG_SINGLE_RING(nChain,Net);
ZZ_ORG_SINGLE_TRIANGLE(byBlock,Block,Pin);
ZZ_ORG_SINGLE_TRIANGLE(byNet,Net,Pin);

#define BSIZE 80

#ifdef ZZ_ANSI
int main(int argc,char **argv)
{
    void myFun(char *obj, int type, int size, char *priv);
#else


int main(argc,argv)
int argc;
char *argv[];
{
    FILE *fopen();
    void myFun();
#endif
    int x1,y1,x2,y2;
    char c,name[BSIZE],buff[BSIZE],*nn,*v[2],*t[2];
    FILE *file1,*file2;
    Block *bp,*br,*bStart;
    Net *np,*nStart;
    Pin *pp,*pr,*ps;

    if(argc<=1)file1=stdin;  else file1=fopen(argv[1],"r");
    if(argc<=2)file2=stdout; else file2=fopen(argv[2],"w");

    bStart=(Block *)NULL; nStart=(Net *)NULL;
    while(fgets(buff,BSIZE,file1)){
        sscanf(buff,"%c %s %d %d %d %d",&c,name,&x1,&y1,&x2,&y2);
        if(c=='B'){
            ZZ_PLAIN_ALLOC(Block,1,bp);
            ZZ_STRING_ALLOC(name,nn);
            bp->name=nn; bp->x1=x1; bp->y1=y1; bp->x2=x2; bp->y2=y2;
            ZZ_ADD_SINGLE_RING(bChain,bStart,bp);
        }
        else if(c=='P'){
            ZZ_PLAIN_ALLOC(Pin,1,pp);
            pp->x1=x1; pp->y1=y1; pp->x2=x2; pp->y2=y2;
            /* is this net already listed ? */
            ZZ_A_TRAVERSE_SINGLE_RING(nChain,nStart,np){
                if(!strcmp(name,np->name))goto N_LOOP;
            }ZZ_A_END;
            ZZ_PLAIN_ALLOC(Net,1,np);
            ZZ_STRING_ALLOC(name,nn);
            np->name=nn;
            ZZ_ADD_SINGLE_RING(nChain,nStart,np);
N_LOOP:
            ZZ_ADD_SINGLE_TRIANGLE(byBlock,bp,pp);
            ZZ_ADD_SINGLE_TRIANGLE(byNet,np,pp);
        }
    }
    fclose(file1);

    /* for all blocks, print the x-span of all connected nets */
    ZZ_A_TRAVERSE_SINGLE_RING(bChain,bStart,bp){
        fprintf(file2,"block=%s nets=",bp->name);
        ZZ_A_TRAVERSE_SINGLE_TRIANGLE(byBlock,bp,pp){
            ZZ_PARENT_SINGLE_TRIANGLE(byNet,pp,np);
            x1=INF; x2= -INF;
            ZZ_CHILD(byNet,np,ps); /* equivalent of ZZ_TRAVERSE loop */
            for(pr=ps;;){
                ZZ_PARENT_SINGLE_TRIANGLE(byBlock,pr,br);
                x1=MIN(x1,br->x1 + pr->x1);
                x2=MAX(x2,br->x1 + pr->x2);
                ZZ_FORWARD(byNet,pr,pr);
                if(pr==ps)break;
            }
            fprintf(file2," %s(%d,%d)",np->name,x1,x2);
        }ZZ_A_END;
        fprintf(file2,"\n");
    }ZZ_A_END;
    fprintf(file2,"\n");

    /* test the sweap function */
    v[0]=(char*)bStart; v[1]=(char*)nStart;
    t[0]="Block";       t[1]="Net";
    ZZ_SWEEP_SET(2,v,t);
    ZZ_SWEEP_FUNCTION(myFun,(char*)file2);
    return(0);
}
/* --------------------------------------- */
/* function to print one object */
#ifdef ZZ_ANSI
void myFun(char *obj,int typeInd,int size,char *priv)
#else
void myFun(obj,typeInd,size,priv)
char *obj;
int typeInd;
int size;
char *priv;
#endif
{
    FILE *fp;
    char *type;
    Block *bp;
    Net *np;
    Pin *pp;

    fp=(FILE *)priv;
    ZZ_TYPE_NAME(typeInd,type);
    if(!strcmp(type,"Block")){
        bp=(Block*)obj;
        fprintf(fp,"Block %s size=%d\n",bp->name,size);
    }
    else if(!strcmp(type,"Net")){
        np=(Net*)obj;
        fprintf(fp,"Net %s size=%d\n",np->name,size);
    }
    else {
        pp=(Pin*)obj;
        fprintf(fp,"Pin (%d,%d %d,%d) size=%d\n",
                   pp->x1,pp->y1,pp->x2,pp->y2,size);
    }
}
#include "zzfunc.c"
