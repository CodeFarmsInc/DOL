// pager is a self-enclosed program, which is a part of the library,
// but is itself coded with OrgC. File pager.hpp is automatically generated.
// It corresponds to the default file zzincl.h.
// File pager.k is the equivalent of zzincl.h,
// file pager.g is the equivalent of "zzfunc.c".
// These files are generated by running zzprep on pager.hpp.
//
// The reason why we can add pager in this form is that ZZinternal objects
// used in the pager do not have to be persistent. When the pager is closed,
// all its content is already stored on its file, and if the pager is
// invoked again on the same file by another program, the same data
// is automatically available.
//
// Also, a neutral ZZinterface separates the user code from the pager.
// The ZZinterface passes only record index, record size, and a buffer.
// No poZZinters to user object are being passed. Pager operates like an
// independent program in terms of global variables, orgC typetables, etc.
// The only reason why it links to the rest of the library (msgs.c)
// is the centrally controlled allocation and error messages.
//
// Pager is essentially a C functions which, in case of C++, is wrapped
// under a special hyper class. It is not included in UTILITIES,
// because it is a rather specialized operation, and it would increase
// the size of executables for enybody who needs saving to disk.
//
// Pager is implemented in a way which permits to keep several
// pagers operating independently at the same time. The poZZinter to the
// required zzHead (each zzHead represents one pager) is being passed 
// as a "general-link", cast as (char *). In this way, different user
// objects can have their own pagers, while the system is prevented
// from saving pagers to disk.
//
// A rather tricky sequence is required to make the pager a part
// of the OrgC library. First, the library must be compiled without
// the pager. Then the preprocessor is compiled, which depends
// on the general part of the library. Then the pager is compiled,
// (it needs the preprocessor), and can be added to the library.
// Jiri Soukup, Oct.11/91

#include "pager.hpp"
#include "pager.g"
#include <string.h>

/* offset for lseek() is always  in bytes from the beginning of the file */
static void pageToMemory(zzHead *, Page *);
static void pageToDisk(zzHead *, Page *);
static ZZint cmpPager(const void *,const void *);
Page *loadPage(zzHead *, ZZint );
void *ZZnewObj(ZZint,ZZint);
ZZint ZZdelObj(char *);

#ifdef ZORTECH
extern "C" {
    ZZint open(char *,ZZint,ZZint);
    ZZint creat(char *,ZZint);
    ZZint close(ZZint);
    ZZint read(ZZint,char *,ZZint);
    ZZint write(ZZint,char *,ZZint);
    ZZlong lseek(ZZint,ZZlong,ZZint);
}
#endif

#ifdef GNU
extern "C" {
    ZZint open(const char *,ZZint,...);
    // ZZint creat(const char *,short unsigned ZZint);
    ZZint close(ZZint);
    ZZlong lseek(ZZint,ZZlong,ZZint);
#ifndef UPP
    ZZint read(ZZint,char *,ZZint); 
    ZZint write(ZZint,char *,ZZint);
#endif
}
#endif

#ifndef MAC
#ifndef HP
#ifndef __VMS
#ifdef SUNPLUS
#ifndef SABERCPLUS
extern "C" {
    ZZint close(ZZint);
    ZZint read(ZZint,char *,ZZint);
    ZZint write(ZZint,char *,ZZint);
    ZZlong lseek(ZZint,ZZlong,ZZint);
#ifndef IBM
#ifndef LUCID
#ifndef SUN2_1
#ifndef DECPLUS
    ZZint open(char *,ZZint,ZZint);
#endif
#endif
#endif
#endif
}
#endif
#endif
#endif
#endif
#endif

/* SUN C++ Ver.3.0 does not like default constructors inline */
zzHead::zzHead(){ZZ_INIT(zzHead);}
zzHead::~zzHead(){ZZ_CHECK(zzHead);}
Page::Page(){ZZ_INIT(Page); dirty=0;}
Page::~Page(){ZZ_CHECK(Page);}

// ------------------------------------------------------------- 
// Return the high-water-mark of the currently used file
// ------------------------------------------------------------- 
ZZlong ZZfillPager(char *head){return ((zzHead *)head)->fileFill;}

/* ------------------------------------------------------------- */
/* ZZformPager() opens a new pager, and returns poZZinter to its header
 * casted as (char *). This is one of very few exceptions where
 * casting is used, and the true purpose is to block the expansion
 * mechanism from saving ZZinternal pager objects to disk.
 * When the function is called on a file which is already used,
 * the error is reported, and no action is taken.
 * If the file already exists, the old file is automatically used.
 * If the file does not exist yet, a new file is being opened.
 * Any problems with opening the files are reported through the general
 * message functions.
 */
char *ZZformPager(const char *fName,ZZint pageSize,ZZint numPages,ZZint init)
{
    char c,*p,*fn;
    zzHead *hp;
    ZZint i;

    // shut up warnings about unused variables
    ZZbestGuess=ZZbestGuess;
    ZZptrOff=ZZptrOff;
    ZZbindASCII=ZZbindASCII;
    ZZnoLeak=ZZnoLeak;
    ZZvClassPresent=ZZvClassPresent;
    ZZallocPtr=ZZallocPtr;
    ZZbindSize=ZZbindSize;
    ZZbindName=ZZbindName;
    ZZpList=ZZpList;
    ZZiList=ZZiList;

    i=sizeof(ZZint);
    if(numPages<=0)numPages=1;
    else if(i<4){ /* avoid size overflow later */
        i=32767/pageSize;
        if(i<numPages){numPages=i; ZZmsgD(30,numPages);}
    }
    zz_heads_iterator it(hStart);
    for(hp= ++it; hp; hp= ++it){
        fn=zz_fileName.fwd(hp);
        if(!strcmp(fName,fn)){
            ZZmsgS(36,fName); /* parser file already in use */
            return((char *)hp);
        }
    }
    hp=new zzHead;
    hStart=zz_heads.add(hStart,hp);
    fn=zz_util.strAlloc(fName);
    zz_fileName.add(hp,fn);
#ifdef ZORTECH
    hp->handle=open(fName,O_CREAT | O_RDWR,S_IREAD | S_IWRITE);
    if(hp->handle<0)hp->handle=creat(fName, 0700);
#else
#ifdef MAC
    hp->handle=open(fName,O_CREAT | O_RDWR);
#else
#ifdef __VMS
    hp->handle=open(fName,O_CREAT | O_RDWR, 0); 
                                /* use default file protection */
#else
#ifdef DOS
    hp->handle=open(fName,O_CREAT | O_RDWR | O_BINARY,S_IREAD | S_IWRITE);
#else
    hp->handle=open(fName,O_CREAT | O_RDWR,S_IREAD | S_IWRITE);
#endif
#endif
#endif
#endif
    if(hp->handle<0){
        ZZmsgS(0,fName); /* problem to open the file */
        return((char *)NULL);
    }
    hp->hwm=0;
    hp->pageSize=pageSize;
    hp->numPages=numPages;
    hp->buffSize=pageSize*numPages;
    hp->buffFill=0;
    hp->fileFill=lseek(hp->handle, 0L, 2); /* 2=end of file position */
    hp->mb=(char *)ZZnewObj(hp->buffSize,0);
    if(hp->mb==NULL){
        ZZmsgS(37,fName);
        fn=zz_fileName.del(hp);
        delete fn;
        hStart=zz_heads.del(hStart,hp);
        delete hp;
        return((char *)NULL);
    }
    hp->ini=NULL;
    if(init>0){
        hp->ini=(char *)ZZnewObj(pageSize,0);
        if(hp->ini==NULL)ZZmsgS(39,fName);
        else {
            if(init==1)c='\0'; else c=' ';
            for(p=hp->ini, i=0; i<pageSize; i++,p++)*p=c;
        }
    }

    /* form empty hash table with plenty of space */
    zz_pageHash.form(hp,2*numPages);
    return((char *)hp);
}
/* ------------------------------------------------------------- */
/* ZZioPager writes/reads a stream of bytes ZZinto the paging area.
 * The stream may overlap page boundaries.
 * When buff is given, it loads the result ZZinto it. 
 * Returns: Number of characters moved in either way.
 *     Returns -1 if there is a * problem, for example pager not set
 * on this object, or buff==NULL.
 */
ZZint ZZioPager(ZZint io,char *head,ZZlong ind,char *buff,ZZint n)
{
    ZZlong start; /* start of the page */
    ZZlong i1,i2; /* limits of the area to fill */
    ZZlong moved;  /* number of bytes moved within one page */
    zzHead *hp;
    ZZint pSize,pNo,i,k,sz1,sz2;
    static Page tp;
    Page *pp;
    char *c,*first,*p1,*p2;;

    if(!head || !buff)return(-1);
    first=NULL;
    hp=(zzHead *)head;
    pSize=hp->pageSize;
    pNo=(ZZint)(ind/pSize); /* page number */
    start=pNo*pSize; /* start of the first page */

    i2=ind+n; 
    if(i2>hp->hwm+1){
        if(io==0)i2=hp->hwm+1;
        else     hp->hwm=i2-1;
    }

    for(i1=ind, k=0; i1<i2; i1=i1+moved, start=start+pSize, pNo++){
        moved=pSize-(i1-start);
        tp.pageNo=pNo;
        pp=zz_pageHash.get(hp,&tp);
        if(!pp)pp=loadPage(hp,pNo);
        if(!pp){
            c=zz_fileName.fwd(hp);
            ZZmsgS(38,c);
            return(-1);
        }
        if(io==1 || buff==0)pp->dirty=1; 
        if(!first)first=pp->where;

#ifdef OLD // old version, tricky to convert, keep it for a while
        for(c=pp->where, i=(ZZint)(i1-start); i<pSize; i++,k++){
            if(k>=n)break; 
            if(io==1)c[i]=buff[k];
            else     buff[k]=c[i];
        }
#else // OLD
        c=pp->where;
        sz1=pSize-(i1-start);
        if(start+sz1+1 > hp->hwm) sz1=hp->hwm-start+1;
        sz2=n-k;
        if(sz1>sz2)sz1=sz2;
        if(io==1)memcpy(&(c[i1-start]), &(buff[k]), sz1);
        else    memcpy(&(buff[k]), &(c[i1-start]), sz1);
        k=k+sz1;
#endif // OLD
        /* move the page to the top of the stack */
        zz_pages.del(hp,pp);
        zz_pages.add(hp,pp);
        zz_pages.set(hp,pp);
        /* avoid loading a page if not needed */
        if(k>=n)break;
    }
    return i2-ind;
}
/* ------------------------------------------------------------- */
/* Functions to control the hashing */

ZZint zz_pageHash_class::cmp(Page *p1, Page *p2){
  if(p1->pageNo==p2->pageNo)return(0); else return(1); }

ZZint zz_pageHash_class::hash(Page *p, ZZint size){
  ZZint ZZhashInt(ZZint key,ZZint size); return(ZZhashInt(p->pageNo,size)); }
/* ------------------------------------------------------------- */
/* loadPage() loads the page of the given number ZZinto the memory buffer.
 * Decisions to be made:
 * Memory buffer assignment:
 *     - not full number of pages used: assign next section;
 *       create a new page object;
 *     - full number of pages is used: find the last page,
 *       send it to disk, copy new page ZZinto the same area,
 *       remove the Page from the stack and from the hash table;
 *       reassign pageNo; move the Page to a new position in
 *       the stack and in the hash table.
 */ 
Page *loadPage(zzHead *hp, ZZint n)
{
    Page *pp;
    char *p,c;
    ZZint i,pSize;

    pSize=hp->pageSize;
    if(hp->buffFill<hp->buffSize){
        /* page system not full, adding a new page */
        pp=new Page;
        pp->pageNo=n;
        pp->where=(&(hp->mb[hp->buffFill]));
        zz_pages.add(hp,pp);
        zz_pages.set(hp,pp);
        zz_pageHash.add(hp,pp);
        hp->buffFill+=pSize;

        if(hp->ini){ /* initialize the area */
            c=hp->ini[0];
            for(i=0, p=pp->where; i<pSize; i++, p++)*p=c;
        }
    }
    else {
        /* replace the oldest page */
        pp=zz_pages.child(hp);
        pageToDisk(hp,pp);
        zz_pages.del(hp,pp);
        zz_pageHash.del(hp,pp);
        pp->pageNo=n;
        zz_pages.add(hp,pp);
        zz_pages.set(hp,pp);
        zz_pageHash.add(hp,pp);
    }
    pageToMemory(hp,pp); /* if new data, this may result in no action */
    return(pp);
}
/* ------------------------------------------------------------- */
// Flush all the dirty pages to the disk, without closing the file
// The check for dirty pages is done inside pageToDisk().
/* ------------------------------------------------------------- */
void ZZflushPager(char *hc){
    zzHead *hp;
    Page *pp;

    hp=(zzHead *)hc;
    if(!hp || hp->handle<0)return;
    zz_pages.sort(cmpPager,hp); /* sort pages by pageNo */
    zz_pages_iterator it(hp);
    for(pp= ++it; pp; pp= ++it){
        pageToDisk(hp,pp);
    }
}
/* ------------------------------------------------------------- */
/* ZZclosePager() closes the given pager, sends all the information
 * to disk, closes the file, and frees all memory including the paging
 * buffer.
 *
 * The algorithm first sorts the list of all active pages, so that
 * when moving them to disk, no filler is required.
 */
void ZZclosePager(char *hc)
{
    Page *pp;
    char *fn;
    zzHead *hp;

    ZZflushPager(hc);
    hp=(zzHead *)hc;
    close(hp->handle);

    ZZdelObj(hp->mb);
    if(hp->ini)ZZdelObj(hp->ini);
    fn=zz_fileName.del(hp); /* disconnect the name */
    delete fn;
    zz_pageHash.free(hp); /* free the whole hash table */
    zz_pages_iterator it(hp);
    for(pp= ++it; pp; pp= ++it){ // takes pages form the stack
        zz_pages.del(hp,pp);
        delete pp;
    }
    hStart=zz_heads.del(hStart,hp); /* remove from list of pagers */
    delete hp;
}
/* ------------------------------------------------------------- */
/* Compare function for sorting pages in the increasing order of
 * page numbers. This will avoid using filler when closing a pager */
static ZZint cmpPager(const void *p1,const void *p2)
{
    Page *pp1,*pp2;
    pp1=(Page *)p1; pp2=(Page *)p2;
    if(pp1->pageNo<pp2->pageNo)return(-1);
    if(pp1->pageNo>pp2->pageNo)return(1);
    return(0);
}
/* ------------------------------------------------------------- */
/* Writing a page to the disk:
 *     - if the page is within the size of the file, just move it in;
 *     - if the page is outside of the current size, write a filler
 *       and then the new page; update fileFill info.
 */
static void pageToDisk(zzHead *hp, Page *pp)
{
    ZZlong newPos,size;
    
    if(pp->dirty==0)return;
    newPos=pp->pageNo;
    size=hp->pageSize;
    newPos=newPos*size;
    if(hp->fileFill<newPos){
        lseek(hp->handle, 0L, 2); /* 2=mode set to the end of file */
        /* creating a new section on disk */
        for(;hp->fileFill<newPos; hp->fileFill=hp->fileFill+size){
            /* filler pages must be initialized */
            if(hp->ini) write(hp->handle, hp->ini,hp->pageSize);
            else         write(hp->handle, pp->where,hp->pageSize);
        }
    }
    /* over-writing old data on disk */
    lseek(hp->handle, newPos, 0); /* 0=offset mode from beg.of file */
    write(hp->handle, pp->where, hp->pageSize);
    if(hp->fileFill<newPos+size)hp->fileFill=newPos+size;
    pp->dirty=0;
    return;
}
/* ------------------------------------------------------------- */
/* Moving a page from disk to memory - this is a straight byte transfer
 * If this section of the data is not on the disk yet, just do nothing.
 */
static void pageToMemory(zzHead *hp, Page *pp)
{
    ZZlong i,newPos,size;
    ZZint pSize;
    char *p,s;
    
    pSize=hp->pageSize;
    newPos=pp->pageNo;
    size=pSize;
    newPos=newPos*size;
    if(hp->fileFill<=newPos){
        if(hp->ini){ /* avoid old garbage in the new page */
            s=hp->ini[0];
            for(p=pp->where, i=0; i<pSize; i++, p++)*p=s;
        }
        return;
    }
    lseek(hp->handle, newPos, 0); /* 0=offset mode from beg.of file */
    read(hp->handle, pp->where, hp->pageSize);
    return;
}
// ------------------------------------------------------------- 
#ifdef ZZ_ANSI
static void blockWarnings(void){
#else
static void blockWarnings(){
#endif
ZZcustomPtr=ZZdiskIO;
ZZcustomPtr=ZZdebFLG; ZZdebFLG=ZZcustomPtr;
ZZnTbType=ZZpTbType; ZZpTbType=ZZnTbType;
ZZmemPool=ZZmemEnd; ZZmemEnd=ZZmemPool;
}
// ----------------------------------------------------------------
void ZZpagerCompile(void){
ZZbuff[0]=' ';
}
// ----------------------------------------------------------------