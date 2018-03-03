#include "zzincl.h"
#ifdef FLOATLINK
#include <math.h>
#endif
Rectangle::Rectangle(ZZZiClass *x):Shape(x){ZZSS_Rectangle(this)}
 void* Rectangle::operator new(size_t size){void *ZZmassAlloc(size_t,ZZint);
  ZZnumObjects++;
  printf("NEW rect\n");
  if(ZZmemSwitch){Rectangle *p;
	  printf("SW2\n"); // ???
    ZZ_OBJECT_ALLOC(Rectangle,p);return((void*)p);}
  else {
	  printf("SW0\n"); // ???
	  return(ZZmassAlloc((size_t)size,(ZZint)1));}}
 void Rectangle::operator delete(void *ptr){void ZZmassFree(void *);
  if(ZZnumObjects>0)ZZnumObjects--;
  if(ZZmemSwitch)ZZ_OBJECT_FREE(Rectangle,(Rectangle *)ptr)
  else ZZmassFree(ptr);}
Square::Square(ZZZiClass *x):Shape(x){ZZSS_Square(this)}
 void* Square::operator new(size_t size){void *ZZmassAlloc(size_t,ZZint);
  ZZnumObjects++;
  printf("NEW squa\n");
  if(ZZmemSwitch){Square *p;
	  printf("SW2\n"); // ???
    ZZ_OBJECT_ALLOC(Square,p);return((void*)p);}
  else {
	  printf("SW0\n"); // ???
	  return(ZZmassAlloc((size_t)size,(ZZint)1));}}
 void Square::operator delete(void *ptr){void ZZmassFree(void *);
  if(ZZnumObjects>0)ZZnumObjects--;
  if(ZZmemSwitch)ZZ_OBJECT_FREE(Square,(Square *)ptr)
  else ZZmassFree(ptr);}
Shape::Shape(ZZZiClass *){ZZSS_Shape(this)}
 void* Shape::operator new(size_t size){void *ZZmassAlloc(size_t,ZZint);
  ZZnumObjects++;
  if(ZZmemSwitch){Shape *p;
    ZZ_OBJECT_ALLOC(Shape,p);return((void*)p);}
  else {return(ZZmassAlloc((size_t)size,(ZZint)1));}}
 void Shape::operator delete(void *ptr){void ZZmassFree(void *);
  if(ZZnumObjects>0)ZZnumObjects--;
  if(ZZmemSwitch)ZZ_OBJECT_FREE(Shape,(Shape *)ptr)
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
ZZ1all* ZZVall ZZHall :: add(ZZ1all *s,ZZ1all *t){ZZ_ADD_SINGLE_RING(all,s,t); return(s);}
ZZ1all* ZZVall ZZHall :: del(ZZ1all *s,ZZ1all *t){ZZ_DELETE_SINGLE_RING(all,s,t); return(s);}
ZZ1all* ZZVall ZZHall :: merge(ZZ1all *s,ZZ1all *t){
                               ZZ_MERGE_SINGLE_RING(all,s,t,NULL); return(s);}
ZZ1all* ZZVall ZZHall :: sort(ZZTsortFun cmpF,ZZ1all *p){
                                 ZZ_SORT_SINGLE_RING(all,cmpF,p); return(p);}
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
    ZZstrList[0].vObj[0]=(char *)(new Rectangle((ZZZiClass *)NULL));
    ZZstrList[0].vObj[1]=(char *)(new Rectangle((ZZZiClass *)NULL));
  }
  if(!(ZZstrList[1].vObj[0])){
    ZZstrList[1].vObj[0]=(char *)(new Square((ZZZiClass *)NULL));
    ZZstrList[1].vObj[1]=(char *)(new Square((ZZZiClass *)NULL));
  }
  if(!(ZZstrList[2].vObj[0])){
    ZZstrList[2].vObj[0]=(char *)(new Shape((ZZZiClass *)NULL));
    ZZstrList[2].vObj[1]=(char *)(new Shape((ZZZiClass *)NULL));
  }
for(i=0;i<2;i++){
  ((Shape *)(ZZstrList[2].vObj[0]))->ZZinitSet();
  ((Square *)(ZZstrList[1].vObj[0]))->ZZinitSet();
  ((Rectangle *)(ZZstrList[0].vObj[0]))->ZZinitSet();
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
ZZ_LOCAL int ZZZIRectangle(void){return(0);}
ZZ_LOCAL int ZZZJRectangle(void){return(-1);}
ZZ_LOCAL int ZZZISquare(void){return(1);}
ZZ_LOCAL int ZZZJSquare(void){return(-1);}
ZZ_LOCAL int ZZZIShape(void){return(2);}
ZZ_LOCAL int ZZZJShape(void){return(-1);}
/* ----------------------------------------- */
ZZ_LOCAL void ZZvSet(ZZint tp){
  int i; i=ZZmemSwitch; ZZmemSwitch=0;
  switch(tp){
    case 0: (void)new Rectangle((ZZZiClass *)NULL); break;
    case 1: (void)new Square((ZZZiClass *)NULL); break;
    case 2: (void)new Shape((ZZZiClass *)NULL); break;
    default: ZZmsgD(27,tp); ZZerror=ZZerror|040;
  }
  ZZmemSwitch=i;
printf("zzfunc.c ZZmemSwitch=%u\n",ZZmemSwitch); // ???
}
/* ----------------------------------------- */
ZZ_LOCAL void *ZZtopType(void *ptr,ZZint tp,ZZint *newTp){
  switch(tp){
    case 0: ptr=(void *)(((Rectangle *)ptr)->zzThisIs((ZZint*)newTp)); break;
    case 1: ptr=(void *)(((Square *)ptr)->zzThisIs((ZZint*)newTp)); break;
    case 2: ptr=(void *)(((Shape *)ptr)->zzThisIs((ZZint*)newTp)); break;
    default: ZZmsgD(27,tp); ZZerror=ZZerror|040;
  }
  return(ptr);
}
