class BookToAuthor; // relation
class Book; // entity1
class Author; // entity2
                          
void booksToAuthors_2XtoX::add(BookToAuthor *r,Book *e1,Author *e2){ // equivalent of addTail()
    BookToAuthor *head;

    booksToAuthors_1XtoX::add(r,e1);

    if(r->ZZds.ZZbooksToAuthors.next2){
        printf("booksToAuthors.add() error: element=%d already in booksToAuthors\n",r);
        return;
    }
    if(e2->ZZds.ZZbooksToAuthors.tail2){
        head=e2->ZZds.ZZbooksToAuthors.tail2->ZZds.ZZbooksToAuthors.next2;
        r->ZZds.ZZbooksToAuthors.next2=head; e2->ZZds.ZZbooksToAuthors.tail2->ZZds.ZZbooksToAuthors.next2=r;
        r->ZZds.ZZbooksToAuthors.prev2=e2->ZZds.ZZbooksToAuthors.tail2; head->ZZds.ZZbooksToAuthors.prev2=r;
    }
    else {e2->ZZds.ZZbooksToAuthors.tail2=r->ZZds.ZZbooksToAuthors.next2=r->ZZds.ZZbooksToAuthors.prev2=r;}

    e2->ZZds.ZZbooksToAuthors.tail2=r;
    r->ZZds.ZZbooksToAuthors.parent2=e2;
}

void booksToAuthors_2XtoX::remove(BookToAuthor *r){
    BookToAuthor *prv,*nxt; Author *par;

    booksToAuthors_1XtoX::remove(r);

    nxt=r->ZZds.ZZbooksToAuthors.next2;
    prv=r->ZZds.ZZbooksToAuthors.prev2;
    par=r->ZZds.ZZbooksToAuthors.parent2;
    if(nxt==NULL || prv==NULL || par==NULL){
        printf("booksToAuthors:remove() error: node=%d not on the list\n",r); return;
    }

    if(r==nxt)par->ZZds.ZZbooksToAuthors.tail2=NULL;
    else {
        if(r==par->ZZds.ZZbooksToAuthors.tail2)par->ZZds.ZZbooksToAuthors.tail2=prv;
        prv->ZZds.ZZbooksToAuthors.next2=nxt;
        nxt->ZZds.ZZbooksToAuthors.prev2=prv;
    }
    r->ZZds.ZZbooksToAuthors.next2=r->ZZds.ZZbooksToAuthors.prev2=NULL;
    r->ZZds.ZZbooksToAuthors.parent2=NULL;
}

Author* const booksToAuthors_2XtoX::entity2(BookToAuthor *r){return r->ZZds.ZZbooksToAuthors.parent2;}

BookToAuthor* const booksToAuthors_2XtoX::next2(BookToAuthor *r){   // returns NULL when s is the tail
    Author *p2;
    p2=r->ZZds.ZZbooksToAuthors.parent2;
    if(!r || !p2)return NULL;
    if(r==p2->ZZds.ZZbooksToAuthors.tail2)return NULL;
    return r->ZZds.ZZbooksToAuthors.next2;
}
    

BookToAuthor* const booksToAuthors_2XtoX::prev2(BookToAuthor *r){   // returns NULL when s is the head
    Author *p2; BookToAuthor *prv;
    p2=r->ZZds.ZZbooksToAuthors.parent2;
    if(!r || !p2)return NULL;
    prv=r->ZZds.ZZbooksToAuthors.prev2;
    if(prv==p2->ZZds.ZZbooksToAuthors.tail2)return NULL;
    return prv;
}

BookToAuthor* booksToAuthors_2XtoXIterator::from2(Author *e){
    BookToAuthor *ret;

    tail2=e->ZZds.ZZbooksToAuthors.tail2;
    if(!tail2)return NULL;
    ret=tail2->ZZds.ZZbooksToAuthors.next2;
    if(ret==tail2)nxt2=tail2=NULL; 
    else nxt2=ret->ZZds.ZZbooksToAuthors.next2;
    return ret;
}

BookToAuthor* const booksToAuthors_2XtoXIterator::next2(){
    BookToAuthor *r;

    r=nxt2;
    if(r==tail2)nxt2=tail2=NULL; else nxt2=r->ZZds.ZZbooksToAuthors.next2;
    return r;
}
