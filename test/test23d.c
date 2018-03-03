// Testing virtual functions and saving on disk for arrays, second stage
#include <stdio.h>
#define ZZmain
#include "zzincl.h"
#include "test23c.h"

int main(void)
{
    char *v[1],*t[1];;
    Header *hp;
    void prtData(Header *);

    v[0]=(char *)NULL; // just to make sure ZZ_OPEN really works
    util.open((char*)"afile",1,v,t); // load all data back into memory
    hp=(Header *)v[0];
    prtData(hp); // though in different location, result should be the same

    util.mode(0,1,0,0); // switch to the binary format
    v[0]=(char *)hp; t[0]=(char*)"Header";
    util.save((char*)"bfile",1,v,t); // global save
    return(0);
}
#include "zzfunc.c"
