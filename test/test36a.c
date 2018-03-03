// Testing OrgC++ organization with a local scope
// Here RING myRing is knows only within the scope of class A
// This is a UNIX version for C++ 2.0, look at test36b.c for C++ 2.1
// This test did not work with ULTRIX DEC C++, but may be now after the
// latest fix (J.S. Feb.16/94)

// IMPORTANT: If you use C++ version 2.1 or higher, you must define ZZcplus21
//            instead of just ZZcplus in your environment file
//            The best is if you modify file lib/env3s.h accordingly

#include <stdio.h>
#define ZZmain
#include "zzincl.h"

class A {
    static A *entry;
    int a;
public:
    ZZ_EXT_A
    int val(void){return a;};
    A(){entry=NULL;}
    A(int i);
    ~A();
    A* next(void);
    ZZ_LOCAL_SINGLE_RING(myRing,A,A);
};
ZZ_HYPER_UTILITIES(util);

A* A::entry;
A* A::next(void){return myRing.fwd(this);}
A::A(int i){a=i; entry=myRing.add(entry,this);}
A::~A(){if(entry)entry=myRing.del(entry,this);}

int main(void){
    A aa,*a1,*a2;

    a1=new A(1);
    a2=new A(2);

    a2=a1->next();
    printf("%d %d\n",a1->val(),a2->val());

    // a1=myRing.fwd(a2);  causes compiler error, unknown myRing
}
#include "zzfunc.c"
