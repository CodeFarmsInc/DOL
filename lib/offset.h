/* ============================================================ */

/****************************************************************/
/*							      	*/
/*   Copyright (C) 1988 1989             			*/
/*	Code Farms Inc.,  All Rights Reserved.			*/
/*							  	*/
/****************************************************************/

/* ============================================================ */
#ifdef ZZmain
ZZ_LOCAL int ZZptrOff; /* fwp offset */
#else
extern int ZZptrOff; /* fwp offset */
#endif

#define ZZptrRel(A) ((char**)(((A)+ZZptrOff)))

union ZZUNI {
    FILE *fp;
    void *p;
    ZZsize s;
    ZZint i;
    ZZlong l;
    unsigned ZZlong ul;
    ZZptrIntType pit;
    ZZsigIntType sit;
    char c;
    ZZfloat f;
};
