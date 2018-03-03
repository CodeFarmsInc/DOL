/* Testing virtual functions and saving on disk for arrays, second stage */
#include <stdio.h>
#include "zzincl.h"
#include "test23c.h"

void prtData(Header *hp) //print out all data
{
    Square *sp;
    Rectangle *rp;
    ZZint i,size,wMark,incr;

    printf("-----------------\n");
    size=sqrs.size(hp,&wMark,&incr);
    for(i=0;i<=wMark;i++){
        sp=sqrs.ind(hp,i);
        sp->prt();
    }

    size=recs.size(hp,&wMark,&incr);
    for(i=0;i<=wMark;i++){
        rp=recs.ind(hp,i);
        rp->prt();
    }
    size=size; // TurboC++ complains about unused variable
}
