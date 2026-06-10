#include <gtk/gtk.h>

void insert_text_at_position(GtkTextBuffer *buffer, const gchar *text, gint position) {
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, position);
    gtk_text_buffer_insert(buffer, &iter, text, -1);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *text_view = gtk_text_view_new();
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    insert_text_at_position(buffer, "Hello, World!", 5);

    gtk_container_add(GTK_CONTAINER(window), text_view);
    gtk_widget_show_all(window);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_main();

    return 0;
}
