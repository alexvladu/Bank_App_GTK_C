enum {
    COLUMN_id,
    COLUMN_card_id,
    COLUMN_type,
    COLUMN_amount,
    COLUMN_time,
    COLUMN_desc,
    NUM_COLUMNS
};
void add_row(GtkListStore *list_store, gint id, gint card_id, const gchar*type, gint amount, const gchar*time, const gchar *desc) {
    GtkTreeIter iter;
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter, COLUMN_id, id, COLUMN_card_id, card_id, COLUMN_type, type, COLUMN_amount, amount, COLUMN_time, time, COLUMN_desc, desc, -1);
}
void remove_last_row(GtkWidget *tree_view) {
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(tree_view));

    // Get the number of children in the model
    gint n_children = gtk_tree_model_iter_n_children(model, NULL);

    if (n_children > 0) {
        // Get the iterator for the last row
        GtkTreeIter last_iter;
        gtk_tree_model_iter_nth_child(model, &last_iter, NULL, n_children - 1);

        // Remove the last row
        gtk_list_store_remove(GTK_LIST_STORE(model), &last_iter);
    }
}
char *get_column_text(int i)
{
	char *string=malloc(50);
	if(i==0)
   		strcpy(string, "Transaction Id");
    if(i==1)
    	strcpy(string, "Card Id");
    if(i==2)
    	strcpy(string, "Type");
    if(i==3)
    	strcpy(string, "Amount");
    if(i==4)
    	strcpy(string, "Time");
	if(i==5)
    	strcpy(string, "Description");
    return string;
}
void show_5_data_from_tabel(int page, int card_id, GtkListStore *list_store)
{
	FILE *file=fopen("Data/transaction.in", "r");
	char *line=malloc(200);
	int id=0;
	int card_item=0;
	int current_page=1;
	int dr=get_count_transaction_id(card_id)-5*(page-1);
	int st=dr-4;
	struct Transaction display_reversed[10];
	int display_reversed_size=0;
	int counter=0;
	while(fgets(line, 100, file) != NULL)
	{
		line[strlen(line)-1]='\0';
		struct Transaction transaction=create_transaction(line);
		if(transaction.card_id==card_id)
		{
			counter++;
			if(counter>=st && counter<=dr)
			{
				display_reversed_size++;
				if(transaction.type==4)
				{
					char *text=malloc(200);
					strcpy(text, "Transfer to Card #");
					strcat(text, transaction.desc);
					strcpy(transaction.desc, text);
				}
				display_reversed[display_reversed_size]=transaction;
			}
		}
		else if(transaction.type==4 && check_number_string(transaction.desc) && transform_chars_to_integer(transaction.desc)==card_id)
		{
			counter++;
			if(counter>=st && counter<=dr)
			{
				display_reversed_size++;
				if(transaction.type==4)
				{
					char *text=malloc(200);
					transform_integer_to_chars(transaction.desc, transaction.card_id, 0);
					strcpy(text, "Received from Card #");
					strcat(text, transaction.desc);
					strcpy(transaction.desc, text);
				}
				display_reversed[display_reversed_size]=transaction;
			}
		}
	}
	for(int i=display_reversed_size; i>=1; i--)
	{
		struct Transaction transaction=display_reversed[i];
		if(transaction.type==1)
			add_row(list_store, transaction.id, transaction.card_id, "Deposit", transaction.amount, transaction.time, transaction.desc);
		if(transaction.type==2)
			add_row(list_store, transaction.id, transaction.card_id, "Withdraw", transaction.amount, transaction.time, transaction.desc);
		if(transaction.type==3)
			add_row(list_store, transaction.id, transaction.card_id, "Pay", transaction.amount, transaction.time, transaction.desc);
		if(transaction.type==4)
			add_row(list_store, transaction.id, transaction.card_id, "Transfer", transaction.amount, transaction.time, transaction.desc);
	}
	fclose(file);
}
void go_page_left(GtkWidget *widget, gpointer *data)//card id, page, tree_view
{
	struct Send_Transaction_Data *d= (struct Send_Transaction_Data *)data;
	if(*d->pagina==1)
		return;
	(*d->pagina)--;
	for(int i=1; i<=5; i++)
		remove_last_row(d->tree_view);
	show_5_data_from_tabel(*d->pagina, *d->card_id, d->list_store);
	gtk_label_set_text(GTK_LABEL(d->page_info), display_pages_count(*d->pagina, get_count_transaction_id(*d->card_id)));
}
void go_page_right(GtkWidget *widget, gpointer *data)//card_id, page
{
	struct Send_Transaction_Data *d= (struct Send_Transaction_Data *)data;
	int nr=get_count_transaction_id(*d->card_id);
    if(nr%5==0)
    	nr/=5;
    else nr=nr/5+1;
	if(*d->pagina==nr)
		return;
	(*d->pagina)++;
	for(int i=1; i<=5; i++)
		remove_last_row(d->tree_view);
	show_5_data_from_tabel(*d->pagina, *d->card_id, d->list_store);
	gtk_label_set_text(GTK_LABEL(d->page_info), display_pages_count(*d->pagina, get_count_transaction_id(*d->card_id)));
}
void display_transactions(GtkWidget *button, gpointer data)
{
	struct Send_Transaction_Data *d = (struct Send_Transaction_Data *)data;
	if(*d->card_id==0)
		return;
	int nr=get_count_transaction_id(*d->card_id);
    if(nr%5==0)
    	nr/=5;
    else nr=nr/5+1;
    if(*d->pagina>nr)
    	*d->pagina=1;
    GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_window_set_title(GTK_WINDOW(dialog), "Show Transactions");
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 800, 400);
    gtk_window_set_resizable(GTK_WINDOW (dialog), 0);
    
	GtkWidget *grid = gtk_grid_new();
	GtkWidget *page_info=gtk_label_new(display_pages_count(*d->pagina, get_count_transaction_id(*d->card_id)));
	GtkListStore *list_store=gtk_list_store_new(NUM_COLUMNS, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);
	GtkWidget *tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(list_store));
    for (int i = 0; i < NUM_COLUMNS; i++) {
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes("", renderer, "text", i, NULL);
        gtk_tree_view_column_set_title(column, get_column_text(i));
        gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    }
    d->page_info=page_info;
    d->list_store=list_store;
    d->tree_view=tree_view;
	gtk_grid_attach(GTK_GRID(grid), tree_view, 1, 0, 1, 1);
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
	show_5_data_from_tabel(*d->pagina, *d->card_id, d->list_store);
    
    GtkWidget *grid1 = gtk_grid_new();

	GtkWidget *left_button = gtk_button_new();
    GtkWidget *left_icon = gtk_image_new_from_icon_name("go-previous", GTK_ICON_SIZE_BUTTON);  // Icon for 'go-previous'
    gtk_button_set_image(GTK_BUTTON(left_button), left_icon);
    g_signal_connect(left_button, "clicked", G_CALLBACK(go_page_left), d);
    
    GtkWidget *right_button = gtk_button_new();
    GtkWidget *right_icon = gtk_image_new_from_icon_name("go-next", GTK_ICON_SIZE_BUTTON);  // Icon for 'go-previous'
    g_signal_connect(right_button, "clicked", G_CALLBACK(go_page_right), d);
    gtk_button_set_image(GTK_BUTTON(right_button), right_icon);
    if(get_count_transaction_id(*d->card_id))
    {
		gtk_grid_attach(GTK_GRID(grid1), left_button, 1, 0, 1, 1);
		gtk_grid_attach(GTK_GRID(grid1), page_info, 2, 0, 1, 1);
		gtk_grid_attach(GTK_GRID(grid1), right_button, 3, 0, 1, 1);
		gtk_widget_set_halign(grid1, GTK_ALIGN_CENTER);
		gtk_box_pack_start(GTK_BOX(box), grid, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(box), grid1, TRUE, TRUE, 0);
		gtk_container_add(GTK_CONTAINER(modal_area), box);
    }
    else
    {
    	GtkWidget *label = gtk_label_new("There are no transactions");
    	gtk_widget_set_name(label, "selecttext-runapp");
    	gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);
    	gtk_container_add(GTK_CONTAINER(modal_area), box);
    }
    gtk_widget_show_all(dialog);
}
