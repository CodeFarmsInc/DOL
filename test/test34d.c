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

        util.mode(1,0,0,0); // invoke ASCII mode
        util.open("bfile",1,v,t);
        D *dp=(D*)(v[0]);
        dp->display("opened ASCII");

        util.mode(0,1,0,0); // now use binary mode
        v[0]=(char *)dp; t[0]="D";
        dp->save_all();
}
