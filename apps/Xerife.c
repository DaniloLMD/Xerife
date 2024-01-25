#include "../include/xerife.h"
#include <gtk-3.0/gtk/gtk.h>

llista Lista_atual_selecionada;
char user_name[100];
#define Max_senha 30
#define Max_nome 30

//variaveis para a parte de cadastrar lista
int contador = 0;
int n_entrada_saida = 0;
GtkListStore* list_store_arquivos_selecionados;
GtkTreeIter iter;


//labels da parte de exibir questao
GtkLabel* label_n_questao;
GtkLabel* label_enunciado_questao;

GtkBuilder *builder;
GtkWidget *window;
GtkStack *stack;
GtkStack *stack_exibir_lista;

//fie chooser referentes a parte de cadastrar questão entrada e saida
//GtkFileChooser* file_chooser;

const char *qtd_questao;
const char *qtd_entrada_saida;
const char *nome_lista;

gchar *caminho_desq_questao;
gchar *caminho_entrada_questao;
gchar *caminho_saida_questao;
gchar* arquivo_usuario_path;



/**
 * @brief Está função destroi a janela geral do aplicativo usando a função main quit
 */
void on_main_window_destroy () {
    gtk_main_quit();
}

/**
 * @brief está função usa as folhas de estilo aplicativas na interface grafica deve ser chamada \n antes de carregar a janela
 * @param 
 * @return 
 */
void usar_estilo () {
    //GtkCssProvider o objeto gtk que guarda o arquivo.css 
    GtkCssProvider *css_provider = gtk_css_provider_new();
    //aqui carregar o provider colocando o objeto que vai receber e o caminho para o arquivo .css
    gtk_css_provider_load_from_path(css_provider, PATH_CSS, false);
    //carregando de fato o css
    gtk_style_context_add_provider_for_screen(
            gdk_screen_get_default(),
            GTK_STYLE_PROVIDER(css_provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
}

int main (int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file(PATH_XERIFE_GLADE);
    
    //file chooser referentes a parte de cadastro de questao  
    
    //labels da parte de mostrar questao
    label_n_questao = GTK_LABEL(gtk_builder_get_object(builder, "numero-questao"));
    label_enunciado_questao = GTK_LABEL(gtk_builder_get_object(builder, "enunciado_questao"));
    
    //stack e window do programa inteiro
    stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));
    stack_exibir_lista = GTK_STACK(gtk_builder_get_object(builder, "stack_exibir_lista"));

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
        "on_cad_lista_enviar_bt_clicked", G_CALLBACK(on_cad_lista_enviar_bt_clicked),
        "on_deslogar_clicked", G_CALLBACK(on_deslogar_clicked),
        "on_bt_ir_cadastrar_lista_clicked", G_CALLBACK(on_bt_ir_cadastrar_lista_clicked),
        "on_bt_mostrar_listas_ativas_clicked", G_CALLBACK(on_bt_mostrar_listas_ativas_clicked),
        "bt_enviar_entrada_saida", G_CALLBACK(bt_enviar_entrada_saida),
        "on_button_submeter_questao_clicked", G_CALLBACK(on_button_submeter_questao_clicked),
        "on_stack_1_escolher_arquivo_file_chooser_confirm_overwrite", G_CALLBACK(on_stack_1_escolher_arquivo_file_chooser_confirm_overwrite),
        "on_stack_1_escolher_arquivo_file_chooser_file_activated",   G_CALLBACK(on_stack_1_escolher_arquivo_file_chooser_file_activated),
        "on_stack_1_casos_de_teste_button_back_clicked", G_CALLBACK(on_stack_1_casos_de_teste_button_back_clicked),
        "on_stack_2_casos_de_teste_button_back_clicked", G_CALLBACK(on_stack_2_casos_de_teste_button_back_clicked),
        "on_bt_ok_message_dialog_box_clicked", G_CALLBACK(on_bt_ok_message_dialog_box_clicked),
        "on_bt_voltar_casos_de_teste_clicked", G_CALLBACK(on_bt_voltar_casos_de_teste_clicked),
        "on_bt_back_descricao_questao_clicked", G_CALLBACK(on_bt_back_descricao_questao_clicked), 
        "on_bt_forward_descricao_questao_clicked", G_CALLBACK(on_bt_forward_descricao_questao_clicked),
        "on_bt_descricao_questao_sair_clicked", G_CALLBACK(on_bt_descricao_questao_sair_clicked),
        "on_bt_lista_ativa_sair_clicked", G_CALLBACK(on_bt_lista_ativa_sair_clicked),
        "on_bt_voltar_cadlista_clicked", G_CALLBACK(on_bt_voltar_cadlista_clicked),
        "on_bt_deletar_lista_clicked", G_CALLBACK(on_bt_deletar_lista_clicked),
        "on_bt_voltar_deletar_lista_numero_clickedF", G_CALLBACK(on_bt_voltar_deletar_lista_numero_clicked),
        "on_bt_enviar_deletar_lista_numero_clicked", G_CALLBACK(on_bt_enviar_deletar_lista_numero_clicked),
        "on_bt_mostrar_rank_clicked", G_CALLBACK(on_bt_mostrar_rank_clicked),
        "on_bt_voltar_rank_clicked", G_CALLBACK(on_bt_voltar_rank_clicked),
        "on_file_chooser_arquivos_cad_geral_confirm_overwrite", G_CALLBACK(on_file_chooser_arquivos_cad_geral_confirm_overwrite),
        "on_file_chooser_arquivos_cad_geral_file_activated", G_CALLBACK(on_file_chooser_arquivos_cad_geral_file_activated),
        "on_bt_desfazer_cad_activate", G_CALLBACK(on_bt_desfazer_cad_activate),
        "on_bt_exercicos_listar_clicked", G_CALLBACK(on_bt_exercicos_listar_clicked),
        "on_bt_sair_da_lista_clicked", G_CALLBACK(on_bt_sair_da_lista_clicked),
        "on_bt_cancelar_cad_clicked", G_CALLBACK(on_bt_cancelar_cad_clicked),
        "on_tree_view_listas_ativas_row_activated", G_CALLBACK(on_tree_view_listas_ativas_row_activated),
        "on_bt_ok_codigo_prompt_clicked", G_CALLBACK(on_bt_ok_codigo_prompt_clicked),
        NULL
    );

    //função do gtk que vai conectar todos as sinais e função de callback do programa
    gtk_builder_connect_signals(builder, NULL);
    
    //função que vai carregar o css
    usar_estilo();
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

void on_bt_submeter_pagina_questao_clicked () {

}

/**
 * @brief Ela vai deixar a visivel a pagina de hub
 * @return void
 */
void on_bt_voltar_cadastro_clicked () {
    gtk_stack_set_visible_child_name(stack, "login");
}   

/**
 * @brief exibe um prompt de mensagem na tela
 * @param const_char* texto que vai ser o titulo do prompt 
 * @param const_char* texto secundario que vai ser exibido no prompt da tela
 * @return void
 */
void mensagem (const char *texto, const char *texto_secundario) {
    GtkMessageDialog *prompt = GTK_MESSAGE_DIALOG(gtk_builder_get_object(builder, "janela_prompt"));
    g_object_set(prompt, "text", texto, NULL);
    g_object_set(prompt, "secondary_text", texto_secundario, NULL);
    
    gtk_widget_show_all(GTK_WIDGET(prompt));
    gtk_dialog_run(GTK_DIALOG(prompt));
}

/**
 * @brief esconde o prompt de mensagem que foi carregado na tela
 * @return void
 */
void on_bt_ok_message_dialog_box_clicked () {
    gtk_widget_hide(GTK_WIDGET(GTK_MESSAGE_DIALOG(gtk_builder_get_object(builder, "janela_prompt"))));
}

/**
 * @brief realiza o cadastro do usuario no sistema
 * @return void
 */
void on_bt_enviar_cadastro_clicked () {
    GtkEntry *eusuario = GTK_ENTRY(gtk_builder_get_object(builder, "entry_usuario_cadastro"));
    GtkEntry *esenha = GTK_ENTRY(gtk_builder_get_object(builder, "entry_senha_cadastro"));
    const char *usuario = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry_usuario_cadastro")));
    const char *senha = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry_senha_cadastro")));

    /*
        verifica se foi digitado algo nos coleteres de text caso uma string vazia tenha sido informada ele exibe
        na tela um aviso e pede para o usúario informar um nome e senha.
    */
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
    /*
        verifica se a senha e nome de usuario estão no limite permitdo pelo sistema caso ele ultrapasse este limite 
        uma mensagem e jogada na tela e o usuario deve informar outra senha e nome
    */
    else if (strlen(usuario) > Max_nome || strlen(senha) > Max_senha) {
        mensagem("Limite de caracteres excedido", "no maximo 200 caracteres para senha e nome de usuário\n tente novamente"); 
        gtk_entry_set_text(eusuario, "");
        gtk_entry_set_text(esenha, "");
    } else {
        /*
            chama uma função de cadastro que realiza alguma verificações internar e retorna 1 caso tenha dado tudo certo
        */
        if (cadastro(usuario, senha) == 1) {
            mensagem(usuario, "Foi cadastrado com sucesso");
            gtk_stack_set_visible_child_name(stack, "login");
            gtk_entry_set_text(eusuario, "");
            gtk_entry_set_text(esenha, "");
        } 
        /*
            retorna 2 caso o usuario informado já esteja cadastrado no sistema 
        */
        else if (cadastro(usuario, senha) == 2) {
            mensagem(usuario, "já existe tente outro");
            gtk_entry_set_text(eusuario, "");
            gtk_entry_set_text(esenha, "");
        }
        /*  
            retorna 3 caso o usuario ou senha tenha caracteres proibidos no caso (,)
        */
        else if (cadastro(usuario, senha) == 3) {
            mensagem("Caractere virgula ( , ) não é permitido", "escolha outro nome ou senha");
            gtk_entry_set_text(eusuario, "");
            gtk_entry_set_text(esenha, "");
        }
    }
}

void limpar_entry(GtkEntry *x) {
    gtk_entry_set_text(x, "");
}


/**
 * @brief realiza o login no sistema
 * @return void
 */
void on_bt_login_tela_login_clicked () {
    GtkEntry *eusuario = GTK_ENTRY(gtk_builder_get_object(builder, "entry_usuario_login"));
    GtkEntry *esenha = GTK_ENTRY(gtk_builder_get_object(builder, "entry_senha_login"));
    const char *usuario = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry_usuario_login")));
    //pegando o nome do usuario logado atualmente
    strcpy(user_name, usuario);
    
    const char *senha = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry_senha_login")));
    /*
        verifica se o nome de usuário obece os limites do sistema
    */
    if (strlen(usuario) > Max_nome || strlen(senha) > Max_senha) {
        mensagem("Login ou Senha excedem a quantidade maxima de caracteres", "");
        gtk_entry_set_text(eusuario, "");
        gtk_entry_set_text(esenha, "");
        return;
    } 
    /*
        verifica se os campos informados estão vazios
    */
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
            gtk_stack_set_visible_child_name(stack, "hub");

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
    //gtk_stack_set_visible_child_name(stack, "hub");
}

/**
 * @brief deixa visivel a página de cadastro da questão
 * @return void
 */
void on_cadastro_questao_clicked () {
    gtk_stack_set_visible_child_name(stack, "pag_cad_questao");
};

/**
 * @brief deixa visivel a página de cadastro de usuário 
 * @return 
 */
void on_bt_cadastre_se_login_clicked () {
    gtk_stack_set_visible_child_name(stack, "cadastro");
}

/**
 * @brief realiza o cadastro da lista pegando o nome, quantidade questões, e numero de entradas e saidas
 * @return void
 */
void on_cad_lista_enviar_bt_clicked () {
    int resultado = 0;
    GtkEntry *enome_lista = GTK_ENTRY(gtk_builder_get_object(builder, "entry_nome_lista"));
    GtkEntry *eqtd_questoes = GTK_ENTRY(gtk_builder_get_object(builder, "entry_numero_de_questoes_cad_lista"));
    GtkEntry *eqtd_entrada_saida = GTK_ENTRY(gtk_builder_get_object(builder, "entry_numero_de_entradas_saidas_cad_lista"));

    GtkListStore* list_store_arquivos_selecionados =  GTK_LIST_STORE(gtk_builder_get_object(builder, "list_store_arquivos_cadastrados"));
    gtk_list_store_clear(list_store_arquivos_selecionados);

    nome_lista = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry_nome_lista")));
    resultado = verificacoes_nome_lista(nome_lista);
    
    if (resultado == 1) {
        qtd_entrada_saida = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry_numero_de_entradas_saidas_cad_lista")));
        qtd_questao = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entry_numero_de_questoes_cad_lista")));
        
        //verifica se algum dos campos contem uma string vazia caso esteja não realiza o cadastro da lista
        
        if ((strcmp(qtd_entrada_saida, "") == 0) || (strcmp(qtd_questao, "") == 0 || (strcmp(nome_lista, "") == 0))) {
            mensagem("algum dos campos está vazio", "");
        }
        else if (!contem_apenas_numeros(qtd_entrada_saida) || !contem_apenas_numeros(qtd_questao)) {
            mensagem("Campo de quantidade de entradas e saidas", "aceita apenas valores numéricos e maiores que 0");
            limpar_entry(eqtd_entrada_saida);
            limpar_entry(eqtd_questoes);
        }
        else {
            /*
            //chama os passos necessários para cria uma lista
            casdastrar_lista(nome_lista, qtd_entrada_saida, qtd_questao);
        
            //aqui carrego a descrição na pasta da questão
            cadastro_descricao_questao(qtd_questao);

            */
    
            //cria a pilha usada para constrolar o cadastro da descrição, entradas e saidas de cada questão
            criar_pilha_geral(qtd_entrada_saida, qtd_questao);
            
            //indo para a pagina geral de cadastro da lista onde vai ser informado os arquivos de entradas, saidas e desq de questão
            gtk_stack_set_visible_child_name(stack, "pag_cad_geral");    
            contador = 0;
        }
    } else {
        switch (resultado)
        {
        case 2:
            mensagem("Nome de lista já foi cadastrado", "escolha outro por favor");
            break;
        
        case 3:
            mensagem("O nome da lista deve conter", "pelo menos uma letra");
            break;
        }
        limpar_entry(enome_lista);
    }   
}


/**
 * @brief desloga do sistema e volta para pagina de login
 * @return void
 */
void on_deslogar_clicked () {
    gtk_stack_set_visible_child_name(stack, "login");
    mensagem("deslogado com sucesso","");
}    

/**
 * @brief 
 * @param 
 * @return 
 */
void on_bt_ir_cadastrar_lista_clicked () {
    gtk_stack_set_visible_child_name(stack, "teste");
}

/**
 * @brief exibe na tela as listas ativas
 * @param 
    * @return 
    */
void on_bt_mostrar_listas_ativas_clicked () {

    if(get_qtd_listas() == 0){
        mensagem("AVISO", "Não há listas cadastradas!");
        return;
    }


    
    iniciar_list_store_listas_ativas(builder);
    gtk_stack_set_visible_child_name(stack, "pag_mostrar_listas");
    gtk_stack_set_visible_child_name(stack_exibir_lista, "pag_exibir_questao");
}

/**
 * @brief exibe na tela o file chooser para o usuario escolher o arquivo a ser julgado
 * @param 
 * @return 
 */
void on_button_submeter_questao_clicked () {
    if(strcmp(user_name, "") == 0){
        mensagem("AVISO!!!", "Logue com um nome de usuario para evitar bugs");
        return;
    }
    gtk_stack_set_visible_child_name(stack_exibir_lista, "pag_enviar_arquivo_resposta");
}

/**
 * @brief exibe a tela de cadastrar entradas e saidas
 * @param 
 * @return 
 */
void bt_enviar_entrada_saida () {
    gtk_stack_set_visible_child_name(stack, "pag_cad_entrada_saida");
};

//escolher_arquivo stack de escolher arquivo

void on_stack_1_escolher_arquivo_file_chooser_confirm_overwrite(){}

/**
 * @brief verifica se o codigo escolhido pelo usuario tem uma extensao valida, se tiver chama as funcoes de julgar o codigo e exibir os casos de teste
 * @param 
 * @return 
 */
void on_stack_1_escolher_arquivo_file_chooser_file_activated(){
    arquivo_usuario_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(gtk_builder_get_object(builder, "stack_1_escolher_arquivo_file_chooser")));

    if(extension_is_valid(arquivo_usuario_path) == false){
        char* file_name = get_file_name_from_path(arquivo_usuario_path);
        char texto[100];
        g_snprintf(texto, 100, "Arquivo \"%s\" possui extensao invalida", file_name);
        mensagem("AVISO", texto);
        return;
    }

    mostrar_casos_de_testes(arquivo_usuario_path);
    gtk_stack_set_visible_child_name(stack_exibir_lista, "resultado_caso_de_teste");
}

/**
 * @brief volta na tela de enunciado da questao
 * @param 
 * @return 
 */
void on_stack_1_casos_de_teste_button_back_clicked(){
    gtk_stack_set_visible_child_name(stack, "stack_0_enunciado_questao");
}

/**
 * @brief julga o codigo e retorna uma string baseado no inteiro correspodente. Ex: caso o julgamento retorne ACCEPTED, retorna a string "ACCEPTED"
 * @param 
 * @return 
 */
// stack de casos_de_teste
char* get_answer(int resultado){
    switch (resultado)
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

/**
 * @brief atualiza a list store com os casos de teste
 * @param 
 * @return 
 */
void mostrar_casos_de_testes(const char* file_path){

    GtkListStore* list_store_casos_de_teste;
    list_store_casos_de_teste =  GTK_LIST_STORE(gtk_builder_get_object(builder, "list_store_casos_de_teste"));
    GtkTreeIter iter;
    gtk_list_store_clear(list_store_casos_de_teste);
    
    int teste = 1; //caso de teste atual

    int n_lista = Lista_atual_selecionada.numero_da_lista;
    int n_questao = Lista_atual_selecionada.numero_da_questao;
    int qtd_casos_de_teste = Lista_atual_selecionada.qtd_entrada_saida;


    char *file_name = get_file_name_from_path(file_path);
    char file_extension[15];
    get_file_extension(file_name, file_extension);
    
    mensagem("JULGANDO", "Por favor aguarde");
    int acertos = 0;
    char * answer;
    int resultado;
    while(teste <= qtd_casos_de_teste){
        resultado = julgar_arquivo(file_path, n_lista, n_questao, teste);
        answer = get_answer(resultado);

        gtk_list_store_append(list_store_casos_de_teste, &iter);
        
        gtk_list_store_set(
            list_store_casos_de_teste, &iter,
            0, teste,
            1, answer,
            -1
        );
        teste++;

        if(resultado != ACCEPTED){
            //se ele nao acertou, atualiza o rank apenas aumentando o numero de tentativas 
            if(!checa_se_ja_fez_a_questao(user_name, Lista_atual_selecionada.numero_da_lista, Lista_atual_selecionada.numero_da_questao)){  
                atualiza_arquivo_rank(Lista_atual_selecionada.numero_da_lista, user_name, false);
            }

            set_novo_envio(n_lista, n_questao, user_name, answer, file_extension, file_path);
            free(file_name);

            return;
        }
    }

    set_novo_envio(n_lista, n_questao, user_name, answer, file_extension, file_path);
    free(file_name);


    //se o usuario ja fez a questao antes, apenas ignora e nao muda o rank
    if(!checa_se_ja_fez_a_questao(user_name, Lista_atual_selecionada.numero_da_lista, Lista_atual_selecionada.numero_da_questao)){  
        //se ele acertou, atualiza o rank aumentando o pontos e as tentativas
        atualiza_arquivo_registro(user_name, Lista_atual_selecionada.numero_da_lista, Lista_atual_selecionada.numero_da_questao);
        atualiza_arquivo_rank(Lista_atual_selecionada.numero_da_lista, user_name, true);
    }
    else{
        mensagem("AVISO", "VOCE JA FEZ A QUESTAO ANTES");
    }
}   

/**
 * @brief volta para a tela de enunciado de questoes
 * @param 
 * @return 
 */
void on_stack_2_casos_de_teste_button_back_clicked(){
    gtk_stack_set_visible_child_name(stack, "stack_0_enunciado_questao");
}

/**
 * @brief volta para a tela do enunciado de questoes
 * @param 
 * @return 
 */
void on_bt_voltar_casos_de_teste_clicked(){
    gtk_stack_set_visible_child_name(stack, "pag_hub_exibir_lista");
    gtk_stack_set_visible_child_name(stack_exibir_lista, "pag_exibir_questao");
}

/**
 * @brief exibe na tela a questao anterior da lista atual, de maneira circular
 * @param 
 * @return 
 */
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

/**
 * @brief exibe na tela a proxima questao da lista atual, de maneira circular
 * @param 
 * @return 
 */
void on_bt_forward_descricao_questao_clicked(){
    /*if(Lista_atual_selecionada.numero_da_questao == Lista_atual_selecionada.quantidade_de_questoes){
        mensagem("Última questão", "Não há mais questões para frente");
        return;
    }*/ 
    Lista_atual_selecionada.numero_da_questao = (Lista_atual_selecionada.numero_da_questao)%(Lista_atual_selecionada.quantidade_de_questoes) + 1;
    mostrar_n_questao(label_n_questao, Lista_atual_selecionada.numero_da_questao);
    mostrar_enunciado(label_enunciado_questao, Lista_atual_selecionada.numero_da_lista, Lista_atual_selecionada.numero_da_questao);
}

/**
 * @brief exibe a tela de listas ativas
 * @param 
 * @return 
 */
void on_bt_descricao_questao_sair_clicked(){
    gtk_stack_set_visible_child_name(stack, "pag_mostrar_listas");
}

/**
 * @brief exibe a tela do hub
 * @param 
 * @return 
 */
void on_bt_lista_ativa_sair_clicked(){
    gtk_stack_set_visible_child_name(stack, "hub");
}


/**
 * @brief exibe a tela do hub
 * @param 
 * @return 
 */
void on_bt_voltar_cadlista_clicked(){
    gtk_stack_set_visible_child_name(stack, "hub");
}

/**
 * @brief atualiza a list store com o nome das listas na pagina de deletar listas
 * @param 
 * @return 
 */
void atualizar_list_store_deletar_listas(){
    GtkListStore* list_store_listas;
    list_store_listas =  GTK_LIST_STORE(gtk_builder_get_object(builder, "list_store_listas"));
    
    GtkTreeIter iter;
    gtk_list_store_clear(list_store_listas);
    
    int n_listas = get_qtd_listas();
    char list_name[100];

    for(int i = 1; i <= n_listas; i++){

        set_nome_lista(i, list_name);

        gtk_list_store_append(list_store_listas, &iter);
        gtk_list_store_set(
            list_store_listas, &iter,
            0, i,
            1, list_name,
            -1
        );
    }

}

/**
 * @brief atualiza e mostra na tela a list store com as listas ativas e a tela de deletar listas
 * @param 
 * @return 
 */
void on_bt_deletar_lista_clicked(){

   /* if(get_qtd_listas() == 0){
        mensagem("AVISO", "Não há listas ativas cadastradas!");
        return;
    }*/

    /*mostrar a list store de listas */
    atualizar_list_store_deletar_listas();

    gtk_stack_set_visible_child_name(stack, "page_deletar_lista_numero");
}

/**
 * @brief mostra a tela do hub
 * @param 
 * @return 
 */
void on_bt_voltar_deletar_lista_numero_clicked(){
    gtk_stack_set_visible_child_name(stack, "hub");
}

/**
 * @brief le o numero da lista via entry e deleta a lista de mesmo numero
 * @param 
 * @return 
 */
void on_bt_enviar_deletar_lista_numero_clicked(){

    GtkEntry *entry = GTK_ENTRY(gtk_builder_get_object(builder, "entry_deletar_lista_numero"));

    const gchar* entrada = gtk_entry_get_text(entry);

    int num_da_lista = atoi(entrada);

    if(num_da_lista < 1 || num_da_lista > get_qtd_listas()){
        mensagem("AVISO", "Lista invalida!\n");
        return;
    }

    mensagem("Lista apagada com sucesso", "");

    deletar_lista(num_da_lista);
   
    atualizar_list_store_deletar_listas();
}

/**
 * @brief atualiza e mostra a list store e a pagina do rank
 * @param 
 * @return 
 */
void on_bt_mostrar_rank_clicked(){

    GtkListStore* list_store_rank;
    list_store_rank =  GTK_LIST_STORE(gtk_builder_get_object(builder, "list_store_rank"));
    GtkTreeIter iter;
    
    gtk_list_store_clear(list_store_rank);
   

    int posicao = 1;

    char rank_path[100];
    sprintf(rank_path, "%s/lista%d/rank.txt", PATH_BANCO_LISTAS, Lista_atual_selecionada.numero_da_lista);
    
    FILE *rank = fopen(rank_path, "r");

    char nome[50];
    int acertos, tentativas;

    while( fscanf(rank, "%[^,],%d,%d%*c", nome, &acertos, &tentativas) != EOF ){
        gtk_list_store_append(list_store_rank, &iter);
        gtk_list_store_set(
            list_store_rank , &iter,
            0, posicao++,
            1, nome,
            2, acertos,
            3, tentativas,
            -1
        );
    }
    fclose(rank);

    gtk_stack_set_visible_child_name(stack_exibir_lista, "rank");
    GtkLabel* label_sua_posicao = GTK_LABEL(gtk_builder_get_object(builder, "label_sua_posicao"));

    int posicao_usuario = get_posicao(user_name, Lista_atual_selecionada.numero_da_lista, Lista_atual_selecionada.numero_da_questao);
    char texto_posicao[50];
    char numero_posicao[10];
    
    if(posicao_usuario   == -1){
        sprintf(numero_posicao, "N/A");
    }
    else {
        sprintf(numero_posicao, "%d", posicao_usuario);
    }
    sprintf(texto_posicao, "Sua posição: %s", numero_posicao);
    gtk_label_set_text(label_sua_posicao, texto_posicao);
}

/**
 * @brief deixa visivel o hub que mostra as listas ativas no sistema
 * @return void
 */
void on_bt_voltar_rank_clicked(){
    gtk_stack_set_visible_child_name(stack, "pag_mostrar_listas");
}

void on_file_chooser_arquivos_cad_geral_confirm_overwrite () {};

/**
 * @brief atualiza a list store e a stack dos arquivos enviados pelo usuario
 * @param 
 * @return 
 */
void on_file_chooser_arquivos_cad_geral_file_activated () {
    char caminho_destino[200];
    int lista_att = 0;
    FILE *file = NULL;
    file = fopen(PATH_QTD_TXT, "r");

    char aux[50];
    char aux2[200];
    char aux3[50];

    fscanf(file, "%d", &lista_att);
    
    lista_att += 1;

    fclose(file);
    gchar* caminho_file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(gtk_builder_get_object(builder, "file_chooser_arquivos_cad_geral")));
    strcpy(aux2, caminho_file);
   
    int qt_questao_at = atoi(qtd_questao);
    int total_et_sd = atoi(qtd_entrada_saida);

    int mod = 2*total_et_sd + 1;
    int n_questao = contador/mod + 1;

    if (contador%mod == 0) {
        sprintf(caminho_destino, "dados/banco_listas/lista%d/questao%d/desq.txt\n",lista_att , n_questao);
        sprintf(aux,"Questao%d", n_questao);

        n_entrada_saida = 1;
    }
    else if ((contador%mod) % 2 != 0) {
        sprintf(caminho_destino, "dados/banco_listas/lista%d/questao%d/entrada/entrada%d.txt\n", lista_att, n_questao, n_entrada_saida);
        sprintf(aux,"Questao%d/entrada%d", n_questao, n_entrada_saida);
    }
    else {
        sprintf(caminho_destino, "dados/banco_listas/lista%d/questao%d/saida/saida%d.txt\n", lista_att, n_questao, (n_entrada_saida));
        sprintf(aux,"Questao%d/saida%d", n_questao, n_entrada_saida);

        n_entrada_saida++;
    }

    gravar_pilha_geral(caminho_file, caminho_destino);

    //gtk_list_store_clear(list_store_arquivos_selecionados);
 
    list_store_arquivos_selecionados =  GTK_LIST_STORE(gtk_builder_get_object(builder, "list_store_arquivos_cadastrados"));
   
    gtk_list_store_append(list_store_arquivos_selecionados, &iter);
        
    gtk_list_store_set(
        list_store_arquivos_selecionados, &iter,
        0, aux,
        1, aux2,
        -1
    );

    if (n_questao == qt_questao_at && n_entrada_saida == total_et_sd+1)  {
        //chama os passos necessários para cria uma lista
        casdastrar_lista(nome_lista, qtd_entrada_saida, qtd_questao);
        
        //aqui carrego a descrição na pasta da questão
        cadastro_descricao_questao(qtd_questao);


        cria_pastas_entrada_saida(qtd_questao);
        mostrar_pilha();
        mensagem("lista foi cadastrada", "com sucesso");



        gtk_stack_set_visible_child_name(stack, "teste");
        
    };
    contador++;
}

/**
 * @brief está função retira o top da pilha que cadastra as questões
 * @return void
 */
void on_bt_desfazer_cad_activate() {
    if (pilha_tamanho_atual() != 0) {
        

        list_store_arquivos_selecionados =  GTK_LIST_STORE(gtk_builder_get_object(builder, "list_store_arquivos_cadastrados"));
        gtk_tree_model_iter_nth_child(GTK_TREE_MODEL(list_store_arquivos_selecionados), &iter, NULL, pilha_tamanho_atual() -1);
        gtk_list_store_remove(list_store_arquivos_selecionados, &iter);
        contador--;
        pop_pilha_geral();
        
    } else {
        mensagem("nenhum arquivo", "foi selecionado");
    }
};

/**
 *  @brief exibe a tela da pagina de questoes
 *  @param
 *  @return
 **/

void on_bt_exercicos_listar_clicked() {
    gtk_stack_set_visible_child_name(stack_exibir_lista, "pag_exibir_questao");
}

/**
 *  @brief exibe a tela de listas ativas
 *  @param
 *  @return 
 **/
void on_bt_sair_da_lista_clicked() {
    gtk_stack_set_visible_child_name(stack, "pag_mostrar_listas");
}


/**
 *  @brief 
 *  @param funcao que cancela o cadastro da lista e exibe a tela anterior de cadastro
 *  @return
 **/
void on_bt_cancelar_cad_clicked(){
    gtk_stack_set_visible_child_name(stack, "teste");
}

void on_tree_view_listas_ativas_row_activated(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data){
    gint n_lista;
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
    gtk_tree_model_get_iter(model, &iter, path);
    gtk_tree_model_get(model, &iter, 0, &n_lista, -1);

    Lista_atual_selecionada.numero_da_lista = n_lista;
    Lista_atual_selecionada.numero_da_questao = 1;
    Lista_atual_selecionada.quantidade_de_questoes = get_qtd_questoes(n_lista);
    Lista_atual_selecionada.qtd_entrada_saida = get_qtd_entrada_saida(n_lista);
    mostrar_n_lista(GTK_LABEL(gtk_builder_get_object(builder, "label_numero_da_lista")), Lista_atual_selecionada.numero_da_lista);
    mostrar_nome_lista(GTK_LABEL(gtk_builder_get_object(builder, "label_nome_da_lista")), Lista_atual_selecionada.numero_da_lista);
    mostrar_n_questao(label_n_questao, Lista_atual_selecionada.numero_da_questao);
    mostrar_enunciado(label_enunciado_questao, Lista_atual_selecionada.numero_da_lista, Lista_atual_selecionada.numero_da_questao);
    gtk_stack_set_visible_child_name(stack, "pag_hub_exibir_lista");
}

void on_bt_mostrar_envios_clicked(){

    atualiza_list_store_envios(builder, Lista_atual_selecionada.numero_da_lista);

    gtk_stack_set_visible_child_name(stack_exibir_lista, "envios");
}

void on_tree_view_envios_row_activated(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data){
    GtkTreeIter iter;

    gint n_envio;

    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
    gtk_tree_model_get_iter(model, &iter, path);
    gtk_tree_model_get(model, &iter, 0, &n_envio, -1);

    
    char codigo[5000];
    get_code_from_envio(Lista_atual_selecionada.numero_da_lista, n_envio, codigo);


    codigo_prompt (n_envio, codigo, builder);
}

/**
 * @brief esconde o prompt de mensagem que foi carregado na tela
 * @return void
 */
void on_bt_ok_codigo_prompt_clicked () {
    gtk_widget_hide(GTK_WIDGET(GTK_MESSAGE_DIALOG(gtk_builder_get_object(builder, "codigo_prompt"))));
}