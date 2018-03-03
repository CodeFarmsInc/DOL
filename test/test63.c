// WARNING: NOT WORKING IN SEVERAL COMBINATION
// UNDER DEBUGGING    Jiri Feb.2014

// USING ARRAYS AND DIFFERENT STYLE OF SAVING TO DISK
// depending to what #define TESTING_... you use.
// Note:
//   <books> is array of Books, but <cats> is array of pointers to Category
// ---------------------------------------------------------------------
#define TESTING_ASCII
#define ZZmain
// #define TESTING_BINARY
// #define TESTING_BLASTING
// ---------------------------------------------------------------------
#define ZZascii
#include "zzincl.h"

class Library {
    ZZ_EXT_Library
public:
    // Library(){ZZ_INIT(Library);}
    void prt();
};
#ifdef TESTING_ASCII
ZZ_FORMAT(Library,"");
#endif

class Book {
    ZZ_EXT_Book
    int catInd; // category index
public:
    // Book(){ZZ_INIT(Book);}
    void set(const char *name,int cat);
    void prt(Library *lib);
};
#ifdef TESTING_ASCII
ZZ_FORMAT(Book,"%d,catInd");
#endif

class Category {
    ZZ_EXT_Category
public:
    Category(){ZZ_INIT(Category);} // needed when the other constructor used
    Category(const char *name);
};
#ifdef TESTING_ASCII
ZZ_FORMAT(Category,"");
#endif

ZZ_HYPER_ARRAY(books,Library,Book);
ZZ_HYPER_ARRAY(cats,Library,Category*);
ZZ_HYPER_NAME(bName,Book);
ZZ_HYPER_NAME(cName,Category);
ZZ_HYPER_UTILITIES(util);

void Library::prt(){
    int wm,sz,i; Book *bp;

    printf("\nPrint content of the library:\n");
    books.size(this,&wm,&sz);
    for(i=0; i<=wm; i++){
	bp=books.ind(this,i);
	bp->prt(this);
    }
}

void Book::set(const char *name,int cat){
        bName.add(this,util.strAlloc(name));
	catInd=cat;
}

void Book::prt(Library *lib){
	Category **cpp;
	char* bn=bName.fwd(this);
	cpp=cats.ind(lib,catInd);
	char *cn=cName.fwd(*cpp);
	printf("%s %s\n",bn,cn);
}

Category::Category(const char *name){
	ZZ_INIT(Category);
	cName.add(this,util.strAlloc(name));
}

int main(){
    Library *lib; Book *bp; Category *cp,**cpp;
    int i,k,n;
    char *v[1], *t[1];


    // ??? error when blasting is not used, 4 errors in binding
    // util.mode(0,1,0,0);
    // util.blkAlloc(10000,8);  ??? error when first parameter not 0
    // util.blkAlloc(0,8); // page 256 bytes

 
    lib=new Library;
    cats.form(lib,3,0);
    cpp=cats.ind(lib,0); *cpp=new Category("cat0"); 
    cpp=cats.ind(lib,1); *cpp=new Category("cat1"); 

    books.form(lib,10,5);
    bp=books.ind(lib,0); bp->set("book0",0);
    bp=books.ind(lib,1); bp->set("book1",1);
    bp=books.ind(lib,2); bp->set("book2",1);
    bp=books.ind(lib,3); bp->set("book3",0);

    lib->prt();

    printf("before save()\n");
    v[0]=(char*)lib;
    t[0]=util.strAlloc("Library");
    util.save("myFile",1,v,t);


    util.clear(1,v,t);

    v[0]=NULL;
    t[0]=NULL;
    printf("before open()\n");
    util.open("myFile",1,v,t);

    lib=(Library*)(v[0]);
    lib->prt();
    return 0;
}

#include "zzfunc.c"
