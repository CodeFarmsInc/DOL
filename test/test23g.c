// Testing virtual functions and saving on disk with bitmap memory blasting.
// The program generates about 35kB of data.
//
// This is program is just a version of test23f.c mangled so that Borland 3.00
// accepts it.
#include <stdio.h>
#define ZZmain
#include "zzincl.h"

// The following parameters correspond to 35kB data with 2**14=16kB pages
#define TOTAL_MEMORY 35000
#define MEMORY_LIMIT 60000
#define PAGE_BITS 14
int numObj;

class Shape {
    ZZ_EXT_Shape
public:
    virtual int get(){return(0);}; // SUN C++ compiler requires this
};
ZZ_HYPER_SINGLE_RING(all,Shape);
ZZ_HYPER_UTILITIES(util);
    
class Square : public Shape{ 
    int x;
    ZZ_EXT_Square
public:
    int get(void){return(x);};
    Square *newSquare(int i){Square *p;
           ZZ_OBJECT_ALLOC(Square,p); x=i; return(p);};
};

class Rectangle : public Shape{
    int x,y;
    ZZ_EXT_Rectangle
public:
    int get(void){return(x);};
    Rectangle *newRectangle(int i){Rectangle *p;
           ZZ_OBJECT_ALLOC(Rectangle,p); x=y=i; return(p);};
};

int main(void)
{
    char *v[1],*t[1];;
    Square *sp,ss;
    Rectangle *rp,rr;
    Shape *op;
    int i,k;
    void testData(char *,Shape *);

    util.mode(0,0,0,0);   // invoke memory blasting
    util.blkAlloc(MEMORY_LIMIT,PAGE_BITS); // select size of memory blocks
    numObj=(TOTAL_MEMORY/44)*3; // 16+16+12=44B for each 3 objects
    
    op=(Shape *)NULL;
    for(i=k=0;i<numObj;i++,k++){ // generate lot of mixed data
        if(k==0){ // generate 1 square for every 3 objects
            sp=ss.newSquare(i);
            op=all.add(op,(Shape *)sp);
            op=(Shape *)sp; // maintain the order
        }
        else {   // generate 2 rectangles for every 3 objects
            rp=rr.newRectangle(i);
            op=all.add(op,(Shape *)rp);
            op=(Shape *)rp; // maintain the order
        }
        if(k==2)k= -1; // let k run between 0 and 2 only
    }
    testData("before save",op);

    v[0]=(char *)op;
    printf("save ...\n");
    util.save("myfile",1,v,t);
    printf("clear ...\n");
    util.clear(1,v,t);
    v[0]=NULL;
    printf("open ...\n");
    util.open("myfile",1,v,t);
    op=(Shape *)(v[0]);
    testData("after open",op);
    return(0);
}
//---------------------------------------------------------------------
void testData(char *label,Shape *op) // test all data
{
    Shape *pp;
    int i,k,x;

    printf("%s:\n",label);
    i=k=0;
    all_iterator it(op);
    for(pp= ++it; pp; pp= ++it){
        x=pp->get();
        if(x!=i){
            printf("disagreement: %d in position %d\n",x,i);
            return;
        }
        i++;
        if(k==2)k= -1;
        k++;
    }
    printf("    all data correct last=%d\n",i-1);
}
#include "zzfunc.c"
