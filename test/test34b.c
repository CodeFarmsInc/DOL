// combined test of virtual base classes and different ways
// of saving to disk but, compared to test34a.c, here we
// try save and open in separate runs:
// test34b: saves using blasting
// test34c: restores blasting, saves in ASCII
// test34d: restores ASCII, saves in binary
// test34e: restores binary
#define ZZmain
#include "incl34.h"

int main() {
        char *v[1],*t[1];

        util.mode(0,0,0,0); // invoke memory blasting
        util.blkAlloc(10000,10); // 1kB pages, max 10kB

        D *dp = new D;
        B *bp = (B*)dp;
        F *fp = new F;
        E *ep = new E;

        contents.add(bp, (C*)fp);
        contents.add(bp, (C*)ep);
        dp->display("new data");

        v[0]=(char *)dp;
        util.save("afile",1,v,t);
}
