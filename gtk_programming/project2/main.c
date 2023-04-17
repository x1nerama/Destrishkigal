#include <gtk-2.0/gtk/gtk.h>
#include <glib-2.0/glib.h>

int main(int argc, char *argv[]) {
    /* Create Widgets */
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label1, *label2; /* Labels */
    GtkWidget *entry1, *entry2; /* Entrys for Input */
    GtkWidget *button;
    /* Init */
    gtk_init(&argc, &argv);
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL); /* Create Window with TOPLEVEL */
        gtk_window_set_title(GTK_WINDOW(window), "Bufferoverflow GUI ~ devTBenoth");
        gtk_container_set_border_width(GTK_CONTAINER(window), 10);
        gtk_window_resizable(GTK_WINDOW(true), FALSE);
        gtk_window
}