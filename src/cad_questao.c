#include "../include/cad_questao.h"
#include "../include/includes.h"
#include "../include/pilha_cadastro.h"



pilha_desq *pilha_geral;
int q1;
int q2;
char caminho_atual[90];
char caminho_final[370];
char lista_atual[200];

/**
 * @brief está função vai criar as pastas que vão receber cada questão, criando o caminho automatico até elas
 * @param const_char* quantidade de questões que a lista tem
 * @return void
 */
void cria_pastas_desq_questao (const char * qtd_questao) {
    int max_questao = atoi(qtd_questao);
    FILE *aqr = fopen(PATH_QTD_TXT, "r");
    fscanf(aqr, "%[^\n]", lista_atual);
    fclose(aqr);
    char caminho[100];

    /*
        este for vai caminhar pelos caminhos criando a quantidade x de pastas necessárias para 
        armazenar a quantidade de questões de cada lista x
    */
    for (int i = 1; i <= max_questao; i++) {
        sprintf(caminho, "mkdir %s/lista%d/questao%d/", PATH_BANCO_LISTAS, atoi(lista_atual), i);
        system(caminho);
    }

    //chamando a função que vai carregar a lista criada para controlar o entrada de dados no front end
    //criar_carregar_lista(qtd_questao);
}

/**
 * @brief Parece com a função de cima porém ela caminha pelas pastas das questões criada pela função de cima \n e cria sub-pastas de entrada e saida onde vão ser guardados os arquivos de entrada e saida dessas respectivas questões
 * @param const_char* quantidade de questẽos da lista
 * @return void
 */
void cria_pastas_entrada_saida (const char *qtd_questao) {
    char caminho[200] = "";
    int max_questao = atoi(qtd_questao);

    for (int i = 1; i <= max_questao; i++) {
        sprintf(caminho, "mkdir %s/lista%d/questao%d/entrada/", PATH_BANCO_LISTAS, atoi(lista_atual), i);
        system(caminho);
        sprintf(caminho, "mkdir %s/lista%d/questao%d/saida/", PATH_BANCO_LISTAS, atoi(lista_atual), i);
        system(caminho);
    }
}

/**
 * @brief função de controle sua unica função é chamar outras na ordem que foram designadas 
 * @param qtd_questao
 * @return void
 */
void cadastro_descricao_questao(const char* qtd_questao) {
    cria_pastas_desq_questao(qtd_questao);
};

/**
 * @brief 
 * @param 
 * @return 
 */


void criar_pilha_geral (const char *qtd_e, const char *qtd_q) {
    q1 = atoi(qtd_q);
    q2 = atoi(qtd_e);
    pilha_geral = criar_pilha();
}

/**
 * @brief 
 * @param 
 * @return 
 */

void gerar_caminhos() {
    strcpy(caminho_atual, "");
    strcpy(caminho_final, "");
};

/**
 * @brief 
 * @param 
 * @return 
 */
void gravar_pilha_geral(const char *caminho, char *caminho_onde_vai) {
    char comando[500];
    sprintf(comando, "cp %s %s", caminho, caminho_onde_vai);
    push(pilha_geral, comando);
}

/**
 * @brief 
 * @param 
 * @return 
 */
void mandar_arquivos() {
    for (int i = pilha_geral -> tamanho; i >= 1; i--) {
        system(pilha_geral -> fim -> comando);
        pop(pilha_geral);
    }
}

/**
 * @brief 
 * @param 
 * @return 
 */
int pilha_tamanho_atual() {
    return get_size(pilha_geral);
}

/**
 * @brief 
 * @param 
 * @return 
 */
void mostrar_pilha() {
    printf("tamanho da pilha %d\n", pilha_geral -> tamanho);
    exibir_lista(pilha_geral);
    mandar_arquivos();
}

void pop_pilha_geral(){
    pop(pilha_geral);
}