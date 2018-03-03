// This is the same program as test23a.c, but coded in a different,
// more object-oriented style.

#include <stdio.h>
#define ZZ_INHERIT
#define ZZmain
#define ZZascii
#include "zzincl.h"

class Shape {
    static Shape *op;
    static char *tp;
    ZZ_EXT_Shape
public:
    virtual void prt(void){};
    virtual void save(char *){};
    void add(char *type);
    void prtData(void);
    void saveAll(char *fileName);
    Shape* openAll(char *fileName);
    void destroy(void);
};
Shape* Shape::op=NULL;
char* Shape::tp=NULL;
ZZ_FORMAT(Shape,"");
    
class Square : public Shape{ 
    int x;
    ZZ_EXT_Square
public:
    void prt(void){printf("Square %d\n",x);};
    Square(int a){x=a;};
    // not generated automatically when other constructor is used:
    Square(){ZZ_INIT(Square);} 
    virtual void save(char *file);
};
ZZ_FORMAT(Square,"%d,x");

class Rectangle : public Shape{
    int x,y;
    ZZ_EXT_Rectangle
public:
    void prt(void){printf("Rectangle %dx%d\n",x,y);};
    Rectangle(int a,int b){x=a; y=b;};
    // not generated automatically when other constructor is used:
    Rectangle(){ZZ_INIT(Rectangle);} 
    virtual void save(char *file);
};
ZZ_FORMAT(Rectangle,"%d %d,x,y");
 
ZZ_HYPER_SINGLE_RING(all,Shape);
ZZ_HYPER_UTILITIES(util);

void Square::save(char *file){ZZ_STORE(Square,file);};
void Rectangle::save(char *file){ZZ_STORE(Rectangle,file);};
void Shape::add(char *type){ (void)all.add(op,this); op=this; if(!tp)tp=type;}
void Shape::prtData(void){Shape *pp;
    all_iterator it(op); for(pp= ++it;pp;pp= ++it)pp->prt(); printf("\n");}
void Shape::saveAll(char *fn){ Shape *pp;
    op->save(fn);
    all_iterator it(op); // traverse all data, save each object
    for(pp= ++it;pp;pp= ++it){pp->save(fn); } util.close(fn);
}
void Shape::destroy(void){ Shape *pp;
    all_iterator it(op); // traverse all data, save each object
    for(pp= ++it;pp;pp= ++it){ op=all.del(op,pp); } 
    op=(Shape *)NULL;
}
Shape* Shape::openAll(char *fn){ char *v[1],*t[1];
    util.open(fn,1,v,t); // load all data back into memory
    if(!strcmp(t[0],"Square"))Shape::op=(Shape *)((Square *)v[0]);
    if(!strcmp(t[0],"Rectangle"))Shape::op=(Shape *)((Rectangle *)v[0]);
    return(op);
}

#define BF 80
char buff[BF];

int main(void)
{
    char c[20];
    int x,y;
    Square *sp;
    Rectangle *rp;
    Shape *pp;
    void prtData(Shape *);

    while(gets(buff)){ // read in all input data
        sscanf(buff,"%c",c);
        switch(c[0]) {
            case 'S':
                sscanf(buff,"%c %d",&c,&x);
                sp=new Square(x);
                pp=((Shape *)sp);
                pp->add((char*)"Square");
                break;
            case 'R':
                sscanf(buff,"%c %d %d",&c,&x,&y);
                rp=new Rectangle(x,y);
                pp=((Shape *)rp);
                pp->add((char*)"Rectangle");
                break;
            default: printf("wrong input code\n");
        }
    }

    pp->prtData(); // print all data as loaded
    pp->saveAll((char*)"afile"); // traverse data and save each object
    pp->destroy();        // destroy all memory data
    pp->openAll((char*)"afile");  // reload all data from disk

    pp->prtData(); // though in different location, result should be the same
    return(0);
}
//-------------------------------------------------------------------------
#include "zzfunc.c"
