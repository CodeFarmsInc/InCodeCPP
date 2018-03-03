// ----------------------------------------------------------
//                    1XtoX<Relation,Entity>
// ----------------------------------------------------------
// This data organization is not intended for direct use. It is the root
// organization of ManyToMany for 2,3 or more participating classes.
// Note that 1XtoX is derived from Aggregate2<>, but the 
// parameters are reversed.
//                                    Jiri Soukup, July 14, 2005
// ----------------------------------------------------------

// ----------------------------------------------------------
#ifndef ZZ_booksToAuthors_1XTOX_INCLUDED
#define ZZ_booksToAuthors_1XTOX_INCLUDED

class BookToAuthor;
class Book;

// description of the cooperating classes
class booksToAuthors_1XtoXRelation : public booksToAuthors_Aggregate2Child {
public:
    booksToAuthors_1XtoXRelation() : booksToAuthors_Aggregate2Child(){ }
};

class booksToAuthors_1XtoXEntity1 : public booksToAuthors_Aggregate2Parent {
public:
    booksToAuthors_1XtoXEntity1() : booksToAuthors_Aggregate2Parent(){ }
};

// ----------------------------------------------------------

class booksToAuthors_1XtoX : private booksToAuthors_Aggregate2 {

public:
    static void add(BookToAuthor *r, Book *e){ booksToAuthors_Aggregate2::addTail(e,r);}
    static void remove(BookToAuthor *r){ booksToAuthors_Aggregate2::remove(r); }
    static Book* const entity1(BookToAuthor *r){ return booksToAuthors_Aggregate2::parent(r); }
    static BookToAuthor* const next1(BookToAuthor *r){ // returns NULL when s is the tail
        return booksToAuthors_Aggregate2::next(r);
    }
    static BookToAuthor* const prev1(BookToAuthor *r){ // returns NULL when s is the head
        return booksToAuthors_Aggregate2::prev(r);
    }
};

class booksToAuthors_1XtoXIterator : private booksToAuthors_Aggregate2Iterator {
    // standard interface:          for(r=it.from1(e); r; r=it.next1()){...}
public:
    BookToAuthor* from1(Book *e){return booksToAuthors_Aggregate2Iterator::fromHead(e);}
    BookToAuthor* const next1(){return booksToAuthors_Aggregate2Iterator::next();}
};

#endif // ZZ_booksToAuthors_1XTOX_INCLUDED
