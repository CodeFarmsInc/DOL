// -------------------------------------------------------------------
// This file tests operator-- for all data organizations that have it.
// It does this indirectly, by calling macro RETRACE, which is just
// like ITERATE, but proceeds in the reverse order.
// These tests not only test the traversal of using --, but also 
// disconnecting and destroying the entire set.
// -------------------------------------------------------------------
#include <stdio.h>
#define ZZmain
#include "zzincl.h"

class A {
    int k;
    ZZ_EXT_A
public:
    A(){ZZ_INIT(A); k=0;} // not generated automatically when A(int kk) used
    A(int kk){ZZ_INIT(A); k=kk;}
    void prt(const char *label){printf("%s A=%d\n",label,k);}
};
class B {
    int k;
    ZZ_EXT_B
public:
    B(){ZZ_INIT(B); k=0;} // not generated automatically in this case
    B(int kk){ZZ_INIT(B); k=kk;}
    void prt(const char *label){printf("%s B=%d\n",label,k);}
};
class R {
    ZZ_EXT_R
};

ZZ_HYPER_M_TO_N(mton,A,R,B);
ZZ_HYPER_DOUBLE_AGGREGATE(agg,A,B);
ZZ_HYPER_DOUBLE_COLLECT(col,A,B);
ZZ_HYPER_DOUBLE_RING(rin,B);
ZZ_HYPER_DOUBLE_TREE(tre,B);
ZZ_HYPER_M_TO_1(mto1,B,R,A);
ZZ_HYPER_1_TO_N(iton,A,R,B);

int main(){
    int i;
    A *a,*a1,*a2,*a3; 
    B *b,*bStart,*b1,*b2,*b3,*b4;
    R *r;
    a=new A;

    // Test of DOUBLE_TRIANGLE -------------------
    for(i=0; i<5; i++){
        b=new B(i);
        agg.add(a,b);
    }
    agg_iterator it1(a);
    RETRACE(it1,b){
        b->prt("aggregate");
        agg.del(b);
        delete b;
    }
    if(agg.child(a)==NULL)printf("no child left\n\n");

    // Test of DOUBLE_COLLECT -------------------
    for(i=0; i<5; i++){
        b=new B(i);
        col.add(a,b);
    }
    col_iterator it2(a);
    RETRACE(it2,b){
        b->prt("collection");
        col.del(a,b);
        delete b;
    }
    if(col.child(a)==NULL)printf("no child left\n\n");

    // Test of DOUBLE_RING -------------------
    bStart=NULL;
    for(i=0; i<5; i++){
        b=new B(i);
        bStart=rin.add(bStart,b);
    }
    rin_iterator it3(bStart);
    RETRACE(it3,b){
        b->prt("ring");
        bStart=rin.del(bStart,b);
        delete b;
    }
    if(bStart==NULL)printf("no child left\n\n");

    // Test of DOUBLE_TREE -------------------
    bStart=new B(0);
    for(i=1; i<5; i++){
        b=new B(i);
        tre.add(bStart,b);
    }
    tre_iterator it4(bStart);
    RETRACE(it4,b){
        b->prt("tree");
        tre.del(b);
        delete b;
    }
    if(tre.child(bStart)==NULL)printf("no child left\n\n");

    // Test of M_TO_1 -------------------
    for(i=0; i<5; i++){
        b=new B(i);
        r=new R;
        mto1.add(b,r,a);
    }
    mto1_iterator it5(a);
    RETRACE(it5,r){
        b=mto1.source(r);
        b->prt("mto1");
        mto1.del(r); 
        delete b; delete r;
    }
    if(mto1.bwd(a)==NULL)printf("no child left\n\n");

    // Test of 1_TO_N -------------------
    for(i=0; i<5; i++){
        b=new B(i);
        r=new R;
        iton.add(a,r,b);
    }
    iton_iterator it6(a);
    RETRACE(it6,r){
        b=iton.target(r);
        b->prt("1ton");
        iton.del(r); 
        delete b; delete r;
    }
    if(iton.fwd(a)==NULL)printf("no child left\n\n");

    // Test of M_TO_N ----------------------
    // We will not destroy objects, just traverse them
    a1=new A(11); r=new R; b1=new B(21); mton.add(a1,r,b1);
                  r=new R; b2=new B(22); mton.add(a1,r,b2);
                  r=new R; b3=new B(23); mton.add(a1,r,b3);
    a2=new A(12); r=new R; b4=new B(24); mton.add(a2,r,b4);
                  r=new R;               mton.add(a2,r,b1);
    a3=new A(13); r=new R;               mton.add(a3,r,b1);
    
    mton_sIterator it7(a1);
    RETRACE(it7,r){
        b=mton.target(r);
        b->prt("mton from A11 to");
    }
    mton_tIterator it8(b1);
    RETRACE(it8,r){
        a=mton.source(r);
        a->prt("mton from B21 to");
    }

    return 0;
}
#include "zzfunc.c"
