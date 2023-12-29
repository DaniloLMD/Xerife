#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "julgar.h"
#include <unistd.h>
#include <pthread.h>

#define normal printf("\e[0m");
#define azul printf("\e[1;34m");
#define vermelho printf("\e[1;31m");
#define verde printf("\e[1;32m");
#define amarelo printf("\e[1;33m");

typedef char bool;
#define true 1
#define false 0

int time_limit = 1;

struct ThreadParametros{
    pthread_t thread_monitorada;
    bool ativa;
    int execucao_status;
    char* comando_execucao;
    bool time_limit_exceeded;
};

//funcao que monitora se a thread da execucao ainda esta rodando
void* thread_funcao_cronometro(void* param_ref){

    struct ThreadParametros* param = (struct ThreadParametros*) param_ref;

    sleep(time_limit);

    if(param->ativa == true){
        param->ativa = false;
        pthread_cancel(param->thread_monitorada);
        param->time_limit_exceeded = true;
    }

    pthread_exit(NULL);
}

//funcao que executa o programa enquanto e monitorada pelo cronometro
void* thread_funcao_executa(void* param_ref){
    struct ThreadParametros* param = (struct ThreadParametros*) param_ref;

    param->execucao_status = system(param->comando_execucao);

    param->ativa = false;
    pthread_exit(NULL);
}

int checa_resposta(const char* nome_arquivo_saida){

    char path_saida[50] = "arquivos/saidas/";
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

    if(compilacao != 0){
        vermelho
        printf("COMPILATION ERROR\n");
        normal
        return COMPILATION_ERROR;
    }//compilacao mal sucedida



    //int execucao = system(comando);
    //fazendo as threads para pegar TLE
    pthread_t thread_cronometro;
    pthread_t thread_executadora;
    struct ThreadParametros param;

    param.ativa = true;
    param.time_limit_exceeded = false;
    param.thread_monitorada = thread_executadora;
    param.execucao_status = 0;
    param.comando_execucao = comando;

    pthread_create(&thread_cronometro, NULL, thread_funcao_cronometro, (void*) &param);
    pthread_create(&param.thread_monitorada, NULL, thread_funcao_executa, (void*) &param);
    pthread_join(thread_cronometro, NULL);
    pthread_join(param.thread_monitorada, NULL);


    if(param.time_limit_exceeded == true){
        amarelo
        printf("TIME LIMIT EXCEEDED\n");
        normal
        return TIME_LIMIT_EXCEEDED;
    }

    int execucao = param.execucao_status;
    if(execucao != 0){
        amarelo
        printf("RUNTIME ERROR\n");
        normal
        return RUNTIME_ERROR;
    }//execucao mal sucedida

    char nome_saida[3] = "s";
    nome_saida[1] = num_teste + '0';
    return checa_resposta(nome_saida);
}

int julgar(const char* texto){

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


/*  
    funcoes de thread

    pthread_t thread1;
    pthread_create(&thread1, NULL, computation, (void*) &value1);       //cria uma thread, a funcao e o parametro dela tem que ser do tipo void*
    pthread_join(thread1, NULL);                                        //junta as threads na aplicacao normal novamente
    pthread_cancel(thread1);                                            //fecha forcadamente uma thread ativa    
    pthread_exit(NULL);                                                 //fecha a thread explicitamente(nao termina ainda, tem que usar o join), indica que ela nao tem mais nada pra fazer
*/
