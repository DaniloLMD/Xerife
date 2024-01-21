#ifndef __MOSTRAR_QUESTAO_H__
#define __MOSTRAR_QUESTAO_H__

#include <gtk/gtk.h>

void mostrar_enunciado(GtkLabel* label, int n_lista, int n_questao);
void mostrar_n_questao(GtkLabel* label, int n_questao);

void mostrar_questao(GtkLabel* label_numero, GtkLabel* label_enunciado, int n_lista, int n_questao);

void mostrar_n_lista(GtkLabel *label, int n_lista);

void mostrar_nome_lista(GtkLabel *label, int n_lista);

#endif