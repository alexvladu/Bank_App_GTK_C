#ifndef auth
#define auth
void remove_current_grid(GtkWidget *button, gpointer window);
void try_to_register(GtkWidget *button, gpointer data)
{
	struct Send_Register_Data *d = (struct Send_Register_Data *)data;
	const gchar *prenume = gtk_entry_get_text(GTK_ENTRY(d->prenume));
	const gchar *nume = gtk_entry_get_text(GTK_ENTRY(d->nume));
	const gchar *phone = gtk_entry_get_text(GTK_ENTRY(d->phone));
	const gchar *email = gtk_entry_get_text(GTK_ENTRY(d->email));
	const gchar *password = gtk_entry_get_text(GTK_ENTRY(d->password));
	const gchar *prenume_checked=validate_prenume(prenume);
	const gchar *nume_checked=validate_nume(nume);
	const gchar *phone_checked=validate_phone(phone);
	const gchar *email_checked=validate_email(email);
	const gchar *password_checked=validate_password(password);
	if(check_ok_string(prenume_checked) && check_ok_string(nume_checked) && check_ok_string(phone_checked) && check_ok_string(email_checked) && check_ok_string(password_checked) && !find_email_in_database(email) && !find_phone_in_database(phone))
	{
		insert_user(get_last_user_id()+1, prenume, nume, phone, email, password);
		gtk_container_remove(GTK_CONTAINER(window), grid_register);
		run_aplication(get_last_user_id());
	}
	else
	{
		GtkWidget *dialog=gtk_dialog_new();
    	GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    	gtk_window_set_title(GTK_WINDOW(dialog), "Register Error");
    	gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   		gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    	gtk_widget_set_size_request(dialog, 1000, 450);
    	
    	GtkWidget *error_grid = gtk_grid_new();
    	gtk_grid_set_column_homogeneous(GTK_GRID(error_grid), TRUE); // Make columns equal width
    	gtk_container_add(GTK_CONTAINER(modal_area), error_grid);
    	if(!check_ok_string(prenume_checked)){
			GtkWidget *error = gtk_label_new(prenume_checked);
			gtk_grid_attach(GTK_GRID(error_grid), error, 0, 1, 1, 1);
			gtk_widget_set_halign(error, GTK_ALIGN_START);
			gtk_widget_set_name(error, "register-error");
    	}
    	if(!check_ok_string(nume_checked)){
    		GtkWidget *error = gtk_label_new(nume_checked);
			gtk_grid_attach(GTK_GRID(error_grid), error, 0, 2, 1, 1);
			gtk_widget_set_halign(error, GTK_ALIGN_START);
			gtk_widget_set_name(error, "register-error");
    	}
    	if(!check_ok_string(phone_checked)){
    		GtkWidget *error = gtk_label_new(phone_checked);
			gtk_grid_attach(GTK_GRID(error_grid), error, 0, 3, 1, 1);
			gtk_widget_set_halign(error, GTK_ALIGN_START);
			gtk_widget_set_name(error, "register-error");
    	}
    	if(!check_ok_string(email_checked)){
    		GtkWidget *error = gtk_label_new(email_checked);
			gtk_grid_attach(GTK_GRID(error_grid), error, 0, 4, 1, 1);
			gtk_widget_set_halign(error, GTK_ALIGN_START);
			gtk_widget_set_name(error, "register-error");
    	}
    	if(!check_ok_string(password_checked)){
    		GtkWidget *error = gtk_label_new(password_checked);
			gtk_grid_attach(GTK_GRID(error_grid), error, 0, 5, 1, 1);
			gtk_widget_set_halign(error, GTK_ALIGN_START);
			gtk_widget_set_name(error, "register-error");
		}
		if(find_email_in_database(email)){
			GtkWidget *error = gtk_label_new("Email is already in use!");
			gtk_grid_attach(GTK_GRID(error_grid), error, 0, 6, 1, 1);
			gtk_widget_set_halign(error, GTK_ALIGN_START);
			gtk_widget_set_name(error, "register-error");
		}
		if(find_phone_in_database(phone)){
			GtkWidget *error = gtk_label_new("Phone is already in use");
			gtk_grid_attach(GTK_GRID(error_grid), error, 0, 7, 1, 1);
			gtk_widget_set_halign(error, GTK_ALIGN_START);
			gtk_widget_set_name(error, "register-error");
		}
    	gtk_widget_show_all(dialog);
	}
}
void init_grid_register(GtkWidget *window)
{
	grid_register = gtk_grid_new();
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(box), 5);
	GtkWidget *Select_Login = gtk_button_new_with_label("Login");
	GtkWidget *Select_Register = gtk_button_new_with_label("Register");
	gtk_widget_set_size_request(Select_Login, 200, 60);
	gtk_widget_set_size_request(Select_Register, 200, 60);
	gtk_widget_set_name(Select_Register, "select-button");
	gtk_widget_set_name(Select_Login, "select-button");
	gtk_box_pack_start(GTK_BOX(box), Select_Login, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), Select_Register, TRUE, TRUE, 0);
    g_signal_connect(Select_Login, "clicked", G_CALLBACK(remove_current_grid), window);
    gtk_grid_attach(GTK_GRID(grid_register), box, 0, 0, 1, 1);
    
    GtkWidget *prenume_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(prenume_entry), "First Name");
    gtk_grid_attach(GTK_GRID(grid_register), prenume_entry, 0, 1, 1, 1);
    gtk_widget_set_name(prenume_entry, "login-register");
    
    GtkWidget *nume_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(nume_entry), "Last Name");
    gtk_grid_attach(GTK_GRID(grid_register), nume_entry, 0, 2, 1, 1);
    gtk_widget_set_name(nume_entry, "login-register");
    
    GtkWidget *phone_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(phone_entry), "Phone Number");
    gtk_grid_attach(GTK_GRID(grid_register), phone_entry, 0, 3, 1, 1);
    gtk_widget_set_name(phone_entry, "login-register");
    
    GtkWidget *email_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(email_entry), "Email");
    gtk_grid_attach(GTK_GRID(grid_register), email_entry, 0, 4, 1, 1);
    gtk_widget_set_name(email_entry, "login-register");
    
    GtkWidget *password_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Password");
    gtk_grid_attach(GTK_GRID(grid_register), password_entry, 0, 5, 1, 1);
    gtk_widget_set_name(password_entry, "login-register");
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    
	GtkWidget *Register = gtk_button_new_with_label("Create account");
	gtk_grid_attach(GTK_GRID(grid_register), Register, 0, 6, 1, 1);
	gtk_widget_set_size_request(Register, 250, 150);
    // Setarea identificatorului CSS pentru butonul de login
    gtk_widget_set_name(Register, "register-button");
    struct Send_Register_Data *data = g_new(struct Send_Register_Data, 1);
    data->prenume=prenume_entry;
    data->nume=nume_entry;
    data->phone=phone_entry;
    data->email=email_entry;
    data->password=password_entry;
    g_signal_connect(Register, "clicked", G_CALLBACK(try_to_register), data);
	gtk_widget_set_halign(grid_register, GTK_ALIGN_CENTER);
	gtk_container_add(GTK_CONTAINER(window), grid_register);
	gtk_widget_show_all(window);
}
void try_to_login(GtkWidget *button, gpointer data)
{
	struct Send_Login_Data *d = (struct Send_Login_Data *)data;
	const gchar *phone=gtk_entry_get_text(GTK_ENTRY(d->phone));
	const gchar *password=gtk_entry_get_text(GTK_ENTRY(d->password));
	int id=get_id_by_phone_and_password(phone, password);
	if(id>=0)
	{
		gtk_container_remove(GTK_CONTAINER(window), grid_login);
		run_aplication(id);
	}
}
void init_grid_login(GtkWidget *window)
{;
	grid_login = gtk_grid_new();
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(box), 5);
	GtkWidget *Select_Login = gtk_button_new_with_label("Login");
	GtkWidget *Select_Register = gtk_button_new_with_label("Register");
	gtk_widget_set_size_request(Select_Login, 200, 60);
	gtk_widget_set_size_request(Select_Register, 200, 60);
	gtk_widget_set_name(Select_Register, "select-button");
	gtk_widget_set_name(Select_Login, "select-button");
	gtk_box_pack_start(GTK_BOX(box), Select_Login, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), Select_Register, TRUE, TRUE, 0);
    g_signal_connect(Select_Register, "clicked", G_CALLBACK(remove_current_grid), window);
	gtk_grid_attach(GTK_GRID(grid_login), box, 0, 0, 1, 1);
    	
    GtkWidget *phone_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(phone_entry), "Phone Number");
    gtk_grid_attach(GTK_GRID(grid_login), phone_entry, 0, 1, 1, 1);
    gtk_widget_set_name(phone_entry, "login-register");
    
    GtkWidget *password_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Password");
    gtk_grid_attach(GTK_GRID(grid_login), password_entry, 0, 2, 1, 1);
    gtk_widget_set_name(password_entry, "login-register");
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    
	GtkWidget *Login = gtk_button_new_with_label("Log in");
	gtk_grid_attach(GTK_GRID(grid_login), Login, 0, 3, 1, 1);
	gtk_widget_set_size_request(Login, 250, 150);
    // Setarea identificatorului CSS pentru butonul de login
    gtk_widget_set_name(Login, "login-button");
    struct Send_Login_Data *data = g_new(struct Send_Login_Data, 1);
    data->phone=phone_entry;
    data->password=password_entry;
    g_signal_connect(Login, "clicked", G_CALLBACK(try_to_login), data);
	gtk_widget_set_halign(grid_login, GTK_ALIGN_CENTER);
	gtk_container_add(GTK_CONTAINER(window), grid_login);
	gtk_widget_show_all(window);
}
void remove_current_grid(GtkWidget *button, gpointer window) {
	current_login_display=(current_login_display+1)%2;
	if(current_login_display){
		gtk_container_remove(GTK_CONTAINER(window), grid_register);
		init_grid_login(window);
	}
	else{
		gtk_container_remove(GTK_CONTAINER(window), grid_login);
		init_grid_register(window);
	}
	gtk_widget_show_all(window);
}
#endif
