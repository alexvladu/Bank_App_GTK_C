#ifndef run_app
#define run_app
#include "Headers/change_pass.h"
#include "Headers/create_card.h"
#include "Headers/select_card.h"
#include "Headers/card_operation.h"
#include "Headers/edit_card.h"
#include "Headers/ac_management.h"
#include "Headers/show_transactions.h"
#include "Headers/xtra.h"
#include "Headers/external.h"
void import_file(GtkWidget *widget, gpointer data) {
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
void export_data_function(GtkWidget *button, int *cardid)
{
	if(*cardid==0)
		return;
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_window_set_title(GTK_WINDOW(dialog), "Show Transactions");
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 800, 400);
    gtk_window_set_resizable(GTK_WINDOW (dialog), 0);
    
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(modal_area), vbox);
    
    GtkWidget *pdf = gtk_label_new("Exported PDF Successfully");
    GtkWidget *csv = gtk_label_new("Exported CSV Successfully");
    GtkWidget *where = gtk_label_new("You can find data in Extern_File");
    
	gtk_widget_set_name(pdf, "exps-runapp");
	gtk_widget_set_name(csv, "exps-runapp");
	gtk_widget_set_name(where, "exp-runapp");
    
    gtk_box_pack_start(GTK_BOX(vbox), pdf, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), csv, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), where, TRUE, TRUE, 0);
    
    gtk_widget_show_all(dialog);
    
	create_pdf(cardid);
}
void run_aplication(int id)
{
	struct User user=get_user_by_id(id);
	int *select_card_id=g_new(int, 1);
	*select_card_id=0;
	int *pagina=g_new(int, 1);
	*pagina=1;
	GtkWidget *display_select_card_label=gtk_label_new("Please select a card");
	
	GtkWidget *app_grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), app_grid);
	gtk_widget_set_halign(app_grid, GTK_ALIGN_CENTER);
	display_welcome(app_grid, display_select_card_label, user);
    
    GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(box1), 5);
    gtk_widget_set_halign(box1, GTK_ALIGN_CENTER);
    
	GtkWidget *select_account = gtk_button_new_with_label("Select Card");
	gtk_widget_set_size_request(select_account, 300, 100);
	gtk_widget_set_name(select_account, "select-runapp");
	gtk_box_pack_start(GTK_BOX(box1), select_account, FALSE, FALSE, 0);
	
	GtkWidget *show_transactions = gtk_button_new_with_label("Show transactions");
	gtk_widget_set_size_request(show_transactions, 300, 100);
	gtk_widget_set_name(show_transactions, "accesdenied-runapp");
	gtk_box_pack_start(GTK_BOX(box1), show_transactions, FALSE, FALSE, 0);
	
	GtkWidget *box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(box2), 5);
    gtk_widget_set_halign(box2, GTK_ALIGN_CENTER);
	
	GtkWidget *deposit = gtk_button_new_with_label("Deposit");
	gtk_widget_set_size_request(deposit, 300, 100);
	gtk_widget_set_name(deposit, "accesdenied-runapp");
	gtk_box_pack_start(GTK_BOX(box2), deposit, FALSE, FALSE, 0);
	
	GtkWidget *withdraw = gtk_button_new_with_label("Withdraw");
	gtk_widget_set_size_request(withdraw, 300, 100);
	gtk_widget_set_name(withdraw, "accesdenied-runapp");
	gtk_box_pack_start(GTK_BOX(box2), withdraw, FALSE, FALSE, 0);
	
	GtkWidget *box3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(box3), 5);
    gtk_widget_set_halign(box3, GTK_ALIGN_CENTER);
    
	GtkWidget *pay = gtk_button_new_with_label("Pay");
	gtk_widget_set_size_request(pay, 300, 100);
	gtk_widget_set_name(pay, "accesdenied-runapp");
	gtk_box_pack_start(GTK_BOX(box3), pay, FALSE, FALSE, 0);
    
	GtkWidget *transfer = gtk_button_new_with_label("Transfer");
	gtk_widget_set_size_request(transfer, 300, 100);
	gtk_widget_set_name(transfer, "accesdenied-runapp");
	gtk_box_pack_start(GTK_BOX(box3), transfer, FALSE, FALSE, 0);
	
	GtkWidget *box4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(box4), 5);
    gtk_widget_set_halign(box4, GTK_ALIGN_CENTER);
    
	GtkWidget *check_balance = gtk_button_new_with_label("Check Balance");
	gtk_widget_set_size_request(check_balance, 300, 100);
	gtk_widget_set_name(check_balance, "accesdenied-runapp");
	gtk_box_pack_start(GTK_BOX(box4), check_balance, FALSE, FALSE, 0);
	
    GtkWidget *account_management = gtk_button_new_with_label("Account Management");
	gtk_widget_set_size_request(account_management, 300, 100);
	gtk_widget_set_name(account_management, "checkbalance-runapp");
	gtk_box_pack_start(GTK_BOX(box4), account_management, FALSE, FALSE, 0);
	
	GtkWidget *box5 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(box5), 5);
    gtk_widget_set_halign(box5, GTK_ALIGN_CENTER);
    
	GtkWidget *import_data = gtk_button_new_with_label("Import data");
	gtk_widget_set_size_request(import_data, 300, 100);
	gtk_widget_set_name(import_data, "accesdenied-runapp");
	gtk_box_pack_start(GTK_BOX(box5), import_data, FALSE, FALSE, 0);
	
	GtkWidget *export_data = gtk_button_new_with_label("Export Data");
	gtk_widget_set_size_request(export_data, 300, 100);
	gtk_widget_set_name(export_data, "accesdenied-runapp");
	gtk_box_pack_start(GTK_BOX(box5), export_data, FALSE, FALSE, 0);
	
	GtkWidget *box6 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(box6), 5);
    gtk_widget_set_halign(box6, GTK_ALIGN_CENTER);
       
    GtkWidget *change_password = gtk_button_new_with_label("Change password");
	gtk_widget_set_size_request(change_password, 300, 100);
	gtk_widget_set_name(change_password, "logout-runapp");
	gtk_box_pack_start(GTK_BOX(box6), change_password, FALSE, FALSE, 0);
    GtkWidget *logout = gtk_button_new_with_label("Log out");
	gtk_widget_set_size_request(logout, 300, 100);
	gtk_widget_set_name(logout, "logout-runapp");
	gtk_box_pack_start(GTK_BOX(box6), logout, FALSE, FALSE, 0);
	struct Send_Select_Card_Data *d=g_new(struct Send_Select_Card_Data, 1);
	d->user_id=id;
	d->select_card_id=select_card_id;
	d->display_select_card_label=display_select_card_label;
	d->select_account=select_account;
	d->show_transactions=show_transactions;
	d->deposit=deposit;
	d->withdraw=withdraw;
	d->pay=pay;
	d->import_data=import_data;
	d->export_data=export_data;
	d->transfer=transfer;
	d->check_balance=check_balance;
	g_signal_connect(select_account, "clicked", G_CALLBACK(select_card), d);
	struct Send_Operation_Data *d1=g_new(struct Send_Operation_Data, 1);
	d1->card_id=select_card_id;
	d1->user_id=id;
	g_signal_connect(deposit, "clicked", G_CALLBACK(deposit_function), d1);
	g_signal_connect(withdraw, "clicked", G_CALLBACK(withdraw_function), d1);
	g_signal_connect(pay, "clicked", G_CALLBACK(pay_function), d1);
	g_signal_connect(transfer, "clicked", G_CALLBACK(transfer_function), d1);
	
	struct Send_Transaction_Data *d2=g_new(struct Send_Transaction_Data, 1);
	d2->pagina=pagina;
	d2->card_id=select_card_id;
    d2->page_info=gtk_label_new(display_pages_count(*pagina, get_last_transaction_id()));
	d2->list_store=gtk_list_store_new(NUM_COLUMNS, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);
	d2->tree_view=gtk_tree_view_new_with_model(GTK_TREE_MODEL(d2->list_store));
    for (int i = 0; i < NUM_COLUMNS; i++) {
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes("", renderer, "text", i, NULL);
        gtk_tree_view_column_set_title(column, get_column_text(i));
        gtk_tree_view_append_column(GTK_TREE_VIEW(d2->tree_view), column);
    }
	g_signal_connect(show_transactions, "clicked", G_CALLBACK(display_transactions), d2);
    g_signal_connect(check_balance, "clicked", G_CALLBACK(check_balance_function), select_card_id);
	g_signal_connect(account_management, "clicked", G_CALLBACK(account_management_function), GINT_TO_POINTER(id));
	g_signal_connect(change_password, "clicked", G_CALLBACK(change_password_function), GINT_TO_POINTER(id));
	g_signal_connect(export_data, "clicked", G_CALLBACK(export_data_function), select_card_id);
	g_signal_connect(logout, "clicked", G_CALLBACK(logout_function), app_grid);
	g_signal_connect(import_data, "clicked", G_CALLBACK(import_file), NULL);
	gtk_grid_attach(GTK_GRID(app_grid), box1, 0, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(app_grid), box2, 0, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(app_grid), box3, 0, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(app_grid), box4, 0, 6, 1, 1);
	gtk_grid_attach(GTK_GRID(app_grid), box5, 0, 7, 1, 1);
	gtk_grid_attach(GTK_GRID(app_grid), box6, 0, 8, 1, 1);
	gtk_widget_show_all(window);
}
#endif
