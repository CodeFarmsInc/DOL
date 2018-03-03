// This test shows two ways of using OrgC++ within a local scope.
#include <stdio.h>
#define ZZmain
#include "zzincl.h"

class A;
class B {
    ZZ_EXT_B
public:
    A *aPtr;
    B(){};
};
class A {
    static B *entry;
    B b;
    int a;
    ZZ_EXT_A
public:
    A(int i);
    A(){} // must be given when the other constructor is used
   ~A();
    A *next(void);
    void prt(void){printf("%d\n",a);};
};
B * A::entry=NULL;
ZZ_HYPER_SINGLE_RING(ring1,B);
A::~A(){if(entry){entry=ring1.del(entry,&(this->b));}}
A::A(int i){ ZZ_INIT(A);
       a=i; entry=ring1.add(entry,&(this->b)); b.aPtr=this;}
A* A::next(void){return(ring1.fwd(&(this->b))->aPtr);}

int main(void){
    A *a; int i;

    for(i=0;i<5;i++)a=new A(i);
    for(i=0;i<5;i++, a=a->next())a->prt();
    return(0);
}
#include "zzfunc.c"

