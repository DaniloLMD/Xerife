#include "../include/xerife.h"
#include <gtk-3.0/gtk/gtk.h>

llista Lista_atual_selecionada;

//labels da parte de exibir questao
GtkLabel* label_n_questao;
GtkLabel* label_enunciado_questao;

GtkBuilder *builder;
GtkWidget *window;
GtkStack *stack;

//labels referentes a pagina de registrar questão
GtkLabel *label_pag_enviar_desq_questao;
GtkLabel *label_pag_enviar_entrada;
GtkLabel *label_pag_enviar_saida;
GtkLabel *label_questao_cad_entrada_saida;

//GtkListStore* list_store_casos_de_teste;

//estes labels pertencem a página de carregar as listas
GtkLabel *numero_questao;
GtkLabel *titulo_questao;

//fie chooser referentes a parte de cadastrar questão entrada e saida
GtkFileChooser *desq_questao;
GtkFileChooser *entrada_questao;
GtkFileChooser *saida_questao;
GtkFileChooser* file_chooser;

const char *qtd_questao;
const char *qtd_entrada_saida;

gchar *caminho_desq_questao;
gchar *caminho_entrada_questao;
gchar *caminho_saida_questao;
gchar* arquivo_usuario_path;

GtkMessageDialog *prompt;

void on_main_window_destroy () {
    gtk_main_quit();
}

void usar_estilo () {
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, PATH_CSS, false);
    gtk_style_context_add_provider_for_screen(
            gdk_screen_get_default(),
            GTK_STYLE_PROVIDER(css_provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
}

void on_sinal_clicked (){
    g_print("oii estou funcionando");
}

int main (int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file(PATH_XERIFE_GLADE);
    //labels que pertencem a página de carregar questão
    numero_questao = GTK_LABEL(gtk_builder_get_object(builder, "label_numero_lista_exibir_lista"));
    titulo_questao = GTK_LABEL(gtk_builder_get_object(builder, "label_titulo_questao_exibir_lista"));
    
    //file chooser referentes a parte de cadastro de questao
    desq_questao = GTK_FILE_CHOOSER(gtk_builder_get_object(builder, "file_chooser_text_questao"));
    entrada_questao = GTK_FILE_CHOOSER(gtk_builder_get_object(builder, "file_chooser_entrada_questao"));
    saida_questao = GTK_FILE_CHOOSER(gtk_builder_get_object(builder, "file_chooser_saida_questao"));
    file_chooser = GTK_FILE_CHOOSER(gtk_builder_get_object(builder, "stack_1_escolher_arquivo_file_chooser")); 

    //labels da parte de mostrar questao
    label_n_questao = GTK_LABEL(gtk_builder_get_object(builder, "numero-questao"));
    label_enunciado_questao = GTK_LABEL(gtk_builder_get_object(builder, "enunciado_questao"));

    //stack e window do programa inteiro
    stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    //list_store_casos_de_teste = GTK_LIST_STORE(gtk_builder_get_object(builder, "list_store_casos_de_teste"));

    gtk_builder_add_callback_symbols( builder,
        "on_main_window_destroy", G_CALLBACK(on_main_window_destroy),
        "on_bt_submeter_pagina_questao_clicked", G_CALLBACK(on_bt_submeter_pagina_questao_clicked),
        "on_bt_voltar_cadastro_clicked", G_CALLBACK (on_bt_voltar_cadastro_clicked),
        "on_bt_enviar_cadastro_clicked", G_CALLBACK(on_bt_enviar_cadastro_clicked),
        "on_bt_login_tela_login_clicked", G_CALLBACK(on_bt_login_tela_login_clicked),
        "on_bt_cadastre_se_login_clicked", G_CALLBACK(on_bt_cadastre_se_login_clicked),
        "on_cadastro_questao_clicked", G_CALLBACK(on_cadastro_questao_clicked),
        "on_sinal_clicked", G_CALLBACK(on_sinal_clicked),
        "on_cad_lista_enviar_bt_clicked", G_CALLBACK(on_cad_lista_enviar_bt_clicked),
        "on_bt_avancar_exibir_listar_clicked", G_CALLBACK(on_bt_avancar_exibir_listar_clicked),
        "on_bt_voltar_exibir_lista_clicked", G_CALLBACK(on_bt_voltar_exibir_lista_clicked),
        "on_deslogar_clicked", G_CALLBACK(on_deslogar_clicked),
        "on_bt_ir_cadastrar_lista_clicked", G_CALLBACK(on_bt_ir_cadastrar_lista_clicked),
        "on_bt_mostrar_listas_ativas_clicked", G_CALLBACK(on_bt_mostrar_listas_ativas_clicked),
        "on_file_chooser_text_questao_confirm_overwrite", G_CALLBACK(on_file_chooser_text_questao_confirm_overwrite),
        "on_file_chooser_text_questao_file_activated", G_CALLBACK(on_file_chooser_text_questao_file_activated),
        "on_file_chooser_entrada_questao_confirm_overwrite", G_CALLBACK(on_file_chooser_entrada_questao_confirm_overwrite),
        "on_file_chooser_entrada_questao_file_activated", G_CALLBACK(on_file_chooser_entrada_questao_file_activated),
        "on_file_chooser_saida_questao_confirm_overwrite", G_CALLBACK(on_file_chooser_saida_questao_confirm_overwrite),
        "on_file_chooser_saida_questao_file_activated", G_CALLBACK(on_file_chooser_saida_questao_file_activated),
        "bt_enviar_entrada_saida", G_CALLBACK(bt_enviar_entrada_saida),
        "bt_proxima_questao_cad_enviar_desq_pag", G_CALLBACK(bt_proxima_questao_cad_enviar_desq_pag),
        "on_bt_proxima_questao_entrada_saida_clicked", G_CALLBACK(on_bt_proxima_questao_entrada_saida_clicked),
        "on_button_submeter_questao_clicked", G_CALLBACK(on_button_submeter_questao_clicked),
        "on_stack_1_escolher_arquivo_file_chooser_confirm_overwrite", G_CALLBACK(on_stack_1_escolher_arquivo_file_chooser_confirm_overwrite),
        "on_stack_1_escolher_arquivo_file_chooser_file_activated",   G_CALLBACK(on_stack_1_escolher_arquivo_file_chooser_file_activated),
        "on_stack_1_casos_de_teste_button_back_clicked", G_CALLBACK(on_stack_1_casos_de_teste_button_back_clicked),
        "on_stack_2_casos_de_teste_button_back_clicked", G_CALLBACK(on_stack_2_casos_de_teste_button_back_clicked),
        "on_bt_lista_selecionada_entrar_clicked", G_CALLBACK(on_bt_lista_selecionada_entrar_clicked),
        "on_bt_ok_message_dialog_box_clicked", G_CALLBACK(on_bt_ok_message_dialog_box_clicked),
        "on_bt_voltar_casos_de_teste_clicked", G_CALLBACK(on_bt_voltar_casos_de_teste_clicked),
        "on_bt_back_descricao_questao_clicked", G_CALLBACK(on_bt_back_descricao_questao_clicked), 
        "on_bt_forward_descricao_questao_clicked", G_CALLBACK(on_bt_forward_descricao_questao_clicked),
        "on_bt_descricao_questao_sair_clicked", G_CALLBACK(on_bt_descricao_questao_sair_clicked),
        "on_bt_lista_ativa_sair_clicked", G_CALLBACK(on_bt_lista_ativa_sair_clicked),
        "on_bt_voltar_cadlista_clicked", G_CALLBACK(on_bt_voltar_cadlista_clicked),
        NULL
    );

    gtk_builder_connect_signals(builder, NULL);

    
    usar_estilo();
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
    prompt = GTK_MESSAGE_DIALOG(gtk_builder_get_object(builder, "janela_prompt"));
    g_object_set(prompt, "text", texto, NULL);
    g_object_set(prompt, "secondary_text", texto_secundario, NULL);
    
    gtk_widget_show_all(GTK_WIDGET(prompt));
    gtk_dialog_run(GTK_DIALOG(prompt));
}

void on_bt_ok_message_dialog_box_clicked () {
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

    else if (strlen(usuario) > 30 || strlen(senha) > 30) {
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
        else if (cadastro(usuario, senha) == 3) {
            mensagem("Caractere virgula ( , ) não é permitido", "escolha outro nome ou senha");
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
    if (strlen(usuario) > 30 || strlen(senha) > 30) {
        mensagem("Login ou Senha excedem a quantidade maxima de caracteres", "");
        gtk_entry_set_text(eusuario, "");
        gtk_entry_set_text(esenha, "");
        return;
    }
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
    gtk_stack_set_visible_child_name(stack, "hub");

}

void on_cadastro_questao_clicked () {
    gtk_stack_set_visible_child_name(stack, "pag_cad_questao");
};

void on_bt_cadastre_se_login_clicked () {
    gtk_stack_set_visible_child_name(stack, "cadastro");
}

void on_cad_lista_enviar_bt_clicked () {
    const char *nome_lista = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry_nome_lista")));
    qtd_entrada_saida = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry_numero_de_entradas_saidas_cad_lista")));
    qtd_questao = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry_numero_de_questoes_cad_lista")));
    
    //verifica se algum dos campos contem uma string vazia caso esteja não realiza o cadstro da lista
    if ((strcmp(qtd_entrada_saida, "") == 0) || (strcmp(qtd_questao, "") == 0 || (strcmp(nome_lista, "") == 0))) {
        mensagem("algum dos campos está vazio", "");
    }
    else {
        casdastrar_lista(nome_lista, qtd_entrada_saida, qtd_questao);
    
        //aqui carrego a lista com a pasta
        cadastro_descricao_questao(qtd_questao);

        gtk_stack_set_visible_child_name(stack, "page_cadastro_desq_questao");    
    }
}


void on_bt_avancar_exibir_listar_clicked () {
    int resposta = avancar_lista(numero_questao, titulo_questao);
    Lista_atual_selecionada = checar_lista_monitorada();

    switch (resposta)
    {
    case 1:
        mensagem("Você chegou na ultima lista", "So a opção voltar funcionara");
        break;
    
    default:
        break;
    }
}

void on_bt_voltar_exibir_lista_clicked () {
    int resposta = voltar_lista(numero_questao, titulo_questao);
    Lista_atual_selecionada = checar_lista_monitorada();
    
    switch (resposta)
    {
    case 1:
        mensagem("Você chegou na primeira lista", "So a opção avançar funcionara");
        break;
    
    default:
        break;
    }
}

void on_bt_lista_selecionada_entrar_clicked () {
    Lista_atual_selecionada.numero_da_questao = 1;
    mostrar_n_questao(label_n_questao, Lista_atual_selecionada.numero_da_questao);
    mostrar_enunciado(label_enunciado_questao, Lista_atual_selecionada.numero_da_lista, Lista_atual_selecionada.numero_da_questao);
    gtk_stack_set_visible_child_name(stack, "stack_0_enunciado_questao");
    
}

void on_deslogar_clicked () {
    gtk_stack_set_visible_child_name(stack, "login");
    mensagem("deslogado com sucesso","");
}    

void on_bt_ir_cadastrar_lista_clicked () {
    gtk_stack_set_visible_child_name(stack, "teste");
}

void on_bt_mostrar_listas_ativas_clicked () {
    carregar_listas_ativas();
    gtk_stack_set_visible_child_name(stack, "pag_mostrar_listas");
    iniciar_label(numero_questao, titulo_questao);
    Lista_atual_selecionada = checar_lista_monitorada();
}

void bt_proxima_questao_cad_enviar_desq_pag () {
    label_pag_enviar_desq_questao = GTK_LABEL(gtk_builder_get_object(builder, "label_pag_enviar_desq_questao"));

    if (proxima_questao(caminho_desq_questao) == 1) {
        qtd_entrada_saida = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry_numero_de_entradas_saidas_cad_lista")));
        cria_pastas_entrada_saida(qtd_questao);

        criar_carregar_lista(qtd_questao);
        criar_carregar_lista_entrada_saida(qtd_entrada_saida);
        gtk_stack_set_visible_child_name(stack, "pag_cad_entrada_saida");
    };
    
    atualizar_text_label(label_pag_enviar_desq_questao, 'd');
}

void on_bt_proxima_questao_entrada_saida_clicked () {
    label_pag_enviar_saida = GTK_LABEL(gtk_builder_get_object(builder, "label_pag_enviar_saida"));
    label_pag_enviar_entrada = GTK_LABEL(gtk_builder_get_object(builder, "label_pag_enviar_entrada"));
    label_questao_cad_entrada_saida = GTK_LABEL(gtk_builder_get_object(builder, "label_questao_cad_entrada_saida"));

    if (proxima_questao_entrada_saida() == 1) {
        gtk_stack_set_visible_child_name(stack, "login");
    }
    atualizar_text_label(label_questao_cad_entrada_saida, 'q');
    atualizar_text_label(label_pag_enviar_entrada, 'e');
    atualizar_text_label(label_pag_enviar_saida, 's');
}

void on_button_submeter_questao_clicked () {
    gtk_stack_set_visible_child_name(stack, "stack_1_escolher_arquivo");
}

void bt_enviar_entrada_saida () {
    gtk_stack_set_visible_child_name(stack, "pag_cad_entrada_saida");
};

//escolher_arquivo stack de escolher arquivo

void on_stack_1_escolher_arquivo_file_chooser_confirm_overwrite(){}

void on_stack_1_escolher_arquivo_file_chooser_file_activated(){
    arquivo_usuario_path = gtk_file_chooser_get_filename(file_chooser);

    if(extension_is_valid(arquivo_usuario_path) == false){
        char* file_name = get_file_name_from_path(arquivo_usuario_path);
        char texto[100];
        g_snprintf(texto, 100, "Arquivo \"%s\" possui extensao invalida", file_name);
        mensagem("AVISO", texto);
        return;
    }

    mostrar_casos_de_testes(arquivo_usuario_path);
    gtk_stack_set_visible_child_name(stack, "stack_2_casos_de_teste");
}

void on_stack_1_casos_de_teste_button_back_clicked(){
    gtk_stack_set_visible_child_name(stack, "stack_0_enunciado_questao");
}

// stack de casos_de_teste
char* get_answer(const char* file_path, int n_lista, int n_questao, int n_caso_de_teste){
    switch (julgar_arquivo(file_path, n_lista, n_questao, n_caso_de_teste))
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
        return "ERROR";
    }
}

void mostrar_casos_de_testes(const char* file_path){

    GtkListStore* list_store_casos_de_teste;
    list_store_casos_de_teste =  GTK_LIST_STORE(gtk_builder_get_object(builder, "list_store_casos_de_teste"));
    
    
    int teste = 1; //caso de teste atual

    int n_lista = Lista_atual_selecionada.numero_da_lista;
    int n_questao = Lista_atual_selecionada.numero_da_questao;
    int qtd_casos_de_teste = Lista_atual_selecionada.qtd_entrada_saida;

    GtkTreeIter iter;
    gtk_list_store_clear(list_store_casos_de_teste);


    
    mensagem("JULGANDO", "Por favor aguarde");
    while(teste <= qtd_casos_de_teste){
        
        gtk_list_store_append(list_store_casos_de_teste, &iter);
        
        gtk_list_store_set(
            list_store_casos_de_teste, &iter,
            0, teste,
            1, get_answer(file_path, n_lista, n_questao, teste),
            -1
        );
        teste++;
    }
}   

void on_stack_2_casos_de_teste_button_back_clicked(){
    gtk_stack_set_visible_child_name(stack, "stack_0_enunciado_questao");
}

void on_file_chooser_text_questao_confirm_overwrite(){};

void on_file_chooser_text_questao_file_activated () {
    caminho_desq_questao = gtk_file_chooser_get_filename(desq_questao);  
    gravar_arquivo(caminho_desq_questao);
    mensagem("arquivo selecionado com succeso", "clicke em ok e depois em proxima questão");
};

//dois boleanos para verificar se os dois arquivos foram selecionados
bool Clicked1 = false;
bool Clicked2 = false;

void on_file_chooser_entrada_questao_confirm_overwrite (){};

void on_file_chooser_entrada_questao_file_activated () {
    Clicked1 = true;
    caminho_entrada_questao = gtk_file_chooser_get_filename(entrada_questao);

    if (Clicked1 == true && Clicked2 == false) {
        (caminho_entrada_questao, caminho_saida_questao);
        gravar_arquivo_entrada(caminho_entrada_questao);

        mensagem("arquivo de entrada selecionado", "por favor selecione as saidas");

    } else if (Clicked1 == true && Clicked2 == true) {
        gravar_arquivo_entrada(caminho_entrada_questao);

        mensagem("arquivos cadastrados com sucesso", "clique em proxima questão para avançar");
        Clicked1 = false;
        Clicked2 = false;
    }
};

void on_file_chooser_saida_questao_confirm_overwrite (){};

void on_file_chooser_saida_questao_file_activated () {
    Clicked2 = true;
    caminho_saida_questao = gtk_file_chooser_get_filename(saida_questao);

    if (Clicked2 == true && Clicked1 == false) {
        gravar_arquivo_saida(caminho_saida_questao);
        mensagem("arquivo de saida selecionado", "por favor selecione o arquivo de entrada");

    }
    else if (Clicked2 == true && Clicked1 == true) {
        gravar_arquivo_saida(caminho_saida_questao);

        mensagem("arquivos cadastrados com sucesso", "clique em proxima questão para avançar");
        Clicked1 = false;
        Clicked2 = false;
    }
};

void on_bt_voltar_casos_de_teste_clicked(){
    gtk_stack_set_visible_child_name(stack, "stack_0_enunciado_questao");
}

void on_bt_back_descricao_questao_clicked(){
    /*if(Lista_atual_selecionada.numero_da_questao == 1){
        mensagem("Primeira questão", "Não há mais questões para trás");
        return;
    }*/

    Lista_atual_selecionada.numero_da_questao--;
    if(Lista_atual_selecionada.numero_da_questao <= 0)
        Lista_atual_selecionada.numero_da_questao = Lista_atual_selecionada.quantidade_de_questoes;

    mostrar_n_questao(label_n_questao, Lista_atual_selecionada.numero_da_questao);
    mostrar_enunciado(label_enunciado_questao, Lista_atual_selecionada.numero_da_lista, Lista_atual_selecionada.numero_da_questao);
}

void on_bt_forward_descricao_questao_clicked(){
    /*if(Lista_atual_selecionada.numero_da_questao == Lista_atual_selecionada.quantidade_de_questoes){
        mensagem("Última questão", "Não há mais questões para frente");
        return;
    }*/ 
    Lista_atual_selecionada.numero_da_questao = (Lista_atual_selecionada.numero_da_questao)%(Lista_atual_selecionada.quantidade_de_questoes) + 1;
    mostrar_n_questao(label_n_questao, Lista_atual_selecionada.numero_da_questao);
    mostrar_enunciado(label_enunciado_questao, Lista_atual_selecionada.numero_da_lista, Lista_atual_selecionada.numero_da_questao);
}

void on_bt_descricao_questao_sair_clicked(){
    gtk_stack_set_visible_child_name(stack, "pag_mostrar_listas");
}


void on_bt_lista_ativa_sair_clicked(){
    gtk_stack_set_visible_child_name(stack, "hub");
}


void on_bt_voltar_cadlista_clicked(){
    gtk_stack_set_visible_child_name(stack, "hub");
}