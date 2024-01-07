#ifndef editare
#define editare
void edit_card_function(GtkWidget *button, gpointer data)
{
	struct Send_Pick_Edit_Card_Data *d=(struct Send_Pick_Edit_Card_Data *)data;
	char *text=malloc(200);
	int card_id=d->card_id;
	strcpy(text, gtk_entry_get_text(GTK_ENTRY(d->entry)));
	gtk_widget_destroy(d->parent_dialog);
	struct Card card=get_card_by_id(card_id);
	strcpy(card.desc, text);
	change_card(card);
}
void return_edit_card(GtkWidget *button, gpointer data)
{
	struct Send_Pick_Edit_Card_Data *d=(struct Send_Pick_Edit_Card_Data *)data;
	int card_id=d->card_id;
	gtk_widget_destroy(d->parent_dialog);
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));

	struct Card card=get_card_by_id(card_id);
	char *type_of_card=malloc(200);
	if(card.type==1)
		strcpy(type_of_card, "Edit Credit Card Purpose");
	if(card.type==2)
		strcpy(type_of_card, "Edit Checking Card Purpose");
	if(card.type==3)
		strcpy(type_of_card, "Edit Savings Card Purpose");

    gtk_window_set_title(GTK_WINDOW(dialog), type_of_card);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 400, 200);
    
    GtkWidget *purpose = gtk_entry_new();
    gtk_widget_set_size_request(purpose, 200, 50);
	gtk_entry_set_placeholder_text(GTK_ENTRY(purpose), "Purpose");//place holder
	gtk_entry_set_text(GTK_ENTRY(purpose), card.desc);
	
	GtkWidget *submit = gtk_button_new_with_label("Save changes");
	
	gtk_widget_set_name(purpose, "create-card-purpose");
	gtk_widget_set_name(submit, "create-card-submit");
	

	d->parent_dialog=dialog;
	d->entry=purpose;
	
	g_signal_connect(submit, "clicked", G_CALLBACK(edit_card_function), d);
	
	GtkWidget *grid = gtk_grid_new();
	gtk_grid_attach(GTK_GRID(grid), purpose, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), submit, 0, 2, 1, 1);
    gtk_container_add(GTK_CONTAINER(modal_area), grid);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    
    gtk_window_set_resizable(GTK_WINDOW(dialog), 0);
	gtk_widget_grab_focus(submit);
    gtk_widget_show_all(dialog);
}
void try_edit_card(GtkWidget *button, gpointer data)
{
	struct Send_Edit_Card_Data *d= (struct Send_Edit_Card_Data *)data;
	gtk_widget_destroy(d->parent_dialog);
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_window_set_title(GTK_WINDOW(dialog), "Edit Card");
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 700, 700);
    
    // Create a scrolled window
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);           
    gtk_box_pack_start(GTK_BOX(modal_area), scrolled_window, TRUE, TRUE, 0);
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(scrolled_window), box);

	FILE *file=fopen("Data/card.in", "r");
	GtkWidget *card[20];
	int card_size=0;
	char *line=malloc(200);
	while(fscanf(file, "%100s", line)==1)
	{
		struct Card c=create_card(line);
		if(c.user_id==d->id)
		{
			char *to_display=malloc(200);
			if(c.type==1)
				strcpy(to_display, "Credit Card #");
			if(c.type==2)
				strcpy(to_display, "Checking Card #");
			if(c.type==3)
				strcpy(to_display, "Savings Card #");
			char *number=malloc(200);
			transform_integer_to_chars(number, c.id, 0);
			strcat(to_display, number);
			strcat(to_display, "\nPurpose: ");
			strcat(to_display, c.desc);
			strcat(to_display, "\nBalance: ");
			transform_integer_to_chars(number, c.amount, 0);
			strcat(to_display, number);
			GtkWidget *button = gtk_button_new_with_label(to_display);
			gtk_widget_set_name(button, "selectcard-runapp");
			gtk_widget_set_hexpand(button, FALSE);
			gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
			gtk_widget_set_size_request(button, 600, 300);
			
			struct Send_Pick_Edit_Card_Data *pick=g_new(struct Send_Pick_Edit_Card_Data, 1);
			pick->card_id=c.id;
			pick->card_type=c.type;
			pick->parent_dialog=dialog;
			pick->data=*d;
			
			g_signal_connect(button, "clicked", G_CALLBACK(return_edit_card), pick);
			card[card_size++]=button;
		}
	}
	fclose(file);
	GtkWidget *text_select;
	if(card_size)
		text_select=gtk_label_new("Choose a card to edit");
	else
		text_select=gtk_label_new("You don't have a card.\nPlease Create one!");
	gtk_widget_set_name(text_select, "selecttext-runapp");
	gtk_box_pack_start(GTK_BOX(box), text_select, FALSE, FALSE, 0);
	for(int i=0; i<card_size; i++)
		gtk_box_pack_start(GTK_BOX(box), card[i], FALSE, FALSE, 0);
		
	GtkWidget *endline0=gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(box), endline0, FALSE, FALSE, 0);
	GtkWidget *endline1=gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(box), endline1, FALSE, FALSE, 0);
		
    //gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(dialog), 0);
    gtk_widget_show_all(dialog);
}
void delete_card_function(GtkWidget *button, gpointer data)
{
	struct Send_Pick_Edit_Card_Data *d=(struct Send_Pick_Edit_Card_Data *)data;
	char *text=malloc(200);
	int card_id=d->card_id;
	gtk_widget_destroy(d->parent_dialog);
	struct Card card=get_card_by_id(card_id);
	delete_card(card);
}
void cancel_delete_card_function(GtkWidget *button, gpointer data)
{
	struct Send_Pick_Edit_Card_Data *d=(struct Send_Pick_Edit_Card_Data *)data;
	gtk_widget_destroy(d->parent_dialog);
}
void return_delete_card(GtkWidget *button, gpointer data)
{
	struct Send_Pick_Edit_Card_Data *d=(struct Send_Pick_Edit_Card_Data *)data;
	int card_id=d->card_id;
	gtk_widget_destroy(d->parent_dialog);
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));

	struct Card card=get_card_by_id(card_id);
	char *type_of_card=malloc(200);
	if(card.type==1)
		strcpy(type_of_card, "Delete Credit Card");
	if(card.type==2)
		strcpy(type_of_card, "Delete Checking Card");
	if(card.type==3)
		strcpy(type_of_card, "Delete Savings Card");

    gtk_window_set_title(GTK_WINDOW(dialog), type_of_card);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 400, 200);
    
    GtkWidget *purpose = gtk_entry_new();
    gtk_widget_set_size_request(purpose, 200, 50);
	gtk_entry_set_placeholder_text(GTK_ENTRY(purpose), "Purpose");//place holder
	gtk_entry_set_text(GTK_ENTRY(purpose), card.desc);
	
	GtkWidget *delete_card = gtk_button_new_with_label("Delete Card");
	GtkWidget *cancel_card = gtk_button_new_with_label("Cancel Card");
	
	gtk_widget_set_name(delete_card, "create-card-submit");
	gtk_widget_set_name(cancel_card, "create-card-submit-red");
	

	d->parent_dialog=dialog;
	d->entry=purpose;
	
	g_signal_connect(delete_card, "clicked", G_CALLBACK(delete_card_function), d);
	g_signal_connect(cancel_card, "clicked", G_CALLBACK(cancel_delete_card_function), d);
	
	GtkWidget *grid = gtk_grid_new();
	gtk_grid_attach(GTK_GRID(grid), delete_card, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), cancel_card, 0, 2, 1, 1);
    gtk_container_add(GTK_CONTAINER(modal_area), grid);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    
    gtk_window_set_resizable(GTK_WINDOW(dialog), 0);
    gtk_widget_show_all(dialog);
}
void try_delete_card(GtkWidget *button, gpointer data)
{
	struct Send_Edit_Card_Data *d= (struct Send_Edit_Card_Data *)data;
	gtk_widget_destroy(d->parent_dialog);
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_window_set_title(GTK_WINDOW(dialog), "Delete Card");
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 700, 700);
    
    // Create a scrolled window
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);           
    gtk_box_pack_start(GTK_BOX(modal_area), scrolled_window, TRUE, TRUE, 0);
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(scrolled_window), box);

	FILE *file=fopen("Data/card.in", "r");
	GtkWidget *card[20];
	int card_size=0;
	char *line=malloc(200);
	while(fscanf(file, "%100s", line)==1)
	{
		struct Card c=create_card(line);
		if(c.user_id==d->id)
		{
			char *to_display=malloc(200);
			if(c.type==1)
				strcpy(to_display, "Credit Card #");
			if(c.type==2)
				strcpy(to_display, "Checking Card #");
			if(c.type==3)
				strcpy(to_display, "Savings Card #");
			char *number=malloc(200);
			transform_integer_to_chars(number, c.id, 0);
			strcat(to_display, number);
			strcat(to_display, "\nPurpose: ");
			strcat(to_display, c.desc);
			strcat(to_display, "\nBalance: ");
			transform_integer_to_chars(number, c.amount, 0);
			strcat(to_display, number);
			GtkWidget *button = gtk_button_new_with_label(to_display);
			gtk_widget_set_name(button, "selectcard-runapp");
			gtk_widget_set_hexpand(button, FALSE);
			gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
			gtk_widget_set_size_request(button, 600, 300);
			
			struct Send_Pick_Edit_Card_Data *pick=g_new(struct Send_Pick_Edit_Card_Data, 1);
			pick->card_id=c.id;
			pick->card_type=c.type;
			pick->parent_dialog=dialog;
			pick->data=*d;
			
			g_signal_connect(button, "clicked", G_CALLBACK(return_delete_card), pick);
			card[card_size++]=button;
		}
	}
	fclose(file);
	GtkWidget *text_select;
	if(card_size)
		text_select=gtk_label_new("Choose a card to delete");
	else
		text_select=gtk_label_new("You don't have a card.\nPlease Create one!");
	gtk_widget_set_name(text_select, "selecttext-runapp");
	gtk_box_pack_start(GTK_BOX(box), text_select, FALSE, FALSE, 0);
	for(int i=0; i<card_size; i++)
		gtk_box_pack_start(GTK_BOX(box), card[i], FALSE, FALSE, 0);
		
	GtkWidget *endline0=gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(box), endline0, FALSE, FALSE, 0);
	GtkWidget *endline1=gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(box), endline1, FALSE, FALSE, 0);
		
    //gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(dialog), 0);
    gtk_widget_show_all(dialog);
}
#endif
