@implementation $$_Ring2
// --------------------------------------------------------
+ (int) debugFun: ($1*) tail
{
    $1 *p,*nxt,*head; int h,t,ret;
    $$_Ring2Iterator *it=[[$$_Ring2Iterator new] init];

    ret=0;
    for(p=[it fromHead: tail], h=0, head=NULL; p; p=[it next], h++){
        if(h==0)head=p;
        nxt=p->$0.next;
        if(nxt->$0.prev!=p ||nxt==NULL){
            printf("debug error fromHead index=%llu\n",(U)h);
            ret=1;
            break;
        }
    }
    if(!head || head->$0.prev!=tail || tail->$0.next!=head){
        printf("debug tail-head error fromHead\n");
        ret=1;
    }

    for(p=[it fromTail: tail], t=0, head=NULL; p; p=[it next], t++){
        nxt=p->$0.prev;
        if(nxt==tail)head=p;
        if(nxt->$0.next!=p ||nxt==NULL){
            printf("debug error2 fromHead index=%llu\n",(U)h);
            ret=1;
            break;
        }
    }
    if(!head || head->$0.prev!=tail || tail->$0.next!=head){
        printf("debug tail-head error fromTail\n");
        ret=1;
    }

    if(t!=h){
       printf("debug error counts fromHead=%llu, fromTail=%llu\n",(U)h,(U)t);
       ret=1;
    }
    return ret;
}

// --------------------------------------------------------
+ ($1*) next: ($1*) tail elem: ($1*) c // returns NULL when p is the tail
{
    $1* ret=c->$0.next;
    if(c==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

// --------------------------------------------------------
+ ($1*) prev: ($1*) tail elem: ($1*) c // returns NULL when p is the head
{
    $1* ret=c->$0.prev;
    if(ret==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

// --------------------------------------------------------
+ ($1*) nextRing: ($1*) c // next in the ring
{
    return c->$0.next;
}

// --------------------------------------------------------
+ ($1*) prevRing: ($1*) c // previous in the ring
{
    return c->$0.prev;
}

// --------------------------------------------------------
+ ($1*) addHead: ($1*) tail add: ($1*) c // returns new tail
{
    $1 *head;

    if(c->$0.next || c->$0.prev){
        printf("$$.addHead() error: element=%llu already in $$\n",(U)c);
        return NULL;
    }
    if(tail){
        head=tail->$0.next;
        c->$0.next=head; tail->$0.next=c;
        c->$0.prev=tail; head->$0.prev=c;
    }
    else {tail=c; c->$0.next=c; c->$0.prev=c;}
    return tail; 
}
                          
// --------------------------------------------------------
+ ($1*) addTail: ($1*) tail add: ($1*) c // returns new tail
{
    if(c->$0.next){
        printf("$$.addTail() error: element=%llu already in $$\n",(U)c);
        return NULL;
    }
    [$$_Ring2 addHead: tail add: c];
    return c; // returns new tail
}
                          
                          
// --------------------------------------------------------
// append element c2 after element c1, returns new tail
+ ($1*) append: ($1*) tail after: ($1*) c1 add: ($1*) c2
{
    $1 *nxt;

    if(c1->$0.next==NULL){
        printf("$$.append() error: element=%llu not in $$\n",(U)c1);
        return NULL;
    }
    if(c2->$0.next){
        printf("$$.append() error: element=%llu already in $$\n",(U)c2);
        return NULL;
    }
    nxt=c1->$0.next;
    c2->$0.next=nxt; c1->$0.next=c2;
    nxt->$0.prev=c2; c2->$0.prev=c1;
    if(tail==c1)tail=c2;
    return tail;
}
                          
                          
// --------------------------------------------------------
// insert element c1 before element c2
+ (void) insert: ($1*) c1 before: ($1*) c2
{
    $1 *prv;

    if(c1->$0.next || c1->$0.prev){
        printf("$$.insert() error: element=%llu already in $$\n",(U)c1);
        return;
    }
    if(c2->$0.next==NULL || c2->$0.prev==NULL){
        printf("$$.insert() error: element=%llu not in $$\n",(int)c2);
        return;
    }
    prv=c2->$0.prev;
    prv->$0.next=c1; c1->$0.next=c2;
    c2->$0.prev=c1; c1->$0.prev=prv;
}
                          
                          
// --------------------------------------------------------
// Compared to the singly-linked ring (Ring1), this function is much
// more efficient.

+ ($1*) remove: ($1*) tail elem: ($1*) c
{
    $1 *prv,*nxt; $1 *t;

    t=tail;
    if(c->$0.next==NULL || c->$0.prev==NULL){
        printf("$$:remove() error: node=%llu not on the list\n",(int)c); return NULL;
    }
    nxt=c->$0.next;
    prv=c->$0.prev;
    if(c==nxt)t=NULL;
    else {
        if(c==t)t=prv;
        prv->$0.next=nxt;
        nxt->$0.prev=prv;
    }
    c->$0.next=c->$0.prev=NULL;
    return t;
}


// --------------------------------------------------------
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

+ ($1*) sort: (ZZsortFun) cmpFun tail: ($1*) tail
{
    $1 *a1,*a2,*t,*t1,*t2,*p,*nxt,*subs,*last,*lastA1;
    int stopFlg,choice,closeSublist;

    if(!tail)return tail; // the list is empty
    if(tail==tail->$0.next)return tail; // the list has just one item

    // detect the initial sorted sublists
    for(p=subs=last=tail->$0.next, closeSublist=0; p; p=nxt){
        if(closeSublist){
            last->$0.prev=p;
            last=p;
            closeSublist=0;
        }

        if(p==tail){
            if(subs==last)return tail; // the list is already sorted
            nxt=NULL;
            closeSublist=1;
        }
        else {
            nxt=p->$0.next;
            if((*cmpFun)(p,p->$0.next)>0)closeSublist=1;
        }

        if(closeSublist)p->$0.next=NULL;
    }
    last->$0.prev=NULL; // close the chain

    // keep sorting adjacent sublists until everything is one list
    for(stopFlg=0; !stopFlg;){ // keep repeating

        // process all sublist pairs
        for(a1=subs, lastA1=NULL; a1; a1=nxt){
            a2=a1->$0.prev;
            if(a2==NULL){
                if(subs==a1)stopFlg=1;
                else { lastA1->$0.prev=a1; a1->$0.prev=NULL;}
                break; // last odd sublist, do nothing
            }
            nxt=a2->$0.prev;

            // the two sublists to be merged start at a1 and a2
           
            for(t1=a1, t2=a2, last=NULL; t1||t2; ){

                if(t1==NULL)choice=2;
                else if(t2==NULL)choice=1;
                else {
                    if((*cmpFun)(t1,t2)<=0)choice=1;
                    else choice=2;
                }

                if(choice==1){ t=t1; t1=t1->$0.next; }
                else         { t=t2; t2=t2->$0.next; }

                if(last==NULL){
                    if(lastA1==NULL)subs=t;
                    else lastA1->$0.prev=t;
                    lastA1=t; lastA1->$0.prev=NULL;
                }
                else last->$0.next=t;

                last=t;
            }
        }
    }
    tail=last; // from merging the last two sublists

    // reset the ring and all the 'prev' pointers, 'subs' is the list head
    for(p=subs; p; p=nxt){
        nxt=p->$0.next;
        if(nxt)nxt->$0.prev=p;
        else {
            subs->$0.prev=p;
            p->$0.next=subs;
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

+ (void) merge: ($1*) s second: ($1*) t 
{
    $1 *u,*v;

    if(s==t)return; // same objects, no action
    u=s->$0.next; v=t->$0.next;
    if(!u || !v ){
        printf("cannot merge/split $$=",s);
        return;
    }
    // re-linking s-u, t-v to s-v, t-u
    t->$0.next=u; u->$0.prev=t;
    s->$0.next=v; v->$0.prev=s;
}
@end


@implementation $$_Ring2Iterator
// --------------------------------------------------------
- (id) init{ tail=nxt=NULL; dir=0; return self;}
// --------------------------------------------------------
- ($1*) fromHead: ($1*) p
{ 
    $1 *ret;

    dir=0;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    ret=tail->$0.next;
    if(ret==tail)nxt=tail=NULL; 
    else nxt=ret->$0.next;
    return ret;
}

// --------------------------------------------------------
- ($1*) fromTail: ($1*) p
{ 
    dir=1;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    nxt=tail->$0.prev;
    if(nxt==tail)nxt=tail=NULL; 
    return p;
}


// --------------------------------------------------------
- ($1*) next
{ 
    $1 *c;

    c=nxt;
    if(dir==0){ if(c==tail)nxt=tail=NULL; else nxt=c->$0.next; }
    else      { if(c==tail)c=nxt=tail=NULL; else nxt=c->$0.prev; }
    return(c);
}
@end
