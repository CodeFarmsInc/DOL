#include "pager.k"
#ifdef FLOATLINK
#include <math.h>
#endif
Page::Page(ZZZiClass *){ZZSS_Page(this)}
 void* Page::operator new(size_t size){void *ZZmassAlloc(size_t,ZZint);
  ZZnumObjects++;
  if(ZZmemSwitch){Page *p;
    ZZ_OBJECT_ALLOC(Page,p);return((void*)p);}
  else {return(ZZmassAlloc((size_t)size,(ZZint)1));}}
 void Page::operator delete(void *ptr){void ZZmassFree(void *);
  if(ZZnumObjects>0)ZZnumObjects--;
  if(ZZmemSwitch)ZZ_OBJECT_FREE(Page,(Page *)ptr)
  else ZZmassFree(ptr);}
zzHead::zzHead(ZZZiClass *){ZZSS_zzHead(this)}
 void* zzHead::operator new(size_t size){void *ZZmassAlloc(size_t,ZZint);
  ZZnumObjects++;
  if(ZZmemSwitch){zzHead *p;
    ZZ_OBJECT_ALLOC(zzHead,p);return((void*)p);}
  else {return(ZZmassAlloc((size_t)size,(ZZint)1));}}
 void zzHead::operator delete(void *ptr){void ZZmassFree(void *);
  if(ZZnumObjects>0)ZZnumObjects--;
  if(ZZmemSwitch)ZZ_OBJECT_FREE(zzHead,(zzHead *)ptr)
  else ZZmassFree(ptr);}
/* ----------------------------------------- */
void ZZHzz_util :: save(const char *file,ZZint n,char **v, char **t){
                                            ZZ_SAVE(file,n,v,t);}
void ZZHzz_util :: deep(const char *file,void *v, char *t){ZZ_DEEP(file,v,t);}
void ZZHzz_util :: open(const char *file,ZZint n,char **v, char **t){
                                            ZZ_OPEN(file,n,v,t);}
void ZZHzz_util :: clear(ZZint n,char **v, char **t){ZZ_CLEAR(n,v,t);}
char* ZZHzz_util :: getID(char *p){char *n;ZZ_GET_SELF_ID(p,n);return(n);}
void ZZHzz_util :: blkFree(ZZint m){ZZ_BLOCK_FREE(m);}
char* ZZHzz_util :: strAlloc(ZZint sz){
    void *ZZFUN_galloc();
    char* p=(char*)ZZgalloc(sz);
    if(!p) {ZZmsgS(7,"ZZ_STRING_ALLOC()"); ZZerrFLG=ZZerrFLG|01;}
    return p;
}
/* ----------------------------------------- */
ZZ1zz_heads* ZZVzz_heads ZZHzz_heads :: add(ZZ1zz_heads *s,ZZ1zz_heads *t){ZZ_ADD_DOUBLE_RING(zz_heads,s,t); return(s);}
ZZ1zz_heads* ZZVzz_heads ZZHzz_heads :: ins(ZZ1zz_heads *s,ZZ1zz_heads *t){
                                      ZZ_INSERT_DOUBLE_RING(zz_heads,s,t); return(s);}
ZZ1zz_heads* ZZVzz_heads ZZHzz_heads :: del(ZZ1zz_heads *s,ZZ1zz_heads *t){
                                      ZZ_DELETE_DOUBLE_RING(zz_heads,s,t); return(s);}
ZZ1zz_heads* ZZVzz_heads ZZHzz_heads :: merge(ZZ1zz_heads *s,ZZ1zz_heads *t){
                               ZZ_MERGE_DOUBLE_RING(zz_heads,s,t,NULL); return(s);}
ZZ1zz_heads* ZZVzz_heads ZZHzz_heads :: sort(ZZTsortFun cmpF,ZZ1zz_heads *p){
                                  ZZ_SORT_DOUBLE_RING(zz_heads,cmpF,p); return(p);}
/* ----------------------------------------- */
/* ----------------------------------------- */
ZZ2zz_pageHash* ZZVzz_pageHash ZZHzz_pageHash :: get(ZZ1zz_pageHash *h,ZZ2zz_pageHash *t){ZZ2zz_pageHash *p;ZZ_GET_HASH(zz_pageHash,h,t,p); return(p);}
void ZZVzz_pageHash ZZHzz_pageHash :: add(ZZ1zz_pageHash *h,ZZ2zz_pageHash *t){ZZ_ADD_HASH(zz_pageHash,h,t);}
ZZint ZZVzz_pageHash ZZHzz_pageHash :: add2(ZZ1zz_pageHash *h,ZZ2zz_pageHash *t,ZZint sameKey){
                    ZZint i; ZZ_ADD2_HASH(zz_pageHash,h,t,sameKey,i); return i;}
void ZZVzz_pageHash ZZHzz_pageHash :: del(ZZ1zz_pageHash *h,ZZ2zz_pageHash *t){ZZ_DELETE_HASH(zz_pageHash,h,t);}
void ZZVzz_pageHash ZZHzz_pageHash :: form(ZZ1zz_pageHash *h,ZZint sz){ZZ_FORM_HASH(zz_pageHash,h,sz);}
void ZZVzz_pageHash ZZHzz_pageHash :: resize(ZZ1zz_pageHash *h,ZZint sz){ZZ_RESIZE_HASH(zz_pageHash,h,sz);}
ZZint  ZZVzz_pageHash ZZHzz_pageHash :: size(ZZ1zz_pageHash *h,ZZint *n){ZZint s; ZZ_SIZE_HASH(zz_pageHash,h,s,*n); return(s);}
ZZ2zz_pageHash * ZZVzz_pageHash ZZHzz_pageHash :: slot(ZZ1zz_pageHash *h,ZZint st){ZZ2zz_pageHash *o; ZZ_SLOT_HASH(zz_pageHash,h,st,o); return(o);}
void ZZVzz_pageHash ZZHzz_pageHash :: free(ZZ1zz_pageHash *h){ZZ_FREE_HASH(zz_pageHash,h);}
// -----------------------------------------------------------------------
// This function disassembles the hash table, and without allocating
// new space, it reloads all objects back into it. The function is typically
// used after switching to a different ..hash() and/or ..cmp() functions.
// -----------------------------------------------------------------------
void ZZVzz_pageHash ZZHzz_pageHash :: newFun(ZZ1zz_pageHash *hp){
    ZZ2zz_pageHash *head,*s,*p; ZZint i,sz; char **a;
    zz_pageHash_iterator it;
    if(!hp || !(hp->ZZazz_pageHash))return;
    head=NULL; // move all objects into a single temporary list
    sz=hp->ZZazz_pageHash->size;
    a=(char**)(hp->ZZazz_pageHash->array);
    for(i=0; i<sz; i++) { // walk through all buckets
        s=slot(hp,i);
        it.start(s);
        while(p= ++it){
            p->ZZfzz_pageHash=head; head=p;
        }
        a[i]=NULL;
    }
    for(p=head; p; p=s){ // walk through the temporary list and reload objects
        s=p->ZZfzz_pageHash; p->ZZfzz_pageHash=NULL; add(hp,p);
    }
}
/* ----------------------------------------- */
void ZZVzz_pages ZZHzz_pages :: add(ZZ1zz_pages *s,ZZ2zz_pages *t){zz_pages_iterator *i;
    ZZ_ADD_DOUBLE_COLLECT(zz_pages,s,t);
    // check all iterators for this item
    for(i=zz_pages.iterators; i; i=i->fList){if(i->nxt==t->ZZfzz_pages)i->nxt=t;}
}
void ZZVzz_pages ZZHzz_pages :: ins(ZZ2zz_pages *s,ZZ2zz_pages *t){zz_pages_iterator *i;
    ZZ_INSERT_DOUBLE_COLLECT(zz_pages,s,t);
    // check all iterators for this item
    for(i=zz_pages.iterators; i; i=i->fList){if(i->nxt==t->ZZfzz_pages)i->nxt=t;}
}
void ZZVzz_pages ZZHzz_pages :: del(ZZ1zz_pages *p,ZZ2zz_pages *c){zz_pages_iterator *i;
    // check all iterators for this item
    if(!p || !c)return;
    for(i=zz_pages.iterators; i; i=i->fList){
        if(i->nxt==c){
            if(p->ZZczz_pages==c){i->nxt=NULL; i->boss=NULL;}
            else i->nxt=c->ZZfzz_pages;
        }
    }
    ZZ_DELETE_DOUBLE_COLLECT(zz_pages,p,c); }
void ZZVzz_pages ZZHzz_pages :: merge(ZZ2zz_pages *s,ZZ2zz_pages *t,ZZ1zz_pages *p){ZZ_MERGE_DOUBLE_COLLECT(zz_pages,s,t,p); }
void ZZVzz_pages ZZHzz_pages :: sort(ZZTsortFun cmpF,ZZ1zz_pages *p){ZZ_SORT_DOUBLE_COLLECT(zz_pages,cmpF,p);}
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
    ZZstrList[0].vObj[0]=(char *)(new Page((ZZZiClass *)NULL));
    ZZstrList[0].vObj[1]=(char *)(new Page((ZZZiClass *)NULL));
  }
  if(!(ZZstrList[1].vObj[0])){
    ZZstrList[1].vObj[0]=(char *)(new zzHead((ZZZiClass *)NULL));
    ZZstrList[1].vObj[1]=(char *)(new zzHead((ZZZiClass *)NULL));
  }
for(i=0;i<2;i++){
  ((zzHead *)(ZZstrList[1].vObj[0]))->ZZinitSet();
  ((Page *)(ZZstrList[0].vObj[0]))->ZZinitSet();
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
ZZ_LOCAL int ZZZIPage(void){return(0);}
ZZ_LOCAL int ZZZJPage(void){return(-1);}
ZZ_LOCAL int ZZZIzzHead(void){return(1);}
ZZ_LOCAL int ZZZJzzHead(void){return(-1);}
/* ----------------------------------------- */
ZZ_LOCAL void ZZvSet(ZZint tp){
  int i; i=ZZmemSwitch; ZZmemSwitch=0;
  switch(tp){
    case 0: (void)new Page((ZZZiClass *)NULL); break;
    case 1: (void)new zzHead((ZZZiClass *)NULL); break;
    default: ZZmsgD(27,tp); ZZerror=ZZerror|040;
  }
  ZZmemSwitch=i;
}
/* ----------------------------------------- */
ZZ_LOCAL void *ZZtopType(void *ptr,ZZint tp,ZZint *newTp){
  switch(tp){
    case 0: ptr=(void *)(((Page *)ptr)->zzThisIs((ZZint*)newTp)); break;
    case 1: ptr=(void *)(((zzHead *)ptr)->zzThisIs((ZZint*)newTp)); break;
    default: ZZmsgD(27,tp); ZZerror=ZZerror|040;
  }
  return(ptr);
}
