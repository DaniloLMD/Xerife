#include "../include/struct_list.h"

/**
 * @brief 
 * @param 
 * @return
 */
lhead *criar_l_lista() {
    lhead *lista = NULL;

    do {
        lista = (lhead*) malloc(sizeof(lhead)*1);
    } while (lista == NULL);

    lista -> begin = NULL;
    lista -> end = NULL;
    lista -> tamanho = 0;

    return lista;
};

/**
 * @brief 
 * @param 
 * @return
 */
lnode *criar_l_no(char titulo[100]) {
    lnode *no = NULL;
    do {
        no = (lnode*) malloc(sizeof(lnode)*1);
    } while (no == NULL);
    no -> titulo = (char*) malloc(sizeof(char)*200);
    no -> next = NULL;
    no -> prev = NULL;
    strcpy(no -> titulo, titulo);
    
    return no;
}; 

/**
 * @brief 
 * @param 
 * @return
 */
bool adicionar_l_fim(lhead *lista, char titulo [100]) {
    if (lista != NULL){
        lnode *no = criar_l_no(titulo);
        lnode *aux = NULL;

        if (lista -> tamanho == 0) {
            lista -> begin = no;
            lista -> end = no;    
        } else {
            aux = lista -> end;
            lista -> end = no;
            lista -> end -> prev = aux;
            aux -> next = lista -> end;
        }
        
        lista -> tamanho++;

        return true;
    } else {
        return false;
    }
};


/**
 * @brief 
 * @param 
 * @return
 */
bool destruir_l_lista(lhead * lista) {
    if (lista != NULL) {
        lnode *aux = NULL;
        lnode *Pnode = lista -> begin;
        for (int i = 0; i < lista -> tamanho; i++) {
            aux = Pnode;
            Pnode = Pnode -> next;
            free(aux->titulo);
            free(aux);
        }
        free(lista);
        return true;
    } else {
        return false;
    }
};
