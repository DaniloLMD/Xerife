#include <stdlib.h>
#include <stdbool.h>
#include "julgar.h"

GtkBuilder* builder;
GtkWidget* window;
GtkStack* stack;
GtkListStore* list_store_casos_de_teste;
GtkFileChooser* file_chooser;
gchar* arquivo_usuario_path;
GtkMessageDialog *mensagem_dialogo;
//==========    outros   ================
void mostrar_casos_de_testes(const char* file_path);

void on_window_enunciado_destroy(){
    gtk_main_quit();
}

void mensagem(char *text, char *secondary_text){
    mensagem_dialogo = GTK_MESSAGE_DIALOG(gtk_builder_get_object(builder, "mensagem_enunciado"));
    
    g_object_set(mensagem_dialogo, "text", text, NULL);
    g_object_set(mensagem_dialogo, "secondary_text", secondary_text, NULL);
    
    gtk_widget_show_all(GTK_WIDGET(mensagem_dialogo));
    gtk_dialog_run(GTK_DIALOG(mensagem_dialogo));
    /*gtk_widget_hide(GTK_WIDGET(mensagem_dialogo));*/
}

void on_mensagem_enunciado_ok_button_clicked(){
    gtk_widget_hide(GTK_WIDGET(mensagem_dialogo));
}


//==========    stack_0_enunciado_questao   ================

void on_button_submeter_questao_clicked(){
    gtk_stack_set_visible_child_name(stack, "stack_1_escolher_arquivo");
}


//==========    stack_1_escolher_arquivo   ================

void on_stack_1_escolher_arquivo_file_chooser_confirm_overwrite(){}

void on_stack_1_escolher_arquivo_file_chooser_file_activated(){
    arquivo_usuario_path = gtk_file_chooser_get_filename(file_chooser);

    if(julgar_arquivo(arquivo_usuario_path, 1) == INVALID_EXTENSION){
        mensagem("AVISO", "Arquivo selecionado possui extensao invalida");
        return;
    }

    gtk_stack_set_visible_child_name(stack, "stack_2_casos_de_teste");
    sleep(1);
    mostrar_casos_de_testes(arquivo_usuario_path);
    
}

void on_stack_1_casos_de_teste_button_back_clicked(){
    gtk_stack_set_visible_child_name(stack, "stack_0_enunciado_questao");
}


//==========    stack_2_casos_de_teste   ================

char* get_answer(const char* file_path, int caso_de_teste){
    switch (julgar_arquivo(file_path, caso_de_teste))
    {

    case ACCEPTED:
        return "ACCEPTED";

    case WRONG_ANSWER:
        return "WRONG ANSWER";

    case COMPILATION_ERROR:
        return "COMPILATION ERROR";

        break;
    case RUNTIME_ERROR:
        return "RUNTIME ERROR";
        break;

    case TIME_LIMIT_EXCEEDED:
        return "TIME LIMIT EXCEEDED";
    
    default:
        return "SYSTEM ERROR";
    }
}

void mostrar_casos_de_testes(const char* file_path){
    /*proximo_user->proximo = NULL;
    proximo_user = cabecalho_user;*/

    int teste = 1;
    int qtd_testes = 50;

    GtkTreeIter iter;
    gtk_list_store_clear(list_store_casos_de_teste);
    while(teste <= qtd_testes){
        gtk_list_store_append(list_store_casos_de_teste, &iter);
        gtk_list_store_set(list_store_casos_de_teste, &iter,
            0, teste,
            1, get_answer(file_path, teste%4),
            -1
        );
        //proximo_user = proximo_user->proximo;
        teste++;
    }
}

void on_stack_2_casos_de_teste_button_back_clicked(){
    gtk_stack_set_visible_child_name(stack, "stack_1_escolher_arquivo");
}



//==========    main   ================
int main(int argc, char* argv[]){

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("descricao-e-submeter-questoes.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_enunciado"));
    stack = GTK_STACK(gtk_builder_get_object(builder, "stack_descricao_e_submeter_questao"));
    file_chooser = GTK_FILE_CHOOSER(gtk_builder_get_object(builder, "stack_1_escolher_arquivo_file_chooser"));
    list_store_casos_de_teste = GTK_LIST_STORE(gtk_builder_get_object(builder, "list_store_casos_de_teste"));

    gtk_builder_add_callback_symbols(
        builder,
        "on_window_enunciado_destroy",                  G_CALLBACK(on_window_enunciado_destroy),
        "on_button_submeter_questao_clicked",           G_CALLBACK(on_button_submeter_questao_clicked),
        "on_stack_1_escolher_arquivo_file_chooser_confirm_overwrite", G_CALLBACK(on_stack_1_escolher_arquivo_file_chooser_confirm_overwrite),
        "on_stack_1_escolher_arquivo_file_chooser_file_activated",   G_CALLBACK(on_stack_1_escolher_arquivo_file_chooser_file_activated),
        "on_stack_1_casos_de_teste_button_back_clicked", G_CALLBACK(on_stack_1_casos_de_teste_button_back_clicked),
        "on_mensagem_enunciado_ok_button_clicked", G_CALLBACK(on_mensagem_enunciado_ok_button_clicked),
        "on_stack_2_casos_de_teste_button_back_clicked",        G_CALLBACK(on_stack_2_casos_de_teste_button_back_clicked),
        NULL
    );

    gtk_builder_connect_signals(builder, NULL);


    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}