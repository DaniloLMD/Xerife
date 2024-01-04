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

//extensao do arquivo (.c , .cpp, .py)
char file_extension[20];


//nome da entrada e da saida do caso de teste atual
char nome_entrada[5];
char nome_saida[5];
    
//time limit da questao
int time_limit = 1;

//struct pra guardar as threads pra buscar tle
struct ThreadParametros{
    pthread_t thread_monitorada;
    pthread_t thread_monitora;
    bool ativa;
    int execucao_status;
    char* comando_executar_execucao;
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

    param->execucao_status = system(param->comando_executar_execucao);

    param->ativa = false;
    pthread_cancel(param->thread_monitora);
    pthread_exit(NULL);
}


void checa_tle(bool* tle_check, int* runtime_check, char* comando_executar_execucao){
    pthread_t thread_cronometro;
    pthread_t thread_executadora;
    struct ThreadParametros param;

    param.ativa = true;
    param.time_limit_exceeded = false;
    param.thread_monitorada = thread_executadora;
    param.thread_monitora = thread_cronometro;
    param.execucao_status = 0;
    param.comando_executar_execucao = comando_executar_execucao;

    pthread_create(&param.thread_monitora, NULL, thread_funcao_cronometro, (void*) &param);
    pthread_create(&param.thread_monitorada, NULL, thread_funcao_executa, (void*) &param);
    pthread_join(param.thread_monitora, NULL);
    pthread_join(param.thread_monitorada, NULL);

   *tle_check = param.time_limit_exceeded;
   *runtime_check = param.execucao_status;
}

int checa_resposta(const char* nome_arquivo_saida){

    char path_saida[50] = "arquivos/saidas/";
    strcat(path_saida, nome_arquivo_saida);

    FILE* resposta = fopen(path_saida, "r");
    FILE* resposta_usuario = fopen("arquivos/usuario_saidas/saida", "r");
    
    bool wrong_answer = false;

    int eof1, eof2;
    char s1[500], s2[500];
    while(1){

        eof1 = fscanf(resposta, "%[^\n]%*c", s1);
        eof2 = fscanf(resposta_usuario, "%[^\n]%*c", s2);

        if(eof1 == EOF && eof2 == EOF){
            break;
        }

        if(eof1 == EOF){
            if(strcmp(s2, "\n") != 0){
                wrong_answer = true;
                break;
            }
            continue;
        }
        if(eof2 == EOF){
            if(strcmp(s1, "\n") != 0){
                wrong_answer = true;
                break;
            }
            continue;
        }

        if(strcmp(s1, s2) != 0){
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

int judge_c_file(int caso_de_teste){

    char comando_executar[100] = "./arquivos/compilados/usuario_compilado < arquivos/entradas/";
    strcat(comando_executar, nome_entrada);
    strcat(comando_executar, " > arquivos/usuario_saidas/saida");
    
    int compilacao = system("gcc arquivos/usuario_codigos/usuario.c -o arquivos/compilados/usuario_compilado");

    if(compilacao != 0){
        vermelho
        printf("COMPILATION ERROR\n");
        normal
        return COMPILATION_ERROR;
    }//compilacao mal sucedida

    bool tle;
    int execucao;
    checa_tle(&tle, &execucao, comando_executar);
    if(tle){
        amarelo
        printf("TIME LIMIT EXCEEDED\n");
        normal
        return TIME_LIMIT_EXCEEDED;
    }

    if(execucao != 0){
        amarelo
        printf("RUNTIME ERROR\n");
        normal
        return RUNTIME_ERROR;
    }//execucao mal sucedida
    
    return checa_resposta(nome_saida);
}

int judge_cpp_file(int caso_de_teste){

    char comando_executar[100] = "./arquivos/compilados/usuario_compilado < arquivos/entradas/";
    strcat(comando_executar, nome_entrada);
    strcat(comando_executar, " > arquivos/usuario_saidas/saida");
    
    int compilacao = system("g++ arquivos/usuario_codigos/usuario.cpp -o arquivos/compilados/usuario_compilado");

    if(compilacao != 0){
        vermelho
        printf("COMPILATION ERROR\n");
        normal
        return COMPILATION_ERROR;
    }//compilacao mal sucedida

    bool tle;
    int execucao;
    checa_tle(&tle, &execucao, comando_executar);
    if(tle){
        amarelo
        printf("TIME LIMIT EXCEEDED\n");
        normal
        return TIME_LIMIT_EXCEEDED;
    }

    if(execucao != 0){
        amarelo
        printf("RUNTIME ERROR\n");
        normal
        return RUNTIME_ERROR;
    }//execucao mal sucedida
    
    return checa_resposta(nome_saida);
}


char* get_file_name_from_path(const char* path){
    char *file_name;
    int index_barra = -1;
    int size = 0;

    for(int i = 0; i < strlen(path); i++){
        if(path[i] == '/'){
            index_barra = i;
        }
    }
    
    file_name = (char*) malloc((strlen(path) - index_barra) * sizeof(char));
    for(int i = index_barra+1; i < strlen(path); i++){
        file_name[size++] = path[i];
    }
    file_name[size] = '\0';

    return file_name;

}

void get_file_extension(const char* file_name){
    int index_ponto = -1;
    int size = 0;

    for(int i = 0; i < strlen(file_name); i++){
        if(file_name[i] == '.'){
            index_ponto = i;
        }
    }

    if(index_ponto == -1){
        file_extension[0] = '\0';
        return;
    } 

    for(int i = index_ponto+1; i < strlen(file_name); i++){
        file_extension[size++] = file_name[i];
    }
    file_extension[size] = '\0';
    
}

bool extension_compare(const char* extension_test){
    return !(strcmp(file_extension, extension_test));
}

int julgar_arquivo(const char* file_path, int caso_de_teste){


    g_snprintf(nome_entrada, 5, "e%d", caso_de_teste);
    g_snprintf(nome_saida, 5, "s%d", caso_de_teste);

    char* file_name = get_file_name_from_path(file_path);
    get_file_extension(file_name);

    //copiando o arquivo informado ate a pasta onde ele sera julgado
    char comando_executar_copy[1000] = "cp ";
    strcat(comando_executar_copy, file_path);
    strcat(comando_executar_copy, " arquivos/usuario_codigos/usuario.");
    strcat(comando_executar_copy, file_extension);
    system(comando_executar_copy);

    free(file_name);
    //verificando as extensoes possiveis
    if(extension_compare("c")){
        return judge_c_file(caso_de_teste);
    }
    else if(extension_compare("cpp")){
        return judge_cpp_file(caso_de_teste);
    }
    else {
        return INVALID_EXTENSION;
    }

}





/*  
    funcoes de thread

    pthread_t thread1;
    pthread_create(&thread1, NULL, computation, (void*) &value1);       //cria uma thread, a funcao e o parametro dela tem que ser do tipo void*
    pthread_join(thread1, NULL);                                        //junta as threads na aplicacao normal novamente
    pthread_cancel(thread1);                                            //fecha forcadamente uma thread ativa    
    pthread_exit(NULL);                                                 //fecha a thread explicitamente(nao termina ainda, tem que usar o join), indica que ela nao tem mais nada pra fazer
*/
