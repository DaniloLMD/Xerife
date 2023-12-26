#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "julgar.h"

#define normal printf("\e[0m");
#define azul printf("\e[1;34m");
#define vermelho printf("\e[1;31m");
#define verde printf("\e[1;32m");
#define amarelo printf("\e[1;33m");

typedef char bool;
#define true 1
#define false 0

int checa_resposta(const char* nome_arquivo_saida){

    char path_saida[50] = "./arquivos/saidas/";
    strcat(path_saida, nome_arquivo_saida);

    FILE* resposta = fopen(path_saida, "r");
    FILE* resposta_usuario = fopen("arquivos/usuario_saidas/saida", "r");
    
    char c = 0, c2 = 0;
    bool wrong_answer = false;

    while(fscanf(resposta, "%c", &c) != EOF){
        fscanf(resposta_usuario, "%c", &c2);
        if(c != c2 && c2 != EOF){
            wrong_answer = true;
            break;
        }
    }

    if(wrong_answer == true){
        vermelho
        printf("WRONG ANSWER\n");
        normal
        return WRONG_ANSWER;
    }//resposta errada
    else{
        verde
        printf("ACCEPTED!\n");
        normal
        return ACCEPTED;
    }//resposta certa

}

int testa(int num_teste){

    char nome_entrada[3] = "e";
    nome_entrada[1] = num_teste+'0';

    char comando[100] = "./arquivos/compilados/usuario_compilado < arquivos/entradas/";
    strcat(comando, nome_entrada);
    strcat(comando, " > arquivos/usuario_saidas/saida");
    
    int compilacao = system("gcc arquivos/usuario_codigos/usuario.c -o arquivos/compilados/usuario_compilado");
    printf("compilacao = %d\n", compilacao);    
    if(compilacao == 0){
        int execucao = system(comando);
        printf("execucao = %d\n", execucao);

        if(execucao != 0){
            amarelo
            printf("RUNTIME ERROR\n");
            normal
            return RUNTIME_ERROR;
        }//execucao mal sucedida
    }//compilacao bem sucedida
    else{
        vermelho
        printf("COMPILATION ERROR\n");
        normal
        return COMPILATION_ERROR;
    }//compilacao mal sucedida

    char nome_saida[3] = "s";
    nome_saida[1] = num_teste + '0';
    return checa_resposta(nome_saida);
}

int escrever(const char* texto){

    FILE* resposta = NULL;
    //FILE* resposta_usuario = NULL;
    //FILE* usuario_cod = NULL;

    resposta = fopen("arquivos/usuario_codigos/usuario.c", "w");
    fprintf(resposta, "%s", texto);
    fclose(resposta);
    

    return testa(1);
    /*printf("TESTE 2: "); testa(2);
    printf("TESTE 3: "); testa(3);*/
}
