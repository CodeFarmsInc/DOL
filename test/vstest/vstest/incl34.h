#define ZZascii
#define ZZnoDestr
#include <stdio.h>
#ifdef UNIX
#include <stream.h>
#else
#include <iostream.h>
#endif
#include "zzincl.h"
void prtobj(char*,void*,int);

class A 
{
public:
         virtual void print_on(void){};
         // virtual void print_on(void)=0; does not work with DOL
 
         virtual void save_it(char *fName){};
         // virtual void save_it(char *fName)=0; does not work with DOL

         int a1,a2,a3;
private:
         ZZ_EXT_A
};
ZZ_FORMAT(A,"%d %d %d,a1,a2,a3");

class B 
{
public:
        virtual void print_on(void){}
        virtual void save_it(char *fName){}
        B();
        ~B();
        ZZ_EXT_B
        int b1,b2;
};
ZZ_FORMAT(B,"%d %d,b1,b2");

class C : virtual public A
{
public:
        virtual void print_on(void){}
        virtual void save_it(char *fName){}
        virtual void debprt(void){}
        C();
        ~C();
        ZZ_EXT_C
        int c1,c2,c3;
};
ZZ_FORMAT(C,"%d %d %d,c1,c2,c3");

class D : public B
{
public:
        void print_on(void){cout<<"D: "<<b1<<b2<<d1<<"\n";}
        virtual void save_it(char *fName){ZZ_STORE(D,fName);}
        void save_all(char *fName);
        void display(char *label);
        void debprt(void){prtobj("D:",this,sizeof(D));}
        D();
        ~D();
        int d1;
        ZZ_EXT_D
};
ZZ_FORMAT(D,"%d,d1");

class E : public D, public C
{
public:
        void print_on(void){cout<<"E: "<<a1<<a2<<a3<<b1<<b2<<c1<<c2<<c3<<e1<<"\n";}
        virtual void save_it(char *fName){ZZ_STORE(E,fName);}
        void debprt(void){prtobj("E:",this,sizeof(E));}
        void save_all(char *fName);
        E();
        ~E();
private:
        int e1;
        ZZ_EXT_E
};
ZZ_FORMAT(E,"%d,e1");

class F : public C
{
public:
        F();
        ~F();
        void print_on(void){cout<<"F: "<<a1<<a2<<a3<<c1<<c2<<c3<<f1<<"\n";}
        virtual void save_it(char *fName){ZZ_STORE(F,fName);}
        void debprt(void){prtobj("F:",this,sizeof(F));}
private:
        int f1;
        ZZ_EXT_F
};
ZZ_FORMAT(F,"%d,f1");

ZZ_HYPER_SINGLE_COLLECT(contents, B, C);
ZZ_HYPER_UTILITIES(util);

B::B(){};
B::~B(){ZZ_CHECK(B);}
C::C(){a1=a2=a3=8; c1=c2=c3=9;};
C::~C(){ZZ_CHECK(C);}
D::D(){b1=b2=2; d1=3;}
D::~D(){ZZ_CHECK(D);}
E::E(){b1=b2=5; a1=a2=a3=8; c1=c2=c3=6; d1=3; e1=7;}
E::~E(){ZZ_CHECK(E);}
F::F(){a1=a2=a3=8; c1=c2=c3=9; f1=1;}
F::~F(){ZZ_CHECK(F);}
void D::save_all(char *fName) {
        C *cp; B *bp;
        ZZ_KEY_SAVE(D,fName,this);
        ZZ_STORE(D,fName);
        bp=(B *)this;
        contents_iterator it(bp);
        for (cp = ++it;cp;cp= ++it){
            cp->save_it(fName);
        }
        util.close(fName);
}

void D::display(char *label) {
        C *cp;
        cout<<label<<":\n";
        this->print_on();
        contents_iterator it((B*)this);
        for (cp = ++it;cp;cp= ++it){
            cp->print_on();
        }
}

// debugging function to display contents of objects
//  and internal pointers
void prtobj(char *label,void *p,int s){
    char **pp,**sp,*t;

    printf("%s\n",label);
    t=(char *)p;
    sp=(char **)(t+s);
    for(pp=(char **)p; pp!=sp; pp++)printf("  %d %d\n",pp,*pp);
}
#include "zzfunc.c"
