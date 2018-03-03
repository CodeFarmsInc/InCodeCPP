#ifndef ZZ_CODEGEN_INCLUDE
#define ZZ_CODEGEN_INCLUDE


#define PPF_PATH "c:\ppf\factory.h\factory.h"
#include "..\..\lib\general.h"

class Library;
class Book;
class Author;
class BookToAuthor;

#include "tmp/books.h"
#include "tmp/books1.h"
#include "tmp/bookTitle.h"
#include "tmp/bookAbstract.h"
#include "tmp/authors.h"
#include "tmp/authors1.h"
#include "tmp/authorName.h"
#include "tmp/booksToAuthors.h"
#include "tmp/booksToAuthors1.h"
#include "tmp/booksToAuthors2.h"
#include "tmp/booksToAuthors3.h"
#include "tmp/booksToAuthors4.h"

// -----------------------------------------------
typedef class books_LinkedList2 books;
typedef class bookTitle_Name bookTitle;
typedef class bookAbstract_Name bookAbstract;
typedef class authors_LinkedList2 authors;
typedef class authorName_Name authorName;
typedef class booksToAuthors_2XtoX booksToAuthors;
// -----------------------------------------------


class ZZ_Library {
public:
    books_LinkedList2Parent ZZbooks;
    authors_LinkedList2Parent ZZauthors;
};

class ZZ_Book {
public:
    books_LinkedList2Child ZZbooks;
    bookTitle_NameParent ZZbookTitle;
    bookAbstract_NameParent ZZbookAbstract;
    booksToAuthors_2XtoXEntity1 ZZbooksToAuthors;
};

class ZZ_Author {
public:
    authors_LinkedList2Child ZZauthors;
    authorName_NameParent ZZauthorName;
    booksToAuthors_2XtoXEntity2 ZZbooksToAuthors;
};

class ZZ_BookToAuthor {
public:
    booksToAuthors_2XtoXRelation ZZbooksToAuthors;
};

typedef books_LinkedList2Iterator books_Iterator;
typedef authors_LinkedList2Iterator authors_Iterator;
typedef booksToAuthors_2XtoXIterator booksToAuthors_Iterator;

#endif // ZZ_CODEGEN_INCLUDE
