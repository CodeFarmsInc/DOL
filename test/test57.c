// Test proposed by Eli Tilevich:

// IMPORTANT:
// If all your objects are automatically allocated (as in this program),
// you can remove all the ZZ_INIT(...); statements.
// This will make the initialization of all objects slightly faster.

// Notes:
//    This program will not allow you to test performance or memory size,
//    unless you generate a larger volume of data automatically. I am sure you
//    can modify this program accordingly.
// 
//    Remember, that a big part of DOL is the data persistency.
//    I am not demonstrating it here, but some part of data initialization
//    etc. is required for this, which may show as a minor performance
//    penalty.

//    I used simple collections for Students and Classes.
//    For you this is the easiest code to read,
//    but the lookup requires a search
//    through the collection. If would be much faster to use a hash table.

//    If you want to see such a version let me know.
//    This would be also a test of how flexible
//    my implementation is (maintenance, flexibility, robustness).
//    For saving data to disk, I am using the 'binary' mode, which has
//    the simplest interface, but is not the fastest. Memory blasting
//    is about 10x faster.

// Running the program:
//   just type: tmp
//   If you type STOP instead of your name, the program will stop and save
//   all the data to disk file eli.dat.
//   When you invoke the program next time, it will pick up the old data
//   automatically. In order to start fresh, just remove file eli.dat from
//   your directory.

#include <stdio.h>
#define ZZmain
#include "zzincl.h"

// School encapsulates your problem
class School {
    ZZ_EXT_School
public:
    School(){ZZ_INIT(School);}
    char *getName(int i,char *buf);
};

class Student {
    ZZ_EXT_Student
public:
    Student(char *name);
    Student(){ZZ_INIT(Student);} // not generated automatically
};

class Class {
    ZZ_EXT_Class   
public:
    Class(char *name);
    Class(){ZZ_INIT(Class);} // not generated automatically
};

class Takes {
    int mark;
    int absentDays;
    ZZ_EXT_Takes  
public:
    Takes() {ZZ_INIT(Takes);}
    int addAbsent(int d){absentDays+=d; return absentDays;} // for d=0 reports
    int getMark(){return mark;}
    void setMark(int m){mark=m;}
};


// ----------- data organization --------------
ZZ_HYPER_UTILITIES(util);
ZZ_HYPER_M_TO_N(scRelation,Student,Takes,Class);
ZZ_HYPER_NAME(studentName,Student);
ZZ_HYPER_NAME(className,Class);
ZZ_HYPER_DOUBLE_COLLECT(students,School,Student);
ZZ_HYPER_DOUBLE_COLLECT(classes,School,Class);
// --------------------------------------------

Student::Student(char *name){
    ZZ_INIT(Student);
    char* p=util.strAlloc(name);
    studentName.add(this,p);
}

Class::Class(char *name){
    ZZ_INIT(Class);
    char* p=util.strAlloc(name);
    className.add(this,p);
}

// pick up names including spaces, if i>0 skip the first word
char* School::getName(int i,char *buf){
    char *p;
    for(p=buf; *p!='\n'; p++)continue;
    *p='\0'; // mark the end of the name
    if(i==0)return buf;
    for(p=buf; *p!='\0' && *p!=' '; p++)continue;
    if(*p=='\0')return p;
    for( ;*p==' ' && *p!='\0'; p++);
    return p;
}

#define BSIZE 80
char buff[BSIZE];

int main(int argc,char **argv) {
    School *school; Student *sp; Takes *tp; Class *cp;
    void *root[1]; char *type[1],*name,cc; FILE *fp;
    students_iterator sit;
    classes_iterator cit;
    scRelation_sIterator sourceIter;

    fp=fopen("eli.dat","r"); // just test whether the file exists
    if(!fp)school=new School;
    else {                   // pick up the old data from the disk
        fclose(fp);
        util.open("eli.dat",1,root,type);
        if(util.error()){printf("wrong file format: %s\n","eli.dat"); return 1;}
        school=(School*)(root[0]);
    }

    for(;;){
        printf("type your name:\n");
        fgets(buff,BSIZE,stdin);
        name=school->getName(0,buff);
        if(!strcmp(name,"STOP"))break;
        
        sit.start(school); // search for 'your name'
        ITERATE(sit,sp){
            if(!strcmp(name,studentName.fwd(sp)))break;
        }
        if(sp){
            printf("registered in:");
            sourceIter.start(sp);
            ITERATE(sourceIter,tp){ // walk through all Takes's of sp
                cp=scRelation.target(tp);
                printf("(%s)",className.fwd(cp));
            }
            printf("\n");
        }
        else {
            printf("new student=%s\n",name);
            sp=new Student(name);
            students.add(school,sp);
        }
        for(;;){
            printf("menu(A className,D className,R=remove student,E=exit):\n");
            fgets(buff,BSIZE,stdin);
            sscanf(buff,"%c",&cc);
            name=school->getName(1,buff);
            if(cc=='A'){
                // first check that this student isn't already registered there
                sourceIter.start(sp);
                ITERATE(sourceIter,tp){ // walk through all Takes's of sp
                    cp=scRelation.target(tp);
                    if(!strcmp(name,className.fwd(cp)))break;
                }
                if(tp){ printf("... you are already registered\n"); continue;}

                // find the class
                cit.start(school);
                ITERATE(cit,cp){ // search for the class of the given name
                    if(!strcmp(name,className.fwd(cp)))break;
                }
                if(!cp){
                    printf("... new class\n");
                    cp=new Class(name);
                    classes.add(school,cp);
                }
                tp=new Takes; // many-to-many involves 3 object types!!
                scRelation.add(sp,tp,cp);
            }
            else if(cc=='D'){
                sourceIter.start(sp);
                ITERATE(sourceIter,tp){ // walk through all Takes's of sp
                    cp=scRelation.target(tp);
                    if(!strcmp(name,className.fwd(cp)))break;
                }
                if(!tp){
                    printf(" you are not registered for this class\n");
                    continue;
                }
                scRelation.del(tp); // disconnect tp
                delete tp;
            }
            else if(cc=='R'){
                sourceIter.start(sp); // delete all class links of this student
                ITERATE(sourceIter,tp){ // walk through all Takes's of sp
                    scRelation.del(tp); // disconnect tp
                    delete tp;          // yes, this is allowed within the loop!
                }
                students.del(school,sp);
                break;
            }
            else if(cc=='E')break;
            else printf("unknown command=%c\n",cc);
        }
    }

    root[0]=(void*)school;
    type[0]=(char*)"School";
    util.save("eli.dat",1,root,type);
    return(0);
}
#include "zzfunc.c"
