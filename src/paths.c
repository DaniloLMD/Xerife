#include "../include/includes.h"

/**
 * @brief recebe o número da lista e uma string, e grava na string o nome referente a lista
 * @param n_listas numero da lista
 * @param list_name string em que o nome da lista será gravado
 * @return void
 */
void set_nome_lista(int n_lista, char* list_name){
    char path[100];
    char name[100];
    FILE* f = NULL;

    sprintf(path, "%s/lista%d/nome_lista.txt", PATH_BANCO_LISTAS, n_lista);
    f = fopen(path, "r");
    
    fscanf(f, "%[^\n]", name);
    fclose(f);
    strcpy(list_name, name);
}

/**
 * @brief retorna a quantidade de listas existentes
 * @param 
 * @return int - quantidade de listas existentes 
 */
int get_qtd_listas(){

    //lendo a quantidade total de listas
    int qtd_listas;
    FILE* ptr = fopen(PATH_QTD_TXT, "r");
    fscanf(ptr, "%d", &qtd_listas);
    fclose(ptr);
    
    return qtd_listas;
}

/**
 * @brief retorna a quantidade de questoes da lista n_lista
 * @param n_lista numero da lista
 * @return int - quantidade de questoes da lista n_lista 
 */
int get_qtd_questoes(int n_lista){

    int qtd_questoes;
    char path_quantidade_txt[150];

    sprintf(path_quantidade_txt, "%s/lista%d/qtd_entrada_saida/quantidade_questoes.txt", PATH_BANCO_LISTAS, n_lista);

    FILE* ptr = fopen(path_quantidade_txt, "r");
    fscanf(ptr, "%d", &qtd_questoes);
    fclose(ptr);
    
    return qtd_questoes;
}

/**
 * @brief retorna a quantidade de entradas e saidas da lista n_lista
 * @param n_lista numero da lista
 * @return int - quantidade de entradas e saidas da lista n_lista 
 */
int get_qtd_entrada_saida(int n_lista){
    int qtd_entradas;
    char path_quantidade_txt[150];

    sprintf(path_quantidade_txt, "%s/lista%d/qtd_entrada_saida/quantidade.txt", PATH_BANCO_LISTAS, n_lista);

    FILE* ptr = fopen(path_quantidade_txt, "r");
    fscanf(ptr, "%d", &qtd_entradas);
    fclose(ptr);
    
    return qtd_entradas;
}