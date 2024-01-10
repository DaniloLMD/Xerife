#ifndef cad_questao
#define cad_questao

#include "includes.h"
#include "control_list.h"
#include "gtk-3.0/gtk/gtk.h"

void cria_pastas_entrada_saida (const char*); 
void criar_carregar_lista(const char *qtd_questao);
void criar_carregar_lista_entrada_saida(const char *qtd_entrada_saida);
void cadastro_descricao_questao(const char*);
int proxima_questao();
void gravar_arquivo(gchar*);
int proxima_questao_entrada_saida();
void gravar_arquivo_entrada(gchar *caminho_entrada);
void gravar_arquivo_saida(gchar*caminho_saida);
void atualizar_text_label(GtkLabel *text, char c);

#endif