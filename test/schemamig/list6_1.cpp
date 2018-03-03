// Listing 6.1: Original data organization
// Create test data and save it in the ASCII mode in file1

#include <stdio.h>
#define ZZmain
#define ZZascii
#include "zzincl.h"

class Library {
    ZZ_EXT_Library
public:
    Library(){};
    void prt();
};
ZZ_FORMAT(Library,"");

class Book {
    ZZ_EXT_Book
public:
    int pages;
    float cost;
    Book(){};
    Book(char *title,float price);
};
ZZ_FORMAT(Book,"%d %f,pages,cost");

class Author {
     ZZ_EXT_Author
public:
    Author(){};
    Author(char *name);
};
ZZ_FORMAT(Author,"");

ZZ_HYPER_SINGLE_COLLECT(books,Library,Book);
ZZ_HYPER_SINGLE_COLLECT(authors,Library,Author);
ZZ_HYPER_SINGLE_LINK(toAuthor,Book,Author);
ZZ_HYPER_NAME(bookName,Book);
ZZ_HYPER_NAME(authName,Author);
ZZ_HYPER_UTILITIES(util);

Book::Book(char *title,float price){
    char* p=util.strAlloc(title); bookName.add(this,p); cost=price;
}
Author::Author(char *name){
    char* p=util.strAlloc(name); authName.add(this,p);
}
void Library::prt(){
    Author *at; Book *bk; int i;
    books_iterator bit;
    authors_iterator ait;

    printf("Authors: \n");
    ait.start(this);
    ITERATE(ait,at){printf("%s\n",authName.fwd(at));}

    printf("Books: \n");
    i=0;
    bit.start(this);
    ITERATE(bit,bk){
        at=toAuthor.fwd(bk);
	// limit number of prints, but go through all books 
	if(i<6) printf("%s: %s,   $%5.2f\n",
			authName.fwd(at),bookName.fwd(bk),bk->cost);
	i++;
    }
    printf("total of %d books\n",i);
}

// chose any number size of data you want
#define numPairs 40 

int main(){
    Library *lib; Book *bk; Author *a1,*a2; int i; char buff[80]; float price;
    char *v[1],*t[1];

    lib=new Library;
    a1=new Author("Andrew Acklin");
    authors.add(lib,a1);
    a2=new Author("Carl Crowford");
    authors.add(lib,a2);
    for(i=0; i<numPairs; i++){
        sprintf(buff,"Book Title%d",2*i+1);
	price=(2*i+1)+0.99;
	bk=new Book(buff,price);
	books.add(lib,bk);
	toAuthor.add(bk,a1);

        sprintf(buff,"Book Title%d",2*i+2);
	price=(2*i+2)+0.99;
	bk=new Book(buff,price);
	books.add(lib,bk);
	toAuthor.add(bk,a2);
    }

    lib->prt(); // print the entire data
    v[0]=(char*)lib;
    t[0]="Library";
    util.save("file1",1,v,t);

    return 0;
}
#include "zzfunc.c"
