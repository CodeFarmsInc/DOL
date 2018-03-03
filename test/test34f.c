// Combined test of virtual base classes and different ways
// of saving to disk. All methods tried within the same run.
//
// This is the same test as test34a.c, but due to various limitations
// of Borland3.0 compiler, the code is more complicated and not as
// easy to read. The main problems with Borland:
//
// Borland 3.0 does not allow assignment to 'this' in the constructor,
// and OrgC++ library is already setting up the operator new().
// That requires to use newD(), newE(), newF() in places, where
// AT&T UNIX can simply use a constructor.
//
// For example, what in UNIX is:
//   D(){ZZ_OBJECT_ALLOC(D,this); a1=a2=a3=1; b1=b2=2; d1=3;}
// Here is coded as:
//   D *newD(void){D *p;ZZ_OBJECT_ALLOC(D,p);a1=a2=a3=1;b1=b2=2;d1=3;return(p);}
//
// For traversing loops, the simple UNIX form 
//   while (cp = it++){
// must be replaced under Borland by
//   for(cp= ++it; cp; cp= ++it){
// 
// After all this the program still would not run, in spite of playing
// around with the positions of functions and files, it does not link
// in ZZ_GENERAL_EXT(), even if I compile zzfunc.c separately.
// Try to compile test34f.c and test34g.c together. The result should
// be the same as for test34a.c.

#define ZZmain
#define ZZascii
#include <stdio.h>
#ifdef UNIX
#include <stream.h>
#else
#include <iostream.h>
#endif
#include "zzincl.h"
#include "incl34.f"

void D::save_all(void) {
        C *cp; B *bp;
        ZZ_KEY_SAVE(D,"bfile",this);
        ZZ_STORE(D,"bfile");
        bp=(B *)this;
        contents_iterator it(bp);
        for(cp= ++it; cp; cp= ++it){ // while (cp = it++){
            cp->save_it();
        }
        util.close("bfile");
}

void D::display(void) {
        C *cp;
        contents_iterator it((B*)this);
        for(cp= ++it; cp; cp= ++it){ // while(cp = it++){
            cp->print_on();
        }
}

void inhprt(char *);

int main(void) {
    char *v[1],*t[1];
    D d; E e; F f; // for allocation, enforced by Borland only

    util.blkAlloc(10000,10); // 1kB pages, max 10kB
    util.mode(2,0,0,0); // memory blasting

    D *dp = d.newD();
    B *bp = (B*)dp;
    F *fp = f.newF();
    E *ep = e.newE();

    contents.add(bp, (C*)fp);
    contents.add(bp, (C*)ep);
    dp->display();

    v[0]=(char *)dp;
    util.save("afile",1,v,t);
    util.clear(1,v,t);
    util.open("afile",1,v,t);
    dp=(D*)(v[0]);
    dp->display();
    util.blkFree(1);

    util.mode(1,0,0,0); // invoke ASCII mode
    dp->save_all();
    util.open("bfile",1,v,t);
    dp=(D*)(v[0]);
    dp->display();

    util.mode(0,1,0,0); // invoke binary mode
    v[0]=(char *)dp; t[0]="D";
    dp->save_all();
    util.open("bfile",1,v,t);
    dp=(D*)(v[0]);
    dp->display();
    return(0);
}
