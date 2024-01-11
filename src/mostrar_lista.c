#include "../include/mostrar_lista.h"
#include "../include/includes.h"

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
        sprintf(caminho, "%s/lista%d/nome_lista.txt", PATH_BANCO_LISTAS,i);
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

void atualizar_label(GtkLabel *labelx, char *texto) {
    gtk_label_set_text(labelx, texto);
}

void iniciar_label(GtkLabel* numero_da_questao, GtkLabel* titulo_da_questao) {
    char texto[200];
    sprintf(texto, "lista %d", ponteiro_atual -> id);
    atualizar_label(numero_da_questao, texto);
    atualizar_label(titulo_da_questao, ponteiro_atual -> titulo);
};


/**
 * @brief 
 * @param 
 * @return
 */
int avancar_lista(GtkLabel *numero_questao, GtkLabel *titulo_quest) {
    char texto[200] = "";
    ponteiro_atual = ponteiro_atual -> next;
    sprintf(texto, "Lista (%d)", ponteiro_atual -> id);

    atualizar_label(titulo_quest, ponteiro_atual -> titulo);
    atualizar_label(numero_questao, texto);
};

/**
 * @brief 
 * @param 
 * @return
 */
int voltar_lista(GtkLabel *numero_questao, GtkLabel *titulo_quest) {
    char texto[200] = "";   
    ponteiro_atual = ponteiro_atual -> prev;
    
    sprintf(texto, "Lista (%d)", ponteiro_atual -> id);
    atualizar_label(titulo_quest, ponteiro_atual -> titulo);
    atualizar_label(numero_questao, texto);
};

/**
 * @brief 
 * @param 
 * @return
 */
llista checar_lista_monitorada () {
    llista lista_observada;
    FILE *file = NULL;
    char comando[200] = "";
    char qtd[200];
    char qtd_de_questoes[200];
    sprintf(comando, "dados/banco_listas/lista%d/qtd_entrada_saida/quantidade.txt", ponteiro_atual -> id);
    
    file = fopen(comando, "r");
    fscanf(file, "%[^\n]", qtd);
    fclose(file);
    
    strcpy(comando, "");
    sprintf(comando, "dados/banco_listas/lista%d/qtd_entrada_saida/quantidade_questoes.txt", ponteiro_atual -> id);
    file = fopen(comando, "r");
    fscanf(file, "%[^\n]", qtd_de_questoes);
    fclose(file);
    
    lista_observada.qtd_entrada_saida = 0;
    lista_observada.numero_da_lista = 0;
    lista_observada.quantidade_de_questoes = 0;
    lista_observada.numero_da_questao = 0;
    lista_observada.numero_da_lista = ponteiro_atual -> id;
    lista_observada.qtd_entrada_saida =  atoi(qtd);

    lista_observada.quantidade_de_questoes = atoi(qtd_de_questoes);


    return lista_observada;
}