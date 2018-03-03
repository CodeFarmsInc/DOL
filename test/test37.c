// This example tests an array of objects that have virtual
// functions.
// I am working on this right now ... JS, Apr.15/92
#include <stdio.h>
#define ZZmain
#define ZZascii
#define ZZnoDestr
#include "zzincl.h"

class H{   // dummy header object to keep the array
  ZZ_EXT_H
};
ZZ_FORMAT(H,"");

class A{
  ZZ_EXT_A
public:
  int a;
  virtual void prt(void){};
  virtual void clr(void){};
};
ZZ_FORMAT(A,"%d,a");

class B : public A{
  ZZ_EXT_B
public:
  int b;
  void prt(void){printf("b=%d\n",b);}
  void clr(void){b=0;}
};
ZZ_FORMAT(B,"%d,b");

class C : public A{
  ZZ_EXT_C
public:
  int c;
  void prt(void){printf("c=%d\n",c);}
  void clr(void){c=0;}
};
ZZ_FORMAT(C,"%d,c");

ZZ_HYPER_SINGLE_RING(aRing,A);
ZZ_HYPER_ARRAY(bb,H,B);
ZZ_HYPER_UTILITIES(util);

// destructive display, which changes the content of the data
void display(A *entry){
    A *a;
    printf("-----\n");
    aRing_iterator it(entry);
    ITERATE(it,a){
        a->prt();
        a->clr();
    }
}

int main(void){
    A *entry; B *b; C *c; H *h;
    char *v[3],*t[3];
    int i;

    h=new H;
    bb.form(h,6,0); // must be fixed if pointers point into array
    entry=(A *)NULL;
    for(i=0;i<5;i++){
        b=bb.ind(h,i);
        b->b=i;
        entry=aRing.add(entry,(A *)b);
    }
    c=new C; c->c=9;
    entry=aRing.add(entry,(A *)c);

    v[0]=(char *)(h); v[1]=(char *)entry; v[2]=(char *)c;
    t[0]=(char*)"H";         t[1]=(char*)"A";           t[2]=(char*)"C";
    util.save("sFile",3,v,t); // save to disk
    display(entry);    // display sets all attributes to 0
    v[1]=(char *)NULL; // prevent using old data

    util.open("sFile",3,v,t); // retrieve from disk
    h=(H *)(v[0]); entry=(A *)(v[1]); c=(C *)(v[2]);
    display(entry);
    return(0);
}
#include "zzfunc.c"
