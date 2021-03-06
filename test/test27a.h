#ifdef TURBOC
#include <iostream.h>
#define STREAM_DEFINED
#endif

#ifdef UNIX
#include <iostream.h>
#define STREAM_DEFINED
#endif


#ifdef MICROSOFT
#define STREAM_DEFINED
#endif

#ifndef STREAM_DEFINED
#include <stream.h>
#endif

class A2;

class A1 {
  ZZ_EXT_A1
  int slot1;
public:
  A1(void);
  void Save(const char* file);
  void SetLink(A2*);
  A2* GetLink(void);
  void Dump(void);
};

class A2 {
  ZZ_EXT_A2
  int slot2;
public:
  A2(void);
  void Save(const char* file);
  void Dump();
};

ZZ_HYPER_SINGLE_LINK(A1_A2_links, A1, A2);
