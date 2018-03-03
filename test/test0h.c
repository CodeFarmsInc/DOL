/* The same problem as test0g, except that the RING class is also
 * implemented with OrgC. This is not a standard way of using
 * the orgC library - it is mixing the C and C++ style together
 * just as a test.
 */
#include <stdio.h>
#define ZZmain
#include "zzincl.h"

typedef void* ent;

struct RING {      /* single linked ring */
    ZZ_EXT_RING
    RING *add(RING* start,RING* newp);
    RING *next(RING* ptr);
};
ZZ_ORG_SINGLE_RING(myRing,RING);
RING* RING::next(RING* ptr){RING *nxt;ZZ_FORWARD(myRing,ptr,nxt);return(nxt);};


struct Block : public RING {
    ZZ_EXT_Block
    char *name;
    int x1,y1,x2,y2; /* corners of the block */
    Block *add(Block *start, Block *newp)
	             {return((Block *)RING::add(start,newp));}
    Block *next(Block *ptr){return((Block *)RING::next(ptr));}
};

struct NetRing : public RING {
friend struct Net;
    Net *net;
    NetRing *add(NetRing *start, NetRing *newp)
	           {return((NetRing *)RING::add(start,newp));}
    NetRing *next(NetRing *ptr)
		         {return((NetRing *)RING::next(ptr));}
};

struct Net {
    ZZ_EXT_Net  
    char *name;
    struct NetRing *nRing;
};

struct Pin {
    ZZ_EXT_Pin 
    int x1,y1,x2,y2; /* relative to the block lower-left corner */
};

#define INF 10000
#define MAX(A,B) ((A)<(B) ? (B) : (A))
#define MIN(A,B) ((A)>(B) ? (B) : (A))

ZZ_ORG_SINGLE_TRIANGLE(byBlock,Block,Pin);
ZZ_ORG_SINGLE_TRIANGLE(byNet,Net,Pin);

#define BSIZE 80

int main(int argc,char *argv[])
{
    int x1,y1,x2,y2;
    char c,name[BSIZE],buff[BSIZE],*nn;
    FILE *file1,*file2;
    Block *bp,*br,*bStart;
    Net *np;
    NetRing *nrp,*nrStart;
    Pin *pp,*pr;

    if(argc<=1)file1=stdin;  else file1=fopen(argv[1],"r");
    if(argc<=2)file2=stdout; else file2=fopen(argv[2],"w");

    bStart=(Block *)NULL; nrStart=(NetRing *)NULL;
    while(fgets(buff,BSIZE,file1)){
        sscanf(buff,"%c %s %d %d %d %d\n",
		     	      &c,name,&x1,&y1,&x2,&y2);
        if(c=='B'){
            ZZ_PLAIN_ALLOC(Block,1,bp);
            bp->x1=x1; bp->y1=y1; bp->x2=x2; bp->y2=y2;
            ZZ_STRING_ALLOC(name,nn);
            bp->name=nn;
	    bStart=(*bp).add(bStart,bp);
        }
        else if(c=='P'){
            ZZ_PLAIN_ALLOC(Pin,1,pp);
            pp->x1=x1; pp->y1=y1; pp->x2=x2; pp->y2=y2;
            /* is this net already listed ? */
            for(nrp=nrStart; nrp; ){
		np=nrp->net;
                if(!strcmp(name,np->name))goto N_LOOP;
		nrp=(*nrp).next(nrp);
		if(nrp==nrStart)break;
	    }
            ZZ_PLAIN_ALLOC(Net,1,np);
            ZZ_STRING_ALLOC(name,nn);
            np->name=nn;
            nrp= new NetRing;
	    nrp->net=np;
	    np->nRing=nrp;
	    nrStart=(*nrp).add(nrStart,nrp);
N_LOOP:
            ZZadd(byBlock,bp,pp);
            ZZ_ADD(byNet,np,pp);
        }
    }
    fclose(file1);

    /* for all blocks, print the x-span of all nets */
    bStart=(*bStart).next(bStart); /* shift start to get reverse order */
    for(bp=bStart;bp;){
        fprintf(file2,"block=%s nets=",bp->name);
        ZZ_A_TRAVERSE(byBlock,bp,pp){
            ZZ_PARENT(byNet,pp,np);
            x1=INF; x2= -INF;
            ZZ_A_TRAVERSE(byNet,np,pr){
                ZZ_PARENT(byBlock,pr,br);
                x1=MIN(x1,br->x1 + pr->x1);
                x2=MAX(x2,br->x1 + pr->x2);
            }ZZ_A_END;
            fprintf(file2," %s(%d,%d)",np->name,x1,x2);
        }ZZ_A_END;
        fprintf(file2,"\n");
        bp=(*bp).next(bp);
        if(bp==bStart)break;
    }
    return(0);
}
/* --------------------------------------------------- */
/* function RING::add() would be a part of C++ library */
RING *RING::add(RING *start, RING *newp)
{
    ZZ_ADD(myRing,start,newp);
    return(start);
}
#include "zzfunc.c"
