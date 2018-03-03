// Testing the allocation from the list of free objects with memory blasting. 

#define ZZmain
#include "zzincl.h"

class Library{
    ZZ_EXT_Library
public:
    // Library(){ZZ_INIT(Library);}
    ~Library(){ZZ_CHECK(Library);}
    Library* newObj(void){
	    Library *p; ZZ_OBJECT_NEW(Library,p); return(p); }
    void delObj(){ ZZ_OBJECT_FREE(Library,this); }
}LIB;

class Book{
    ZZ_EXT_Book
public:
    // Book(){ZZ_INIT(Book);}
    ~Book(){ZZ_CHECK(Book);}
    int id;
    Book* newObj(void){
	    Book *p; ZZ_OBJECT_NEW(Book,p); return(p); }
    void delObj(){ ZZ_OBJECT_FREE(Book,this); }
}BK;

ZZ_HYPER_DOUBLE_COLLECT(books,Library,Book);
ZZ_HYPER_UTILITIES(util);
    
int main(void) {
    int i; Library lib; Book *bk;
    void *v[1]; char *t[1];
    books_iterator itb;
    Library* LIB=new Library;
    Book* BK=new Book;

    util.blkAlloc(10000,10);
    util.mode(2,0,0,0);

    for(i=0;i<20; i++){
	bk=BK->newObj(); bk->id=i;
	books.add(&lib,bk);
    }

    itb.start(&lib);
    ITERATE(itb,bk){
	if((bk->id)%6 == 0){
             printf(" deleting book %d %d\n",bk->id,bk); 
	     books.del(&lib,bk);
	     bk->delObj();
	}
    }

    for(i=20; i<26; i++){
	bk=BK->newObj(); bk->id=i;
        printf(" adding book %d %d\n",i,bk); 
	books.add(&lib,bk);
    }
   
    return 0;
}
	
#include "zzfunc.c"
