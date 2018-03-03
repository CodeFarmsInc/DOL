/****************************************************************/
/*							      	*/
/*   Copyright (C) 1988 1989             			*/
/*	Code Farms Inc.,  All Rights Reserved.			*/
/*							  	*/
/****************************************************************/

#define zzLIB
#include <stdio.h>
#include "environ.h"
#include "types.h"
#include "heading.h"
#include "offset.h"
#include "msgs.h"

static char **pp;
#define GET_NEXT(A,B) {pp=ZZptrRel(A); (B)=(*pp);}
#define SET_NEXT(A,B) {pp=ZZptrRel(A); (*pp)=(B);}

/* main call to the ring sorting function, sets up the ring poZZinter
 * ofset and then sorts the ring.
 * The sorting algorithm works like this:
 * First it finds sub-sections that are already sorted.
 * Then it walks over the list and picks up the first two subsections,
 * and merges them. Then it keeps walking through the list and 
 * picks up next two subsections and merges them, and so on until 
 * the end of list is reached. Then it starts again from the beginning,
 * and repeats this process until all data is sorted.
 * The advantages of this algorithm are:
 * O(log n) complexity, no recursive function used, no additional
 * storage or temporary stack needed.
 * Author: Jiri Soukup, 1989
 */
#ifdef ZZ_ANSI
char* ZZrSRfun(char *rPtr,char *tail,ZZTsortFun cmpF)
{
    ZZint ZZpOffset(char *r,char *s);
#else


char *ZZrSRfun(rPtr,tail,cmpF)
char *rPtr;    /* ring poZZinter for the tail, neede to derive the offset */
char *tail;   /* tail of the ring */
ZZint (*cmpF)(); /* compare two objects, like for qsort() */
/* function returns the new tail of the ring */
{
    ZZint ZZpOffset();
#endif
    char *h1,*t1,*h2,*t2,*p,*nxt,*p1,*p2,*first,*last,*start,*hook1,*hook2;
    ZZint stopFlg;

    if(!tail)return(tail);
    ZZptrOff=ZZpOffset(rPtr,tail);
    GET_NEXT(tail,start);
    if(tail==start)return(tail);

    /* walk through the input, insert up/down section by section */
    for(stopFlg=0, t1=tail; !stopFlg; t1=t2){ 
        GET_NEXT(t1,h2);
        t2=h2;
        GET_NEXT(h2,nxt);
        for(p=nxt; p!=h2 ;p=nxt){
            if(p==tail)stopFlg=1;
            GET_NEXT(p,nxt);
	    if((*cmpF)(p,t2)>=0)t2=p;
	    else if((*cmpF)(p,h2)<=0){
                if(nxt==h2){h2=p; break;}
                else {
                    SET_NEXT(t2,nxt); SET_NEXT(t1,p); SET_NEXT(p,h2); h2=p;                }
            }
            else break;
        }
    }
    GET_NEXT(t2,nxt);
    if(nxt==h2)return(t2); /* result already sorted */
    start=h2; /* section may overlap the original start */  

    /* keep sorting adjacent sublists until everything is one list */
    for(stopFlg=0; !stopFlg;){
        hook1=t2;
        /* find the first sublist */
        GET_NEXT(t2,h1);
        GET_NEXT(h1,nxt);
        for(last=h1, p=nxt; ; last=p, p=nxt){
            GET_NEXT(p,nxt);
	    if((*cmpF)(last,p)>0)break;
        }
        t1=last; h2=nxt;
        if(h2==h1)break; /* one sorted sublist, job finished */

        /* find the second sublist */
        GET_NEXT(t1,h2);
        GET_NEXT(h2,nxt);
        for(last=h2, p=nxt; ; last=p, p=nxt){
            GET_NEXT(p,nxt);
	    if((*cmpF)(last,p)>0)break;
        }
        t2=last;
        if(h1==p)stopFlg=1; /* these are the last two sublists */
        hook2=p;

        SET_NEXT(t1,NULL); SET_NEXT(t2,NULL); /* unhook both sublists */

        /* merge the two lists, new list from 'first' to 'last' */
        first=last=(char *)NULL;
        for(p1=h1, p2=h2 ;p1||p2; last=p ){
	    if(!p1)     p=p2;
	    else if(!p2)p=p1;
	    else if((*cmpF)(p1,p2)<=0)p=p1;
	    else p=p2;
    
            GET_NEXT(p,nxt);
	    if(p==p1) p1=nxt; else p2=nxt;
            if(!first)first=p;
            if(last){SET_NEXT(last,p);}
        }

        /* hook both list back ZZinto the main list */
        if(stopFlg){SET_NEXT(last,first);}
        else { SET_NEXT(hook1,first); SET_NEXT(last,hook2); }
        t2=last;
    }
    return(last);
}
#ifdef ZZ_ANSI
void dumbZortechLinker(void){}
#else
void dumbZortechLinker(){}
#endif
