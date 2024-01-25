#include "../include/login.h"
#include "../include/lista_login.h"
#include "../include/includes.h"
#define max_nome 35
#define max_senha 35

void tolower_case (char *nome) {
    for (int i = 0; i < strlen(nome); i++) {
        if (nome[i] >= 'A' && nome[i] <= 'Z') {
            nome[i] +=  'a' - 'A';
        }
    } 
}

/**
 * @brief 
 * @param 
 * @return
 */
head *ler_arquivo() {
    head *Lista_usuarios = NULL;
    FILE *list_usu = fopen(PATH_USUARIOS_CADASTRADOS_CSV, "r");
    char enome[max_nome];
    char esenha[max_senha];
    char virgula;
    Lista_usuarios = criar_lista();
    
    no *node = NULL;

    while((fscanf(list_usu, "%[^,],%[^\n]%*c", enome, esenha) != EOF)) {
            inserir_no_fim(Lista_usuarios , enome, esenha);
    }

    fclose(list_usu);
    return Lista_usuarios;
};

/**
 * @brief 
 * @param 
 * @return
 */
int quantidade_diferentes (const char *s1, const char *s2) {
    int qtd = 0;
    if (strlen(s1) != strlen(s2)) return 0;
    for (int i = 0; i < strlen(s1); i++) {
        if (s1[i] != s2[i]) {
            qtd++;
        }
    }
    return qtd;
}

/**
 * @brief 
 * @param 
 * @return
 */
int login (const char nome[max_nome], const char senha[max_senha]) {
    head *Lista_usuarios = NULL;
    Lista_usuarios = ler_arquivo();
    no *node = NULL;
    char copia_nome[max_nome] = "";
    strcpy(copia_nome, nome);
    tolower_case(copia_nome);

    node = Lista_usuarios -> begin;
    

    for (int i = 0; i < Lista_usuarios -> size; i++) {
        if ((strcmp(node -> nome, copia_nome) == 0) && strcmp(node -> senha, senha) == 0) {
            return 1;
        } 
        else if ((strcmp(node -> nome, copia_nome) == 0) && strcmp(node -> senha, senha) != 0) {
            return 2;
        }
        node = node -> next;
    }
    destruir_lista(Lista_usuarios);
    return 3;
}