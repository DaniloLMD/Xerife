#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

/*
    uma das listas do projeto (usamos essa estrutura no cadastro, login, exibição de questões.....)
*/

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
no *criar_node (char *nome, char *senha); 
void inserir_no_fim(head *list , char *nome, char *senha);
bool destruir_lista (head *ref);

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

/*
    pilha que foi utilizada no cadastro de questões
*/


#define max_comando 150

typedef struct desqnode{
    char comando[max_comando];
    struct desqnode *proximo;
    struct desqnode *anterior;
} desq_node;

typedef struct {
  desq_node *comeco;
  desq_node *fim;
  int tamanho;

} pilha_desq;

pilha_desq *criar_pilha();
desq_node *criar_desq_node (char caminho[max_comando]);
bool destruir_pilha_cad(pilha_desq *ref);
bool push(pilha_desq *ref, char caminho[max_comando]);
bool pop (pilha_desq *ref);
void exibir_lista(pilha_desq *ref);   
int get_size(pilha_desq *ref);


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

desq_node *criar_desq_node (char cmd[max_comando]) {
    desq_node *novo_no = NULL;
    do {
        novo_no = (desq_node*) malloc(sizeof(desq_node)*1);

    } while (novo_no == NULL);

    strcpy(novo_no -> comando, cmd);

    return novo_no;
}

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

int get_size(pilha_desq *ref) {
    return ref -> tamanho;
}

typedef struct {
    int numero_da_lista;
    int qtd_entrada_saida;
    int quantidade_de_questoes;
    int numero_da_questao;
} llista;

struct ThreadParametros{
    pthread_t thread_monitorada;
    pthread_t thread_monitora;
    bool ativa;
    int execucao_status;
    char* comando_executar_execucao;
    bool time_limit_exceeded;
};