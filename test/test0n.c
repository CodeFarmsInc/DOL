/* The same netlist example as in test0d, here coded in the C++ style
 *  with hyper-objects. The program tests, at the same time,
 * SINGLE and DOUBLE RING, SINGLE_TRIANGLE and SINGLE_COLLECTION, with
 * ASCII SAVE. The results should be exactly the same as for test0d.c
 */

#define ZZascii
#include <stdio.h>
#define ZZmain
#include "zzincl.h"

class Block {
    ZZ_EXT_Block 
public:
    int x1,y1,x2,y2; /* corners of the block */
    Block();
    ~Block();
};
ZZ_FORMAT(Block,"%d %d %d %d,x1,y1,x2,y2");
Block::Block(){}
Block::~Block(){ZZ_CHECK_FREE(Block,1,this);}

class Net {
    ZZ_EXT_Net  
public:
    Net();
    ~Net();
};
ZZ_FORMAT(Net,"");
Net::Net(){}
Net::~Net(){ZZ_CHECK_FREE(Net,1,this);}

class Pin {
    ZZ_EXT_Pin 
public:
    int x1,y1,x2,y2; /* pin, relative to the block lower-left corner  */
    Pin();
    ~Pin();
};
ZZ_FORMAT(Pin,"%d %d %d %d,x1,y1,x2,y2");
Pin::Pin(){}
Pin::~Pin(){ZZ_CHECK_FREE(Pin,1,this);}

ZZ_HYPER_UTILITIES(util);
ZZ_HYPER_SINGLE_RING(bChain,Block);
ZZ_HYPER_DOUBLE_RING(nChain,Net);
ZZ_HYPER_SINGLE_TRIANGLE(byBlock,Block,Pin);
ZZ_HYPER_SINGLE_COLLECT(byCol,Block,Pin);
ZZ_HYPER_SINGLE_TRIANGLE(byNet,Net,Pin);
ZZ_HYPER_NAME(bName,Block);
ZZ_HYPER_NAME(nName,Net);

#define INF 10000
#define MAX(A,B) ((A)<(B) ? (B) : (A))
#define MIN(A,B) ((A)>(B) ? (B) : (A))

#define BSIZE 80
char name[BSIZE],buff[BSIZE];

int main(int argc,char **argv)
{
    int x1,y1,x2,y2;
    char c,*nn,*v[2],*t[2];
    FILE *file1,*file2;
    Block *bp,*br,*bStart;
    Net *np,*nStart;
    Pin *pp,*pr;
    void myFun(char *obj, ZZint type, ZZint size, const char *priv);

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
            nChain_iterator nIter(nStart);
            ITERATE(nIter,np){
                nn=nName.fwd(np);
                if(!strcmp(name,nn))break;
            }
            if(strcmp(name,nn)){ /* if the name not found */
                np=new Net;
                nn=util.strAlloc(name);
                nName.add(np,nn);
                nStart=nChain.add(nStart,np);
            }
            byBlock.add(bp,pp);
            byNet.add(np,pp);
        }
    }
    fclose(file1);

    // Uncoment one of these two lines to set the mode:
    // util.mode(0,1,0,0); // binary mode
    // util.mode(1,1,0,0); // ASCII mode
    // If you don't, the default is ASCII because #define ZZasii is used
    
    v[0]=(char*)bStart; v[1]=(char*)nStart;
    t[0]=(char*)"Block";       t[1]=(char*)"Net";
    util.save((char*)"sfile",2,v,t);

    util.clear(2,v,t); // otherwise you'll have two copies of the data in memory

    util.open((char*)"sfile",2,v,t);
    if(util.error())return(1); /* ZZerror=0100 if wrong file */
    bStart=(Block*)v[0];
    nStart=(Net*)v[1];

    /* for all blocks, print the x-span of all connected nets */
    bChain_iterator bIter(bStart);
    ITERATE(bIter,bp){
        nn=bName.fwd(bp);
        fprintf(file2,"block=%s nets=",nn);
        byBlock_iterator bbIter(bp);
        ITERATE(bbIter,pp){
            np=byNet.par(pp);
            x1=INF; x2= -INF;
            byNet_iterator bnIter(np);
            ITERATE(bnIter,pr){
                br=byBlock.par(pr);
                x1=MIN(x1,br->x1 + pr->x1);
                x2=MAX(x2,br->x1 + pr->x2);
            }
            nn=nName.fwd(np);
            fprintf(file2," %s(%d,%d)",nn,x1,x2);
        }
        fprintf(file2,"\n");
    }
    fprintf(file2,"\n");

    /* compare TRIANGLE and COLLECTION, print message if not the same */
    bChain_iterator kIter(bStart);
    ITERATE(kIter,bp){
        byBlock_iterator bbIter(bp);
        byCol_iterator bcIter(bp);
        for(pp= ++bbIter,pr= ++bcIter; pp&&pr; pp= ++bbIter, pr= ++bcIter){
            if(pp!=pr){
                nn=bName.fwd(bp);
                fprintf(file2,"block=%s different pins\n",nn);
            }
        }
    }

    /* test the sweap function */
    v[0]=(char*)bStart; v[1]=(char*)nStart;
    t[0]=(char*)"Block";       t[1]=(char*)"Net";
    util.swpSet(2,v,t);
    util.swpFun(myFun,(char*)file2);
    util.swpFree();
    return(0);
}
/* --------------------------------------- */
/* function to print one object */
// ZZint is interpreted as int, except under Windows7/64 it is (long long)
void myFun(char *obj,ZZint typeInd,ZZint size,const char *priv)
{
    FILE *fp;
    Block *bp;
    Net *np;
    Pin *pp;
    char *type,*nn;

    fp=(FILE *)priv;
    ZZ_TYPE_NAME(typeInd,type);
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
}
#include "zzfunc.c"
