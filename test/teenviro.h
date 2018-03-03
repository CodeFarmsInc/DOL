/****************************************************************/
/*							      	*/
/* Copyright (C) 1988 1989 Code Farms Inc. All Rights Reserved. */
/*							  	*/
/****************************************************************/

/* Environment: DOS, UNIX, or VMS
 *
 * DOS must also have: either TURBOC, MICROSOFT, or ZORTECH
 * If you use a memory model where the pointer is larger than int,
 * such as the Microsoft or Turbo C Large Memory Model, you also have to use:
 *     #define LARGE_POINTER
 * 
 * SUN, APOLLO, uVax, Masscomp, HP, they all run under UNIX 
 * VMS VAX must have define OTHER
 */

#define DOS
#define TURBOC
#define ZZcplus
#define ZZansi
#define ZZ_INHERIT
#define LARGE_POINTER
