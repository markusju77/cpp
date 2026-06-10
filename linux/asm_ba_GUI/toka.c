#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>

GtkWidget   *isanta;
GtkWidget   *fixed;
GtkWidget   *Nappi;
GtkWidget   *lapsi;
GtkBuilder  *builder;

static void on_Nappi_clicked(GtkButton *Nappi){
    gtk_widget_show(lapsi);
}

int main(int argc, char *argv[]){
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();

    gtk_builder_add_from_file (builder, "toka.glade", NULL);

    isanta = (GtkWidget *)gtk_builder_get_object(builder, "isanta");
    


    g_signal_connect(isanta, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //gtk_builder_connect_signals(builder, isanta);

    fixed = (GtkWidget *)gtk_builder_get_object(builder, "fixed");
    Nappi = (GtkWidget *)gtk_builder_get_object(builder, "Nappi");
    lapsi = (GtkWidget *)gtk_builder_get_object(builder, "lapsi");
    g_signal_connect(Nappi, "clicked", G_CALLBACK(on_Nappi_clicked), NULL);
    //g_signal_connect(Nappi, "clicked", on_Nappi_clicked(), NULL);
/*
    gtk_widget_show(window);
*/
    gtk_widget_show_all(isanta);
    gtk_main();
    return EXIT_SUCCESS;
}

