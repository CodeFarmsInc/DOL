
#include <stdio.h>
#define ZZmain
#include "zzincl.h"

class Head {
    ZZ_EXT_Head
};

class Employee {
    int id;
    ZZ_EXT_Employee
public:
    Employee(int idn,char *name);
    Employee(){}; // required if other constructors present
    void prt();
};

ZZ_HYPER_SINGLE_COLLECT(list1,Head,Employee);
ZZ_HYPER_SINGLE_COLLECT(list2,Head,Employee);
ZZ_HYPER_NAME(eName,Employee);
ZZ_HYPER_UTILITIES(util);

Employee::Employee(int idn, char *name){char *p;
    id=idn; p=util.strAlloc(name); eName.add(this,p);}
void Employee::prt(void){printf("%d %s\n",id,eName.fwd(this));}

int main(){
    int i; Head *h; Employee *e; char *v[1],*t[1];
    static char * names[4]={"Black","White","Green","Brown"};
   
    h=new Head;
    for(i=0;i<4;i++){
        e=new Employee(i,names[i]);
        list1.add(h,e);
        if(names[i][0]=='B')list2.add(h,e);
    }
    list1_iterator it1(h);
    ITERATE(it1,e){
        e->prt();
    }
    printf("\n");
    list2_iterator it2(h);
    ITERATE(it2,e){
        e->prt();
    }

    v[0]=(char *)h; t[0]="Head";
    util.save("myfile",1,v,t);
    return 0;
}
#include "zzfunc.c"
