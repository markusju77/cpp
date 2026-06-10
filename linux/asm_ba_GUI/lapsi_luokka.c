#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Fixed Size GtkTextView Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);

    GtkWidget *text_view = gtk_text_view_new();
    gtk_widget_set_size_request(text_view, 200, 100); // Fixed size
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
