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

class B2;

class B1 {
  ZZ_EXT_B1
  int slot1;
public:
  B1(void);
  void Save(const char* file);
  void SetLink(B2*);
  B2* GetLink(void);
  void Dump(void);
};

class B2 {
  ZZ_EXT_B2
  int slot2;
public:
  B2(void);
  void Save(const char* file);
  void Dump();
};

ZZ_HYPER_SINGLE_LINK(B1_B2_links, B1, B2);
