// Testing multiple inheritance and ASCII saving, plus
// using ZZ_GENERAL_EXT, and saving a block of bytes. 
// Note that util.open() restores also GENERAL_LINK.
#include <stdio.h>
#define ZZascii
#define ZZmain
#define ZZnoDestr
#include "zzincl.h"

class NamedObject {
  ZZ_EXT_NamedObject
public:
  char *name;
};
ZZ_FORMAT(NamedObject, "");

class Flags {
  ZZ_EXT_Flags
public:
  unsigned int flag_bits;  // Store the flags in here.
};
ZZ_FORMAT(Flags, "%d, flag_bits");

class FlaggedObject {
  ZZ_EXT_FlaggedObject
public:
  Flags flags;
  void prtflg(void){printf("flg=%d\n",flags.flag_bits);}
};
ZZ_FORMAT(FlaggedObject, "");

class Prototype : public NamedObject, public FlaggedObject {
  ZZ_EXT_Prototype
public:
  int instance_count; // how many cells have been instantiated
  unsigned char t[2];
  void Save(void);
  void prt(void);
};
ZZ_FORMAT(Prototype, "%d %c %c, instance_count, t[0], t[1]");

ZZ_HYPER_GENERAL_LINK(xCor, Prototype);
ZZ_HYPER_GENERAL_LINK(yCor, Prototype);
ZZ_HYPER_UTILITIES(util);

void Prototype::Save(void){
    ZZ_KEY_SAVE(Prototype, "myfile", this);
    ZZ_OBJECT_SAVE(Prototype, "myfile", this, 1);
    ZZ_OBJECT_SAVE(char, "myfile", (char *)xCor.fwd(this), (int)sizeof(int));
    ZZ_OBJECT_SAVE(char, "myfile", (char *)yCor.fwd(this), (int)sizeof(int));
}
void Prototype::prt(void){printf("%d %d\n",t[0],t[1]);
    ((FlaggedObject*)this)->prtflg();
    printf("%d %d\n",*((int*)(xCor.fwd(this))),*((int*)(yCor.fwd(this))));
}

int main(void) {
    Prototype *p;
    char *v[1],*t[1];
    static int i[2]={33,1447};

    p=new Prototype;
    ((FlaggedObject*)p)->flags.flag_bits=83;
    p->t[0]=33; p->t[1]=37;
    xCor.add(p,(char *)(&(i[0])));
    yCor.add(p,(char *)(&(i[1])));
    p->Save();
    util.close("myfile");
    util.open("myfile",1,v,t);
    p=(Prototype *)v[0];
    p->prt();
    return(0);
}
#include "zzfunc.c"
