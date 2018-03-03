/* This is the same example as test0a.c, except that generic
 * functions ZZ_ADD and ZZadd are used, and ZZselectMacros is
 * used to generate the reduced zzcomb.h in the current directory.
 * Also, the whole organization is saved on disk, then destroyed
 * in memory, restored, and the results are calculated from there.
 * This is a fairly good test of ZZ_SAVE() and ZZ_OPEN().
 * The result must be identical with test0a.c
 * The program also tests ZZ_MODE_SAVE() by declaring the saving
 * mode in ASCII, but then overwriting it to the binary format.
 *
 * For the purpose of testing, the names are not handled in the standard,
 * correct and save way. The program assumes that the names are permanently
 * in memory, regardless of SAVE/OPEN.
 *  The proper way of handling names in this case would be to use
 * the organization of NAME.
 *
 * ZORTECH 2.0 compiler has a problem with this test. Functions zz_inp_..
 * are declared but not used, and the linker seems they are missing.
 * Compare this problem with test0d, which is exactly the same, except that
 * these functions are used (ASCII save) - and that runs fine with ZORTECH.
 */

#include <stdio.h>
#define ZZmain
#define ZZascii
#define ZZselectMacros
#include "zzincl.h"

typedef struct Block Block;
typedef struct Net Net;
typedef struct Pin Pin;

struct Block {
    ZZ_EXT_Block    /* let the program to hide the pointers here */
    char *name;
    int x1,y1,x2,y2; /* corners of the block */
};

struct Net {
    ZZ_EXT_Net    /* let the program to hide the pointers here */
    char *name;
};

struct Pin {
    ZZ_EXT_Pin    /* let the program to hide the pointers here */
    int x1,y1,x2,y2; /* pin, relative to the block lower-left corner  */
};

#define INF 10000
#define MAX(A,B) ((A)<(B) ? (B) : (A))
#define MIN(A,B) ((A)>(B) ? (B) : (A))
#define BSIZE 80
static char name[BSIZE],buff[BSIZE];

ZZ_ORG_SINGLE_RING(bChain,Block);
ZZ_ORG_SINGLE_RING(nChain,Net);
ZZ_ORG_SINGLE_TRIANGLE(byBlock,Block,Pin);
ZZ_ORG_SINGLE_TRIANGLE(byNet,Net,Pin);

#define BSIZE 80

#ifdef ZZ_ANSI
int main(int argc,char **argv)
#else


int main(argc,argv)
int argc;
char *argv[];
#endif
{
    int x1,y1,x2,y2;
    char c,*nn,*v[2],*t[2];
    FILE *file1,*file2;
    Block *bp,*br,*bStart;
    Net *np,*nStart;
    Pin *pp,*pr;
#ifdef ZZ_ANSI
    void myFun(char *obj, int type, int size, char *priv);
#else
    FILE *fopen();
    void myFun();
#endif

    if(argc<=1)file1=stdin;  else file1=fopen(argv[1],"r");
    if(argc<=2)file2=stdout; else file2=fopen(argv[2],"w");
 
    /* use binary format for SAVE/OPEN */
    ZZ_MODE_SAVE(0,0,0,0);

    bStart=(Block *)NULL; nStart=(Net *)NULL;
    while(fgets(buff,BSIZE,file1)){
        sscanf(buff,"%c %s %d %d %d %d",&c,name,&x1,&y1,&x2,&y2);
        if(c=='B'){
            ZZ_PLAIN_ALLOC(Block,1,bp);
            ZZ_STRING_ALLOC(name,nn);
            bp->name=nn; bp->x1=x1; bp->y1=y1; bp->x2=x2; bp->y2=y2;
            ZZ_ADD(bChain,bStart,bp);
        }
        else if(c=='P'){
            ZZ_PLAIN_ALLOC(Pin,1,pp);
            pp->x1=x1; pp->y1=y1; pp->x2=x2; pp->y2=y2;
            /* is this net already listed ? */
            ZZ_A_TRAVERSE_SINGLE_RING(nChain,nStart,np){
                if(!strcmp(name,np->name))goto N_LOOP;
            }ZZ_A_END;
            ZZ_PLAIN_ALLOC(Net,1,np);
            ZZ_STRING_ALLOC(name,nn);
            np->name=nn;
            ZZadd(nChain,nStart,np);
N_LOOP:
            ZZadd(byBlock,bp,pp);
            ZZ_ADD(byNet,np,pp);
        }
    }
    fclose(file1);

    v[0]=(char*)bStart; v[1]=(char*)nStart;
    t[0]="Block";       t[1]="Net";
    ZZ_SAVE("sfile",2,v,t);
    ZZ_CLEAR(2,v,t);
    ZZ_OPEN("sfile",2,v,t);
    bStart=(Block*)v[0];
    nStart=(Net*)v[1];

    /* for all blocks, print the x-span of all connected nets */
    ZZ_A_TRAVERSE(bChain,bStart,bp){
        fprintf(file2,"block=%s nets=",bp->name);
        ZZ_A_TRAVERSE(byBlock,bp,pp){
            ZZ_PARENT(byNet,pp,np);
            x1=INF; x2= -INF;
            ZZ_A_TRAVERSE(byNet,np,pr){
                ZZ_PARENT(byBlock,pr,br);
                x1=MIN(x1,br->x1 + pr->x1);
                x2=MAX(x2,br->x1 + pr->x2);
            }ZZ_A_END;
            fprintf(file2," %s(%d,%d)",np->name,x1,x2);
        }ZZ_A_END;
        fprintf(file2,"\n");
    }ZZ_A_END;
    fprintf(file2,"\n");

    /* test the sweap function */
    v[0]=(char*)bStart; v[1]=(char*)nStart;
    t[0]="Block";       t[1]="Net";
    ZZ_SWEEP_SET(2,v,t);
    ZZ_SWEEP_FUNCTION(myFun,(char*)file2);
    return(0);
}
/* --------------------------------------- */
/* function to print one object */
#ifdef ZZ_ANSI
void myFun(char *obj,int typeInd,int size,char *priv)
#else


void myFun(obj,typeInd,size,priv)
char *obj;
int typeInd;
int size;
char *priv;
#endif
{
    FILE *fp;
    char *type;
    Block *bp;
    Net *np;
    Pin *pp;

    fp=(FILE *)priv;
    ZZ_TYPE_NAME(typeInd,type);
    if(!strcmp(type,"Block")){
        bp=(Block*)obj;
        fprintf(fp,"Block %s size=%d\n",bp->name,size);
    }
    else if(!strcmp(type,"Net")){
        np=(Net*)obj;
        fprintf(fp,"Net %s size=%d\n",np->name,size);
    }
    else {
        pp=(Pin*)obj;
        fprintf(fp,"Pin (%d,%d %d,%d) size=%d\n",
                   pp->x1,pp->y1,pp->x2,pp->y2,size);
    }
}
#include "zzfunc.c"
/* ===================================================== */
/* The following functions are really not necessary, but they
 * must be formally declared (at least as dummies) or ZZ_FORMAT must
 * be used (which generates them automatically) since we specified
 * ZZascii, even though we are using the binary format.
 */
#ifdef ZZ_ANSI
int zz_out_Pin(FILE *fp,Pin *p){
    fprintf(fp,"%d %d %d %d\n",p->x1,p->y1,p->x2,p->y2);
    return(0);
}
int zz_out_Net(FILE *fp,Net *p){
    fprintf(fp,"%s\n",p->name);
    return(0);
}
int zz_out_Block(FILE *fp,Block *p){
    fprintf(fp,"%s %d %d %d %d\n",p->name,p->x1,p->y1,p->x2,p->y2);
    return(0);
}
int zz_inp_Pin(FILE *fp,Pin *p){
    if(!fgets(buff,BSIZE,fp))return(1);
    sscanf(buff,"%d %d %d %d\n",&(p->x1),&(p->y1),&(p->x2),&(p->y2));
    return(0);
}
int zz_inp_Net(FILE *fp,Net *p){
    if(!fgets(buff,BSIZE,fp))return(1);
    sscanf(buff,"%s\n",name);
    ZZ_STRING_ALLOC(name,p->name);
    if(!(p->name))printf("name alloc error %s\n",name);
    return(0);
}
int zz_inp_Block(FILE *fp,Block *p){
    if(!fgets(buff,BSIZE,fp))return(1);
    sscanf(buff,"%s %d %d %d %d\n",name,&(p->x1),&(p->y1),&(p->x2),&(p->y2));
    ZZ_STRING_ALLOC(name,p->name);
    if(!(p->name))printf("name alloc error %s\n",name);
    return(0);
}
#else
int zz_out_Pin(fp,p) FILE *fp; Pin *p; {
    fprintf(fp,"%d %d %d %d\n",p->x1,p->y1,p->x2,p->y2);
    return(0);
}
int zz_out_Net(fp,p) FILE *fp; Net *p; {
    fprintf(fp,"%s\n",p->name);
    return(0);
}
int zz_out_Block(fp,p) FILE *fp; Block *p; {
    fprintf(fp,"%s %d %d %d %d\n",p->name,p->x1,p->y1,p->x2,p->y2);
    return(0);
}
int zz_inp_Pin(fp,p) FILE *fp; Pin *p; {
    if(!fgets(buff,BSIZE,fp))return(1);
    sscanf(buff,"%d %d %d %d\n",&(p->x1),&(p->y1),&(p->x2),&(p->y2));
    return(0);
}
int zz_inp_Net(fp,p) FILE *fp; Net *p; {
    if(!fgets(buff,BSIZE,fp))return(1);
    sscanf(buff,"%s\n",name);
    ZZ_STRING_ALLOC(name,p->name);
    if(!(p->name))printf("name alloc error %s\n",name);
    return(0);
}
int zz_inp_Block(fp,p) FILE *fp; Block *p; {
    if(!fgets(buff,BSIZE,fp))return(1);
    sscanf(buff,"%s %d %d %d %d\n",name,&(p->x1),&(p->y1),&(p->x2),&(p->y2));
    ZZ_STRING_ALLOC(name,p->name);
    if(!(p->name))printf("name alloc error %s\n",name);
    return(0);
}
#endif
