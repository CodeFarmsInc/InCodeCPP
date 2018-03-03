
// -------- data structure DOUBLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class books_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_books_LINKED_LIST2_INCLUDED
#define ZZ_books_LINKED_LIST2_INCLUDED

class Library;
class Book;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class books_LinkedList2Parent {
public:
    Book* tail;
    books_LinkedList2Parent(){ tail=NULL; }
};

class books_LinkedList2Child : public books_Ring2Element {
public:
    books_LinkedList2Child() : books_Ring2Element(){ }
};

// the following class is used when Parent==Child
class books_LinkedList2ParentLinkedList2Child : public books_Ring2Element {
public:
    Book* tail;
    books_LinkedList2ParentLinkedList2Child() : books_Ring2Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class books_LinkedList2 : books_Ring2 {

public:
    static Book* const tail(Library *p);
    static Book* const head(Library *p);
    static void addHead(Library *p, Book *c);
    static void addTail(Library *p, Book *c);
    static void append(Library *p,Book *c1, Book *c2);
    static void insert(Book *c1, Book *c2);
    static void remove(Library *p, Book *c);
    static Book* const next(Library *p, Book *c);
    static Book* const prev(Library *p, Book *c);
    static Book* const nextRing(Book *c);
    static Book* const prevRing(Book *c);
    static void sort(ZZsortFun cmpFun, Library *p);
    static void merge(Book *s,Book *t,Library *p);
    static void setTail(Library* p,Book* c,int check);

    // historical DOL compatible interface
    static void del(Library *p, Book *c) { remove(p,c); }
    static void add(Library *p, Book *c) { addHead(p,c);}
    static void ins(Book *c1, Book *c2) { insert(c1,c2); }
    static Book* child(Library* p);
    static void set(Library* p,Book* c){ setTail(p,c,0);}
    static Book* const fwd(Book *c){return nextRing(c);}
    static Book* const bwd(Book *c){return prevRing(c);}
};

class books_LinkedList2Iterator : public books_Ring2Iterator {
public:
    books_LinkedList2Iterator() : books_Ring2Iterator(){}
    books_LinkedList2Iterator(const Library *p) : books_Ring2Iterator(){ start(p); }
    void start(const Library *p);
    Book* fromHead(Library *p);
    Book* fromTail(Library *p);
};
    
#endif // ZZ_books_LINKED_LIST2_INCLUDED
