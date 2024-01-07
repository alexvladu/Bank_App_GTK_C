#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "Headers/pre_process.h"
#include "Headers/domain.h"
#include "Headers/data_query.h"
GtkWidget *grid_login;
GtkWidget *grid_register;
GtkWidget *window;
int current_login_display=1;
void init_grid_login(GtkWidget *window);
#include "run_app.h"
#include "Headers/auth.h"
void init_window(GtkWidget *window)
{
	gtk_window_set_title(GTK_WINDOW(window), "Banking Aplication");
  	gtk_window_set_default_size (GTK_WINDOW (window), 1366, 800);
 	gtk_window_set_resizable(GTK_WINDOW (window), 0);
}
void init_main_grid(GtkWidget *main_grid, GtkWidget *import_data_button)
{
	gtk_grid_attach(GTK_GRID(main_grid), import_data_button, 0, 0, 1, 1);
	gtk_widget_set_halign(main_grid, GTK_ALIGN_CENTER);
}
void file_open(GtkWidget *widget, gpointer window) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;
    dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(window), action, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
    gtk_window_set_default_size(GTK_WINDOW(dialog), 800, 600);
    gtk_window_set_resizable(GTK_WINDOW (dialog), 0);
    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        g_print("Selected file: %s\n", filename);
    }
    gtk_widget_destroy(dialog);
}
int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    init_window(window);

    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    gtk_css_provider_load_from_file(provider, g_file_new_for_path("Style/style.css"), NULL);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
		
    //GtkWidget *import_data_button = gtk_button_new_with_label("Import Data");
	//g_signal_connect(import_data_button, "clicked", G_CALLBACK(file_open), window);
	
	run_aplication(1);
	
    gtk_widget_show_all(window);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_main();
    return 0;
}
