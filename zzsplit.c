/* Program to read file zzfunc.c and split it into sections
 * separated by special ifdef statements.
 * The purpose of this program is to provide a spliting
 * facility for environments, where file zzfunc.c may
 * be too big for the compiler to handle, especially for
 * larger projects.
 *
 * Calling sequence:  zzplit zzfunc.c zzfun.c inp
 * where
 *        zzfunc.c is the original (normal) zzfunc.c file
 *                 default: zzfunc.c
 *        zzfun.c  is the new file with special ifdefs
 *                 default: zzfun.c
 *        inp      is the input file containing one number
 *                 (= required number of sections)
 *                 default: stdin
 *
 * If the file cannot split into that many sections,
 * some of the end-sections may be missing (be empty).
 */
#include <stdio.h>
#include <stdlib.h>
#include "environ.h"

#ifdef VMS
#include "[.lib]heading.h"
#else
#ifdef MAC
#include ":lib:heading.h"
#else
#include "lib/heading.h"
#endif
#endif

#ifdef ZZ_ANSI
void msgS(int,const char*);
#else
void msgS();
#endif

typedef struct Block Block;
struct Block {   /* one for each section */
    Block *next; /* linked list */
    int size;    /* size in number of lines */
    int sect;    /* section assigned */
}*head,*tail;

#define MARK "----"
#define BS 256
#ifdef ZZ_ANSI
int main(int argc,char **argv)
#else

int main(argc,argv)
int argc;
char *argv[];
#endif
{
    FILE *f1,*f2,*f3,*f4;
    char *fn,buff[BS];
    int i,nSect,nBlock,nLine,targSize,fill;
    Block *bp;
#ifndef ZZ_ANSI
    FILE *fopen();
#endif

    if(argc<=1)fn=(char*)"zzfunc.c";else fn=argv[1];
    f1=fopen(fn,"r");
    if(!f1){msgS(0,fn); return(1);}
    if(argc<=2)fn=(char*)"zzfun.c"; else fn=argv[2];
    f2=fopen(fn,"w");
    if(!f2){msgS(0,fn); return(1);}
    if(argc<=3)f3=stdin;  else f3=fopen(argv[3],"r");
    if(!f3){msgS(0,"file with the number of sections"); return(1);}

    /* record Blocks and their sizes */
    head=tail=NULL;
    for(nLine=nBlock=0; fgets(buff,BS,f1); nLine++){
        if(!tail || !strncmp(MARK,&(buff[3]),4)){
            bp=(Block *)malloc(sizeof(struct Block));
            if(!bp){msgS(1,"small internal data\n"); return(2);}
            bp->size=0;
            if(!head)head=bp;
            else tail->next=bp;
            tail=bp;
            bp->next=NULL;
            nBlock++;
        }
        (bp->size)++;
    }
    rewind(f1);

    /* get the requested number of sections, default = 1 */
    if(fgets(buff,BS,f3))sscanf(buff,"%d",&nSect);
    else {msgS(2,""); return(4);}
    if(nSect<=0)return(3);
    
    /* spliting algorithm */
    for(bp=head, fill=0, i=1; bp; bp=bp->next){
        targSize=nLine/nSect;
        fill+=bp->size;
        if(fill>targSize && fill!=bp->size && nSect>1 && fill>(int)(1.5*bp->size)){
            i++;
            nSect--;
            fill=bp->size;
        }
        bp->sect=i;
        nLine=nLine - bp->size;
    }
    
    /* generate the final output */
    fprintf(f2,"#ifdef SECTION1\n");
    for(bp=head; bp; bp=bp->next){
        for(i=0;i<bp->size;i++){
            if(fgets(buff,BS,f1))fprintf(f2,"%s",buff);
            else break;
        }
        if(bp->next && bp->sect!=bp->next->sect){
            fprintf(f2,"#endif\n");
            fprintf(f2,"#ifdef SECTION%d\n",bp->next->sect);
        }
    }
    fprintf(f2,"#endif\n");
    return(0);
}
/* ------------------------------------------------------- */
#ifdef ZZ_ANSI
void msgS(int i,const char *p){

#else
void msgS(i,p)int i; char *p;{
#endif
    switch(i){
        case 0: printf("problem to open file: %s\n",p); break;
        case 1: printf("allocation problem: %s\n",p); break;
        case 2: printf("number of sections must be given\n");
        default: printf("wrong error code=%d, msgS\n",i); break;
    }
}
