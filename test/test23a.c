// Testing virtual functions and saving to disk in different modes.
// Some savings are global (giving a root objects), some save individual
// objects which is a special, normally not recommended method.
//
// Test23a: Creates data, saves in ascii, opens in ascii, saves in binary.
// Test23b: Same as test23a, but free lists are used.
// Test23i: Same as test23a but coded in a better, more object-oriented style
// Test23j: Same as test23a but better handling of roots.
//
// Test23c: First test of a series. One object with array, save in ascii
// Test23d: Getting the ascii data and saving it in binary.
// Test23e: Read the binary data, check it is still the same.
//
// Test23f: Create about 350kB of data, save and then open in mem.blasting
// Test23g: Same program mangled for the Borland compiler very long time ago
// Test23k: Create a ring of objects, save and open it in binary.
// Test23x: Auxilliary function prtData() needed by all the other test23*.c.

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

int main(void)
{
    char c[20],*v[1],*t[1];;
    int x,y;
    Square *sp;
    Rectangle *rp;
    Shape *op,*pp;
    void prtData(Shape *);

    op=(Shape *)NULL;
    v[0]=(char *)NULL; // catch the first object and its type
    while(gets(buff)){ // read in all input data
        sscanf(buff,"%c",c);
        switch(c[0]) {
            case 'S':
                sp=new(Square);
                sscanf(buff,"%c %d",&c,&x);
                sp->set(x);
                op=all.add(op,(Shape *)sp);
                if(!v[0]){v[0]=(char *)sp; t[0]=(char*)"Square";}
                break;
            case 'R':
                rp=new(Rectangle);
                sscanf(buff,"%c %d %d",&c,&x,&y);
                rp->set(x,y);
                op=all.add(op,(Shape *)rp);
                if(!v[0]){v[0]=(char *)rp; t[0]=(char*)"Rectangle";}
                break;
            default: printf("wrong input code\n");
        }
    }

    prtData(op); // print all data as loaded
    all_iterator it(op);
    for(pp= ++it; pp; pp= ++it){
        pp->save((char*)"afile");
    }
    util.close((char*)"afile");
    v[0]=(char *)NULL; // just to make sure ZZ_OPEN really works
    util.open((char*)"afile",1,v,t); // load all data back into memory
    if(!strcmp(t[0],"Square"))op=(Shape *)((Square *)v[0]);
    if(!strcmp(t[0],"Rectangle"))op=(Shape *)((Rectangle *)v[0]);
    prtData(op); // though in different location, result should be the same

    util.mode(0,1,0,0); // switch to the binary format
    it.start(op);
    for(pp= ++it; pp; pp= ++it){
        pp->save((char*)"bfile");
    }
    util.close((char*)"bfile");
    v[0]=(char *)NULL; // just to make sure ZZ_OPEN really works
    util.open((char*)"bfile",1,v,t); // load all data back into memory
    if(!strcmp(t[0],"Square"))op=(Shape *)((Square *)v[0]);
    if(!strcmp(t[0],"Rectangle"))op=(Shape *)((Rectangle *)v[0]);
    prtData(op); // though in different location, result should be the same
    return(0);
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
