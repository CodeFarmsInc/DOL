// Example of memory blasting when using arrays.
// ---------------------------------------------------------------------

#define ZZmain
#include "zzincl.h"

class Library {
    ZZ_EXT_Library
public:
    void prt();
};

class Book {
    ZZ_EXT_Book
    int catInd; // category index
public:
    Book(){ZZ_INIT(Book);}
    void set(char *name,int cat);
    void prt(Library *lib);
};

class Category {
    ZZ_EXT_Category
public:
    Category(){ZZ_INIT(Category);}
    Category(char *name);
};

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

void Book::set(char *name,int cat){
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

Category::Category(char *name){
	ZZ_INIT(Category);
	cName.add(this,util.strAlloc(name));
}

int main(){
    Library *lib; Book *bp; Category *cp,**cpp;
    int i,k,n;
    char *v[1], *t[1];

    util.blkAlloc(1000,8); // page 32B
    util.mode(2,0,0,0);

    printf("??? new Library\n");
    lib=new Library;
    printf("??? form cats\n");
    cats.form(lib,3,0);
    printf("??? set cat0\n");
    cpp=cats.ind(lib,0); *cpp=new Category("cat0"); 
    printf("??? set cat1\n");
    cpp=cats.ind(lib,1); *cpp=new Category("cat1"); 

    printf("??? form books\n");
    books.form(lib,10,5);
    printf("??? set book0\n");
    bp=books.ind(lib,0); bp->set("book0",0);
    printf("??? set book1\n");
    bp=books.ind(lib,1); bp->set("book1",1);
    printf("??? set book2\n");
    bp=books.ind(lib,2); bp->set("book2",1);
    printf("??? set book3\n");
    bp=books.ind(lib,3); bp->set("book3",0);

    lib->prt();

    printf("??? before save\n");
    v[0]=(char*)lib; t[0]="Library";
    util.save("myFile",1,v,t);

    v[0]=NULL;
    printf("??? before open\n");
    util.open("myFile",1,v,t);
    lib=(Library*)(v[0]);
    lib->prt();
    return 0;
}

#include "zzfunc.c"
