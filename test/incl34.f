void prtobj(char*,void*,int);

class A 
{
public:
         virtual void print_on(void){};
         virtual void save_it(void){};
         int a1,a2,a3;
private:
         ZZ_EXT_A
};
ZZ_FORMAT(A,"%d %d %d,a1,a2,a3");

class B : virtual public A
{
public:
        virtual void print_on(void){}
        virtual void save_it(void){}
        ZZ_EXT_B
        int b1,b2;
private:
};
ZZ_FORMAT(B,"%d %d,b1,b2");

class C : virtual public A
{
public:
        virtual void print_on(void){}
        virtual void save_it(void){}
        virtual void debprt(void){}
        ZZ_EXT_C
        int c1,c2,c3;
private:
};
ZZ_FORMAT(C,"%d %d %d,c1,c2,c3");

class D : public B
{
public:
        void print_on(void){cout<<"D: "<<a1<<a2<<a3<<b1<<b2<<d1<<"\n";}
        virtual void save_it(void){ZZ_STORE(D,"bfile");}
        void save_all(void);
        void display(void);
        void debprt(void){prtobj("D:",this,sizeof(D));}
        D *newD(void){D *p; ZZ_OBJECT_ALLOC(D,p);
                            a1=a2=a3=1; b1=b2=2; d1=3; return(p);}
private:
        int d1;
        ZZ_EXT_D
};
ZZ_FORMAT(D,"%d,d1");

class E : public B, public C
{
public:
        void print_on(void){cout<<"E: "<<a1<<a2<<a3<<b1<<b2<<c1<<c2<<c3<<e1<<"\n";}
        virtual void save_it(void){ZZ_STORE(E,"bfile");}
        void debprt(void){prtobj("E:",this,sizeof(E));}
        void save_all(void);
        E *newE(void){E *p; ZZ_OBJECT_ALLOC(E,p);
                            a1=a2=a3=4; b1=b2=5; c1=c2=c3=6; e1=7; return(p);}
private:
        int e1;
        ZZ_EXT_E
};
ZZ_FORMAT(E,"%d,e1");

class F : public C
{
public:
        F *newF(void){F *p; ZZ_OBJECT_ALLOC(F,p);
                            a1=a2=a3=8; c1=c2=c3=9; f1=0; return(p);}
        void print_on(void){cout<<"F: "<<a1<<a2<<a3<<c1<<c2<<c3<<f1<<"\n";}
        virtual void save_it(void){ZZ_STORE(F,"bfile");}
        void debprt(void){prtobj("F:",this,sizeof(F));}
private:
        int f1;
        ZZ_EXT_F
};
ZZ_FORMAT(F,"%d,f1");

ZZ_HYPER_SINGLE_COLLECT(contents, B, C);
ZZ_HYPER_UTILITIES(util);
