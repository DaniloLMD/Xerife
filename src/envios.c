#include <stdlib.h>
#include "../include/includes.h"
#include <gtk/gtk.h>

GtkBuilder *builder = NULL;

/**
 * @brief recebe o numero de uma lista e cria a pasta de envios nela
 * @param n_lista numero da lista
 * @return void
*/
void inicializar_pasta_envios(int n_lista){
    char path[100];
    char cmd_mkdir[150];

    sprintf(path, "%s/lista%d", PATH_BANCO_LISTAS, n_lista);
    sprintf(cmd_mkdir, "mkdir %s/envios", path);
    system(cmd_mkdir);
    
    sprintf(path, "%s/lista%d/envios/qtd_envios.txt", PATH_BANCO_LISTAS, n_lista);
    FILE *envios = fopen(path, "w");
    fprintf(envios, "0");
    fclose(envios);

}

/**
 * @brief recebe o numero da lista e retorna a quantidade de codigos enviados nela
 * @param n_lista numero da lista
 * @return quantidade de codigos enviados
*/
int get_qtd_envios(int n_lista){
    char path[100];
    int qtd_envios;
    
    sprintf(path, "%s/lista%d/envios/qtd_envios.txt", PATH_BANCO_LISTAS, n_lista);
    FILE *envios = fopen(path, "r");
    fscanf(envios, "%d", &qtd_envios);
    fclose(envios);

    return qtd_envios;

}

/**
 * @brief recebe o numero da lista e incrementa a quantidade de envios nela em 1
 * @param n_lista numero da lista
 * @return void
*/
void incrementa_qtd_envios(int n_lista){
    char path[100];
    int qtd_envios = get_qtd_envios(n_lista);

    sprintf(path, "%s/lista%d/envios/qtd_envios.txt", PATH_BANCO_LISTAS, n_lista);
    FILE *envios = fopen(path, "w");
    fprintf(envios, "%d", qtd_envios+1);
    fclose(envios);
}

/**
 * @brief salva o codigo enviado no sistema
 * @param n_lista numero da lista
 * @param n_questao numero da questao
 * @param user_name nome do usuario
 * @param resultado resultado do codigo, "ACCEPTED", "WRONG", etc
 * @param linguagem linguagem do codigo, C, CPP, etc
 * @return void
*/
void set_novo_envio(int n_lista, int n_questao, char* user_name, char* resultado, char* linguagem, const char *code_path){
    char path[100];
    char code[5000];
    char str[2];
    str[1] = '\0';

    incrementa_qtd_envios(n_lista);
    sprintf(path, "%s/lista%d/envios/envio%d.txt", PATH_BANCO_LISTAS, n_lista, get_qtd_envios(n_lista));

    //lendo e copiando o codigo
    FILE *code_file = fopen(code_path, "r");

    strcpy(code, "");
    while(fscanf(code_file, "%c", &str[0]) != EOF){
        strcat(code, str);
    }
    fclose(code_file);
    
    //criando e registrando o arquivo de envio
    FILE *envio = fopen(path, "w");
    fprintf(envio, "%d,%s,%s,%s\n", n_questao, user_name, resultado, linguagem);
    fprintf(envio, "%s", code);
    fclose(envio);
}

/**
 * @brief recebe um builder e o numero da lista, carrega e atualiza a list store com os envios
 * @param builder builder do gtk para carregar a list store
 * @param n_lista numero da lista
 * @return void
*/
void atualiza_list_store_envios(GtkBuilder *builder, int n_lista){

    GtkListStore* list_store_envios;
    list_store_envios =  GTK_LIST_STORE(gtk_builder_get_object(builder, "list_store_envios"));
    GtkTreeIter iter;

    gtk_list_store_clear(list_store_envios);
    
    int qtd_envios = get_qtd_envios(n_lista);

    char path[100];
    FILE *envio = NULL;

    int n_questao;
    char usuario[50];
    char resultado[50];
    char linguagem[15];

    for(int i = qtd_envios; i >= 1; i--){
        sprintf(path, "%s/lista%d/envios/envio%d.txt", PATH_BANCO_LISTAS, n_lista, i);
        envio = fopen(path, "r");
        fscanf(envio, "%d,%[^,],%[^,],%[^\n]%*c", &n_questao, usuario, resultado, linguagem);
    
        gtk_list_store_append(list_store_envios, &iter);
        gtk_list_store_set(
            list_store_envios, &iter,
            0, i,
            1, n_questao,
            2, usuario,
            3, resultado,
            4, linguagem,
            -1
        );  

        fclose(envio);
    }
    //1,clear,WRONG ANSWER,c
}   

/**
 * @brief exibe um prompt com o codigo na tela
 * @param n_envio numero do envio do codigo 
 * @param codigo string com o codigo
 * @param builder builder para carregar o prompt
 * @return void
 */
void codigo_prompt (int n_envio, char *codigo, GtkBuilder* builder) {
    
    char texto[20];
    sprintf(texto, "Envio %d", n_envio);

    GtkMessageDialog *prompt = GTK_MESSAGE_DIALOG(gtk_builder_get_object(builder, "codigo_prompt"));
    GtkLabel *label = GTK_LABEL(gtk_builder_get_object(builder, "codigo_prompt_label"));

    g_object_set(prompt, "text", texto, NULL);
    g_object_set(prompt, "secondary_text", "AAAA", NULL);
    gtk_label_set_text(label, codigo);
    
    gtk_widget_show_all(GTK_WIDGET(prompt));
    gtk_dialog_run(GTK_DIALOG(prompt));
}

/**
 * @brief recebe numero da lista e do envio e grava o codigo em uma string
 * @param n_lista numero da lista
 * @param n_envio numero do envio
 * @param str string em que o codigo sera salvo
 * @return void
*/
void get_code_from_envio(int n_lista, int n_envio, char* str){
    char path[100];
    char c[2];
    char lixo[100];
    c[1] = '\0';
    
    sprintf(path, "%s/lista%d/envios/envio%d.txt", PATH_BANCO_LISTAS, n_lista, n_envio);
    FILE* envio = fopen(path, "r");
    
    strcpy(str, "");


    fscanf(envio, "%[^\n]%*c", lixo);
    while(fscanf(envio, "%c", &c[0]) != EOF){
        strcat(str, c);
    }

    fclose(envio);
}