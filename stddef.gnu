// This may look like C code, but it is really -*- C++ -*-
/* 
Copyright (C) 1988 Free Software Foundation
    written by Doug Lea (dl@rocky.oswego.edu)

This file is part of GNU CC.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.  No author or distributor
accepts responsibility to anyone for the consequences of using it
or for whether it serves any particular purpose or works at all,
unless he says so in writing.  Refer to the GNU CC General Public
License for full details.

Everyone is granted permission to copy, modify and redistribute
GNU CC, but only under the conditions described in the
GNU CC General Public License.   A copy of this license is
supposed to have been given to you along with GNU CC so you
can know your rights and responsibilities.  It should be in a
file named COPYING.  Among other things, the copyright notice
and this notice must be preserved on all copies.  
*/

#ifndef _stddef_h
#ifdef __GNUG__
#pragma once
#pragma interface
#endif

#define _stddef_h
#define _SIZE_T
#define _PTRDIFF_T

// TRUE, FALSE, bool, are now in <bool.h>, for ANSI compatibility

#ifndef _SIZE_T
#ifndef _SIZE_T_
typedef unsigned int size_t;
#endif
#endif

#ifndef _PTRDIFF_T
#ifndef _PTRDIFF_T_
typedef long int	 ptrdiff_t;
#endif
#endif

#ifdef DGUX
typedef	int	wchar_t;
#else
typedef	unsigned short	wchar_t;
#endif

#ifndef NULL
#define NULL 0
#endif

/* Offset of member MEMBER in a struct of type TYPE.  */

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#endif
