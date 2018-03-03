/* Test of DOUBLE_TREE: - exactly the same problem as test12a,
 * except that the Node objects are managed from the Organized C
 * allocation pool.
 */

#define ZZmain
#include <stdio.h>
#include "zzincl.h"
#define BSIZE 80
#define ABS(A) ((A)<0 ? (-(A)) : (A))

typedef struct Node Node;
struct Node {
    ZZ_EXT_Node
    int width;
};
ZZ_ORG_DOUBLE_TREE(tree,Node);
ZZ_ORG_PROPERTY(Node);
ZZ_ORG_NAME(name,Node);

char pName[]="atom"; /* all properties have the same name */
FILE *file1,*file2;

/* Declarations to circumvent a Borland C++ 3.0 bug */
#ifdef ZZ_ANSI
    void prt1(char *n,Node *p),prt2(Node *p),prt3(Node *p),menu(void);
    void addAtom(Node *a,char *buff),save(Node *a,char *buff);
    Node *newNode(char *buff),*find(Node *a,Node *b,char *buff);
    Node *nOpen(Node *a,char *buff),*remNode(Node *a);
    Node *search(Node *a,char *nm);
#else
    void prt1(),prt2(),prt3();
    void addAtom(),save(),menu();
    Node *newNode(),*find(),*nOpen(),*remNode();
    Node *search();
#endif

#ifdef ZZ_ANSI
int main(int argc,char **argv)
{
#else


int main(argc,argv)
int argc;
char *argv[];
{
#endif
    char sw,buff[BSIZE],*rn;
    Node *root,*cur,*cp;
    int i;

    if(argc<=1)file1=stdin;  else file1=fopen(argv[1],"r");
    if(argc<=2)file2=stdout; else file2=fopen(argv[2],"w");
     
    /* just for testing, move several objects into the memory pool */
    for(i=0;i<3;i++){
        ZZ_PLAIN_ALLOC(Node,1,cp);
        ZZ_OBJECT_FREE(Node,cp);
    }

    root=(Node *)NULL;
    ZZ_OBJECT_ALLOC(Node,root); /* root of the tree */
    root->width=1;
    ZZ_STRING_ALLOC("root",rn);
    ZZ_ADD(name,root,rn);
    cur=root;
    menu();

    /* loop to read input */
    while(fgets(buff,BSIZE,file1)){
        fprintf(file2,">");
        sscanf(buff,"%c",&sw);
        switch(sw){
            case '?': menu(); break; /* display menu */
            case 'p': prt1("THIS NODE:",cur); break; /* print the current node */
            case 'P': prt2(cur); break; /* print all under this parent */
            case 'T': prt3(root); break; /* print the whole tree */
            case 'U': ZZ_PARENT(tree,cur,cp); /* move up the tree */
                      if(cp==(Node *)NULL)cur=root; else cur=cp;
                      break;
            case 'D': ZZ_CHILD(tree,cur,cur); /* move down the tree */
                      break;
            case 'R': ZZ_FORWARD(tree,cur,cur); break; /* move to the right */
            case 'L': ZZ_BACKWARD(tree,cur,cur); break; /* move to the left */
            case 'r': cur=remNode(cur); break; /* remove the current node */
            case 'C': cp=newNode(buff);
                      ZZ_ADD(tree,cur,cp); 
                      break; /* make a new child */
            case 'I': cp=newNode(buff);
                      ZZ_INSERT(tree,cur,cp);
                      break; /* make a new child */
            case 'A': cp=newNode(buff);
                      ZZ_APPEND(tree,cur,cp);
                      break; /* make a new child */
            case 'F': cp=find(root,cur,buff); /* find node by the name */
                      if(!cp)fprintf(file2,"node not found\n"); else cur=cp;
                      break;
            case 'a': ZZ_DELETE_PROPERTY(cur,pName); /* delete old atom first */
                      addAtom(cur,buff); /* add new atom */
                      break;
            case 'd': ZZ_DELETE_PROPERTY(cur,pName); break; /* delete atom */
            case 'O': root=nOpen(root,buff); break;/* load new tree from disk */
            case 'S': save(root,buff); break; /* save current tree on disk */
            case 'E': strcpy(buff,"S backup");
                      save(root,buff); /* exit with a save */
                      fprintf(file2,"result saved as -backup-\n");
                      ZZ_OBJECT_CLEAR();
                      return(0);
        }
    }
    return(1);
}
/* ------------------------------------------------------------------------ */
#ifdef ZZ_ANSI
void menu(void)
#else
void menu()
#endif
{
    fprintf(file2,"MENU: [n=name,t=type(i|f|s),v=value|string,w=width]\n\n");
    fprintf(file2,"PRINT: p=node, P=level, T=tree, ?=menu\n");
    fprintf(file2,"MOVES: U=up, D=down, L=left, R=right, F=find, E=exit\n");
    fprintf(file2,
            "ADD NODES: C=child|I=insert|A=append (name aWidth aHeight)\n");
    fprintf(file2,"ADD ATOMS:  a=add (int/float/string value)\n");
    fprintf(file2,"DELETE: r=remove node, d=delete atom\n");
    fprintf(file2,"SAVE/RESTORE: S=save|O=open (fileName)\n");
    fprintf(file2,"for a single node use aWidth=0, example: C N1 0\n");
}
/* ------------------------------------------------------------------------ */
/* print the current node */
#ifdef ZZ_ANSI
void prt1(char *label,Node *cur)
#else


void prt1(label,cur)
char *label;
Node *cur;
#endif
{
    char *tp;
    int *ip,num;

    ZZ_FORWARD(name,cur,tp);
    fprintf(file2,"%s %s\n",label,tp);
    ZZ_GET_PROPERTY(tp,cur,pName,ip,num);
    ZZ_PRINT_PROPERTY(file2,tp,pName,ip,num);
}
/* ------------------------------------------------------------------------ */
/* print all nodes under this parent */
#ifdef ZZ_ANSI
void prt2(Node *par)
{
#else


void prt2(par)
Node *par;
{
#endif
    Node *np;

    fprintf(file2,"\n");
    prt1("PARENT:",par);
    ZZ_A_TRAVERSE(tree,par,np){
        prt1("NODE:",np);
    }ZZ_A_END;
}
/* ------------------------------------------------------------------------ */
/* print the whole tree */
#ifdef ZZ_ANSI
void prt3(Node *root)
{
#else


void prt3(root)
Node *root;
{
    void prt3();
#endif
    Node *np;

    ZZ_CHILD(tree,root,np);
    if(np){
        prt2(root);
        ZZ_A_TRAVERSE(tree,root,np){
            prt3(np);
        }ZZ_A_END;
    }
}
/* ------------------------------------------------------------------------ */
/* remove the given node */
#ifdef ZZ_ANSI
Node *remNode(Node *gn)
#else


Node *remNode(gn)
Node *gn; /* given node */
#endif
/* returns replacement for the current node, normally parent */
{
    Node *np,*pp;
    char *nn;

    ZZ_PARENT(tree,gn,pp);
    if(!pp){fprintf(file2,"you cannot remove the root node\n"); return(gn);}
    ZZ_DELETE_PROPERTY(gn,pName);
    ZZ_DELETE(tree,(Node *)NULL,gn);
    ZZ_A_TRAVERSE(tree,gn,np){
        ZZ_DELETE(tree,(Node *)NULL,np);
        ZZ_ADD(tree,pp,np); /* reconnect subtree to the new parent */
    }ZZ_A_END;
    ZZ_DELETE(name,gn,nn);
    ZZ_OBJECT_FREE(Node,gn);
    ZZ_STRING_FREE(nn);
    return(pp);
}
/* ------------------------------------------------------------------------ */
/* create a new node according to the spec given in the buffer */
#ifdef ZZ_ANSI
Node *newNode(char *buff)
#else
Node *newNode(buff)
char *buff;
#endif
{
    Node *np,*pp;
    int n,w,h,i,j,k;
    char c,nm[BSIZE],*sp;

    sscanf(buff,"%c %s %d",&c,nm,&w);
    if(w>0){
        sscanf(buff,"%c %s %d %d",&c,nm,&w,&h);
        n=w*h;
    }
    else n=1;
    ZZ_OBJECT_ALLOC(Node,np);
    if(!np)fprintf(file2,"allocation error in newNode()\n");
    np->width=w;
    ZZ_STRING_ALLOC(nm,sp); /* add name of the node */
    ZZ_ADD(name,np,sp);
    if(n>1){
        for(i=j=k=1;i<=n;i++,j++){
            if(j>w){j-=w; k++;}
            if(h==1)sprintf(buff,"%s[%d]",nm,j);
            else    sprintf(buff,"%s[%d.%d]",nm,j,k);
            ZZ_OBJECT_ALLOC(Node,pp);
            if(!pp)fprintf(file2,"allocation error in newNode()\n");
            pp->width=0;
            ZZ_STRING_ALLOC(buff,sp); /* add name of the node */
            ZZ_ADD(name,pp,sp);
            ZZ_ADD(tree,np,pp);
        }
    }
    return(np);
}
/* ------------------------------------------------------------------------ */
/* find node of the given name - search first at this level, then down,
 * then the whole tree */
#ifdef ZZ_ANSI
Node *find(Node *root,Node *cur,char *buff)
{
#else


Node *find(root,cur,buff)
Node *root; /* root of the tree */
Node *cur;  /* current node */
char *buff; /* one char command plus the name */
/* returns the node found, NULL if not found */
{
#endif
    Node *pp,*np;
    char *nn,nm[BSIZE],c;

    sscanf(buff,"%c %s",&c,nm);

    /* try this level of the hierarchy */
    ZZ_PARENT(tree,cur,pp);
    if(pp){
        ZZ_A_TRAVERSE(tree,pp,np){
            ZZ_FORWARD(name,np,nn);
            if(!strcmp(nn,nm))return(np);
        }ZZ_A_END;
    }
    /* try this tree down */
    np=search(cur,nm); if(np)return(np);
    /* try the whole tree */
    np=search(root,nm); if(np)return(np);
    return((Node *)NULL);
}
/* ------------------------------------------------------------------------ */
/* recursive search for the node with the given name, return NULL if not found*/
#ifdef ZZ_ANSI
Node *search(Node *par,char *nm)
{
#ifdef ZORTECH
    Node *search();
#endif
#else


Node *search(par,nm)
Node *par; /* parent of this level of hierarchy */
char *nm;  /* name to search for */
{
    Node *search();
#endif
    Node *np,*sp;
    char *nn;

    /* check the parent first */
    ZZ_FORWARD(name,par,nn);
    if(!strcmp(nn,nm))return(par);

    /* now try all children and subtrees */
    ZZ_A_TRAVERSE(tree, par,np){
        sp=search(np,nm);
        if(sp)return(sp);
    }ZZ_A_END;
    return((Node *)NULL);
}
/* ------------------------------------------------------------------------ */
/* add atom to the current node */
#ifdef ZZ_ANSI
void addAtom(Node *cur,char *buff)
#else


void addAtom(cur,buff)
Node *cur; /* current node */
char *buff; /* a int/float/string value/string */
#endif
{
    char *tx,type[BSIZE],nm[BSIZE],c;
    int i;
    float f;

    sscanf(buff,"%c %s",&c,type);
    if(!strcmp(type,"int")){
        sscanf(buff,"%c %s %d",&c,type,&i);
        ZZ_SET_PROPERTY(int,cur,pName,&i,1);
    }
    else if(!strcmp(type,"float")){
        sscanf(buff,"%c %s %f",&c,type,&f);
        ZZ_SET_PROPERTY(float,cur,pName,&f,1);
    }
    else if(!strcmp(type,"string")){
        sscanf(buff,"%c %s %s",&c,type,nm);
        tx=nm;
        ZZ_SET_PROPERTY(string,cur,pName,&tx,1);
    }
    else fprintf(file2,"format must be: a int/float/string value/string\n");
}
/* ------------------------------------------------------------------------ */
/* open = load a new tree from the given file */
#ifdef ZZ_ANSI
Node *nOpen(Node *oldRoot,char *buff)
#else
Node *nOpen(oldRoot,buff)
Node *oldRoot;
char *buff; /* syntax: O fileName */
#endif
/* returns the new root */
{
    char *v[1],*t[1],nm[BSIZE],c;
   
    /* remove the old tree */
    v[0]=(char*)oldRoot; t[0]="Node";
    ZZ_CLEAR(1,v,t);

    /* reload the tree from the given file */
    sscanf(buff,"%c %s",&c,nm); /* gets the file name in nm */
    ZZ_OPEN(nm,1,v,t);
    return((Node*)(v[0]));
}
/* ------------------------------------------------------------------------ */
/* save the current tree on disk, in the file with the given name */
#ifdef ZZ_ANSI
void save(Node *root,char *buff)
#else
void save(root,buff)
Node *root;
char *buff; /* syntax: S fileName */
#endif
{
    char *v[1],*t[1],nm[BSIZE],c;
   
    sscanf(buff,"%c %s",&c,nm); /* gets the file name in nm */
    v[0]=(char*)root; t[0]="Node";
    ZZ_SAVE(nm,1,v,t);
}
/* ------------------------------------------------------------------------ */
#include "zzfunc.c"
