// --------------------------------------------------------

int authors_Ring2::debugFun(Author *tail){
    Author *p,*nxt,*head; int h,t,ret;
    authors_Ring2Iterator it;

    ret=0;
    for(p=it.fromHead(tail), h=0, head=NULL; p; p=it.next(), h++){
        if(h==0)head=p;
        nxt=p->ZZds.ZZauthors.next;
        if(nxt->ZZds.ZZauthors.prev!=p ||nxt==NULL){
            printf("debug error fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZauthors.prev!=tail || tail->ZZds.ZZauthors.next!=head){
        printf("debug tail-head error fromHead\n");
        ret=1;
    }

    for(p=it.fromTail(tail), t=0, head=NULL; p; p=it.next(), t++){
        nxt=p->ZZds.ZZauthors.prev;
        if(nxt==tail)head=p;
        if(nxt->ZZds.ZZauthors.next!=p ||nxt==NULL){
            printf("debug error2 fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZauthors.prev!=tail || tail->ZZds.ZZauthors.next!=head){
        printf("debug tail-head error fromTail\n");
        ret=1;
    }

    if(t!=h){
       printf("debug error counts fromHead=%d, fromTail=%d\n",h,t);
       ret=1;
    }
    return ret;
}

Author* const authors_Ring2::next(Author *tail, Author *c){
    Author* ret=c->ZZds.ZZauthors.next;
    if(c==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

Author* const authors_Ring2::prev(Author *tail, Author *c){
    Author* ret=c->ZZds.ZZauthors.prev;
    if(ret==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

Author* const authors_Ring2::nextRing(Author *c){
    return c->ZZds.ZZauthors.next;
}

Author* const authors_Ring2::prevRing(Author *c){
    return c->ZZds.ZZauthors.prev;
}

Author* authors_Ring2::addHead(Author *tail, Author *c){
    Author *head;

    if(c->ZZds.ZZauthors.next || c->ZZds.ZZauthors.prev){
        printf("authors.addHead() error: element=%d already in authors\n",c);
        return NULL;
    }
    if(tail){
        head=tail->ZZds.ZZauthors.next;
        c->ZZds.ZZauthors.next=head; tail->ZZds.ZZauthors.next=c;
        c->ZZds.ZZauthors.prev=tail; head->ZZds.ZZauthors.prev=c;
    }
    else {tail=c; c->ZZds.ZZauthors.next=c; c->ZZds.ZZauthors.prev=c;}
    return tail; 
}
                          
Author* authors_Ring2::addTail(Author *tail, Author *c){
    if(c->ZZds.ZZauthors.next){
        printf("authors.addTail() error: element=%d already in authors\n",c);
        return NULL;
    }
    addHead(tail,c);
    return c; // returns new tail
}
                          
                          
// append element c2 after element c1
Author* authors_Ring2::append(Author *tail,Author *c1, Author *c2){
    Author *nxt;

    if(c1->ZZds.ZZauthors.next==NULL){
        printf("authors.append() error: element=%d not in authors\n",c1);
        return NULL;
    }
    if(c2->ZZds.ZZauthors.next){
        printf("authors.append() error: element=%d already in authors\n",c2);
        return NULL;
    }
    nxt=c1->ZZds.ZZauthors.next;
    c2->ZZds.ZZauthors.next=nxt; c1->ZZds.ZZauthors.next=c2;
    nxt->ZZds.ZZauthors.prev=c2; c2->ZZds.ZZauthors.prev=c1;
    if(tail==c1)tail=c2;
    return tail;
}
                          
                          
// append element c1 before element c2
void authors_Ring2::insert(Author *c1, Author *c2){
    Author *prv;

    if(c1->ZZds.ZZauthors.next || c1->ZZds.ZZauthors.prev){
        printf("authors.insert() error: element=%d already in authors\n",c1);
        return;
    }
    if(c2->ZZds.ZZauthors.next==NULL || c2->ZZds.ZZauthors.prev==NULL){
        printf("authors.insert() error: element=%d not in authors\n",c2);
        return;
    }
    prv=c2->ZZds.ZZauthors.prev;
    prv->ZZds.ZZauthors.next=c1; c1->ZZds.ZZauthors.next=c2;
    c2->ZZds.ZZauthors.prev=c1; c1->ZZds.ZZauthors.prev=prv;
}
                          
                          
// Compared to the singly-linked ring (Ring1), this function is much
// more efficient.

Author* authors_Ring2::remove(Author *tail, Author *c){
    Author *prv,*nxt; Author *t;

    t=tail;
    if(c->ZZds.ZZauthors.next==NULL || c->ZZds.ZZauthors.prev==NULL){
        printf("authors:remove() error: node=%d not on the list\n",c); return NULL;
    }
    nxt=c->ZZds.ZZauthors.next;
    prv=c->ZZds.ZZauthors.prev;
    if(c==nxt)t=NULL;
    else {
        if(c==t)t=prv;
        prv->ZZds.ZZauthors.next=nxt;
        nxt->ZZds.ZZauthors.prev=prv;
    }
    c->ZZds.ZZauthors.next=c->ZZds.ZZauthors.prev=NULL;
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

Author* authors_Ring2::sort(ZZsortFun cmp, Author *tail){
    Author *a1,*a2,*t,*t1,*t2,*p,*nxt,*subs,*last,*lastA1;
    int stopFlg,choice,closeSublist;

    if(!tail)return tail; // the list is empty
    if(tail==tail->ZZds.ZZauthors.next)return tail; // the list has just one item

    // detect the initial sorted sublists
    for(p=subs=last=tail->ZZds.ZZauthors.next, closeSublist=0; p; p=nxt){
        if(closeSublist){
            last->ZZds.ZZauthors.prev=p;
            last=p;
            closeSublist=0;
        }

        if(p==tail){
            if(subs==last)return tail; // the list is already sorted
            nxt=NULL;
            closeSublist=1;
        }
        else {
            nxt=p->ZZds.ZZauthors.next;
            if((*cmp)(p,p->ZZds.ZZauthors.next)>0)closeSublist=1;
        }

        if(closeSublist)p->ZZds.ZZauthors.next=NULL;
    }
    last->ZZds.ZZauthors.prev=NULL; // close the chain

    // keep sorting adjacent sublists until everything is one list
    for(stopFlg=0; !stopFlg;){ // keep repeating

        // process all sublist pairs
        for(a1=subs, lastA1=NULL; a1; a1=nxt){
            a2=a1->ZZds.ZZauthors.prev;
            if(a2==NULL){
                if(subs==a1)stopFlg=1;
                else { lastA1->ZZds.ZZauthors.prev=a1; a1->ZZds.ZZauthors.prev=NULL;}
                break; // last odd sublist, do nothing
            }
            nxt=a2->ZZds.ZZauthors.prev;

            // the two sublists to be merged start at a1 and a2
           
            for(t1=a1, t2=a2, last=NULL; t1||t2; ){

                if(t1==NULL)choice=2;
                else if(t2==NULL)choice=1;
                else {
                    if((*cmp)(t1,t2)<=0)choice=1;
                    else choice=2;
                }

                if(choice==1){ t=t1; t1=t1->ZZds.ZZauthors.next; }
                else         { t=t2; t2=t2->ZZds.ZZauthors.next; }

                if(last==NULL){
                    if(lastA1==NULL)subs=t;
                    else lastA1->ZZds.ZZauthors.prev=t;
                    lastA1=t; lastA1->ZZds.ZZauthors.prev=NULL;
                }
                else last->ZZds.ZZauthors.next=t;

                last=t;
            }
        }
    }
    tail=last; // from merging the last two sublists

    // reset the ring and all the 'prev' pointers, 'subs' is the list head
    for(p=subs; p; p=nxt){
        nxt=p->ZZds.ZZauthors.next;
        if(nxt)nxt->ZZds.ZZauthors.prev=p;
        else {
            subs->ZZds.ZZauthors.prev=p;
            p->ZZds.ZZauthors.next=subs;
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

void authors_Ring2::merge(Author *s,Author* t){
    Author *u,*v;

    if(s==t)return; // same objects, no action
    u=s->ZZds.ZZauthors.next; v=t->ZZds.ZZauthors.next;
    if(!u || !v ){
        printf("cannot merge/split authors=",s);
        return;
    }
    // re-linking s-u, t-v to s-v, t-u
    t->ZZds.ZZauthors.next=u; u->ZZds.ZZauthors.prev=t;
    s->ZZds.ZZauthors.next=v; v->ZZds.ZZauthors.prev=s;
}


Author* authors_Ring2Iterator::fromHead(Author *p){ 
    Author *ret;

    dir=0;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    ret=tail->ZZds.ZZauthors.next;
    if(ret==tail)nxt=tail=NULL; 
    else nxt=ret->ZZds.ZZauthors.next;
    return ret;
}

Author* authors_Ring2Iterator::fromTail(Author *p){ 
    dir=1;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    nxt=tail->ZZds.ZZauthors.prev;
    if(nxt==tail)nxt=tail=NULL; 
    return p;
}


Author* const authors_Ring2Iterator::next(){ 
    Author *c;

    c=nxt;
    if(dir==0){ if(c==tail)nxt=tail=NULL; else nxt=c->ZZds.ZZauthors.next; }
    else      { if(c==tail)c=nxt=tail=NULL; else nxt=c->ZZds.ZZauthors.prev; }
    return(c);
}


void authors_Ring2Iterator::start(Author *p){ 
    Author *ret;

    tail=p; nxt=NULL;
}


Author* const authors_Ring2Iterator::operator++(){ 
    Author *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZauthors.next;
    }
    else if(tail) {
        ret=tail->ZZds.ZZauthors.next;
        if(ret==tail)tail=NULL;
        else nxt=ret->ZZds.ZZauthors.next;
    }
    else ret=NULL;
    return ret;
}


Author* const authors_Ring2Iterator::operator--(){ 
    Author *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)ret=tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZauthors.prev;
    }
    else if(tail) {
        ret=tail;
        if(ret==tail->ZZds.ZZauthors.next)tail=NULL;
        else nxt=ret->ZZds.ZZauthors.prev;
    }
    else ret=NULL;
    return ret;
}
