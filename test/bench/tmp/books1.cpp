// --------------------------------------------------------
class Library;
class Book;

Book* const books_LinkedList2::tail(Library *p){return p->ZZds.ZZbooks.tail;}

Book* const books_LinkedList2::head(Library *p){
    if(!(p->ZZds.ZZbooks.tail) || !(p->ZZds.ZZbooks.tail->ZZds.ZZbooks.next))return NULL;
    else return p->ZZds.ZZbooks.tail->ZZds.ZZbooks.next;
}

void books_LinkedList2::addHead(Library *p, Book *c){
    p->ZZds.ZZbooks.tail=books_Ring2::addHead(p->ZZds.ZZbooks.tail,c);
}

void books_LinkedList2::addTail(Library *p, Book *c){
    p->ZZds.ZZbooks.tail=books_Ring2::addTail(p->ZZds.ZZbooks.tail,c);
}

void books_LinkedList2::append(Library *p,Book *c1, Book *c2){
    p->ZZds.ZZbooks.tail=books_Ring2::append(p->ZZds.ZZbooks.tail,c1,c2);
}

void books_LinkedList2::insert(Book *c1, Book *c2){books_Ring2::insert(c1,c2);}

void books_LinkedList2::sort(ZZsortFun cmpFun, Library *p){
    p->ZZds.ZZbooks.tail=books_Ring2::sort(cmpFun,p->ZZds.ZZbooks.tail);
}

void books_LinkedList2::remove(Library *p, Book *c){
    p->ZZds.ZZbooks.tail=books_Ring2::remove(p->ZZds.ZZbooks.tail,c);
}

Book* const books_LinkedList2::next(Library *p,Book *c){ 
                               return books_Ring2::next(p->ZZds.ZZbooks.tail,c);}

Book* const books_LinkedList2::prev(Library *p,Book *c){ 
                               return books_Ring2::prev(p->ZZds.ZZbooks.tail,c);}

Book* const books_LinkedList2::nextRing(Book *c){ return books_Ring2::nextRing(c);}

Book* const books_LinkedList2::prevRing(Book *c){ return books_Ring2::prevRing(c);}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void books_LinkedList2::merge(Book *s,Book *t,Library *p){
    Book *pp,*tail; int merge;
 
    tail=p->ZZds.ZZbooks.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZbooks.next; pp; pp=pp->ZZds.ZZbooks.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("books error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZbooks.next; pp; pp=pp->ZZds.ZZbooks.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("books error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    books_Ring2::merge(s,t); 
    if(merge)p->ZZds.ZZbooks.tail=NULL; else p->ZZds.ZZbooks.tail=t;
}

Book* books_LinkedList2::child(Library *p){
    Book* t;
    t=p->ZZds.ZZbooks.tail; if(t)return t->ZZds.ZZbooks.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void books_LinkedList2::setTail(Library* p,Book* c,int check){
    Book *pp,*tail;

    tail=p->ZZds.ZZbooks.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZbooks.next; pp; pp=pp->ZZds.ZZbooks.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("books warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZbooks.tail=c;
}

void books_LinkedList2Iterator::start(const Library *p){
    books_Ring2Iterator::start(p->ZZds.ZZbooks.tail);
}

Book* books_LinkedList2Iterator::fromHead(Library *p){
    return books_Ring2Iterator::fromHead(p->ZZds.ZZbooks.tail); 
}

Book* books_LinkedList2Iterator::fromTail(Library *p){
    return books_Ring2Iterator::fromTail(p->ZZds.ZZbooks.tail); 
}
