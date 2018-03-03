#include "zzincl_a.h"
#ifdef FLOATLINK
#include <math.h>
#endif
A2::A2(ZZZiClass *){ZZSS_A2(this)}
 void* A2::operator new(size_t size){void *ZZmassAlloc(size_t,ZZint);
  ZZnumObjects++;
  if(ZZmemSwitch){A2 *p;
    ZZ_OBJECT_ALLOC(A2,p);return((void*)p);}
  else {return(ZZmassAlloc((size_t)size,(ZZint)1));}}
 void A2::operator delete(void *ptr){void ZZmassFree(void *);
  if(ZZnumObjects>0)ZZnumObjects--;
  if(ZZmemSwitch)ZZ_OBJECT_FREE(A2,(A2 *)ptr)
  else ZZmassFree(ptr);}
A1::A1(ZZZiClass *){ZZSS_A1(this)}
 void* A1::operator new(size_t size){void *ZZmassAlloc(size_t,ZZint);
  ZZnumObjects++;
  if(ZZmemSwitch){A1 *p;
    ZZ_OBJECT_ALLOC(A1,p);return((void*)p);}
  else {return(ZZmassAlloc((size_t)size,(ZZint)1));}}
 void A1::operator delete(void *ptr){void ZZmassFree(void *);
  if(ZZnumObjects>0)ZZnumObjects--;
  if(ZZmemSwitch)ZZ_OBJECT_FREE(A1,(A1 *)ptr)
  else ZZmassFree(ptr);}
/* ----------------------------------------- */
void ZZHutil :: save(const char *file,ZZint n,char **v, char **t){
                                            ZZ_SAVE(file,n,v,t);}
void ZZHutil :: deep(const char *file,void *v, char *t){ZZ_DEEP(file,v,t);}
void ZZHutil :: open(const char *file,ZZint n,char **v, char **t){
                                            ZZ_OPEN(file,n,v,t);}
void ZZHutil :: clear(ZZint n,char **v, char **t){ZZ_CLEAR(n,v,t);}
char* ZZHutil :: getID(char *p){char *n;ZZ_GET_SELF_ID(p,n);return(n);}
void ZZHutil :: blkFree(ZZint m){ZZ_BLOCK_FREE(m);}
char* ZZHutil :: strAlloc(ZZint sz){
    void *ZZFUN_galloc();
    char* p=(char*)ZZgalloc(sz);
    if(!p) {ZZmsgS(7,"ZZ_STRING_ALLOC()"); ZZerrFLG=ZZerrFLG|01;}
    return p;
}
/* ----------------------------------------- */
/* ----------------------------------------- */

ZZ_LOCAL void ZZ_GENERAL_EXT(void){
  char *p; int i;
  void ZZsetMask(void);
  static int repeat={0};
#ifdef FLOATLINK
double x; x=sin(0.0); x=x;
#endif
#ifdef ZORTECH
{void dumbZortechLinker(); dumbZortechLinker();}
#endif
  ZZorgcVersion=ZZorgcVersion;
  p=NULL;
  p=p;
  ZZsList=ZZstrList;
  ZZpList= &(ZZptrList[0]);
  ZZiList= &(ZZinhList[0]);
  if(repeat)return;else repeat=1;
  if(!(ZZstrList[0].vObj[0])){
    ZZstrList[0].vObj[0]=(char *)(new A2((ZZZiClass *)NULL));
    ZZstrList[0].vObj[1]=(char *)(new A2((ZZZiClass *)NULL));
  }
  if(!(ZZstrList[1].vObj[0])){
    ZZstrList[1].vObj[0]=(char *)(new A1((ZZZiClass *)NULL));
    ZZstrList[1].vObj[1]=(char *)(new A1((ZZZiClass *)NULL));
  }
for(i=0;i<2;i++){
  ((A1 *)(ZZstrList[1].vObj[0]))->ZZinitSet();
  ((A2 *)(ZZstrList[0].vObj[0]))->ZZinitSet();
}
#ifndef ZZlocal
ZZsetMask();
#endif
#ifdef ZZcCalloc
ZZcallocFlg=1;
#else
ZZcallocFlg=0;
#endif
}
/* ----------------------------------------- */
/* ----------------------------------------- */
ZZ_LOCAL void ZZvSet(ZZint tp){
  int i; i=ZZmemSwitch; ZZmemSwitch=0;
  switch(tp){
    case 0: (void)new A2((ZZZiClass *)NULL); break;
    case 1: (void)new A1((ZZZiClass *)NULL); break;
    default: ZZmsgD(27,tp); ZZerror=ZZerror|040;
  }
  ZZmemSwitch=i;
}
/* ----------------------------------------- */
ZZ_LOCAL void *ZZtopType(void *ptr,ZZint tp,ZZint *newTp){
  switch(tp){
    case 0: ptr=(void *)(((A2 *)ptr)->zzThisIs((ZZint*)newTp)); break;
    case 1: ptr=(void *)(((A1 *)ptr)->zzThisIs((ZZint*)newTp)); break;
    default: ZZmsgD(27,tp); ZZerror=ZZerror|040;
  }
  return(ptr);
}
