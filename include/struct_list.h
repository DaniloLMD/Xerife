#ifndef STRUCT_LIST
#define STRUCT_LIST
#include "includes.h"

typedef struct l_node {
    char *titulo;
    int id;
    struct l_node *next;
    struct l_node *prev;
} lnode;

typedef struct l_head {
    int tamanho;
    lnode *begin;
    lnode *end;
} lhead;

lhead *criar_l_lista();
lnode *criar_l_no(char [100]);

bool adicionar_l_fim(lhead *, char[100]);
bool destruir_l_lista(lhead *);

#endif