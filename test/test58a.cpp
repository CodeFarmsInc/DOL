#include "zzincl.h"
#include "test58a.h"

// only relations which involve A
ZZ_HYPER_NAME(aName,A);
ZZ_HYPER_UTILITIES(util);

// This constructor not only sets 'a', it also uses i to pick up the name
A::A(int i){
    static const char* n[]={"Jack","Jill","Peter","John","Charlie","Joan","Clara"};

    a=i;
    char* nm=util.strAlloc(n[i]);
    aName.add(this,nm);
}
    
void A::prt(){printf("    A=%d %s\n",a,aName.fwd(this));}
