// Listing 6.3: Phase III, removing unwanted members and associations
// Read the binary file4 and save it file5, in the new(!) ASCII format.

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
ZZ_FORMAT(Library,""); // same format

class Publication { // -------- entire class new
    ZZ_EXT_Publication
public:
    int year;
};
ZZ_FORMAT(Publication,"%d,year"); // format required, but irrelevant

class Book : public Publication { // -------- new inheritance
    ZZ_EXT_Book
public:
    int pages;
    float cost;
    Book(){};
    Book(char *title);
};
ZZ_FORMAT(Book,"%f,cost"); // NEW format

class Author {
     ZZ_EXT_Author
public:
    int phone; // ---------- new
    Author(){};
    Author(char *name);
};
ZZ_FORMAT(Author,"%d,phone"); // NEW format

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
    char *v[1],*t[1];

    util.mode(0,1,0,0); // binary more
    util.open("file2",1,v,t);
    lib=(Library*)(v[0]);

    lib->prt2();

    util.mode(1,0,0,0); // ASCII mode
    v[0]=(char*)lib; 
    t[0]="Library";
    util.save("file3",1,v,t);

    return 0;
}
#include "zzfunc.c"
