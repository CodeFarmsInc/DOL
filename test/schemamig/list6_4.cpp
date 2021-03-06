// Listing 6.4: Phase IV, final version of the code which reads
// Read the ASCII file5 which is already in the new format, and save the data
// in the same format in file6. This is the final version of the datafrom which
// allthe old stuff has been removed. This program can read either file5 or 
// file6 as the input. 

#include <stdio.h>
#define ZZmain
#define ZZascii
#include "zzincl.h"

class Library {
    ZZ_EXT_Library
public:
    Library(){};
    // void prt1(); // ---------- old style print, removed, makes no sense
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
    // int pages; --------- removed
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

// ZZ_HYPER_SINGLE_COLLECT(books,Library,Book);  -------- removed
ZZ_HYPER_SINGLE_COLLECT(publications,Library,Publication); // --- new
ZZ_HYPER_HASH(allBooks,Library,Book); // ---------- new
ZZ_HYPER_SINGLE_COLLECT(authors,Library,Author);
ZZ_HYPER_SINGLE_LINK(toAuthor,Book,Author);
ZZ_HYPER_NAME(bookName,Book);
ZZ_HYPER_NAME(authName,Author);
ZZ_HYPER_UTILITIES(util);

Book::Book(char *title){char* p=util.strAlloc(title); bookName.add(this,p);}
Author::Author(char *name){char* p=util.strAlloc(name); authName.add(this,p);}
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

    util.mode(1,0,0,0); // ASCII mode
    util.open("file3",1,v,t);
    lib=(Library*)(v[0]);

    lib->prt2();

    v[0]=(char*)lib; 
    t[0]="Library";
    util.save("file4",1,v,t);

    return 0;
}
#include "zzfunc.c"
