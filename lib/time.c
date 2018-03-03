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
#include "orgctime.h"
#include "msgs.h"

/* time(2) required for UNIX, gettime() and getdate() used in DOS */
#ifdef UNIX
#include <time.h>
#ifdef ZZcplus
#ifndef SABERCPLUS
extern "C" {time_t time(time_t *);}
#endif
#endif
#endif

#ifdef VMS
#include <time.h>
#endif
#ifdef DOS
#include <dos.h>
#endif
#ifdef MICROSOFT
#include <time.h>
#endif

/* ----------------------------------------------------------------------- */
/* get date and time from the oper.system and convert it
 * into a time stamp, with the accuracy of seconds.
 * The time stamp will be set in a string 4 bytes long (ZZtSize=4).
 */
#ifdef ZZ_ANSI
void ZZstTime(unsigned char *c)
{
#else


void ZZstTime(c)
unsigned char *c; /* array of ZZtSize characters to store the timeStamp */
{
#endif
    int d1,d2,d3,t1,t2,t3;
    unsigned int a,b,q;
#ifdef TURBOC
    struct date d;
    struct time t;

    getdate(&d);
    gettime(&t);
    d1=d.da_year-(d.da_year/100)*100-88;
    d2=d.da_mon-1;
    d3=d.da_day;
    t1=t.ti_hour;
    t2=t.ti_min;
    t3=t.ti_sec;
#endif
#ifdef MICROSOFT
#ifdef MICROSOFT8
    time_t clock;
#else
    unsigned long clock;
#endif
#ifdef MICROSOFT6
    unsigned long time();
#endif
    struct tm *t;

    clock=time(0);
#ifdef ZORTECH
    t=localtime((long *)(&clock));
#else
    t=gmtime(&clock);
#endif
    d1=t->tm_year-88; /* already - 1900 in UNIX */
    d2=t->tm_mon;
    d3=t->tm_mday;
    t1=t->tm_hour;
    t2=t->tm_min;
    t3=t->tm_sec;
#endif

#ifdef UNIX
#ifdef MAC
    time_t clock;
#else
#ifdef DECPLUS
    time_t clock;
#else
    long clock;
#endif
#endif
#ifndef MAC
#ifndef ZZcplus
    long time();
#endif
#endif
    struct tm *t;

    clock=time(0);
#ifdef MAC
    t=localtime(&clock);
#else
    t=gmtime(&clock);
#endif
    d1=t->tm_year-88; /* already - 1900 in UNIX */
    d2=t->tm_mon;
    d3=t->tm_mday;
    t1=t->tm_hour;
    t2=t->tm_min;
    t3=t->tm_sec;
#endif
#ifdef VMS
    time_t clock;
    struct tm *t;
    clock=time(NULL);
    t=localtime(&clock);
    d1=t->tm_year-88; /* already - 1900 like in UNIX */
    d2=t->tm_mon;
    d3=t->tm_mday;
    t1=t->tm_hour;
    t2=t->tm_min;
    t3=t->tm_sec;
#endif

/* WARNING: Under C++ compilers and MAC, the month is smaller by 1.
 * This is unbelievable, I provide a correction. */
#ifdef MAC
    d2++;
#else
#ifdef ZZcplus
    d2++;
#endif
#endif

    q=t1/8;  /* time is longer, store part in the date bits */
    a=((d1*13+d2)*32+d3)*4+q; b=a/256;
    c[0]=b; c[1]=(a-b*256);
    a=((t1-q*8)*60+t2)*60+t3; b=a/256;
    c[2]=b; c[3]=(a-b*256);
    return;
}
/* ----------------------------------------------------- */
/* convert the internal packed timeStamp into byte coded date and time */
#ifdef ZZ_ANSI
void ZZgtTime(unsigned char *is,unsigned char *es)
#else


void ZZgtTime(is,es)
unsigned char *is; /* internal stamp, packed in ZZtSize bytes (=4) */
unsigned char *es; /* external stamp, 6 bytes */
#endif
{
    unsigned int a,b,q;
    
    a=is[0]; b=is[1]; a=(256*a+b); /* packed date converted to one integer */
    b=a/4; q=a-b*4; a=b;
    b=a/32; es[2]=(a-b*32); a=b;   /* day */
    b=a/13; es[1]=(a-b*13);        /* month */
    es[0]=b+88;                     /* year -1900 */
    
    a=is[2]; b=is[3]; a=(256*a+b); /* packed time converted to one integer */
    b=a/60; es[5]=(a-b*60); a=b;   /* seconds */
    b=a/60; es[4]=(a-b*60);        /* minutes */
    es[3]=b+q*8;                     /* hours */

    return;
}
