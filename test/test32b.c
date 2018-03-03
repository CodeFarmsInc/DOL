// Combined testing of several features in C++:
// - saving a dynamic array of objects with pointers leading into the array
//   (dynamic ARRAY is used, but it is formed as 'fixed')
// - Saving in binary format intermittently on two files
// - On one file saving with ZZ_OBJECT_SAVE(), on the other with ZZ_SAVE()
// 
// For comparision, see a similar (but not exactly the same) C example
// in test32a.c.
// Both tests are set up so that they should have identical results.
//
// Jiri Soukup, Dec.9/91

#include <stdio.h>
#define ZZmain
#define ZZ_INHERIT
#include "zzincl.h"

#define BSIZE 80

class Header {
    ZZ_EXT_Header
public:
    void addTown(const char *sn, const char *tn);
    void printAll(void);
    void save(void);
};
class State {
    ZZ_EXT_State
};
class Town {
    ZZ_EXT_Town
public:
    void save(void);
};
ZZ_HYPER_NAME(sName,State);
ZZ_HYPER_NAME(tName,Town);
ZZ_HYPER_SINGLE_TRIANGLE(where,State,Town);
ZZ_HYPER_ARRAY(states,Header,State);
ZZ_HYPER_UTILITIES(util);

void Header::save(void){
    ZZint i,hwm,incr; State *sp; char *np;
    ZZ_OBJECT_SAVE(Header,"file1",this,1);
    (void)states.size(this,&hwm,&incr);
    for(i=0;i<=hwm;i++){
        sp=states.ind(this,i);
        np=sName.fwd(sp);
        if(np)ZZ_OBJECT_SAVE(char,"file1",np,0);
    }
}

void Town::save(void){char *np;
    np=tName.fwd(this);
    if(np)ZZ_OBJECT_SAVE(char,"file1",np,0);
    ZZ_OBJECT_SAVE(Town,"file1",this,1);
}

void Header::printAll(void){
    ZZint i,hwm,incr;
    Town *tp;
    State *sp,*ss;
    char *n1,*n2;

    (void)states.size(this,&hwm,&incr);
    for(i=0;i<=hwm;i++){
        sp=states.ind(this,i);
        where_iterator it(sp);
        for(tp= ++it; tp; tp= ++it){
            ss=where.par(tp);
            n1=sName.fwd(ss);
            n2=tName.fwd(tp);
            printf("%s\t%s\n",n1,n2);
        }
    }
    printf("\n");
}

void Header::addTown(const char *sn,const char *tn){
// sn,tn are state name and town name
    ZZint i,hwm,incr;
    char *np;
    Town *tp;
    State *sp;

    (void)states.size(this,&hwm,&incr);
    for(i=0;i<=hwm;i++){
        sp=states.ind(this,i);
        np=sName.fwd(sp);
        if(!strcmp(np,sn))break;
    }
    if(i>hwm){
        np=util.strAlloc(sn);
        sp=states.ind(this,i);
        sName.add(sp,np);
    }
    np=util.strAlloc(tn);
    tp=new Town;
    tName.add(tp,np);
    where.add(sp,tp);
}
 /* -------------------------------------------------------- */

#define A_SIZE 5

int main(void)
{
    State *sp;
    Header *hp;
    ZZint i,hwm,incr;
    Town *tp;
    char *v[1],*t[1],buff[BSIZE];

    hp=new Header;
    sp=states.form(hp,A_SIZE,-1); /* declare a fixed array */
    
    hp->addTown("Florida","Jacksonville");
    hp->addTown("NewYork","Rochester");
    hp->addTown("Florida","Orlando");
    hp->addTown("Florida","Miami");
    hp->addTown("NewYork","Albany");

    hp->save();
    v[0]=(char *)hp; t[0]=(char*)"Header";
    util.save("file2",1,v,t); /* testing simultaneous save to both files */
    (void)states.size(hp,&hwm,&incr);
    for(i=0;i<=hwm;i++){
        sp=states.ind(hp,i);
        where_iterator it(sp);
        for(tp= ++it; tp; tp= ++it){
            tp->save();
        }
    }
    util.close("file1");

    util.open("file1",1,v,t);
    hp=(Header *)(v[0]);
    hp->printAll();

    util.open("file2",1,v,t);
    hp=(Header *)(v[0]);
    hp->printAll();
    return(0);
}
/* -------------------------------------------------------- */
#include "zzfunc.c"
