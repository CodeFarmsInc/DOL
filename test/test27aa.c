#include <stdio.h>
#define ZZmain
#include "zzincl_a.h"
#include "test27a.h"
#include "test27.h"

int main(void)
{
  A1 testA1,*a;
  A2 testA2;
  testA1.SetLink(&testA2);
  char *v[1],*t[1];
  testA1.Save("afile");
  util.close("afile");
  util.open("afile",1,v,t);
  a=(A1 *)v[0];
  a->Dump();
  return(0);
}
#include "zzfunc_a.c"
