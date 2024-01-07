#ifndef change_pass
#define change_pass
void try_change_password(GtkWidget *button, gpointer data)
{
	struct Send_Change_Password_Data *d = (struct Send_Change_Password_Data *)data;
	char *old_password=malloc(200);
	strcpy(old_password, gtk_entry_get_text(GTK_ENTRY(d->old_password)));
	char *new_password=malloc(200);
	strcpy(new_password, gtk_entry_get_text(GTK_ENTRY(d->new_password)));
	
	gtk_entry_set_text(GTK_ENTRY(d->old_password), "");
	gtk_entry_set_text(GTK_ENTRY(d->new_password), "");
	int id=d->id;
	struct User user=get_user_by_id(id);
	if(!check_equ_string(user.password, old_password))
	{
		GtkWidget *dialog=gtk_dialog_new();
		GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
		gtk_window_set_title(GTK_WINDOW(dialog), "ERROR");
		gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
	   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
		gtk_widget_set_size_request(dialog, 400, 200);
		
		GtkWidget *grid = gtk_grid_new();
    	gtk_container_add(GTK_CONTAINER(modal_area), grid);
    	gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
		
		GtkWidget *error = gtk_label_new("Old password does not match");
		gtk_widget_set_name(error, "dialog-changepswd-runapp");
		
		gtk_grid_attach(GTK_GRID(grid), error, 0, 1, 1, 1);
		gtk_widget_show_all(dialog);
		return;
	}
	const char *new_password_checked=validate_password(new_password);
	if(!check_ok_string(new_password_checked))
	{
		GtkWidget *dialog=gtk_dialog_new();
		GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
		gtk_window_set_title(GTK_WINDOW(dialog), "ERROR");
		gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
	   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
		gtk_widget_set_size_request(dialog, 400, 200);
		
		GtkWidget *grid = gtk_grid_new();
    	gtk_container_add(GTK_CONTAINER(modal_area), grid);
    	gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
		
		GtkWidget *error = gtk_label_new(new_password_checked);
		gtk_widget_set_name(error, "dialog-changepswd-runapp");
		
		gtk_grid_attach(GTK_GRID(grid), error, 0, 1, 1, 1);
		gtk_widget_show_all(dialog);
		return;
	}
	if(check_equ_string(old_password, new_password))
	{
		GtkWidget *dialog=gtk_dialog_new();
		GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
		gtk_window_set_title(GTK_WINDOW(dialog), "ERROR");
		gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
	   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
		gtk_widget_set_size_request(dialog, 400, 200);
		
		GtkWidget *grid = gtk_grid_new();
    	gtk_container_add(GTK_CONTAINER(modal_area), grid);
    	gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
		
		GtkWidget *error = gtk_label_new("Password are the same!");
		gtk_widget_set_name(error, "dialog-changepswd-runapp");
		
		gtk_grid_attach(GTK_GRID(grid), error, 0, 1, 1, 1);
		gtk_widget_show_all(dialog);
		return;
	}
	GtkWidget *dialog=gtk_dialog_new();
	GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	gtk_window_set_title(GTK_WINDOW(dialog), "SUCCES!");
	gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
	gtk_widget_set_size_request(dialog, 400, 200);
	
	GtkWidget *grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(modal_area), grid);
	gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
	
	GtkWidget *error = gtk_label_new("The password was succesfully changed!");
	gtk_widget_set_name(error, "dialog-changepswd-runapp");
	
	gtk_grid_attach(GTK_GRID(grid), error, 0, 1, 1, 1);
	gtk_widget_show_all(dialog);
	strcpy(user.password, new_password);
	change_user(user);
	return;
}
void change_password_function(GtkWidget *button, gpointer id)
{
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    gtk_window_set_title(GTK_WINDOW(dialog), "Change password");
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 600, 400);
	
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(modal_area), grid);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    
    GtkWidget *endline0 = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), endline0, 0, 0, 1, 1);
    
    GtkWidget *old_password=gtk_entry_new();
    gtk_widget_set_size_request(old_password, 250, 40);
	gtk_entry_set_placeholder_text(GTK_ENTRY(old_password), "Old Password");//place holder
	gtk_widget_set_name(old_password, "password-runapp");
	gtk_entry_set_visibility(GTK_ENTRY(old_password), FALSE); // Initially hide the password
	
	GtkWidget *new_password=gtk_entry_new();
	gtk_widget_set_size_request(new_password, 250, 40);
	gtk_entry_set_placeholder_text(GTK_ENTRY(new_password), "New Password");//place holder
	gtk_widget_set_name(new_password, "password-runapp");
	gtk_entry_set_visibility(GTK_ENTRY(new_password), FALSE); // Initially hide the password
    
    gtk_grid_attach(GTK_GRID(grid), old_password, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), new_password, 0, 3, 1, 1);
    GtkWidget *button_submit=gtk_button_new_with_label("Change password");
    gtk_widget_set_size_request(button_submit, 250, 80);
    gtk_widget_set_name(button_submit, "pswd-confirm-runapp");
    gtk_grid_attach(GTK_GRID(grid), button_submit, 0, 4, 1, 1);
    
    struct Send_Change_Password_Data *d=g_new(struct Send_Change_Password_Data, 1);
    d->old_password=old_password;
    d->new_password=new_password;
    d->id=GPOINTER_TO_INT(id);
   	g_signal_connect(button_submit, "clicked", G_CALLBACK(try_change_password), d);
    
    gtk_window_set_resizable(GTK_WINDOW(dialog), 0);
	gtk_widget_grab_focus(button_submit);
    gtk_widget_show_all(dialog);
}
#endif
