/* The same netlist example as in test0p except Pin coordinates are stored as single bytes
 * When executed with input inp0, the result should be out0i.
 * We run it here with different data, in order to test negative values. 
 */

#define ZZascii
#include <stdio.h>
#define ZZmain
#include "zzincl.h"

typedef struct Block Block;
typedef struct Net Net;
typedef struct Pin Pin;

struct Block {
    ZZ_EXT_Block    /* let the program to hide the pointers here */
    int x1,y1,x2,y2; /* corners of the block */
};
ZZ_FORMAT(Block,"%d %d %d %d,x1,y1,x2,y2");

struct Net {
    ZZ_EXT_Net    /* let the program to hide the pointers here */
};
ZZ_FORMAT(Net,"");

struct Pin {
    ZZ_EXT_Pin    /* let the program to hide the pointers here */
    char x1,y1,x2,y2; /* pin, relative to the block lower-left corner  */
};
ZZ_FORMAT(Pin,"%a %a %a %a,x1,y1,x2,y2");

ZZ_ORG_DOUBLE_RING(bChain,Block);
ZZ_ORG_DOUBLE_RING(nChain,Net);
ZZ_ORG_DOUBLE_COLLECT(byBlock,Block,Pin);
ZZ_ORG_DOUBLE_COLLECT(byNet,Net,Pin);
ZZ_ORG_NAME(bName,Block);
ZZ_ORG_NAME(nName,Net);

#define BSIZE 80
char name[BSIZE],buff[BSIZE];

#ifdef ZZ_ANSI
int main(int argc,char **argv)
#else


int main(argc,argv)
int argc;
char *argv[];
#endif
{
    int x1,y1,x2,y2;
    char c,*nn,*v[2],*t[2];
    FILE *file1,*file2;
    Block *bp,*bStart;
    Net *np,*nStart;
    Pin *pp,*pr;
#ifdef ZZ_ANSI
    int nSort(char *p1,char *p2),pSort(char *p1,char *p2);
    void prtBlocks(FILE *fp,Block *bStart);
    void prtNets(FILE *fp,Net *nStart);
#else
    FILE *fopen();
    int nSort(),pSort();
    void prtBlocks();
    void prtNets();
#endif

    if(argc<=1)file1=stdin;  else file1=fopen(argv[1],"r");
    if(argc<=2)file2=stdout; else file2=fopen(argv[2],"w");

    bStart=(Block *)NULL; nStart=(Net *)NULL;
    while(fgets(buff,BSIZE,file1)){
        sscanf(buff,"%c %s %d %d %d %d",&c,name,&x1,&y1,&x2,&y2);
        if(c=='B'){
            ZZ_PLAIN_ALLOC(Block,1,bp);
            ZZ_STRING_ALLOC(name,nn);
            ZZ_ADD(bName,bp,nn);
            bp->x1=x1; bp->y1=y1; bp->x2=x2; bp->y2=y2;
            ZZ_ADD(bChain,bStart,bp);
        }
        else if(c=='P'){
            ZZ_PLAIN_ALLOC(Pin,1,pp);
            pp->x1=x1; pp->y1=y1; pp->x2=x2; pp->y2=y2;
            /* is this net already listed ? */
            ZZ_A_TRAVERSE(nChain,nStart,np){
                ZZ_FORWARD(nName,np,nn);
                if(!strcmp(name,nn))goto N_LOOP;
            }ZZ_A_END;
            ZZ_PLAIN_ALLOC(Net,1,np);
            ZZ_STRING_ALLOC(name,nn);
            ZZ_ADD(nName,np,nn);
            ZZadd(nChain,nStart,np);
N_LOOP:
            ZZadd(byBlock,bp,pp);
            ZZ_ADD(byNet,np,pp);
        }
    }
    fclose(file1);

    /* pickup two pins and delete them */
    ZZ_CHILD(byBlock,bStart,pp);
    ZZ_FORWARD(bName,bStart,nn);
    fprintf(file2,"deleting from block=%s pin=(%d,%d %d,%d)\n",
                                   nn,pp->x1,pp->y1,pp->x2,pp->y2);
    ZZ_DELETE(byBlock,bStart,pp);

    ZZ_FORWARD(nChain,nStart,np);
    ZZ_CHILD(byNet,np,pp);
    ZZ_FORWARD(byNet,pp,pp);
    ZZ_FORWARD(nName,np,nn);
    fprintf(file2,"deleting from net=%s pin=(%d,%d %d,%d)\n",
                                   nn,pp->x1,pp->y1,pp->x2,pp->y2);
    ZZ_DELETE(byNet,np,pp);
    fprintf(file2,"\n");

    v[0]=(char*)bStart; v[1]=(char*)nStart;
    t[0]="Block";       t[1]="Net";
    ZZ_SAVE("sfile",2,v,t);
    ZZ_CLEAR(2,v,t);
    ZZ_OPEN("sfile",2,v,t);
    if(ZZerror)return(0); /* ZZerror=0100 if wrong file */
    bStart=(Block*)v[0];
    nStart=(Net*)v[1];

    prtBlocks(file2,bStart);
    fprintf(file2,"\n");
    prtNets(file2,nStart);
    fprintf(file2,"\n");

    /* sort Nets and then pins within each net */
    ZZ_SORT(nChain,nSort,nStart);
    ZZ_A_TRAVERSE(nChain,nStart,np){
        ZZ_SORT(byNet,pSort,np);
        /* move to the second pin */
        ZZ_CHILD(byNet,np,pp);
        ZZ_FORWARD(byNet,pp,pp);
        ZZ_SET(byNet,np,pp);
    }ZZ_A_END;

    /* merge first two Blocks */
    ZZ_FORWARD(bChain,bStart,bp);
    ZZ_FORWARD(bChain,bp,bp);
    ZZ_CHILD(byBlock,bStart,pp);
    ZZ_CHILD(byBlock,bp,pr);
    ZZ_MERGE(byBlock,pp,pr,bp);
    /* split the second pin out of it and put it under the second block */
    ZZ_FORWARD(byBlock,pp,pr);
    ZZ_MERGE(byBlock,pp,pr,bp);
    /* split the ring of nets into two parts */
    ZZ_FORWARD(nChain,nStart,np);
    ZZ_FORWARD(nChain,np,np);
    ZZ_MERGE(nChain,nStart,np,NULL);

    prtBlocks(file2,bStart);
    fprintf(file2,"\nFirst set of nets:\n");
    prtNets(file2,nStart);
    fprintf(file2,"\nSecond set of nets:\n");
    prtNets(file2,np);
    return(0);
}
/* ------------------------------------------------------------- */
/* for all blocks, print the translated position of the pins */
#ifdef ZZ_ANSI
void prtBlocks(FILE *file2,Block *bStart)
#else
void prtBlocks(file2,bStart)
FILE *file2;
Block *bStart;
#endif
{
    Block *bp;
    Pin *pp;
    char *nn;
    int x1,y1,x2,y2;

    ZZ_A_TRAVERSE(bChain,bStart,bp){
        ZZ_FORWARD(bName,bp,nn);
        fprintf(file2,"block=%s pins=",nn);
        ZZ_A_TRAVERSE(byBlock,bp,pp){
            x1=bp->x1 + pp->x1;
            y1=bp->y1 + pp->y1;
            x2=bp->x1 + pp->x2;
            y2=bp->y1 + pp->y2;
            fprintf(file2," (%d,%d %d,%d)",x1,y1,x2,y2);
        }ZZ_A_END;
        fprintf(file2,"\n");
    }ZZ_A_END;
}
/* ------------------------------------------------------------- */
/* for all Nets, print the relative position of the pins */
#ifdef ZZ_ANSI
void prtNets(FILE *file2,Net *nStart)
#else
void prtNets(file2,nStart)
FILE *file2;
Net *nStart;
#endif
{    
    Net *np;
    Pin *pp;
    char *nn;

    ZZ_A_TRAVERSE(nChain,nStart,np){
        ZZ_FORWARD(nName,np,nn);
        fprintf(file2,"net=%s pins=",nn);
        ZZ_A_TRAVERSE(byNet,np,pp){
            fprintf(file2," (%d,%d %d,%d)",pp->x1,pp->y1,pp->x2,pp->y2);
        }ZZ_A_END;
        fprintf(file2,"\n");
    }ZZ_A_END;
}
/* ------------------------------------------------------------- */
#ifdef ZZ_ANSI
int nSort(char *s1,char *s2)
#else
int nSort(s1,s2)
char *s1,*s2;
#endif
{ char *n1,*n2;
  Net *p1,*p2;

  p1=(Net *)s1; p2=(Net *)s2;
  ZZ_FORWARD(nName,p1,n1);
  ZZ_FORWARD(nName,p2,n2);
  return(strcmp(n1,n2));
}
/* ------------------------------------------------------------- */
#ifdef ZZ_ANSI
int pSort(char *s1,char *s2)
#else
int pSort(s1,s2)
char *s1,*s2;
#endif
{
  Pin *p1,*p2;

  p1=(Pin *)s1; p2=(Pin *)s2;
  if(p1->x1<p2->x1)return(-1);
  if(p1->x1>p2->x1)return(1);
  if(p1->y1<p2->y1)return(-1);
  if(p1->y1>p2->y1)return(1);
  return(0);
}
/* ------------------------------------------------------------- */
#include "zzfunc.c"
