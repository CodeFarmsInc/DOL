// --------------------------------------------------------------------
// This program tests adding and removing objects from an ordered array.
// --------------------------------------------------------------------
#include <stdio.h>
#define ZZmain
#include "zzincl.h"

class Header {
    ZZ_EXT_Header
};

class Entry {
   ZZ_EXT_Entry
public:
    int  value;
    static int cmp(const void *e1,const void *e2){
        return ((Entry*)e1)->value - ((Entry*)e2)->value;}
};

ZZ_HYPER_ARRAY(myArray,Header,Entry);

int main(){
    int side,i,i1,i2,num,incr,found; Entry e,*ep; Header *hp;

    printf("ORDER TEST:\n");
    hp=new Header;
    myArray.form(hp,200,-2);
    for(i1=0, i2=9, side=0; i2>=i1; side=1-side ){ // load varying values
        if(side==0){i=i1; i1++;}
        else       {i=i2; i2--;}
        e.value=i;
        myArray.addOrd(Entry::cmp,hp,&e);
    }
    myArray.size(hp,&num,&incr);
    for(i=0; i<=num; i++){  // print the result
        ep=myArray.ind(hp,i);
        if(ep)printf("%d ",ep->value);
    }
    printf("\n");

    // remove three items
    e.value=7; myArray.delOrd(Entry::cmp,hp,&e);
    e.value=8; myArray.delOrd(Entry::cmp,hp,&e);
    e.value=0; myArray.delOrd(Entry::cmp,hp,&e);
    e.value=3; myArray.delOrd(Entry::cmp,hp,&e);
    myArray.size(hp,&num,&incr);
    for(i=0; i<=num; i++){  // print the result
        ep=myArray.ind(hp,i);
        if(ep)printf("%d ",ep->value);
    }
    printf("\n");

    // add a few new entries
    e.value=7; myArray.addOrd(Entry::cmp,hp,&e);
    e.value=6; myArray.addOrd(Entry::cmp,hp,&e);
    e.value=11; myArray.addOrd(Entry::cmp,hp,&e);
    e.value=13; myArray.addOrd(Entry::cmp,hp,&e);
    e.value=10; myArray.addOrd(Entry::cmp,hp,&e);
    myArray.size(hp,&num,&incr);
    for(i=0; i<=num; i++){  // print the result
        ep=myArray.ind(hp,i);
        if(ep)printf("%d ",ep->value);
    }
    printf("\n");
    e.value=5; i=myArray.getOrd(Entry::cmp,hp,&e,&found);
    if(found)printf("found value=%d index=%d\n",e.value,i);
    return 0;
}    
#include "zzfunc.c"
