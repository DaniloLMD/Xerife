#include "pilha_cadastro.h"
#include <gtk-3.0/gtk/gtk.h>


#define max_comando 150


/**
 * @brief cria uma pilha nova e aloca memória pra ela
 * @return pilha_desq* ponteiro que referência a pilha que foi criada
 */
pilha_desq *criar_pilha() {
    pilha_desq *nova = NULL;
    do {
        nova = (pilha_desq*) malloc(sizeof(pilha_desq)*1);
    } while (nova == NULL);

    nova -> comeco = NULL;
    nova -> fim = NULL;
    nova -> tamanho = 0;

    return nova;
}

/**
 * @brief cria um nó que vai ser adicionado na pilha
 * @param char[370] comando que vai ser adicionado na pilha
 * @return desq_node* 
 */
desq_node *criar_desq_node (char cmd[max_comando]) {
    desq_node *novo_no = NULL;
    do {
        novo_no = (desq_node*) malloc(sizeof(desq_node)*1);

    } while (novo_no == NULL);

    strcpy(novo_no -> comando, cmd);

    return novo_no;
}

/**
 * @brief está função vai destruir a pilha e liberar memoria
 * @param pilha_desq* referência para a pilha que vai ser exibida
 * @return bool true caso o processo de adicionar no fim ocorra certo || false caso o processo não ocorra certo
 */
bool destruir_pilha_cad(pilha_desq *ref) {
    desq_node *node_ref = ref -> comeco;
    desq_node *node_aux = NULL;

    if (ref != NULL) {
        for (int i = 0; i < ref -> tamanho; i++) {
            node_aux = node_ref;
            free(node_aux);
            node_ref = node_ref -> proximo;
        }   
    } else {
        return false;
    }

    free(ref);
    return true;
}

/**
 * @brief está função adicionar no fim da pilha
 * @param pilha_desq* referência para a pilha que vai ser exibida
 * @param char[370] comando que vai ser adicionado na pilha
 * @return bool true caso o processo de adicionar no fim ocorra certo || false caso o processo não ocorra certo
 */
bool push(pilha_desq *ref, char comando[max_comando]) {
    if (ref != NULL) {
        desq_node *novo_no = criar_desq_node(comando);
        desq_node *aux = NULL;
        if (ref -> tamanho == 0) {
            ref -> comeco = novo_no;
            ref -> fim = novo_no;
        } else {
            aux = ref -> fim;
            ref -> fim -> proximo = novo_no;
            novo_no -> anterior = ref -> fim;
            ref -> fim = novo_no;
        }
    } else {
        return false;
    }

    ref -> tamanho++;
    return true;
}

/**
 * @brief está função vai retirar o topo da pilha
 * @param pilha_desq* referência para a pilha que vai ser exibida
 * @return bool true caso o processo de adicionar no fim ocorra certo || false caso o processo não ocorra certo
 */
bool pop (pilha_desq *ref) {
    desq_node *aux_node = ref -> fim;
    if (ref != NULL) {
        ref -> fim = ref -> fim -> anterior;
        free(aux_node);
    } else {
        return false;
    }
    ref -> tamanho--;
    return true;
}

/**
 * @brief esta função vai retornar o tamanho total da pilha
 * @param pilha_desq* referência para a pilha que vai ser exibida
 * @return o inteiro que vai corresponder o tamanho total da pilha
 */
int get_size(pilha_desq *ref) {
    return ref -> tamanho;
}

/**
 * @brief esta função vai exibir toda a pilha nó a nó
 * @param pilha_desq* referência para a pilha que vai ser exibida
 * @return void
 */
void exibir_lista(pilha_desq *ref) {
    desq_node *node = ref -> comeco;
    for (int i = 0; i < ref -> tamanho; i++) {
        g_print("%s\n", node -> comando);
        node = node -> proximo;
    }
}   
