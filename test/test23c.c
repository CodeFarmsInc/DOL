// Testing virtual functions and saving on disk for arrays,
// in both ASCII and binary */.
// This is the first stage; the test continues through test23d.c
// and test23e.c
#include <stdio.h>
#define ZZmain
#include "zzincl.h"
#include "test23c.h"

Header::~Header(){ sqrs.free(this); recs.free(this); ZZ_CHECK(Header);}

int main(void)
{
    char c[20],*v[1],*t[1];;
    int ri,si,x,y;
    Square *sp;
    Rectangle *rp;
    Header *hp;
    void prtData(Header *);

    v[0]=NULL;
    hp=new Header;
    sp=sqrs.form(hp,20,0); // fixed array of 20
    rp=recs.form(hp,2,-3); // start with 2, multiply by 3
    ri=si=0;               // index to deposit next entry

    while(gets(buff)){
        sscanf(buff,"%c",&c);
        switch(c[0]) {
            case 'S':
                sp=sqrs.ind(hp,si); si++;
                sscanf(buff,"%c %d",&c,&x);
                sp->set(x);
                break;
            case 'R':
                rp=recs.ind(hp,ri); ri++;
                sscanf(buff,"%c %d %d",&c,&x,&y);
                rp->set(x,y);
                if(!v[0]){v[0]=(char *)rp; t[0]=(char*)"Rectangle";}
                break;
            default: printf("wrong input code\n");
        }
    }

    prtData(hp); // print all data as loaded

    // save all data in ASCII by traversing all objects
    // ZZascii is defined in test23.h
    hp->save((char*)"afile"); // there is only one object to save
    util.close((char*)"afile");
    delete hp;
    return(0);
}
#include "zzfunc.c"
