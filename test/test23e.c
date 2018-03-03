// Testing virtual functions and saving on disk for arrays, third stage
#include <stdio.h>
#define ZZmain
#include "zzincl.h"
#include "test23c.h"

int main(void)
{
    char *v[1],*t[1];;
    Header *hp;
    void prtData(Header *);

    util.mode(0,1,0,0); // use the binary format with IO buffering
    v[0]=(char *)NULL; // just to make sure ZZ_OPEN really works
    util.open((char*)"bfile",1,v,t); // load all data back into memory
    hp=(Header *)v[0];
    prtData(hp); // though in different location, result should be the same
    return(0);
}
#include "zzfunc.c"
