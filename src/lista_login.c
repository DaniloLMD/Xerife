#include "../include/lista_login.h"
#include "../include/includes.h"

/**
 * @brief 
 * @param 
 * @return
 */
head *criar_lista () {
    head *list = NULL;
    do { 
        list = (head*) malloc(sizeof(head)*1);
    } while (list == NULL);
    list -> begin = NULL;
    list -> end = NULL;

    list -> size = 0;
    return list;
};

/**
 * @brief 
 * @param 
 * @return
 */
no *criar_node (char *nome, char *senha) {
    no *node = NULL;
    do {
        node = (no*) malloc(sizeof(no)*1);
    } while (node == NULL);
    
    node -> ant = NULL; 
    node -> next = NULL;
    
    strcpy(node -> nome, nome);
    strcpy(node -> senha, senha);
    return node;
}; 

/**
 * @brief 
 * @param 
 * @return
 */
void inserir_no_fim(head *list, char *nome, char *senha) {
    no *node = criar_node(nome, senha);
    no *ref = NULL;

    if (list != NULL) {
        if (list -> size == 0) {
            list -> begin = node;
            list -> end = node;
        } else {
            ref = list -> end;
            list -> end = node;
            list -> end -> ant = ref;
            ref -> next = list -> end;
        }
        list -> size++;
    } else {
        printf("error");
    }
}; 

/**
 * @brief 
 * @param 
 * @return
 */
bool destruir_lista (head *ref) {
    no *node = ref -> begin;
    no *aux = NULL;

    for (int i = 0; i < ref -> size; i++) {
        aux = node;
        node  = node -> next;
        free(aux);
    }
    free(ref);
}