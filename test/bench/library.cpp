// HOLLOW TEST DOES NOT USE DISK STORAGE, ONLY CREATES NEW DATA WHEN NEEDED.
// IT'S PURPOSE IS TO TEST THAT THE PROGRAM COMPILES AND RUNS THROUGH
// ALL THE STEPS AS EXPECTED BEFORE WE ADD PERSISTENCE TO IT.
// UNCOMMENT THE NEXT #include WHEN TESTING THE PERSISTENCE.
// //-----------------------------------------
#define HOLLOW

#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <locale.h>

#define NSIZE 500

#include "gen.h"


//Entity classes
class Library
{    
public:
    ZZ_Library ZZds;
    //unsigned booksCount;
};

//--------------------------
class Book
{
public:
    ZZ_Book ZZds;
    unsigned vote; //
};

//--------------------------
class Author
{
public:
    ZZ_Author ZZds;
};

//--------------------------
class BookToAuthor {
public:
    ZZ_BookToAuthor ZZds;
};

#define LIBRARY_FILE_FMT    "library_dol_bin_%d_%d.dat"
#define LIBRARY_FILE2_FMT    "library2_dol_bin_%d_%d.dat"
#define RESULTS_FILE_FMT "results_dol_bin_%d_%d.txt"

char *g_libFilename = NULL;
char *g_libFilename2 = NULL;

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


Library *CreateLibrary(bool genAbstract, unsigned booksCount, int saveIt);
void OpenLibrary(Library *givenLib);
void AddResult(int testNo, const char* name, double value);
void PrintResults();
void WriteResultsToFile(unsigned booksCount, const char* res_filename);
unsigned FileSize(const char* filename);

//comparators
int CompBooksByVote(const void *b1, const void *b2);

int main(int argc, char *argv[])
{
    bool create = true;
    bool createOk = false;

    unsigned booksCount = 0;
    bool countOk = false;

    unsigned nthRun = 1;
    bool nthRunOk = false;

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
        else if(strcmp(argv[i], "-n")==0)
        {
            nthRun = (unsigned)atoi(argv[i+1]);
            nthRunOk = true;
            i++;
            continue;
        }
    }
    if(!createOk || !countOk || !nthRunOk)
    {
        Help();
        return -1;
    }

    char lib_filename[NSIZE] = {0,};
    char lib_filename2[NSIZE] = {0,};
    char res_filename[NSIZE] = {0,};
    sprintf(lib_filename, LIBRARY_FILE_FMT, booksCount, nthRun);
    sprintf(lib_filename2, LIBRARY_FILE2_FMT, booksCount, nthRun);
    g_libFilename = lib_filename;
    g_libFilename2 = lib_filename2;

    sprintf(res_filename, RESULTS_FILE_FMT, booksCount, nthRun);

    Library *lib=NULL;
    if(create)
    {
#ifdef HOLLOW
        CreateLibrary(genAbstract, booksCount, 0);        
#else
        CreateLibrary(genAbstract, booksCount, 1);        
#endif
    }
    else
    {        
#ifdef HOLLOW
	lib=CreateLibrary(genAbstract, booksCount, 0);
#endif
        OpenLibrary(lib);        
        booksCount = 0;
    }

    PrintResults();
    WriteResultsToFile(booksCount, res_filename);

    Log("\n\nDOL benchmark done\n");
   // getchar();

    return 0;
}

// saveIt=0 do not save the data at the end, saveIt=1 save it
Library *CreateLibrary(bool genAbstract, unsigned booksCount, int saveIt)
{
    char buff[513];
    remove(g_libFilename);
    remove(g_libFilename2);
    srand((unsigned)time(NULL));

    char *v[1],*t[1];
    Library *lib;
    Book *book;
    Author *auth;
    BookToAuthor *ba;
    unsigned start, time1, time2;
    unsigned count;
    char name[128];
    char *pname;
    unsigned bookAuthCount;

    start = time1 = GetTimeMillis();
    Log("\n\nCreating the library...\n");    
    lib = new Library(); 
   // lib->booksCount = 0;

    //first create authors
    Log("Generating authors...\n");
    unsigned authorsCount = booksCount>=BOOKS_TO_AUTHORS_RATIO ? booksCount / BOOKS_TO_AUTHORS_RATIO : booksCount;
    Author **tmpAuth = new Author*[authorsCount];
    for(unsigned i=0; i<authorsCount; i++)
    {
        auth = new Author();
        sprintf(name, "%c%c author %d",(rand() % 26) + 65, (rand() % 26) + 65, i+1);
	authorName::addNew(auth, name);
        tmpAuth[i] = auth;
	authors::add(lib, auth);
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

	bookTitle::addNew(book, name);
        book->vote = rand();
	books::add(lib, book);
        //lib->booksCount++;

        if(genAbstract)
        {
            memset(buff, 'a', NSIZE); buff[NSIZE]='\0';
            absSize = rand() % NSIZE + 1;
            absSize = absSize < 16 ? 16 : absSize;
            buff[absSize-1] = '\0';
	    bookAbstract::addNew(book, buff);
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

            BookToAuthor *b2a;
            Author *a;
            //iterate already assigned authors of this books
            booksToAuthors_Iterator it;
	    for(b2a=it.from1(book); b2a; b2a=it.next1()){
                a = booksToAuthors::entity2(b2a);
                if(a==auth)
                {
                    ok = false;
                    break;
                }
            }            
            if(ok)
            {
		    booksToAuthors::add(new BookToAuthor(), book, auth);
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
    booksToAuthors_Iterator it;
    bool hasBook;
    for(unsigned i=0; i<authorsCount; i++)
    {
	for(ba=it.from2(tmpAuth[i]); ba; ba=it.next2()){
            hasBook = true;
            break;
        }
        if(!hasBook)
        {
	    authors::del(lib, tmpAuth[i]);
            pname=authorName::del(tmpAuth[i]);
	    delete[] pname;
            delete tmpAuth[i];
        }
    }
    delete [] tmpAuth;

    time2 = GetTimeMillis();
    Log("Done. Time: %d ms, Total: %d ms\n", time2-time1, time2-start);
    AddResult(1, "Library creation [ms]", time2-time1);


    Log("\n\nSorting books by vote...\n");
    time1 = GetTimeMillis();        
    books::sort(CompBooksByVote, lib);
    time2 = GetTimeMillis();
    Log("Done. Time: %d ms, Total: %d ms\n", time2-time1, time2-start);
    AddResult(2, "Sort by vote [ms]", time2-time1);

    if(!saveIt)return lib;
       
    Log("\n\nSaving data...\n");
    time1 = GetTimeMillis();

    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //  Here you save all the data space, and remember 'lib' to be the root
    //  ObjectStore in this place should move the current pages to disk.
    //  Here is what DOL does:
    //
    // v[0]=(char*)lib;
    // t[0]=(char*)"Library";        
    // util.save(g_libFilename, 1, v, t); this is what DOL library does
    //
    //  g_libFilename is the name of the file  
    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
   
    time2 = GetTimeMillis();
    Log("Done. Time: %d ms, Total: %d ms\n", time2-time1, time2-start);
    AddResult(3, "Library saving [ms]", time2-time1);
    
    unsigned size = FileSize(g_libFilename);
    AddResult(4, "File size [MB]", size / 1000000.);
    return NULL; // data not needed any more
}

// if givenLib==NULL, open data from disk, otherwise forget IO and take givenLib
void OpenLibrary(Library *givenLib)
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
    Log("Loading data...\n");

    if(givenLib)lib=givenLib;
    else {

    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //  Here you load all the data from disk, and return v[0] as the root.
    //  For checking, t[0] is a text string with the name of the
    //  class for the root object, but it is not needed in this program.
    //  This is what DOL library does:
    //
    // util.open(g_libFilename, 1, v, t); 
    // if(util.error()!=0){
    //            Log("Error while opening file %s.\n", g_libFilename);}
    // lib = (Library*)v[0];
    //
    //  g_libFilename is the name of the file.
    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    
    }
	time2 = GetTimeMillis();
	Log("Done. Time: %d ms, Total: %d ms\n", time2-time1, time2-start);
	AddResult(5, "Data loading [ms]", time2-time1);
    

    time1 = GetTimeMillis();
    const int topVoted = 5;
    Log("Print top %d voted books...\n", topVoted);
    cnt = 0;
    books_Iterator it;
    it.start(lib);
    ITERATE(it, b)
    {
        if(cnt>=topVoted)
        {
            break;
        }
        Log("%d. book: %s\n", cnt+1, bookTitle::fwd(b));
        cnt++;
    }
    time2 = GetTimeMillis();
	Log("Done. Time: %d ms, Total: %d ms\n", time2-time1, time2-start);
	AddResult(6, "Top voted books [ms]", time2-time1);

    
    time1 = GetTimeMillis();
    const char* find = "Z book";
    Log("Number of books containing '%s' in their title...\n", find);
    it.start(lib);
    cnt = 0;
    ITERATE(it, b)
    {
        if(strstr(bookTitle::fwd(b), find)!=NULL)
        {
            cnt++;
        }
    }
    Log("Number of books: %d\n", cnt);
    time2 = GetTimeMillis();
	Log("Done. Time: %d ms, Total: %d ms\n", time2-time1, time2-start);
	AddResult(7, "Search book by title [ms]", time2-time1);


    time1 = GetTimeMillis();
    Log("\n\nRemove one quarter of the books\n");
    booksToAuthors_Iterator itBas;
    booksToAuthors_Iterator itBat;
    BookToAuthor *b2as, *b2at;
    Author *a;

    it.start(lib);
    cnt = 1;
    ITERATE(it, b)
    {
        if((cnt%4)==0)
        {
            //remove book
	    books::del(lib, b);
            //remove books name
            str=bookTitle::del(b);
	    delete[] str;

            //remove abstract if any
            str = bookAbstract::del(b);
            if(str!=NULL)
            {
                delete[] str;
            }

            //remove the relation Book-Author
	    for(b2as=itBas.from1(b); b2as; b2as=itBas.next1()){
                a = booksToAuthors::entity2(b2as);
                //remove th relation
		booksToAuthors::remove(b2as);
                //if the author does not have any book, remove the author
                hasBook = false;
	        for(b2at=itBat.from2(a); b2at; b2at=itBat.next2()){
                    hasBook = true;
                    break;
                }
                if(!hasBook)
                {
                    //remove author
		    authors::del(lib, a);
                    //remove author's name
                    str=authorName::del(a);
                    delete[] str;
		    delete a;
                }
                delete b2as;
            }
            delete b;
        }
        cnt++;
    }

    time2 = GetTimeMillis();
	Log("Done. Time: %d ms, Total: %d ms\n", time2-time1, time2-start);
	AddResult(8, "Data reduction [ms]", time2-time1);
   


    //save reduced data
    Log("Saving reduced data...\n");
    time1 = GetTimeMillis();

    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //  Here you save all the data space, and remember 'lib' to be the root
    //  ObjectStore in this place should move the current pages to disk.
    //  Here is what DOL does:
    //
    // v[0]=(char*)lib;
    // t[0]=(char*)"Library";
    // util.save(g_libFilename2, 1, v, t); this is what DOL library does
    //
    //  g_libFilename2 is the name of the file, note 2 at the end
    //  of the name.
    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    time2 = GetTimeMillis();
	Log("Done. Time: %d ms, Total: %d ms\n", time2-time1, time2-start);
	AddResult(9, "Reduced data saving [ms]", time2-time1);
        

    unsigned size = FileSize(g_libFilename2);
    AddResult(10, "Reduced file size [MB]", size / 1000000.);
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

void WriteResultsToFile(unsigned booksCount, const char *res_filename)
{
    setlocale(LC_ALL, "");
    FILE *f = fopen(res_filename, "a");

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
    fclose(f);
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
    printf("Usage: DOLBin.exe [params]\n");
    
    printf("param: (required) either '-c' or '-o', where 'c' means 'create library' and 'o' means 'open library'\n"); 
    printf("param: (required) '-b <books_count>': number of books to generate\n");
    printf("param: (required) '-n <run_order>': order of the run of this program\n");
    printf("param: (optional with -c) '-a': generate abstract for each book (random size, max. %d bytes)",NSIZE);
}

#include "gen.cpp"
