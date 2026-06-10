#include <gtk/gtk.h>
GtkWidget *entry1;
GtkWidget *entry2;
GtkWidget *entry3;
GtkWidget *selected_entry = nullptr;
GtkTextBuffer *buffer;
const char* text_to_copy;

void copy_selected_fields(GtkWidget *widget, gpointer data) {
   GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
   //const char* text_to_copy = "Selected: field1, field2"; // Modify this to collect actual values
   text_to_copy = gtk_entry_get_text(GTK_ENTRY(selected_entry));
   if(selected_entry != NULL){
       // GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget));
       // GtkTextIter start, end;
      //  gtk_text_buffer_get_start_iter(buffer, &start);
      //  gtk_text_buffer_get_end_iter(buffer, &end);
      //  gchar *text_to_copy = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
        
        gtk_clipboard_set_text(clipboard, text_to_copy, -1);
//   GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(entry1));
   }else{
        g_print("widget is null");
   }   
}

void paste_to_target_field(GtkWidget *widget, gpointer data) {
    g_print("paste_to_target_field");
   GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
   gchar *text = gtk_clipboard_wait_for_text(clipboard);
   gtk_entry_set_text(GTK_ENTRY(selected_entry), text);
   g_free(text);
}

// Callback for the "Copy" button
void on_copy_button_clicked(GtkButton *button, gpointer user_data) {
    
    //selected_entry = static_cast<GtkWidget *>(user_data);
    copy_selected_fields(selected_entry, NULL);
    /*
    if (selected_entry) {
        // Get the text from the selected entry
        const gchar *text = gtk_entry_get_text(GTK_ENTRY(selected_entry));

        // Access the clipboard
        GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);

        // Set the text to the clipboard
        gtk_clipboard_set_text(clipboard, text, -1);
    }*/
}

// Callback for selecting an entry
void on_entry_selected(GtkEntry *entry, gpointer user_data) {
    //GtkWidget **selected_entry = static_cast<GtkWidget **>(user_data);
    g_print("selected:");
    
    if(entry != NULL){
        g_print("entry is not null");
        selected_entry = GTK_WIDGET(entry);
        //*selected_entry = GTK_WIDGET(entry);
        //buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(selected_entry));

       // GtkTextIter start, end;
      //  gtk_text_buffer_get_start_iter(buffer, &start);
      //  gtk_text_buffer_get_end_iter(buffer, &end);
      //  gchar *text_to_copy = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
        
     //   gtk_clipboard_set_text(clipboard, text_to_copy, -1);
//   GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(entry1));
   }else{
        g_print("selected_entry is null");
   }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Copy-Paste Example");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    // Create a vertical box layout
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create multiple entry fields
    
    GtkWidget *entry1 = gtk_entry_new();
    GtkWidget *entry2 = gtk_entry_new();
    GtkWidget *entry3 = gtk_entry_new();
    
    /*entry1 = gtk_text_view_new();
    entry2 = gtk_text_view_new();
    entry3 = gtk_text_view_new();

    gtk_entry_set_placeholder_text(GTK_ENTRY(entry1), "Field 1");
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry2), "Field 2");
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry3), "Field 3");
*/    

    gtk_box_pack_start(GTK_BOX(vbox), entry1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry3, FALSE, FALSE, 0);

    // Create a "Copy" button
    GtkWidget *copy_button = gtk_button_new_with_label("Copy");
    GtkWidget *paste_button = gtk_button_new_with_label("Paste");
    gtk_box_pack_start(GTK_BOX(vbox), copy_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), paste_button, FALSE, FALSE, 0);

    // Track the currently selected entry
    

    // Connect signals
    
    g_signal_connect(entry1, "focus-in-event", G_CALLBACK(on_entry_selected), &selected_entry);
    g_signal_connect(entry2, "focus-in-event", G_CALLBACK(on_entry_selected), &selected_entry);
    g_signal_connect(entry3, "focus-in-event", G_CALLBACK(on_entry_selected), &selected_entry);
    g_signal_connect(copy_button, "clicked", G_CALLBACK(on_copy_button_clicked), &selected_entry);
    g_signal_connect(paste_button, "clicked", G_CALLBACK(paste_to_target_field), &selected_entry);

    // Show all widgets
    gtk_widget_show_all(window);

    // Connect the destroy signal to quit the application
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();

    return 0;
}
