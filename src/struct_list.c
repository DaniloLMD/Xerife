#include "../include/struct_list.h"
#include "../include/includes.h"

#define max_titulo 100
/**
 * @brief cria uma lista duplamente encadeada
 * @return lhead*
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
 * @brief cria um no para lista onde vai ser quardado um titulo[100] de ate 100 caracteres
 * @param char[100] titulo
 * @return lnode*
 */
lnode *criar_l_no(char titulo[max_titulo]) {
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
 * @brief adiciona no fim da lista e concerta o encadeamento  
 * @param lhead* lista
 * @param char[100] titulo
 * @return bool true caso o processo de adicionar no fim ocorra certo || false caso o processo não ocorra certo
 */
bool adicionar_l_fim(lhead *lista, char titulo [max_titulo]) {
    if (lista != NULL){
        lnode *no = criar_l_no(titulo);
        lnode *aux = NULL;

        if (lista -> tamanho == 0) {
            lista -> begin = no;
            lista -> end = no; 
            lista -> begin -> prev = lista -> end;
            lista -> end -> next = lista -> begin;   
        } else {
            aux = lista -> end;
            lista -> end -> next = no;
            lista -> end = no;
            lista -> end -> prev = aux;
            lista -> end -> next = lista -> begin;
            lista -> begin -> prev = lista -> end;

        }
        
        lista -> tamanho++;

        return true;
    } else {
        return false;
    }
};


/**
 * @brief destruir a lista e liberar memoria
 * @param lhead* ponteiro que guarda a referencia para lista
 * @return bool true caso o processo de adicionar no fim ocorra certo || false caso o processo não ocorra certo
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
