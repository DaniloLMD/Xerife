#include "cadastro.h"


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

int cadastro(const char *usuario, const char *senha) {
    if (usuario_existente(usuario)) return 2;
    FILE *arquivo = NULL;
    arquivo = fopen("../usuarios_cadastrados.csv", "a");
    char nome[202];
    char sen[202];
    
    strcpy(nome, usuario);
    strcpy(sen, senha);
    fputs(nome, arquivo);
    fputc(',', arquivo);
    fputs(sen, arquivo);
    fputc('\n', arquivo);

    fclose(arquivo);

    return 1;
}
