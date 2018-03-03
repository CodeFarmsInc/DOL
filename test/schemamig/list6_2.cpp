// Listing 6.2: Phase II, adding new members and associations
// Read file3 (old data in ASCII)  and copy books from the LinkList
// to Hash (custom code). Save in binary, because DOL does not support 
// reading in one ASCII format and saving in another ASCII format.

#include <stdio.h>
#define ZZmain
#define ZZascii
#include "zzincl.h"

class Library {
    ZZ_EXT_Library
public:
    Library(){};
    void prt1(); // ---------- old style
void prt2(); // ---------- new style
};
ZZ_FORMAT(Library,"");

class Publication { // -------- entire class new
    ZZ_EXT_Publication
public:
    int year;
};
ZZ_FORMAT(Publication,"%d,year"); // of no old format, use the new one 

class Book : public Publication { // -------- new inheritance
    ZZ_EXT_Book
public:
    int pages;
    float cost;
    Book(){};
    Book(char *title);
};
ZZ_FORMAT(Book,"%d %f,pages,cost");

class Author {
     ZZ_EXT_Author
public:
    int phone; // ---------- new
    Author(){};
    Author(char *name);
};
ZZ_FORMAT(Author,"");

ZZ_HYPER_SINGLE_COLLECT(books,Library,Book);
ZZ_HYPER_SINGLE_COLLECT(publications,Library,Publication); // --- new
ZZ_HYPER_HASH(allBooks,Library,Book); // ---------- new
ZZ_HYPER_SINGLE_COLLECT(authors,Library,Author);
ZZ_HYPER_SINGLE_LINK(toAuthor,Book,Author);
ZZ_HYPER_NAME(bookName,Book);
ZZ_HYPER_NAME(authName,Author);
ZZ_HYPER_UTILITIES(util);

Book::Book(char *title){char* p=util.strAlloc(title); bookName.add(this,p);}
Author::Author(char *name){char* p=util.strAlloc(name); authName.add(this,p);}
void Library::prt1(){
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
	if(i<6) printf("%s: %s,  $%5.2f\n",
			authName.fwd(at),bookName.fwd(bk),bk->cost);
	i++;
    }
    printf("total of %d books\n",i);
}
void Library::prt2(){
    Author *at; Book *bk,*bk1; int i,k,sz,numUsed;
    authors_iterator ait;
    allBooks_iterator hit;

    printf("Authors: \n");
    ait.start(this);
    ITERATE(ait,at){printf("%s\n",authName.fwd(at));}

    printf("Books: \n");
    // when traversing hash table, traverse slots by index, then the list
    i=0;
    sz=allBooks.size(this,&numUsed);
    for(k=0; k<sz; k++){
	bk1=allBooks.slot(this,k);
	hit.start(bk1);
	while(bk= ++hit){
            at=toAuthor.fwd(bk);
            if(i<6)printf("%s: %s,  $%5.2f\n",
			    authName.fwd(at),bookName.fwd(bk),bk->cost);
	    i++;
	}
    }
    printf("total of %d books\n",i);
}

// functions required for hashing
inline int allBooks_class::cmp(Book *b1,Book *b2){
    return strcmp(bookName.fwd(b1), bookName.fwd(b2));
}
inline int allBooks_class::hash(Book *bk,int sz){
    int ZZhashStr(char*,int i);
    return ZZhashStr(bookName.fwd(bk),sz);
}
    
#define numPairs 4

int main(){
    Library *lib; Book *bk; Author *a1,*a2; int i; char buff[80];
    books_iterator bit;
    char *v[1],*t[1];

    util.open("file1",1,v,t);
    lib=(Library*)(v[0]);
    lib->prt1(); // print the entire data
    printf("------------\n");

    // transfer Collection also to Hash
    allBooks.form(lib,4*numPairs);
    bit.start(lib);
    ITERATE(bit,bk){
	allBooks.add(lib,bk);
	books.del(lib,bk); // you can do this even when iterating
    }
    printf("???\n");
    lib->prt2();

    util.mode(0,1,0,0); // first 0 means switch to binary mode
    v[0]=(char*)lib;
    t[0]="Library";
    util.save("file2",1,v,t);

    return 0;
}
#include "zzfunc.c"
