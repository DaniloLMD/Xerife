#ifndef XEREFI_H
#define XEREFI_H

#include "cadastro.h"
#include "includes.h"
#include "login.h"
#include "cadastro_lista.h"
#include "mostrar_lista.h"
#include "cad_questao.h"
#include "julgar.h"

void on_bt_submeter_pagina_questao_clicked ();

void on_bt_voltar_cadastro_clicked ();

void mensagem (const char *texto, const char *texto_secundario);

void on_bt_enviar_cadastro_clicked ();

void on_bt_login_tela_login_clicked ();

void on_bt_cadastre_se_login_clicked ();

void on_cadastro_questao_clicked ();

void on_bt_enviar_cadquesatao_clicked ();

void on_bt_enviar_quantidade_questao_clicked ();

void on_cad_lista_enviar_bt_clicked ();

void on_bt_avancar_exibir_listar_clicked ();

void on_bt_voltar_exibir_lista_clicked ();

void on_deslogar_clicked ();

void on_bt_ir_cadastrar_lista_clicked();

void on_bt_mostrar_listas_ativas_clicked ();

void on_bt_enviar_cad_enunciado_questao_clicked ();

void on_file_chooser_text_questao_confirm_overwrite ();

void on_file_chooser_text_questao_file_activated ();

void on_file_chooser_entrada_questao_confirm_overwrite ();

void on_file_chooser_entrada_questao_file_activated ();

void on_file_chooser_saida_questao_confirm_overwrite ();

void on_file_chooser_saida_questao_file_activated ();

void bt_enviar_entrada_saida ();

void bt_proxima_questao_cad_desq_pag();

void bt_proxima_questao_cad_enviar_desq_pag();

void on_bt_enviar_entrada_saida_clicked();

void on_bt_proxima_questao_entrada_saida_clicked();

void on_bt_lista_selecionada_entrar_clicked ();

void on_button_submeter_questao_clicked();

void on_stack_1_escolher_arquivo_file_chooser_confirm_overwrite ();

void on_stack_1_escolher_arquivo_file_chooser_file_activated();

void on_stack_1_casos_de_teste_button_back_clicked();

void on_stack_2_casos_de_teste_button_back_clicked();

void mostrar_casos_de_testes(const char*);

char* get_answer(const char*, int);

void on_bt_ok_message_dialog_box_clicked(); 

#endif