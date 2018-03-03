#include "zzincl.h"
#ifdef FLOATLINK
#include <math.h>
#endif
Author::Author(ZZZiClass *){ZZS_Author}
 void* Author::operator new(size_t size){void *ZZmassAlloc(size_t,ZZint);
  ZZnumObjects++;
  if(ZZmemSwitch){Author *p;
    ZZ_OBJECT_ALLOC(Author,p);return((void*)p);}
  else {return(ZZmassAlloc((size_t)size,(ZZint)1));}}
 void Author::operator delete(void *ptr){void ZZmassFree(void *);
  if(ZZnumObjects>0)ZZnumObjects--;
  if(ZZmemSwitch)ZZ_OBJECT_FREE(Author,(Author *)ptr)
  else ZZmassFree(ptr);}
Book::Book(ZZZiClass *x):Publication(x){ZZS_Book}
 void* Book::operator new(size_t size){void *ZZmassAlloc(size_t,ZZint);
  ZZnumObjects++;
  if(ZZmemSwitch){Book *p;
    ZZ_OBJECT_ALLOC(Book,p);return((void*)p);}
  else {return(ZZmassAlloc((size_t)size,(ZZint)1));}}
 void Book::operator delete(void *ptr){void ZZmassFree(void *);
  if(ZZnumObjects>0)ZZnumObjects--;
  if(ZZmemSwitch)ZZ_OBJECT_FREE(Book,(Book *)ptr)
  else ZZmassFree(ptr);}
Publication::Publication(ZZZiClass *){ZZS_Publication}
 void* Publication::operator new(size_t size){void *ZZmassAlloc(size_t,ZZint);
  ZZnumObjects++;
  if(ZZmemSwitch){Publication *p;
    ZZ_OBJECT_ALLOC(Publication,p);return((void*)p);}
  else {return(ZZmassAlloc((size_t)size,(ZZint)1));}}
 void Publication::operator delete(void *ptr){void ZZmassFree(void *);
  if(ZZnumObjects>0)ZZnumObjects--;
  if(ZZmemSwitch)ZZ_OBJECT_FREE(Publication,(Publication *)ptr)
  else ZZmassFree(ptr);}
Library::Library(ZZZiClass *){ZZS_Library}
 void* Library::operator new(size_t size){void *ZZmassAlloc(size_t,ZZint);
  ZZnumObjects++;
  if(ZZmemSwitch){Library *p;
    ZZ_OBJECT_ALLOC(Library,p);return((void*)p);}
  else {return(ZZmassAlloc((size_t)size,(ZZint)1));}}
 void Library::operator delete(void *ptr){void ZZmassFree(void *);
  if(ZZnumObjects>0)ZZnumObjects--;
  if(ZZmemSwitch)ZZ_OBJECT_FREE(Library,(Library *)ptr)
  else ZZmassFree(ptr);}

ZZint ZZioFunction(FILE *fp,ZZint io,ZZint type,char *p,ZZint strSz)
{
  int zz_out_Author(FILE *f,Author *ptr),zz_inp_Author(FILE *f,Author *ptr);
  void zz_opt_Author(FILE *f,Author *ptr),zz_ipt_Author(Author *ptr);
  int zz_out_Book(FILE *f,Book *ptr),zz_inp_Book(FILE *f,Book *ptr);
  void zz_opt_Book(FILE *f,Book *ptr),zz_ipt_Book(Book *ptr);
  int zz_out_Publication(FILE *f,Publication *ptr),zz_inp_Publication(FILE *f,Publication *ptr);
  void zz_opt_Publication(FILE *f,Publication *ptr),zz_ipt_Publication(Publication *ptr);
  int zz_out_Library(FILE *f,Library *ptr),zz_inp_Library(FILE *f,Library *ptr);
  void zz_opt_Library(FILE *f,Library *ptr),zz_ipt_Library(Library *ptr);
  /* Control of this function:
   *  io==0 reads the whole object (pointers and zz_inp_..())
   *  io==1 prints the whole object;
   *  io==2 reads only the attributes (call to zz_inp_..()).
   *  io==3 debugging print
   */

#ifdef ZZ_ANSI
  void *ZZnewObj(ZZint size,ZZint ini);
#else
  void *ZZnewObj();
#endif
  static char remChar=' ';
  char **s;
  ZZint skipPtr,i,n;

  /* decide when to skip printing pointers */
  skipPtr=0;
  if(type>=0){
      if(ZZstrList[type].numPtr<=0 && ZZstrList[type].timeIndex<0)skipPtr=1;

  }

  /* note everywhere here, fgets cannot handle 0-length string */
  if(io==0 && !skipPtr){
      if(type==(-1) && strSz>0){
          for(n=0; n<strSz-1; n=n+i){
              if(!fgets(p+n,strSz-n+1,fp))return(1);
              p[strSz-1]='\0';
              i=strlen(p+n);
          }
      }
      else {
          if(!fgets(ZZbuff,ZZ_BUFS,fp))return(1);
      }
  }

  switch(type){
    case -8: /* block of general bytes */
      if(io==1)fprintf(fp,"%u\n",*p);
      else {
         sscanf(ZZbuff,"%u",&i);
         *p=i;
      }
      break;

    case -7: /* float or an array of these */
      if(io==1)fprintf(fp,"%f\n",*((ZZfloat *)p));
      else {
         sscanf(ZZbuff,"%f",(float *)p);
      }
      break;

    case -6: /* int or an array of these */
      if(io==1)fprintf(fp,"%d\n",*((int *)p));
      else {
         sscanf(ZZbuff,"%d",(int *)p);
      }
      break;

    case -5: /* char * or an array of these */
      s=(char**)p;
#ifdef LARGE_POINTER
#ifdef Windows64
      if(io==1)fprintf(fp,"%I64u\n",*s);
      else {
          sscanf(ZZbuff,"%I64u",s);
      }
#else
      if(io==1)fprintf(fp,"%lu\n",*s);
      else {
          sscanf(ZZbuff,"%lu",s);
      }
#endif
#else
      if(io==1)fprintf(fp,"%d\n",*s);
      else {
          sscanf(ZZbuff,"%d",s);
      }
#endif
      break;

    case -4: /* array header */
      if(ZZnTbType>=9){
          if(io==1){
#ifdef LARGE_POINTER
#ifdef Windows64
            fprintf(fp,"%I64d %I64d %I64d %I64d %I64d %I64d %I64u\n",
#else
            fprintf(fp,"%d %d %d %d %d %d %lu\n",
#endif
#else
            fprintf(fp,"%d %d %d %d %d %d %d\n",
#endif
              (((ZZarray *)p)->num),
              (((ZZarray *)p)->waterM),
              (((ZZarray *)p)->strType),
              (((ZZarray *)p)->size),
              (((ZZarray *)p)->incr),
              (((ZZarray *)p)->hshType),
              (((ZZarray *)p)->array));
          }
          else {
#ifdef LARGE_POINTER
#ifdef Windows64
            sscanf(ZZbuff,"%I64d %I64d %I64d %I64d %I64d %I64d %I64u",
#else
            sscanf(ZZbuff,"%d %d %d %d %d %d %lu",
#endif
#else
            sscanf(ZZbuff,"%d %d %d %d %d %d %d",
#endif
              &(((ZZarray *)p)->num),
              &(((ZZarray *)p)->waterM),
              &(((ZZarray *)p)->strType),
              &(((ZZarray *)p)->size),
              &(((ZZarray *)p)->incr),
              &(((ZZarray *)p)->hshType),
              &(((ZZarray *)p)->array));
          }
      }
      else {  /* previous versions did not have hshType */
          if(io==1){
#ifdef LARGE_POINTER
#ifdef Windows64
            fprintf(fp,"%d %d %d %d %d %I64u\n",
#else
            fprintf(fp,"%I64d %I64d %I64d %I64d %I64d %I64lu\n",
#endif
#else
            fprintf(fp,"%d %d %d %d %d %d\n",
#endif
              (((ZZarray *)p)->num),
              (((ZZarray *)p)->waterM),
              (((ZZarray *)p)->strType),
              (((ZZarray *)p)->size),
              (((ZZarray *)p)->incr),
              (((ZZarray *)p)->array));
          }
          else {
#ifdef LARGE_POINTER
#ifdef Windows64
            sscanf(ZZbuff,"%I64d %I64d %I64d %I64d %I64d %I64u",
#else
            sscanf(ZZbuff,"%d %d %d %d %d %lu",
#endif
#else
            sscanf(ZZbuff,"%d %d %d %d %d %d",
#endif
              &(((ZZarray *)p)->num),
              &(((ZZarray *)p)->waterM),
              &(((ZZarray *)p)->strType),
              &(((ZZarray *)p)->size),
              &(((ZZarray *)p)->incr),
              &(((ZZarray *)p)->array));
          }
      }
      break;

    case -3: /* property array */
      if(io==1){
#ifdef LARGE_POINTER
#ifdef Windows64
        fprintf(fp,"%I64d %I64u\n",
#else
        fprintf(fp,"%d %lu\n",
#endif
#else
        fprintf(fp,"%d %u\n",
#endif
          (((struct ZZaProp *)p)->size),
          (((struct ZZaProp *)p)->array));
      }
      else {
#ifdef LARGE_POINTER
#ifdef Windows64
        sscanf(ZZbuff,"%d %I64u",
#else
        sscanf(ZZbuff,"%d %lu",
#endif
#else
        sscanf(ZZbuff,"%d %d",
#endif
          &(((struct ZZaProp *)p)->size),
          &(((struct ZZaProp *)p)->array));
      }
      break;

    case -2: /* property header */
      if(remChar=='c'){
        if(io==1){
#ifdef LARGE_POINTER
#ifdef Windows64
          fprintf(fp,"%I64u %I64u %c\n",
#else
          fprintf(fp,"%lu %lu %c\n",
#endif
#else
          fprintf(fp,"%d %d %c\n",
#endif
            (((struct ZZproperty *)p)->codeName),
            (((struct ZZproperty *)p)->next),
            (((struct ZZproperty *)p)->propType.cProp[0]));
        }
        else {
#ifdef LARGE_POINTER
#ifdef Windows64
          sscanf(ZZbuff,"%I64u %I64u %c",
#else
          sscanf(ZZbuff,"%lu %lu %c",
#endif
#else
          sscanf(ZZbuff,"%d %d %c",
#endif
          &(((struct ZZproperty *)p)->codeName),
          &(((struct ZZproperty *)p)->next),
          &(((struct ZZproperty *)p)->propType.cProp[0]));
        }
      }
      else if(remChar=='f'){
        if(io==1){
#ifdef LARGE_POINTER
#ifdef Windows64
          fprintf(fp,"%I64u %I64u %f\n",
#else
          fprintf(fp,"%lu %lu %f\n",
#endif
#else
          fprintf(fp,"%d %d %f\n",
#endif
            (((struct ZZproperty *)p)->codeName),
            (((struct ZZproperty *)p)->next),
            (((struct ZZproperty *)p)->propType.fProp));
        }
        else {
#ifdef LARGE_POINTER
#ifdef Windows64
          sscanf(ZZbuff,"%I64u %I64u %f",
#else
          sscanf(ZZbuff,"%lu %lu %f",
#endif
#else
          sscanf(ZZbuff,"%d %d %f",
#endif
            &(((struct ZZproperty *)p)->codeName),
            &(((struct ZZproperty *)p)->next),
            &(((struct ZZproperty *)p)->propType.fProp));
        }
      }
      else if(remChar=='i'){
        if(io==1){
#ifdef LARGE_POINTER
#ifdef Windows64
          fprintf(fp,"%I64u %I64u %d\n",
#else
          fprintf(fp,"%lu %lu %d\n",
#endif
#else
          fprintf(fp,"%d %d %d\n",
#endif
            (((struct ZZproperty *)p)->codeName),
            (((struct ZZproperty *)p)->next),
            (((struct ZZproperty *)p)->propType.iProp));
        }
        else {
#ifdef LARGE_POINTER
#ifdef Windows64
          sscanf(ZZbuff,"%I64u %I64u %d",
#else
          sscanf(ZZbuff,"%lu %lu %d",
#endif
#else
          sscanf(ZZbuff,"%d %d %d",
#endif
            &(((struct ZZproperty *)p)->codeName),
            &(((struct ZZproperty *)p)->next),
            &(((struct ZZproperty *)p)->propType.iProp));
        }
      }
      else {
        if(io==1){
#ifdef LARGE_POINTER
#ifdef Windows64
          fprintf(fp,"%I64u %I64u %lu\n",
#else
          fprintf(fp,"%lu %lu %lu\n",
#endif
#else
          fprintf(fp,"%d %d %d\n",
#endif
            (((struct ZZproperty *)p)->codeName),
            (((struct ZZproperty *)p)->next),
            (((struct ZZproperty *)p)->propType.arrayProp));
        }
        else {
#ifdef LARGE_POINTER
#ifdef Windows64
          sscanf(ZZbuff,"%I64u %I64u %lu",
#else
          sscanf(ZZbuff,"%lu %lu %lu",
#endif
#else
          sscanf(ZZbuff,"%d %d %d",
#endif
            &(((struct ZZproperty *)p)->codeName),
            &(((struct ZZproperty *)p)->next),
            &(((struct ZZproperty *)p)->propType.arrayProp));
        }
      }
      break;

    case -1: /* text string - usually a name */
      if(io==1)fprintf(fp,"%s\n",p);
      else {
        p[strSz-1]='\0';
      }
      /* remember the first character, which is important for properties */
      remChar=p[0];
      break;

    case 0:
      if(io==1)((Author *)p)->zz_opt_Author(fp,(Author *)p);
      if(io==1 || io==3)((Author *)p)->zz_out_Author(fp,(Author *)p);
      else {
          if(io==0)((Author *)p)->zz_ipt_Author((Author *)p);
         if(((Author *)p)->zz_inp_Author(fp,(Author *)p))return(1);
      }
      break;

    case 1:
      if(io==1)((Book *)p)->zz_opt_Book(fp,(Book *)p);
      if(io==1 || io==3)((Book *)p)->zz_out_Book(fp,(Book *)p);
      else {
          if(io==0)((Book *)p)->zz_ipt_Book((Book *)p);
         if(((Book *)p)->zz_inp_Book(fp,(Book *)p))return(1);
      }
      break;

    case 2:
      if(io==1)((Publication *)p)->zz_opt_Publication(fp,(Publication *)p);
      if(io==1 || io==3)((Publication *)p)->zz_out_Publication(fp,(Publication *)p);
      else {
          if(io==0)((Publication *)p)->zz_ipt_Publication((Publication *)p);
         if(((Publication *)p)->zz_inp_Publication(fp,(Publication *)p))return(1);
      }
      break;

    case 3:
      if(io==1)((Library *)p)->zz_opt_Library(fp,(Library *)p);
      if(io==1 || io==3)((Library *)p)->zz_out_Library(fp,(Library *)p);
      else {
          if(io==0)((Library *)p)->zz_ipt_Library((Library *)p);
         if(((Library *)p)->zz_inp_Library(fp,(Library *)p))return(1);
      }
      break;

    default: printf("ASCII IO wrong type=%d\n",type); break;
  }
return(0);
}
/* ----------------------------------------- */

int Author::zz_inp_Author(FILE *fp,Author *p)
{
    if(!fgets(ZZbuff,ZZ_BUFS,fp))return(1);
    sscanf(ZZbuff,"%d",&(p->phone));
    return(0);
}
/* ----------------------------------------- */

int Book::zz_inp_Book(FILE *fp,Book *p)
{
    if(!fgets(ZZbuff,ZZ_BUFS,fp))return(1);
    sscanf(ZZbuff,"%f",&(p->cost));
    return(0);
}
/* ----------------------------------------- */

int Publication::zz_inp_Publication(FILE *fp,Publication *p)
{
    if(!fgets(ZZbuff,ZZ_BUFS,fp))return(1);
    sscanf(ZZbuff,"%d",&(p->year));
    return(0);
}
/* ----------------------------------------- */

int Library::zz_inp_Library(FILE *fp,Library *p)
{
    fp=fp; p=p;
    return(0);
}
/* ----------------------------------------- */

int Author::zz_out_Author(FILE *fp,Author *p)
{
    if(ZZdebFLG)fprintf(fp," phone=%d\n",p->phone);
    else fprintf(fp,"%d\n",p->phone);
    return(0);
}
/* ----------------------------------------- */

int Book::zz_out_Book(FILE *fp,Book *p)
{
    if(ZZdebFLG)fprintf(fp," cost=%f\n",p->cost);
    else fprintf(fp,"%f\n",p->cost);
    return(0);
}
/* ----------------------------------------- */

int Publication::zz_out_Publication(FILE *fp,Publication *p)
{
    if(ZZdebFLG)fprintf(fp," year=%d\n",p->year);
    else fprintf(fp,"%d\n",p->year);
    return(0);
}
/* ----------------------------------------- */

int Library::zz_out_Library(FILE *fp,Library *p)
{
    fp=fp; p=p;
    return(0);
}
/* ----------------------------------------- */

void Author::zz_ipt_Author(Author *p){
#ifdef Windows64
        sscanf(ZZbuff,"%I64u %I64u",
#else
#ifdef LARGE_POINTER
        sscanf(ZZbuff,"%lu %lu",
#else
        sscanf(ZZbuff,"%d %d",
#endif
#endif
          &(((Author *)p)->ZZnauthName),
          &(((Author *)p)->ZZsauthors));
}
/* ----------------------------------------- */

void Book::zz_ipt_Book(Book *p){
#ifdef Windows64
        sscanf(ZZbuff,"%I64u %I64u %I64u",
#else
#ifdef LARGE_POINTER
        sscanf(ZZbuff,"%lu %lu %lu",
#else
        sscanf(ZZbuff,"%d %d %d",
#endif
#endif
          &(((Book *)p)->ZZnbookName),
          &(((Book *)p)->ZZftoAuthor),
          &(((Book *)p)->ZZfallBooks));
}
/* ----------------------------------------- */

void Publication::zz_ipt_Publication(Publication *p){
#ifdef Windows64
        sscanf(ZZbuff,"%I64u",
#else
#ifdef LARGE_POINTER
        sscanf(ZZbuff,"%lu",
#else
        sscanf(ZZbuff,"%d",
#endif
#endif
          &(((Publication *)p)->ZZspublications));
}
/* ----------------------------------------- */

void Library::zz_ipt_Library(Library *p){
#ifdef Windows64
        sscanf(ZZbuff,"%I64u %I64u %I64u",
#else
#ifdef LARGE_POINTER
        sscanf(ZZbuff,"%lu %lu %lu",
#else
        sscanf(ZZbuff,"%d %d %d",
#endif
#endif
          &(((Library *)p)->ZZcauthors),
          &(((Library *)p)->ZZcpublications),
          &(((Library *)p)->ZZaallBooks));
}
/* ----------------------------------------- */

void Author::zz_opt_Author(FILE *fp,Author *p){
#ifdef Windows64
        fprintf(fp,"%I64u %I64u\n",
#else
#ifdef LARGE_POINTER
        fprintf(fp,"%lu %lu\n",
#else
        fprintf(fp,"%d %d\n",
#endif
#endif
          (((Author *)p)->ZZnauthName),
          (((Author *)p)->ZZsauthors));
}
/* ----------------------------------------- */

void Book::zz_opt_Book(FILE *fp,Book *p){
#ifdef Windows64
        fprintf(fp,"%I64u %I64u %I64u\n",
#else
#ifdef LARGE_POINTER
        fprintf(fp,"%lu %lu %lu\n",
#else
        fprintf(fp,"%d %d %d\n",
#endif
#endif
          (((Book *)p)->ZZnbookName),
          (((Book *)p)->ZZftoAuthor),
          (((Book *)p)->ZZfallBooks));
}
/* ----------------------------------------- */

void Publication::zz_opt_Publication(FILE *fp,Publication *p){
#ifdef Windows64
        fprintf(fp,"%I64u\n",
#else
#ifdef LARGE_POINTER
        fprintf(fp,"%lu\n",
#else
        fprintf(fp,"%d\n",
#endif
#endif
          (((Publication *)p)->ZZspublications));
}
/* ----------------------------------------- */

void Library::zz_opt_Library(FILE *fp,Library *p){
#ifdef Windows64
        fprintf(fp,"%I64u %I64u %I64u\n",
#else
#ifdef LARGE_POINTER
        fprintf(fp,"%lu %lu %lu\n",
#else
        fprintf(fp,"%d %d %d\n",
#endif
#endif
          (((Library *)p)->ZZcauthors),
          (((Library *)p)->ZZcpublications),
          (((Library *)p)->ZZaallBooks));
}
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
ZZ2allBooks* ZZVallBooks ZZHallBooks :: get(ZZ1allBooks *h,ZZ2allBooks *t){ZZ2allBooks *p;ZZ_GET_HASH(allBooks,h,t,p); return(p);}
void ZZVallBooks ZZHallBooks :: add(ZZ1allBooks *h,ZZ2allBooks *t){ZZ_ADD_HASH(allBooks,h,t);}
ZZint ZZVallBooks ZZHallBooks :: add2(ZZ1allBooks *h,ZZ2allBooks *t,ZZint sameKey){
                    ZZint i; ZZ_ADD2_HASH(allBooks,h,t,sameKey,i); return i;}
void ZZVallBooks ZZHallBooks :: del(ZZ1allBooks *h,ZZ2allBooks *t){ZZ_DELETE_HASH(allBooks,h,t);}
void ZZVallBooks ZZHallBooks :: form(ZZ1allBooks *h,ZZint sz){ZZ_FORM_HASH(allBooks,h,sz);}
void ZZVallBooks ZZHallBooks :: resize(ZZ1allBooks *h,ZZint sz){ZZ_RESIZE_HASH(allBooks,h,sz);}
ZZint  ZZVallBooks ZZHallBooks :: size(ZZ1allBooks *h,ZZint *n){ZZint s; ZZ_SIZE_HASH(allBooks,h,s,*n); return(s);}
ZZ2allBooks * ZZVallBooks ZZHallBooks :: slot(ZZ1allBooks *h,ZZint st){ZZ2allBooks *o; ZZ_SLOT_HASH(allBooks,h,st,o); return(o);}
void ZZVallBooks ZZHallBooks :: free(ZZ1allBooks *h){ZZ_FREE_HASH(allBooks,h);}
// -----------------------------------------------------------------------
// This function disassembles the hash table, and without allocating
// new space, it reloads all objects back into it. The function is typically
// used after switching to a different ..hash() and/or ..cmp() functions.
// -----------------------------------------------------------------------
void ZZVallBooks ZZHallBooks :: newFun(ZZ1allBooks *hp){
    ZZ2allBooks *head,*s,*p; ZZint i,sz; char **a;
    allBooks_iterator it;
    if(!hp || !(hp->ZZaallBooks))return;
    head=NULL; // move all objects into a single temporary list
    sz=hp->ZZaallBooks->size;
    a=(char**)(hp->ZZaallBooks->array);
    for(i=0; i<sz; i++) { // walk through all buckets
        s=slot(hp,i);
        it.start(s);
        while(p= ++it){
            p->ZZfallBooks=head; head=p;
        }
        a[i]=NULL;
    }
    for(p=head; p; p=s){ // walk through the temporary list and reload objects
        s=p->ZZfallBooks; p->ZZfallBooks=NULL; add(hp,p);
    }
}
/* ----------------------------------------- */
void ZZVauthors ZZHauthors :: add(ZZ1authors *s,ZZ2authors *t){ZZ_ADD_SINGLE_COLLECT(authors,s,t); }
void ZZVauthors ZZHauthors :: app(ZZ1authors *p,ZZ2authors *x,ZZ2authors *y){
    if(!p || !x){ZZmsg(68); return;}
    y->ZZsauthors=x->ZZsauthors; x->ZZsauthors=y; if(x==chld(p))set(p,y);
}
void ZZVauthors ZZHauthors :: del(ZZ1authors *p,ZZ2authors *c){ZZ_DELETE_SINGLE_COLLECT(authors,p,c); }
void ZZVauthors ZZHauthors :: merge(ZZ2authors *s,ZZ2authors *t,ZZ1authors *p){ZZ_MERGE_SINGLE_COLLECT(authors,s,t,p); }
void ZZVauthors ZZHauthors :: sort(ZZTsortFun cmpF,ZZ1authors *p){ZZ_SORT_SINGLE_COLLECT(authors,cmpF,p);}
/* ----------------------------------------- */
void ZZVpublications ZZHpublications :: add(ZZ1publications *s,ZZ2publications *t){ZZ_ADD_SINGLE_COLLECT(publications,s,t); }
void ZZVpublications ZZHpublications :: app(ZZ1publications *p,ZZ2publications *x,ZZ2publications *y){
    if(!p || !x){ZZmsg(68); return;}
    y->ZZspublications=x->ZZspublications; x->ZZspublications=y; if(x==chld(p))set(p,y);
}
void ZZVpublications ZZHpublications :: del(ZZ1publications *p,ZZ2publications *c){ZZ_DELETE_SINGLE_COLLECT(publications,p,c); }
void ZZVpublications ZZHpublications :: merge(ZZ2publications *s,ZZ2publications *t,ZZ1publications *p){ZZ_MERGE_SINGLE_COLLECT(publications,s,t,p); }
void ZZVpublications ZZHpublications :: sort(ZZTsortFun cmpF,ZZ1publications *p){ZZ_SORT_SINGLE_COLLECT(publications,cmpF,p);}
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
    ZZstrList[0].vObj[0]=(char *)(new Author((ZZZiClass *)NULL));
    ZZstrList[0].vObj[1]=(char *)(new Author((ZZZiClass *)NULL));
  }
  if(!(ZZstrList[1].vObj[0])){
    ZZstrList[1].vObj[0]=(char *)(new Book((ZZZiClass *)NULL));
    ZZstrList[1].vObj[1]=(char *)(new Book((ZZZiClass *)NULL));
  }
  if(!(ZZstrList[2].vObj[0])){
    ZZstrList[2].vObj[0]=(char *)(new Publication((ZZZiClass *)NULL));
    ZZstrList[2].vObj[1]=(char *)(new Publication((ZZZiClass *)NULL));
  }
  if(!(ZZstrList[3].vObj[0])){
    ZZstrList[3].vObj[0]=(char *)(new Library((ZZZiClass *)NULL));
    ZZstrList[3].vObj[1]=(char *)(new Library((ZZZiClass *)NULL));
  }
for(i=0;i<2;i++){
  ((Library *)(ZZstrList[3].vObj[0]))->ZZinitSet();
  ((Publication *)(ZZstrList[2].vObj[0]))->ZZinitSet();
  ((Book *)(ZZstrList[1].vObj[0]))->ZZinitSet();
  ((Author *)(ZZstrList[0].vObj[0]))->ZZinitSet();
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
ZZ_LOCAL int ZZZIAuthor(void){return(0);}
ZZ_LOCAL int ZZZJAuthor(void){return(-1);}
ZZ_LOCAL int ZZZIBook(void){return(1);}
ZZ_LOCAL int ZZZJBook(void){return(-1);}
ZZ_LOCAL int ZZZIPublication(void){return(2);}
ZZ_LOCAL int ZZZJPublication(void){return(-1);}
ZZ_LOCAL int ZZZILibrary(void){return(3);}
ZZ_LOCAL int ZZZJLibrary(void){return(-1);}
/* ----------------------------------------- */
ZZ_LOCAL void ZZvSet(ZZint tp){
  int i; i=ZZmemSwitch; ZZmemSwitch=0;
  switch(tp){
    case 0: (void)new Author((ZZZiClass *)NULL); break;
    case 1: (void)new Book((ZZZiClass *)NULL); break;
    case 2: (void)new Publication((ZZZiClass *)NULL); break;
    case 3: (void)new Library((ZZZiClass *)NULL); break;
    default: ZZmsgD(27,tp); ZZerror=ZZerror|040;
  }
  ZZmemSwitch=i;
}
/* ----------------------------------------- */
ZZ_LOCAL void *ZZtopType(void *ptr,ZZint tp,ZZint *newTp){
  switch(tp){
    case 0: ptr=(void *)(((Author *)ptr)->zzThisIs((ZZint*)newTp)); break;
    case 1: ptr=(void *)(((Book *)ptr)->zzThisIs((ZZint*)newTp)); break;
    case 2: ptr=(void *)(((Publication *)ptr)->zzThisIs((ZZint*)newTp)); break;
    case 3: ptr=(void *)(((Library *)ptr)->zzThisIs((ZZint*)newTp)); break;
    default: ZZmsgD(27,tp); ZZerror=ZZerror|040;
  }
  return(ptr);
}
