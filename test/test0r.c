// The same netlist example as in test0p (DOUBLE_COLLET
// and DOUBLE_RING are used), but coded in C++. 
// The result must be the same as for test0i.c
// Unless you use an extended memory, ZORTECH 3.0 compiler will run
// our of memory under DOS.

#define ZZascii
#include <stdio.h>
#define ZZmain
#include "zzincl.h"

class Block {
    ZZ_EXT_Block    /* let the program to hide the pointers here */
public:
    int x1,y1,x2,y2; /* corners of the block */
};
ZZ_FORMAT(Block,"%d %d %d %d,x1,y1,x2,y2");

class Net {
    ZZ_EXT_Net    /* let the program to hide the pointers here */
public:
    static ZZint nSort(const void*,const void*);
};
ZZ_FORMAT(Net,"");

class Pin {
    ZZ_EXT_Pin    /* let the program to hide the pointers here */
public:
    static ZZint pSort(const void*,const void*);
    int x1,y1,x2,y2; /* pin, relative to the block lower-left corner  */
};
ZZ_FORMAT(Pin,"%d %d %d %d,x1,y1,x2,y2");

ZZ_HYPER_DOUBLE_RING(bChain,Block);
ZZ_HYPER_DOUBLE_RING(nChain,Net);
ZZ_HYPER_DOUBLE_COLLECT(byBlock,Block,Pin);
ZZ_HYPER_DOUBLE_COLLECT(byNet,Net,Pin);
ZZ_HYPER_NAME(bName,Block);
ZZ_HYPER_NAME(nName,Net);
ZZ_HYPER_UTILITIES(util);

#define BSIZE 80
char name[BSIZE],buff[BSIZE];

int main(int argc,char **argv)
{
    int x1,y1,x2,y2;
    char c,*nn,*v[2],*t[2];
    FILE *file1,*file2;
    Block *bp,*bStart;
    Net *np,*nStart;
    Pin *pp,*pr;
    ZZint nSort(const void *p1,const void *p2);
    ZZint pSort(const void *p1,const void *p2);
    void prtBlocks(FILE *fp,Block *bStart);
    void prtNets(FILE *fp,Net *nStart);

    if(argc<=1)file1=stdin;  else file1=fopen(argv[1],"r");
    if(argc<=2)file2=stdout; else file2=fopen(argv[2],"w");

    bStart=(Block *)NULL; nStart=(Net *)NULL;
    while(fgets(buff,BSIZE,file1)){
        sscanf(buff,"%c %s %d %d %d %d",&c,name,&x1,&y1,&x2,&y2);
        if(c=='B'){
            bp=new Block;
            nn=util.strAlloc(name);
            bName.add(bp,nn);
            bp->x1=x1; bp->y1=y1; bp->x2=x2; bp->y2=y2;
            bStart=bChain.add(bStart,bp);
        }
        else if(c=='P'){
            pp=new Pin;
            pp->x1=x1; pp->y1=y1; pp->x2=x2; pp->y2=y2;
            /* is this net already listed ? */
            nChain_iterator nit(nStart);
            ITERATE(nit,np){  // equivalent of: while(np=nit++){
                nn=nName.fwd(np);
                if(!strcmp(name,nn))goto N_LOOP;
            }
            np=new Net;
            nn=util.strAlloc(name);
            nName.add(np,nn);
            nStart=nChain.add(nStart,np);
N_LOOP:
            byBlock.add(bp,pp);
            byNet.add(np,pp);
        }
    }
    fclose(file1);

    /* pickup two pins and delete them */
    pp=byBlock.child(bStart);
    nn=bName.fwd(bStart);
    fprintf(file2,"deleting from block=%s pin=(%d,%d %d,%d)\n",
                                   nn,pp->x1,pp->y1,pp->x2,pp->y2);
    byBlock.del(bStart,pp);

    np=nChain.fwd(nStart);
    pp=byNet.child(np);
    pp=byNet.fwd(pp);
    nn=nName.fwd(np);
    fprintf(file2,"deleting from net=%s pin=(%d,%d %d,%d)\n",
                                   nn,pp->x1,pp->y1,pp->x2,pp->y2);
    byNet.del(np,pp);
    fprintf(file2,"\n");

    v[0]=(char*)bStart; v[1]=(char*)nStart;
    t[0]=(char*)"Block";       t[1]=(char*)"Net";
    util.save((char*)"sfile",2,v,t);
    util.open((char*)"sfile",2,v,t);
    if(ZZerror)return(0); /* ZZerror=0100 if wrong file */
    bStart=(Block*)v[0];
    nStart=(Net*)v[1];

    prtBlocks(file2,bStart);
    fprintf(file2,"\n");
    prtNets(file2,nStart);
    fprintf(file2,"\n");

    /* sort Nets and then pins within each net */
    nStart=nChain.sort(Net::nSort,nStart);
    nChain_iterator nnt(nStart);
    ITERATE(nnt,np){  // equivalent of: while(np=nnt++){
        byNet.sort(Pin::pSort,np);
        /* move to the second pin */
        pp=byNet.child(np);
        pp=byNet.fwd(pp);
        byNet.set(np,pp);
    }

    /* merge first two Blocks */
    bp=bChain.fwd(bStart);
    bp=bChain.fwd(bp);
    pp=byBlock.child(bStart);
    pr=byBlock.child(bp);
    byBlock.merge(pp,pr,bp);
    /* split the second pin out of it and put it under the second block */
    pr=byBlock.fwd(pp);
    byBlock.merge(pp,pr,bp);
    /* split the ring of nets into two parts */
    np=nChain.fwd(nStart);
    np=nChain.fwd(np);
    nStart=nChain.merge(nStart,np);

    prtBlocks(file2,bStart);
    fprintf(file2,"\nFirst set of nets:\n");
    prtNets(file2,nStart);
    fprintf(file2,"\nSecond set of nets:\n");
    prtNets(file2,np);
    return(0);
}
/* ------------------------------------------------------------- */
/* for all blocks, print the translated position of the pins */
void prtBlocks(FILE *file2,Block *bStart)
{
    Block *bp;
    Pin *pp;
    char *nn;
    int x1,y1,x2,y2;

    bChain_iterator bit(bStart);
    ITERATE(bit,bp){ // equivalent of while(bp=bit++){
        nn=bName.fwd(bp);
        fprintf(file2,"block=%s pins=",nn);
        byBlock_iterator pit(bp);
        ITERATE(pit,pp){ // equivalent of while(pp=pit++){
            x1=bp->x1 + pp->x1;
            y1=bp->y1 + pp->y1;
            x2=bp->x1 + pp->x2;
            y2=bp->y1 + pp->y2;
            fprintf(file2," (%d,%d %d,%d)",x1,y1,x2,y2);
        }
        fprintf(file2,"\n");
    }
}
/* ------------------------------------------------------------- */
/* for all Nets, print the relative position of the pins */
void prtNets(FILE *file2,Net *nStart)
{    
    Net *np;
    Pin *pp;
    char *nn;

    nChain_iterator nit(nStart);
    ITERATE(nit,np){ // equivalent of while(np=nit++){
        nn=nName.fwd(np);
        fprintf(file2,"net=%s pins=",nn);
        byNet_iterator pit(np);
        ITERATE(pit,pp){ // equivalent of while(pp=pit++){
            fprintf(file2," (%d,%d %d,%d)",pp->x1,pp->y1,pp->x2,pp->y2);
        }
        fprintf(file2,"\n");
    }
}
/* ------------------------------------------------------------- */
ZZint Net::nSort(const void *s1,const void *s2)
{ char *n1,*n2;
  Net *p1,*p2;

  p1=(Net *)s1; p2=(Net *)s2;
  n1=nName.fwd(p1);
  n2=nName.fwd(p2);
  return(strcmp(n1,n2));
}
/* ------------------------------------------------------------- */
ZZint Pin::pSort(const void *s1,const void *s2)
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
