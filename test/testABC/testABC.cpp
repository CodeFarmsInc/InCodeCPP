// The test problem quoted in Chap.4.9 of the book (The Software Revolution).
// --------------------------------------------------------------------------
#include <iostream>
using namespace std;
#include "gen.h"

class A;
class B;
class C;
#include "testa.h"
#include "testb.h"
#include "testc.h"

int main(void){
    int i,k,n;
    // iterators are automatically provided
    AtoB_Iterator itAB;
    A *ap; B *bp; C *cp;
    
    // create test data one A, three B with two C each.
    ap=new A(0);
    n=1; // for marking all objects
    for(i=1;i<=3;i++){
        bp=new B(n); n++;
        AtoB::addTail(ap,bp);
        for(k=1;k<=2;k++){
           cp=new C(n); n++;
           BtoC::addTail(bp,cp);
        }
    }

    // print the data
    ap->prt();
    itAB.start(ap);
    ITERATE(itAB,bp){
        bp->prt(); // change from the one-file version
    }
    return(0);
}

#include "gen.cpp"
