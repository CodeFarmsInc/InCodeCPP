#ifndef ZZ_bookAbstract_NAME_INCLUDED
#define ZZ_bookAbstract_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class bookAbstract_Name {
// ----------------------------------------------------------

class Book;

// description of the cooperating classes
class bookAbstract_NameParent {
public:
    char* name;
    bookAbstract_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class bookAbstract_Name {

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
    
#endif // ZZ_bookAbstract_NAME_INCLUDED
