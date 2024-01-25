#include "../include/cadastro.h"
#include "../include/includes.h"
#include "../include/login.h"
#define max_nome 35
#define comando 100

/**
 * @brief Verifica se o nome de usuário já existe no sistema
 *
 * @param char_const* nome do usuário
 * 
 * @return Verdadeiro caso a operação tenha sucesso | falso caso o usuário já esteja cadastrado
 * 
 */
bool usuario_existente(const char *usuario) {
    head *Lista_usuarios = NULL;
    Lista_usuarios = criar_lista();
    no *node = NULL;
    Lista_usuarios = ler_arquivo();
   
    node = Lista_usuarios -> begin;

    for (int i = 0; i < Lista_usuarios -> size; i++) {
        if (strcmp(usuario, node -> nome) == 0) {
            return true;
        }
        node = node -> next;
    }
    return false;
    destruir_lista(Lista_usuarios);
}

bool verificar_caracteres_proibidos(const char string[max_nome]) {
    for (int i = 0; i < strlen(string); i++) {
        if(string[i] == ',') {
            return true;
        }
    }
    return false;
}

/**
 * @brief Cadastra o usuário no sistema verificando se ele já está cadastrado
 *
 * @param char_const* nome do usuário
 * @param char_const* senha do usuário
 *
 * @return 1 caso a operação tenha sucesso | 2 caso o usuário já esteja cadastrado
 * 
 */
int cadastro(const char *usuario, const char *senha) {
    if (usuario_existente(usuario)) return 2;
    if (verificar_caracteres_proibidos(usuario) || verificar_caracteres_proibidos(senha)) return 3;
    FILE *arquivo = NULL;
    arquivo = fopen(PATH_USUARIOS_CADASTRADOS_CSV, "a");
    char nome[comando];
    char sen[comando];
    
    strcpy(nome, usuario);
    strcpy(sen, senha);
    printf("fui pra lower %s", nome);

    fputs(nome, arquivo);
    fputc(',', arquivo);
    fputs(sen, arquivo);
    fputc('\n', arquivo);

    fclose(arquivo);

    return 1;
}
