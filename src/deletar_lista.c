#include "../include/includes.h"

/**
 * @brief 
 * @param 
 * @return 
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
 * @brief 
 * @param 
 * @return 
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
 * @brief 
 * @param 
 * @return 
 */
bool deletar_lista(int n_lista){
    char comando[100];
    FILE* ptr;
    int qtd_listas = get_qtd_listas();

    if(qtd_listas < n_lista){     
        return false;
    }

    //apagando a lista desejada
    sprintf(comando, "rm -rf %s/lista%d", PATH_BANCO_LISTAS, n_lista);
    system(comando);

    //renomeando as listas posteriores
    for(int i = n_lista+1; i <= qtd_listas; i++){
        sprintf(comando, "mv %s/lista%d %s/lista%d", PATH_BANCO_LISTAS, i, PATH_BANCO_LISTAS, i-1);
        system(comando);
    }

    //alterando a quantidade total de listas
    qtd_listas--;
    ptr = fopen(PATH_QTD_TXT, "w");
    fprintf(ptr, "%d", qtd_listas);
    fclose(ptr);
    return true;
}