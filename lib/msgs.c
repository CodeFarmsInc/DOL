/*
IMPORTANT IMPORTANT IMPORTANT IMPORTANT

WHEN MODIFYING TEH ERROR REPORTING FUNCTIONS IN THIS FILE msgs.c,
REMEMBER THAT EACH FUNCTION HAS TWO VERSIONS: FOR Winodws7 64bits,
AND THEN FOR ALL OTHER ENVIRONMENTS. IF YOU MODIFY ANY OF THESE FUNCTIONS,
BOTH ITS VERSIONS MUST BE MODIFIED. 
There is no way in C++ to make the formats generic.
                                                Jiri Soukup, Oct.22, 2011
*/

/****************************************************************/
/*							      	*/
/*   Copyright (C) 1988 1989             			*/
/*	Code Farms Inc.,  All Rights Reserved.			*/
/*							  	*/
/****************************************************************/

#include "environ.h"
#include "types.h"

#define zzLIB
#include <stdio.h>
#ifndef GNU
#include <stddef.h>
#endif
#ifdef MICROSOFT
#include <stdlib.h>
#include <malloc.h>
#endif

/* define DECPLUS comes from heading.h, and is not available here */
#ifdef DEC
#ifdef ZZcplus
#ifndef __VMS
#include <malloc.h>
#endif
#include <stdlib.h>
#endif
#endif

#include "types.h"
#include "heading.h"
#include "msgs.h"

char *ZZvirtCntr={(char *)0}; /* controls allocation, see ZZmassAlloc() */
static char msgBuf[256];
static char codeBuf[16];
#ifdef ZZ_ANSI
static void zzReportError(ZZint,char*,char*);
#else
static void zzReportError();
#endif

#ifdef UNIX
#ifndef MAC
#ifndef HP
#ifndef COHERENT
#include <malloc.h>
#endif
#endif
#endif
#endif
#ifdef TURBOC
#include <alloc.h>
#endif

/* -------------------------------------------------------------------- */
/* allocate a new object or objects -
 * here the user can replace malloc() by a private allocation call
 * for the entire Organized C operation
 */
#ifdef ZZ_ANSI
ZZvoidS *ZZnewObj(ZZint sz,ZZint ini) 
{
    ZZvoidS *ZZnewBlock(unsigned ZZint size);
    ZZvoidS *ZZnewBit(ZZsize size);
    ZZvoidS *ZZmassAlloc(size_t, ZZint) ;
#else


ZZvoidS *ZZnewObj(sz,ini) 
ZZint sz;
ZZint ini; /* 0=no initialization, 1=initialize whole object with 0 */
    ZZvoidS *ZZnewBlock(), *ZZnewBit();
    ZZvoidS *ZZmassAlloc() ;
#endif
    void *ptr;
    char *p;
    ZZsize size;
    ZZint i;

    size=sz;
    ptr=(void *)NULL;
    if(ZZmemSwitch==1)ptr=ZZnewBlock(size);
    if(ZZmemSwitch==2)ptr=ZZnewBit(size);
    if(ptr && ini){
        // for(i=0, p=(char *)ptr; i<sz; i++, p++)*p='\0';
	memset(ptr,0,sz);
    }
    if(!ptr)ptr=ZZmassAlloc((size_t)sz,ini);
    return(ptr);
}
/* -------------------------------------------------------------------- */
/* free an object or objects -
 * here the user can replace free() by a private de-allocation call
 * for the entire Organized C operation
 */
#ifdef ZZ_ANSI
ZZint ZZdelObj(char *ptr)
{
    void ZZdelBlock(char *p);
    ZZvoidS ZZmassFree(void *ptr);
#else


ZZint ZZdelObj(ptr)
char *ptr;
{
    void ZZdelBlock();
    ZZvoidS ZZmassFree();
#endif

    if(!ptr){ZZmsg(55); return(1);} /* just a safety precaution */
    if(ZZmemSwitch==1)ZZdelBlock(ptr);
    if(ZZmemSwitch==0)ZZmassFree((void *)ptr);
    // NOTE that for ZZmemSwitch (mem.blasting) nothing is done
    return(0);
}
/* -------------------------------------------------------------------- */
/* Allocate memory for massive memory management.
 * If the global variable ZZvirtCntr!=0, skip allocation, and use
 * the value given there. This is a trick to re-load vf.pointers
 * in C++. Always re-set ZZvirtCntr=NULL on the exit from ZZMassAlloc()
 */
#ifdef ZZ_ANSI
ZZvoidS *ZZmassAlloc(size_t size,ZZint ini) 
{
#ifndef ZZcplus
#ifndef GNU
    ZZvoidS *malloc(size_t sz);
    ZZvoidS *calloc(size_t n,size_t sz);
#endif
#endif
#else


ZZvoidS *ZZmassAlloc(size,ini) 
size_t size;
ZZint ini; /* 0=no initialization, 1=initialize under certain conditions,
	      2=always initialize */
{
#endif
    void *ptr;
    char *p;
    ZZint flg;
    size_t i;

    if(ZZvirtCntr){
        ptr=(void *)ZZvirtCntr;
        ZZvirtCntr=NULL;
    }
    else {
        flg=ZZcallocFlg;
#ifdef ZZcplus
        flg=1;
#endif

/* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */
/* For a private allocation scheme, replace just the two following lines */
/* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */
        if(flg)ptr=(void *)calloc((size_t)1,(size_t)size);
        else           ptr=(void *)malloc((size_t)size);
/* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */
        if(!ptr){
            ZZmsgSD(13,"mass allocation",size);
            ZZerrFLG=ZZerrFLG|01;
        }
        else if(ini==2 || (ini==1 && !flg)){
            /* initialize the object with 0 */
            // for(i=0, p=(char *)ptr; i<size; i++, p++) *p='\0';
	    memset(ptr,0,size);
        }

    }
    return(ptr);
}
/* -------------------------------------------------------------------- */
/* free memory for massive memory management */
#ifdef ZZ_ANSI
ZZvoidS ZZmassFree(void *ptr) 
{
#ifndef ZZcplus
#ifndef MAC
#ifdef UNIX

#ifdef LIANT
    void free(char *p);
#else
#ifdef HP
    void free(void *p);
#else
#ifdef LUCID
    void free(void *p);
#else
#ifndef GNU
    ZZint free(void *p);
#endif
#endif /* LUCID */
#endif /* HP */
#endif /* LIANT */

#else   
    void free(void *p);
#endif  /* UNIX */

#endif  /* MAC */
#endif  /* ZZcplus */
#else   /* ZZ_ANSI */


ZZvoidS ZZmassFree(ptr) 
void *ptr;
{
#ifndef MAC
#ifdef UNIX

#ifdef LIANT
    void free();
#else
#ifndef HP
#ifndef DEC
#ifndef SUN2_1
    ZZint free();
#endif
#endif
#endif
#endif  /* LIANT */

#else   /* UNIX */
    void free();
#endif  /* UNIX */
#endif  /* MAC */
#endif  /* ZZ_ANSI */

    if(!ptr){ZZmsg(55); return;} /* just a safety precaution */

#ifdef SUN
#ifdef LUCID
    (void)free(ptr);
#else
    (void)free((char *)ptr);
#endif
#else
    (void)free(ptr);
#endif
}

#ifdef Windows64 // ====================================================

/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsg(ZZint i) {
#else
void ZZmsg(i) ZZint i; {
#endif
switch(i){
  case 0: sprintf(msgBuf,"ZZinternal error, cannot find selfID organization\n\0"); break;
  case 1: sprintf(msgBuf,
                "WARNING: ZZ_INHERIT present, util.clear() does nothing\n\0"); break;
  case 4: sprintf(msgBuf,"problem with ZZinternal file in getMaster()\n\0");break;
  case 5: sprintf(msgBuf,"cannot run, empty master table\n\0"); break;
  case 6: sprintf(msgBuf,"problem to allocate master tables\n\0"); break;
  case 7: sprintf(msgBuf,"problem to allocate ZZhierarchy definition\n\0"); break;
  case 8: sprintf(msgBuf,"master table error - from organization to its pointers\n\0");
                                                                         break;
  case 9: sprintf(msgBuf,"master table error - from function to its support\n\0"); break;
  case 10: sprintf(msgBuf,"master table error - next in ZZsupport\n\0"); break;
  case 13: sprintf(msgBuf,"problem to open file /dev/idmodule\n\0"); break;
  case 14: sprintf(msgBuf,"problem to read ID module code\n\0"); break;
  case 15: sprintf(msgBuf,"problem: not legitimate ID module code\n\0"); break;
  case 16: sprintf(msgBuf,"correct syntax: zzhelp something\n\0"); break;
  case 17: sprintf(msgBuf,"argument too long\n\0"); break;
  case 18: sprintf(msgBuf,"file macro/zzmaster is missing\n\0"); break;
  case 19: sprintf(msgBuf,"nothing meaningful found\n\0"); break;
  case 20: sprintf(msgBuf,"cannot open file zztemp or zzinfo\n\0"); break;
  case 21: sprintf(msgBuf,"select numbers: \0"); break;
  case 22: sprintf(msgBuf,"view file zzinfo ...\n\0"); break;
  case 23: sprintf(msgBuf,"Best match found:\n\0"); break;
  case 24: sprintf(msgBuf,"function    :\0"); break;
  case 25: sprintf(msgBuf,"gen.function:\0"); break;
  case 26: sprintf(msgBuf,"gen.macro   :\0"); break;
  case 27: sprintf(msgBuf,"macro       :\0"); break;
  case 32: sprintf(msgBuf,"syntax: zzmerge <inp1> <inp2> <out>\n\0"); break;
  case 33: sprintf(msgBuf,"error when dumping property header\n\0"); break;
  case 34: sprintf(msgBuf,"ZZinternal problems, ZZpropDelete() - empty chain\n\0"); break;
  case 35: sprintf(msgBuf,"ZZinternal inconsistency in ZZpropDelete() - problems\n\0");
                                                                        break;
  case 36: sprintf(msgBuf,"install.error: larger size needed for ZZproperty.cProp\n\0");
                                                                        break;
  case 37: sprintf(msgBuf,"error: attempt to access array without forming it first\n\0");
                                                                        break;
  case 38: sprintf(msgBuf,"error: cannot reset hash table without forming it first\n\0");
                                                                        break;
  case 39: sprintf(msgBuf,"unable to allocate a new hash table, old one remains\n\0");
                                                                        break;
  case 40: sprintf(msgBuf,"ZZinternal problem to allocate small array in ZZmemory()\n\0");
                                                                        break;
  case 41: sprintf(msgBuf,"error: short beginning of the ASCII file\n\0"); break;
  case 42: sprintf(msgBuf,"number of organizations decreased\n\0"); break;
  case 44: sprintf(msgBuf,"error in binary format when readBind()\n\0"); break;
  case 46: sprintf(msgBuf,"problem to close file\n\0"); break;
  case 47: sprintf(msgBuf,"ZZinternal algorithm error in DELETE_SINGLE_GRAPH\n\0"); break;
  case 48: sprintf(msgBuf,"syntax: zzselect <inp1> <inp2> <out>\n\0"); break;
  case 50: sprintf(msgBuf,"unexpected size of (char *), for 64bits Windows check lib/environ.h\n\0"); break;
  case 51: sprintf(msgBuf,"ZZinternal error: unable to convert (char *) to ZZint\n\0"); break;
  case 52: sprintf(msgBuf,"not enough memory -\n\0"); break;
  case 53: sprintf(msgBuf,"should never happen: fopen returns -1\n\0"); break;
  case 54: sprintf(msgBuf,"error: OPENNING incompatible data\n\0");break;
  case 55: sprintf(msgBuf,"should never happen: called ZZdelObj(NULL)\n\0"); break;
  case 56: sprintf(msgBuf,"ZZinternal error: there is a header array and mode=0\n\0");break;
  case 57: sprintf(msgBuf,"error: memory block out of range\n\0");break;
  case 58: sprintf(msgBuf,"error: discrepancy for virt.function pointers\n\0");break;
  case 59: sprintf(msgBuf,"error: number of key entries different\n\0");break;
  case 60: sprintf(msgBuf,"error: multiple calls to ZZ_BLOCK_ALLOC(), bits>0\n\0");break;
  case 61: sprintf(msgBuf,"blasting limited to sizeof(char *)==sizeof(ZZint)\n\0");break;
  case 62: sprintf(msgBuf,"ZZinternal error: cannot handle this size of pointer ");break;
  case 63: sprintf(msgBuf,"ZZinternal error: sweap stack allocation\n");break;
  case 64: sprintf(msgBuf,"input for zzprep too large, use ZZbreakLine\n\0");break;
  case 65: sprintf(msgBuf,"mode error: userIO functions not provided\n\0");break;
  case 66: sprintf(msgBuf,"error: virtual array, object larger than the page limit\n\0");break;
  case 67: sprintf(msgBuf,"error in DIRECT_GRAPH set(), read documentation\n\0");break;
  case 68: sprintf(msgBuf,"error: NULL parameter in app() \n\0");break;
  case 69: sprintf(msgBuf,"warning: NULL array in delArr(),sweap.c \n\0");break;
  case 70: sprintf(msgBuf,"blkAlloc() error: both parameters are NULL\n\0");break;
  case 71: sprintf(msgBuf,"Error: x in blkAlloc(..,x) is too small\n\0");break;
  case 72: sprintf(msgBuf,"WARNING: The page size was adjusted to 256B\n\0");break;
  case 73: sprintf(msgBuf,"ERROR: ZZblastOpen() cannot allocate new page or bitmap\n\0"); break;
  case 74: sprintf(msgBuf,"ERROR in algorithm of ZZgrowArrays() \n\0"); break;
  case 75: sprintf(msgBuf,"failed to allocate internal record of classes \n\0"); break;
  case 76: sprintf(msgBuf,"failed to allocate internal lists of virt.pointers\n\0"); break;
  case 77: sprintf(msgBuf,"failure of processing virt.pointers\n\0"); break;
  case 78: sprintf(msgBuf,"option discontinued, use memory blasting with 1 large page\n\0"); break;
  default: sprintf(msgBuf,"strange error detected, code=%I64\n\0",i); break;
}
sprintf(codeBuf,"%I64\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgS(ZZint i,const char *p) {
#else
void ZZmsgS(i,p) ZZint i; char *p; {
#endif
switch(i){
  case 0: sprintf(msgBuf,"problem to open file: %s\n\0",p); break;
  case 1: sprintf(msgBuf,"allocation problem for: %s\n\0",p); break;
  case 2: sprintf(msgBuf,"cannot read file: %s\n\0",p); break;
  case 4: sprintf(msgBuf,"warning: %s in your code but not expanded\n\0",p); break;
  case 5: sprintf(msgBuf,"error: %s needed, but not in your code\n\0",p); break;
  case 6: sprintf(msgBuf,"line:%s - macro syntax error\n\0",p); break;
  case 7: sprintf(msgBuf,"name allocation problem in %s\n\0",p); break;
  case 8: sprintf(msgBuf,"probably error in the format of file %s\n\0",p); break;
  case 9: sprintf(msgBuf,"organization=%s\n\0",p); break;
  case 10: sprintf(msgBuf,"organizations=%s have different pointers\n\0",p); break;
  case 11: sprintf(msgBuf,"ZZinternal error in %s\n\0",p); break;
  case 12: sprintf(msgBuf,"incomplete match for function=%s\n\0",p); break;
  case 13: sprintf(msgBuf,"illegal property type=%s,\n\0",p); break;
  case 14: sprintf(msgBuf,"warning: non-unique use of property named=%s\n\0",p); break;
  case 15: sprintf(msgBuf,"selfID ZZinternal conflict when initializing %s\n\0",p); break;
  case 16: sprintf(msgBuf,"unused entry - message %s\n\0",p); break;
  case 17: sprintf(msgBuf,"error in recovering selfID for %s\n\0",p); break;
  case 18: sprintf(msgBuf,"old %s not in the new organization\n\0",p); break;
  case 19: sprintf(msgBuf,"wrong file access mode=%s\n\0",p);  break;
  case 20: sprintf(msgBuf,"problem to create file %s\n\0",p); break;
  case 21: sprintf(msgBuf,"error in type for the key entry in SAVE: %s\n\0",p); break;
  case 22: sprintf(msgBuf,"structure %s not available for selfID\n\0",p); break;
  case 23: sprintf(msgBuf,"error: forming %s before freeing it\n\0",p); break;
  case 24: sprintf(msgBuf,"error: stack %s not formed before using it\n\0",p); break;
  case 25: sprintf(msgBuf,"error: %s not formed before using the heap\n\0",p); break;
  case 26: sprintf(msgBuf,"error: forming %s before freeing it\n\0",p); break;
  case 27: sprintf(msgBuf,"error: cannot add to %s, not formed or missing header\n\0",p);
                                                                         break;
  case 28: sprintf(msgBuf,"error: %s selected, but not in the original set\n\0",p); break;
  case 29: sprintf(msgBuf,"ZZinternal error in bind.c: ptr type=%c\n\0",p[0]);break;
  case 30: sprintf(msgBuf,"line:%s multiple definition of the FORMAT\n\0",p); break;
  case 31: sprintf(msgBuf,"wrong type=%s when calling ZZbindObj()\n\0",p); break;
  case 33: sprintf(msgBuf,"cannot merge/split for %s, wrong object given\n\0",p); break;
#ifdef LARGE_POINTER
  case 34: sprintf(msgBuf,"%s%I46u%s\0",
#else
  case 34: sprintf(msgBuf,"%s%u%s\0",
#endif
  "warning: cannot allocate block size=",p,
  "         run continues, using the normal allocation\n");break;
  case 35: sprintf(msgBuf,"%s%s\n%s\0",
    "error in ZZ_OPEN when reading type=",p,
    "  for different memory models, use ASCII format\n"); break;
  case 36: sprintf(msgBuf,"error: pager file=%s already open\n\0",p); break;
  case 37: sprintf(msgBuf,"error for pager request file=%s: not enough memory\n\0",p);
                                                                       break;
  case 38: sprintf(msgBuf,"pager error: file=%s failed loading a page\n\0",p); break;
  case 39: sprintf(msgBuf,"pager warning: file=%s not initialized, not enough memory\n\0",
                                                                   p); break;
  case 40: sprintf(msgBuf,"error: attempt to close file=%s, is not open\n\0",p);break;
  case 41: sprintf(msgBuf,"error: cannot activate %s over the current block\n\0",p);break;
  case 42: sprintf(msgBuf,"error: cannot activate %s, not on passive list \n\0",p);break;
  case 43: sprintf(msgBuf,"error: %s already on the passive list \n\0",p);break;
  case 44: sprintf(msgBuf,"error: cannot insert ZZinto empty collection %s\n\0",p);break;
  case 46: sprintf(msgBuf,"error: using hash table=%s before it is formed\n\0",p);break;
  case 50: sprintf(msgBuf,"error: missing end of %s\n\0",p);break;
  case 51: sprintf(msgBuf,"error: unable to allocate 2 internal tables size=%u\n\0",p);break;
  case 52: sprintf(msgBuf,"error in binary disk read for <%s>\n\0",p); break;
  case 53: sprintf(msgBuf,"error in binary disk write for <%s>\n\0",p); break;
  case 54: sprintf(msgBuf,"internal error, type=%s is too long\n\0",p); break;
  default: sprintf(msgBuf,"strange error detected, code=S%I64/%s\n\0",i,p); break;
}
sprintf(codeBuf,"S%I64\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgD(ZZint i,ZZint k) {
#else
void ZZmsgD(i,k) ZZint i,k; {
#endif
switch(i){
  case 0: sprintf(msgBuf,"%I64 errors when creating organizations\n\0",k); break;
  case 1: sprintf(msgBuf,"allocation error for nPar=%I64\n\0",k); break;
  case 2: sprintf(msgBuf,"problem to allocate in ZZmix() n=%I64\n\0",k); break;
  case 3: sprintf(msgBuf,"ZZinternal error, tab=%I64\n\0",k); break;
  case 4: sprintf(msgBuf,"%I64 = wrong reference\n\0",k); break;
  case 5: sprintf(msgBuf,"error when dumping block type %I64\n\0",k); break;
  case 6: sprintf(msgBuf,"alloc.failure when setting property level=%I64\n\0",k); break;
  case 7: sprintf(msgBuf,"array error - negative index %I64\n\0",k); break;
  case 8: sprintf(msgBuf,"unable to allocate array, index=%I64\n\0",k); break;
  case 9: sprintf(msgBuf,"ZZinternal error code=%I64 in ZZmemory()\n\0",k); break;
  case 10: sprintf(msgBuf,"ZZinternal error: %I64 strange code type\n\0",k); break;
  case 11: sprintf(msgBuf,"%I64 errors in binding\n\0",k); break;
  case 12: sprintf(msgBuf,"error %I64: wrong beginning of the binary file\n\0",k); break;
  case 13: sprintf(msgBuf,"error %I64: wrong records on the bind file\n\0",k); break;
  case 15: sprintf(msgBuf,"allocation problem bs.size=%I64 in readBind()\n\0",k); break;
  case 16: sprintf(msgBuf,"allocation problem tempConv=%I64 in readBind()\n\0",k); break;
  case 17: sprintf(msgBuf,"error: %I64 wrong structure index in readBind()\n\0",k); break;
  case 18: sprintf(msgBuf,"%I64 errors when setting up the sweap list\n\0",k); break;
  case 19: sprintf(msgBuf,"unable to increase the sweap table to size=%I64\n\0",k); break;
  case 20: sprintf(msgBuf,"ZZinternal error, type=%I64 out of range in ZZmemory()\n\0",k);
                                                                        break;
  case 21: sprintf(msgBuf,"it does not make sense to form array size=%I64\n\0",k); break;
  case 22: sprintf(msgBuf,"%I64 ZZinternal errors in converting the key entries\n\0",k);break;
  case 23: sprintf(msgBuf,"         old offset=%I64 not found\n\0",k);break;
  case 24: sprintf(msgBuf,"warning: %I64 bytes big block & pool too big to allocate\n\0",k);
                                                                         break;
  case 25: sprintf(msgBuf,"%s%I64%s\0",
     "warning: cannot allocate %I64 bytes for big block data",k,
     "\n         changing to the regular allocation scheme\n");break;
  case 26: sprintf(msgBuf,"error: closing file pointer/handle=%I64, not open\n\0",k);break;
  case 27: sprintf(msgBuf,"ZZinternal error: wrong type=%I64 in ZZvSet()\n\0",k);break;
  case 28: sprintf(msgBuf,"allocating ZZinternal space of %u bytes\n\0",k);break;
  case 29: sprintf(msgBuf,"ZZbreakLine segment estimate=%u bytes\n\0",k);break;
  case 30: sprintf(msgBuf,"warning: pager reduced to %I64 pages\n\0",k);break;
  case 31: sprintf(msgBuf,"warning: entering save() error=%o\n\0",k);break;
  case 32: sprintf(msgBuf,"warning: entering open() error=%o\n\0",k);break;
  case 33: sprintf(msgBuf,"error: bits=%d is too big\n\0",k);break;
  default: sprintf(msgBuf,"strange error detected, code=D%I64/%I64\n\0",i,k); break;
}
sprintf(codeBuf,"D%I64\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgC(ZZint i,const char *c) {
#else
void ZZmsgC(i,c) ZZint i; char *c; {
#endif
switch(i){
  case 0: sprintf(msgBuf,"file zzmaster: wrong pointer type=%c\n\0",*c); break;
  case 1: sprintf(msgBuf,"wrong property type=%c\n\0",*c); break;
  default: sprintf(msgBuf,"strange error detected, code=C%I64/%c\n\0",i,*c); break;
}
sprintf(codeBuf,"C%I64\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgSS(ZZint i,const char *p1,const char *p2) {
#else
void ZZmsgSS(i,p1,p2) ZZint i; char *p1,*p2; {
#endif
switch(i){
  case 0: sprintf(msgBuf,"line:%s strange id=%s\n\0",p1,p2); break;
  case 1: sprintf(msgBuf,"line:%s %s multiply declared\n\0",p1,p2); break;
  case 2: sprintf(msgBuf,"line:%s error: illegal ZZ reference=%s\n\0",p1,p2); break;
  case 3: sprintf(msgBuf,"line: %s wrong id=%s\n\0",p1,p2); break;
  case 4: sprintf(msgBuf,"problem to set pointer=%s for structure=%s\n\0",p1,p2); break;
  case 5: sprintf(msgBuf,"warning: multiple definition %s %s\n\0",p1,p2); break;
  case 6: sprintf(msgBuf,"line %s: warning, %s not declared\n\0",p1,p2); break;
  case 7: sprintf(msgBuf,"Hierarchy error in zzmaster: %s %s\n\0",p1,p2); break;
  case 8: sprintf(msgBuf,"error in %s: cannot write to %s\n\0",p1,p2); break;
  case 10: sprintf(msgBuf,"%s%s%s%s%s%s\0",
      "error: name not initialized when setting new name=",p2,
      "   or: name=",p1," must be deleted, before adding new name=",p2);
                                                        break;
  case 11: sprintf(msgBuf,"... when freeing %s on %s\n\0",p1,p2); break;
  case 12: sprintf(msgBuf,"...error in array %s of objects %s\n\0",p1,p2); break;
#ifdef LARGE_POINTER
  case 13: sprintf(msgBuf,"error in %s, ZZ_SET called for wrong child=%I46u\n\0",
                                                     p1,(ZZlong)(p2)); break;
  case 14: sprintf(msgBuf,"cannot add to %s, object=%I46u not disconnected\n\0",
                                                     p1,(ZZlong)(p2)); break;
#else
  case 13: sprintf(msgBuf,"error in %s, ZZ_SET called for wrong child=%I64\n\0",
                                                     p1,(ZZint)(p2)); break;
  case 14: sprintf(msgBuf,"cannot add to %s, object=%I64 not disconnected\n\0",
                                                     p1,(ZZint)(p2)); break;
#endif
  case 15: sprintf(msgBuf,"line:%s FORMAT for object=%s used before ZZ_EXT \n\0",p1,p2);
                                                                         break;
  case 16: sprintf(msgBuf,"line:%s inheritance of %s, syntax not acceptable\n\0",p1,p2);
                                                                         break;
  case 17: sprintf(msgBuf,"ZZinternal offset discrepancy for %s inside %s:\n\0",p1,p2);
                                                                         break;
#ifdef LARGE_POINTER
  case 18: sprintf(msgBuf,"error for %s: cannot add %I46u, relation already exists\n\0",
                                                      p1,(ZZlong)(p2)); break;
  case 19: sprintf(msgBuf,"cannot add to %s, relation %I46u not disconnected\n\0",
                                                      p1,(ZZlong)(p2)); break;
  case 20: sprintf(msgBuf,"%s%I64u%s%s\0",
      "warning: big block of ",
      (unsigned ZZlong)(p2) - (unsigned ZZlong)(p1),
      " bytes exhausted\n",
      "         changing to the regular allocation scheme\n");break;
  case 21: sprintf(msgBuf,"reading a block of %I46u bytes from disk ...\n\0",
                             (unsigned ZZlong)(p2) - (unsigned ZZlong)(p1)); break;
  case 22: sprintf(msgBuf,"error in generic function=%s organization=%s\n\0",p1,p2);break;
  case 23: sprintf(msgBuf,"cannot add to %s, object %I46u not disconnected\n\0",
                                                 p1,(unsigned ZZlong)(p2)); break;
  case 24: sprintf(msgBuf,"cannot insert %s, object %I46u not disconnected\n\0",
                                                 p1,(unsigned ZZlong)(p2)); break;
  case 25: sprintf(msgBuf,"cannot append %s, object %I46u not disconnected\n\0",
                                                 p1,(unsigned ZZlong)(p2)); break;
  case 26: sprintf(msgBuf,"cannot append to the root of %s, object=%I46u\n\0",
                                                 p1,(unsigned ZZlong)(p2)); break;
  case 27: sprintf(msgBuf,"cannot insert to the root of %s, object=%I46u\n\0",
                                                 p1,(unsigned ZZlong)(p2)); break;
  case 28: sprintf(msgBuf,"error: %I46u blast memory overflow, blastSize=%I46u\n\0",
                                 (unsigned ZZlong)p1,(unsigned ZZlong)p2); break;
  case 29: sprintf(msgBuf,"error: cannot allocate %I46u bytes, page=%I46u\n\0",p1,p2); break;
  case 30: sprintf(msgBuf,"error: cannot add object=%I46u, hash table=%s\n\0",p1,p2);break;
  case 31: sprintf(msgBuf,"error: virt.array size=%I46 index=%I46\n\0",p1,p2);break;
  case 32: sprintf(msgBuf,
       "error del(): object=%I46u in %s, not found in bucket\n\0",p1,p2);break;
  case 33: sprintf(msgBuf,
       "error del(): object=%I46u in %s, bucket is empty\n\0",p1,p2);break;
  case 34: sprintf(msgBuf,"cannot add to %s, parent %I46u not disconnected\n\0",
                                                 p1,(unsigned ZZlong)(p2)); break;
  case 35: sprintf(msgBuf,"cannot add to %s, child %I46u not disconnected\n\0",
                                                 p1,(unsigned ZZlong)(p2)); break;
  case 36: sprintf(msgBuf,
      "warning del(): object=%I64u in %s, not in any hash table\n\0",p1,p2);break;
  case 37: sprintf(msgBuf,"allocation error: object size=%u > page size=%u\n\0", p1,p2); break;
  case 38: sprintf(msgBuf,"ERROR in ZZgrowArrays() pageNo=%I46u bigger than iMax=%I46u\n\0",p1,p2); break;
#else
  case 18: sprintf(msgBuf,"error for %s: cannot add %I64, relation already exists\n\0",
                                                      p1,(ZZint)(p2)); break;
  case 19: sprintf(msgBuf,"cannot add to %s, relation %I64 not disconnected\n\0",
                                                      p1,(ZZint)(p2)); break;
  case 20: sprintf(msgBuf,"%s%I64%s%s\0",
      "warning: big block of ",
      (unsigned ZZint)(p2) - (unsigned ZZint)(p1),
      " bytes exhausted\n",
      "         changing to the regular allocation scheme\n");break;
  case 22: sprintf(msgBuf,"error in generic function=%s organization=%s\n\0",p1,p2);break;
  case 23: sprintf(msgBuf,"cannot add to %s, object %I64 not disconnected\n\0",
                                                 p1,(unsigned ZZint)(p2)); break;
  case 24: sprintf(msgBuf,"cannot insert %s, object %I64 not disconnected\n\0",
                                                 p1,(unsigned ZZint)(p2)); break;
  case 25: sprintf(msgBuf,"cannot append %s, object %I64 not disconnected\n\0",
                                                 p1,(unsigned ZZint)(p2)); break;
  case 26: sprintf(msgBuf,"cannot append to the root of %s, object=%I64\n\0",
                                                 p1,(unsigned ZZint)(p2)); break;
  case 27: sprintf(msgBuf,"cannot insert to the root of %s, object=%I64\n\0",
                                                 p1,(unsigned ZZint)(p2)); break;
  case 28: sprintf(msgBuf,"error: %u blast memory overflow, blastSize=%u\n\0",
                                 (unsigned ZZint)p1,(unsigned ZZint)p2); break;
  case 29: sprintf(msgBuf,"error: cannot allocate %u bytes, page=%u\n\0",p1,p2); break;
  case 30: sprintf(msgBuf,"error: cannot add object=%u, hash table=%s\n\0",p1,p2);break;
  case 31: sprintf(msgBuf,"error: virt.array size=%I46 index=%I46\n\0",p1,p2);break;
  case 32: sprintf(msgBuf,
       "error del(): object=%u in hash=%s, not in bucket\n\0",p1,p2);break;
  case 33: sprintf(msgBuf,
       "error del(): object=%u in hash=%s, bucket is empty\n\0",p1,p2);break;
  case 34: sprintf(msgBuf,"cannot add to %s, parent %I64 not disconnected\n\0",
                                                 p1,(unsigned ZZint)(p2)); break;
  case 35: sprintf(msgBuf,"cannot add to %s, child %I64 not disconnected\n\0",
                                                 p1,(unsigned ZZint)(p2)); break;
  case 36: sprintf(msgBuf,
      "warning del(): object=%I64 in %s, not in any hash table\n\0",p1,p2);break;
  case 37: sprintf(msgBuf,"allocation error: object size=%u > page size=%u\n\0", p1,p2); break;
  case 38: sprintf(msgBuf,"ERROR in ZZgrowArrays() pageNo=%u bigger than iMax=%u\n\o",p1,p2); break;
#endif
  default: sprintf(msgBuf,"strange error detected, code=SS%I64/%s/%s\n\0",i,p1,p2); break;
}
sprintf(codeBuf,"SS%I64\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgDD(ZZint i,ZZint k1,ZZint k2) {
#else
void ZZmsgDD(i,k1,k2) ZZint i,k1,k2; {
#endif
switch(i){
  case 0: sprintf(msgBuf,"%s%I64%s%I64%s\0",
    "ZZinternal counting error in parser k=",k1," n=",k2,
    "\nprobably, your program is too ZZlong\n"); break;
  case 1: sprintf(msgBuf,"array size=%I64 index=%I64 out of range\n\0",k1,k2); break;
  case 4: /* unused entry */ break;
  case 5: sprintf(msgBuf,"wrong ZZinternal setting, ZZnTbType=%I64 ZZpTbType=%I64\n\0",k1,k2);
                                                                        break;
  case 6: sprintf(msgBuf,"warning: pool=%I64, needed=%I64, new block created\n\0",k1,k2);
                                                                        break;
  case 7: sprintf(msgBuf,"error: wrong nesting of {} between lines=%I64,%I64, giving up\n\0",
                                                                 k1,k2); break;
  case 8: sprintf(msgBuf,"internal error blast.c, ZZgrowArrays(), i=%d newHigh=%d\n",
                                                                 k1,k2); break;
  default: sprintf(msgBuf,"strange error detected, code=DD%I64/%I64/%I64\n\0",i,k1,k2); break;
}
sprintf(codeBuf,"DD%I64\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgSD(ZZint i,const char *p,ZZint k) {
#else
void ZZmsgSD(i,p,k) ZZint i,k; char *p; {
#endif
switch(i){
  case 0: sprintf(msgBuf,"ZZinternal overflow %s=%I64\n\0",p,k); break;
  case 1: sprintf(msgBuf,"zzprep BUFSIZE=%I64 insufficient to expand:%s\n\0",k,p); break;
  case 2: sprintf(msgBuf,"zzmaster part=%s index=%I64 out of sequence\n\0",p,k); break;
  case 3: sprintf(msgBuf,"cannot free object=%s, pointer No.%I64 not disconnected\n\0",p,k);
                                                                     break;
#ifdef LARGE_POINTER
  case 4: sprintf(msgBuf,"--- suspicious behaviour, ZZmarkPtr given ptr=%I46u\n\0",p);
#else
  case 4: sprintf(msgBuf,"--- SUSPICIOUS BEHAVIOUR: ZZmarkPtr() given ptr=%u\n\0",p);
#endif
          sprintf(msgBuf,"    not in the allocated area, case %d\n\0",k); break;
#ifdef LARGE_POINTER
  case 12: sprintf(msgBuf,"error1 in ASCII format when readBind(), type=%I64 ptr=%I46u\n\0",
                                                          k,(ZZlong)p); break;
#else
  case 12: sprintf(msgBuf,"error1 in ASCII format when readBind(), type=%I64 ptr=%I64\n\0",
                                                          k,(ZZint)p); break;
#endif
  case 13: sprintf(msgBuf,"error: cannot allocate %I64 Bytes in %s\n\0",k,p);break;
  case 14: sprintf(msgBuf,"error: %s %I64\n\0",p,k);break;
  case 15: sprintf(msgBuf,"unable to allocate sweap table for %I46 objects, %I64 entries\n\0",
           i,*((ZZlong *)p),k); break;
#ifdef LARGE_POINTER
  case 16: sprintf(msgBuf,"ZZinternal error, strategy=%I64 cannot convert=%I46u\n\0",
#else
  case 16: sprintf(msgBuf,"ZZinternal error, strategy=%I64 cannot convert=%I64\n\0",
#endif
           k,p); break;
  case 17: sprintf(msgBuf,"error2 in ASCII format when readBind(), type=%I64 ptr=%I46u\n\0",
                                                          k,(ZZlong)p); break;
  default: sprintf(msgBuf,"strange error detected, code=SD%I64/%s/%I64\n\0",i,p,k); break;
}
sprintf(codeBuf,"SD%I64\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgSSS(ZZint i,const char *p1,const char *p2,const char *p3) {
#else
void ZZmsgSSS(i,p1,p2,p3) ZZint i; char *p1,*p2,*p3; {
#endif
switch(i){
  case 0: sprintf(msgBuf,"line:%s generic=%s expanded=%s not found\n\0",p1,p2,p3); break;
  case 1: sprintf(msgBuf,"line:%s function=%s organization=%s do not match\n\0",p1,p2,p3);
                                                                          break;
  case 4: sprintf(msgBuf,"%30s %12s  file: %s\n\0",p1,p2,p3); break;
#ifdef LARGE_POINTER
  case 5: sprintf(msgBuf,"%s%I46u%s%s%I46u%s%I46u\n\0",
    "WARNING: ZZ_OPEN() reading block of %I46u bytes\n",p1,
    "         existing pool=",p2,
    ", new block created, new pool=",p2); break;
  case 6: sprintf(msgBuf,"Error: New page index=%I46u is over %I46u\n\0",p1,p2);
          sprintf(msgBuf,"   which was derived from blkAlloc(x,...).\n\0");
          sprintf(msgBuf,"   Increase x over %I46u\n\0",p3); break;
  case 7: sprintf(msgBuf,
          "Internal algorithm failure, two page addresses %I46u,%I46u ", p1,p2);
          sprintf(msgBuf,"for the same page index=%I46u\n\0",p3); break;
#else
  case 5: sprintf(msgBuf,"WARNING: ZZ_OPEN() reading block of %u bytes\n\0",p1);
          sprintf(msgBuf,"         existing pool=%u, new block created, new pool=%u\n\0"
                                                              ,p2,p3); break;
  case 6: sprintf(msgBuf,"Error: New page index=%u is over %u\n\0",p1,p2);
          sprintf(msgBuf,"   which was derived from blkAlloc(x,...).\n\0");
          sprintf(msgBuf,"   Increase x over %u\n\0",p3); break;
  case 7: sprintf(msgBuf,"Internal algorithm failure, two page addresse %u,%u",p1,p2;
          sprintf(msgBuf,"for the same page index=%u\n\0",p3); break;
#endif
  case 8: sprintf(msgBuf, "line: %s error: illegal ZZ reference=%s\n\0", p1, p2, p3);break;
  default: sprintf(msgBuf,"strange error detected, code=SSS%I64/%s/%s/%s\n\0",i,p1,p2,p3);
                                                                       break;
}
sprintf(codeBuf,"SSS%I64\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgDDD(ZZint i,ZZint k1,ZZint k2,ZZint k3) {
#else
void ZZmsgDDD(i,k1,k2,k3) ZZint i,k1,k2,k3; {
#endif
switch(i){
  case 1: sprintf(msgBuf,"problem to fit oldType=%I64 offset=%I64 ZZinto newType=%I64\n\0",k1,k2,k3); 
          break;
  default: sprintf(msgBuf,"strange error detected, code=DDD%I64/%I64/%I64/%I64\n\0",i,k1,k2,k3);
          break;
}
sprintf(codeBuf,"DDD%I64\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgSDD(ZZint i,const char *p,ZZint k1,ZZint k2) {
#else
void ZZmsgSDD(i,p,k1,k2) char *p; ZZint i,k1,k2; {
#endif
switch(i){
  case 0:
    sprintf(msgBuf,"cannot free array, element %s[%I64] pointer No=%I64 not disconnected\n\0",
                                                 p,k1,k2); break;
  default: sprintf(msgBuf,"strange error detected, code=SDD%I64/%s/%I64/%I64\n\0",i,p,k1,k2);
                                                                       break;
}
sprintf(codeBuf,"SDD%I64\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgSSD(ZZint i,const char *p1,const char *p2,ZZint k) {
#else
void ZZmsgSSD(i,p1,p2,k) char *p1,*p2; ZZint i,k; {
#endif
switch(i){
#ifdef LARGE_POINTER
  case 0: sprintf(msgBuf,"error in binding, type=%s, ptr offset=%I64, old ptr=%I46u\n\0",
#else
  case 0: sprintf(msgBuf,"error in binding, type=%s, ptr offset=%I64, old ptr=%I64u\n\0",
#endif
                                                             p1,k,p2); break;
#ifdef LARGE_POINTER
  default: sprintf(msgBuf,"strange error detected, code=SSD%I64/%s/%I46u/%I64\n\0",
#else
  default: sprintf(msgBuf,"strange error detected, code=SSD%I64/%s/%I64u/%I64\n\0",
#endif
                                                           i,p1,p2,k); break;
}
sprintf(codeBuf,"SDD%I64\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgSSDD(ZZint i,const char *p1,const char *p2,ZZint k1,ZZint k2) {
#else
void ZZmsgSSDD(i,p1,p2,k1,k2) ZZint i; char *p1,*p2; ZZint k1,k2; {
#endif
switch(i){
  case 0: sprintf(msgBuf,"         type=%s changed to %s, size=%I64 changed to %I64\n\0",
                                       p1,p2,k1,k2); break;
  case 1: sprintf(msgBuf,"%s%s%s%s%s%I64%s%I64\n\0",
    "ZZinternal error for ",p1," inside ",p2,
    "\n     type offset=",k1,", address offset=",k2); break;
  default: sprintf(msgBuf,"strange error detected, code=SSDD%I64/%s/%s/%I64/%I64\n\0",
                                                    i,p1,p2,k1,k2); break;
}
sprintf(codeBuf,"SSDD%I64\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgSDDD(ZZint i,const char *p,ZZint k1,ZZint k2,ZZint k3) {
#else
void ZZmsgSDDD(i,p,k1,k2,k3) char *p; ZZint k1,k2,k3; {
#endif
switch(i){
  case 0: sprintf(msgBuf,"error for %s, start=%I64 numPtr=%I64 selfIndex=%I64\n\0",p,k1,k2,k3);
                                                                         break;
  case 1: sprintf(msgBuf,"ZZinternal index problem for %s j1=%I64 j2=%I64 ns=%I64\n\0",p,k1,k2,k3);
                                                                        break;
  default: sprintf(msgBuf,"strange error detected, code=SDDD%I64/%s/%I64/%I64/%I64\n\0",
                                                          i,p,k1,k2,k3); break;
}
sprintf(codeBuf,"SDDD%I64\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgSL(ZZint i,const char *p,ZZlong k) {
#else
void ZZmsgSL(i,p,k) ZZint i; char *p; ZZlong k; {
#endif

switch(i){
  case 0: sprintf(msgBuf,"error in: %s, cannot convert long=%I64u ZZinto ZZinteger\n\0",p,k);
  default: sprintf(msgBuf,"strange error detected, code=SL%I64/%s/%I64u\n\0",i,p,k); break;
}
sprintf(codeBuf,"SL%I64\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}

/* ---------------------------------------------------------------- */
#ifndef ZZlocal
#ifndef ZZcallBack

/* Special function which converts the 'errCode' string ZZinto a long code
 * Resulting format: XXX0YY where X represents the message type, and Y
 * the ZZinternal message number. The X conversion is:
 * S=1, D=2, L=3, C=4
 * In case of ZZinternal error (errCode cannot be decoded), returns 999999
 */
static ZZlong errorCodeConvert(char *errCode){
 static char c[]={'S','D','L','C','0','1','2','3','4','5','6','7','8','9','E'};
 static ZZint  i[]={ 1 , 2 , 3 , 4 , 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , -1};
 static ZZint num=4; /* number of leading letters in c[] */
    ZZint k,lastK;
    ZZlong r=0;
    char *p;
    for(p=errCode, k=lastK=0; *p!='\0'; p++, lastK=k){
        for(k=0; c[k]!='E'; k++){
            if(*p==c[k])break;
        }
        if(i[k]<0){r=999999; break;}
        if(lastK<num && k>=num)r=r*100; else r=r*10;
        r=r+i[k];
    }
    return r;
}

#ifdef ZZ_ANSI
static void zzReportError(ZZint errVal, char *errCode, char *errMsg)
#else
static void zzReportError(errVal,errCode,errMsg)
ZZint errVal;    /* value of ZZerror, binary encoded */
char *errCode; /* code for lookup in msgs.c */
char *errMsg;  /* error msg normally prZZinted on stdout */
#endif
{
#ifdef SPECIAL_OPTION
    ZZlong code,errorCodeConvert(char *);
    code=errorCodeConvert(errCode);
    printf("errLevel=%I64 errCode=%I46d: %s",errVal,code,errMsg); 
#else // SPECIAL_OPTION
    printf("errLevel=%I64 errCode=%s: %s",errVal,errCode,errMsg); 
#endif // SPECIAL_OPTION
}
#endif /* ZZlocal */
#endif /* ZZcallBack */
/* ---------------------------------------------------------------- */


#else // Windows64 ====================================================

/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsg(ZZint i) {
#else
void ZZmsg(i) ZZint i; {
#endif
switch(i){
  case 0: sprintf(msgBuf,"ZZinternal error, cannot find selfID organization\n\0"); break;
  case 1: sprintf(msgBuf,
                "WARNING: ZZ_INHERIT present, util.clear() does nothing\n\0"); break;
  case 4: sprintf(msgBuf,"problem with ZZinternal file in getMaster()\n\0");break;
  case 5: sprintf(msgBuf,"cannot run, empty master table\n\0"); break;
  case 6: sprintf(msgBuf,"problem to allocate master tables\n\0"); break;
  case 7: sprintf(msgBuf,"problem to allocate ZZhierarchy definition\n\0"); break;
  case 8: sprintf(msgBuf,"master table error - from organization to its pointers\n\0");
                                                                         break;
  case 9: sprintf(msgBuf,"master table error - from function to its support\n\0"); break;
  case 10: sprintf(msgBuf,"master table error - next in ZZsupport\n\0"); break;
  case 13: sprintf(msgBuf,"problem to open file /dev/idmodule\n\0"); break;
  case 14: sprintf(msgBuf,"problem to read ID module code\n\0"); break;
  case 15: sprintf(msgBuf,"problem: not legitimate ID module code\n\0"); break;
  case 16: sprintf(msgBuf,"correct syntax: zzhelp something\n\0"); break;
  case 17: sprintf(msgBuf,"argument too long\n\0"); break;
  case 18: sprintf(msgBuf,"file macro/zzmaster is missing\n\0"); break;
  case 19: sprintf(msgBuf,"nothing meaningful found\n\0"); break;
  case 20: sprintf(msgBuf,"cannot open file zztemp or zzinfo\n\0"); break;
  case 21: sprintf(msgBuf,"select numbers: \0"); break;
  case 22: sprintf(msgBuf,"view file zzinfo ...\n\0"); break;
  case 23: sprintf(msgBuf,"Best match found:\n\0"); break;
  case 24: sprintf(msgBuf,"function    :\0"); break;
  case 25: sprintf(msgBuf,"gen.function:\0"); break;
  case 26: sprintf(msgBuf,"gen.macro   :\0"); break;
  case 27: sprintf(msgBuf,"macro       :\0"); break;
  case 32: sprintf(msgBuf,"syntax: zzmerge <inp1> <inp2> <out>\n\0"); break;
  case 33: sprintf(msgBuf,"error when dumping property header\n\0"); break;
  case 34: sprintf(msgBuf,"ZZinternal problems, ZZpropDelete() - empty chain\n\0"); break;
  case 35: sprintf(msgBuf,"ZZinternal inconsistency in ZZpropDelete() - problems\n\0");
                                                                        break;
  case 36: sprintf(msgBuf,"install.error: larger size needed for ZZproperty.cProp\n\0");
                                                                        break;
  case 37: sprintf(msgBuf,"error: attempt to access array without forming it first\n\0");
                                                                        break;
  case 38: sprintf(msgBuf,"error: cannot reset hash table without forming it first\n\0");
                                                                        break;
  case 39: sprintf(msgBuf,"unable to allocate a new hash table, old one remains\n\0");
                                                                        break;
  case 40: sprintf(msgBuf,"ZZinternal problem to allocate small array in ZZmemory()\n\0");
                                                                        break;
  case 41: sprintf(msgBuf,"error: short beginning of the ASCII file\n\0"); break;
  case 42: sprintf(msgBuf,"number of organizations decreased\n\0"); break;
  case 44: sprintf(msgBuf,"error in binary format when readBind()\n\0"); break;
  case 45: sprintf(msgBuf,"error in binary disk read\n\0"); break;
  case 46: sprintf(msgBuf,"problem to close file\n\0"); break;
  case 47: sprintf(msgBuf,"ZZinternal algorithm error in DELETE_SINGLE_GRAPH\n\0"); break;
  case 48: sprintf(msgBuf,"syntax: zzselect <inp1> <inp2> <out>\n\0"); break;
  case 50: sprintf(msgBuf,"unexpected size of (char *), for 64bits Windows check lib/envmsft.h\n\0"); break;
  case 51: sprintf(msgBuf,"ZZinternal error: unable to convert (char *) to ZZint\n\0"); break;
  case 52: sprintf(msgBuf,"not enough memory -\n\0"); break;
  case 53: sprintf(msgBuf,"should never happen: fopen returns -1\n\0"); break;
  case 54: sprintf(msgBuf,"error: OPENNING incompatible data\n\0");break;
  case 55: sprintf(msgBuf,"should never happen: called ZZdelObj(NULL)\n\0"); break;
  case 56: sprintf(msgBuf,"ZZinternal error: there is a header array and mode=0\n\0");break;
  case 57: sprintf(msgBuf,"error: memory block out of range\n\0");break;
  case 59: sprintf(msgBuf,"error: number of key entries different\n\0");break;
  case 60: sprintf(msgBuf,"error: multiple calls to ZZ_BLOCK_ALLOC(), bits>0\n\0");break;
  case 61: sprintf(msgBuf,"blasting limited to sizeof(char *)==sizeof(ZZint)\n\0");break;
  case 62: sprintf(msgBuf,"ZZinternal error: cannot handle this size of pointer ");break;
  case 63: sprintf(msgBuf,"ZZinternal error: sweap stack allocation\n");break;
  case 64: sprintf(msgBuf,"input for zzprep too large, use ZZbreakLine\n\0");break;
  case 65: sprintf(msgBuf,"mode error: userIO functions not provided\n\0");break;
  case 66: sprintf(msgBuf,"error: virtual array, object larger than the page limit\n\0");break;
  case 67: sprintf(msgBuf,"error in DIRECT_GRAPH set(), read documentation\n\0");break;
  case 68: sprintf(msgBuf,"error: NULL parameter in app() \n\0");break;
  case 69: sprintf(msgBuf,"warning: NULL array in delArr(),sweap.c \n\0");break;
  default: sprintf(msgBuf,"strange error detected, code=%d\n\0",i); break;
}
sprintf(codeBuf,"%d\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgS(ZZint i,const char *p) {
#else
void ZZmsgS(i,p) ZZint i; char *p; {
#endif
switch(i){
  case 0: sprintf(msgBuf,"problem to open file: %s\n\0",p); break;
  case 1: sprintf(msgBuf,"allocation problem for: %s\n\0",p); break;
  case 2: sprintf(msgBuf,"cannot read file: %s\n\0",p); break;
  case 4: sprintf(msgBuf,"warning: %s in your code but not expanded\n\0",p); break;
  case 5: sprintf(msgBuf,"error: %s needed, but not in your code\n\0",p); break;
  case 6: sprintf(msgBuf,"line:%s - macro syntax error\n\0",p); break;
  case 7: sprintf(msgBuf,"name allocation problem in %s\n\0",p); break;
  case 8: sprintf(msgBuf,"probably error in the format of file %s\n\0",p); break;
  case 9: sprintf(msgBuf,"organization=%s\n\0",p); break;
  case 10: sprintf(msgBuf,"organizations=%s have different pointers\n\0",p); break;
  case 11: sprintf(msgBuf,"ZZinternal error in %s\n\0",p); break;
  case 12: sprintf(msgBuf,"incomplete match for function=%s\n\0",p); break;
  case 13: sprintf(msgBuf,"illegal property type=%s,\n\0",p); break;
  case 14: sprintf(msgBuf,"warning: non-unique use of property named=%s\n\0",p); break;
  case 15: sprintf(msgBuf,"selfID ZZinternal conflict when initializing %s\n\0",p); break;
  case 16: sprintf(msgBuf,"unused entry - message %s\n\0",p); break;
  case 17: sprintf(msgBuf,"error in recovering selfID for %s\n\0",p); break;
  case 18: sprintf(msgBuf,"old %s not in the new organization\n\0",p); break;
  case 19: sprintf(msgBuf,"wrong file access mode=%s\n\0",p);  break;
  case 20: sprintf(msgBuf,"problem to create file %s\n\0",p); break;
  case 21: sprintf(msgBuf,"error in type for the key entry in SAVE: %s\n\0",p); break;
  case 22: sprintf(msgBuf,"structure %s not available for selfID\n\0",p); break;
  case 23: sprintf(msgBuf,"error: forming %s before freeing it\n\0",p); break;
  case 24: sprintf(msgBuf,"error: stack %s not formed before using it\n\0",p); break;
  case 25: sprintf(msgBuf,"error: %s not formed before using the heap\n\0",p); break;
  case 26: sprintf(msgBuf,"error: forming %s before freeing it\n\0",p); break;
  case 27: sprintf(msgBuf,"error: cannot add to %s, not formed or missing header\n\0",p);
                                                                         break;
  case 28: sprintf(msgBuf,"error: %s selected, but not in the original set\n\0",p); break;
  case 29: sprintf(msgBuf,"ZZinternal error in bind.c: ptr type=%c\n\0",p[0]);break;
  case 30: sprintf(msgBuf,"line:%s multiple definition of the FORMAT\n\0",p); break;
  case 31: sprintf(msgBuf,"wrong type=%s when calling ZZbindObj()\n\0",p); break;
  case 33: sprintf(msgBuf,"cannot merge/split for %s, wrong object given\n\0",p); break;
#ifdef LARGE_POINTER
  case 34: sprintf(msgBuf,"%s%lu%s\0",
#else
  case 34: sprintf(msgBuf,"%s%u%s\0",
#endif
  "warning: cannot allocate block size=",p,
  "         run continues, using the normal allocation\n");break;
  case 35: sprintf(msgBuf,"%s%s\n%s\0",
    "error in ZZ_OPEN when reading type=",p,
    "  for different memory models, use ASCII format\n"); break;
  case 36: sprintf(msgBuf,"error: pager file=%s already open\n\0",p); break;
  case 37: sprintf(msgBuf,"error for pager request file=%s: not enough memory\n\0",p);
                                                                       break;
  case 38: sprintf(msgBuf,"pager error: file=%s failed loading a page\n\0",p); break;
  case 39: sprintf(msgBuf,"pager warning: file=%s not initialized, not enough memory\n\0",
                                                                   p); break;
  case 40: sprintf(msgBuf,"error: attempt to close file=%s, is not open\n\0",p);break;
  case 41: sprintf(msgBuf,"error: cannot activate %s over the current block\n\0",p);break;
  case 42: sprintf(msgBuf,"error: cannot activate %s, not on passive list \n\0",p);break;
  case 43: sprintf(msgBuf,"error: %s already on the passive list \n\0",p);break;
  case 44: sprintf(msgBuf,"error: cannot insert ZZinto empty collection %s\n\0",p);break;
  case 46: sprintf(msgBuf,"error: using hash table=%s before it is formed\n\0",p);break;
  case 50: sprintf(msgBuf,"error: missing end of %s\n\0",p);break;
  default: sprintf(msgBuf,"strange error detected, code=S%d/%s\n\0",i,p); break;
}
sprintf(codeBuf,"S%d\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgD(ZZint i,ZZint k) {
#else
void ZZmsgD(i,k) ZZint i,k; {
#endif
switch(i){
  case 0: sprintf(msgBuf,"%d errors when creating organizations\n\0",k); break;
  case 1: sprintf(msgBuf,"allocation error for nPar=%d\n\0",k); break;
  case 2: sprintf(msgBuf,"problem to allocate in ZZmix() n=%d\n\0",k); break;
  case 3: sprintf(msgBuf,"ZZinternal error, tab=%d\n\0",k); break;
  case 4: sprintf(msgBuf,"%d = wrong reference\n\0",k); break;
  case 5: sprintf(msgBuf,"error when dumping block type %d\n\0",k); break;
  case 6: sprintf(msgBuf,"alloc.failure when setting property level=%d\n\0",k); break;
  case 7: sprintf(msgBuf,"array error - negative index %d\n\0",k); break;
  case 8: sprintf(msgBuf,"unable to allocate array, index=%d\n\0",k); break;
  case 9: sprintf(msgBuf,"ZZinternal error code=%d in ZZmemory()\n\0",k); break;
  case 10: sprintf(msgBuf,"ZZinternal error: %d strange code type\n\0",k); break;
  case 11: sprintf(msgBuf,"%d errors in binding\n\0",k); break;
  case 12: sprintf(msgBuf,"error %d: wrong beginning of the binary file\n\0",k); break;
  case 13: sprintf(msgBuf,"error %d: wrong records on the bind file\n\0",k); break;
  case 15: sprintf(msgBuf,"allocation problem bs.size=%d in readBind()\n\0",k); break;
  case 16: sprintf(msgBuf,"allocation problem tempConv=%d in readBind()\n\0",k); break;
  case 17: sprintf(msgBuf,"error: %d wrong structure index in readBind()\n\0",k); break;
  case 18: sprintf(msgBuf,"%d errors when setting up the sweap list\n\0",k); break;
  case 19: sprintf(msgBuf,"unable to increase the sweap table to size=%d\n\0",k); break;
  case 20: sprintf(msgBuf,"ZZinternal error, type=%d out of range in ZZmemory()\n\0",k);
                                                                        break;
  case 21: sprintf(msgBuf,"it does not make sense to form array size=%d\n\0",k); break;
  case 22: sprintf(msgBuf,"%d ZZinternal errors in converting the key entries\n\0",k);break;
  case 23: sprintf(msgBuf,"         old offset=%d not found\n\0",k);break;
  case 24: sprintf(msgBuf,"warning: %d bytes big block & pool too big to allocate\n\0",k);
                                                                         break;
  case 25: sprintf(msgBuf,"%s%d%s\0",
     "warning: cannot allocate %d bytes for big block data",k,
     "\n         changing to the regular allocation scheme\n");break;
  case 26: sprintf(msgBuf,"error: closing file pointer/handle=%d, not open\n\0",k);break;
  case 27: sprintf(msgBuf,"ZZinternal error: wrong type=%d in ZZvSet()\n\0",k);break;
  case 28: sprintf(msgBuf,"allocating ZZinternal space of %u bytes\n\0",k);break;
  case 29: sprintf(msgBuf,"ZZbreakLine segment estimate=%u bytes\n\0",k);break;
  case 30: sprintf(msgBuf,"warning: pager reduced to %d pages\n\0",k);break;
  case 31: sprintf(msgBuf,"warning: entering save() error=%o\n\0",k);break;
  case 32: sprintf(msgBuf,"warning: entering open() error=%o\n\0",k);break;
  default: sprintf(msgBuf,"strange error detected, code=D%d/%d\n\0",i,k); break;
}
sprintf(codeBuf,"D%d\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgC(ZZint i,const char *c) {
#else
void ZZmsgC(i,c) ZZint i; char *c; {
#endif
switch(i){
  case 0: sprintf(msgBuf,"file zzmaster: wrong pointer type=%c\n\0",*c); break;
  case 1: sprintf(msgBuf,"wrong property type=%c\n\0",*c); break;
  default: sprintf(msgBuf,"strange error detected, code=C%d/%c\n\0",i,*c); break;
}
sprintf(codeBuf,"C%d\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgSS(ZZint i,const char *p1,const char *p2) {
#else
void ZZmsgSS(i,p1,p2) ZZint i; char *p1,*p2; {
#endif
switch(i){
  case 0: sprintf(msgBuf,"line:%s strange id=%s\n\0",p1,p2); break;
  case 1: sprintf(msgBuf,"line:%s %s multiply declared\n\0",p1,p2); break;
  case 2: sprintf(msgBuf,"line:%s error: illegal ZZ reference=%s\n\0",p1,p2); break;
  case 3: sprintf(msgBuf,"line: %s wrong id=%s\n\0",p1,p2); break;
  case 4: sprintf(msgBuf,"problem to set pointer=%s for structure=%s\n\0",p1,p2); break;
  case 5: sprintf(msgBuf,"warning: multiple definition %s %s\n\0",p1,p2); break;
  case 6: sprintf(msgBuf,"line %s: warning, %s not declared\n\0",p1,p2); break;
  case 7: sprintf(msgBuf,"Hierarchy error in zzmaster: %s %s\n\0",p1,p2); break;
  case 8: sprintf(msgBuf,"error in %s: cannot write to %s\n\0",p1,p2); break;
  case 10: sprintf(msgBuf,"%s%s%s%s%s%s\0",
      "error: name not initialized when setting new name=",p2,
      "   or: name=",p1," must be deleted, before adding new name=",p2);
                                                        break;
  case 11: sprintf(msgBuf,"... when freeing %s on %s\n\0",p1,p2); break;
  case 12: sprintf(msgBuf,"...error in array %s of objects %s\n\0",p1,p2); break;
#ifdef LARGE_POINTER
  case 13: sprintf(msgBuf,"error in %s, ZZ_SET called for wrong child=%lu\n\0",
                                                     p1,(ZZlong)(p2)); break;
  case 14: sprintf(msgBuf,"cannot add to %s, object=%lu not disconnected\n\0",
                                                     p1,(ZZlong)(p2)); break;
#else
  case 13: sprintf(msgBuf,"error in %s, ZZ_SET called for wrong child=%d\n\0",
                                                     p1,(ZZint)(p2)); break;
  case 14: sprintf(msgBuf,"cannot add to %s, object=%d not disconnected\n\0",
                                                     p1,(ZZint)(p2)); break;
#endif
  case 15: sprintf(msgBuf,"line:%s FORMAT for object=%s used before ZZ_EXT \n\0",p1,p2);
                                                                         break;
  case 16: sprintf(msgBuf,"line:%s inheritance of %s, syntax not acceptable\n\0",p1,p2);
                                                                         break;
  case 17: sprintf(msgBuf,"ZZinternal offset discrepancy for %s inside %s:\n\0",p1,p2);
                                                                         break;
#ifdef LARGE_POINTER
  case 18: sprintf(msgBuf,"error for %s: cannot add %lu, relation already exists\n\0",
                                                      p1,(ZZlong)(p2)); break;
  case 19: sprintf(msgBuf,"cannot add to %s, relation %lu not disconnected\n\0",
                                                      p1,(ZZlong)(p2)); break;
  case 20: sprintf(msgBuf,"%s%lu%s%s\0",
      "warning: big block of ",
      (unsigned ZZlong)(p2) - (unsigned ZZlong)(p1),
      " bytes exhausted\n",
      "         changing to the regular allocation scheme\n");break;
  case 21: sprintf(msgBuf,"reading a block of %lu bytes from disk ...\n\0",
                             (unsigned ZZlong)(p2) - (unsigned ZZlong)(p1)); break;
  case 22: sprintf(msgBuf,"error in generic function=%s organization=%s\n\0",p1,p2);break;
  case 23: sprintf(msgBuf,"cannot add to %s, object %lu not disconnected\n\0",
                                                 p1,(unsigned ZZlong)(p2)); break;
  case 24: sprintf(msgBuf,"cannot insert %s, object %lu not disconnected\n\0",
                                                 p1,(unsigned ZZlong)(p2)); break;
  case 25: sprintf(msgBuf,"cannot append %s, object %lu not disconnected\n\0",
                                                 p1,(unsigned ZZlong)(p2)); break;
  case 26: sprintf(msgBuf,"cannot append to the root of %s, object=%lu\n\0",
                                                 p1,(unsigned ZZlong)(p2)); break;
  case 27: sprintf(msgBuf,"cannot insert to the root of %s, object=%lu\n\0",
                                                 p1,(unsigned ZZlong)(p2)); break;
  case 28: sprintf(msgBuf,"error: %lu blast memory overflow, blastSize=%lu\n\0",
                                 (unsigned ZZlong)p1,(unsigned ZZlong)p2); break;
  case 29: sprintf(msgBuf,"error: cannot allocate %lu bytes, page=%lu\n\0",p1,p2); break;
  case 30: sprintf(msgBuf,"error: cannot add object=%lu, hash table=%s\n\0",p1,p2);break;
  case 31: sprintf(msgBuf,"error: virt.array size=%l index=%l\n\0",p1,p2);break;
  case 32: sprintf(msgBuf,
       "error del(): object=%lu in %s, not found in bucket\n\0",p1,p2);break;
  case 33: sprintf(msgBuf,
       "error del(): object=%lu in %s, bucket is empty\n\0",p1,p2);break;
  case 34: sprintf(msgBuf,"cannot add to %s, parent %lu not disconnected\n\0",
                                                 p1,(unsigned ZZlong)(p2)); break;
  case 35: sprintf(msgBuf,"cannot add to %s, child %lu not disconnected\n\0",
                                                 p1,(unsigned ZZlong)(p2)); break;
  case 36: sprintf(msgBuf,
      "warning del(): object=%lu in %s, not in any hash table\n\0",p1,p2);break;
#else
  case 18: sprintf(msgBuf,"error for %s: cannot add %d, relation already exists\n\0",
                                                      p1,(ZZint)(p2)); break;
  case 19: sprintf(msgBuf,"cannot add to %s, relation %d not disconnected\n\0",
                                                      p1,(ZZint)(p2)); break;
  case 20: sprintf(msgBuf,"%s%d%s%s\0",
      "warning: big block of ",
      (unsigned ZZint)(p2) - (unsigned ZZint)(p1),
      " bytes exhausted\n",
      "         changing to the regular allocation scheme\n");break;
  case 22: sprintf(msgBuf,"error in generic function=%s organization=%s\n\0",p1,p2);break;
  case 23: sprintf(msgBuf,"cannot add to %s, object %d not disconnected\n\0",
                                                 p1,(unsigned ZZint)(p2)); break;
  case 24: sprintf(msgBuf,"cannot insert %s, object %d not disconnected\n\0",
                                                 p1,(unsigned ZZint)(p2)); break;
  case 25: sprintf(msgBuf,"cannot append %s, object %d not disconnected\n\0",
                                                 p1,(unsigned ZZint)(p2)); break;
  case 26: sprintf(msgBuf,"cannot append to the root of %s, object=%d\n\0",
                                                 p1,(unsigned ZZint)(p2)); break;
  case 27: sprintf(msgBuf,"cannot insert to the root of %s, object=%d\n\0",
                                                 p1,(unsigned ZZint)(p2)); break;
  case 28: sprintf(msgBuf,"error: %u blast memory overflow, blastSize=%u\n\0",
                                 (unsigned ZZint)p1,(unsigned ZZint)p2); break;
  case 29: sprintf(msgBuf,"error: cannot allocate %u bytes, page=%u\n\0",p1,p2); break;
  case 30: sprintf(msgBuf,"error: cannot add object=%u, hash table=%s\n\0",p1,p2);break;
  case 31: sprintf(msgBuf,"error: virt.array size=%l index=%l\n\0",p1,p2);break;
  case 32: sprintf(msgBuf,
       "error del(): object=%u in hash=%s, not in bucket\n\0",p1,p2);break;
  case 33: sprintf(msgBuf,
       "error del(): object=%u in hash=%s, bucket is empty\n\0",p1,p2);break;
  case 34: sprintf(msgBuf,"cannot add to %s, parent %d not disconnected\n\0",
                                                 p1,(unsigned ZZint)(p2)); break;
  case 35: sprintf(msgBuf,"cannot add to %s, child %d not disconnected\n\0",
                                                 p1,(unsigned ZZint)(p2)); break;
  case 36: sprintf(msgBuf,
      "warning del(): object=%d in %s, not in any hash table\n\0",p1,p2);break;
#endif
  default: sprintf(msgBuf,"strange error detected, code=SS%d/%s/%s\n\0",i,p1,p2); break;
}
sprintf(codeBuf,"SS%d\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgDD(ZZint i,ZZint k1,ZZint k2) {
#else
void ZZmsgDD(i,k1,k2) ZZint i,k1,k2; {
#endif
switch(i){
  case 0: sprintf(msgBuf,"%s%d%s%d%s\0",
    "ZZinternal counting error in parser k=",k1," n=",k2,
    "\nprobably, your program is too ZZlong\n"); break;
  case 1: sprintf(msgBuf,"array size=%d index=%d out of range\n\0",k1,k2); break;
  case 2: sprintf(msgBuf,"error: reading %d bytes, but only %d read in\n\0",k1,k2);break;
  case 3: sprintf(msgBuf,"error: write for %d bytes, only %d written\n\0",k1,k2); break;
  case 4: /* unused entry */ break;
  case 5: sprintf(msgBuf,"wrong ZZinternal setting, ZZnTbType=%d ZZpTbType=%d\n\0",k1,k2);
                                                                        break;
  case 6: sprintf(msgBuf,"warning: pool=%d, needed=%d, new block created\n\0",k1,k2);
                                                                        break;
  case 7: sprintf(msgBuf,"error: wrong nesting of {} between lines=%d,%d, giving up\n\0",
                                                                 k1,k2); break;
  case 8: sprintf(msgBuf,"error: size of object=%u, page size=%u\n\0",k1,k2); break;
  default: sprintf(msgBuf,"strange error detected, code=DD%d/%d/%d\n\0",i,k1,k2); break;
}
sprintf(codeBuf,"DD%d\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgSD(ZZint i,const char *p,ZZint k) {
#else
void ZZmsgSD(i,p,k) ZZint i,k; char *p; {
#endif
switch(i){
  case 0: sprintf(msgBuf,"ZZinternal overflow %s=%d\n\0",p,k); break;
  case 1: sprintf(msgBuf,"zzprep BUFSIZE=%d insufficient to expand:%s\n\0",k,p); break;
  case 2: sprintf(msgBuf,"zzmaster part=%s index=%d out of sequence\n\0",p,k); break;
  case 3: sprintf(msgBuf,"cannot free object=%s, pointer No.%d not disconnected\n\0",p,k);
                                                                     break;
#ifdef LARGE_POINTER
  case 12: sprintf(msgBuf,"error1 in ASCII format when readBind(), type=%d ptr=%lu\n\0",
                                                          k,(ZZlong)p); break;
#else
  case 12: sprintf(msgBuf,"error1 in ASCII format when readBind(), type=%d ptr=%d\n\0",
                                                          k,(ZZint)p); break;
#endif
  case 13: sprintf(msgBuf,"error: cannot allocate %d Bytes in %s\n\0",k,p);break;
  case 14: sprintf(msgBuf,"error: %s %d\n\0",p,k);break;
  case 15: sprintf(msgBuf,"unable to allocate sweap table for %l objects, %d entries\n\0",
           i,*((ZZlong *)p),k); break;
#ifdef LARGE_POINTER
  case 16: sprintf(msgBuf,"ZZinternal error, strategy=%d cannot convert=%lu\n\0",
#else
  case 16: sprintf(msgBuf,"ZZinternal error, strategy=%d cannot convert=%d\n\0",
#endif
           k,p); break;
#ifdef LARGE_POINTER
  case 17: sprintf(msgBuf,"error2 in ASCII format when readBind(), type=%d ptr=%lu\n\0",
                                                          k,(ZZlong)p); break;
#else
  case 17: sprintf(msgBuf,"error2 in ASCII format when readBind(), type=%d ptr=%d\n\0",
                                                          k,(ZZint)p); break;
#endif
  default: sprintf(msgBuf,"strange error detected, code=SD%d/%s/%d\n\0",i,p,k); break;
}
sprintf(codeBuf,"SD%d\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgSSS(ZZint i,const char *p1,const char *p2,const char *p3) {
#else
void ZZmsgSSS(i,p1,p2,p3) ZZint i; char *p1,*p2,*p3; {
#endif
switch(i){
  case 0: sprintf(msgBuf,"line:%s generic=%s expanded=%s not found\n\0",p1,p2,p3); break;
  case 1: sprintf(msgBuf,"line:%s function=%s organization=%s do not match\n\0",p1,p2,p3);
                                                                          break;
  case 4: sprintf(msgBuf,"%30s %12s  file: %s\n\0",p1,p2,p3); break;
#ifdef LARGE_POINTER
  case 5: sprintf(msgBuf,"%s%lu%s%s%lu%s%lu\n\0",
    "WARNING: ZZ_OPEN() reading block of %lu bytes\n",p1,
    "         existing pool=",p2,
    ", new block created, new pool=",p2); break;
  case 6: sprintf(msgBuf,
           "ZZinternal error in %s: using page No.%lu, only %lu pages present\n\0",
                                                             p1,p2,p3); break;
  case 7: sprintf(msgBuf,"memory block conflict index=%lu old page=%lu new=%lu\n\0",
                                                             p1,p2,p3); break;
#else
  case 5: sprintf(msgBuf,"WARNING: ZZ_OPEN() reading block of %u bytes\n\0",p1);
          sprintf(msgBuf,"         existing pool=%u, new block created, new pool=%u\n\0"
                                                              ,p2,p3); break;
  case 6: sprintf(msgBuf,
           "ZZinternal error in %s: using page No.%u, only %u pages present\n\0",
                                                             p1,p2,p3); break;
  case 7: sprintf(msgBuf,"memory block conflict index=%u old page=%u new=%u\n\0",
                                                             p1,p2,p3); break;
#endif

  default: sprintf(msgBuf,"strange error detected, code=SSS%d/%s/%s/%s\n\0",i,p1,p2,p3);
                                                                       break;
}
sprintf(codeBuf,"SSS%d\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgDDD(ZZint i,ZZint k1,ZZint k2,ZZint k3) {
#else
void ZZmsgDDD(i,k1,k2,k3) ZZint i,k1,k2,k3; {
#endif
switch(i){
  case 1: sprintf(msgBuf,"problem to fit oldType=%d offset=%d ZZinto newType=%d\n\0",k1,k2,k3); 
          break;
  default: sprintf(msgBuf,"strange error detected, code=DDD%d/%d/%d/%d\n\0",i,k1,k2,k3);
          break;
}
sprintf(codeBuf,"DDD%d\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgSDD(ZZint i,const char *p,ZZint k1,ZZint k2) {
#else
void ZZmsgSDD(i,p,k1,k2) char *p; ZZint i,k1,k2; {
#endif
switch(i){
  case 0: sprintf(msgBuf,"cannot free array, element %s[%d] pointer No=%d not disconnected\n\0",p,k1,k2); break;
  case 1: sprintf(msgBuf,"error: reading <%s> %I64 bytes, but only %I64 read in\n\0",p,k1,k2); break;
  case 2: sprintf(msgBuf,"error: writing <%s> %I64 bytes, but only %I64 written\n\0",p,k1,k2); break;
  default: sprintf(msgBuf,"strange error detected, code=SDD%d/%s/%d/%d\n\0",i,p,k1,k2);
                                                                       break;
}
sprintf(codeBuf,"SDD%d\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgSSD(ZZint i,const char *p1,const char *p2,ZZint k) {
#else
void ZZmsgSSD(i,p1,p2,k) char *p1,*p2; ZZint i,k; {
#endif
switch(i){
#ifdef LARGE_POINTER
  case 0: sprintf(msgBuf,"error in binding, type=%s, ptr offset=%d, old ptr=%lu\n\0",
#else
  case 0: sprintf(msgBuf,"error in binding, type=%s, ptr offset=%d, old ptr=%du\n\0",
#endif
                                                             p1,k,p2); break;
#ifdef LARGE_POINTER
  default: sprintf(msgBuf,"strange error detected, code=SSD%d/%s/%lu/%d\n\0",
#else
  default: sprintf(msgBuf,"strange error detected, code=SSD%d/%s/%du/%d\n\0",
#endif
                                                           i,p1,p2,k); break;
}
sprintf(codeBuf,"SDD%d\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgSSDD(ZZint i,const char *p1,const char *p2,ZZint k1,ZZint k2) {
#else
void ZZmsgSSDD(i,p1,p2,k1,k2) ZZint i; char *p1,*p2; ZZint k1,k2; {
#endif
switch(i){
  case 0: sprintf(msgBuf,"         type=%s changed to %s, size=%d changed to %d\n\0",
                                       p1,p2,k1,k2); break;
  case 1: sprintf(msgBuf,"%s%s%s%s%s%d%s%d\n\0",
    "ZZinternal error for ",p1," inside ",p2,
    "\n     type offset=",k1,", address offset=",k2); break;
  default: sprintf(msgBuf,"strange error detected, code=SSDD%d/%s/%s/%d/%d\n\0",
                                                    i,p1,p2,k1,k2); break;
}
sprintf(codeBuf,"SSDD%d\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgSDDD(ZZint i,const char *p,ZZint k1,ZZint k2,ZZint k3) {
#else
void ZZmsgSDDD(i,p,k1,k2,k3) char *p; ZZint k1,k2,k3; {
#endif
switch(i){
  case 0: sprintf(msgBuf,"error for %s, start=%d numPtr=%d selfIndex=%d\n\0",p,k1,k2,k3);
                                                                         break;
  case 1: sprintf(msgBuf,"ZZinternal index problem for %s j1=%d j2=%d ns=%d\n\0",p,k1,k2,k3);
                                                                        break;
  default: sprintf(msgBuf,"strange error detected, code=SDDD%d/%s/%d/%d/%d\n\0",
                                                          i,p,k1,k2,k3); break;
}
sprintf(codeBuf,"SDDD%d\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}
/* -------------------------------------------------------------------- */
#ifdef ZZ_ANSI
void ZZmsgSL(ZZint i,const char *p,ZZlong k) {
#else
void ZZmsgSL(i,p,k) ZZint i; char *p; ZZlong k; {
#endif

switch(i){
  case 0: sprintf(msgBuf,"error in: %s, cannot convert long=%I64u ZZinto ZZinteger\n\0",p,k);
  default: sprintf(msgBuf,"strange error detected, code=SL%d/%s/%I64u\n\0",i,p,k); break;
}
sprintf(codeBuf,"SL%d\0",i);
if(ZZerrFLG)zzReportError(ZZerrFLG,codeBuf,msgBuf); else printf("%s",msgBuf);
return;
}

/* ---------------------------------------------------------------- */
#ifndef ZZlocal
#ifndef ZZcallBack

/* Special function which converts the 'errCode' string ZZinto a long code
 * Resulting format: XXX0YY where X represents the message type, and Y
 * the ZZinternal message number. The X conversion is:
 * S=1, D=2, L=3, C=4
 * In case of ZZinternal error (errCode cannot be decoded), returns 999999
 */
static ZZlong errorCodeConvert(char *errCode){
 static char c[]={'S','D','L','C','0','1','2','3','4','5','6','7','8','9','E'};
 static ZZint  i[]={ 1 , 2 , 3 , 4 , 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , -1};
 static ZZint num=4; /* number of leading letters in c[] */
    ZZint k,lastK;
    ZZlong r=0;
    char *p;
    for(p=errCode, k=lastK=0; *p!='\0'; p++, lastK=k){
        for(k=0; c[k]!='E'; k++){
            if(*p==c[k])break;
        }
        if(i[k]<0){r=999999; break;}
        if(lastK<num && k>=num)r=r*100; else r=r*10;
        r=r+i[k];
    }
    return r;
}

#ifdef ZZ_ANSI
static void zzReportError(ZZint errVal, char *errCode, char *errMsg)
#else
static void zzReportError(errVal,errCode,errMsg)
ZZint errVal;    /* value of ZZerror, binary encoded */
char *errCode; /* code for lookup in msgs.c */
char *errMsg;  /* error msg normally prZZinted on stdout */
#endif
{
#ifdef SPECIAL_OPTION
    ZZlong code,errorCodeConvert(char *);
    code=errorCodeConvert(errCode);
    printf("errLevel=%d errCode=%ld: %s",errVal,code,errMsg); 
#else // SPECIAL_OPTION
    printf("errLevel=%d errCode=%s: %s",errVal,errCode,errMsg); 
#endif // SPECIAL_OPTION
}
#endif /* ZZlocal */
#endif /* ZZcallBack */
/* ---------------------------------------------------------------- */

#endif // Windows64 =====================================================
