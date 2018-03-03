
// -------- data structure DOUBLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class authors_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_authors_LINKED_LIST2_INCLUDED
#define ZZ_authors_LINKED_LIST2_INCLUDED

class Library;
class Author;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class authors_LinkedList2Parent {
public:
    Author* tail;
    authors_LinkedList2Parent(){ tail=NULL; }
};

class authors_LinkedList2Child : public authors_Ring2Element {
public:
    authors_LinkedList2Child() : authors_Ring2Element(){ }
};

// the following class is used when Parent==Child
class authors_LinkedList2ParentLinkedList2Child : public authors_Ring2Element {
public:
    Author* tail;
    authors_LinkedList2ParentLinkedList2Child() : authors_Ring2Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class authors_LinkedList2 : authors_Ring2 {

public:
    static Author* const tail(Library *p);
    static Author* const head(Library *p);
    static void addHead(Library *p, Author *c);
    static void addTail(Library *p, Author *c);
    static void append(Library *p,Author *c1, Author *c2);
    static void insert(Author *c1, Author *c2);
    static void remove(Library *p, Author *c);
    static Author* const next(Library *p, Author *c);
    static Author* const prev(Library *p, Author *c);
    static Author* const nextRing(Author *c);
    static Author* const prevRing(Author *c);
    static void sort(ZZsortFun cmpFun, Library *p);
    static void merge(Author *s,Author *t,Library *p);
    static void setTail(Library* p,Author* c,int check);

    // historical DOL compatible interface
    static void del(Library *p, Author *c) { remove(p,c); }
    static void add(Library *p, Author *c) { addHead(p,c);}
    static void ins(Author *c1, Author *c2) { insert(c1,c2); }
    static Author* child(Library* p);
    static void set(Library* p,Author* c){ setTail(p,c,0);}
    static Author* const fwd(Author *c){return nextRing(c);}
    static Author* const bwd(Author *c){return prevRing(c);}
};

class authors_LinkedList2Iterator : public authors_Ring2Iterator {
public:
    authors_LinkedList2Iterator() : authors_Ring2Iterator(){}
    authors_LinkedList2Iterator(const Library *p) : authors_Ring2Iterator(){ start(p); }
    void start(const Library *p);
    Author* fromHead(Library *p);
    Author* fromTail(Library *p);
};
    
#endif // ZZ_authors_LINKED_LIST2_INCLUDED
