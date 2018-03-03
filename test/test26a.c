// Test of saving a combination of individual objects with "deep"
// save. This is one of the key methods applicable to general C++
// programs.
// Also test SINGLE_AGGREGATE (new name for SINGLE_TRIANGLE)

#define ZZascii
#include <stdio.h>
#define ZZmain
#include "zzincl.h"

ZZ_HYPER_UTILITIES(util);
class Block {
    ZZ_EXT_Block  
public:
    void saveGuts(void){util.deep("afile",(char *)this,(char*)"Block");};
};
ZZ_FORMAT(Block,"");

class Link: public Block {
    ZZ_EXT_Link   
public:
    void save(void){ZZ_STORE(Link,"afile");};
};
ZZ_FORMAT(Link,"");

class Term {
    ZZ_EXT_Term  
public:
    int num;
};
ZZ_FORMAT(Term,"%d,num");

class Pin {
    ZZ_EXT_Pin  
public:
    int num;
};
ZZ_FORMAT(Pin,"%d,num");

ZZ_HYPER_SINGLE_RING(ring,Link);
ZZ_HYPER_SINGLE_LINK(toBlock,Link,Block);
ZZ_HYPER_NAME(name,Block);
ZZ_HYPER_SINGLE_AGGREGATE(terms,Block,Term);
ZZ_HYPER_SINGLE_AGGREGATE(pins,Term,Pin);

#define SZ 4
static const char* names[SZ]={"ABCD1","ABCD2","ABCD3","ABCD4"};

// ------------------------------------------------------
int main(void)
{
    Link *generate(char *),*lk,*lp;
    Block *bp;
    int i;
    char *v[1],*t[1];
    void prtAll(const char *,Link *);

    lk=(Link *)NULL;
    for(i=0;i<SZ;i++){
        lp=generate((char*)names[i]);
        lk=ring.add(lk,lp);
    }
    prtAll("before save():",lk);

    // save it using the mixture of the two styles
    ring_iterator ri(lk);
    for(lp= ++ri; lp; lp= ++ri){
        lp->save();  // saves the Link itself
        bp=toBlock.fwd(lp);
        bp->saveGuts(); // saves Block and everything under
    }
    util.close("afile");
    // everything is saved, the first Link will be retrieved as the key entry

    // clear the old data
    v[0]=(char *)lk; t[0]=(char*)"Link";
    // util.clear(1,v,t);

    // reopen the organization will create second copy of the whole organization
    // this is equivalent to what Gorlen calls "deep copy"
    util.open("afile",1,v,t);
    lk=(Link *)v[0];
    prtAll("after open():",lk);
    return(0);
}
// ------------------------------------------------------
// generate one block with terminals and pins
Link *generate(char *blkName)
{
    Link *lp;
    Block *bp;
    Term *tp;
    Pin *pp;
    int i,k;
    char *nm;
    static int m=1;

    lp=new Link;
    bp=new Block;
    nm=util.strAlloc(blkName);
    toBlock.add(lp,bp);
    name.add(bp,nm);
    for(i=0;i<SZ;i++,m++){
        tp=new Term;
        tp->num=m*10;
        terms.add(bp,tp);
        for(k=0;k<SZ;k++){
            pp=new Pin;
            pp->num=tp->num+k;
            pins.add(tp,pp);
        }
    }
    return(lp);
}
// ------------------------------------------------------
// print the whole organization
void prtAll(const char *label,Link *lk)
{
    Link *lp;
    Block *bp;
    Term *tp;
    Pin *pp;
    char *nm;

    printf("%s\n",label);
    ring_iterator ri(lk);
    for(lp= ++ri; lp; lp= ++ri){
        bp=toBlock.fwd(lp);
        nm=name.fwd(bp);
        printf("Block=%s\n",nm);
        terms_iterator ti(bp);
        for(tp= ++ti; tp; tp= ++ti){
            printf("  Term=%d, Pins:",tp->num);
            pins_iterator pi(tp);
            for(pp= ++pi; pp; pp= ++pi)printf(" %d",pp->num);
            printf("\n");
        }
    }
}
#include "zzfunc.c"
