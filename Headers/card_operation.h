#ifndef operations
#define operations
void display_dialog(GtkWidget *parent_dialog, const char *title, const char *text)
{
	gtk_widget_destroy(parent_dialog);
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_window_set_title(GTK_WINDOW(dialog), title);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 500, 250);
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(modal_area), grid);
    GtkWidget *label=gtk_label_new(text);
    gtk_widget_set_name(label, "selecttext-runapp");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);
    
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(dialog), 0);
    gtk_widget_show_all(dialog);
}
char *get_current_time()
{
	time_t currentTime;
	struct tm *localTime;

	// Get the current time
	currentTime = time(NULL);

	// Convert the current time to the local time
	localTime = localtime(&currentTime);

	// Extract date components
	int day = localTime->tm_mday;
	int month = localTime->tm_mon + 1;  // Month starts from 0
	int year = localTime->tm_year + 1900;  // Years since 1900
	int hour = localTime->tm_hour;
	int minute = localTime->tm_min;
	
	char *timp=malloc(200);
	sprintf(timp, "%02d/%02d/%04d.%02d:%02d", day, month, year, hour, minute);
	return timp;
}
void try_deposit(GtkWidget *button, gpointer data)
{
	struct Send_Deposit_Data *d= (struct Send_Deposit_Data *)data;
	char *text=malloc(200);
	strcpy(text, gtk_entry_get_text(GTK_ENTRY(d->entry)));
	if(strlen(text)==0)
		display_dialog(d->dialog, "Deposit error", "Invalid amount");
	else if(!check_number_string(text))
		display_dialog(d->dialog, "Deposit error", "Invalid type of amount");
	else{
		char *succes_text=malloc(200);
		strcpy(succes_text, "You deposited ");
		strcat(succes_text, text);
		strcat(succes_text, " in\n");
		struct Card card=get_card_by_id(*d->data.card_id);
		if(card.type==1)
			strcat(succes_text, "Credit Card #");
		if(card.type==2)
			strcat(succes_text, "Checking Card #");
		if(card.type==3)
			strcat(succes_text, "Savings Card #");
		char *number=malloc(200);
		transform_integer_to_chars(number, card.id, 0);
		strcat(succes_text, number);
		card.amount+=transform_chars_to_integer(text);
		change_card(card);
		insert_transaction(get_last_transaction_id()+1, card.id, 1, transform_chars_to_integer(text), get_current_time(), "None");
		
		display_dialog(d->dialog, "Deposit succes", succes_text);
	}
}
void deposit_function(GtkWidget *button, gpointer data)
{
	struct Send_Operation_Data *d= (struct Send_Operation_Data *)data;
	if(*d->card_id==0)
		return;
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_window_set_title(GTK_WINDOW(dialog), "Deposit");
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 400, 250);
    
    GtkWidget *entry_deposit=gtk_entry_new();
    GtkWidget *submit_button=gtk_button_new_with_label("Deposit");
    
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(modal_area), grid);
    gtk_grid_attach(GTK_GRID(grid), entry_deposit, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), submit_button, 0, 2, 1, 1);

	gtk_widget_set_size_request(entry_deposit, 250, 40);
	gtk_widget_set_size_request(submit_button, 250, 80);
	
	gtk_entry_set_placeholder_text(GTK_ENTRY(entry_deposit), "Sum of money");//place holder
	gtk_widget_set_name(entry_deposit, "deposit-value");
	gtk_widget_set_name(submit_button, "deposit-submit");
	
	//de trimis: id_card, id_user, entry, dialog
	struct Send_Deposit_Data *d1=g_new(struct Send_Deposit_Data, 1);
	d1->data=*d;
	d1->entry=entry_deposit;
	d1->dialog=dialog;
	g_signal_connect(submit_button, "clicked", G_CALLBACK(try_deposit), d1);

    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(dialog), 0);
	gtk_widget_grab_focus(submit_button);
    gtk_widget_show_all(dialog);
}
void try_withdraw(GtkWidget *button, gpointer data)
{
	struct Send_Withdraw_Data *d= (struct Send_Withdraw_Data *)data;
	char *text=malloc(200);
	strcpy(text, gtk_entry_get_text(GTK_ENTRY(d->entry)));
	if(strlen(text)==0)
	{
		display_dialog(d->dialog, "Withdraw error", "Invalid amount");
		return;
	}
	if(!check_number_string(text))
	{
		display_dialog(d->dialog, "Withdraw error", "Invalid type of amount");
		return;
	}
	struct Card card=get_card_by_id(*d->data.card_id);
	if(card.amount<transform_chars_to_integer(text))
	{
		display_dialog(d->dialog, "Withdraw error", "Invalid balance");
		return;
	}
	char *succes_text=malloc(200);
	strcpy(succes_text, "You withdrew ");
	strcat(succes_text, text);
	strcat(succes_text, " from\n");
	if(card.type==1)
		strcat(succes_text, "Credit Card #");
	if(card.type==2)
		strcat(succes_text, "Checking Card #");
	if(card.type==3)
		strcat(succes_text, "Savings Card #");
	char *number=malloc(200);
	transform_integer_to_chars(number, card.id, 0);
	strcat(succes_text, number);
	card.amount-=transform_chars_to_integer(text);
	change_card(card);
	
	insert_transaction(get_last_transaction_id()+1, card.id, 2, transform_chars_to_integer(text), get_current_time(), "None");
	
	display_dialog(d->dialog, "Withdraw succes", succes_text);
}
void withdraw_function(GtkWidget *button, gpointer data)
{
	struct Send_Operation_Data *d= (struct Send_Operation_Data *)data;
	if(*d->card_id==0)
		return;
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_window_set_title(GTK_WINDOW(dialog), "Withdraw");
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 400, 250);
    
    GtkWidget *entry_withdraw=gtk_entry_new();
    GtkWidget *submit_button=gtk_button_new_with_label("Withdraw");
    
    gtk_widget_set_size_request(entry_withdraw, 250, 40);
	gtk_widget_set_size_request(submit_button, 250, 80);
    
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(modal_area), grid);
    gtk_grid_attach(GTK_GRID(grid), entry_withdraw, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), submit_button, 0, 2, 1, 1);

	gtk_entry_set_placeholder_text(GTK_ENTRY(entry_withdraw), "Sum of money");//place holder
	gtk_widget_set_name(entry_withdraw, "withdraw-value");
	gtk_widget_set_name(submit_button, "withdraw-submit");
	
	struct Send_Withdraw_Data *d1=g_new(struct Send_Withdraw_Data, 1);
	d1->data=*d;
	d1->entry=entry_withdraw;
	d1->dialog=dialog;
	g_signal_connect(submit_button, "clicked", G_CALLBACK(try_withdraw), d1);

    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(dialog), 0);
	gtk_widget_grab_focus(submit_button);
    gtk_widget_show_all(dialog);
}
void try_pay(GtkWidget *button, gpointer data)
{
	struct Send_Pay_Data *d= (struct Send_Pay_Data *)data;
	char *text=malloc(200);
	strcpy(text, gtk_entry_get_text(GTK_ENTRY(d->entry)));
	char *details=malloc(200);
	strcpy(details, gtk_entry_get_text(GTK_ENTRY(d->entry_details)));
	if(strlen(text)==0)
	{
		display_dialog(d->dialog, "Pay error", "Invalid amount");
		return;
	}
	if(!check_number_string(text))
	{
		display_dialog(d->dialog, "Pay error", "Invalid type of amount");
		return;
	}
	struct Card card=get_card_by_id(*d->data.card_id);
	if(card.amount<transform_chars_to_integer(text))
	{
		display_dialog(d->dialog, "Pay error", "Invalid balance");
		return;
	}
	char *succes_text=malloc(200);
	strcpy(succes_text, "You payed ");
	strcat(succes_text, text);
	strcat(succes_text, " from\n");
	if(card.type==1)
		strcat(succes_text, "Credit Card #");
	if(card.type==2)
		strcat(succes_text, "Checking Card #");
	if(card.type==3)
		strcat(succes_text, "Savings Card #");
	char *number=malloc(200);
	transform_integer_to_chars(number, card.id, 0);
	strcat(succes_text, number);
	card.amount-=transform_chars_to_integer(text);
	change_card(card);
	
	insert_transaction(get_last_transaction_id()+1, card.id, 3, transform_chars_to_integer(text), get_current_time(), details);
	
	display_dialog(d->dialog, "Pay succes", succes_text);
}
void pay_function(GtkWidget *button, gpointer data)
{
	struct Send_Operation_Data *d= (struct Send_Operation_Data *)data;
	if(*d->card_id==0)
		return;
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_window_set_title(GTK_WINDOW(dialog), "Payment");
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 400, 300);
    
    GtkWidget *entry_pay=gtk_entry_new();
    GtkWidget *entry_pay_detail=gtk_entry_new();
    GtkWidget *submit_button=gtk_button_new_with_label("Pay");
    
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(modal_area), grid);
    
    gtk_widget_set_size_request(entry_pay, 250, 40);
	gtk_widget_set_size_request(entry_pay_detail, 250, 40);
	gtk_widget_set_size_request(submit_button, 250, 80);
    
    gtk_grid_attach(GTK_GRID(grid), entry_pay, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_pay_detail, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), submit_button, 0, 3, 1, 1);

	gtk_entry_set_placeholder_text(GTK_ENTRY(entry_pay), "Sum of money");//place holder
	gtk_entry_set_placeholder_text(GTK_ENTRY(entry_pay_detail), "Payment detail");//place holder
	gtk_widget_set_name(entry_pay, "pay-value");
	gtk_widget_set_name(entry_pay_detail, "pay-value");
	gtk_widget_set_name(submit_button, "pay-submit");

	struct Send_Pay_Data *d1=g_new(struct Send_Pay_Data, 1);
	d1->data=*d;
	d1->entry=entry_pay;
	d1->entry_details=entry_pay_detail;
	d1->dialog=dialog;
	g_signal_connect(submit_button, "clicked", G_CALLBACK(try_pay), d1);

    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(dialog), 0);
	gtk_widget_grab_focus(submit_button);
    gtk_widget_show_all(dialog);
}
void try_transfer(GtkWidget *button, gpointer data)
{
	struct Send_Transfer_Data *d= (struct Send_Transfer_Data *)data;
	char *text=malloc(200);
	strcpy(text, gtk_entry_get_text(GTK_ENTRY(d->entry)));
	char *card_no=malloc(200);
	strcpy(card_no, gtk_entry_get_text(GTK_ENTRY(d->entry_transfer)));
	if(strlen(text)==0)
	{
		display_dialog(d->dialog, "Transfer error", "Invalid amount");
		return;
	}
	if(strlen(card_no)==0)
	{
		display_dialog(d->dialog, "Transfer error", "Invalid receiver");
		return;
	}
	if(!check_number_string(text))
	{
		display_dialog(d->dialog, "Transfer error", "Invalid type of amount");
		return;
	}
	if(!check_number_string(card_no))
	{
		display_dialog(d->dialog, "Transfer error", "Invalid receiver");
		return;
	}
	struct Card card=get_card_by_id(*d->data.card_id);
	struct Card receiver=get_card_by_id(transform_chars_to_integer(card_no));
	if(receiver.id==-1)
	{
		display_dialog(d->dialog, "Transfer error", "Invalid Receiver Card");
		return;
	}
	if(card.id==receiver.id)
	{
		display_dialog(d->dialog, "Transfer error", "You can't transfer to the same card");
		return;
	}
	if(card.amount<transform_chars_to_integer(text))
	{
		display_dialog(d->dialog, "Transfer error", "Invalid balance");
		return;
	}
	char *succes_text=malloc(200);
	strcpy(succes_text, "You transfered ");
	strcat(succes_text, text);
	strcat(succes_text, " from \n");
	if(card.type==1)
		strcat(succes_text, "Credit Card #");
	if(card.type==2)
		strcat(succes_text, "Checking Card #");
	if(card.type==3)
		strcat(succes_text, "Savings Card #");
	char *number=malloc(200);
	transform_integer_to_chars(number, card.id, 0);
	strcat(succes_text, number);
	if(card.type==1)
		strcat(succes_text, " to\nCredit Card #");
	if(card.type==2)
		strcat(succes_text, " to\nChecking Card #");
	if(card.type==3)
		strcat(succes_text, " to\nSavings Card #");
	transform_integer_to_chars(number, receiver.id, 0);
	strcat(succes_text, number);
	card.amount-=transform_chars_to_integer(text);
	change_card(card);
	receiver.amount+=transform_chars_to_integer(text);
	change_card(receiver);
	
	insert_transaction(get_last_transaction_id()+1, card.id, 4, transform_chars_to_integer(text), get_current_time(), card_no);
	
	display_dialog(d->dialog, "Transfer succes", succes_text);
}
void transfer_function(GtkWidget *button, gpointer data)
{
	struct Send_Operation_Data *d= (struct Send_Operation_Data *)data;
	if(*d->card_id==0)
		return;
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_window_set_title(GTK_WINDOW(dialog), "Transfer");
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 400, 300);
    
    GtkWidget *entry_transfer=gtk_entry_new();
    GtkWidget *entry_transfer_id=gtk_entry_new();
    GtkWidget *submit_button=gtk_button_new_with_label("Transfer");
    
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(modal_area), grid);
    gtk_grid_attach(GTK_GRID(grid), entry_transfer, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_transfer_id, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), submit_button, 0, 3, 1, 1);

	gtk_widget_set_size_request(entry_transfer, 250, 40);
	gtk_widget_set_size_request(entry_transfer_id, 250, 40);
	gtk_widget_set_size_request(submit_button, 250, 80);
	
	gtk_entry_set_placeholder_text(GTK_ENTRY(entry_transfer), "Sum of money");//place holder
	gtk_entry_set_placeholder_text(GTK_ENTRY(entry_transfer_id), "Receiver Card #");//place holder
	
	gtk_widget_set_name(entry_transfer, "transfer-value");
	gtk_widget_set_name(entry_transfer_id, "transfer-value");
	gtk_widget_set_name(submit_button, "transfer-submit");

	struct Send_Transfer_Data *d1=g_new(struct Send_Transfer_Data, 1);
	d1->data=*d;
	d1->entry=entry_transfer;
	d1->entry_transfer=entry_transfer_id;
	d1->dialog=dialog;
	g_signal_connect(submit_button, "clicked", G_CALLBACK(try_transfer), d1);

    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(dialog), 0);
	gtk_widget_grab_focus(submit_button);
    gtk_widget_show_all(dialog);
}
#endif
