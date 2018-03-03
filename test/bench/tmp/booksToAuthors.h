
// -------- data structure DOUBLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class booksToAuthors_Ring2
// ----------------------------------------------------------
// Ring2 could be derived from Ring2 through inheritance, but
//  (a) The complex functions (sort, remove, merge) are different anyway,
//  (b) we want to minimize the nubmer of classes which will be code generated.
// For these two reasons, Ring2 is coded as a base class.
// ----------------------------------------------------------
#ifndef ZZ_booksToAuthors_RING2_INCLUDED
#define ZZ_booksToAuthors_RING2_INCLUDED

class BookToAuthor;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class booksToAuthors_Ring2Element {
public:
    BookToAuthor *next;
    BookToAuthor *prev;
    booksToAuthors_Ring2Element(){ next=prev=NULL; }
};

class booksToAuthors_Ring2 {

    static int debugFun(BookToAuthor *tail);
public:
    // standard interface
    static BookToAuthor* addHead(BookToAuthor *tail, BookToAuthor *c); // returns new tail
    static BookToAuthor* addTail(BookToAuthor *tail, BookToAuthor *c); // returns new tail
    static BookToAuthor* append(BookToAuthor *tail,BookToAuthor *c1, BookToAuthor *c2); // returns new tail
    static void insert(BookToAuthor *c1, BookToAuthor *c2); // insert c1 before c2
    static BookToAuthor* remove(BookToAuthor *tail, BookToAuthor *c);  // returns new tail, NULL when empty
    static BookToAuthor* const next(BookToAuthor *p, BookToAuthor *c); // returns NULL when p is the tail
    static BookToAuthor* const prev(BookToAuthor *p, BookToAuthor *c); // returns NULL when p is the head
    static BookToAuthor* const nextRing(BookToAuthor *c); // next in the ring
    static BookToAuthor* const prevRing(BookToAuthor *c); // previous in the ring
    static BookToAuthor* sort(ZZsortFun cmpFun, BookToAuthor *tail); // returns the new tail
    static void merge(BookToAuthor *s,BookToAuthor *t);

    // historical DOL compatible interface
    static BookToAuthor* del(BookToAuthor *tail, BookToAuthor *c) { return remove(tail,c); }
    static BookToAuthor* add(BookToAuthor *tail, BookToAuthor *c) { return addHead(tail,c); }
    static void ins(BookToAuthor *c1, BookToAuthor *c2) { insert(c1,c2); }
    static BookToAuthor* const fwd(BookToAuthor *c){return nextRing(c);}
    static BookToAuthor* const bwd(BookToAuthor *c){return prevRing(c);}
    
};

class booksToAuthors_Ring2Iterator {
    BookToAuthor *tail; // NULL when loop finished
    BookToAuthor *nxt;  // NULL when starting a new loop
    int dir;  // 0=from head, 1=from tail
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    //                              for(p=it.fromTail(x); p; p=it.next()){...}
    booksToAuthors_Ring2Iterator(){tail=nxt=NULL; dir=0;}
    BookToAuthor* fromHead(BookToAuthor *p);
    virtual BookToAuthor* fromTail(BookToAuthor *p);
    virtual BookToAuthor* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    //                              it.start(x); for(p= --it; p; p= --it){...}
    void start(BookToAuthor *p);
    BookToAuthor* const operator++();
    BookToAuthor* const operator--();
    booksToAuthors_Ring2Iterator(BookToAuthor *p){start(p);}
};
    
#endif // ZZ_booksToAuthors_RING2_INCLUDED
