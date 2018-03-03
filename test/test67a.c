// First of three programs that do this:
// test67a: creates a collection of 1000 objects in blasting and
//          saves them to disk.
// test67b: moves half of the objects to free lists, adds 2 and checks that
//          they came from the free list, then saves in binary.
// test67c: allocation in blasting, but opens in binary, then saves in blasting.
//          This second blast save should be about 1/2. 
#include <stdio.h>
#define ZZ_INHERIT
#define ZZmain
#include "zzincl.h"

class Library {
    ZZ_EXT_Library
public:
};

class Book {
    ZZ_EXT_Book
public:
    int id;
};
    
ZZ_HYPER_SINGLE_COLLECT(books,Library,Book);
ZZ_HYPER_NAME(title,Book);
ZZ_HYPER_UTILITIES(util);

//-------------------------------------------------------------------------
// Check whther the data is in the given step - one or two
void checkData(Library *lib,int step){
    Book *bk; int i1,i2;
    books_iterator it;

    i1=i2=0;
    it.start(lib);
    ITERATE(it,bk){
       i1=i2;
       i2=bk->id;
       if(i1==0)continue;
       if(i1-i2 != step){
	   printf("found error: i1=%d i2=%d step=%d\n",i1,i2,step);
	   exit(1);
       }
    }
}
//-------------------------------------------------------------------------
int main(void)
{
    Library *lib; Book *bk; char *s; int i; char *v[1],*t[1];

    util.mode(0,0,0,0); // blkAlloc will overwrite this
    util.blkAlloc(50000,8);

    lib=Library::newObj(); // use neither new() nor delete()
    for(i=0; i<1000; i++){
        bk=Book::newObj();
	bk->id=i;
	books.add(lib,bk);
    }

    checkData(lib,1);
    v[0]=(char*)lib;
    t[0]="Library";
    util.save("67aMB.dat",1,v,t);
    return(0);
}
#include "zzfunc.c"
