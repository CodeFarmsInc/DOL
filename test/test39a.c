// Test of access to the internal type tables
// Use #define FULL_TEST in order to test all features
// including the detection of virtual function pointers,
// which is disabled for the standard regression test, because the
// pointer values are different for each run.
//
// This is a simple test that runs with C++ compilers that do not have
// multiple inheritance, such as AT&T 2.0 on SUN.
// For a more complex test, see test39b.c

#include <stdio.h>
#define ZZmain
#include "zzincl.h"

class Coord {
    ZZ_EXT_Coord
    int x[3];
public:
    void virtual ini(void){};
};

class Shape {
    ZZ_EXT_Shape
public:
    void virtual prt(){};
};
class Tool : public Shape {
    ZZ_EXT_Tool
    int t;
    Coord c;
public:
    void virtual prt(){};
};
class Image: public Tool {
    ZZ_EXT_Image
    int id;
public:
    void prt(){};
};
ZZ_HYPER_SINGLE_TREE(tree,Image);
ZZ_HYPER_SINGLE_TRIANGLE(col,Shape,Tool);
ZZ_HYPER_TYPE(type);

int main(void){
    Shape *sp;
    Tool *tt;
    Image *ip;
    zzTypeInfo inf;
    int i,sz,t1,t2,n;
    ZZint tp;
    void *vp,**vv;
    char *p,*m,c;
#ifdef FULL_TEST
    void*v1,*v2;
#endif

    // Test Part 1: Basic type and casting
    ip=new Image;
    tp=ZZgetType(Shape); // macro to get type index
    sp=(Shape *)ip;
    vp=(void *)sp;

    printf("Shape type=%d\n",(int)tp);
    type.trueType(&vp,&tp); // updates vp and tp to the true image (Image type)
    type.info(tp,&inf);  // returns info for type tp
    if(vp==(void *)sp)
          printf("new correct pointer, %s type=%d\n",inf.name,tp);

    // Test Part 2: Iterating through sub-classes and members
    type_iterator it; // declare iterator, will be used more times
    n=type.num(); // get total number of registered types
    for(t1=0;t1<n;t1++){ // go through all registered types
        type.info(t1,&inf); // get info on this type, we need the name
        printf("%s= ",inf.name);
        it.start(t1); // start iterator of sub-types
        for(t2= ++it; t2>=0; t2= ++it){ // type=0 is a valid value
            type.info(t2,&inf);
            printf("%s(%d):%s ",it.name(),inf.virt,inf.name);
        }
        printf("\n");
    }
    
    ip=new Image;
    tp=ZZgetType(Image);

    // Test Part 3: Traverse pointers on a given object
    ip=new Image;
    tp=ZZgetType(Image);
    printf("\nImage:\n");
    type_pointers ptrs(ip,tp); // traverse HYPER pointers on sp
    for(vv= ++ptrs,i=0; vv; vv= ++ptrs, i++){
        printf("pointer no.=%d to type=%d\n",i,ptrs.nxtType());
    }
    
    tt=new Tool;
    tp=ZZgetType(Tool);
    printf("\nTool:\n");
    ptrs.start(tt,tp); // traverse HYPER pointers on sp
    for(vv= ++ptrs,i=0; vv; vv= ++ptrs, i++){
        printf("pointer no.=%d to type=%d\n",i,ptrs.nxtType());
    }
    
    // Test Part 4: print hidden virt.fun. pointers within an object
    tp=ZZgetType(Image);
    type.info(tp,&inf);
    sz=inf.size;  // sizeof(Image) could be used instead

    // print the two mask
    printf("\nmask: ");
    for(i=0, m=inf.mask2; i<sz; i++, m++){
        if(*m=='\0')c='0'; else if(*m==1)c='1'; else c=*m;
        printf("%c",c);
    }

#ifdef FULL_TEST
    // Test Part 5: print the range of the virtual pointers
    type.virtRange(&v1,&v2);
    printf("\nvirtRange= %lu, %lu\n",v1,v2);
#endif

    // virtual pointers on the given Image object
#ifdef FULL_TEST
    printf("\nobject start=%d size=%d bytes\n",inf.mask1,sz);
#else
    printf("\nobject size=%d bytes\n",sz);
#endif
    for(i=0, p=inf.mask1, m=inf.mask2; i<sz; i++,p++,m++){
            vv=(void **)p;
#ifdef FULL_TEST
        if(*m=='F')printf("virt.fun.ptr at=%d value=%d offset=%d\n",vv,*vv,i);
        if(*m=='C')printf("v.class  ptr at=%d value=%d offset=%d\n",vv,*vv,i);
#else
        if(*m=='F')printf("virt.fun.ptr offset=%d\n",i);
        if(*m=='C')printf("v.class  ptr offset=%d\n",i);
#endif
    }
    return(0);
}
#include "zzfunc.c"
