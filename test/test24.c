/* IMPORTANT: THIS IS A C TEST, NOT C++ TEST, but it works under C++ */
/* It also tests the built-in debugging function from util.c,
 * which is ZZ_DEB_PRT() in C, or function ZZdebPrt() in C++.
 */

/* CALLING SEQUENCE: test24 inp out1
 *    where out1 is the internal data before saving to disk
 *          the same data should appear on stdout (after save & open
 */

/* This is the same example as test0d.c, except that the big-block
 * of memory is used, sweap function is not tested, NAME organization is
 * used for names, and ZZ_FORMAT is used to specify input/output functions.
 * Most likely, the big-block memory model will be used for binary SAVE.
 * Here we test both the ASCII and binary save.
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
ZZ_ORG_NAME(bName,Block);

struct Net {
    ZZ_EXT_Net    /* let the program to hide the pointers here */
};
ZZ_FORMAT(Net,"");
ZZ_ORG_NAME(nName,Net);

struct Pin {
    ZZ_EXT_Pin    /* let the program to hide the pointers here */
    int x1,y1,x2,y2; /* pin, relative to the block lower-left corner  */
};
ZZ_FORMAT(Pin,"%d %d %d %d,x1,y1,x2,y2");

#define INF 1000000
#define MAX(A,B) ((A)<(B) ? (B) : (A))
#define MIN(A,B) ((A)>(B) ? (B) : (A))

ZZ_ORG_SINGLE_RING(bChain,Block);
ZZ_ORG_SINGLE_RING(nChain,Net);
ZZ_ORG_SINGLE_TRIANGLE(byBlock,Block,Pin);
ZZ_ORG_SINGLE_TRIANGLE(byNet,Net,Pin);

#define BSIZE 80
char name[BSIZE],buff[BSIZE];

#ifdef ZZ_ANSI
int main(int argc,char **argv)
{
    void prtBlocks(FILE*,Block*);
#else


int main(argc,argv)
int argc;
char *argv[];
{
    void prtBlocks();
    FILE *fopen();
#endif
    int x1,y1,x2,y2;
    char c,*nn,*v[2],*t[2];
    FILE *file1,*file2,*file3;
    Block *bp,*bStart;
    Net *np,*nStart;
    Pin *pp;

    if(argc<=3){
        printf("wrong call: test24 inp origData finalData\n");
	return 1;
    }
    file1=fopen(argv[1],"r");
    file2=fopen(argv[2],"w");
    file3=fopen(argv[3],"w");
    if(!file1 || !file2 || !file3){
        printf("error: cannot open one of the given files\n");
	return 2;
    }

    ZZ_BLOCK_ALLOC(1000,0);
    bStart=(Block *)NULL; nStart=(Net *)NULL;
    while(fgets(buff,BSIZE,file1)){
        sscanf(buff,"%c %s %d %d %d %d",&c,name,&x1,&y1,&x2,&y2);
        if(c=='B'){
            ZZ_PLAIN_ALLOC(Block,1,bp);
            ZZ_STRING_ALLOC(name,nn);
            bp->x1=x1; bp->y1=y1; bp->x2=x2; bp->y2=y2;
            ZZ_ADD(bName,bp,nn);
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
            ZZ_ADD(nChain,nStart,np);
N_LOOP:
            ZZF_ADD(byBlock,bp,pp);
            ZZ_ADD(byNet,np,pp);
        }
    }
    fclose(file1);
    prtBlocks(file2,bStart);            /* <<<<<<<<<<<<<<<<< */

    /* The interactive feature to debug classes does not work under Windows64 yet
     * The expected input is in inp24 */
// #ifndef Windows64
    ZZ_DEB_PRT(bStart,(char*)"Block");
// #endif
    v[0]=(char*)bStart; v[1]=(char*)nStart;
    t[0]=(char*)"Block";       t[1]=(char*)"Net";
    ZZ_BLOCK_FREE(1);
    ZZ_SAVE((char*)"afile",2,v,t);
    ZZ_BLOCK_FREE(0);
    ZZ_OPEN((char*)"afile",2,v,t);
    if(ZZerror)return(1); /* ZZerror=0100 if wrong file */
    bStart=(Block*)v[0];
    nStart=(Net*)v[1];

    ZZ_MODE_SAVE(0,1,0,0); /* switch to binary format */
    v[0]=(char*)bStart;
    t[0]=(char*)"Block";     
    ZZ_BLOCK_FREE(1);
    ZZ_SAVE((char*)"bfile",1,v,t); /* try different number of key entries */
    ZZ_BLOCK_FREE(0);
    ZZ_OPEN((char*)"bfile",1,v,t);
    if(ZZerror)return(1); /* ZZerror=0100 if wrong file */
    bStart=(Block*)v[0];
    prtBlocks(file3,bStart);            /* <<<<<<<<<<<<<<<<< */
    return(0);
}
/* ------------------------------------------------------------------ */
#ifdef ZZ_ANSI
void prtBlocks(FILE *file2,Block *bStart)
#else
void prtBlocks(file2,bStart) FILE *file2; Block *bStart;
#endif
{
    Block *bp,*br;
    Net *np;
    Pin *pp,*pr;
    int x1,x2;
    char *nn;

    /* for all blocks, print the x-span of all connected nets */
    ZZ_A_TRAVERSE(bChain,bStart,bp){
        ZZ_FORWARD(bName,bp,nn);
        fprintf(file2,"block=%s nets=",nn);
        ZZ_A_TRAVERSE(byBlock,bp,pp){
            ZZ_PARENT(byNet,pp,np);
            x1=INF; x2= -INF;
            ZZ_A_TRAVERSE(byNet,np,pr){
                ZZ_PARENT(byBlock,pr,br);
                x1=MIN(x1,br->x1 + pr->x1);
                x2=MAX(x2,br->x1 + pr->x2);
            }ZZ_A_END;
            ZZ_FORWARD(nName,np,nn);
            fprintf(file2," %s(%d,%d)",nn,x1,x2);
        }ZZ_A_END;
        fprintf(file2,"\n");
    }ZZ_A_END;
}
#include "zzfunc.c"
