/* Test of ARRAY  and saving on disk with hyper-objects in C++,
 * using the ZZ_FORMAT() statements.
 * The program is an equivalent of both test16a.c and test16b.c.
 * The output should be the same as for test16b.c.
 * It saves first in ASCII and then in binary, before it prints the result.
 */

#define ZZascii
#include <stdio.h>
#define ZZmain
#include "zzincl.h"

class Header {
    ZZ_EXT_Header
public:
};
ZZ_FORMAT(Header,"");

class Person {
    ZZ_EXT_Person
public:
    int age;
    float salary;
};
ZZ_FORMAT(Person,"%d %f,age,salary");

class Couple {
    ZZ_EXT_Couple
public:
    int numChild;
};
ZZ_FORMAT(Couple,"%d,numChild");

ZZ_HYPER_SINGLE_RING(people,Person);
ZZ_HYPER_NAME(name,Person);
ZZ_HYPER_SINGLE_LINK(per1,Couple,Person);
ZZ_HYPER_SINGLE_LINK(per2,Couple,Person);
ZZ_HYPER_ARRAY(arr,Header,Couple);
ZZ_HYPER_ARRAY(cArr,Header,int);
ZZ_HYPER_UTILITIES(util);

#define BSIZE 80
char bf[BSIZE],name1[BSIZE],name2[BSIZE];

int main(int argc,char **argv)
{
    Person *getPerson(Person *p,char *nm);
    void printObj(char *obj,ZZint typeInd,ZZint size,const char *priv);
    void printAll(FILE *fp,Header *h);
    FILE *file1,*file2;
    Header *h;
    char c,*n1,*v[1],*t[1];
    int i,n,age,child,*ci,*ip;
    float salary;
    Person *sp,*pp,*p1,*p2;
    Couple *cp;

    if(argc<=1)file1=stdin;  else file1=fopen(argv[1],"r");
    if(argc<=2)file2=stdout; else file2=fopen(argv[2],"w");

    h=new Header;
    sp=(Person *)NULL;
    n=i=0;
    while(fgets(bf,BSIZE,file1)){
        sscanf(bf,"%c",&c);
        if(c=='P'){
            if(n<0){printf("all P records must preceed C records\n");return(0);}
            n++;
            sscanf(bf,"%c %s %d %f",&c,name1,&age,&salary);
            pp=new Person;
            pp->age=age;
            pp->salary=salary;
            n1=util.strAlloc(name1);
            name.add(pp,n1);
            sp=people.add(sp,pp);
        }
        else if(c=='C'){
            if(n>0){
                (void)arr.form(h,n/2,3);
                if(!cArr.formed(h))ci=cArr.form(h,n/2,3); // test of formed()
                if(!cArr.formed(h))ci=cArr.form(h,n/2,3); // should not form
                n= -1;
            }
            sscanf(bf,"%c %s %s %d",&c,name1,name2,&child);
            p1=getPerson(sp,name1);
            p2=getPerson(sp,name2);
            if(p1 && p2){
                cp=arr.ind(h,i);
                per1.add(cp,p1);
                per2.add(cp,p2);
                cp->numChild=child;
		ip=cArr.ind(h,i);
                *ip=child;
                i++;
            }
            else printf("wrong couple definition %s %s\n",name1,name2);
        }
    }

    fclose(file1);

    fprintf(file2,"original result:\n");
    printAll(file2,h);

    /* sweap all objects, print them */
    v[0]=(char*)h; t[0]=(char*)"Header";
    fprintf(file2,"\nlist of all objects:\n");

    util.swpSet(1,v,t);
    util.swpFun(printObj,(const char*)file2);

    util.save("afile",1,v,t); /* ASCII save */
    v[0]=t[0]=(char *)NULL; /* just to be on the safe side */
    util.open("afile",1,v,t);

    util.mode(1,0,0,0); /* change to the binary save */
    util.save("bfile",1,v,t);
    v[0]=t[0]=NULL; /* just to be on the safe side */
    util.open("bfile",1,v,t); /* final restore which will be printed */

    /* second time restore the organization */
    fprintf(file2,"\nrestored from disk:\n");
    h=(Header *)v[0];
    printAll(file2,h);
    return(0);
}
/* ------------------------------------------------------------------ */
Person *getPerson(Person *sp,char *nm)
{
    Person *pp;
    char *nn;

    people_iterator pIter(sp);
    for(pp= ++pIter;pp;pp= ++pIter){ // See NOTE at the end of the code
        nn=name.fwd(pp);
        if(!strcmp(nm,nn))return(pp);
    }
    return((Person *)NULL);
}
/* ------------------------------------------------------------------ */
/* function to print one object */
void printObj(char *obj,ZZint typeInd,ZZint size,const char *priv)
{
    FILE *fp;
    char *type;
    Person *pp;
    char *nn;

    fp=(FILE *)priv;
    type=util.type(typeInd);
#ifdef Windows64
    fprintf(fp,"object type=%I64d %s size=%I64d\n",typeInd,type,size);
#else
    fprintf(fp,"object type=%d %s size=%d\n",typeInd,type,size);
#endif
    fflush(fp);
    if(!strcmp(type,"Person")){
        pp=(Person*)obj;
        nn=name.fwd(pp);
        fprintf(fp,"  Person %s age=%d salary=%f\n",nn,pp->age,pp->salary);
	fflush(fp);
    }
}
/* ------------------------------------------------------------------ */
void printAll(FILE *file2,Header *h)
{
    ZZint i,n,water,incr;
    int *ci;
    char *n1,*n2;
    Couple *ca;
    Person *p1,*p2;

    n=arr.size(h,&water,&incr);
    i=incr; i=n; /* just to shut up compiler */
    ca=arr.ind(h,0);
    ci=cArr.ind(h,0);

    for(i=0;i<=water;i++,ca++){
        p1=per1.fwd(ca);
        n1=name.fwd(p1);
        p2=per2.fwd(ca);
        n2=name.fwd(p2);
        fprintf(file2,
          "%s(%d,%f) %s(%d,%f) child=%d\n",
               n1,p1->age,p1->salary,n2,p2->age,p2->salary,ca->numChild);
        if(ca->numChild!=(ci[i]))fprintf(file2,
                    "   disagreement: i=%d ca=%d ci=%d\n",i,ca->numChild,ci[i]);
    }
}
#include "zzfunc.c"

// NOTE: The most convenient way of iterating over a set is to use a while()
//       loop. In this situation, you can simply use:
//                while(pp=pIter++){
//       Unfortunately, many compilers issue warnings for this code.
//       Using the syntactically correct for() is unwieldy:
//                for(pp= ++pIter;pp;pp= ++pIter){
//       but can be hidden under a macro which is provided by the library:
//                ITERATE(pIter,pp){
