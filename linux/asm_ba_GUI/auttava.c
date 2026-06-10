#include <gtk/gtk.h>

GtkWidget   *isanta;
GtkWidget   *Painike;
GtkWidget   *lapsi;
GtkBuilder  *builder;
GtkWidget *window;
GtkWidget *text_view;
GtkWidget *postfix;
gchar *text;

void suorita(GtkWidget *wid, gpointer ptr){
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    GtkTextBuffer *buffer2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(postfix));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    
    //Siirrä allaoleva liitos myöhemmin text_view liitokseen!
    //gtk_text_buffer_set_text(buffer2, text, -1);
    g_print(text);
}

void on_menu_item_activate(GtkMenuItem *menuitem, gpointer data) {
    g_print("Menu item pressed!\n"); 
    gtk_widget_show_all(window);
}

int main(int argc, char *argv[]){
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "menu_auttavasti.glade", NULL);
    isanta = (GtkWidget *)gtk_builder_get_object(builder, "isanta");
    g_signal_connect(isanta, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    postfix = (GtkWidget *)gtk_builder_get_object(builder, "postfix");

    //lapsi = (GtkWidget *)gtk_builder_get_object(builder, "lapsi");
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //gtk_window_set_default_size(GTK_WINDOW(lapsi), 400, 300);
    GtkMenuItem *menu_item = GTK_MENU_ITEM(gtk_builder_get_object(builder, "syota"));
    text_view = gtk_text_view_new();
    GtkWidget *btn = gtk_button_new_with_label("Suorita");
    g_signal_connect (btn, "clicked", G_CALLBACK(suorita), NULL);
    
    // Set the size request for the GtkTextView
    gtk_widget_set_size_request(text_view, 300, 200);
    GtkWidget *box = gtk_vbox_new (FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), text_view, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), btn, TRUE, TRUE, 0);

    // Add the GtkTextView to the window
    //gtk_container_add(GTK_CONTAINER(window), text_view);
    gtk_container_add(GTK_CONTAINER(window), box);      

    //GtkWidget *tv = (GtkWidget *)gtk_builder_get_object(builder, "tw");
    
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    // Create a GtkTextView widget
    
    g_signal_connect(menu_item, "activate", G_CALLBACK(on_menu_item_activate), NULL);
    //gtk_container_add(GTK_CONTAINER(scrolled_window), tv);
    gtk_widget_hide(window);
    //gtk_widget_show_all(window);
    gtk_widget_show(isanta);
    gtk_main();
    return EXIT_SUCCESS;
}