#include "zzincl_b.h"
#include "test27b.h"

B1::B1(void) {
  ZZ_INIT(B1);
  slot1 = 21;
}

void B1::Save(const char* file) {
  ZZ_STORE(B1,file);
  GetLink()->Save(file);
}

void B1::SetLink(B2* a) {
  B1_B2_links.del(this);
  B1_B2_links.add(this, a);
}

B2* B1::GetLink(void) {
  return B1_B2_links.fwd(this);
}

void B1::Dump(void) {
  cout << "*** B1 Dump ***\n";
  cout << "slot1 = ";
  cout << slot1 << "\n";
  GetLink()->Dump();
}

B2::B2(void) {
  ZZ_INIT(B2);
  slot2 = 22;
 }  

void B2::Save(const char* file) {
  ZZ_STORE(B2,file);
}

void B2::Dump(void) {
  cout << "*** B2 Dump ***\n";
  cout << "slot2 = ";
  cout << slot2 << "\n";
}
