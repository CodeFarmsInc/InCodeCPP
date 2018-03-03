// ----------------------------------------------------------
//                    2XtoX<Relation,Entity1,Entity2>
//
// This is the most frequently used Many-To-Many relation between
// two entity types. For each recorded relation there is an Relation object.
// ----------------------------------------------------------
// By repeating this code with minor modifications, it is easy
// to derive higher order many-to-many relations:
//    from 2XtoX to derive 2XtoX (this code)
//    from 2XtoX to derive 3XtoX
//    from 3XtoX to derive 4XtoX
//    ... and so on ...
//                                    Jiri Soukup, July 14, 2005
// ----------------------------------------------------------

// ----------------------------------------------------------
#ifndef ZZ_booksToAuthors_2XTOX_INCLUDED
#define ZZ_booksToAuthors_2XTOX_INCLUDED

class BookToAuthor;
class Book;
class Author;

// description of the cooperating classes
class booksToAuthors_2XtoXRelation : public booksToAuthors_1XtoXRelation {
public:
    BookToAuthor *next2;
    BookToAuthor *prev2;
    Author *parent2;
    booksToAuthors_2XtoXRelation() : booksToAuthors_1XtoXRelation(){ next2=prev2=NULL; parent2=NULL;}
};

class booksToAuthors_2XtoXEntity1 : public booksToAuthors_1XtoXEntity1 {
public:
    booksToAuthors_2XtoXEntity1() : booksToAuthors_1XtoXEntity1(){ }
};

class booksToAuthors_2XtoXEntity2 {
public:
    BookToAuthor *tail2;
    booksToAuthors_2XtoXEntity2(){tail2=NULL;}
};


// ----------------------------------------------------------

class booksToAuthors_2XtoX : public booksToAuthors_1XtoX {

public:
    static void add(BookToAuthor *r, Book *e1,Author *e2); // equivalent of addTail()
    static void remove(BookToAuthor *r);

    static Book* const entity1(BookToAuthor *r){return booksToAuthors_1XtoX::entity1(r);}
    static BookToAuthor* const next1(BookToAuthor *r)  {return booksToAuthors_1XtoX::next1(r);}
    static BookToAuthor* const prev1(BookToAuthor *r)  {return booksToAuthors_1XtoX::prev1(r);}

    static Author* const entity2(BookToAuthor *r);
    static BookToAuthor* const next2(BookToAuthor *r);   // returns NULL when s is the tail
    static BookToAuthor* const prev2(BookToAuthor *r);   // returns NULL when s is the head
};

class booksToAuthors_2XtoXIterator : public booksToAuthors_1XtoXIterator {
    // standard interface:          for(r=it.from1(e1); r; r=it.next1()){...}
    // standard interface:          for(r=it.from2(e2); r; r=it.next2()){...}
    BookToAuthor *tail2;
    BookToAuthor *nxt2;
public:
    BookToAuthor* from1(Book *e) {return booksToAuthors_1XtoXIterator::from1(e);}
    BookToAuthor* const next1(){return booksToAuthors_1XtoXIterator::next1();}

    BookToAuthor* from2(Author *e);
    BookToAuthor* const next2();
};

#endif // ZZ_booksToAuthors_2XTOX_INCLUDED
