#ifndef MOSTRAR_LIST
#define MOSTRAR_LIST
#include <gtk-3.0/gtk/gtk.h>

#include "struct_list.h"
#include "lista.h"
void carregar_listas_ativas();

int avancar_lista(GtkLabel*, GtkLabel*);

int voltar_lista(GtkLabel*, GtkLabel*);

llista checar_lista_monitorada();

void iniciar_label(GtkLabel*, GtkLabel*);

#endif