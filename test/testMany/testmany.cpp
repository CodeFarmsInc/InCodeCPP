// Test of various forms of the many-to-many organization.
// --------------------------------------------------------------------------
#include <iostream>
using namespace std;
#include "gen.h"

class Student {
public:
    ZZ_Student ZZds; 
    Student(char *name);
    void prt(int end);
};

class Mark {
    int mark;
public:
    ZZ_Mark ZZds; 
    Mark(int m){mark=m;}
    void prt(int end){
        cout << "   mark=" << mark;
        if(end==1)cout << "\n";
        if(end==2)cout << " ";
    }
};

class Takes {
    int mark;
public:
    ZZ_Takes ZZds; 
    Takes(int m){mark=m;}
    void prt(int end){
        cout << "   mark=" << mark;
        if(end==1)cout << "\n";
        if(end==2)cout << " ";
    }
};

class Took {
    int mark;
public:
    ZZ_Took ZZds; 
    Took(int m){mark=m;}
    void prt(int end){
        cout << "   mark=" << mark;
        if(end==1)cout << "\n";
        if(end==2)cout << " ";
    }
};

class Year {
    int year;
public:
    ZZ_Year ZZds; 
    Year(int y){year=y;}
    void prt(int end){
        cout << "Year=" << year;
        if(end==1)cout << "\n";
        if(end==2)cout << " ";
    }
};

class Course {
public:
    ZZ_Course ZZds; 
    Course(char *name);
    void prt(int end);
};


Student::Student(char *name){ // must be after the definition of sName
    sName::addNew(this,name);
}

void Student::prt(int end){
    cout << "Student:" << sName::get(this);
    if(end==1)cout << "\n";
    if(end==2)cout << " ";
}

Course::Course(char *name){ // must be after the definition of sName
    cName::addNew(this,name);
}

void Course::prt(int end){
    cout << "Course:" << cName::get(this);
    if(end==1)cout << "\n";
    if(end==2)cout << " ";
}


int main(void){
    Mark *m; Takes *t; Took *tk;
    Student *s,*s1,*s2,*s3; Course *c1,*c2,*c3; Year *y1,*y2,*y3;
    marks_Iterator it;
    takes_Iterator itt;
    byYear_Iterator ittt;

    // test of 1XtoX
    // -----------------------------------------
    s=new Student("Charles White");
    s->prt(1);

    m=new Mark(3); marks::add(m,s);
    m=new Mark(5); marks::add(m,s);
    m=new Mark(2); marks::add(m,s);
    
    for(m=it.from1(s); m; m=it.next1()){
        m->prt(1);
    }
    cout << "\n";

    // test of 2XtoX
    // -----------------------------------------
    s1=new Student("J.White"); c1=new Course("Calculus");
    s2=new Student("I.Green"); c2=new Course("French");
    s3=new Student("M.Black"); c3=new Course("Physics");

    t=new Takes(1); takes::add(t,s1,c1); 
    t=new Takes(5); takes::add(t,s1,c3); 
    t=new Takes(2); takes::add(t,s2,c1); 
    t=new Takes(3); takes::add(t,s2,c2); 
    t=new Takes(4); takes::add(t,s3,c3); 

    s2->prt(1);
    for(t=itt.from1(s2); t; t=itt.next1()){
        t->prt(2); takes::entity2(t)->prt(1);
    }
    cout << "\n";
    

    c3->prt(1);
    for(t=itt.from2(c3); t; t=itt.next2()){
        t->prt(2); takes::entity1(t)->prt(1);
    }
    cout << "\n";

    // test of 3XtoX
    // -----------------------------------------
    y1=new Year(2001);
    y2=new Year(2002);
    y3=new Year(2003);

    tk=new Took(1); byYear::add(tk,s1,c1,y1);
    tk=new Took(2); byYear::add(tk,s3,c2,y1);
    tk=new Took(3); byYear::add(tk,s1,c2,y3);
    tk=new Took(4); byYear::add(tk,s1,c3,y3);
    tk=new Took(5); byYear::add(tk,s2,c2,y2);

    s1->prt(1);
    for(tk=ittt.from1(s1); tk; tk=ittt.next1()){
        tk->prt(2); byYear::entity2(tk)->prt(2); byYear::entity3(tk)->prt(1);
    }
    cout << "\n";
    

    y3->prt(1);
    for(tk=ittt.from3(y3); tk; tk=ittt.next3()){
        tk->prt(2); byYear::entity1(tk)->prt(2); byYear::entity2(tk)->prt(1);
    }

    
    return(0);
}

#include "gen.cpp"
