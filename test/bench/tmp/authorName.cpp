#include <string.h>
class Author;

void authorName_Name::add(Author *p, char *c){
    char* s=p->ZZds.ZZauthorName.name;
    if(s){
        printf("authorName:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZauthorName.name=c;
}

void authorName_Name::addNew(Author *p, char *c){
    char *s;
    if(!c){
        printf("authorName:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("authorName:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZauthorName.name=s;
}

char* authorName_Name::get(Author *p){ return p->ZZds.ZZauthorName.name;}

int authorName_Name::compare(Author *p1, Author *p2){
    return strcmp(p1->ZZds.ZZauthorName.name, p2->ZZds.ZZauthorName.name);
}

char* authorName_Name::remove(Author *p1){char* s=p1->ZZds.ZZauthorName.name; p1->ZZds.ZZauthorName.name=NULL; return s;}

