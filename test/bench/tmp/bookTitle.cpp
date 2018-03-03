#include <string.h>
class Book;

void bookTitle_Name::add(Book *p, char *c){
    char* s=p->ZZds.ZZbookTitle.name;
    if(s){
        printf("bookTitle:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZbookTitle.name=c;
}

void bookTitle_Name::addNew(Book *p, char *c){
    char *s;
    if(!c){
        printf("bookTitle:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("bookTitle:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZbookTitle.name=s;
}

char* bookTitle_Name::get(Book *p){ return p->ZZds.ZZbookTitle.name;}

int bookTitle_Name::compare(Book *p1, Book *p2){
    return strcmp(p1->ZZds.ZZbookTitle.name, p2->ZZds.ZZbookTitle.name);
}

char* bookTitle_Name::remove(Book *p1){char* s=p1->ZZds.ZZbookTitle.name; p1->ZZds.ZZbookTitle.name=NULL; return s;}

