void display_welcome(GtkWidget *app_grid, GtkWidget *display_select_card_label, struct User user)
{
	char *to_display_welcome=malloc(200);
	strcpy(to_display_welcome, "Welcome, ");
	strcat(to_display_welcome, user.nume);
	strcat(to_display_welcome, " ");
	strcat(to_display_welcome, user.prenume);
	strcat(to_display_welcome, "!");
	GtkWidget *welcome_label=gtk_label_new(to_display_welcome);
	gtk_widget_set_name(welcome_label, "welcome-runapp");
	gtk_widget_set_name(display_select_card_label, "welcome-runapp");
	gtk_grid_attach(GTK_GRID(app_grid), welcome_label, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(app_grid), display_select_card_label, 0, 2, 1, 1);
}
void logout_function(GtkWidget *button, gpointer app_grid)
{
	current_login_display=1;
	gtk_container_remove(GTK_CONTAINER(window), app_grid);
	init_grid_login(window);
}
void check_balance_function(GtkWidget *button, int *cardid)
{
	int card_id=*cardid;
	if(card_id==0)
		return;
	struct Card card=get_card_by_id(card_id);
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_window_set_title(GTK_WINDOW(dialog), "Show Transactions");
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 800, 400);
    gtk_window_set_resizable(GTK_WINDOW (dialog), 0);
    
    GtkWidget *grid = gtk_grid_new();
    char *number=malloc(200);
    transform_integer_to_chars(number, card.amount, 0);
   	char *text=malloc(200);
   	strcpy(text, "Your balance is:");
   	strcat(text, number);
    GtkWidget *label=gtk_label_new(text);
    gtk_widget_set_name(label, "selecttext-runapp");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);
    gtk_container_add(GTK_CONTAINER(modal_area), grid);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);

    gtk_widget_show_all(dialog);
}
