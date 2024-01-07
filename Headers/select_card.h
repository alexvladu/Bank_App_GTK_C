#ifndef select_card_file
#define select_card_file
void return_card(GtkWidget *button, gpointer data)
{
	struct Send_Pick_Card_Data *d= (struct Send_Pick_Card_Data *)data;
	char *text=malloc(200);
	strcpy(text, "You are using ");
	if(d->card_type==1)
		strcat(text, "Credit Card #");
	if(d->card_type==2)
		strcat(text, "Checking Card #");
	if(d->card_type==3)
		strcat(text, "Savings Card #");
	char *number=malloc(200);
	transform_integer_to_chars(number, d->card_id, 0);
	strcat(text, number);
	*d->data.select_card_id=d->card_id;
	gtk_label_set_text(GTK_LABEL(d->data.display_select_card_label), text);
	gtk_widget_queue_draw(GTK_WIDGET(d->data.display_select_card_label));
	
	gtk_widget_set_name(d->data.show_transactions, "select-runapp");
	gtk_widget_set_name(d->data.deposit, "deposit-runapp");
	gtk_widget_set_name(d->data.withdraw, "deposit-runapp");
	gtk_widget_set_name(d->data.pay, "payment-runapp");
	gtk_widget_set_name(d->data.import_data, "importdata-runapp");
	gtk_widget_set_name(d->data.export_data, "importdata-runapp");
	gtk_widget_set_name(d->data.transfer, "payment-runapp");
	gtk_widget_set_name(d->data.check_balance, "checkbalance-runapp");
	
	gtk_widget_destroy(GTK_WIDGET(d->dialog));
	
}
void select_card(GtkWidget *button, gpointer data)
{
	struct Send_Select_Card_Data *d= (struct Send_Select_Card_Data *)data;
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_window_set_title(GTK_WINDOW(dialog), "Account Management");
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
	while(fgets(line, 100, file) != NULL)
	{
		line[strlen(line)-1]='\0';
		struct Card c=create_card(line);
		if(c.user_id==d->user_id)
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
			
			struct Send_Pick_Card_Data *pick=g_new(struct Send_Pick_Card_Data, 1);
			pick->card_id=c.id;
			pick->card_type=c.type;
			pick->dialog=dialog;
			pick->data=*d;
			
			g_signal_connect(button, "clicked", G_CALLBACK(return_card), pick);
			card[card_size++]=button;
		}
	}
	fclose(file);
	GtkWidget *text_select;
	if(card_size)
		text_select=gtk_label_new("Choose a card");
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
