#include "../include/mostrar_lista.h"

lhead *lista_de_listas = NULL;
lnode *ponteiro_atual = NULL;

/**
 * @brief 
 * @param 
 * @return
 */
int pot (int x) {
    if (x == 0) return 1;
    else {
        return 10 * pot(x-1);
    }
}

/**
 * @brief 
 * @param 
 * @return
 */
int string_to_int(char string[]) {
    int i = 0;
    int num = 0;
    int max = strlen(string) - 1;
    for (int i = 0; i < strlen(string); i++) {
        num += (string[i] - '0') * pot(max) ;
        max--;
    }
    return num;
}

/**
 * @brief 
 * @param 
 * @return
 */
void carregar_listas_ativas() {
    char qtdlistas[200] = "";
    char texto[100] = "";
    lnode *aux = NULL;
    lista_de_listas = criar_l_lista();

    FILE *file = fopen(PATH_QTD_TXT, "r");
    fscanf(file, "%[^\n]", qtdlistas);
    char caminho[200];
    fclose(file);


    for (int i = 1; i <= string_to_int(qtdlistas); i++) {
        sprintf(caminho, "%s/lista%d/nome_lista%d.txt", PATH_BANCO_LISTAS,i , i);
        file = fopen(caminho, "r");
        fscanf(file, "%[^\n]", texto);
        adicionar_l_fim(lista_de_listas, texto);
        fclose(file);
    }
    aux = lista_de_listas -> begin;

    for (int i = 1; i <= lista_de_listas -> tamanho; i++) {
        aux -> id = i;
        aux = aux -> next;
    }

    
    ponteiro_atual = lista_de_listas -> begin;
};

/**
 * @brief 
 * @param 
 * @return
 */
int avancar_lista(GtkLabel *numero_questao, GtkLabel *titulo_quest) {
    char numero_lista[200] = "";
    if (lista_de_listas -> tamanho == 0) {
        gtk_label_set_text(numero_questao, "Nenhuma lista cadatrada");
        gtk_label_set_text(titulo_quest, "vazio");
        return 2;
    } else {
        sprintf(numero_lista, "Lista (%d)", ponteiro_atual -> id);
        if (ponteiro_atual != lista_de_listas -> end) {
            gtk_label_set_text(titulo_quest, ponteiro_atual -> titulo);
            gtk_label_set_text(numero_questao, numero_lista);
            ponteiro_atual = ponteiro_atual -> next; 

            return 0;
        } else {
            gtk_label_set_text(titulo_quest, "ultima lista");
            gtk_label_set_text(titulo_quest, lista_de_listas -> end -> titulo);
            gtk_label_set_text(numero_questao, numero_lista);
            return 1;

        }
    }
};

/**
 * @brief 
 * @param 
 * @return
 */
int voltar_lista(GtkLabel *numero_questao, GtkLabel *titulo_quest) {
    char numero_lista[200] = "";
    if (lista_de_listas -> tamanho == 0) {
        gtk_label_set_text(numero_questao, "Nenhuma lista cadatrada");
        gtk_label_set_text(titulo_quest, "vazio");
        return 2;
    } else {
        sprintf(numero_lista, "Lista (%d)", ponteiro_atual -> id);
        if(ponteiro_atual != lista_de_listas -> begin) {    
            gtk_label_set_text(titulo_quest, ponteiro_atual -> titulo);
            gtk_label_set_text(numero_questao, numero_lista);
            ponteiro_atual = ponteiro_atual -> prev;
            
            return 0;

        }else {
            gtk_label_set_text(titulo_quest, "Primeira lista");
            gtk_label_set_text(titulo_quest, lista_de_listas -> begin -> titulo);
            gtk_label_set_text(numero_questao, numero_lista);
            return 1;
        }
    }
};

/**
 * @brief 
 * @param 
 * @return
 */
int checar_lista_monitorada () {
    return ponteiro_atual -> id;
}