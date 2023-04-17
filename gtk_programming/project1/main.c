#include <gtk-3.0/gtk/gtk.h>
#include <glib-2.0/glib.h>

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label1, *label2;
    GtkWidget *entry1, *entry2;
    GtkWidget *button;
    
    gtk_init(&argc, &argv);

    // Pencere oluşturma
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Metin Kutusu Örneği");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE); // Boyutlandırmayı devre dışı bırak
    gtk_widget_set_size_request(window, 600, 400); // Boyut ayarı
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Grid oluşturma
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // İlk metin kutusu
    label1 = gtk_label_new("Adınız: ");
    gtk_grid_attach(GTK_GRID(grid), label1, 0, 0, 20, 20);
    entry1 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry1, 1, 0, 1, 1);

    // İkinci metin kutusu
    label2 = gtk_label_new("Soyadınız: ");
    gtk_grid_attach(GTK_GRID(grid), label2, 0, 1, 1, 1);
    entry2 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry2, 1, 1, 1, 1);

    // Düğme oluşturma
    button = gtk_button_new_with_label("Gönder");
    gtk_grid_attach(GTK_GRID(grid), button, 1, 50, 1, 1);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(gtk_main_quit), NULL);

    // Tüm widget'ları görünür yapma
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}