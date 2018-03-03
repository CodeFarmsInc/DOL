/* test of transferring data between different versions of Organized C
 * This particular input is a simple one-object data from Ver.1.62
 *
 * This test runs on all platforms except for Zortech C++, where 
 * it corrupts the heap. I plan to make a more thorough examination
 * of this case later - J.Soukup, Sept.25/90 
 */
#include <stdio.h>
#define ZZmain
#define ZZascii
#include "zzincl.h"
    typedef struct Instance Instance;
    typedef struct Net Net;
    typedef struct ActTerm ActTerm;
    struct Instance {
        ZZ_EXT_Instance
        int x1,y1,x2,y2;
    };
    ZZ_FORMAT(Instance,"%d %d %d %d,x1,y1,x2,y2");
    struct Net {
        ZZ_EXT_Net
    };
    ZZ_FORMAT(Net,"");
    struct ActTerm {
        ZZ_EXT_ActTerm
        int x,y;
    };
    ZZ_FORMAT(ActTerm,"%d %d,x,y");
    ZZ_ORG_SINGLE_RING(iRing,Instance);
    ZZ_ORG_SINGLE_RING(nRing,Net);
    ZZ_ORG_SINGLE_TRIANGLE(byInst,Instance,ActTerm);
    ZZ_ORG_SINGLE_TRIANGLE(byNet,Net,ActTerm);
    ZZ_ORG_NAME(iName,Instance);
    ZZ_ORG_NAME(nName,Net);
    ZZ_ORG_PROPERTY(Net);
    ZZ_ORG_TIME_STAMP(Instance);

#define BSIZE 80
char buff[BSIZE];
#ifdef ZZ_ANSI
int main(void) {
#else

int main() {
#endif
    Instance *ip;
    char *v[2],*t[2];
    unsigned char s[6];
    
    printf("test 21:\n");
    ZZ_MODE_SAVE(1,0,162,0);
    ZZ_OPEN("inp21",2,v,t);
    ip=(Instance *)v[0];
    ZZ_GET_TIME_STAMP(ip,s);
    printf("%d %d %d %d  time  %d %d %d %d %d %d\n",
            ip->x1,ip->y1,ip->x2,ip->y2,s[0],s[1],s[2],s[3],s[4],s[5]);
    ZZ_A_TRAVERSE(iRing,(Instance *)(v[1]),ip){
        printf("%d %d %d %d\n",ip->x1,ip->y1,ip->x2,ip->y2);
    }ZZ_A_END;
    return(0);
}
#include "zzfunc.c"
