#include <string.h>
class Book;

void bookAbstract_Name::add(Book *p, char *c){
    char* s=p->ZZds.ZZbookAbstract.name;
    if(s){
        printf("bookAbstract:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZbookAbstract.name=c;
}

void bookAbstract_Name::addNew(Book *p, char *c){
    char *s;
    if(!c){
        printf("bookAbstract:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("bookAbstract:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZbookAbstract.name=s;
}

char* bookAbstract_Name::get(Book *p){ return p->ZZds.ZZbookAbstract.name;}

int bookAbstract_Name::compare(Book *p1, Book *p2){
    return strcmp(p1->ZZds.ZZbookAbstract.name, p2->ZZds.ZZbookAbstract.name);
}

char* bookAbstract_Name::remove(Book *p1){char* s=p1->ZZds.ZZbookAbstract.name; p1->ZZds.ZZbookAbstract.name=NULL; return s;}

