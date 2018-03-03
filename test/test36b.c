// Testing OrgC++ organization with a local scope
// Here RING myRing is knows only within the scope of class A
// This is a Borland 3.0 version for C++ 2.1
//
// Borland 3.0 does not handle friends between nested classes correctly
// For that reason, ZZ_EXT_ is public here, though it normally should be private
//
// Also, if a static variable is private, its functions still can be 
// accessed from the outside. There is no way to block myRing from the
// outside access. I am disappointed. I don't know whether this is
// Borland's problem, or C++ 2.1.
// Lucid compiler 2.2 also cannot handle this.
//
// Note that methods of myRing can be used inside inline functions of class A
// because the ZZ_LOCAL_.. statement is also inside A, not after it as it
// happens when the ZZ_HYPER_.. statement is used.

#include <stdio.h>
#define ZZmain
#define ZZcplus21
#include "zzincl.h"

class A {
    int a;
    static A *entry;
public:
    ZZ_LOCAL_SINGLE_RING(myRing,A,A);  // IMPORTANT: must be before ZZ_EXT

    ZZ_EXT_A
    int val(void){return a;};
    A(){}
    A(int i){a=i; entry=A::myRing.add(entry,this);}
    ~A(){if(entry)entry=myRing.del(entry,this);}
    A* next(void){return A::myRing.fwd(this);}
};
A* A::entry=NULL;
#include "zzfunc.c"


int main(void){
    A *a1,*a2;

    a1=new A(1);
    a2=new A(2);

    a2=a1->next();
    printf("%d %d\n",a1->val(),a2->val());

    return(0);
}
