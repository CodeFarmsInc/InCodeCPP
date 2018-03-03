// --------------------------------------------------------
class Book;
class BookToAuthor;

BookToAuthor* const booksToAuthors_LinkedList2::tail(Book *p){return p->ZZds.ZZbooksToAuthors.tail;}

BookToAuthor* const booksToAuthors_LinkedList2::head(Book *p){
    if(!(p->ZZds.ZZbooksToAuthors.tail) || !(p->ZZds.ZZbooksToAuthors.tail->ZZds.ZZbooksToAuthors.next))return NULL;
    else return p->ZZds.ZZbooksToAuthors.tail->ZZds.ZZbooksToAuthors.next;
}

void booksToAuthors_LinkedList2::addHead(Book *p, BookToAuthor *c){
    p->ZZds.ZZbooksToAuthors.tail=booksToAuthors_Ring2::addHead(p->ZZds.ZZbooksToAuthors.tail,c);
}

void booksToAuthors_LinkedList2::addTail(Book *p, BookToAuthor *c){
    p->ZZds.ZZbooksToAuthors.tail=booksToAuthors_Ring2::addTail(p->ZZds.ZZbooksToAuthors.tail,c);
}

void booksToAuthors_LinkedList2::append(Book *p,BookToAuthor *c1, BookToAuthor *c2){
    p->ZZds.ZZbooksToAuthors.tail=booksToAuthors_Ring2::append(p->ZZds.ZZbooksToAuthors.tail,c1,c2);
}

void booksToAuthors_LinkedList2::insert(BookToAuthor *c1, BookToAuthor *c2){booksToAuthors_Ring2::insert(c1,c2);}

void booksToAuthors_LinkedList2::sort(ZZsortFun cmpFun, Book *p){
    p->ZZds.ZZbooksToAuthors.tail=booksToAuthors_Ring2::sort(cmpFun,p->ZZds.ZZbooksToAuthors.tail);
}

void booksToAuthors_LinkedList2::remove(Book *p, BookToAuthor *c){
    p->ZZds.ZZbooksToAuthors.tail=booksToAuthors_Ring2::remove(p->ZZds.ZZbooksToAuthors.tail,c);
}

BookToAuthor* const booksToAuthors_LinkedList2::next(Book *p,BookToAuthor *c){ 
                               return booksToAuthors_Ring2::next(p->ZZds.ZZbooksToAuthors.tail,c);}

BookToAuthor* const booksToAuthors_LinkedList2::prev(Book *p,BookToAuthor *c){ 
                               return booksToAuthors_Ring2::prev(p->ZZds.ZZbooksToAuthors.tail,c);}

BookToAuthor* const booksToAuthors_LinkedList2::nextRing(BookToAuthor *c){ return booksToAuthors_Ring2::nextRing(c);}

BookToAuthor* const booksToAuthors_LinkedList2::prevRing(BookToAuthor *c){ return booksToAuthors_Ring2::prevRing(c);}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void booksToAuthors_LinkedList2::merge(BookToAuthor *s,BookToAuthor *t,Book *p){
    BookToAuthor *pp,*tail; int merge;
 
    tail=p->ZZds.ZZbooksToAuthors.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZbooksToAuthors.next; pp; pp=pp->ZZds.ZZbooksToAuthors.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("booksToAuthors error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZbooksToAuthors.next; pp; pp=pp->ZZds.ZZbooksToAuthors.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("booksToAuthors error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    booksToAuthors_Ring2::merge(s,t); 
    if(merge)p->ZZds.ZZbooksToAuthors.tail=NULL; else p->ZZds.ZZbooksToAuthors.tail=t;
}

BookToAuthor* booksToAuthors_LinkedList2::child(Book *p){
    BookToAuthor* t;
    t=p->ZZds.ZZbooksToAuthors.tail; if(t)return t->ZZds.ZZbooksToAuthors.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void booksToAuthors_LinkedList2::setTail(Book* p,BookToAuthor* c,int check){
    BookToAuthor *pp,*tail;

    tail=p->ZZds.ZZbooksToAuthors.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZbooksToAuthors.next; pp; pp=pp->ZZds.ZZbooksToAuthors.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("booksToAuthors warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZbooksToAuthors.tail=c;
}

void booksToAuthors_LinkedList2Iterator::start(const Book *p){
    booksToAuthors_Ring2Iterator::start(p->ZZds.ZZbooksToAuthors.tail);
}

BookToAuthor* booksToAuthors_LinkedList2Iterator::fromHead(Book *p){
    return booksToAuthors_Ring2Iterator::fromHead(p->ZZds.ZZbooksToAuthors.tail); 
}

BookToAuthor* booksToAuthors_LinkedList2Iterator::fromTail(Book *p){
    return booksToAuthors_Ring2Iterator::fromTail(p->ZZds.ZZbooksToAuthors.tail); 
}
