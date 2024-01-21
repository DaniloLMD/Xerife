#include "../include/mostrar_lista.h"
#include "../include/includes.h"

/**
 * @brief Recebe um builder do gtk, carrega e atualiza uma tree view com as listas ativas
 * @param builder builder do gtk para carregar a tree view
 * @return void
*/
void iniciar_list_store_listas_ativas(GtkBuilder* builder){
    GtkListStore* list_store_listas_ativas;
    list_store_listas_ativas =  GTK_LIST_STORE(gtk_builder_get_object(builder, "list_store_listas_ativas"));
    GtkTreeIter iter;
    gtk_list_store_clear(list_store_listas_ativas);

    char list_name[100];
    for(int i = 1; i <= get_qtd_listas(); i++){

        set_nome_lista(i, list_name);

        gtk_list_store_append(list_store_listas_ativas, &iter);
        gtk_list_store_set(
            list_store_listas_ativas, &iter,
            0, i,
            1, list_name,
            2, get_qtd_questoes(i),
            -1
        );
    }
}
