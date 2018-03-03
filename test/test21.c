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
    struct Net {
        ZZ_EXT_Net
    };
    struct ActTerm {
        ZZ_EXT_ActTerm
        int x,y;
    };
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
/* ===================================================== */
#include "zzfunc.c"

#ifdef ZZ_ANSI
int zz_out_Instance(FILE *fp,Instance *p) {
#else
int zz_out_Instance(fp,p) FILE *fp; Instance *p; {
#endif
    fprintf(fp,"%d %d %d %d\n",p->x1,p->y1,p->x2,p->y2);
    return(0);
}
#ifdef ZZ_ANSI
int zz_out_Net(FILE *fp,Net *p) {
#else
int zz_out_Net(fp,p) FILE *fp; Net *p; {
#endif
    fp=fp; p=p; /* avoid warnings from the compiler */
    return(0);
}
#ifdef ZZ_ANSI
int zz_out_ActTerm(FILE*fp,ActTerm *p) {
#else
int zz_out_ActTerm(fp,p) FILE *fp; ActTerm *p; {
#endif
    fprintf(fp,"%d %d\n",p->x,p->y);
    return(0);
}
#ifdef ZZ_ANSI
int zz_inp_Instance(FILE *fp,Instance *p) {
#else
int zz_inp_Instance(fp,p) FILE *fp; Instance *p; {
#endif
    if(!fgets(buff,BSIZE,fp))return(1);
    sscanf(buff,"%d %d %d %d\n",&(p->x1),&(p->y1),&(p->x2),&(p->y2));
    return(0);
}
#ifdef ZZ_ANSI
int zz_inp_Net(FILE *fp,Net *p) {
#else
int zz_inp_Net(fp,p) FILE *fp; Net *p; {
#endif
    fp=fp; p=p; /* avoid warnings from the compiler */
    return(0);
}
#ifdef ZZ_ANSI
int zz_inp_ActTerm(FILE *fp,ActTerm *p) {
#else
int zz_inp_ActTerm(fp,p) FILE *fp; ActTerm *p; {
#endif
    if(!fgets(buff,BSIZE,fp))return(1);
    sscanf(buff,"%d %d\n",&(p->x),&(p->y));
    return(0);
}
