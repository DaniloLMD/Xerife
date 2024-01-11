#include "../include/includes.h"
#include "../include/rank.h"


// #############        Funcoes da lista        #######################

struct rank_node{
    char nome[100];
    int pontos;
    struct rank_node* next;
    struct rank_node* prev;
};

struct rank_head{
    int size;
    struct rank_node* first;
    struct rank_node* last;
};


RNode* RNode_new(char* nome, int pontos){
    RNode* node = (RNode*) malloc(sizeof(RNode));

    node->next = NULL;
    node->prev = NULL;
    strcpy(node->nome, nome);
    node->pontos = pontos;

    return node;
}

RHead* RHead_new(){
    RHead* head = (RHead*) malloc(sizeof(RHead));

    head->first = NULL;
    head->last = NULL;
    head->size = 0;

    return head;
}

void RHead_delete(RHead** head_ref){
    RHead* head = *head_ref;
    if(head == NULL)
        return;

    RNode* node_atual = head->first;

    if(node_atual != NULL){
        while(node_atual->next != NULL){
            node_atual = node_atual->next;
            free(node_atual->prev);
        }
        free(node_atual);
    }

    free(head);
    *head_ref = NULL;
}

void RHead_ordered_insert(RHead* lista, char* nome, int pontos){
    RNode* node = RNode_new(nome, pontos);

    //1 caso: inserir numa lista vazia
    if(lista->size == 0){
        lista->first = lista->last = node;
    }
    else{
        RNode* node_atual = lista->first;

        while(node_atual != NULL){
            
            //2 caso: node tem pontos maior, entao vai ser inserido antes do node atual
            if(node_atual->pontos < node->pontos){
                if(lista->first == node_atual){
                    lista->first = node;
                }

                node->next = node_atual;
                node->prev = node_atual->prev;
                node_atual->prev = node;

                if(node->prev != NULL){
                    node->prev->next = node;
                }
            
                lista->size++;

                return;
            }

            node_atual = node_atual->next;
        }

        //3 caso: node tem o menor numero de pontos ate agr, entao vai ser inserido no final
        node->prev = lista->last;
        lista->last->next = node;
        lista->last = node;
        node->next = NULL;
    }

    lista->size++;
}


//#########################################################################


/**
 *  @brief atualiza o arquivo de rank, aumentando os pontos do usuario em 1 
 *  @param n_lista numero da lista que deseja atualizar o rank
 *  @param user_name nome do usuario que deseja aumentar os pontos
 *  @return void
*/
void atualiza_rank(int n_lista, char * user_name){
    char rank_path[100];
    //sprintf(rank_path, "%s/lista%d/rank.txt", PATH_BANCO_LISTAS, n_lista);
    sprintf(rank_path, "rank.txt");

    FILE *rank = fopen(rank_path, "r");

    char nome_atual[100];
    int pontos;
    char achou_user = 0;

    char ** matriz_nomes = NULL;
    int * vetor_pontos = NULL;
    int qtd_usuarios = 0; 

    RHead* lista = RHead_new();

    while( fscanf(rank, "%[^,],%d%*c", nome_atual, &pontos) != EOF){
        if(strcmp(nome_atual, user_name) == 0){
            achou_user = 1;
            pontos++;
        }

        RHead_ordered_insert(lista, nome_atual, pontos);
    }

    //se ainda nao achou o user_name, registra ele no ranking
    if(!achou_user){
        RHead_ordered_insert(lista, user_name, 1);
    }
    fclose(rank);

    rank = fopen(rank_path, "w");
    /*RNode* node = lista->first;
    for(int i = 0; i < lista->size; i++){
        fprintf(rank, "%s,%d\n", node->nome, node->pontos);
        node = node->next;
    }**/

    for(RNode *node = lista->first; node != NULL; node = node->next){
        fprintf(rank, "%s,%d\n", node->nome, node->pontos);
    }

    fclose(rank);
    
    RHead_delete(&lista);
}

int main(){
    atualiza_rank(1, "Luis");
}


/*
    danio
    luiz
    Danilo
    catulio
*/