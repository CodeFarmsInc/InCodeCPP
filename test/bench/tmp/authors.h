
// -------- data structure DOUBLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class authors_Ring2
// ----------------------------------------------------------
// Ring2 could be derived from Ring2 through inheritance, but
//  (a) The complex functions (sort, remove, merge) are different anyway,
//  (b) we want to minimize the nubmer of classes which will be code generated.
// For these two reasons, Ring2 is coded as a base class.
// ----------------------------------------------------------
#ifndef ZZ_authors_RING2_INCLUDED
#define ZZ_authors_RING2_INCLUDED

class Author;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class authors_Ring2Element {
public:
    Author *next;
    Author *prev;
    authors_Ring2Element(){ next=prev=NULL; }
};

class authors_Ring2 {

    static int debugFun(Author *tail);
public:
    // standard interface
    static Author* addHead(Author *tail, Author *c); // returns new tail
    static Author* addTail(Author *tail, Author *c); // returns new tail
    static Author* append(Author *tail,Author *c1, Author *c2); // returns new tail
    static void insert(Author *c1, Author *c2); // insert c1 before c2
    static Author* remove(Author *tail, Author *c);  // returns new tail, NULL when empty
    static Author* const next(Author *p, Author *c); // returns NULL when p is the tail
    static Author* const prev(Author *p, Author *c); // returns NULL when p is the head
    static Author* const nextRing(Author *c); // next in the ring
    static Author* const prevRing(Author *c); // previous in the ring
    static Author* sort(ZZsortFun cmpFun, Author *tail); // returns the new tail
    static void merge(Author *s,Author *t);

    // historical DOL compatible interface
    static Author* del(Author *tail, Author *c) { return remove(tail,c); }
    static Author* add(Author *tail, Author *c) { return addHead(tail,c); }
    static void ins(Author *c1, Author *c2) { insert(c1,c2); }
    static Author* const fwd(Author *c){return nextRing(c);}
    static Author* const bwd(Author *c){return prevRing(c);}
    
};

class authors_Ring2Iterator {
    Author *tail; // NULL when loop finished
    Author *nxt;  // NULL when starting a new loop
    int dir;  // 0=from head, 1=from tail
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    //                              for(p=it.fromTail(x); p; p=it.next()){...}
    authors_Ring2Iterator(){tail=nxt=NULL; dir=0;}
    Author* fromHead(Author *p);
    virtual Author* fromTail(Author *p);
    virtual Author* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    //                              it.start(x); for(p= --it; p; p= --it){...}
    void start(Author *p);
    Author* const operator++();
    Author* const operator--();
    authors_Ring2Iterator(Author *p){start(p);}
};
    
#endif // ZZ_authors_RING2_INCLUDED
