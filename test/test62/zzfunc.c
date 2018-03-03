#include "zzincl.h"
#ifdef FLOATLINK
#include <math.h>
#endif
Connection::Connection(ZZZiClass *){ZZS_Connection}
 void* Connection::operator new(size_t size){void *ZZmassAlloc(size_t,ZZint);
  ZZnumObjects++;
  if(ZZmemSwitch){Connection *p;
    ZZ_OBJECT_ALLOC(Connection,p);return((void*)p);}
  else {return(ZZmassAlloc((size_t)size,(ZZint)1));}}
 void Connection::operator delete(void *ptr){void ZZmassFree(void *);
  if(ZZnumObjects>0)ZZnumObjects--;
  if(ZZmemSwitch)ZZ_OBJECT_FREE(Connection,(Connection *)ptr)
  else ZZmassFree(ptr);}
Station::Station(ZZZiClass *){ZZS_Station}
 void* Station::operator new(size_t size){void *ZZmassAlloc(size_t,ZZint);
  ZZnumObjects++;
  if(ZZmemSwitch){Station *p;
    ZZ_OBJECT_ALLOC(Station,p);return((void*)p);}
  else {return(ZZmassAlloc((size_t)size,(ZZint)1));}}
 void Station::operator delete(void *ptr){void ZZmassFree(void *);
  if(ZZnumObjects>0)ZZnumObjects--;
  if(ZZmemSwitch)ZZ_OBJECT_FREE(Station,(Station *)ptr)
  else ZZmassFree(ptr);}
Place::Place(ZZZiClass *){ZZS_Place}
 void* Place::operator new(size_t size){void *ZZmassAlloc(size_t,ZZint);
  ZZnumObjects++;
  if(ZZmemSwitch){Place *p;
    ZZ_OBJECT_ALLOC(Place,p);return((void*)p);}
  else {return(ZZmassAlloc((size_t)size,(ZZint)1));}}
 void Place::operator delete(void *ptr){void ZZmassFree(void *);
  if(ZZnumObjects>0)ZZnumObjects--;
  if(ZZmemSwitch)ZZ_OBJECT_FREE(Place,(Place *)ptr)
  else ZZmassFree(ptr);}
Network::Network(ZZZiClass *){ZZS_Network}
 void* Network::operator new(size_t size){void *ZZmassAlloc(size_t,ZZint);
  ZZnumObjects++;
  if(ZZmemSwitch){Network *p;
    ZZ_OBJECT_ALLOC(Network,p);return((void*)p);}
  else {return(ZZmassAlloc((size_t)size,(ZZint)1));}}
 void Network::operator delete(void *ptr){void ZZmassFree(void *);
  if(ZZnumObjects>0)ZZnumObjects--;
  if(ZZmemSwitch)ZZ_OBJECT_FREE(Network,(Network *)ptr)
  else ZZmassFree(ptr);}
/* ----------------------------------------- */

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
/* ----------------------------------------- */
/* ----------------------------------------- */
void ZZVroads ZZHroads :: add(ZZ1roads **v,ZZ2roads *e){ZZ_ADD_SINGLE_GRAPH(roads,v,e); }
void ZZVroads ZZHroads :: del(ZZ2roads *e){ZZ_DELETE_SINGLE_GRAPH(roads,NULL,e); }
ZZ2roads* ZZVroads ZZHroads :: fwd(ZZ1roads **v,ZZ2roads *e){ZZ2roads *t;
      if(e->ZZxroads==v[0])t=e->ZZrroads;
      else if(e->ZZyroads==v[0])t=e->ZZsroads;
      else t=NULL;
      if(t){
          if(t->ZZxroads==v[0])v[1]=t->ZZyroads;
          else if(t->ZZyroads==v[0])v[1]=t->ZZxroads;
      }
      else v[1]=NULL;
      return(t);
}
void ZZVroads ZZHroads :: set(ZZ1roads *v,ZZ2roads *e){
    if(e->ZZxroads==v || e->ZZyroads==v)v->ZZeroads=e;
    else ZZmsgSS(32,(char *)v,(char *)e);
}
/* ----------------------------------------- */
void ZZVflights ZZHflights :: add(ZZ1flights **v,ZZ2flights *e){ZZ_ADD_SINGLE_GRAPH(flights,v,e); }
void ZZVflights ZZHflights :: del(ZZ2flights *e){ZZ_DELETE_SINGLE_GRAPH(flights,NULL,e); }
ZZ2flights* ZZVflights ZZHflights :: fwd(ZZ1flights **v,ZZ2flights *e){ZZ2flights *t;
      if(e->ZZxflights==v[0])t=e->ZZrflights;
      else if(e->ZZyflights==v[0])t=e->ZZsflights;
      else t=NULL;
      if(t){
          if(t->ZZxflights==v[0])v[1]=t->ZZyflights;
          else if(t->ZZyflights==v[0])v[1]=t->ZZxflights;
      }
      else v[1]=NULL;
      return(t);
}
void ZZVflights ZZHflights :: set(ZZ1flights *v,ZZ2flights *e){
    if(e->ZZxflights==v || e->ZZyflights==v)v->ZZeflights=e;
    else ZZmsgSS(32,(char *)v,(char *)e);
}
/* ----------------------------------------- */
void ZZVplacesTree ZZHplacesTree :: add(ZZ1placesTree *p,ZZ1placesTree *c){ZZ_ADD_SINGLE_TREE(placesTree,p,c); }
void ZZVplacesTree ZZHplacesTree :: app(ZZ1placesTree *t,ZZ1placesTree *c){ZZ_APPEND_SINGLE_TREE(placesTree,t,c); }
void ZZVplacesTree ZZHplacesTree :: del(ZZ1placesTree *t){ZZ_DELETE_SINGLE_TREE(placesTree,NULL,t); }
/* ----------------------------------------- */
#ifndef ZORTECH
void ZZVplacesArr ZZHplacesArr :: sort(ZZTsortArr cmpF,ZZ1placesArr *hp){ZZ_SORT_ARRAY(placesArr,cmpF,hp);}
#endif
void ZZVplacesArr ZZHplacesArr :: inHeap(ZZTsortFun cmpF,ZZ1placesArr *hp,ZZ2placesArr *p,ZZTheapBck bck){
                     ZZ_IN_HEAP(placesArr,cmpF,hp,p,bck);}
void ZZVplacesArr ZZHplacesArr :: outHeap(ZZTsortFun cmpF,ZZ1placesArr *hp,ZZ2placesArr *p,ZZTheapBck bck){
                     ZZ_OUT_HEAP(placesArr,cmpF,hp,p,bck);}
void ZZVplacesArr ZZHplacesArr :: updHeap(ZZTsortFun cmpF,ZZ1placesArr *hp,ZZint i,ZZTheapBck bck){
                     ZZ_UPDATE_HEAP(placesArr,cmpF,hp,i,bck);}
void ZZVplacesArr ZZHplacesArr :: delHeap(ZZTsortFun cmpF,ZZ1placesArr *hp,ZZint i,ZZTheapBck bck){
                     ZZ_DELETE_HEAP(placesArr,cmpF,hp,i,bck);}
void ZZVplacesArr ZZHplacesArr :: push(ZZ1placesArr *hp,ZZ2placesArr *p){ZZ_PUSH_ARRAY(placesArr,hp,p);}
ZZ2placesArr* ZZVplacesArr ZZHplacesArr :: pop(ZZ1placesArr *hp){ZZ2placesArr *p; ZZ_POP_ARRAY(placesArr,hp,p); return(p);}
// -----------------------------------------------------------------------
// Add a new object into the ordered collection. This is relatively
// fast using binary search to find the position, but a section of
// the array must move to open one slot.
// -----------------------------------------------------------------------
void ZZVplacesArr ZZHplacesArr :: addOrd(ZZTsortFun cmpF,ZZ1placesArr *hp,ZZ2placesArr *op){
    ZZint k=binSearch(cmpF,hp,op);
    if(k<0) ins(hp,-k-1,op);
}
// -----------------------------------------------------------------------
// First find the object, using binary search, then remove it using the
// other delOrd() function
// -----------------------------------------------------------------------
void ZZVplacesArr ZZHplacesArr :: delOrd(ZZTsortFun cmpF,ZZ1placesArr *hp,ZZ2placesArr *op){
    ZZint k=binSearch(cmpF,hp,op);
    if(k<0)return; // the object is not in the array
    delOrd(hp,k-1);
}
    
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void ZZVplacesArr ZZHplacesArr :: delOrd(ZZ1placesArr *hp,ZZint ind){
    ZZ2placesArr* a=(ZZ2placesArr *)(hp->ZZaplacesArr->array);
    ZZint wm=hp->ZZaplacesArr->waterM;
    // some platforms have special efficient ways of moving blocks of memory
#ifdef MICROSOFT
    if(ind<wm)memmove(&(a[ind]), &(a[ind+1]), sizeof(ZZ2placesArr)*(wm-ind));
#else // MICROSOFT
    for(ZZint i=ind; i<wm; i++)a[i]=a[i+1];
#endif// MICROSOFT
    hp->ZZaplacesArr->waterM=wm-1;
}

// -----------------------------------------------------------------------
// Insert a copy of object op into the array before the object which
// now has index i, and shift the remaining part of the array to open
// one slot. If i>waterM, insert the object into position i.
// -----------------------------------------------------------------------
void ZZVplacesArr ZZHplacesArr :: ins(ZZ1placesArr *hp,ZZint i,ZZ2placesArr *op){
    ZZ2placesArr* a=(ZZ2placesArr *)(hp->ZZaplacesArr->array);
    ZZint wm=hp->ZZaplacesArr->waterM;
    // some platforms have special efficient ways of moving blocks of memory
#ifdef MICROSOFT
    if(i<=wm)memmove(&(a[i+1]), &(a[i]), sizeof(ZZ2placesArr)*(wm-i+1));
#else // MICROSOFT
    for(ZZint k=wm; k>=i; k--)a[k+1]=a[k];
#endif// MICROSOFT
    a[i]=(*op);
    if(i<=wm)wm++; else wm=i;
    hp->ZZaplacesArr->waterM=wm;
}

// -----------------------------------------------------------------------
// Binary search, returns the index of the given object, or the next
// after it (if the equivalent object is not in the array) with 
// a negative sign. If the array has not been formed, the function
// generates an error message and returns 0.
// IMPORTANT: The index returned by this routine starts from 1, NOT from 0
//   as usual in C. The reason is that 0 cannot be give a negative sign.
// -----------------------------------------------------------------------
ZZint ZZVplacesArr ZZHplacesArr :: binSearch(ZZTsortFun cmpF,ZZ1placesArr *hp,ZZ2placesArr *op){
    ZZint i1,i2,k,cmp,wm; ZZ2placesArr *rr; ZZ2placesArr *arr; ZZarray *za;

    za=hp->ZZaplacesArr;
    if(za){
        i1=0; wm=i2=hp->ZZaplacesArr->waterM; k= -1; arr=(ZZ2placesArr *)(hp->ZZaplacesArr->array);
    }
    if(!za || !arr){ZZmsg(37); return 0;}
    if(i2<0)return -1;
    rr= &(arr[i1]); cmp=cmpF(op,rr);
    if(cmp==0)return i1+1;
    if(cmp<0)return -(i1+1);
    rr= &(arr[i2]); cmp=cmpF(op,rr);
    if     (cmp>0) return -(wm+2); 
    else if(cmp==0)return wm+1; 

    k=(i1+i2)/2;
    while(k>i1){
        rr= &(arr[k]); cmp=cmpF(rr,op);
        if(cmp>0)i2=k;
        else if(cmp<0)i1=k;
        else return k+1;
        k=(i1+i2)/2;
    }
    k++;
    rr= &(arr[k]); cmp=cmpF(rr,op);
    if(cmp==0)return k+1; else return -(k+1);
}

// -----------------------------------------------------------------------
// For the key given in op, find the index of the object in the array,
// using the binary search. If the object is not found, return 
// the index of the entry before which the new object would have
// to be inserted. The function returns found=1 when found, =0 when not.
// -----------------------------------------------------------------------
ZZint ZZVplacesArr ZZHplacesArr :: getOrd(ZZTsortFun cmpF,ZZ1placesArr *hp,ZZ2placesArr *op,ZZint *found){
    ZZint k=binSearch(cmpF,hp,op);
    if(k>0){*found=1; k=k-1;}
    else   {*found=0; k=(-k-1);}
    return k;
}
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
    ZZstrList[0].vObj[0]=(char *)(new Connection((ZZZiClass *)NULL));
    ZZstrList[0].vObj[1]=(char *)(new Connection((ZZZiClass *)NULL));
  }
  if(!(ZZstrList[1].vObj[0])){
    ZZstrList[1].vObj[0]=(char *)(new Station((ZZZiClass *)NULL));
    ZZstrList[1].vObj[1]=(char *)(new Station((ZZZiClass *)NULL));
  }
  if(!(ZZstrList[2].vObj[0])){
    ZZstrList[2].vObj[0]=(char *)(new Place((ZZZiClass *)NULL));
    ZZstrList[2].vObj[1]=(char *)(new Place((ZZZiClass *)NULL));
  }
  if(!(ZZstrList[3].vObj[0])){
    ZZstrList[3].vObj[0]=(char *)(new Network((ZZZiClass *)NULL));
    ZZstrList[3].vObj[1]=(char *)(new Network((ZZZiClass *)NULL));
  }
for(i=0;i<2;i++){
  ((Network *)(ZZstrList[3].vObj[0]))->ZZinitSet();
  ((Place *)(ZZstrList[2].vObj[0]))->ZZinitSet();
  ((Station *)(ZZstrList[1].vObj[0]))->ZZinitSet();
  ((Connection *)(ZZstrList[0].vObj[0]))->ZZinitSet();
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
ZZ_LOCAL int ZZZIConnection(void){return(0);}
ZZ_LOCAL int ZZZJConnection(void){return(-1);}
ZZ_LOCAL int ZZZIStation(void){return(1);}
ZZ_LOCAL int ZZZJStation(void){return(-1);}
ZZ_LOCAL int ZZZIPlace(void){return(2);}
ZZ_LOCAL int ZZZJPlace(void){return(-1);}
ZZ_LOCAL int ZZZINetwork(void){return(3);}
ZZ_LOCAL int ZZZJNetwork(void){return(-1);}
/* ----------------------------------------- */
ZZ_LOCAL void ZZvSet(ZZint tp){
  int i; i=ZZmemSwitch; ZZmemSwitch=0;
  switch(tp){
    case 0: (void)new Connection((ZZZiClass *)NULL); break;
    case 1: (void)new Station((ZZZiClass *)NULL); break;
    case 2: (void)new Place((ZZZiClass *)NULL); break;
    case 3: (void)new Network((ZZZiClass *)NULL); break;
    default: ZZmsgD(27,tp); ZZerror=ZZerror|040;
  }
  ZZmemSwitch=i;
}
/* ----------------------------------------- */
ZZ_LOCAL void *ZZtopType(void *ptr,ZZint tp,ZZint *newTp){
  switch(tp){
    case 0: ptr=(void *)(((Connection *)ptr)->zzThisIs((ZZint*)newTp)); break;
    case 1: ptr=(void *)(((Station *)ptr)->zzThisIs((ZZint*)newTp)); break;
    case 2: ptr=(void *)(((Place *)ptr)->zzThisIs((ZZint*)newTp)); break;
    case 3: ptr=(void *)(((Network *)ptr)->zzThisIs((ZZint*)newTp)); break;
    default: ZZmsgD(27,tp); ZZerror=ZZerror|040;
  }
  return(ptr);
}
