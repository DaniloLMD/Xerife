#include "../include/cadastro_lista.h"
#include "gtk-3.0/gtk/gtk.h"
#include "../include/includes.h"
#include "../include/envios.h"

int qtd_lista = 0;
#define tamanho_dos_caminhos 150

bool compara_string (const char *nome, char texto[]) {
    if (strlen(nome) != strlen(texto)) return false;
    else {
        for (int i = 0; i < strlen(nome); i++) {
            if(nome[i] != texto[i]) return false;
        }
    }
}

bool lista_ja_cadastrada (const char *nome) {
    char texto[tamanho_dos_caminhos] = "";
    char caminho[tamanho_dos_caminhos];
    int n_list = 0;

    FILE *file = NULL;
    file = fopen(PATH_QTD_TXT, "r");
    fscanf(file ,"%[^\n]", texto);
    n_list = atoi(texto);
    fclose(file);
    strcpy(texto, "");

    for (int i = 1; i <= n_list; i++) {
        sprintf(caminho, "%s/lista%d/nome_lista.txt", PATH_BANCO_LISTAS,i);
        file = fopen(caminho, "r");
        fscanf(file, "%[^\n]", texto);

        if (compara_string(nome, texto)) {
            return true;
        }
        fclose(file);
    }

    return false;
};

bool verificar_caractere_padrao(const char* nome) {
    for (int i = 0; i < strlen(nome); i++) {
        if ((nome[i] >= 'a' && nome[i] <= 'z') || (nome[i] >= 'A' && nome[i] <= 'Z') ) return true;
    }
    return false;
};

bool contem_apenas_numeros(const char *stringx) {
    for (int i = 0; i < strlen(stringx); i++) {
        if (stringx[i] >= '0' && stringx[i] <= '9') continue;
        return false;
    }
    return true;
};


int verificacoes_nome_lista(const char* nome) {
    if (verificar_caractere_padrao(nome) && !lista_ja_cadastrada(nome)) {
        return 1;
    }
    else if (lista_ja_cadastrada(nome)) {
        return 2;
    }
    else if (!verificar_caractere_padrao(nome)) {
        return 3;
    }
};

/**
 * @brief Cadastra o Nome da lista nos arquivos do sistema
 *
 * @param char_const* nome do usuário
 * 
 *
 * @return void
 */
void cadastrar_nome_lista(char const *nome) {
    char nome_da_questao[tamanho_dos_caminhos] = "";
    char aux[tamanho_dos_caminhos]= "";
    //construindo o caminho para abrir o arquivo
    char caminho[tamanho_dos_caminhos];
    strcat(aux, PATH_BANCO_LISTAS);
    strcat(aux, "/");
    strcpy(caminho, aux);
    char pasta[tamanho_dos_caminhos] = "lista";
    char nome_arq[tamanho_dos_caminhos] =  "/nome_lista";
    //abrindo o arquivo que guarda a quantidade de listas no sistema
    FILE *file = fopen(PATH_QTD_TXT, "r");  
    char numero[tamanho_dos_caminhos] = "";
    //lendo a quantidade de listas no sistema
    fscanf(file, "%[^\n]", numero);
    strcat(pasta, numero);
    strcat(caminho, pasta);
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
    char caminho[tamanho_dos_caminhos];
    g_snprintf(caminho, tamanho_dos_caminhos, "mkdir %s/lista", PATH_BANCO_LISTAS);

    //criando o arquivo de ranking
    FILE *file = fopen(PATH_QTD_TXT, "r");  
    char numero[tamanho_dos_caminhos] = "";  
    fscanf(file, "%[^\n]", numero);

    strcat(caminho, numero);
    system(caminho);

    fclose(file);

    //criando pasta e arquivo de envios
    inicializar_pasta_envios(get_qtd_listas());

    //criando o arquivo de rank
    char rank_path[tamanho_dos_caminhos];
    FILE *rank;
    int n_lista = atoi(numero);
    
    sprintf(rank_path, "%s/lista%d/rank.txt", PATH_BANCO_LISTAS, n_lista);
    rank = fopen(rank_path, "w");
    fclose(rank);
    
    //criando o arquivo de registro de questoes que cada usuario fez
    //strcpy(rank_path, "");
    sprintf(rank_path, "%s/lista%d/registro.txt", PATH_BANCO_LISTAS, n_lista);
    rank = fopen(rank_path, "w");
    fprintf(rank, "0");
    fclose(rank);
}

void cria_past_qtd_entrada_saida(const char* qtd_entrada_saida, const char* qtd_questoes) {
    char comando[tamanho_dos_caminhos] = "";
    sprintf(comando, "mkdir dados/banco_listas/lista%d/qtd_entrada_saida", qtd_lista);
    system(comando);
    strcpy(comando, "");
    sprintf(comando, "dados/banco_listas/lista%d/qtd_entrada_saida/quantidade.txt", qtd_lista);
    FILE *file = fopen(comando, "w");
    fprintf(file, "%s\n", qtd_entrada_saida);
    fclose(file);

    //criando o caminho para criar o txt
    strcpy(comando, "");
    sprintf(comando, "dados/banco_listas/lista%d/qtd_entrada_saida/quantidade_questoes.txt", qtd_lista);
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
    char quantidade[tamanho_dos_caminhos] = "";
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

