#ifndef ZZ_bookTitle_NAME_INCLUDED
#define ZZ_bookTitle_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class bookTitle_Name {
// ----------------------------------------------------------

class Book;

// description of the cooperating classes
class bookTitle_NameParent {
public:
    char* name;
    bookTitle_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class bookTitle_Name {

public:
    static void add(Book *p, char *c);     // add link to
    static void addNew(Book *p, char *c);  // allocate string, add link
    static char* get(Book *p);
    static char* remove(Book *p);
    static int compare(Book *p1,Book *p2);
    // ...
    // historical DOL interface
    static char* del(Book *p){char* s=get(p); remove(p); return s;}
    static char* fwd(Book *p){return get(p);}
};
    
#endif // ZZ_bookTitle_NAME_INCLUDED
