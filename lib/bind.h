/* ============================================================ */

/****************************************************************/
/*							      	*/
/*   Copyright (C) 1988 1989             			*/
/*	Code Farms Inc.,  All Rights Reserved.			*/
/*							  	*/
/****************************************************************/

/* ============================================================ */

#ifdef DOS
#include <fcntl.h>
#endif

#ifdef UNIX
#include <fcntl.h>
#ifndef MAC
#include <sys/types.h>
#endif
#ifdef SUN
#ifdef UPP
#include <io.h>
#else
#ifndef MAC
#include <sys/uio.h>
#endif
#endif
#endif
#endif

#ifdef VMS
#include <file.h>
#include <types.h>
#endif

/* input/output file when binding */

struct ZZstrLST {
    char *strName;  /* name of the structure */
    ZZint start;      /* offset for the start of ZZ_EXT, in bytes */
    ZZint size;       /* size of the whole structure in bytes */
    ZZint numPtr;     /* number of pointers in ZZ_EXT, -1 is the endmark */
    ZZint selfIndex;  /* order index of the selfID pointer */
    ZZint propIndex;  /* order index of the property pointer */
    ZZint timeIndex;  /* order index equivalent to start timeStamp */
    ZZint arrayIndex; /* last section of pointers are all for arrays */
    ZZint ptrInd;     /* index to ZZptrList to get type codes for all pointers */
    ZZint inhInd;     /* inheritance index ZZinto ZZtypeHier list, ZZiList */
    char *vObj[2];    /* 0= master object with correct virt. pointers */
                      /* 1= master object with byte 'F' marking virt. pointers */
    ZZint vPtr;       /* 1=virt.pointer actually used, 0=not used */
};
/* convention: entry with numPtr=-1 marks the end of the list,
 *             ptrInd for that entry gives total number of pointers and
 *             other variables,
 *             If, in the last record, start=0, it means that the big
 *             block of memory is being used.
 * vObj[0] has NULL in all positions except for vf and vc pointers
 * vObj[1] has '\0' in all bytes except for bytes that start a virtual
 *             function pointer ('F') or virtual base class pointer ('C')
 * Note that, for some compilers such as Borland, the two pointer types
 * may have different size.
 */

struct ZZbinStore {
    char *ptr;  /* pointer to the beginning of the block */
    ZZint strInd; /* structure type index ZZinto ZZstrList[] */
    ZZint size;   /* size of the block in bytes */
};

struct ZZtypeHier {
    ZZint type;   /* index ZZinto the type table, must be >=0 */
    ZZint offset; /* offset of ZZ_EXT within the parent, in bytes */
    ZZint num;    /* 0=inherited, 1=single object, >1 embedded array, -1 unused */
    char *name; /* member name, *'ZZinherit','ZZvirtual' if inheritance,
                   'ZZrefer' if v.c. involved */
};
/* Note that ZZaddress does not represent a true hierarchical
 * relation, it is used to store the offset for virtual classes
 * burried under more than one inheritance level */

/* pointer conversion table */
struct ZZbindTBL {
    char *oldp;    /* old pointer */
    char *newp;    /* new pointer */
    ZZint strIndex;  /* old structure index */
    ZZint arrSize;   /* overall size of object or array */
    struct ZZbindTBL *next; /* linking the chain */
};

#ifdef ZZmain
ZZ_LOCAL struct ZZbindTBL **ZZbindTable ={0}; /* hash table for pointer conversion */
ZZ_LOCAL ZZint ZZbindSize={0}; /* size of the hash table */
ZZ_LOCAL char *ZZbindName;  /* name of the currently opened bind file */
ZZ_LOCAL ZZint ZZbindCntrl={0};
ZZ_LOCAL struct ZZstrLST *ZZsList; /* description of classes */
ZZ_LOCAL struct ZZstrLST *ZZoList; // description of old classes */
ZZ_LOCAL struct ZZtypeHier *ZZiList={0}; /* inheritance list */
ZZ_LOCAL char **ZZpList;
#endif
#ifndef ZZmain
extern struct ZZbindTBL **ZZbindTable; /* hash table for pointer conversion */
extern ZZint ZZbindSize;
extern char *ZZbindName;  /* name of the currently opened bind file */
extern ZZint ZZbindCntrl;
extern struct ZZstrLST *ZZsList;
extern struct ZZstrLST *ZZoList;
extern struct ZZtypeHier *ZZiList;
extern char **ZZpList;
#endif

