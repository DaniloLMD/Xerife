#include "../include/cad_questao.h"
#include "../include/includes.h"


 
chead *lista = NULL;
chead *lista_questao = NULL;
cnode *aux = NULL;
cnode *aux_entrada_saida = NULL;

char lista_atual[200];

/**
 * @brief está função carrega a lista que está sendo cadastrada no sistema
 * 
 * @param const_char* quantidade de questões presentes na lista
 * @return void
 */
void criar_carregar_lista(const char *qtd_questao) {
    lista = criar_c_lista();
    for (int i = 1; i <= atoi(qtd_questao); i++) {
        adicionar_c_fim(lista, i);
    }
    aux = lista -> begin;
};

/**
 * @brief está função vai criar a lista de entrada e saida que cada questão vai receber \n usada para controlar o fluxo de dados no sistema
 * @param const_char* quantidade de entrada e saidas da lista 
 * @return void
 */
void criar_carregar_lista_entrada_saida(const char *qtd_entrada_saida) {
    lista_questao = criar_c_lista();
    for (int i = 1; i <= atoi(qtd_entrada_saida); i++) {
        adicionar_c_fim(lista_questao, i);
    }
    aux_entrada_saida = lista_questao -> begin;
};

/**
 * @brief está função vai criar as pastas que vão receber cada questão, criando o caminho automatico até elas
 * @param const_char* quantidade de questões que a lista tem
 * @return void
 */
void cria_pastas_desq_questao (const char * qtd_questao) {
    int max_questao = atoi(qtd_questao);
    FILE *aqr = fopen(PATH_QTD_TXT, "r");
    fscanf(aqr, "%[^\n]", lista_atual);
    fclose(aqr);
    char caminho[100];

    /*
        este for vai caminhar pelos caminhos criando a quantidade x de pastas necessárias para 
        armazenar a quantidade de questões de cada lista x
    */
    for (int i = 1; i <= max_questao; i++) {
        sprintf(caminho, "mkdir %s/lista%d/questao%d/", PATH_BANCO_LISTAS, atoi(lista_atual), i);
        system(caminho);
    }

    //chamando a função que vai carregar a lista criada para controlar o entrada de dados no front end
    criar_carregar_lista(qtd_questao);
}

/**
 * @brief Parece com a função de cima porém ela caminha pelas pastas das questões criada pela função de cima \n e cria sub-pastas de entrada e saida onde vão ser guardados os arquivos de entrada e saida dessas respectivas questões
 * @param const_char* quantidade de questẽos da lista
 * @return void
 */
void cria_pastas_entrada_saida (const char *qtd_questao) {
    char caminho[200] = "";
    int max_questao = atoi(qtd_questao);

    for (int i = 1; i <= max_questao; i++) {
        sprintf(caminho, "mkdir %s/lista%d/questao%d/entrada/", PATH_BANCO_LISTAS, atoi(lista_atual), i);
        system(caminho);
        sprintf(caminho, "mkdir %s/lista%d/questao%d/saida/", PATH_BANCO_LISTAS, atoi(lista_atual), i);
        system(caminho);
    }
}

/**
 * @brief função de controle sua unica função é chamar outras na ordem que foram designadas 
 * @param qtd_questao
 * @return void
 */
void cadastro_descricao_questao(const char* qtd_questao) {
    cria_pastas_desq_questao(qtd_questao);
};

/**
 * @brief está função copia os arquivos que estão na pasta fornecida e move para pasta que guarda as questões de cada lista
 * @param gchar* caminho da pasta que contem o arquivo que deseja ser gravado no sistema 
 * @return void
 */
void gravar_arquivo (gchar *caminho) {
    //grava a descrição da questão
    char caminho_destino[100];
    char caminho_final[300] = "cp ";
    sprintf(caminho_destino, " %s/lista%d/questao%d/desq.txt", PATH_BANCO_LISTAS, atoi(lista_atual), aux -> numero_questao);
    strcat(caminho_final, (char*) caminho);
    strcat(caminho_final, caminho_destino);
    system(caminho_final);

}

/**
 * @brief Libera as memórias que foram alocadas e usadas durante o processo das outras funções
 * @return void 
 */
void fechar_recursos() {
    destruir_c_lista(lista);
}

/**
 * @brief Está função avança na lista que foi simulada usando uma lista encadeada 
 * @return 1 caso a lista tenha chegado no seu final
 */
int proxima_questao () {
    if (aux == lista -> end) {
        fechar_recursos();
        return 1;
    } else {
        aux = aux -> next;
    }    
};

void atualizar_text_label(GtkLabel *text, char c) {
    char texto[100];
    if (c == 'q') {
        sprintf(texto, "questão atual %d", aux -> numero_questao);
        gtk_label_set_text(text, texto);
    }
    if (c == 'd') {
        sprintf(texto, "Selecione o .txt que contem a descrição da questão %d", aux -> numero_questao);
        gtk_label_set_text(text, texto);
        return;
    }
    if (c == 'e') {
        sprintf(texto, "Selecione o .txt que contem a entrada %d", aux_entrada_saida -> numero_questao);
        gtk_label_set_text(text, texto);

        return;
    }
    if (c == 's') {
        sprintf(texto, "Selecione o .txt que contem a saida %d", aux_entrada_saida -> numero_questao);
        gtk_label_set_text(text, texto);

        return;
    }
}

void gravar_arquivo_entrada (gchar* caminho_entrada) {
    char caminho_destino[100];
    char caminho_final[300] = "cp ";

    sprintf(caminho_destino, " %s/lista%d/questao%d/entrada/entrada%d.txt", PATH_BANCO_LISTAS, atoi(lista_atual),
        aux -> numero_questao, aux_entrada_saida -> numero_questao
    );
    
    strcat(caminho_final, (char*) caminho_entrada);
    strcat(caminho_final, caminho_destino);

    system(caminho_final);

}

/**
 * @brief está função copia os dados fornecidos nos caminhos para as pastas \n que foram criadas para recebê-los
 * @param gchar* caminho_entrada
 * @param gchar* caminho_saida
 * @return void
 */
void gravar_arquivo_saida (gchar *caminho_saida) {
    char caminho_destino[100];
    char caminho_final[300] = "cp ";

    sprintf(caminho_destino, " %s/lista%d/questao%d/saida/saida%d.txt", PATH_BANCO_LISTAS, atoi(lista_atual),
        aux -> numero_questao, aux_entrada_saida -> numero_questao
    );

    strcat(caminho_final, (char*) caminho_saida);
    strcat(caminho_final, caminho_destino);

    system(caminho_final);

}

/**
 * @brief está função avança na lista encadeada de entrada e saidas
 *
 * @return void 
 */
int proxima_questao_entrada_saida () {
    if (aux_entrada_saida == lista_questao -> end ) {
        aux_entrada_saida = lista_questao -> begin;
        /*
            a ideia aqui foi simular uma matriz usando listas encadeadas por isso toda vez que a lista
            de entradas e saidas chega no final ela volta pro começo
            já que a estrutura de uma lista de questões segue esse padrão
            Questão 1 (entradas e saidas) 
            Questão 2 (entradas e saidas)
            as listas são cadastradas com a mesma quantidade de entradas e saídas 
        */
        if (aux == lista -> end) {
            destruir_c_lista(lista);
            destruir_c_lista(lista_questao);

            return 1;
        }
        //saltando de linha na matriz
        aux = aux -> next;
    } 
    else {
        //pulando de coluna na matriz
        aux_entrada_saida = aux_entrada_saida -> next;
    }
}