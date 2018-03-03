/* Testing virtual functions and the automatic jump to the top
 * object - this is the ultimate wasy of saving data organizations
 * in C++ */
#include <stdio.h>
#define ZZ_INHERIT
#define ZZmain
#define ZZascii
#include "zzincl.h"


class Shape {
    ZZ_EXT_Shape
public:
    virtual void prt(void){};
};
ZZ_FORMAT(Shape,"");
    
class Square : public Shape{ 
    int x;
    ZZ_EXT_Square
public:
    void prt(void){printf("Square %d\n",x);};
    void set(int a){x=a;};
};
ZZ_FORMAT(Square,"%d,x");

class Rectangle : public Shape{
    int x,y;
    ZZ_EXT_Rectangle
public:
    void prt(void){printf("Rectangle %dx%d\n",x,y);};
    void set(int a,int b){x=a; y=b;};
};
ZZ_FORMAT(Rectangle,"%d %d,x,y");
 
ZZ_HYPER_SINGLE_RING(all,Shape);
ZZ_HYPER_UTILITIES(util);
#define BF 80
char buff[BF];

int main(void)
{
    char c[20],*v[1],*t[1];;
    int x,y;
    Square *sp;
    Rectangle *rp;
    Shape *op;
    void prtData(Shape *);

    op=(Shape *)NULL;
    while(gets(buff)){ // read in all input data
        sscanf(buff,"%c",c);
        switch(c[0]) {
            case 'S':
                sp=new(Square);
                sscanf(buff,"%c %d",&c,&x);
                sp->set(x);
                op=all.add(op,(Shape *)sp);
                break;
            case 'R':
                rp=new(Rectangle);
                sscanf(buff,"%c %d %d",&c,&x,&y);
                rp->set(x,y);
                op=all.add(op,(Shape *)rp);
                break;
            default: printf("wrong input code\n");
        }
    }

    prtData(op); // print all data as loaded
    v[0]=(char *)sp; t[0]="Square"; // only top objects as key entries
    util.save("myFile",1,v,t);
    util.open("myFile",1,v,t);
    op=(Shape *)((Shape *)(v[0]));
    prtData(op); // though in different location, result should be the same
    return(0);
}
//-------------------------------------------------------------------------
void prtData(Shape *op) //print out all data
{
    Shape *pp;

    all_iterator it(op);
    ITERATE(it,pp){
        pp->prt();
    }
}
#include "zzfunc.c"
