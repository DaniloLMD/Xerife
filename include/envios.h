#ifndef __ENVIOS_H__
#define __ENVIOS_H__

#include <gtk/gtk.h>

void inicializar_pasta_envios(int n_lista);

int get_qtd_envios(int n_lista);

void incrementa_qtd_envios(int n_lista);

void set_novo_envio(int n_lista, int questao, char* user_name, char* resultado, char* linguagem, const char* code_path);

void atualiza_list_store_envios(GtkBuilder *builder, int n_lista);

void codigo_prompt (int n_envio, char *codigo, GtkBuilder* builder);

void get_code_from_envio(int n_lista, int n_envio, char* str);

#endif