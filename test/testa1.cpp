// Demonstration of saving data to disk - the simplest to use method
// called "binary mode". Serialization functions are automatically 
// generated, and applied when traversing (again transparently) the entire
// data structure from the given root.
// For the instruction on how to change the saving mode within the same
// program run, read the documentation of UTILITIES:mode().
// --------------------------------------------------------------------------
#define ZZmain // use exactly in one file of your program
#include "zzincl.h" // generated by zzprep
#include "testa.h"
int main(){
    int i=10345; Library *lib; Author *aut; Book *bk; 
    void* v[1]; char* t[1]; // for saving to disk
    lib=new Library;

    aut=new Author("Booch"); authors.add(lib,aut);
    bk=new Book(i); books.add(aut,bk); i++;
    bk=new Book(i); books.add(aut,bk); i++;
    
    aut=new Author("Stroustrup"); authors.add(lib,aut);
    bk=new Book(i); books.add(aut,bk); i++;
    
    // save data to disk, 'lib' is the root of all the data
    v[0]=lib; t[0]="Library";
    util.save("myFile",1,v,t); // 1 root, type=Library
    if(util.error()) printf("error in saving to file 'myFile'\n");
    return 0;
}
