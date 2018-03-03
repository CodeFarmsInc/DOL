#include <stdio.h>
#define ZZmain
#include "zzincl_b.h"
#include "test27b.h"
#include "test27.h"

int main(void)
{
  B1 testB1,*a;
  B2 testB2;
  testB1.SetLink(&testB2);
  char *v[1],*t[1];
  testB1.Save("bfile");
  util.close("bfile");
  util.open("bfile",1,v,t);
  a=(B1 *)v[0];
  a->Dump();
  return(0);
}
#include "zzfunc_b.c"
