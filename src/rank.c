#include "../include/includes.h"
#include "../include/rank.h"

// #############        Funcoes da lista        #######################

/**
 * @brief 
 * @param 
 * @return 
 */
struct rank_node{
    char nome[50];
    int pontos;
    int tentativas;
    struct rank_node* next;
    struct rank_node* prev;
};

/**
 * @brief 
 * @param 
 * @return 
 */
struct rank_head{
    int size;
    struct rank_node* first;
    struct rank_node* last;
};


/**
 * @brief 
 * @param 
 * @return 
 */
RNode* RNode_new(char* nome, int pontos, int tentativas){
    RNode* node = (RNode*) malloc(sizeof(RNode));

    node->next = NULL;
    node->prev = NULL;
    strcpy(node->nome, nome);
    node->pontos = pontos;
    node->tentativas = tentativas;

    return node;
}

/**
 * @brief 
 * @param 
 * @return 
 */
RHead* RHead_new(){
    RHead* head = (RHead*) malloc(sizeof(RHead));

    head->first = NULL;
    head->last = NULL;
    head->size = 0;

    return head;
}

/**
 * @brief 
 * @param 
 * @return 
 */
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

/**
 * @brief 
 * @param 
 * @return 
 */
void RHead_ordered_insert(RHead* lista, char* nome, int pontos, int tentativas){
    RNode* node = RNode_new(nome, pontos, tentativas);

    //1 caso: inserir numa lista vazia
    if(lista->size == 0){
        lista->first = lista->last = node;
    }
    else{
        RNode* node_atual = lista->first;

        while(node_atual != NULL){
            
            //2 caso: node tem pontos maior, ou tem os mesmos pontos mas menos tentativas, entao vai ser inserido antes do node atual
            if(node_atual->pontos < node->pontos || (node_atual->pontos == node->pontos && node_atual->tentativas > node->tentativas)){
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
 *  @param acertou booleano para saber se o usuario acertou a questao ou nao. Se acertou, os pontos aumentam, se nao, apenas as tentativas aumentam
 *  @return void
*/
void atualiza_arquivo_rank(int n_lista, char * user_name, bool acertou){
    char rank_path[100];
    sprintf(rank_path, "%s/lista%d/rank.txt", PATH_BANCO_LISTAS, n_lista);
    
    FILE *rank = fopen(rank_path, "r");

    char nome_atual[100];
    int pontos;
    int tentativas;
    char achou_user = 0;

    char ** matriz_nomes = NULL;
    int * vetor_pontos = NULL;
    int qtd_usuarios = 0; 

    RHead* lista = RHead_new();

    while( fscanf(rank, "%[^,],%d,%d%*c", nome_atual, &pontos, &tentativas) != EOF){
        if(strcmp(nome_atual, user_name) == 0){
            achou_user = 1;
            tentativas++;
            if(acertou == true) pontos++;
        }

        RHead_ordered_insert(lista, nome_atual, pontos, tentativas);
    }

    //se ainda nao achou o user_name, registra ele no ranking
    if(!achou_user){
        tentativas = 1;
        pontos = 0;
        if(acertou == true) pontos++;
        RHead_ordered_insert(lista, user_name, pontos, tentativas);
    }
    fclose(rank);

    rank = fopen(rank_path, "w");

    for(RNode *node = lista->first; node != NULL; node = node->next){
        fprintf(rank, "%s,%d,%d\n", node->nome, node->pontos, node->tentativas);
    }

    fclose(rank);
    
    RHead_delete(&lista);
}


//#######################################   PARTE DE VERIFICAR SE JA FEZ A QUESTAO ################################

/**
 * @brief 
 * @param 
 * @return 
 */
struct queue_registro_node{
    char nome[50];
    int qtd_questoes_feitas;
    int *questoes_feitas;
    QNode* next;
};

/**
 * @brief 
 * @param 
 * @return 
 */
struct queue_registro_lista{
    int size;
    QNode* first;
    QNode* last;
};  

/**
 * @brief 
 * @param 
 * @return 
 */
QNode* QNode_new(char* nome, int qtd_questoes_feitas, int* questoes_feitas){
    QNode* new_node = (QNode*) malloc(sizeof(QNode));
    strcpy(new_node->nome, nome);
    new_node->qtd_questoes_feitas = qtd_questoes_feitas;
    new_node->questoes_feitas = questoes_feitas;
    new_node->next = NULL;

    return new_node;
}

/**
 * @brief 
 * @param 
 * @return 
 */
void QHead_delete(QHead** head_ref){
    QHead* head = *head_ref;

    QNode *atual, *anterior;
    atual = head->first;
    
    while(atual != NULL){
        anterior = atual;
        atual = atual->next;
        if(anterior->questoes_feitas) 
            free(anterior->questoes_feitas);
        free(anterior);
    }

    free(head);
    *head_ref = NULL;
}

/**
 * @brief 
 * @param 
 * @return 
 */
QHead* QHead_new(){
    QHead* new_head = (QHead*) malloc(sizeof(QHead));
    new_head->first = NULL;
    new_head->last = NULL;
    new_head->size = 0;

    return new_head;
}

/**
 * @brief 
 * @param 
 * @return 
 */
void QHead_insert(QHead* head, char* nome, int qtd_questoes_feitas, int* questoes_feitas){
    QNode* new_node = QNode_new(nome, qtd_questoes_feitas, questoes_feitas);
   
    head->size++;
   
    if(head->last == NULL){
        head->first = new_node;
        head->last = new_node;
    }
    else{
        head->last->next = new_node;
    }

    head->last = new_node;
}

/**
 * @param user_name nome do usuario
 * @param n_lista numero da lista
 * @param n_questao numero da questao
 * @return true, se o usuario ja fez a questao ou false, caso contrario
*/
bool checa_se_ja_fez_a_questao(char* user_name, int n_lista, int n_questao){

    char registro_path[50];
    FILE* file;

    int qtd_usuarios;
    char nome_atual[50];
    int qtd_questoes_feitas;
    int questao_atual;
    char lixo[100];

    sprintf(registro_path, "%s/lista%d/registro.txt", PATH_BANCO_LISTAS, n_lista);
    file = fopen(registro_path, "r");
    //le a quantidade de usuarios
    fscanf(file, "%d%*c", &qtd_usuarios);
    while(qtd_usuarios--){
        //le o nome do usuario atual e a quantidade de questoes que ele fez
        fscanf(file, "%[^,],%d%*c", nome_atual, &qtd_questoes_feitas);    
        //se o usuario for o que a gente ta buscado, buscar as questoes
        if(strcmp(nome_atual, user_name) == 0){
            while(qtd_questoes_feitas--){
                fscanf(file, "%d%*c", &questao_atual);
                if(questao_atual == n_questao){
                    return true;
                }
            }
        }
        else{
            fscanf(file, "%[^\n]%*c", lixo);
        }
    }


    fclose(file);
    return false;
}

/**
 * @brief recebe um nome de usuario e retorna a posicao dele no ranking
 * @param user_name string com o nome do usuario
 * @param n_lista numero da lista
 * @param n_questao numero da questao
 * @return posicao do usuario na lista, -1 se nao estiver
*/
int get_posicao(char* user_name, int n_lista, int n_questao){
    
    char rank_path[100];
    sprintf(rank_path, "%s/lista%d/rank.txt", PATH_BANCO_LISTAS, n_lista);
    FILE *rank = fopen(rank_path, "r");

    char nome_atual[100];

    
    int pontos, tentativas;
    int posicao = 1;
    while( fscanf(rank, "%[^,],%d,%d%*c", nome_atual, &pontos, &tentativas) != EOF){
        if(strcmp(nome_atual, user_name) == 0){
            return posicao;
        }
        posicao++;
    }
    
    return -1;
}   

/**
 * 
 * @brief funcao que recebe o numero da lista, o numero da questao e o nome do usuario e registra que tal usuario já respondeu a questao.
 * @return void 
 * @param n_lista numero da lista
 * @param user_name nome do usuario
 * @param n_questao_feita numero da questao que o usuario fez
*/
void atualiza_arquivo_registro(char* user_name, int n_lista, int n_questao_feita){
    char registro_path[50];
    char nome_atual[50];
    int qtd_questoes_feitas;
    int questao_atual;
    int qtd_usuarios;
    int *questoes_feitas;
    FILE* file;
    int achou_usuario;

    QHead* head = QHead_new();
    
    sprintf(registro_path, "%s/lista%d/registro.txt", PATH_BANCO_LISTAS, n_lista);

    //lendo os elementos da fila
    file = fopen(registro_path, "r");
    fscanf(file, "%d%*c", &qtd_usuarios);
  
    achou_usuario = 0;
    for(int k = 0; k < qtd_usuarios; k++){       
        fscanf(file, "%[^,],%d%*c", nome_atual, &qtd_questoes_feitas);

        questoes_feitas = (int*) malloc(qtd_questoes_feitas * sizeof(int));
        for(int i = 0; i < qtd_questoes_feitas; i++){
            fscanf(file, "%d%*c", &questoes_feitas[i]);
        }
        if(strcmp(nome_atual, user_name) == 0){
            questoes_feitas = (int*) realloc(questoes_feitas, (qtd_questoes_feitas + 1) * sizeof(int));
            questoes_feitas[qtd_questoes_feitas] = n_questao_feita;
            qtd_questoes_feitas++;
            achou_usuario = 1;
        }

        QHead_insert(head, nome_atual, qtd_questoes_feitas, questoes_feitas);
        questoes_feitas = NULL;
    }

    //se nao achou o usuario, cadastra ele
    if(!achou_usuario){ 
        qtd_usuarios++;
        qtd_questoes_feitas = 1;
        questoes_feitas = (int*) malloc(qtd_questoes_feitas * sizeof(int));
        questoes_feitas[0] = n_questao_feita;

        QHead_insert(head, user_name, qtd_questoes_feitas, questoes_feitas);
        questoes_feitas = NULL;
    }

    //printando os elementos da fila
    QNode* node_atual = head->first;
    file = fopen(registro_path, "w");
    fprintf(file, "%d\n", qtd_usuarios);

    while(node_atual != NULL){
        fprintf(file, "%s,%d\n", node_atual->nome, node_atual->qtd_questoes_feitas);

        for(int i = 0; i < node_atual->qtd_questoes_feitas; i++){
            fprintf(file, "%d ", node_atual->questoes_feitas[i]);
        }
        fprintf(file, "\n");


        node_atual = node_atual->next;
    }

    fclose(file);
    QHead_delete(&head);

}
