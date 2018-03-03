// Exactly the same as test27a.c, but using stdio.h
#include <stdio.h>
#include "zzincl_a.h"
#include "test27a.h"

A1::A1(void) {
  ZZ_INIT(A1);
  slot1 = 11;
}

void A1::Save(const char* file) {
  ZZ_STORE(A1,file);
  GetLink()->Save(file);
}

void A1::SetLink(A2* a) {
  A1_A2_links.del(this);
  A1_A2_links.add(this, a);
}

A2* A1::GetLink(void) {
  return A1_A2_links.fwd(this);
}

void A1::Dump(void) {
  printf("*** A1 Dump ***\n");
  printf("slot1 = %d\n",slot1);
  GetLink()->Dump();
}

A2::A2(void) {
  ZZ_INIT(A2);
  slot2 = 12;
}  

void A2::Save(const char* file) {
  ZZ_STORE(A2,file);
}

void A2::Dump(void) {
  printf("*** A2 Dump ***\n");
  printf("slot2 = %d\n",slot2);
}
