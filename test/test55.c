// Demonstration how objects of unknows types can be represented using
// the PROPERTY organization. The input of each object starts with the line
// OBJECT type        ... followed by the an arbitrary number of lines
// type name value    ... for each attribute
//
// Run: program inpFile outFile
//
// All different types are, internally, represented as one type = Obj,
// NAME objType indicates what type it is, and the attributes can be
// detected by their labels.
//
// Normally objects for the same type have always the same number of
// attributes. This sample input tests a more difficult (and more interesting)
// case when occassionally some attributes are be missing.

#ifdef INP55
OBJECT employee
int salary 450
string name Miguel Cordero
OBJECT employee
int salary 550
string address 14 Vista Dr., Santiago
Object department
string name Computer Science
OBJECT employee
string name Jiri Vrba
string address Zitna 2, Praha
#endif // INP55

#include <stdio.h>
#define ZZmain
#include "zzincl.h"

class Root { // root of all data
    ZZ_EXT_Root
};

class Obj { // root of all data
    ZZ_EXT_Obj
public:
};

ZZ_HYPER_UTILITIES(util);
ZZ_HYPER_SINGLE_COLLECT(col,Root,Obj); // list of all objects
ZZ_HYPER_NAME(objType,Obj);            // records the type
ZZ_HYPER_PROPERTY(Obj);   // bunch of properties can be attached to any Obj

#define BSIZE 80

int main(int argc,char **argv) {
    char buff[BSIZE],type[BSIZE],attribute[BSIZE],cValue[BSIZE];
    int iValue,i,sz;
    FILE *file1,*file2;
    Root *root;
    Obj *obj;
    char *p, *tp;

    if(argc<=1)file1=stdin;  else file1=fopen(argv[1],"r");
    if(argc<=2)file2=stdout; else file2=fopen(argv[2],"w");

    root=new Root;
    obj=NULL;
    while(fgets(buff,BSIZE,file1)){ // read all the input, and create data
        sscanf(buff,"%s %s",type,attribute);
        if(!strcmp(type,"OBJECT")){ // create a new object
            obj=new Obj;
            p=util.strAlloc(attribute);
            if(!obj || !p){printf("allocation error\n"); return 1;}
            objType.add(obj,p); // add the NAME of the type
            col.add(root,obj);  // add obj to the collection of all objects
            col.set(root,obj);  // keep the same order
        }
        else if(!strcmp(type,"int")){ // attribute which is an integer
            sscanf(buff,"%s %s %d",type,attribute,&iValue);
            if(!obj){
                printf("input error: attributes without object\n"); 
                return 2;
            }
            obj->setProp("int",attribute,&iValue,1);
        }
        else if(!strcmp(type,"string")){ // attribute which is an integer
            // skip two blanks to find the beginning of the string
            // this is important when the string itself may include
            // blanks like in names or addresses
            for(p=buff, i=0; *p && i<2; p++)if(*p==' ')i++;
            if(!obj || i<2){
                printf("input error: missing object or attribute string\n");
                return 3;
            }
            obj->setProp("string",attribute,&p,1);
        }
        else printf("program not set up to handle type=%s, skipped\n",type);
    }

    // walk through all the data, and add all salaries for type=employee
    i=0; // will calculate the total
    col_iterator cit(root);
    ITERATE(cit,obj){
        p=objType.fwd(obj);
        if(strcmp("employee",p))continue; // skip objects that are not employees
        p=obj->getProp("salary",&tp,&sz);
        if(sz==0)continue; // property not found
        iValue= *((int*)p);       
        i=i+iValue;
    }
    fprintf(file2,"total salary=%d\n",i);
    return 0;
}
#include "zzfunc.c"
