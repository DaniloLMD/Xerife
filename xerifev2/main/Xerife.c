#include "xerife.h"
#include <stdio.h>
#include <gtk-3.0/gtk/gtk.h>

GtkBuilder *builder;
GtkWidget *window;
GtkStack *stack;

void on_main_window_destroy () {
    gtk_main_quit();
}
int main (int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("Xerife.glade");

    gtk_builder_add_callback_symbols( builder,
        "on_main_window_destroy", G_CALLBACK(on_main_window_destroy),
        "on_bt_submeter_pagina_questao_clicked", G_CALLBACK(on_bt_submeter_pagina_questao_clicked),
        "on_bt_voltar_cadastro_clicked", G_CALLBACK (on_bt_voltar_cadastro_clicked),
        "on_bt_enviar_cadastro_clicked", G_CALLBACK(on_bt_enviar_cadastro_clicked),
        "on_bt_login_tela_login_clicked", G_CALLBACK(on_bt_login_tela_login_clicked),
        "on_bt_cadastre_se_login_clicked", G_CALLBACK(on_bt_cadastre_se_login_clicked),
        NULL
    );

    gtk_builder_connect_signals(builder, NULL);

    stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

void on_bt_submeter_pagina_questao_clicked () {

}

void on_bt_voltar_cadastro_clicked () {
    gtk_stack_set_visible_child_name(stack, "login");
}   

void mensagem (const char *texto, const char *texto_secundario) {
    GtkMessageDialog *prompt = GTK_MESSAGE_DIALOG(gtk_builder_get_object(builder, "janela-prompt"));
    g_object_set(prompt, "text", texto, NULL);
    g_object_set(prompt, "secondary_text", texto_secundario, NULL);
    
    gtk_widget_show_all(GTK_WIDGET(prompt));
    gtk_dialog_run(GTK_DIALOG(prompt));
    gtk_widget_hide(GTK_WIDGET(prompt));

}

void on_bt_enviar_cadastro_clicked () {
    GtkEntry *eusuario = GTK_ENTRY(gtk_builder_get_object(builder, "entry_usuario_cadastro"));
    GtkEntry *esenha = GTK_ENTRY(gtk_builder_get_object(builder, "entry_senha_cadastro"));
    const char *usuario = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry_usuario_cadastro")));
    const char *senha = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry_senha_cadastro")));
   
    if (strlen(usuario) == 0 || strlen(senha) == 0) {
        if (strlen(usuario) == 0 && strlen(senha) == 0) {
            mensagem("ambos os campos estão vazios", "por favor informe nome e senha");
        }
        else if (strlen(usuario) == 0) {
            mensagem("Campo do usuário vazio", "por favor coloque um nome");
        } else {
            mensagem("Campo de senha vazia", "por favor informe uma senha");
        }
    }

    else if (strlen(usuario) > 200 || strlen(senha) > 200) {
        mensagem("Limite de caracteres excedido", "no maximo 200 caracteres para senha e nome de usuário\n tente novamente"); 
        gtk_entry_set_text(eusuario, "");
        gtk_entry_set_text(esenha, "");
    } else {
        if (cadastro(usuario, senha) == 1) {
            mensagem(usuario, "Foi cadastrado com sucesso");
            gtk_stack_set_visible_child_name(stack, "login");
            gtk_entry_set_text(eusuario, "");
            gtk_entry_set_text(esenha, "");
        } 
        else if (cadastro(usuario, senha) == 2) {
            mensagem(usuario, "já existe tente outro");
            gtk_entry_set_text(eusuario, "");
            gtk_entry_set_text(esenha, "");
        }
    }
}

void on_bt_login_tela_login_clicked () {
    GtkEntry *eusuario = GTK_ENTRY(gtk_builder_get_object(builder, "entry_usuario_login"));
    GtkEntry *esenha = GTK_ENTRY(gtk_builder_get_object(builder, "entry_senha_login"));
    const char *usuario = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry_usuario_login")));
    const char *senha = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry_senha_login")));
    
    if ((strcmp(usuario, "") == 0) && strcmp(senha, "") == 0) {
        mensagem("Espaço de senha ou usuario está vazia", "insira seus dados de login");
        gtk_entry_set_text(eusuario, "");
        gtk_entry_set_text(esenha, "");
    } else {
        int resposta = login(usuario, senha);

        switch (resposta)
        {
        case 1:
            mensagem("logado com sucesso !!!", "");
            gtk_entry_set_text(eusuario, "");
            gtk_entry_set_text(esenha, "");

            break;
        case 2:
            mensagem("senha ou login incorreto !!!", "");
            gtk_entry_set_text(eusuario, "");
            gtk_entry_set_text(esenha, "");

            break;
        case 3:
            mensagem(usuario, " não está cadastrado");
            gtk_entry_set_text(eusuario, "");
            gtk_entry_set_text(esenha, "");

            break;
        default:
            break;
        }
    }
   
}


void on_bt_cadastre_se_login_clicked () {
    gtk_stack_set_visible_child_name(stack, "cadastro");
}