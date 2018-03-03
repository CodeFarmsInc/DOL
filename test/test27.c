// At the first glance, it may appear that the use of zzincl.h file
// causes a single-point dependency in large programs, where many programmers
// develop classes independently. This example shows that this is not true;
// each class can be developed and tested independently.
//
// In this example, programmer A is developing classes A1 and A2, stored
// in test27a.h and test27a.c. Programmer A compiles (test27a.o) and even
// tests the classes (including saving on disk, see test27aa.c) independently
// from other programmers.
//
// Programmer B does exactly the same for classes B1 and B2. Each of the two
// programmers uses his/her own zzincl.h and zzfunc.c.
//
// When pulling the whole system together, all four classes can be used together
// linking to files test27a.o and test27b.o with test27.c. No recompilation
//  is necessary.
//
// In order to run this test under UNIX, replace ORGC by the full path to
// the orgC directory:
//     cp ORGC/lib/env3s.h ORGC/lib/environ.h
//     cp test27.h tmp
//     cat test27a.h>>tmp
//     ORGC/zzprep tmp zzincl_a.h zzmaster zzfunc_a.c
//     CC -c test27a.c
//     CC  test27aa.c test27a.o ORGC/lib/zzclib.a
//     a.out>res27a
//     cp test27.h tmp
//     cat test27b.h>>tmp
//     ORGC/zzprep tmp zzincl_b.h zzmaster zzfunc_b.c
//     CC -c test27b.c
//     CC  test27bb.c test27b.o ORGC/lib/zzclib.a
//     a.out>res27b
//     cp test27a.h tmp
//     cat test27b.h>> tmp
//     cat test27.h>> tmp
//     ORGC/zzprep tmp zzincl.h
//     CC  test27.c test27a.o test27b.o ORGC/lib/zzclib.a
//     a.out>res27
//     diff res27 out27
//
// How does it work?
// file zzincl.h contains two types of information: (1) Expansion and type 
// conversion for classes that are being processed by each programmer. There
// is no mutual interaction. (2) Type tables, inheritance graph, and internal
// pointer lists. These are global; for a different environment the tables
// are changing, but not theobject files.

#include <stdio.h>
#define ZZmain
#include "zzincl.h"
#include "test27a.h"
#include "test27b.h"
#include "test27.h"

int main()
{
  A1* a1=new A1;
  A2* a2=new A2;
  B1* b1=new B1;
  B2* b2=new B2;
  a1->SetLink(a2);
  b1->SetLink(b2);
  char *v[2],*t[2];
  v[0]=(char *)a1; t[0]=(char*)"A1";
  v[1]=(char *)b1; t[1]=(char*)"B1";
  util.save("file",2,v,t);
  a1=(A1 *)NULL; b1=(B1 *)NULL;
  util.open("file",2,v,t);
  a1=(A1 *)v[0];
  b1=(B1 *)v[1];
  a1->Dump();
  b1->Dump();
  return(0);
}
#include "zzfunc.c"
