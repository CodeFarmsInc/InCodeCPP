// --------------------------------------------------------

int books_Ring2::debugFun(Book *tail){
    Book *p,*nxt,*head; int h,t,ret;
    books_Ring2Iterator it;

    ret=0;
    for(p=it.fromHead(tail), h=0, head=NULL; p; p=it.next(), h++){
        if(h==0)head=p;
        nxt=p->ZZds.ZZbooks.next;
        if(nxt->ZZds.ZZbooks.prev!=p ||nxt==NULL){
            printf("debug error fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZbooks.prev!=tail || tail->ZZds.ZZbooks.next!=head){
        printf("debug tail-head error fromHead\n");
        ret=1;
    }

    for(p=it.fromTail(tail), t=0, head=NULL; p; p=it.next(), t++){
        nxt=p->ZZds.ZZbooks.prev;
        if(nxt==tail)head=p;
        if(nxt->ZZds.ZZbooks.next!=p ||nxt==NULL){
            printf("debug error2 fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZbooks.prev!=tail || tail->ZZds.ZZbooks.next!=head){
        printf("debug tail-head error fromTail\n");
        ret=1;
    }

    if(t!=h){
       printf("debug error counts fromHead=%d, fromTail=%d\n",h,t);
       ret=1;
    }
    return ret;
}

Book* const books_Ring2::next(Book *tail, Book *c){
    Book* ret=c->ZZds.ZZbooks.next;
    if(c==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

Book* const books_Ring2::prev(Book *tail, Book *c){
    Book* ret=c->ZZds.ZZbooks.prev;
    if(ret==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

Book* const books_Ring2::nextRing(Book *c){
    return c->ZZds.ZZbooks.next;
}

Book* const books_Ring2::prevRing(Book *c){
    return c->ZZds.ZZbooks.prev;
}

Book* books_Ring2::addHead(Book *tail, Book *c){
    Book *head;

    if(c->ZZds.ZZbooks.next || c->ZZds.ZZbooks.prev){
        printf("books.addHead() error: element=%d already in books\n",c);
        return NULL;
    }
    if(tail){
        head=tail->ZZds.ZZbooks.next;
        c->ZZds.ZZbooks.next=head; tail->ZZds.ZZbooks.next=c;
        c->ZZds.ZZbooks.prev=tail; head->ZZds.ZZbooks.prev=c;
    }
    else {tail=c; c->ZZds.ZZbooks.next=c; c->ZZds.ZZbooks.prev=c;}
    return tail; 
}
                          
Book* books_Ring2::addTail(Book *tail, Book *c){
    if(c->ZZds.ZZbooks.next){
        printf("books.addTail() error: element=%d already in books\n",c);
        return NULL;
    }
    addHead(tail,c);
    return c; // returns new tail
}
                          
                          
// append element c2 after element c1
Book* books_Ring2::append(Book *tail,Book *c1, Book *c2){
    Book *nxt;

    if(c1->ZZds.ZZbooks.next==NULL){
        printf("books.append() error: element=%d not in books\n",c1);
        return NULL;
    }
    if(c2->ZZds.ZZbooks.next){
        printf("books.append() error: element=%d already in books\n",c2);
        return NULL;
    }
    nxt=c1->ZZds.ZZbooks.next;
    c2->ZZds.ZZbooks.next=nxt; c1->ZZds.ZZbooks.next=c2;
    nxt->ZZds.ZZbooks.prev=c2; c2->ZZds.ZZbooks.prev=c1;
    if(tail==c1)tail=c2;
    return tail;
}
                          
                          
// append element c1 before element c2
void books_Ring2::insert(Book *c1, Book *c2){
    Book *prv;

    if(c1->ZZds.ZZbooks.next || c1->ZZds.ZZbooks.prev){
        printf("books.insert() error: element=%d already in books\n",c1);
        return;
    }
    if(c2->ZZds.ZZbooks.next==NULL || c2->ZZds.ZZbooks.prev==NULL){
        printf("books.insert() error: element=%d not in books\n",c2);
        return;
    }
    prv=c2->ZZds.ZZbooks.prev;
    prv->ZZds.ZZbooks.next=c1; c1->ZZds.ZZbooks.next=c2;
    c2->ZZds.ZZbooks.prev=c1; c1->ZZds.ZZbooks.prev=prv;
}
                          
                          
// Compared to the singly-linked ring (Ring1), this function is much
// more efficient.

Book* books_Ring2::remove(Book *tail, Book *c){
    Book *prv,*nxt; Book *t;

    t=tail;
    if(c->ZZds.ZZbooks.next==NULL || c->ZZds.ZZbooks.prev==NULL){
        printf("books:remove() error: node=%d not on the list\n",c); return NULL;
    }
    nxt=c->ZZds.ZZbooks.next;
    prv=c->ZZds.ZZbooks.prev;
    if(c==nxt)t=NULL;
    else {
        if(c==t)t=prv;
        prv->ZZds.ZZbooks.next=nxt;
        nxt->ZZds.ZZbooks.prev=prv;
    }
    c->ZZds.ZZbooks.next=c->ZZds.ZZbooks.prev=NULL;
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

Book* books_Ring2::sort(ZZsortFun cmp, Book *tail){
    Book *a1,*a2,*t,*t1,*t2,*p,*nxt,*subs,*last,*lastA1;
    int stopFlg,choice,closeSublist;

    if(!tail)return tail; // the list is empty
    if(tail==tail->ZZds.ZZbooks.next)return tail; // the list has just one item

    // detect the initial sorted sublists
    for(p=subs=last=tail->ZZds.ZZbooks.next, closeSublist=0; p; p=nxt){
        if(closeSublist){
            last->ZZds.ZZbooks.prev=p;
            last=p;
            closeSublist=0;
        }

        if(p==tail){
            if(subs==last)return tail; // the list is already sorted
            nxt=NULL;
            closeSublist=1;
        }
        else {
            nxt=p->ZZds.ZZbooks.next;
            if((*cmp)(p,p->ZZds.ZZbooks.next)>0)closeSublist=1;
        }

        if(closeSublist)p->ZZds.ZZbooks.next=NULL;
    }
    last->ZZds.ZZbooks.prev=NULL; // close the chain

    // keep sorting adjacent sublists until everything is one list
    for(stopFlg=0; !stopFlg;){ // keep repeating

        // process all sublist pairs
        for(a1=subs, lastA1=NULL; a1; a1=nxt){
            a2=a1->ZZds.ZZbooks.prev;
            if(a2==NULL){
                if(subs==a1)stopFlg=1;
                else { lastA1->ZZds.ZZbooks.prev=a1; a1->ZZds.ZZbooks.prev=NULL;}
                break; // last odd sublist, do nothing
            }
            nxt=a2->ZZds.ZZbooks.prev;

            // the two sublists to be merged start at a1 and a2
           
            for(t1=a1, t2=a2, last=NULL; t1||t2; ){

                if(t1==NULL)choice=2;
                else if(t2==NULL)choice=1;
                else {
                    if((*cmp)(t1,t2)<=0)choice=1;
                    else choice=2;
                }

                if(choice==1){ t=t1; t1=t1->ZZds.ZZbooks.next; }
                else         { t=t2; t2=t2->ZZds.ZZbooks.next; }

                if(last==NULL){
                    if(lastA1==NULL)subs=t;
                    else lastA1->ZZds.ZZbooks.prev=t;
                    lastA1=t; lastA1->ZZds.ZZbooks.prev=NULL;
                }
                else last->ZZds.ZZbooks.next=t;

                last=t;
            }
        }
    }
    tail=last; // from merging the last two sublists

    // reset the ring and all the 'prev' pointers, 'subs' is the list head
    for(p=subs; p; p=nxt){
        nxt=p->ZZds.ZZbooks.next;
        if(nxt)nxt->ZZds.ZZbooks.prev=p;
        else {
            subs->ZZds.ZZbooks.prev=p;
            p->ZZds.ZZbooks.next=subs;
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

void books_Ring2::merge(Book *s,Book* t){
    Book *u,*v;

    if(s==t)return; // same objects, no action
    u=s->ZZds.ZZbooks.next; v=t->ZZds.ZZbooks.next;
    if(!u || !v ){
        printf("cannot merge/split books=",s);
        return;
    }
    // re-linking s-u, t-v to s-v, t-u
    t->ZZds.ZZbooks.next=u; u->ZZds.ZZbooks.prev=t;
    s->ZZds.ZZbooks.next=v; v->ZZds.ZZbooks.prev=s;
}


Book* books_Ring2Iterator::fromHead(Book *p){ 
    Book *ret;

    dir=0;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    ret=tail->ZZds.ZZbooks.next;
    if(ret==tail)nxt=tail=NULL; 
    else nxt=ret->ZZds.ZZbooks.next;
    return ret;
}

Book* books_Ring2Iterator::fromTail(Book *p){ 
    dir=1;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    nxt=tail->ZZds.ZZbooks.prev;
    if(nxt==tail)nxt=tail=NULL; 
    return p;
}


Book* const books_Ring2Iterator::next(){ 
    Book *c;

    c=nxt;
    if(dir==0){ if(c==tail)nxt=tail=NULL; else nxt=c->ZZds.ZZbooks.next; }
    else      { if(c==tail)c=nxt=tail=NULL; else nxt=c->ZZds.ZZbooks.prev; }
    return(c);
}


void books_Ring2Iterator::start(Book *p){ 
    Book *ret;

    tail=p; nxt=NULL;
}


Book* const books_Ring2Iterator::operator++(){ 
    Book *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZbooks.next;
    }
    else if(tail) {
        ret=tail->ZZds.ZZbooks.next;
        if(ret==tail)tail=NULL;
        else nxt=ret->ZZds.ZZbooks.next;
    }
    else ret=NULL;
    return ret;
}


Book* const books_Ring2Iterator::operator--(){ 
    Book *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)ret=tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZbooks.prev;
    }
    else if(tail) {
        ret=tail;
        if(ret==tail->ZZds.ZZbooks.next)tail=NULL;
        else nxt=ret->ZZds.ZZbooks.prev;
    }
    else ret=NULL;
    return ret;
}
