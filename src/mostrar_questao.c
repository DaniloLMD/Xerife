#include "mostrar_questao.h"
#include "paths.h"
#include "includes.h"
#include "../include/deletar_lista.h"

/**
 * @brief 
 * @param 
 * @return 
 */
void mostrar_enunciado(GtkLabel* label, int n_lista, int n_questao){
    FILE* file;
    char path[500];

    g_snprintf(path, 500, "%s/lista%d/questao%d/desq.txt", PATH_BANCO_LISTAS, n_lista, n_questao);

    file = fopen(path, "r");

    char enunciado[10000] = ""; 
    char str[2];
    int limite_de_caracteres_por_linha = 100;
    str[1] = '\0';

    int caracteres_lidos = 0;
    bool quebrar_linha = false;

    while( fscanf(file, "%c", &str[0]) != EOF){
        strcat(enunciado, str);

        caracteres_lidos++;
        if(str[0] == '\n') caracteres_lidos = 0;
        else if(caracteres_lidos == limite_de_caracteres_por_linha){
            quebrar_linha = true;
        }

        if(quebrar_linha == true && str[0] == ' '){
            caracteres_lidos = 0;
            str[0] = '\n';
            strcat(enunciado, str);
            quebrar_linha = false;
        }
    }
    
    gtk_label_set_text(label, enunciado);
}

/**
 * @brief 
 * @param  
 * @param
 * @return 
 */
void mostrar_n_questao(GtkLabel* label, int n_questao){
    char numero_questao[50];
    g_snprintf(numero_questao, 50, "Questão %d", n_questao);
    gtk_label_set_text(label, numero_questao);
}

void mostrar_n_lista(GtkLabel *label, int n_lista){
    char numero_lista[150];

    g_snprintf(numero_lista, 50, "Lista %d", n_lista);
    gtk_label_set_text(label, numero_lista);
}

void mostrar_nome_lista(GtkLabel *label, int n_lista){
    char nome_lista[100];

    set_nome_lista(n_lista, nome_lista);
    gtk_label_set_text(label, nome_lista);
}