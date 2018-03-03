#ifndef ZZ_authorName_NAME_INCLUDED
#define ZZ_authorName_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class authorName_Name {
// ----------------------------------------------------------

class Author;

// description of the cooperating classes
class authorName_NameParent {
public:
    char* name;
    authorName_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class authorName_Name {

public:
    static void add(Author *p, char *c);     // add link to
    static void addNew(Author *p, char *c);  // allocate string, add link
    static char* get(Author *p);
    static char* remove(Author *p);
    static int compare(Author *p1,Author *p2);
    // ...
    // historical DOL interface
    static char* del(Author *p){char* s=get(p); remove(p); return s;}
    static char* fwd(Author *p){return get(p);}
};
    
#endif // ZZ_authorName_NAME_INCLUDED
