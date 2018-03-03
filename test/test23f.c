// Testing virtual functions and saving on disk with bitmap memory blasting 
// The first program parameter is the number of bits to form a page,
// for example 20 for 1MB pages. The program generates about 3.5MB of data.
//
// Note that with memory blasting v[0] can be a pointer to
// a base object without casting.
#include <stdio.h>
#include <string.h>
#define ZZmain
#include "zzincl.h"

// The following parameters correspond to 0.35MB data with 2**17=0.1MB pages
#define PAGE_BITS 17 // use 19 if you want to test the single page option
#define TOTAL_MEMORY 400000
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
    Square(){};
    Square(int i){x=i;};
};

class Rectangle : public Shape{
    int x,y;
    ZZ_EXT_Rectangle
public:
    int get(void){return(x);};
    Rectangle(){};
    Rectangle(int i){x=y=i;};
};

// debug print of the hidden virtual pointer
void debugVirt(void *p){
    char** s=(char**)p;
    printf("virt.pointer=%u\n",(unsigned)(*s));
}

int main(void)
{
    char *v[1],*t[1];;
    Square *sp;
    Rectangle *rp;
    Shape *op;
    int i,k,obj3Sz;
    void testData(char *,Shape *);

    util.mode(0,1,0,0);   // invoke memory blasting
    util.blkAlloc(TOTAL_MEMORY/2,PAGE_BITS); // select size of memory blocks
    // IMPORTANT: JUST FOR TESTING, WE USE UNREALISTICALLY SMALL ESTIMATE OF
    // MEMORY (ABOUT 1/2) WHICH WILL TRIGGER REALLOCATION OF THE INTERNAL ARRAYS

    obj3Sz=sizeof(Square)+2*sizeof(Rectangle);
    numObj=(TOTAL_MEMORY/obj3Sz)*3; 
    op=(Shape *)NULL;
    for(i=k=0;i<numObj;i++,k++){ // generate lot of mixed data
        if(k==0){ // generate 1 square for every 3 objects
            sp=new Square(i);
            op=all.add(op,(Shape *)sp);
            op=(Shape *)sp; // maintain the order
        }
        else {   // generate 2 rectangles for every 3 objects
            rp=new Rectangle(i);
            op=all.add(op,(Shape *)rp);
            op=(Shape *)rp; // maintain the order
        }
        if(k==2)k= -1; // let k run between 0 and 2 only
    }
    testData((char*)"before save",op);

    v[0]=(char *)op; t[0]=(char*)"Shape";
    printf("save ...\n");
    util.save((char*)"myfile",1,v,t);
    printf("clear ...\n");
    util.clear(1,v,t);

    v[0]=NULL;
    printf("open ...\n");
    util.open((char*)"myfile",1,v,t);
    op=(Shape *)(v[0]);
    testData((char*)"after open",op);

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
    ITERATE(it,pp){
    // for(pp= ++it; pp; pp= ++it){ // another possible syntax
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
