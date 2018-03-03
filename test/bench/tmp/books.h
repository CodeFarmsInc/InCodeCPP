
// -------- data structure DOUBLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class books_Ring2
// ----------------------------------------------------------
// Ring2 could be derived from Ring2 through inheritance, but
//  (a) The complex functions (sort, remove, merge) are different anyway,
//  (b) we want to minimize the nubmer of classes which will be code generated.
// For these two reasons, Ring2 is coded as a base class.
// ----------------------------------------------------------
#ifndef ZZ_books_RING2_INCLUDED
#define ZZ_books_RING2_INCLUDED

class Book;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class books_Ring2Element {
public:
    Book *next;
    Book *prev;
    books_Ring2Element(){ next=prev=NULL; }
};

class books_Ring2 {

    static int debugFun(Book *tail);
public:
    // standard interface
    static Book* addHead(Book *tail, Book *c); // returns new tail
    static Book* addTail(Book *tail, Book *c); // returns new tail
    static Book* append(Book *tail,Book *c1, Book *c2); // returns new tail
    static void insert(Book *c1, Book *c2); // insert c1 before c2
    static Book* remove(Book *tail, Book *c);  // returns new tail, NULL when empty
    static Book* const next(Book *p, Book *c); // returns NULL when p is the tail
    static Book* const prev(Book *p, Book *c); // returns NULL when p is the head
    static Book* const nextRing(Book *c); // next in the ring
    static Book* const prevRing(Book *c); // previous in the ring
    static Book* sort(ZZsortFun cmpFun, Book *tail); // returns the new tail
    static void merge(Book *s,Book *t);

    // historical DOL compatible interface
    static Book* del(Book *tail, Book *c) { return remove(tail,c); }
    static Book* add(Book *tail, Book *c) { return addHead(tail,c); }
    static void ins(Book *c1, Book *c2) { insert(c1,c2); }
    static Book* const fwd(Book *c){return nextRing(c);}
    static Book* const bwd(Book *c){return prevRing(c);}
    
};

class books_Ring2Iterator {
    Book *tail; // NULL when loop finished
    Book *nxt;  // NULL when starting a new loop
    int dir;  // 0=from head, 1=from tail
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    //                              for(p=it.fromTail(x); p; p=it.next()){...}
    books_Ring2Iterator(){tail=nxt=NULL; dir=0;}
    Book* fromHead(Book *p);
    virtual Book* fromTail(Book *p);
    virtual Book* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    //                              it.start(x); for(p= --it; p; p= --it){...}
    void start(Book *p);
    Book* const operator++();
    Book* const operator--();
    books_Ring2Iterator(Book *p){start(p);}
};
    
#endif // ZZ_books_RING2_INCLUDED
