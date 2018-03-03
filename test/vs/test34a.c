void inhprt(char *);
// combined test of virtual base classes and different ways
// of saving to disk. All methods tried within the same run.
//
// WARNING: test34*.c programs do not run with some of the most
//          recent compilers such as Lucid or Borland 3.1, probably
//          because of the obsolete assignment to 'this' in some constructors
#define ZZmain
#include "incl34.h"

int main() {
        char *v[1],*t[1];

        // util.blkAlloc(10000,10); // 1kB pages, max 10kB
        util.mode(1,0,0,0); // invoke memory blasting

        D *dp = new D;
        B *bp = (B*)dp;
        F *fp = new F;
        E *ep = new E;

        contents.add(bp, (C*)fp);
        contents.add(bp, (C*)ep);
        dp->display("initial data");

        v[0]=(char *)dp; t[0]="D";
        util.save("mfile",1,v,t);
        util.clear(1,v,t);
        util.open("mfile",1,v,t);
        dp=(D*)(v[0]);
        dp->display("after blasting");
/* JS
        util.blkFree(1); // switch to the normal allocation (from the heap)

        util.mode(1,0,0,0); // invoke ASCII mode
        dp->save_all("afile"); t[0]="D"; // saves to "afile"
        util.open("afile",1,v,t);
        dp->display("after non-standard ASCII");
*/

        util.mode(0,1,0,0); // invoke binary mode
        v[0]=(char *)dp; t[0]="D";
        dp->save_all("bFile");
        util.open("bfile",1,v,t);
        dp=(D*)(v[0]);
        dp->display("after binary");
        return 0;
}
