#include "mostrar_questao.h"
#include "paths.h"

void mostrar_enunciado(GtkLabel* label, int n_lista, int n_questao){
    FILE* file;
    char path[500];

    g_snprintf(path, 500, "%s/lista%d/questao%d/desq.txt", PATH_BANCO_LISTAS, n_lista, n_questao);

    file = fopen(path, "r");

    char enunciado[10000] = ""; 
    char str[2];
    str[1] = '\0';

    while( fscanf(file, "%c", &str[0]) != EOF){
        strcat(enunciado, str);
    }
    
    gtk_label_set_text(label, enunciado);
}

void mostrar_n_questao(GtkLabel* label, int n_questao){
    char numero_questao[50];
    g_snprintf(numero_questao, 50, "Questão %d", n_questao);
    gtk_label_set_text(label, numero_questao);
}