/* test of combined use of SAVE and GENERAL_LINK.
 * Originally, the two could not be used simultaneously;
 * this is a test of the new features introduced on Oct.10/89 */
#include <stdio.h>
#define ZZmain
#include "zzincl.h"

typedef struct Block Block;
typedef struct Pin Pin;

struct Block {
    ZZ_EXT_Block    /* let the program to hide the pointers here */
    int x;
};
struct Pin {
    ZZ_EXT_Pin    /* let the program to hide the pointers here */
    int x;
};

ZZ_ORG_GENERAL_LINK(link,Pin);
ZZ_ORG_NAME(bName,Block);

#ifdef ZZ_ANSI
int main(void)
#else
int main()
#endif
{
    char *v[2],*t[2],*cp;
    Block *bp;
    Pin *pp;

    /* allocate two objects */
    ZZ_PLAIN_ALLOC(Block,1,bp);
    ZZ_PLAIN_ALLOC(Pin,1,pp);
    ZZ_STRING_ALLOC("BLOCK1",cp);
    ZZ_ADD(bName,bp,cp);
    pp->x=1; bp->x=2;
    ZZ_ADD(link,pp,bp); /* make a general link between them */
    /* save the whole "database" */
    v[0]=(char*)pp; v[1]=(char*)bp;
    t[0]=(char*)"Pin"; t[1]=(char*)"Block";
    ZZ_SAVE((char*)"sfile",2,v,t);
    return(0);
}
#include "zzfunc.c"
