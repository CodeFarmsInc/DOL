/* Test of directed graph, combined with a ring and a hash table.
 * This is a depth-first graph search based on an algorithm
 * provided by Robert Jones from Wegberg, Germany */
#include <stdio.h>
#define ZZmain
#include "zzincl.h"
#define hashSize 23

typedef struct stelle stelle;
typedef struct knupfen knupfen;
typedef struct ergebnis ergebnis;
typedef struct header header;
struct header {
    ZZ_EXT_header
};
struct stelle {
    ZZ_EXT_stelle
        char *name;
};
struct knupfen {
    ZZ_EXT_knupfen
	int gewicht;
	char rueckkehr; /* controls bactracking */
};
struct ergebnis {
   ZZ_EXT_ergebnis
        stelle *von;
        stelle *bis;
	int  kante;
};

ZZ_ORG_HASH(sHash,header,stelle);
ZZ_ORG_SINGLE_RING(eRing,ergebnis);
ZZ_ORG_DIRECT_GRAPH(graph,stelle,knupfen);

knupfen *pfad_start;
stelle *stelle_list;
header *hp;
ergebnis *bt_start;

#ifdef ZZansi
stelle *eingabe(char *frage);
stelle *pruef(char *name);
int setup(void);
int kante_eintragen(char *von,char *bis,int kante);
stelle *suchStelle(char *name);
int anzeigen(stelle *bis);
int vergleichen(stelle *von,stelle *bis);
int fest_legen(stelle *von,stelle **beliebiger_punkt);
int verbindung(stelle *von,stelle *bis);
int eintragen(stelle *von,stelle *bis,int kante);
int entfernen(stelle **von,stelle **bis,int *kante);
#else
stelle *eingabe();
stelle *pruef();
int setup();
int kante_eintragen();
stelle *suchStelle();
int anzeigen();
int vergleichen();
int fest_legen();
int verbindung();
int eintragen();
int entfernen();
#endif

#ifdef ZZascii
int main(void)

#else
int main()
#endif
{
    stelle *von,*bis,*eingabe(),*suchStelle();
    stelle *sp;
    knupfen *kp;
    ergebnis *ep;

    ZZ_PLAIN_ALLOC(header,1,hp);
    stelle_list=(stelle *)NULL;
    pfad_start=(knupfen *)NULL;
    setup();
    bt_start=(ergebnis *)NULL;
            
    von=eingabe("from? ");
    bis=eingabe("to?   ");
    verbindung(von,bis);
    anzeigen(bis);
    return(0);
}
/* Verify validity of a given end-point, and convert it to internal pointer */
#ifdef ZZascii
stelle *eingabe(char *frage)

#else
stelle *eingabe(frage)
char *frage;
#endif
{
        stelle *sp;
        char name[20]; /* buffer to input start/end node */

        for(sp=(stelle *)NULL; !sp;){
		printf(frage);
		gets(name);
		sp=pruef(name);
		if(!sp)printf("Invalid name, please correct\n");
	}
	return(sp);
}
/* Is this node in the set? */
#ifdef ZZansi
stelle *pruef(char *name)

#else
stelle *pruef(name)
char *name;
#endif
{
    stelle *sp,ss;

    ss.name=name;
    ZZ_GET_HASH(sHash,hp,&ss,sp);
    return(sp);
}
/* setup the task including the stelle_list */
#ifdef ZZansi
int setup(void)

#else
int setup()
#endif
{
        ZZ_FORM_HASH(sHash,hp,hashSize);
	kante_eintragen("a1","a2",10);
	kante_eintragen("a2","a3",10);
	kante_eintragen("a1","c1",8);
	kante_eintragen("a1","a3",19);
	kante_eintragen("c1","b2",15);
	kante_eintragen("c1","c3",18);
	kante_eintragen("c1","a2",5);
	kante_eintragen("a3","c2",10);
	kante_eintragen("a3","b1",15);
	kante_eintragen("b1","c3",15);
	kante_eintragen("a3","c3",10);
	kante_eintragen("b1","b3",7);
	kante_eintragen("a3","b3",12);
        return(0);
}
/* Record one edge of the graph */
#ifdef ZZansi
int kante_eintragen(char *von,char *bis,int kante)

#else
int kante_eintragen(von,bis,kante)
char *von,*bis;
int kante;
#endif
{
        stelle *s[2];
        knupfen *kp;

        ZZ_PLAIN_ALLOC(knupfen,1,kp);
	s[0]=suchStelle(von);
	s[1]=suchStelle(bis);
	kp->gewicht=kante;
	kp->rueckkehr=0;
        ZZ_ADD(graph,s,kp);
        return(0);
}
/* find/generate stelle for the given name */
#ifdef ZZansi
stelle *suchStelle(char *name)

#else
stelle *suchStelle(name)
char *name;
#endif
{
    stelle *sp,ss;

    ss.name=name; /* template object to search for */
    ZZ_GET_HASH(sHash,hp,&ss,sp);
    if(sp)return(sp);
    ZZ_PLAIN_ALLOC(stelle,1,sp);
    ZZ_STRING_ALLOC(name,sp->name);
    ZZ_ADD_HASH(sHash,hp,sp);
    return(sp);
}
/* Print out the results from the recorded list */
#ifdef ZZansi
int anzeigen(stelle *bis)

#else
int anzeigen(bis)
stelle *bis;
#endif
{
	int kante;
        ergebnis *ep;

	printf("\n%s",bis->name);
        kante=0;
        ZZ_A_TRAVERSE(eRing,bt_start,ep){
		printf(" to %s",ep->von->name);
		kante+=ep->kante;
	}ZZ_A_END;
	printf("\ncost is %d\n",kante);
        return(0);
}
/* Is there a direct link to the target? */
#ifdef ZZansi
int vergleichen(stelle *von,stelle *bis)

#else
int vergleichen(von,bis)
stelle *von, *bis;
#endif
{
        knupfen *kp;
        stelle *s[2];

        s[0]=von;
        ZZ_A_TRAVERSE(graph,s,kp){
		if(s[1]==bis)return(kp->gewicht);
        }ZZ_A_END;
	return(0); /* der Pfad existiert nicht */
}
/* Find a new in-between node of the potential path */
#ifdef ZZansi
int fest_legen(stelle *von,stelle **beliebiger_punkt)

#else
int fest_legen(von,beliebiger_punkt)
stelle *von, **beliebiger_punkt;
#endif
{
	int kante;
        knupfen *kp,*pos;
        stelle *s[2],*t[2],*ss;

	kante=0;
        pos=(knupfen *)NULL;
        s[0]=von;
        ZZ_A_TRAVERSE(graph,s,kp){
	    if(!(kp->rueckkehr)) {
		if(kp->gewicht>=kante) {
		    pos=kp;
                    ss=s[1];
		    kante=kp->gewicht;
		}
	    }
	}ZZ_A_END;
	if(pos) {
		*beliebiger_punkt=ss;
		pos->rueckkehr=1; 
		return(pos->gewicht);
	}
	return(0);
}
/* The main depth-first algorithm */
#ifdef ZZansi
int verbindung(stelle *von,stelle *bis)

#else
int verbindung(von,bis)
stelle *von,*bis;
#endif
{
	int d,kante;
	stelle *beliebiger_punkt;
        knupfen *kp;

	d=vergleichen(von,bis);

	if(d) { /* target connected */
		eintragen(von,bis,d);
		return(0);
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
        return(0);
}
/* Record the partial result in a list */
#ifdef ZZansi
int eintragen(stelle *von,stelle *bis,int kante)

#else
int eintragen(von,bis,kante)
stelle *von, *bis;
int kante;
#endif
{
    ergebnis *ep;

    ZZ_PLAIN_ALLOC(ergebnis,1,ep);
    ep->von=von;
    ep->bis=bis;
    ep->kante=kante;
    ZZ_ADD(eRing,bt_start,ep);
    return(0);
}
#ifdef ZZansi
int entfernen(stelle **von,stelle **bis,int *kante)

#else
int entfernen(von,bis,kante)
stelle **von, **bis;
int *kante;
#endif
{
    ergebnis *ep;

    if(bt_start){
        ZZ_FORWARD(eRing,bt_start,ep);
        *von=ep->von;
        *bis=ep->bis;
        *kante=ep->kante;
        ZZ_DELETE(eRing,bt_start,ep);
        ZZ_PLAIN_FREE(ergebnis,1,ep);
    }
    return(0);
}

/* ----------------------------------------------------------- */
#ifdef ZZansi
int zz_hashCmp_sHash(char *s1,char *s2)

#else
int zz_hashCmp_sHash(s1,s2)char *s1,*s2;
#endif
{ stelle *p1,*p2; p1=(stelle *)s1; p2=(stelle *)s2;
  return(strcmp(p1->name,p2->name)); }

#ifdef ZZansi
int zz_hashInd_sHash(char *s,int size)
{ stelle *p; int ZZhashStr(char*,int);

#else
int zz_hashInd_sHash(s,size) char *s; int size;
{ stelle *p; int ZZhashStr();
#endif
  p=(stelle *)s;
  return(ZZhashStr(p->name,size)); }

#include "zzfunc.c"
