#define ZZascii
#include <stdio.h>
#ifdef UNIX
#include <stream.h>
#else
#include <iostream.h>
#endif
#include "zzincl.h"
#include "incl34.f"
#include "zzfunc.c"
// debugging function to display contents of objects
//  and internal pointers
void prtobj(char *label,void *p,int s){
    char **pp,**sp,*t;

    printf("%s\n",label);
    t=(char *)p;
    sp=(char **)(t+s);
    for(pp=(char **)p; pp!=sp; pp++)printf("  %d %d\n",pp,*pp);
}
