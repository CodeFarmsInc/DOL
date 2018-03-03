// Simple test of function app() for SINGLE_COLLECT
#define ZZmain
#include <stdio.h>
#include "zzincl.h"

class A {
    ZZ_EXT_A
};
class B {
    int b;
    ZZ_EXT_B
public:
    B(){ZZ_INIT(B);}
    B(int i){ZZ_INIT(B); b=i;}
    void prt(){printf("%d ",b);}
};

ZZ_HYPER_SINGLE_COLLECT(col,A,B);

int main(){
    A* a; B *b[10],*bp; int i;

    a=new A;
    for(i=1; i<=9; i++)b[i]=new B(i);
    col.add(a,b[7]); col.add(a,b[5]); col.add(a,b[3]); col.add(a,b[1]);
    col.app(a,b[5],b[6]);
    col.app(a,b[3],b[4]);
    col.app(a,b[7],b[8]);
    col.app(a,b[1],b[2]);
    col.app(a,b[8],b[9]);
    col_iterator it(a);
    ITERATE(it,bp){ bp->prt(); }
    printf("\n");
    return 0;
}
#include "zzfunc.c"
