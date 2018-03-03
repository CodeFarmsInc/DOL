// This program demonstrates how to structure the code
// with separate *.h and *.cpp for each application class

#define ZZmain
#include "zzincl.h"
#include "test58a.h"
#include "test58b.h"
// with ZZmain and zzfunc.c, all the relations must be included
#include "test58r.h"

int main(){
    B *b; A *a; void *v[1]; char *t[1];
    aggr_iterator git;

    b=new B(7);
    b->prt();
     
    git.start(b);
    ITERATE(git,a){
        a->prt();
    }

    v[0]=b; t[0]=(char*)"B";
    util.save("myFile",1,v,t);
    return 0;
}    

#include "zzfunc.c"
