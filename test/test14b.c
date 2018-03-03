/* Input format:
 *   O file = open network from a file;
 *   E file = exit and store the network on a file;
 *   S stateName gas = introduce new state;
 *   T stateName townName = introduce new town;
 *   H town1Name town2Name distance = add highway;
 *   h town1Name town2Name = delete highway;
 *   A town1Name town2Name cost = add air link;
 *   a town1Name town2Name = delete air link;
 *   R town1Name town2Name = find 2 routes and print them;
 * No sophisticated searches for names, just linear searches.
 */
#define ZZmain
#define ZZascii
#include <stdio.h>
#include "zzincl.h"

typedef struct State State;
typedef struct Town Town;
typedef struct Highway Highway;
typedef struct AirLink AirLink;
typedef struct Header Header;
struct State {
    ZZ_EXT_State
    float gas; /* gas price per mile */
};
ZZ_FORMAT(State,"%f,gas");
struct Town {
    ZZ_EXT_Town
    float cost;         /* for the algorithm */
    struct Town *trace; /* route traceback */
};
ZZ_FORMAT(Town,"%f,cost");
struct Highway {
    ZZ_EXT_Highway
    int distance;
};
ZZ_FORMAT(Highway,"%d,distance");
struct AirLink {
    ZZ_EXT_AirLink
    float fare;
};
ZZ_FORMAT(AirLink,"%f,fare");
struct Header {  /* header for the heap */
    ZZ_EXT_Header
};
ZZ_FORMAT(Header,"");
ZZ_ORG_SINGLE_RING(states,State);
ZZ_ORG_SINGLE_TRIANGLE(byState,State,Town);
ZZ_ORG_SINGLE_GRAPH(hwy,Town,Highway);
ZZ_ORG_SINGLE_GRAPH(air,Town,AirLink);
ZZ_ORG_NAME(sName,State); /* name stored as a part of the organization */
ZZ_ORG_NAME(tName,Town);  /* name stored as a part of the organization */
ZZ_ORG_ARRAY(heap,Header,Town*); /* heap for the routing algorithm */

/* dummy call-back function for heap, not needed here */
#ifdef ZZ_ANSI
void bck(void*,int);
void bck(void *p,int i){p=p; i=i;}
#else
void bck();
void bck(p,i)void *p; int i;{p=p; i=i;}
#endif

#define BSIZE 80
static char buff[BSIZE],name1[BSIZE],name2[BSIZE];
static Header *head;
#define INF 1.e30
static FILE *file1,*file2;
#ifndef ZZ_ANSI
FILE *fopen();
#endif

/* Declaration to circumvent bug in BorlandC++ 3.0 */
#ifdef ZZ_ANSI
    void hwyExpand(Town **t),airExpand(Town **t),prtRoute(char *lbl,Town *t);
    Town *search(State *s,char *nm);
    int init(State *s);
    State *stOpen(State *s),*newState(State *s),*newTown(State *s);
    void save(State *s),newHwy(State *s),newAir(State *s);
    void route2(State *s),del1(State *s);
    int heapSort(const void *p1,const void *p2);
#else
    void hwyExpand(),airExpand(),prtRoute();
    Town *search();
    int init();
    State *stOpen(),*newState(),*newTown();
    void save(),newHwy(),newAir(),route2(),del1();
    int heapSort();
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
    char sw;
    State *sStart;

    if(argc<=1)file1=stdin;  else file1=fopen(argv[1],"r");
    if(argc<=2)file2=stdout; else file2=fopen(argv[2],"w");

    ZZ_PLAIN_ALLOC(Header,1,head) /* prepare header for the heap */

    sStart=(State *)NULL; /* start with no State */
    /* loop to read input */
    while(fgets(buff,BSIZE,file1)){
        sscanf(buff,"%c",&sw);
        switch(sw){
            case 'S': sStart=newState(sStart); break; /* new state */
            case 'T': sStart=newTown(sStart); break; /* new town */
            case 'H': newHwy(sStart); break; /* new highway */
            case 'h': del1(sStart); break; /* delete highway */
            case 'A': newAir(sStart); break; /* new air connection */
            case 'a': del1(sStart); break; /* delete air connection */
            case 'R': route2(sStart); break; /* print 2 routes */
            case 'O': sStart=stOpen(sStart); break; /* open old network */
            case 'E': save(sStart); return(0); /* save and exit */
            default:  fprintf(file2,"wrong control=%c\n",sw); break;
        }
    }
    return(1);
}
/* ------------------------------------------------------------------------ */
/* introduce new state, input is in buff, return new start of the ring */
#ifdef ZZ_ANSI
State *newState(State *start)
#else


State *newState(start)
State *start; /* old start of the ring */
#endif
{
    State *sp,*ss;
    char c,*np;
    float gas;

    sscanf(buff,"%c %s %f",&c,name1,&gas); 
    sp=(State *)NULL;
    ZZ_A_TRAVERSE(states,start,ss){ /* is this State already recorded? */
        ZZ_FORWARD(sName,ss,np)
        if(!strcmp(name1,np)){sp=ss; ZZ_A_BREAK;}
    }ZZ_A_END
    if(sp){ /* State already in, only reset gas */
        sp->gas=gas;
        return(start);
    }
    ZZ_PLAIN_ALLOC(State,1,sp); /* allocate 1 State */
    sp->gas=gas;
    ZZ_STRING_ALLOC(name1,np); /* allocate name */
    ZZ_ADD(sName,sp,np); /* add name to the state */
    ZZ_ADD(states,start,sp);
    return(start);
}
/* ------------------------------------------------------------------------ */
/* introduce new town, input is in buff. Warning: may introduce new State */
#ifdef ZZ_ANSI
State *newTown(State *start)
{
#else


State *newTown(start)
State *start; /* start of the state ring */
{
#endif
    State *sp,*ss;
    Town *tp;
    char c,*np;

    sscanf(buff,"%c %s %s",&c,name1,name2);
    tp=search(start,name2); /* check whether the town already recorded */
    if(tp){
        fprintf(file2,"possible error, town=%s recorded twice\n",name2);
        return(start);
    }
    ZZ_PLAIN_ALLOC(Town,1,tp); /* allocate 1 State */
    sp=(State *)NULL;
    ZZ_A_TRAVERSE(states,start,ss){ /* search for the state */
        ZZ_FORWARD(sName,ss,np)
        if(!strcmp(name1,np)){sp=ss; ZZ_A_BREAK;}
    }ZZ_A_END
    if(!sp){ /* the state is not in yet - gas 0.0 by initialization */
        ZZ_PLAIN_ALLOC(State,1,sp); /* allocate 1 State */
        ZZ_STRING_ALLOC(name1,np); /* allocate name */
        ZZ_ADD(sName,sp,np); /* add name to the state */
        ZZ_ADD(states,start,sp);
    }
    ZZ_STRING_ALLOC(name2,np); /* allocate name */
    ZZ_ADD(tName,tp,np); /* add name to the town */
    ZZ_ADD(byState,sp,tp); /* add town to the state */
    return(start);
}
/* ------------------------------------------------------------------------ */
/* search for the town of the given name, return NULL if not found */
#ifdef ZZ_ANSI
Town *search(State *start,char *name)
#else
Town *search(start,name)
State *start; /* start of the ring of all states */
char *name;          /* given name */
#endif
{
    State *sp;
    Town *tp;
    char *np;

    ZZ_A_TRAVERSE(states,start,sp){   /* traverse all states */
        ZZ_A_TRAVERSE(byState,sp,tp){ /* traverse towns under state sp */
            ZZ_FORWARD(tName,tp,np); /* get name of town tp */
            if(!strcmp(name,np))return(tp);
        }ZZ_A_END
    }ZZ_A_END
    return((Town *)NULL);
}
/* ------------------------------------------------------------------------ */
/* add new highway */
#ifdef ZZ_ANSI
void newHwy(State *start)
{
#else


void newHwy(start)
State *start; /* start of all states */
{
#endif
    char c;
    Highway *hp;
    Town *tp[2];
    int dist;

    sscanf(buff,"%c %s %s %d",&c,name1,name2,&dist);
    tp[0]=search(start,name1); /* search for the first town */
    tp[1]=search(start,name2); /* search for the second town */
    if(!tp[0] || !tp[1]){
        fprintf(file2,"cannot find towns %s %s\n",name1,name2);
        return;
    }
    ZZ_PLAIN_ALLOC(Highway,1,hp); /* allocate 1 State */
    hp->distance=dist;
    ZZ_ADD(hwy,tp,hp); /* add highway between the two towns */
    return;
}
/* ------------------------------------------------------------------------ */
/* add new air link */
#ifdef ZZ_ANSI
void newAir(State *start)
{
#else


void newAir(start)
State *start; /* start of all states */
{
#endif
    char c;
    AirLink *ap;
    Town *tp[2];
    float fare;

    sscanf(buff,"%c %s %s %f",&c,name1,name2,&fare);
    tp[0]=search(start,name1); /* search for the first town */
    tp[1]=search(start,name2); /* search for the second town */
    if(!tp[0] || !tp[1]){
        fprintf(file2,"cannot find towns %s %s\n",name1,name2);
        return;
    }
    ZZ_PLAIN_ALLOC(AirLink,1,ap); /* allocate 1 State */
    ap->fare=fare;
    ZZ_ADD(air,tp,ap); /* add air connection between the two towns */
    return;
}
/* ------------------------------------------------------------------------ */
/* delete air link */
#ifdef ZZ_ANSI
void del1(State *start)
{
#else


void del1(start)
State *start; /* start of all states */
{
#endif
    char c;
    Town *tp[2];

    sscanf(buff,"%c %s %s",&c,name1,name2);
    tp[0]=search(start,name1); /* search for the first town */
    tp[1]=search(start,name2); /* search for the second town */
    if(!tp[0] || !tp[1]){
        fprintf(file2,"cannot find towns %s %s\n",name1,name2);
        return;
    }
    if(c=='a')ZZ_DELETE(air,tp,(AirLink *)NULL) /* delete air connection connection */
    else      ZZ_DELETE(hwy,tp,(Highway *)NULL) /* delete a highway */
    return;
}
/* ------------------------------------------------------------------------ */
/* cancel the current network, if any, and open backup */
#ifdef ZZ_ANSI
State *stOpen(State *start)
#else
State *stOpen(start)
State *start; /* start of all states */
#endif
{
    char *v[1],*t[1],c;
   
    /* remove the old network */
    if(start){
        v[0]=(char*)start; t[0]="State";
        ZZ_CLEAR(1,v,t)
    }

    /* reload the tree from the given file */
    sscanf(buff,"%c %s",&c,name1); /* get the file name in name1 */
    ZZ_OPEN(name1,1,v,t)
    return((State *)(v[0]));
}
/* ------------------------------------------------------------------------ */
/* save the current tree on the given file */
#ifdef ZZ_ANSI
void save(State *start)
#else


void save(start)
State *start;
#endif
{
    char *v[1],*t[1],c;
   
    sscanf(buff,"%c %s",&c,name1); /* get the file name in name1 */
    v[0]=(char*)start; t[0]="State";
    if(start)ZZ_SAVE(name1,1,v,t)
    else fprintf(file2,"no data in - nothing to save\n");
}
/* ------------------------------------------------------------------------ */
/* find two alternate routes between two towns, and print them */
#ifdef ZZ_ANSI
void route2(State *start)
{
#else
void route2(start)
State *start; /* start of the ring of all states */
{
#endif
    char c;
    Town *tp[2],**arr;
    int n;

    sscanf(buff,"%c %s %s",&c,name1,name2);
    tp[0]=search(start,name1);
    tp[1]=search(start,name2);
    if(!tp[0] || !tp[1]){
        fprintf(file2,"cannot find towns %s %s\n",name1,name2);
        return;
    }
    if(tp[0]==tp[1]){fprintf(file2,"..are you joking?\n"); return;}
    n=init(start); /* initialize town cost and traceback, count towns */
    ZZ_FORM_ARRAY(heap,head,n,n,arr) 
    hwyExpand(tp);
    prtRoute("hwy",tp[1]);
    ZZ_RESET_ARRAY(heap,head,-1,n)
    n=init(start); /* initialize town cost and traceback, count towns */
    airExpand(tp);
    prtRoute("air",tp[1]);
    ZZ_FREE_ARRAY(heap,head)
}
/* ------------------------------------------------------------------------ */
/* find the least expensive air route between two towns */
#ifdef ZZ_ANSI
void airExpand(Town **tp)
{
#else


void airExpand(tp)
Town *tp[];
{
#endif
    int n,w,i;
    Town *tt,*tv[2];
    AirLink *ap;

    tp[0]->cost=0.0;
    ZZ_IN_HEAP(heap,heapSort,head,&(tp[0]),bck)
    for(;;){ /* main expansion loop */
        ZZ_SIZE_ARRAY(heap,head,n,w,i) /* returns watermark<0 when empty */
        if(w<0)return; /* heap empty */
        w=n; w=i;/* does nothing, just shuts up compiler messages */
        ZZ_OUT_HEAP(heap,heapSort,head,&tt,bck)
        if(tt->cost>=tp[1]->cost)return; /* no sense to expand more */
        tv[0]=tt;
        ZZ_A_TRAVERSE(air,tv,ap){
            if(tv[1]->cost>tt->cost+ap->fare){
                tv[1]->cost=tt->cost+ap->fare;
                tv[1]->trace=tt;
                ZZ_IN_HEAP(heap,heapSort,head,&(tv[1]),bck)
            }
        }ZZ_A_END
    }
}
/* ------------------------------------------------------------------------ */
/* find the least expensive hwy route between two towns */
#ifdef ZZ_ANSI
void hwyExpand(Town **tp)
{
#else


void hwyExpand(tp)
Town *tp[];
{
#endif
    int n,w,i;
    Town *tt,*tv[2];
    State *sp;
    Highway *hp;
    float diff;

    tp[0]->cost=0.0;
    ZZ_IN_HEAP(heap,heapSort,head,&(tp[0]),bck)
    for(;;){ /* main expansion loop */
        ZZ_SIZE_ARRAY(heap,head,n,w,i) /* returns watermark<0 when empty */
        if(w<0)return; /* heap empty */
        w=n; w=i;/* does nothing, just shuts up compiler messages */
        ZZ_OUT_HEAP(heap,heapSort,head,&tt,bck)
        if(tt->cost>=tp[1]->cost)return; /* no sense to expand more */
        ZZ_PARENT(byState,tt,sp)
        tv[0]=tt;
        ZZ_A_TRAVERSE(hwy,tv,hp){
            diff=(hp->distance)*(sp->gas);
            if(tv[1]->cost>tt->cost+diff){
                tv[1]->cost=tt->cost+diff;
                tv[1]->trace=tt;
                ZZ_IN_HEAP(heap,heapSort,head,&(tv[1]),bck)
            }
        }ZZ_A_END
    }
}
/* ------------------------------------------------------------------------ */
/* compare function to sort the heap of Town pointers */
#ifdef ZZ_ANSI
int heapSort(const void *s1,const void *s2)
#else
int heapSort(s1,s2) void *s1,*s2;
#endif
{
    Town **p1,**p2;

    p1=(Town **)s1; p2=(Town **)s2;
    if((*p1)->cost<(*p2)->cost)return(-1);
    if((*p1)->cost>(*p2)->cost)return(1);
    return(0);
}
/* ------------------------------------------------------------------------ */
/* initialize all towns for routing, return number of towns */
#ifdef ZZ_ANSI
int init(State *start)
#else
int init(start)
State *start; /* start of all states */
#endif
{
    int n;
    State *sp;
    Town *tp;

    n=0;
    ZZ_A_TRAVERSE(states,start,sp){
        ZZ_A_TRAVERSE(byState,sp,tp){
            n++;
            tp->trace=(Town *)NULL;
            tp->cost=INF;
        }ZZ_A_END
    }ZZ_A_END
    return(n);
}
/* ------------------------------------------------------------------------ */
/* print one route */
#ifdef ZZ_ANSI
void prtRoute(char *label,Town *st)
#else
void prtRoute(label,st)
char *label; /* label for the print */
Town *st; /* start of the trace */
#endif
{
    Town *tp;
    char *np;

    fprintf(file2,"%s: ",label);
    if(!(st->trace)){fprintf(file2,"no connection\n"); return;}
    for(tp=st; tp; tp=tp->trace){
        ZZ_FORWARD(tName,tp,np)
        fprintf(file2,"%s ",np);
    }
    fprintf(file2," cost=%f\n",st->cost);
    return;
}
/* ------------------------------------------------------------------------ */
#include "zzfunc.c"
