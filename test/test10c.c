/* The same problem as test10a.c, but coded with hyper-objects in C++ */

/* Input format: first line: rootX,rootY,minWidth,resist,curDensity
                 other lines: fromX,fromY,toX,toY,current        */

#define ZZmain
#include <stdio.h>
#include "zzincl.h"
#define BSIZE 80
#define ABS(A) ((A)<0 ? (-(A)) : (A))

#ifdef ZORTECH
#define tFLOAT float
#else
#define tFLOAT float
#endif

class Node {
    ZZ_EXT_Node
public:
    int x,y;
    int width;
    tFLOAT current;
    tFLOAT volt;
};

ZZ_HYPER_SINGLE_RING(ring,Node);
ZZ_HYPER_SINGLE_TREE(tree,Node);
ZZ_HYPER_UTILITIES(util);

#ifdef ZZ_ANSI
int main(int argc,char **argv)
{
    void treeCurrent(Node *p,tFLOAT cur);
    void treeVoltage(Node *p,tFLOAT res);
    void printResult(FILE *fp,Node *p);
#else


int main(argc,argv)
int argc;
char *argv[];
{
    FILE *fopen();
    void treeCurrent(),treeVoltage(),printResult();
#endif
    FILE *file1,*file2;
    char buff[BSIZE];
    int x,y,mw;
    tFLOAT resist,cDens;
    Node *np,*nn,*start,*root;

    if(argc<=1)file1=stdin;  else file1=fopen(argv[1],"r");
    if(argc<=2)file2=stdout; else file2=fopen(argv[2],"w");
    
    start=(Node *)NULL; /* start of the ring */
    root=new Node; /* root of the tree */
    root->current=0.0;
    start=ring.add(start,root);
    /* read min.width, spec.resistance and current cDensity */
    fgets(buff,BSIZE,file1);
    sscanf(buff,"%d %d %d %f %f",
                           &(root->x),&(root->y),&(mw),&(resist),&(cDens));
    /* read the description of the network, root first */
    while(fgets(buff,BSIZE,file1)){
       nn=new Node;
       sscanf(buff,"%d %d %d %d %f",&(x),&(y),&(nn->x),&(nn->y),&(nn->current));
       ring_iterator rIter(start);
       for(np= ++rIter; np; np= ++rIter){
	    if(np->x==x&&np->y==y)goto FOUND;
       };
       printf("input error: %d %d not found\n",x,y);
       continue;
FOUND: start=ring.add(start,nn);
       tree.add(np,nn);
       nn->width=mw;
    }
    treeCurrent(root,cDens);
    root->volt=0.0;
    treeVoltage(root,resist);
    printResult(file2,root);
    return(0);
}
/* -------------------------------------------------------- */
#ifdef ZZ_ANSI
void treeCurrent(Node *pp,tFLOAT cDens)
{
#ifdef ZORTECH
    void treeCurrent();
#endif
#else


void treeCurrent(pp,cDens) Node *pp; tFLOAT cDens;
{
    void treeCurrent();
#endif
    Node *cp;
    int w;

    tree_iterator tIter(pp);
    for(cp= ++tIter; cp; cp= ++tIter){
	treeCurrent(cp,cDens);
	pp->current=pp->current+cp->current;
    }
    w=(int)(pp->current/cDens);
    if(w>pp->width)pp->width=w;
}
/* -------------------------------------------------------- */
#ifdef ZZ_ANSI
void treeVoltage(Node *pp,tFLOAT resist)
{
#ifdef ZORTECH
    void treeVoltage();
#endif
#else


void treeVoltage(pp,resist) Node *pp; tFLOAT resist;
{
    void treeVoltage();
#endif
    tFLOAT sr; /* segment resistance */
    Node *cp;

    tree_iterator tIter(pp);
    for(cp= ++tIter; cp; cp= ++tIter){
	sr=(ABS(cp->x-pp->x)+ABS(cp->y-pp->y))*resist/cp->width;
	cp->volt=pp->volt+cp->current*sr;
	treeVoltage(cp,resist);
    }
}
/* -------------------------------------------------------- */
#ifdef ZZ_ANSI
void printResult(FILE *file2,Node *pp)
{
#ifdef ZORTECH
    void printResult();
#endif
#else
void printResult(file2,pp) FILE *file2; Node *pp;
{
    void printResult();
#endif
    Node *cp;

    tree_iterator tIter(pp);
    for(cp= ++tIter; cp; cp= ++tIter){
        fprintf(file2,"from (%d,%d) to (%d,%d) cur=%f width=%d volt=%f\n",
	   pp->x,pp->y,cp->x,cp->y,cp->current,cp->width,cp->volt);
        printResult(file2,cp);
    }
}
#include "zzfunc.c"
