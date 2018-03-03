class Book;
class BookToAuthor;
                          
void booksToAuthors_Aggregate2::addHead(Book *p, BookToAuthor *c){
    if(c->ZZds.ZZbooksToAuthors.parent){
        printf("booksToAuthors.addHead() error: Child=%d already in booksToAuthors_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZbooksToAuthors.parent=p;
    booksToAuthors_LinkedList2::addHead(p,c);
}
                          
void booksToAuthors_Aggregate2::addTail(Book *p, BookToAuthor *c){
    if(c->ZZds.ZZbooksToAuthors.parent){
        printf("booksToAuthors.addTail() error: Child=%d already in booksToAuthors_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZbooksToAuthors.parent=p;
    booksToAuthors_LinkedList2::addTail(p,c);
}
                          
// append Child c2 after Child c1
void booksToAuthors_Aggregate2::append(BookToAuthor *c1, BookToAuthor *c2){
    Book* p=c1->ZZds.ZZbooksToAuthors.parent;
    if(!p){
        printf("booksToAuthors.append() error: c1=%d not in booksToAuthors_Aggregate2\n",c1);
        return;
    }
    if(c2->ZZds.ZZbooksToAuthors.parent){
        printf("booksToAuthors.addTail() error: c2=%d already in booksToAuthors_Aggregate2\n",c2);
        return;
    }
    c2->ZZds.ZZbooksToAuthors.parent=p;
    booksToAuthors_LinkedList2::append(p,c1,c2);
}
                          
// insert Child c1 before Child c1
void booksToAuthors_Aggregate2::insert(BookToAuthor *c1, BookToAuthor *c2){
    Book* p=c2->ZZds.ZZbooksToAuthors.parent;
    if(!p){
        printf("booksToAuthors.append() error: c2=%d not in booksToAuthors_Aggregate2\n",c2);
        return;
    }
    if(c1->ZZds.ZZbooksToAuthors.parent){
        printf("booksToAuthors.addTail() error: c1=%d already in booksToAuthors_Aggregate2\n",c1);
        return;
    }
    c1->ZZds.ZZbooksToAuthors.parent=p;
    booksToAuthors_LinkedList2::insert(c1,c2);
}
                          
void booksToAuthors_Aggregate2::remove(BookToAuthor *c){
    Book* p=c->ZZds.ZZbooksToAuthors.parent;
    if(p){booksToAuthors_LinkedList2::remove(p,c); c->ZZds.ZZbooksToAuthors.parent=NULL;}
    else printf("WARNING: booksToAuthors.remove() with c=%d already disconnected\n",c);
}

Book* const booksToAuthors_Aggregate2::parent(BookToAuthor *c){
                                                 return c->ZZds.ZZbooksToAuthors.parent; }

