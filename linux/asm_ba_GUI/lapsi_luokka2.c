#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create a new window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GtkTextView Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Create a GtkTextView widget
    GtkWidget *text_view = gtk_text_view_new();

    // Set the size request for the GtkTextView
    gtk_widget_set_size_request(text_view, 300, 200);

    // Add the GtkTextView to the window
    gtk_container_add(GTK_CONTAINER(window), text_view);

    // Connect the destroy signal to quit the GTK main loop
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Show all widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();

    return 0;
}
