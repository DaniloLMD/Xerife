#ifndef CONTROL_LIST
#define CONTROL_LIST
#include "includes.h"

typedef struct c_node {
    int numero_questao;
    struct c_node *next;
    struct c_node *prev;
} cnode;

typedef struct c_head {
    int tamanho;
    cnode *begin;
    cnode *end;
} chead;

chead *criar_c_lista();
cnode *criar_c_no(int);

bool adicionar_c_fim(chead *, int);
bool destruir_c_lista(chead *);

#endif