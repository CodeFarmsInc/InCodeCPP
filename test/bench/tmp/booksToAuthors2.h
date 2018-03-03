
// ----------------- data structure Aggregate ---------------
// ----------------------------------------------------------
// EQUIVALENT OF:
//     template <class Parent, class Child> class booksToAuthors_Aggregate :
//                                   public booksToAuthors_LinkedList<Parent,Child>
// INHERITS FROM: LinkedList
// ----------------------------------------------------------
#ifndef ZZ_booksToAuthors_AGGREGATE2_INCLUDED
#define ZZ_booksToAuthors_AGGREGATE2_INCLUDED

class Book;
class BookToAuthor;

// description of the cooperating classes
class booksToAuthors_Aggregate2Parent : public booksToAuthors_LinkedList2Parent {
public:
    booksToAuthors_Aggregate2Parent() : booksToAuthors_LinkedList2Parent(){ }
};

class booksToAuthors_Aggregate2Child : public booksToAuthors_LinkedList2Child {
public:
    Book* parent;
    booksToAuthors_Aggregate2Child() : booksToAuthors_LinkedList2Child(){ parent=NULL; }
};

// the following class is used when Parent==Child
class booksToAuthors_Aggregate2ParentAggregate2Child 
       : public booksToAuthors_LinkedList2ParentLinkedList2Child {
public:
    Book* parent;
    booksToAuthors_Aggregate2ParentAggregate2Child()
       : booksToAuthors_LinkedList2ParentLinkedList2Child(){ parent=NULL; }
};

// ----------------------------------------------------------

class booksToAuthors_Aggregate2 : public booksToAuthors_LinkedList2 {

public:
    static void addHead(Book *p, BookToAuthor *c);
    static void addTail(Book *p, BookToAuthor *c);
    static void append(BookToAuthor *c1, BookToAuthor *c2); // has a different syntax
    static void insert(BookToAuthor *c1, BookToAuthor *c2); 
    static void remove(BookToAuthor *c);             // has a different syntax
    static Book* const parent(BookToAuthor *c);    // is new
    static BookToAuthor* const next(BookToAuthor *c){ // returns NULL when s is the tail
        return booksToAuthors_LinkedList2::next(parent(c),c);
    }
    static BookToAuthor* const prev(BookToAuthor *c){ // returns NULL when s is the head
        return booksToAuthors_LinkedList2::prev(parent(c),c);
    }
    // ...
};

class booksToAuthors_Aggregate2Iterator : public booksToAuthors_LinkedList2Iterator {
};

#endif // ZZ_booksToAuthors_AGGREGATE2_INCLUDED
