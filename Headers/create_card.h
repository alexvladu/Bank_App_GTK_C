#ifndef create_memcard
#define create_memcard
void create_card_function(GtkWidget *button, gpointer data)
{
	struct Send_Create_Card_Data *d = (struct Send_Create_Card_Data *)data;
	int id=d->id;
	int type=d->type;
	char *purpose=malloc(200);
	strcpy(purpose, gtk_entry_get_text(GTK_ENTRY(d->entry)));
	
	
	gtk_widget_destroy(GTK_WIDGET(d->parent_dialog));
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    gtk_window_set_title(GTK_WINDOW(dialog), "Succes!");
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 400, 200);
    
	GtkWidget *grid = gtk_grid_new();
	GtkWidget *succes = gtk_label_new("Your card was succesfully created");
	gtk_widget_set_name(succes, "selecttext-runapp");
	
	insert_card(get_last_card_id()+1, id, type, 0, purpose);
	
	gtk_grid_attach(GTK_GRID(grid), succes, 0, 1, 1, 1);
    gtk_container_add(GTK_CONTAINER(modal_area), grid);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(dialog), 0);
    gtk_widget_show_all(dialog);
    
    
}
void try_create_card(GtkWidget *button, gpointer data)
{
	struct Send_Create_Card_Data *d = (struct Send_Create_Card_Data *)data;
	int type=d->type;
	int id=d->id;
	gtk_widget_destroy(GTK_WIDGET(d->parent_dialog));
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_window_set_title(GTK_WINDOW(dialog), "Account Management");
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 400, 200);
    
    GtkWidget *purpose = gtk_entry_new();
    gtk_widget_set_size_request(purpose, 200, 50);
	gtk_entry_set_placeholder_text(GTK_ENTRY(purpose), "Purpose");//place holder
	
	char *type_of_card=malloc(200);
	if(type==1)
		strcpy(type_of_card, "Create Credit Card");
	if(type==2)
		strcpy(type_of_card, "Create Checking Card");
	if(type==3)
		strcpy(type_of_card, "Create Savings Card");
		
	GtkWidget *submit = gtk_button_new_with_label(type_of_card);
	
	gtk_widget_set_name(purpose, "create-card-purpose");
	gtk_widget_set_name(submit, "create-card-submit");
	

	d->parent_dialog=dialog;
	d->entry=purpose;
	
	g_signal_connect(submit, "clicked", G_CALLBACK(create_card_function), d);
	
	GtkWidget *grid = gtk_grid_new();
	gtk_grid_attach(GTK_GRID(grid), purpose, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), submit, 0, 2, 1, 1);
    gtk_container_add(GTK_CONTAINER(modal_area), grid);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    
    gtk_window_set_resizable(GTK_WINDOW(dialog), 0);
	gtk_widget_grab_focus(submit);
    gtk_widget_show_all(dialog);
}
#endif
