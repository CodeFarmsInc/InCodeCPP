// --------------------------------------------------------

int booksToAuthors_Ring2::debugFun(BookToAuthor *tail){
    BookToAuthor *p,*nxt,*head; int h,t,ret;
    booksToAuthors_Ring2Iterator it;

    ret=0;
    for(p=it.fromHead(tail), h=0, head=NULL; p; p=it.next(), h++){
        if(h==0)head=p;
        nxt=p->ZZds.ZZbooksToAuthors.next;
        if(nxt->ZZds.ZZbooksToAuthors.prev!=p ||nxt==NULL){
            printf("debug error fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZbooksToAuthors.prev!=tail || tail->ZZds.ZZbooksToAuthors.next!=head){
        printf("debug tail-head error fromHead\n");
        ret=1;
    }

    for(p=it.fromTail(tail), t=0, head=NULL; p; p=it.next(), t++){
        nxt=p->ZZds.ZZbooksToAuthors.prev;
        if(nxt==tail)head=p;
        if(nxt->ZZds.ZZbooksToAuthors.next!=p ||nxt==NULL){
            printf("debug error2 fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZbooksToAuthors.prev!=tail || tail->ZZds.ZZbooksToAuthors.next!=head){
        printf("debug tail-head error fromTail\n");
        ret=1;
    }

    if(t!=h){
       printf("debug error counts fromHead=%d, fromTail=%d\n",h,t);
       ret=1;
    }
    return ret;
}

BookToAuthor* const booksToAuthors_Ring2::next(BookToAuthor *tail, BookToAuthor *c){
    BookToAuthor* ret=c->ZZds.ZZbooksToAuthors.next;
    if(c==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

BookToAuthor* const booksToAuthors_Ring2::prev(BookToAuthor *tail, BookToAuthor *c){
    BookToAuthor* ret=c->ZZds.ZZbooksToAuthors.prev;
    if(ret==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

BookToAuthor* const booksToAuthors_Ring2::nextRing(BookToAuthor *c){
    return c->ZZds.ZZbooksToAuthors.next;
}

BookToAuthor* const booksToAuthors_Ring2::prevRing(BookToAuthor *c){
    return c->ZZds.ZZbooksToAuthors.prev;
}

BookToAuthor* booksToAuthors_Ring2::addHead(BookToAuthor *tail, BookToAuthor *c){
    BookToAuthor *head;

    if(c->ZZds.ZZbooksToAuthors.next || c->ZZds.ZZbooksToAuthors.prev){
        printf("booksToAuthors.addHead() error: element=%d already in booksToAuthors\n",c);
        return NULL;
    }
    if(tail){
        head=tail->ZZds.ZZbooksToAuthors.next;
        c->ZZds.ZZbooksToAuthors.next=head; tail->ZZds.ZZbooksToAuthors.next=c;
        c->ZZds.ZZbooksToAuthors.prev=tail; head->ZZds.ZZbooksToAuthors.prev=c;
    }
    else {tail=c; c->ZZds.ZZbooksToAuthors.next=c; c->ZZds.ZZbooksToAuthors.prev=c;}
    return tail; 
}
                          
BookToAuthor* booksToAuthors_Ring2::addTail(BookToAuthor *tail, BookToAuthor *c){
    if(c->ZZds.ZZbooksToAuthors.next){
        printf("booksToAuthors.addTail() error: element=%d already in booksToAuthors\n",c);
        return NULL;
    }
    addHead(tail,c);
    return c; // returns new tail
}
                          
                          
// append element c2 after element c1
BookToAuthor* booksToAuthors_Ring2::append(BookToAuthor *tail,BookToAuthor *c1, BookToAuthor *c2){
    BookToAuthor *nxt;

    if(c1->ZZds.ZZbooksToAuthors.next==NULL){
        printf("booksToAuthors.append() error: element=%d not in booksToAuthors\n",c1);
        return NULL;
    }
    if(c2->ZZds.ZZbooksToAuthors.next){
        printf("booksToAuthors.append() error: element=%d already in booksToAuthors\n",c2);
        return NULL;
    }
    nxt=c1->ZZds.ZZbooksToAuthors.next;
    c2->ZZds.ZZbooksToAuthors.next=nxt; c1->ZZds.ZZbooksToAuthors.next=c2;
    nxt->ZZds.ZZbooksToAuthors.prev=c2; c2->ZZds.ZZbooksToAuthors.prev=c1;
    if(tail==c1)tail=c2;
    return tail;
}
                          
                          
// append element c1 before element c2
void booksToAuthors_Ring2::insert(BookToAuthor *c1, BookToAuthor *c2){
    BookToAuthor *prv;

    if(c1->ZZds.ZZbooksToAuthors.next || c1->ZZds.ZZbooksToAuthors.prev){
        printf("booksToAuthors.insert() error: element=%d already in booksToAuthors\n",c1);
        return;
    }
    if(c2->ZZds.ZZbooksToAuthors.next==NULL || c2->ZZds.ZZbooksToAuthors.prev==NULL){
        printf("booksToAuthors.insert() error: element=%d not in booksToAuthors\n",c2);
        return;
    }
    prv=c2->ZZds.ZZbooksToAuthors.prev;
    prv->ZZds.ZZbooksToAuthors.next=c1; c1->ZZds.ZZbooksToAuthors.next=c2;
    c2->ZZds.ZZbooksToAuthors.prev=c1; c1->ZZds.ZZbooksToAuthors.prev=prv;
}
                          
                          
// Compared to the singly-linked ring (Ring1), this function is much
// more efficient.

BookToAuthor* booksToAuthors_Ring2::remove(BookToAuthor *tail, BookToAuthor *c){
    BookToAuthor *prv,*nxt; BookToAuthor *t;

    t=tail;
    if(c->ZZds.ZZbooksToAuthors.next==NULL || c->ZZds.ZZbooksToAuthors.prev==NULL){
        printf("booksToAuthors:remove() error: node=%d not on the list\n",c); return NULL;
    }
    nxt=c->ZZds.ZZbooksToAuthors.next;
    prv=c->ZZds.ZZbooksToAuthors.prev;
    if(c==nxt)t=NULL;
    else {
        if(c==t)t=prv;
        prv->ZZds.ZZbooksToAuthors.next=nxt;
        nxt->ZZds.ZZbooksToAuthors.prev=prv;
    }
    c->ZZds.ZZbooksToAuthors.next=c->ZZds.ZZbooksToAuthors.prev=NULL;
    return t;
}


// Sort the ring and return the new tail.
// The algorithm is based on repeated merging of sorted sublists,
// and is O(n log n). Note that the function is coded without the overhead
// of using recursive functions.
// Even though of the same order, this algorithm is faster than the one
// used for Ring1 - there are repeated searches for the sorted subsets.
//
// Algorithm:
// First traverse the list using the 'next' pointer, and detect sorted
// sublists. Make these sublists NULL-ending and, temporarily, connect
// the heads of these sublists.
// In repeated passes, merge the sublists until there is only one sublist.
// Then convert the representation back to ring, and set the 'prev' pointers.
//
//
// a1   a2            a1        a2      a1
// |    |             |         |       |
// 5->9 8->10->14->16 4->11->37 3->5->7 2->6->12->13     'next' pointer
// |   /|            /|        /|      /|  
// ->-- ------->----- ---->---- --->--- ----->NULL       'prev' pointer
//
//
//
// This gets sorted to:
//
// 5->8->9->10->14->16 3->4->5->7->11->37 2->6->12->13
//  |                 /|                 /|
//  --------->-------- ---------->------- ------>NULL
//
// ---------------------------------------------------------------

BookToAuthor* booksToAuthors_Ring2::sort(ZZsortFun cmp, BookToAuthor *tail){
    BookToAuthor *a1,*a2,*t,*t1,*t2,*p,*nxt,*subs,*last,*lastA1;
    int stopFlg,choice,closeSublist;

    if(!tail)return tail; // the list is empty
    if(tail==tail->ZZds.ZZbooksToAuthors.next)return tail; // the list has just one item

    // detect the initial sorted sublists
    for(p=subs=last=tail->ZZds.ZZbooksToAuthors.next, closeSublist=0; p; p=nxt){
        if(closeSublist){
            last->ZZds.ZZbooksToAuthors.prev=p;
            last=p;
            closeSublist=0;
        }

        if(p==tail){
            if(subs==last)return tail; // the list is already sorted
            nxt=NULL;
            closeSublist=1;
        }
        else {
            nxt=p->ZZds.ZZbooksToAuthors.next;
            if((*cmp)(p,p->ZZds.ZZbooksToAuthors.next)>0)closeSublist=1;
        }

        if(closeSublist)p->ZZds.ZZbooksToAuthors.next=NULL;
    }
    last->ZZds.ZZbooksToAuthors.prev=NULL; // close the chain

    // keep sorting adjacent sublists until everything is one list
    for(stopFlg=0; !stopFlg;){ // keep repeating

        // process all sublist pairs
        for(a1=subs, lastA1=NULL; a1; a1=nxt){
            a2=a1->ZZds.ZZbooksToAuthors.prev;
            if(a2==NULL){
                if(subs==a1)stopFlg=1;
                else { lastA1->ZZds.ZZbooksToAuthors.prev=a1; a1->ZZds.ZZbooksToAuthors.prev=NULL;}
                break; // last odd sublist, do nothing
            }
            nxt=a2->ZZds.ZZbooksToAuthors.prev;

            // the two sublists to be merged start at a1 and a2
           
            for(t1=a1, t2=a2, last=NULL; t1||t2; ){

                if(t1==NULL)choice=2;
                else if(t2==NULL)choice=1;
                else {
                    if((*cmp)(t1,t2)<=0)choice=1;
                    else choice=2;
                }

                if(choice==1){ t=t1; t1=t1->ZZds.ZZbooksToAuthors.next; }
                else         { t=t2; t2=t2->ZZds.ZZbooksToAuthors.next; }

                if(last==NULL){
                    if(lastA1==NULL)subs=t;
                    else lastA1->ZZds.ZZbooksToAuthors.prev=t;
                    lastA1=t; lastA1->ZZds.ZZbooksToAuthors.prev=NULL;
                }
                else last->ZZds.ZZbooksToAuthors.next=t;

                last=t;
            }
        }
    }
    tail=last; // from merging the last two sublists

    // reset the ring and all the 'prev' pointers, 'subs' is the list head
    for(p=subs; p; p=nxt){
        nxt=p->ZZds.ZZbooksToAuthors.next;
        if(nxt)nxt->ZZds.ZZbooksToAuthors.prev=p;
        else {
            subs->ZZds.ZZbooksToAuthors.prev=p;
            p->ZZds.ZZbooksToAuthors.next=subs;
        }
    }
    return tail;
}


// ---------------------------------------------------------------
// This method provides two functions:
// If s and t are on different rings, the two rings merge.
// If s and t are on the same ring, the ring splits into two,
// and s and t can then be used as reference points (new tails).
//
//             spliting                 merging
//
//     ..<...v....t..<..              ......<.....
//     .     |    |    .              .          .
//     ..>...s....u..>..              ....v..t....
//                                        |  |
//                                    ....s..u....
//                                    .          .
//                                    ......<.....
//
// Algorithm:
// Assuming that u=s->next, and v=t->next,
// we only disconnect s-u and t-v, and connect s-v and t-u.
// When s==t or s or t are not in a ring, no action is taken.
// ---------------------------------------------------------------

void booksToAuthors_Ring2::merge(BookToAuthor *s,BookToAuthor* t){
    BookToAuthor *u,*v;

    if(s==t)return; // same objects, no action
    u=s->ZZds.ZZbooksToAuthors.next; v=t->ZZds.ZZbooksToAuthors.next;
    if(!u || !v ){
        printf("cannot merge/split booksToAuthors=",s);
        return;
    }
    // re-linking s-u, t-v to s-v, t-u
    t->ZZds.ZZbooksToAuthors.next=u; u->ZZds.ZZbooksToAuthors.prev=t;
    s->ZZds.ZZbooksToAuthors.next=v; v->ZZds.ZZbooksToAuthors.prev=s;
}


BookToAuthor* booksToAuthors_Ring2Iterator::fromHead(BookToAuthor *p){ 
    BookToAuthor *ret;

    dir=0;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    ret=tail->ZZds.ZZbooksToAuthors.next;
    if(ret==tail)nxt=tail=NULL; 
    else nxt=ret->ZZds.ZZbooksToAuthors.next;
    return ret;
}

BookToAuthor* booksToAuthors_Ring2Iterator::fromTail(BookToAuthor *p){ 
    dir=1;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    nxt=tail->ZZds.ZZbooksToAuthors.prev;
    if(nxt==tail)nxt=tail=NULL; 
    return p;
}


BookToAuthor* const booksToAuthors_Ring2Iterator::next(){ 
    BookToAuthor *c;

    c=nxt;
    if(dir==0){ if(c==tail)nxt=tail=NULL; else nxt=c->ZZds.ZZbooksToAuthors.next; }
    else      { if(c==tail)c=nxt=tail=NULL; else nxt=c->ZZds.ZZbooksToAuthors.prev; }
    return(c);
}


void booksToAuthors_Ring2Iterator::start(BookToAuthor *p){ 
    BookToAuthor *ret;

    tail=p; nxt=NULL;
}


BookToAuthor* const booksToAuthors_Ring2Iterator::operator++(){ 
    BookToAuthor *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZbooksToAuthors.next;
    }
    else if(tail) {
        ret=tail->ZZds.ZZbooksToAuthors.next;
        if(ret==tail)tail=NULL;
        else nxt=ret->ZZds.ZZbooksToAuthors.next;
    }
    else ret=NULL;
    return ret;
}


BookToAuthor* const booksToAuthors_Ring2Iterator::operator--(){ 
    BookToAuthor *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)ret=tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZbooksToAuthors.prev;
    }
    else if(tail) {
        ret=tail;
        if(ret==tail->ZZds.ZZbooksToAuthors.next)tail=NULL;
        else nxt=ret->ZZds.ZZbooksToAuthors.prev;
    }
    else ret=NULL;
    return ret;
}
