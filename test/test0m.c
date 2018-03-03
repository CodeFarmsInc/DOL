/* This is test0d.c reprogrammed in C++ with ZZ_HYPER_ declarations
 * of hyper-objects. The program tests: Hyper objects, saving in both
 * binary and ASCII format, and the SWEEP function after using SAVE/OPEN.
 * Because it stores names differently, the second part of the output
 * is different from result of test0a.
 * Note that the ZORTECH compiler requires a different use of the iterator.
 * Unless you use an extended memory, the Zortech 3.0 compiler will run
 * out of memory under DOS. 
 */

#define ZZascii
#include <stdio.h>
#define ZZmain
#include "zzincl.h"

class Block {
    ZZ_EXT_Block
public:
    int x1,y1,x2,y2; // corners of the block, could be private
    Block();
};
ZZ_FORMAT(Block,"%d %d %d %d,x1,y1,x2,y2");
Block::Block(){ZZ_INIT(Block);}

class Net {
    ZZ_EXT_Net   
public:
    Net();
};
ZZ_FORMAT(Net,"");
Net::Net(){ZZ_INIT(Net);}

class Pin {
    ZZ_EXT_Pin  
public:
    int x1,y1,x2,y2; // corners of the pin, relative to block, could be private
    Pin();
};
ZZ_FORMAT(Pin,"%d %d %d %d,x1,y1,x2,y2");
Pin::Pin(){ZZ_INIT(Pin);}


#define INF 10000
#define MAX(A,B) ((A)<(B) ? (B) : (A))
#define MIN(A,B) ((A)>(B) ? (B) : (A))

ZZ_HYPER_UTILITIES(util);
ZZ_HYPER_SINGLE_RING(bChain,Block);
ZZ_HYPER_SINGLE_RING(nChain,Net);
ZZ_HYPER_SINGLE_TRIANGLE(byBlock,Block,Pin);
ZZ_HYPER_SINGLE_TRIANGLE(byNet,Net,Pin);
ZZ_HYPER_NAME(bName,Block);
ZZ_HYPER_NAME(nName,Net);

#define BSIZE 80
char name[BSIZE],buff[BSIZE];

void myFun(char *obj, ZZint type, ZZint size, const char *priv);
int main(int argc,char **argv)
{
    int x1,y1,x2,y2;
    char c,*nn,*v[2],*t[2];
    FILE *file1,*file2;
    Block *bp,*br,*bStart;
    Net *np,*nStart;
    Pin *pp,*pr;

    if(argc<=1)file1=stdin;  else file1=fopen(argv[1],"r");
    if(argc<=2)file2=stdout; else file2=fopen(argv[2],"w");

    bStart=(Block *)NULL; nStart=(Net *)NULL;
    while(fgets(buff,BSIZE,file1)){
        sscanf(buff,"%c %s %d %d %d %d",&c,name,&x1,&y1,&x2,&y2);
        if(c=='B'){
            bp=new Block;
            bp->x1=x1; bp->y1=y1; bp->x2=x2; bp->y2=y2;
            nn=util.strAlloc(name);
            bName.add(bp,nn);
            bStart=bChain.add(bStart,bp);
        }
        else if(c=='P'){
            pp=new Pin;
            pp->x1=x1; pp->y1=y1; pp->x2=x2; pp->y2=y2;
            /* is this net already listed ? */
            nChain_iterator nIter(nStart);
            ITERATE(nIter,np){
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

    /* first SAVE/OPEN in ASCII */
    v[0]=(char*)bStart; v[1]=(char*)nStart;
    t[0]=(char*)"Block";       t[1]=(char*)"Net";
    util.save("afile",2,v,t);
    util.open("afile",2,v,t);
    if(util.error())return(0);
    bStart=(Block*)v[0];
    nStart=(Net*)v[1];

    /* now use binary SAVE/OPEN */
    util.mode(0,1,0,0);
    v[0]=(char*)bStart; v[1]=(char*)nStart;
    t[0]=(char*)"Block";       t[1]=(char*)"Net";
    util.save("bfile",2,v,t);
    util.open("bfile",2,v,t);
    if(util.error())return(0);
    bStart=(Block*)v[0];
    nStart=(Net*)v[1];

    /* actual algorithm, includes the print of result */
    bChain_iterator bIter(bStart);
    ITERATE(bIter,bp){
        nn=bName.fwd(bp);
        fprintf(file2,"block=%s nets=",nn);
        byBlock_iterator bb(bp);
        ITERATE(bb,pp){
            np=byNet.par(pp);
            x1=INF; x2= -INF;
            byNet_iterator nIter(np);
            ITERATE(nIter,pr){
                br=byBlock.par(pr);
                x1=MIN(x1,br->x1 + pr->x1);
                x2=MAX(x2,br->x1 + pr->x2);
            };
            nn=nName.fwd(np);
            fprintf(file2," %s(%d,%d)",nn,x1,x2);
        }
        fprintf(file2,"\n");
    }
    fprintf(file2,"\n");

    /* test the sweap function */
    v[0]=(char*)bStart; v[1]=(char*)nStart;
    t[0]=(char*)"Block";       t[1]=(char*)"Net";
    util.swpSet(2,v,t);
    util.swpFun(myFun,(char*)file2);
    return(0);
}
/* --------------------------------------- */
/* function to print one object */
/* ZZint is interpreted as int, except under Windows7/64 bits as (long long) */
#ifdef ZZ_ANSI
void myFun(char *obj,ZZint typeInd,ZZint size,const char *priv)
#else


void myFun(obj,typeInd,size,priv)
char *obj;
int typeInd;
int size;
char *priv;
#endif
{
    FILE *fp;
    Block *bp;
    Net *np;
    Pin *pp;
    char *nn,*type;

    fp=(FILE *)priv;
    type=util.type(typeInd);
    if(!strcmp(type,"Block")){
        bp=(Block*)obj;
        nn=bName.fwd(bp);
        fprintf(fp,"Block %s size=%d\n",nn,size);
    }
    else if(!strcmp(type,"Net")){
        np=(Net*)obj;
        nn=nName.fwd(np);
        fprintf(fp,"Net %s size=%d\n",nn,size);
    }
    else if(!strcmp(type,"Pin")){
        pp=(Pin*)obj;
        fprintf(fp,"Pin (%d,%d %d,%d) size=%d\n",
                   pp->x1,pp->y1,pp->x2,pp->y2,size);
    }
    else fprintf(fp,"name=%s\n",obj);
}
/* ===================================================== */
#include "zzfunc.c"
