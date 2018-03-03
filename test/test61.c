// Testing ASCII save and ZZ_FORMAT for derived classes.
#include <stdio.h>
#define ZZ_INHERIT
#define ZZmain
#define ZZascii
#include "zzincl.h"

class Root {
    ZZ_EXT_Root
public:
};
ZZ_FORMAT(Root,"");

class Shape {
protected:
    int heigth;
    int width;
    ZZ_EXT_Shape
public:
    virtual void prt(){};
};
ZZ_FORMAT(Shape,"%d %d,heigth,width");
    
class Peak : public Shape{ 
    int mass;
    ZZ_EXT_Peak
public:
    Peak(int h,int w,int m){ZZ_INIT(Peak); heigth=h; width=w; mass=m;}
    Peak(){ZZ_INIT(Peak);} // not automatically generated in this situation
    void prt(){printf("h=%d w=%d m=%d\n",heigth,width,mass);}
};
ZZ_FORMAT(Peak,"%d,mass");


ZZ_HYPER_SINGLE_COLLECT(shapes,Root,Shape);
ZZ_HYPER_UTILITIES(util);

int main(void){
    Root *rt; Shape *sh;  char *v[1],*t[1];
    rt=new Root;
    sh=new Peak(7,8,9);
    sh->prt();
    shapes.add(rt,sh);

    v[0]=(char*)rt; t[0]=(char*)"Root";
    util.save("data61",1,v,t);
    rt=NULL;
    sh=NULL;

    util.open("data61",1,v,t);
    rt=(Root*)(v[0]);
    sh=shapes.child(rt);
    sh->prt();
    
    return(0);
}
#include "zzfunc.c"
