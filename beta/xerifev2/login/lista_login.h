#ifndef list_login
#define list_login
#include "../includes.h"
typedef struct node {
    char nome[202];
    char senha[202];
    struct node *next;
    struct node *ant;
} no;

typedef struct {
    no *begin;
    no *end;
    int size;
} head;

head *criar_lista ();
no *criar_node (char nome[202], char senha[202]); 
void inserir_no_fim(head *list , char nome[202], char senha[202]);
bool destruir_lista (head *ref);

#endif