#ifndef cad_questao
#define cad_questao

#include "includes.h"
#include "control_list.h"
#include "gtk-3.0/gtk/gtk.h"

void cria_pastas_entrada_saida (const char*); 
void cadastro_descricao_questao(const char*);
void gravar_arquivo(gchar*);
void criar_pilha_geral(const char *qtd_entrada_saida, const char* qtd_questao);
void gravar_pilha_geral(const char *caminho, char *caminho_onde_vai);
void pop_pilha_geral();
void mostrar_pilha();
int pilha_tamanho_atual();

#endif