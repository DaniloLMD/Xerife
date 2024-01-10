#include "../include/cadastro_lista.h"
#include "gtk-3.0/gtk/gtk.h"
#include "../include/includes.h"

int qtd_lista = 0;

/**
 * @brief Cadastra o Nome da lista nos arquivos do sistema
 *
 * @param char_const* nome do usuário
 * 
 *
 * @return void
 */
void cadastrar_nome_lista(char const *nome) {
    char nome_da_questao[100] = "";
    char aux[200]= "";
    //construindo o caminho para abrir o arquivo
    char caminho[500];
    strcat(aux, PATH_BANCO_LISTAS);
    strcat(aux, "/");
    strcpy(caminho, aux);
    char pasta[500] = "lista";
    char nome_arq[500] =  "/nome_lista";
    //abrindo o arquivo que guarda a quantidade de listas no sistema
    FILE *file = fopen(PATH_QTD_TXT, "r");  
    char numero[200] = "";
    //lendo a quantidade de listas no sistema
    fscanf(file, "%[^\n]", numero);
    strcat(pasta, numero);
    strcat(caminho, pasta);
    strcat(nome_arq, numero);
    strcat(nome_arq, ".txt");
    strcat(caminho, nome_arq);
    //fechando o arquivo
    fclose(file);
    //copiando o nome da questão que está sendo cadastrada
    strcpy(nome_da_questao, nome);

    ///abrindo o arquivo que a questão vai ser gravada
    FILE *arq = fopen(caminho, "a");
    fputs(nome_da_questao, arq);
    fputc('\n', arq);
    fclose(arq);

};

/**
 * @brief Cria a pasta que vai guardar a lista que está sendo criada, fazendo todo o caminho até ela
 *
 * @return void
 */
void criar_pasta_lista () {
    //mesmo processo da função anterior
    char caminho[2000];
    g_snprintf(caminho, 2000, "mkdir %s/lista", PATH_BANCO_LISTAS);

    FILE *file = fopen(PATH_QTD_TXT, "r");  
    char numero[200] = "";  
    fscanf(file, "%[^\n]", numero);

    strcat(caminho, numero);
    system(caminho);

    fclose(file);
}

void cria_past_qtd_entrada_saida(const char* qtd_entrada_saida, const char* qtd_questoes) {
    char comando[200] = "";
    sprintf(comando, "mkdir dados/banco_listas/lista%d/qtd_entrada_saida%d", qtd_lista, qtd_lista);
    system(comando);
    strcpy(comando, "");
    sprintf(comando, "dados/banco_listas/lista%d/qtd_entrada_saida%d/quantidade%d.txt", qtd_lista, qtd_lista, qtd_lista);
    FILE *file = fopen(comando, "w");
    fprintf(file, "%s\n", qtd_entrada_saida);
    fclose(file);

    //criando o caminho para criar o txt
    strcpy(comando, "");
    sprintf(comando, "dados/banco_listas/lista%d/qtd_entrada_saida%d/quantidade_questoes%d.txt", qtd_lista, qtd_lista, qtd_lista);
    file = fopen(comando, "w");
    fprintf(file, "%s\n", qtd_questoes);
    fclose(file);

};


/**
 * @brief Está função atualiza a quantidade total de listas cadastradas no sistema (qtd.txt)
 * @brief nome arquivo que recebe este dado
 * @return void
 */
void atualizar_qtd_lista () {
    //abrindo e lendo a quantidade de listas no sistema
    FILE *file = NULL;

    file = fopen(PATH_QTD_TXT, "r");
    char quantidade[200] = "";
    int intquantidade = 0;
    
    fscanf(file ,"%[^\n]", quantidade);
    intquantidade = atoi(quantidade);
    intquantidade++;
    qtd_lista = intquantidade;
    fclose(file);


    //atualizando a quantidade de listas no sistema
    file = NULL;
    file = fopen(PATH_QTD_TXT, "w");
    fprintf(file, "%d\n", intquantidade);
    fclose(file);
    
}

/**
 * @brief Está função serve para constrolar todas as outras. Chamando os passos necessários para que uma lista seja cadastrada \n a ordem que eles são chamados \n  
 * @brief  1-atualizar_qtd_lista(); \n
 * @brief  2-criar_pasta_lista(); \n
 * @brief  3-cadastrar_nome_lista(nome); \n
 * @brief  está ordem não pode ser alterada pois a lógica foi pensada assim \n
 * @param const_char* nome do usuário
 *  
 * @return void 
 */
void casdastrar_lista(const char *nome, const char* qtd_entrada_saida, const char *qtd_questoes) {
    atualizar_qtd_lista();
    criar_pasta_lista();
    cria_past_qtd_entrada_saida(qtd_entrada_saida, qtd_questoes);
    cadastrar_nome_lista(nome);
};
