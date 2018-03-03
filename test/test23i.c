/* Testing virtual functions and saving on disk, in both ASCII and binary */
#include <stdio.h>
#define ZZ_INHERIT
#define ZZmain
#define ZZascii
#include "zzincl.h"


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
void Square::save(char *file){ZZ_STORE(Square,file);};
void Rectangle::save(char *file){ZZ_STORE(Rectangle,file);};

ZZ_HYPER_SINGLE_RING(all,Shape);
ZZ_HYPER_UTILITIES(util);
#define BF 80
char buff[BF];
void myFun(char *obj, int type, int size, char *priv);

int main(void)
{
    char c[20];
    int x,y;
    Square *sp;
    Rectangle *rp;
    Shape *op,*gOpen(char*);
    void prtData(Shape *),gSave(Shape*,char*);

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

    gSave(op,"bfile");
    op=gOpen("bfile");
    prtData(op); // though in different location, result should be the same

    util.mode(0,1,0,0); // switch to the binary format
    gSave(op,"bfile");
    op=gOpen("bfile");
    prtData(op); // though in different location, result should be the same
    return(0);
}
//-------------------------------------------------------------------------
// global save using the sweep function
void gSave(Shape *op, char *fName){
    char *v[1],*t[1];

    v[0]=(char*)op;
    t[0]="Shape";
    util.swpSet(1,v,t);
    util.swpFun(myFun,fName);
    util.close(fName);
}
//-------------------------------------------------------------------------
// global open to save repetition of the same code
Shape *gOpen(char *fName){
    char *v[1],*t[1];
    Shape *op;

    v[0]=(char *)NULL; // just to make sure ZZ_OPEN really works
    util.open(fName,1,v,t); // load all data back into memory
    if(!strcmp(t[0],"Square"))op=(Shape *)((Square *)v[0]);
    if(!strcmp(t[0],"Rectangle"))op=(Shape *)((Rectangle *)v[0]);
    return(op);
}
//-------------------------------------------------------------------------
/* function to print one object */
void myFun(char *obj,int typeInd,int size,char *priv)
{
    Shape *pp;
    Rectangle *re;
    Square *sq;
    char *type;

    size=size; // avoid compiler warnings
    type=util.type(typeInd);
    if(!strcmp(type,"Shape")){
        pp=(Shape *)obj;
        pp->save(priv);
    }
    else if(!strcmp(type,"Rectangle")){
        re=(Rectangle *)obj;
        re->save(priv);
    }
    else if(!strcmp(type,"Square")){
        sq=(Square *)obj;
        sq->save(priv);
    }
    else printf("%d %s=unknown type\n",typeInd,type);
}
//-------------------------------------------------------------------------
void prtData(Shape *op) //print out all data
{
    Shape *pp;

    all_iterator it(op);
    for(pp= ++it; pp; pp= ++it){
        pp->prt();
    }
}
#include "zzfunc.c"
