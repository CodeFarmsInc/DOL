/* Like test23a.c, but a more elegant way of handling the entry keys */
#include <stdio.h>
#define ZZ_INHERIT
#define ZZmain
#define ZZascii
#include "zzincl.h"

class Root
{
    ZZ_EXT_Root
public:
    void save(char *);
};
ZZ_FORMAT(Root,"");

class Shape {
    ZZ_EXT_Shape
public:
    virtual void prt(void){};
    virtual void save(char *){};
};
ZZ_FORMAT(Shape,"");
    
class Square : public Shape{ 
    int x;
    ZZ_EXT_Square
public:
    void prt(void){printf("Square %d\n",x);};
    void set(int a){x=a;};
    virtual void save(char *file);
};
ZZ_FORMAT(Square,"%d,x");

class Rectangle : public Shape{
    int x,y;
    ZZ_EXT_Rectangle
public:
    void prt(void){printf("Rectangle %dx%d\n",x,y);};
    void set(int a,int b){x=a; y=b;};
    virtual void save(char *file);
};
ZZ_FORMAT(Rectangle,"%d %d,x,y");
 
// bug in Borland 3.00: these cannot be inline
void Root::save(char *file){ZZ_STORE(Root,file);};
void Square::save(char *file){ZZ_STORE(Square,file);};
void Rectangle::save(char *file){ZZ_STORE(Rectangle,file);};

ZZ_HYPER_SINGLE_COLLECT(all,Root,Shape);
ZZ_HYPER_UTILITIES(util);
#define BF 80
char buff[BF];

int main(void)
{
    char c[20],*v[1],*t[1];;
    int x,y;
    Root *rt;
    Square *sp;
    Rectangle *rp;
    Shape *pp;
    void prtData(Root *);

    rt=new Root;
    while(gets(buff)){ // read in all input data
        sscanf(buff,"%c",c);
        switch(c[0]) {
            case 'S':
                sp=new(Square);
                sscanf(buff,"%c %d",&c,&x);
                sp->set(x);
                all.add(rt,(Shape *)sp);
                break;
            case 'R':
                rp=new(Rectangle);
                sscanf(buff,"%c %d %d",&c,&x,&y);
                rp->set(x,y);
                all.add(rt,(Shape *)rp);
                break;
            default: printf("wrong input code\n");
        }
    }

    prtData(rt); // print all data as loaded
    rt->save((char*)"afile");
    all_iterator it(rt);
    ITERATE(it,pp){
        pp->save((char*)"afile");
    }
    util.close((char*)"afile");
    v[0]=(char *)NULL; // just to make sure ZZ_OPEN really works
    util.open((char*)"afile",1,v,t); // load all data back into memory
    rt=(Root *)v[0];
    prtData(rt); // though in different location, result should be the same

    util.mode(0,1,0,0); // switch to the binary format
    rt->save((char*)"bfile");
    it.start(rt);
    ITERATE(it,pp){
        pp->save((char*)"bfile");
    }
    util.close((char*)"bfile");
    v[0]=(char *)NULL; // just to make sure ZZ_OPEN really works
    util.open((char*)"bfile",1,v,t); // load all data back into memory
    rt=(Root *)v[0];
    prtData(rt); // though in different location, result should be the same
    return(0);
}
//-------------------------------------------------------------------------
void prtData(Root *rt) //print out all data
{
    Shape *pp;

    all_iterator it(rt);
    ITERATE(it,pp){
        pp->prt();
    }
}
#include "zzfunc.c"
