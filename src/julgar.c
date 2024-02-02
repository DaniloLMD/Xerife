#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../include/julgar.h"
#include "../include/includes.h"

#define normal printf("\e[0m");
#define azul printf("\e[1;34m");
#define vermelho printf("\e[1;31m");
#define verde printf("\e[1;32m");
#define amarelo printf("\e[1;33m");

//typedef char bool;
#define true 1
#define false 0

//extensao do arquivo (.c , .cpp, .py)
char file_extension[20];

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

/**
 * @brief funcao que executa o codigo do usuario e verifica se ocorreram Runtime Error ou Time Limit Exceeded
 * @param tle_check referencia para uma variavel que guarda a ocorrencia de Time Limit Exceeded
 * @param runtime_check referencia para uma variavel que guarda a ocorrencia de Runtime Error
 * @param comando_executar_execucao string que contem o comando para executar o codigo
 * @return 
 */
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

/**
 * @brief compara a saida gerada pelo codigo do usuario com a saida do sistema e retorna se sao iguais
 * @param n_lista numero da lista
 * @param n_questao numero da questao
 * @param n_caso_de_teste numero do caso de teste a ser ulgado
 * @return ACCEPTED se forem iguais ou WRONG ANSWER caso contrario
 */
int checa_resposta(int n_lista, int n_questao, int n_caso_de_teste){

    char path_saida[300];       // = "arquivos/saidas/";
    snprintf(path_saida, 300, "%s/lista%d/questao%d/saida/saida%d.txt",
        PATH_BANCO_LISTAS, n_lista, n_questao,  n_caso_de_teste
    );

    FILE* resposta = fopen(path_saida, "r");
    FILE* resposta_usuario = fopen(PATH_SAIDA_USUARIO, "r");
    
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

    fclose(resposta);
    fclose(resposta_usuario);

    if(wrong_answer == true){
        return WRONG_ANSWER;
    }//resposta errada
    else{
        return ACCEPTED;
    }//resposta certa

}

/**
 * @brief julga um codigo escrito em c
 * @param n_lista numero da lista
 * @param n_questao numero da questao
 * @param n_caso_de_teste numero do caso de teste a ser julgado
 * @return resultado do julgamento, ACCEPTED, COMPILATION ERROR, etc
 */
int judge_c_file(int n_lista, int n_questao, int n_caso_de_teste){
    //montando o comando para compilar o arquivo
    char comando_compilar[300];
    snprintf(comando_compilar, 300, "gcc %s%s -o %s", PATH_CODIGO_USUARIO, file_extension, PATH_COMPILADO_USUARIO);
    
    //montando o comando para executar o arquivo
    char comando_executar[300];
    snprintf(comando_executar, 300, "%s > %s < %s/lista%d/questao%d/entrada/entrada%d.txt",
        PATH_COMPILADO_USUARIO, PATH_SAIDA_USUARIO,
        PATH_BANCO_LISTAS, n_lista, n_questao, n_caso_de_teste
    );

    int compilacao = system(comando_compilar);

    if(compilacao != 0){
        return COMPILATION_ERROR;
    }//compilacao mal sucedida

    bool tle;
    int execucao;
    checa_tle(&tle, &execucao, comando_executar);
if(tle){
        return TIME_LIMIT_EXCEEDED;
    }

    if(execucao != 0){
        return RUNTIME_ERROR;
    }//execucao mal sucedida
    
    return checa_resposta(n_lista, n_questao, n_caso_de_teste);
}

/**
 * @brief julga um codigo escrito em c++
 * @param n_lista numero da lista
 * @param n_questao numero da questao
 * @param n_caso_de_teste numero do caso de teste a ser julgado
 * @return resultado do julgamento, ACCEPTED, COMPILATION ERROR, etc
 */
int judge_cpp_file(int n_lista, int n_questao, int n_caso_de_teste){

    //montando o comando para executar o arquivo
    char comando_executar[300];
    snprintf(comando_executar, 300, "%s > %s < %s/lista%d/questao%d/entrada/entrada%d.txt",
        PATH_COMPILADO_USUARIO, PATH_SAIDA_USUARIO,
        PATH_BANCO_LISTAS, n_lista, n_questao, n_caso_de_teste
    );

    //montando o comando para compilar o arquivo
    char comando_compilar[300];
    snprintf(comando_compilar, 300, "g++ %s%s -o %s", PATH_CODIGO_USUARIO, file_extension, PATH_COMPILADO_USUARIO);
    

    int compilacao = system(comando_compilar);

    if(compilacao != 0){
        return COMPILATION_ERROR;
    }//compilacao mal sucedida

    bool tle;
    int execucao;
    checa_tle(&tle, &execucao, comando_executar);
if(tle){
        return TIME_LIMIT_EXCEEDED;
    }

    if(execucao != 0){
        return RUNTIME_ERROR;
    }//execucao mal sucedida
    
    return checa_resposta(n_lista, n_questao, n_caso_de_teste);
}

int judge_py_file(int n_lista, int n_questao, int n_caso_de_teste){

    //montando o comando para executar o arquivo
    char comando_executar[300];
    snprintf(comando_executar, 300, "python3 %spy > %s < %s/lista%d/questao%d/entrada/entrada%d.txt",
        PATH_CODIGO_USUARIO, PATH_SAIDA_USUARIO,
        PATH_BANCO_LISTAS, n_lista, n_questao, n_caso_de_teste
    );

    /*//montando o comando para compilar o arquivo
    char comando_compilar[300];
    snprintf(comando_compilar, 300, "g++ %s%s -o %s", PATH_CODIGO_USUARIO, file_extension, PATH_COMPILADO_USUARIO);
   */ 

    //int compilacao = system(comando_compilar);

    /*if(compilacao != 0){
        return COMPILATION_ERROR;
    }//compilacao mal sucedida*/

    bool tle;
    int execucao;
    checa_tle(&tle, &execucao, comando_executar);
    if(tle){
        return TIME_LIMIT_EXCEEDED;
    }

    if(execucao != 0){
        return RUNTIME_ERROR;
    }//execucao mal sucedida
    
    return checa_resposta(n_lista, n_questao, n_caso_de_teste);
    
}

/**
 * @brief recebe o caminho de um arquivo e retorna o nome dele. Ex : Desktop/pasta/arq.txt , retorna arq.txt
 * @param path string com o path ate o arquivo desejado
 * @return nome do arquivo junto de sua extensao
 */
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

/**
 * @brief recebe o nome de um arquivo e grava sua extensao em uma string. Ex: arq.txt , grava txt
 * @param file_name nome do arquivo
 * @param extension_ref referencia para a string que guardara a extensao
 * @return void
 */
void get_file_extension(const char* file_name, char* extension_ref){
    int index_ponto = -1;
    int size = 0;

    for(int i = 0; i < strlen(file_name); i++){
        if(file_name[i] == '.'){
            index_ponto = i;
        }
    }

    if(index_ponto == -1){
        extension_ref[0] = '\0';
        return;
    } 

    for(int i = index_ponto+1; i < strlen(file_name); i++){
        extension_ref[size++] = file_name[i];
    }
    extension_ref[size] = '\0';
    
}


/**
 * @brief recebe uma extensao e retorna se o arquivo possui extensao igual
 * @param extension_test extensao a ser comparada, "txt", "c", "cpp", "py"
 * @return true, se a extensao for igual, false caso contrario
 */
bool extension_compare(const char* extension_test){
    return !(strcmp(file_extension, extension_test));
}

/**
 * @brief 
 * @param file_path caminho ate o arquivo
 * @param n_lista numero da lista 
 * @param n_questao numero da questao
 * @param n_caso_de_teste numero do caso de teste a ser julgado
 * @return resultado do julgamento, ACCEPTED, WRONG ANSWER, COMPILATION ERROR, etc
 */
int julgar_arquivo(const char* file_path, int n_lista, int n_questao, int n_caso_de_teste){

    //pegando o nome do arquivo
    char* file_name = get_file_name_from_path(file_path);
    //pegando a extensao do arquivo
    get_file_extension(file_name, file_extension);

    //copiando o arquivo informado ate a pasta onde ele sera julgado
    char comando_executar_copy[300];
    snprintf(comando_executar_copy, 300, "cp %s %s%s", file_path, PATH_CODIGO_USUARIO, file_extension);
    system(comando_executar_copy);
    
    free(file_name);

    //verificando as extensoes possiveis
    if(extension_compare("c")){
        return judge_c_file(n_lista, n_questao, n_caso_de_teste);
    }
    else if(extension_compare("cpp")){
        return judge_cpp_file(n_lista, n_questao, n_caso_de_teste);
    }
    else if(extension_compare("py")){
        return judge_py_file(n_lista, n_questao, n_caso_de_teste);
    }
    else {
        return INVALID_EXTENSION;
    }

}

/**
 * @brief recebe o caminho de um arquivo e retorna se a extensao dele e valida
 * @param arquivo_path caminho ate o arquivo
 * @return true, se a extensao estiver dentre as validas, false caso contrario
 */
int extension_is_valid(const char* arquivo_path){
    //pegando o nome do arquivo
    char* file_name = get_file_name_from_path(arquivo_path);
    //pegando a extensao do arquivo
    get_file_extension(file_name, file_extension);
    free(file_name);
    if(extension_compare("c")){
        return true;
    }
    else if(extension_compare("cpp")){
        return true;
    }
    else if(extension_compare("py")){
        return true;
    }

    return false;
}

/*  
    funcoes de thread

    pthread_t thread1;
    pthread_create(&thread1, NULL, computation, (void*) &value1);       //cria uma thread, a funcao e o parametro dela tem que ser do tipo void*
    pthread_join(thread1, NULL);                                        //junta as threads na aplicacao normal novamente
    pthread_cancel(thread1);                                            //fecha forcadamente uma thread ativa    
    pthread_exit(NULL);                                                 //fecha a thread explicitamente(nao termina ainda, tem que usar o join), indica que ela nao tem mais nada pra fazer
*/