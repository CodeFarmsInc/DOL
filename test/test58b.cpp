#include "zzincl.h"

// must include all classes which share a relation with B
#include "test58a.h"
#include "test58b.h"

// only relations which involve B
ZZ_HYPER_SINGLE_AGGREGATE(aggr,B,A);

// This constructor not only sets 'b', it also adds i objects of type A
B::B(int i){
    int k; A *a;

    b=i;
    for(k=0; k<i; k++){
        a=new A(k);
        aggr.add(this,a);
        aggr.set(a); // just to maintain the same order
    }
}
    
void B::prt(){printf("B=%d\n",b);}
