
// -------- data structure DOUBLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class booksToAuthors_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_booksToAuthors_LINKED_LIST2_INCLUDED
#define ZZ_booksToAuthors_LINKED_LIST2_INCLUDED

class Book;
class BookToAuthor;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class booksToAuthors_LinkedList2Parent {
public:
    BookToAuthor* tail;
    booksToAuthors_LinkedList2Parent(){ tail=NULL; }
};

class booksToAuthors_LinkedList2Child : public booksToAuthors_Ring2Element {
public:
    booksToAuthors_LinkedList2Child() : booksToAuthors_Ring2Element(){ }
};

// the following class is used when Parent==Child
class booksToAuthors_LinkedList2ParentLinkedList2Child : public booksToAuthors_Ring2Element {
public:
    BookToAuthor* tail;
    booksToAuthors_LinkedList2ParentLinkedList2Child() : booksToAuthors_Ring2Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class booksToAuthors_LinkedList2 : booksToAuthors_Ring2 {

public:
    static BookToAuthor* const tail(Book *p);
    static BookToAuthor* const head(Book *p);
    static void addHead(Book *p, BookToAuthor *c);
    static void addTail(Book *p, BookToAuthor *c);
    static void append(Book *p,BookToAuthor *c1, BookToAuthor *c2);
    static void insert(BookToAuthor *c1, BookToAuthor *c2);
    static void remove(Book *p, BookToAuthor *c);
    static BookToAuthor* const next(Book *p, BookToAuthor *c);
    static BookToAuthor* const prev(Book *p, BookToAuthor *c);
    static BookToAuthor* const nextRing(BookToAuthor *c);
    static BookToAuthor* const prevRing(BookToAuthor *c);
    static void sort(ZZsortFun cmpFun, Book *p);
    static void merge(BookToAuthor *s,BookToAuthor *t,Book *p);
    static void setTail(Book* p,BookToAuthor* c,int check);

    // historical DOL compatible interface
    static void del(Book *p, BookToAuthor *c) { remove(p,c); }
    static void add(Book *p, BookToAuthor *c) { addHead(p,c);}
    static void ins(BookToAuthor *c1, BookToAuthor *c2) { insert(c1,c2); }
    static BookToAuthor* child(Book* p);
    static void set(Book* p,BookToAuthor* c){ setTail(p,c,0);}
    static BookToAuthor* const fwd(BookToAuthor *c){return nextRing(c);}
    static BookToAuthor* const bwd(BookToAuthor *c){return prevRing(c);}
};

class booksToAuthors_LinkedList2Iterator : public booksToAuthors_Ring2Iterator {
public:
    booksToAuthors_LinkedList2Iterator() : booksToAuthors_Ring2Iterator(){}
    booksToAuthors_LinkedList2Iterator(const Book *p) : booksToAuthors_Ring2Iterator(){ start(p); }
    void start(const Book *p);
    BookToAuthor* fromHead(Book *p);
    BookToAuthor* fromTail(Book *p);
};
    
#endif // ZZ_booksToAuthors_LINKED_LIST2_INCLUDED
