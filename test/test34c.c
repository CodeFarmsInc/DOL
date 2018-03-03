// combined test of virtual base classes and different ways
// of saving to disk but, compared to test34a.c, here we
// try to save and open in separate runs:
// test34b: saves using blasting
// test34c: restores blasting, saves in ASCII
// test34d: restores ASCII, saves in binary
// test34e: restores binary
#define ZZmain
#include "incl34.h"

int main(void) {
        char *v[1],*t[1];
        D *dp;

        util.mode(0,0,0,0); // invoke memory blasting
        // util.blkAlloc(200,6);
        util.blkAlloc(10000,10);
        util.open("afile",1,v,t);
        dp=(D*)(v[0]);
        dp->display("opened blasting");
        util.mode(1,0,0,0); // save in ASCII
        util.blkFree(1);
        dp->save_all();
        return(0);
}
