/* Test of undirected graph, hash table, and single ring,
 * using hyper-objects.
 * This is the same problem as test25b.c, but undirected
 * graph is used to store the data. When traversing, the
 * direction of the edge is derived from the order of the
 * end nodes.
 *   This program also tests processing of large input
 * files by zzprep, using 'ZZbreakLine' as a mark for
 * segments to be processed seperately.
 *   Except for that, between test25b.c and this program,
 *  only 3 lines are different. Search for comment with ??? to find them.
 */
#include <stdio.h>
#define ZZmain
#define ZZnoDestr
#include "zzincl.h"
#define hashSize 23

class header {
    ZZ_EXT_header
};

class stelle {
    ZZ_EXT_stelle
public:
    char *name;
};

class knupfen {
    ZZ_EXT_knupfen
public:
	int gewicht;
	char rueckkehr; /* controls the backtrack */
};
ZZbreakLine

class ergebnis {
   ZZ_EXT_ergebnis
public:
        stelle *von;
        stelle *bis;
	int  kante;
};

ZZ_HYPER_HASH(sHash,header,stelle);
ZZ_HYPER_SINGLE_RING(eRing,ergebnis);
ZZbreakLine
ZZ_HYPER_SINGLE_GRAPH(graph,stelle,knupfen); /* ??? different  graph */
ZZ_HYPER_UTILITIES(util);

knupfen *pfad_start;
stelle *stelle_list;
ergebnis *bt_start;
header *hp;
int main(void)
{
    stelle *von,*bis;
    void verbindung(stelle *von,stelle *bis);
    void anseigen(stelle *bis);
    void setup(void);
    stelle *suchStelle(char *name);
    stelle *eingabe(char *name);
    void anzeigen(stelle *bis);

    hp=new header;
    stelle_list=(stelle *)NULL;
    pfad_start=(knupfen *)NULL;
    setup();
    bt_start=(ergebnis *)NULL;
    von=eingabe((char*)"from? ");
    bis=eingabe((char*)"to?   ");
    verbindung(von,bis);
    anzeigen(bis);
    return(0);
}
/* The main depth-first algorithm */
void verbindung(stelle *von,stelle *bis)
{
	int d,kante;
	stelle *beliebiger_punkt;
	int vergleichen(stelle *von,stelle *bis);
	void eintragen(stelle *von,stelle *bis,int d);
	int fest_legen(stelle *von,stelle **beliebiger_punkt);
	void entfernen(stelle **von,stelle **bis,int *kante);

	d=vergleichen(von,bis);

	if(d) { /* target point reached */
		eintragen(von,bis,d);
		return;
	}
        /* try an alternate path */
	kante=fest_legen(von,&beliebiger_punkt);
	if(kante) {
		eintragen(von,bis,kante);
		verbindung(beliebiger_punkt,bis);
	}
	else if(bt_start) { /* return back */
		entfernen(&von,&bis,&kante);
		verbindung(von,bis);
     	}
}
/* Verify validity of an end-point, and convert it to a pointer */
stelle *eingabe(char *frage)
{
        stelle *sp,*pruef(char *);
        char name[20]; /* buffer to input start/end node */

        for(sp=(stelle *)NULL; !sp;){
		printf(frage);
		gets(name);
		sp=pruef(name);
		if(!sp)printf("Invalid name, please correct\n");
	}
	return(sp);
}
/* Is this node part of the set? */ 
stelle *pruef(char *name)
{
    stelle *sp,ss;

    ss.name=name;
    sp=sHash.get(hp,&ss);
    return(sp);
}
/* setup the task including the stelle_list */
void setup(void)
{
	void kante_eintragen(char *,char *,int);
        
        sHash.form(hp,hashSize);
	kante_eintragen((char*)"a1",(char*)"a2",10);
	kante_eintragen((char*)"a2",(char*)"a3",10);
	kante_eintragen((char*)"a1",(char*)"c1",8);
	kante_eintragen((char*)"a1",(char*)"a3",19);
	kante_eintragen((char*)"c1",(char*)"b2",15);
	kante_eintragen((char*)"c1",(char*)"c3",18);
	kante_eintragen((char*)"c1",(char*)"a2",5);
	kante_eintragen((char*)"a3",(char*)"c2",10);
	kante_eintragen((char*)"a3",(char*)"b1",15);
	kante_eintragen((char*)"b1",(char*)"c3",15);
	kante_eintragen((char*)"a3",(char*)"c3",10);
	kante_eintragen((char*)"b1",(char*)"b3",7);
	kante_eintragen((char*)"a3",(char*)"b3",12);
}
/* Add a new edge to the graph */
void kante_eintragen(char *von,char *bis,int kante)
{
        stelle *s[2],*suchStelle(char *);
        knupfen *kp;

        kp=new knupfen;
	s[0]=suchStelle(von);
	s[1]=suchStelle(bis);
	kp->gewicht=kante;
	kp->rueckkehr=0;
        graph.add(s,kp);
        graph.del(kp);  // ??? delete and add it again just as a test
        graph.add(s,kp);
}
/* find/generate stelle for the given name */
stelle *suchStelle(char *name)
{
    stelle *sp,ss;

    ss.name=name; /* template object to search for */
    sp=sHash.get(hp,&ss);
    if(sp)return(sp);
    sp=new stelle;
    sp->name=util.strAlloc(name);
    sHash.add(hp,sp);
    return(sp);
}
/* From the collected record, print the result */
void anzeigen(stelle *bis)
{
	int kante;
        ergebnis *ep;

	printf("\n%s",bis->name);
        kante=0;
        eRing_iterator eIter(bt_start);
        for(ep= ++eIter; ep; ep= ++eIter){
		printf(" to %s",ep->von->name);
		kante+=ep->kante;
	}
	printf("\ncost is %d\n",kante);
}
/* Is there a direct connection to the target? */
int vergleichen(stelle *von,stelle *bis)
{
        knupfen *kp;
        stelle *s;

        graph_iterator gIter(von);
        for(kp= ++gIter; kp; kp= ++gIter){
                s=gIter.adj();
		if(s==bis)return(kp->gewicht);
        }
	return 0; /* path not completed yet */
}
/* Find a new in-between point for the path */
int fest_legen(stelle *von,stelle **beliebiger_punkt)
{
	int kante;
        knupfen *kp,*pos;
        stelle *ss,*t[2]; /* ??? t[2] has been added */

	kante=0;
        pos=(knupfen *)NULL;
        graph_iterator gIter(von);
        for(kp= ++gIter; kp; kp= ++gIter){
            graph.nodes(t,kp);                     /* ??? added */
	    if(t[0]==von && !(kp->rueckkehr)) { /* ??? changed */
		if(kp->gewicht>=kante) {
		    pos=kp;
                    ss=gIter.adj();
		    kante=kp->gewicht;
		}
	    }
	}
	if(pos) {
		*beliebiger_punkt=ss;
		pos->rueckkehr=1; /* mark it */
		return(pos->gewicht);
	}
	return 0;
}
/* add the partial solution to the list */
void eintragen(stelle *von,stelle *bis,int kante)
{
    ergebnis *ep;

    ep=new ergebnis;
    ep->von=von;
    ep->bis=bis;
    ep->kante=kante;
    bt_start=eRing.add(bt_start,ep);
}
void entfernen(stelle **von,stelle **bis,int *kante)
{
    ergebnis *ep;

    if(bt_start){
        ep=eRing.fwd(bt_start);
        *von=ep->von;
        *bis=ep->bis;
        *kante=ep->kante;
        bt_start=eRing.del(bt_start,ep);
        delete ep;
    }
}

#include "zzfunc.c"
/* ----------------------------------------------------------- */
ZZint sHash_class::cmp(stelle *p1,stelle *p2){return(strcmp(p1->name,p2->name)); }

ZZint sHash_class::hash(stelle *p,ZZint size)
{ ZZint ZZhashStr(char *,ZZint); return(ZZhashStr(p->name,size)); }

