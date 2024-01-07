#ifndef management
#define management
void account_management_function(GtkWidget *button, gpointer id_user)
{
	int id=GPOINTER_TO_INT(id_user);
	GtkWidget *dialog=gtk_dialog_new();
    GtkWidget *modal_area=gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    gtk_window_set_title(GTK_WINDOW(dialog), "Account Management");
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));//aduce modal pe planul aplicatiei
   	gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);//pe plan principal
    gtk_widget_set_size_request(dialog, 1000, 500);
    
    GtkWidget *create_credit_card = gtk_button_new_with_label("Create credit card");
    gtk_widget_set_name(create_credit_card, "acm-button-runapp1");
    gtk_widget_set_size_request(create_credit_card, 300, 100);
    
    GtkWidget *create_checking_card = gtk_button_new_with_label("Create checking card");
    gtk_widget_set_name(create_checking_card, "acm-button-runapp1");
    gtk_widget_set_size_request(create_checking_card, 300, 100);
    
    GtkWidget *create_savings_card = gtk_button_new_with_label("Create savings card");
    gtk_widget_set_name(create_savings_card, "acm-button-runapp1");
    gtk_widget_set_size_request(create_savings_card, 300, 100);
    
    GtkWidget *edit_card = gtk_button_new_with_label("Edit card");
    gtk_widget_set_name(edit_card, "acm-button-runapp3");
    gtk_widget_set_size_request(edit_card, 300, 100);
    
    GtkWidget *delete_card = gtk_button_new_with_label("Delete card");
    gtk_widget_set_name(delete_card, "acm-button-runapp3");
    gtk_widget_set_size_request(delete_card, 300, 100);
    
    GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(box1), 5);
    gtk_widget_set_halign(box1, GTK_ALIGN_CENTER);
    
    GtkWidget *box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(box2), 5);
    gtk_widget_set_halign(box2, GTK_ALIGN_CENTER);
    
    gtk_box_pack_start(GTK_BOX(box1), create_credit_card, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box1), create_checking_card, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box1), create_savings_card, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box2), edit_card, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box2), delete_card, FALSE, FALSE, 0);
    
    struct Send_Create_Card_Data *d1=g_new(struct Send_Create_Card_Data, 1);
    struct Send_Create_Card_Data *d2=g_new(struct Send_Create_Card_Data, 1);
    struct Send_Create_Card_Data *d3=g_new(struct Send_Create_Card_Data, 1);
    d1->id=id;
    d1->type=1;
    d1->parent_dialog=dialog;
    d2->id=id;
    d2->type=2;
    d2->parent_dialog=dialog;
    d3->id=id;
    d3->type=3;
    d3->parent_dialog=dialog;
    g_signal_connect(create_credit_card, "clicked", G_CALLBACK(try_create_card), d1);
    g_signal_connect(create_checking_card, "clicked", G_CALLBACK(try_create_card), d2);
    g_signal_connect(create_savings_card, "clicked", G_CALLBACK(try_create_card), d3);
    
    struct Send_Edit_Card_Data *d4=g_new(struct Send_Edit_Card_Data, 1);
    d4->id=id;
    d4->parent_dialog=dialog;
    g_signal_connect(edit_card, "clicked", G_CALLBACK(try_edit_card), d4);
    
    struct Send_Delete_Card_Data *d5=g_new(struct Send_Delete_Card_Data, 1);
    d5->id=id;
    d5->parent_dialog=dialog;
    g_signal_connect(delete_card, "clicked", G_CALLBACK(try_delete_card), d5);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(modal_area), grid);
    gtk_grid_attach(GTK_GRID(grid), box1, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), box2, 0, 3, 1, 1);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(dialog), 0);
    gtk_widget_show_all(dialog);
}
#endif
