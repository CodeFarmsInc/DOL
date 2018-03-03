
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <Windows.h>
#include <locale.h>

#define ZZmain
#include "zzincl.h"


//Entity classes
class Library
{    
    ZZ_EXT_Library
public:
    unsigned booksCount;
};

//--------------------------
class Book
{
    ZZ_EXT_Book
public:
    unsigned vote; //
};

//--------------------------
class Author
{
    ZZ_EXT_Author
public:
};

//--------------------------
class WrittenBy {
    ZZ_EXT_WrittenBy
public:
};

ZZ_HYPER_DOUBLE_COLLECT(books,Library,Book);
ZZ_HYPER_NAME(bookTitle,Book);
ZZ_HYPER_NAME(bookAbstract, Book);
ZZ_HYPER_DOUBLE_COLLECT(authors,Library,Author);
ZZ_HYPER_NAME(authorName,Author);
ZZ_HYPER_M_TO_N(writtenBy,Book,WrittenBy,Author);
ZZ_HYPER_UTILITIES(util);

//unsigned g_booksCount = 0;

#define LIBRARY_FILE    "library_dol.dat"
#define LIBRARY_FILE2    "library2_dol.dat"
#define MAX_AUTHORS_PER_BOOK 3
#define BOOKS_TO_AUTHORS_RATIO 5
//some utility functions
unsigned GetTimeMillis();
void Log(const char *msg, ...);
void Help();

class Result
{
public:
    char testName[128];
    int testNo;
    double value;
    Result():testNo(0), value(0.0)
    {
        memset(testName, 0, sizeof(testName));
    }
};
#define RESULTS_COUNT 12
Result g_Results[RESULTS_COUNT];
unsigned g_ResultsCount = 0;


void CreateLibrary(bool genAbstract, unsigned booksCount);
void OpenLibrary();
void AddResult(int testNo, const char* name, double value);
void PrintResults();
void WriteResultsToFile(unsigned booksCount);
unsigned FileSize(const char* filename);

//comparators
int CompBooksByVote(const void *b1, const void *b2);

int main(int argc, char *argv[])
{
    //memory blasting    
    util.mode(0, 1, 0, 0);    
    util.blkAlloc(0, 28);    // OK run
    // util.blkAlloc(500000, 20);    // crash, 50k books=4MB data, page 1MB
    // util.blkAlloc(500000000, 0);  // one large block

    bool create = true;
    bool createOk = false;

    unsigned booksCount = 0;
    bool countOk = false;

    bool genAbstract = false;

    for(int i = 1; i<argc; i++)
    {
        if(strcmp(argv[i], "-c")==0)
        {
            create = true;
            createOk = true;
            continue;
        }
        else if(strcmp(argv[i], "-b")==0)
        {
            if(i < (argc-1))
            {
                booksCount = (unsigned)atoi(argv[i+1]);
                countOk = true;
                i++;
                continue;
            }
        }
        else if(strcmp(argv[i], "-a")==0)
        {
            genAbstract = true;
            continue;
        }
        else if(strcmp(argv[i], "-o")==0)
        {
            create = false;
            createOk = true;
            continue;
        }
    }
    if(!createOk || (create && !countOk))
    {
        Help();
        return -1;
    }

    if(create)
    {
        CreateLibrary(genAbstract, booksCount);
       if(util.error())return 7; 
    }
    else
    {
        booksCount = 0;
        OpenLibrary();
    }

    PrintResults();
    WriteResultsToFile(booksCount);

    Log("\n\nDOL benchmark done\n");
   // getchar();

    return 0;
}

void CreateLibrary(bool genAbstract, unsigned booksCount)
{
    remove(LIBRARY_FILE);
    remove(LIBRARY_FILE2);
    srand((unsigned)time(NULL));

    char *v[1],*t[1];
    Library *lib;
    Book *book;
    Author *auth;
    WrittenBy *wBy;
    unsigned start, time1, time2;
    unsigned count;
    char name[128];
    char *pname;
    unsigned bookAuthCount;

    start = time1 = GetTimeMillis();
    Log("**** Creating the library... ****\n");    
    lib = new Library(); 
    lib->booksCount = 0;

    //first create authors
    Log("Generating authors...\n");
    unsigned authorsCount = booksCount>=BOOKS_TO_AUTHORS_RATIO ? booksCount / BOOKS_TO_AUTHORS_RATIO : booksCount;
    Author **tmpAuth = new Author*[authorsCount];
    for(unsigned i=0; i<authorsCount; i++)
    {
        auth = new Author();
        sprintf(name, "%c%c author %d",(rand() % 26) + 65, (rand() % 26) + 65, i+1);
        pname = util.strAlloc(name);
        authorName.add(auth, pname);
        tmpAuth[i] = auth;
        authors.add(lib, auth);
    }

    Log("Generating books...\n");
    //generate books
    int absSize;
    char *abstr;
    for(unsigned i=0; i<booksCount; i++)
    {
        book = new Book();
        name[0] = '\0'; // empty string
		//generate random book name
        sprintf(name, "%c%c book %u\0", (rand() % 26) + 65, (rand() % 26) + 65, i+1);

        pname=util.strAlloc(name);
        bookTitle.add(book, pname);
        book->vote = rand();
        books.add(lib, book);
        lib->booksCount++;

        if(genAbstract)
        {
            absSize = rand() % 512 + 1;
            absSize = absSize < 16 ? 16 : absSize;
            abstr = util.strAlloc(absSize);
            memset(abstr, 'a', absSize);
            abstr[absSize-1] = '\0';
            bookAbstract.add(book, abstr);
        }

        //random authors
        bookAuthCount = authorsCount>=MAX_AUTHORS_PER_BOOK ? rand() % MAX_AUTHORS_PER_BOOK : authorsCount;
        bookAuthCount = bookAuthCount==0 ? 1 : bookAuthCount;
        
        count = 0;        
        bool ok;
        //avoid assign one author twice to the same book
        while(true)
        {
            int idx = rand()%authorsCount;
            auth = tmpAuth[idx];           
            ok = true;

            WrittenBy *w;
            Author *a;
            //iterate already assigned authors of this books
            writtenBy_sIterator it(book);
            ITERATE(it, w)
            {
                a = writtenBy.target(w);
                if(a==auth)
                {
                    ok = false;
                    break;
                }
            }            
            if(ok)
            {
                writtenBy.add(book, new WrittenBy(), auth);
                count++;
            }
            else
            {
                continue;
            }
            if(count==bookAuthCount)
            {
                break;
            }
        }
    }

    //remove authors with no book
    writtenBy_tIterator it;
    bool hasBook;
    for(unsigned i=0; i<authorsCount; i++)
    {
        it.start(tmpAuth[i]);
        wBy = NULL;
        hasBook = false;
        ITERATE(it, wBy)
        {
            hasBook = true;
            break;
        }
        if(!hasBook)
        {
            authors.del(lib, tmpAuth[i]);
        }
    }
    delete [] tmpAuth;

    time2 = GetTimeMillis();
    Log("Done. Time: %d ms, Total: %d ms\n", time2-time1, time2-start);
    AddResult(1, "Library creation [ms]", time2-time1);


    Log("\n\n**** Sorting books by vote... ****\n");
    time1 = GetTimeMillis();        
    books.sort(CompBooksByVote, lib);
    time2 = GetTimeMillis();
    Log("Done. Time: %d ms, Total: %d ms\n", time2-time1, time2-start);
    AddResult(2, "Sort by vote [ms]", time2-time1);

       
    Log("\n\n**** Saving data... ****\n");
    time1 = GetTimeMillis();
    v[0]=(char*)lib;
    t[0]=(char*)"Library";        
    util.save(LIBRARY_FILE, 1, v, t);
    time2 = GetTimeMillis();
    Log("Done. Time: %d ms, Total: %d ms\n", time2-time1, time2-start);
    AddResult(3, "Library saving [ms]", time2-time1);
    
    unsigned size = FileSize(LIBRARY_FILE);
    AddResult(4, "File size [MB]", size / 1000000.);

    //free the library
    //util.clear(1, v, t);
    
}

void OpenLibrary()
{
    char *v[1],*t[1];
    Library *lib;
    Book *b;
    unsigned start, time1, time2;
    int cnt;
    char *str;
    bool hasBook;

    start = GetTimeMillis();
    time1 = start;
    Log("Loading the data...\n");
    util.open(LIBRARY_FILE, 1, v, t);
    if(util.error()!=0)
    {
        Log("Error No.%o while opening file %s.\n", util.error(),LIBRARY_FILE);        
    }
    lib = (Library*)v[0];
	time2 = GetTimeMillis();
	Log("Done. Time: %d ms, Total: %d ms\n", time2-time1, time2-start);
	AddResult(5, "Data loading [ms]", time2-time1);
    

    time1 = GetTimeMillis();
    const int topVoted = 5;
    Log("Print top %d voted books...\n", topVoted);
    cnt = 0;
    books_iterator it(lib);
    ITERATE(it, b)
    {
        if(cnt>=topVoted)
        {
            break;
        }
        Log("%d. book: %s\n", cnt+1, bookTitle.fwd(b));
        cnt++;
    }
    time2 = GetTimeMillis();
	Log("Done. Time: %d ms, Total: %d ms\n", time2-time1, time2-start);
	AddResult(6, "Top voted books", time2-time1);

    
    time1 = GetTimeMillis();
    const char* find = "Z book";
    Log("Number of books containing '%s' in their title...\n", find);
    it.start(lib);
    cnt = 0;
    ITERATE(it, b)
    {
        if(strstr(bookTitle.fwd(b), find)!=NULL)
        {
            cnt++;
        }
    }
    Log("Number of books: %d\n", cnt);
    time2 = GetTimeMillis();
	Log("Done. Time: %d ms, Total: %d ms\n", time2-time1, time2-start);
	AddResult(7, "Search book by title", time2-time1);


    time1 = GetTimeMillis();
    Log("Remove one quarter of the books\n");
    writtenBy_sIterator itWbys;
    writtenBy_tIterator itWbyt;
    WrittenBy *wbys, *wbyt;
    Author *a;

    it.start(lib);
    cnt = 1;
    ITERATE(it, b)
    {
        if((cnt%4)==0)
        {
            //remove book
            books.del(lib, b);
            //remove books name
            util.strFree(bookTitle.del(b));
            //remove abstract if any
            str = bookAbstract.del(b);
            if(str!=NULL)
            {
                util.strFree(str);
            }
            //remove the relation Book-Author
            itWbys.start(b);
            ITERATE(itWbys, wbys)
            {
                a = writtenBy.target(wbys);
                //remove th relation
                writtenBy.del(wbys);
                //if the author does not have any book, remove the author
                itWbyt.start(a);
                hasBook = false;
                ITERATE(itWbyt, wbyt)
                {
                    hasBook = true;
                    break;
                }
                if(!hasBook)
                {
                    //remove author
                    authors.del(lib, a);
                    //remove author's name
                    util.strFree(authorName.del(a));
                    delete a;
                }

                delete wbys;
            }

            delete b;
        }
        cnt++;
    }
    time2 = GetTimeMillis();
	Log("Done. Time: %d ms, Total: %d ms\n", time2-time1, time2-start);
	AddResult(8, "Data reduction", time2-time1);

    //save reduced data
    v[0]=(char*)lib;
    t[0]=(char*)"Library";
    util.save(LIBRARY_FILE2, 1, v, t);

    unsigned size = FileSize(LIBRARY_FILE2);
    AddResult(9, "Reduced file size [MB]", size / 1000000.);
}

void AddResult(int testNo, const char* name, double value)
{
    g_Results[g_ResultsCount].testNo = testNo;
    strcpy(g_Results[g_ResultsCount].testName, name);
    g_Results[g_ResultsCount].value = value;
    g_ResultsCount++;
}

void PrintResults()
{
    printf("\nBENCHMARK RESULTS:\n\n");

    printf("----------------------------------------------------------------------------\n");
    printf("TestNo. | Test Name                                             | Value |\n");
    printf("============================================================================\n");
    for(unsigned i = 0; i < g_ResultsCount; i++)
    {
        printf("   %02d   | %-53s | %-8.2lf |\n", g_Results[i].testNo, g_Results[i].testName, g_Results[i].value);
    }
    printf("----------------------------------------------------------------------------\n");
}

void WriteResultsToFile(unsigned booksCount)
{
    setlocale(LC_ALL, "");
    FILE *f = fopen("dol_results.txt", "a");
    //books_count
    // testno; test_name; value
    if(booksCount != 0)
    {
        fprintf(f, "\n%d;;;\n", booksCount);
    }
    for(unsigned i = 0; i < g_ResultsCount; i++)
    {
        char * end = ((i == (g_ResultsCount-1)) && booksCount!=0) ? "" : "\n";
        fprintf(f, ";%d;%s;%.2lf%s", g_Results[i].testNo, g_Results[i].testName, g_Results[i].value, end);
    }
    if(booksCount!=0)
    {
        fprintf(f, "\n");
    }
    else
    {
        fprintf(f, "\n");
        fprintf(f, "\n");
        fprintf(f, "\n");
        fprintf(f, "\n");
    }
    // fclose(f);
}

unsigned GetTimeMillis()
{
	LARGE_INTEGER now;	
	static bool first = true;
	static LARGE_INTEGER freq;
	if(first)
	{
		QueryPerformanceFrequency(&freq);		
		first = false;
	}

	QueryPerformanceCounter(&now);
	now.QuadPart = now.QuadPart/(freq.QuadPart/ 1000);
	return (unsigned)now.QuadPart;
}

void Log(const char *msg, ...)
{
        va_list argptr;
        va_start(argptr, msg);
        vprintf(msg, argptr);
        va_end(argptr);
}

int CompBooksByVote(const void *b1, const void *b2)
{
    Book *book1 = (Book*)b1;
    Book *book2 = (Book*)b2;

    return book2->vote - book1->vote;
}

unsigned FileSize(const char* filename)
{
    DWORD size = 0;
    DWORD high;
    HANDLE f = CreateFileA(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(f != INVALID_HANDLE_VALUE)
    {
        size = GetFileSize(f, &high);
        DWORD err = GetLastError();
        CloseHandle(f);
    }

    return size;
}

void Help()
{
    printf("Usage: DOLTest.exe [params]\n");
    printf("param: (required) either '-c' or '-o', where 'c' means 'create library' and 'o' means 'open library'\n"); 
    printf("param: (required with -c) '-b <books_count>': number of books to generate\n");
    printf("param: (optional with -c) '-a': generate abstract for each book (random size, max. 512 bytes)");
}

#include "zzfunc.c"
