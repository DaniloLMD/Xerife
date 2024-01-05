#include "../include/control_list.h"
/**
 * @brief cria a lista encadeada
 * 
 * @return retura a cabeça de uma lista encadeada
 */
chead *criar_c_lista() {
    chead *lista = NULL;

    do {
        lista = (chead*) malloc(sizeof(chead)*1);
    } while (lista == NULL);

    lista -> begin = NULL;
    lista -> end = NULL;
    lista -> tamanho = 0;

    return lista;
};

/**
 * @brief cria um nó
 * @param int valor inteiro que vai ser armazenado no respectivo nó criado
 * @return retorna um cnode
 */
cnode *criar_c_no(int numero) {
    cnode *no = NULL;
    do {
        no = (cnode*) malloc(sizeof(cnode)*1);
    } while (no == NULL);
    no -> numero_questao = numero;
    no -> next = NULL;
    no -> prev = NULL;
    
    return no;
}; 

/**
 * @brief adiciona no fim da lista encadeada encadeando ela duplamente
 * @param chead ponteior para cabeça da lista
 * @param int valor inteiro que vai ser aclopado no nó e logo em siga na lista
 * @return verdadeiro caso a operação seja bem sucessedida | falso caso o contrario
 */
bool adicionar_c_fim(chead *lista, int numero) {
    if (lista != NULL){
        cnode *no = criar_c_no(numero);
        cnode *aux = NULL;

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
 * @brief libera a memória alocada na construção da lista encadeada
 * @param chead* ponteiro para cabeça da lista encadeada
 * @return verdadeiro caso a operação seja bem sucessedida | falso caso o contrario
 */
bool destruir_c_lista(chead * lista) {
    if (lista != NULL) {
        cnode *aux = NULL;
        cnode *Pnode = lista -> begin;
        for (int i = 0; i < lista -> tamanho; i++) {
            aux = Pnode;
            Pnode = Pnode -> next;
            free(aux);
        }
        free(lista);
        return true;
    } else {
        return false;
    }
};

