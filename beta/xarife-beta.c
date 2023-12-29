//#include <gtk-3.0/gtk/gtk.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>
#include "julgar.h"

GtkBuilder *builder;
GtkWidget *window;

void on_onmainwindow_destroy () {
    gtk_main_quit();
}

void usar_estilo () {
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, "a.css", false);
    gtk_style_context_add_provider_for_screen(
            gdk_screen_get_default(),
            GTK_STYLE_PROVIDER(css_provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
}

void mensagem (const char* text, const char* secundary) {
    GtkDialog *msg = GTK_DIALOG(gtk_builder_get_object(builder, "msg"));
    g_object_set(msg, "text", text, NULL);
    g_object_set(msg, "secondary_text", secundary, NULL);

    gtk_widget_show_all(GTK_WIDGET(msg));
    gtk_dialog_run(msg);
    gtk_widget_hide(GTK_WIDGET(msg));

}
void on_submeter_clicked () {
    
    //char *texto = gtk_builder_get_object(builder, "entrada");
    const char *texto = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "entrada")));
    
    // função que vai rodar o codigo ficar aqui ex 1 sucesso 2 run time 3 compile error 4 time limit
    

    switch (julgar(texto))
    {
    case ACCEPTED:
        mensagem("ACCEPTED", ":)");
        break;
    case WRONG_ANSWER:
        mensagem("WRONG ANSWER", ":'(");

        break;
    case COMPILATION_ERROR:
        mensagem("COMPILATION ERROR", ":o");

        break;
    case RUNTIME_ERROR:
        mensagem("RUNTIME ERROR", ":-O");
        break;

    case TIME_LIMIT_EXCEEDED:
        mensagem("TIME LIMIT EXCEEDED", "!!!");
        break;
    
    default:
        mensagem("nao era pra ter aparecido nao", "eita");
        break;
    }

    
} 
int main (int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("xarife-beta.glade");

    gtk_builder_add_callback_symbols(builder,
        "on_submeter_clicked", on_submeter_clicked,
        "on_onmainwindow_destroy", on_onmainwindow_destroy,
    
        NULL
    );
    gtk_builder_connect_signals(builder, NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "onmainwindow"));
    usar_estilo();
    gtk_widget_show_all(window);
    
    gtk_main();
}