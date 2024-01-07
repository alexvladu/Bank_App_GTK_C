#ifndef domain
#define domain
#include "algorithm.h"
struct Send_Register_Data{
	GtkWidget *prenume;
	GtkWidget *nume;
	GtkWidget *phone;
	GtkWidget *email;
	GtkWidget *password;
};
struct Send_Select_Card_Data{
	int user_id;
	int *select_card_id;
	GtkWidget *display_select_card_label;
	GtkWidget *select_account;
	GtkWidget *show_transactions;
	GtkWidget *deposit;
	GtkWidget *withdraw;
	GtkWidget *import_data;
	GtkWidget *export_data;
	GtkWidget *pay;
	GtkWidget *transfer;
	GtkWidget *check_balance;
};
struct Send_Pick_Card_Data{
	int card_id;
	int card_type;
	struct Send_Select_Card_Data data;
	GtkWidget *dialog;
};
struct Send_Operation_Data{
	int *card_id;
	int user_id;
};
struct Send_Deposit_Data{
	struct Send_Operation_Data data;
	GtkWidget *entry;
	GtkWidget *dialog;
};
struct Send_Withdraw_Data{
	struct Send_Operation_Data data;
	GtkWidget *entry;
	GtkWidget *dialog;
};
struct Send_Pay_Data{
	struct Send_Operation_Data data;
	GtkWidget *entry;
	GtkWidget *entry_details;
	GtkWidget *dialog;
};
struct Send_Transfer_Data{
	struct Send_Operation_Data data;
	GtkWidget *entry;
	GtkWidget *entry_transfer;
	GtkWidget *dialog;
};
struct Send_Login_Data{
	GtkWidget *phone;
	GtkWidget *password;
};
struct Send_Change_Password_Data{
	GtkWidget *old_password;
	GtkWidget *new_password;
	int id;
};
struct Send_Create_Card_Data{
	GtkWidget *parent_dialog;
	GtkWidget *entry;
	int id;
	int type;
};
struct Send_Edit_Card_Data{
	GtkWidget *parent_dialog;
	int id;
};
struct Send_Pick_Edit_Card_Data{
	int card_id;
	int card_type;
	struct Send_Edit_Card_Data data;
	GtkWidget *parent_dialog;
	GtkWidget *entry;
};
struct Send_Delete_Card_Data{
	GtkWidget *parent_dialog;
	int id;
};
struct Send_Transaction_Data{
	int *pagina;
	int *card_id;
	GtkWidget *page_info;
	GtkWidget *tree_view;
	GtkListStore *list_store;
};
struct User{
	int id;
	char *prenume;
	char *nume;
	char *phone;
	char *email;
	char *password;
};
struct Card{
	int id;
	int user_id;
	int type;
	int amount;
	char *desc;
};
struct Transaction{
	int id;
	int card_id;
	int type;
	int amount;
	char *time;
	char *desc;
};

struct User create_user(char *line)
{
	struct User user;
	int ind=0;
	char *aux_id=malloc(32);
	int user_id_len=0;
	for(ind; line[ind]!='|'; ind++)
		aux_id[user_id_len++]=line[ind];
	aux_id[user_id_len]='\0';
	ind++;
	user.id=transform_chars_to_integer(aux_id);
	
	user.prenume=malloc(32);
	int user_prenume_len=0;
	for(ind; line[ind]!='|'; ind++)
		user.prenume[user_prenume_len++]=line[ind];
	user.prenume[user_prenume_len]='\0';
	ind++;

	user.nume=malloc(32);
	int user_nume_len=0;
	for(ind; line[ind]!='|'; ind++)
		user.nume[user_nume_len++]=line[ind];
	user.nume[user_nume_len]='\0';
	ind++;
	
	user.phone=malloc(25);
	int user_phone_len=0;
	for(ind; line[ind]!='|'; ind++)
		user.phone[user_phone_len++]=line[ind];
	user.phone[user_phone_len]='\0';
	ind++;
	
	user.email=malloc(32);
	int user_email_len=0;
	for(ind; line[ind]!='|'; ind++)
		user.email[user_email_len++]=line[ind];
	user.email[user_email_len]='\0';
	ind++;
	
	user.password=malloc(32);
	int user_password_len=0;
	for(ind; line[ind]; ind++)
		user.password[user_password_len++]=line[ind];
	user.password[user_password_len]='\0';
	return user;
};
struct Card create_card(char *line)
{
	struct Card card;
	int ind=0;
	char *aux_id=malloc(32);
	int card_id_len=0;
	for(ind; line[ind]!='|'; ind++)
		aux_id[card_id_len++]=line[ind];
	aux_id[card_id_len]='\0';
	ind++;
	card.id=transform_chars_to_integer(aux_id);
	
	char *user_id=malloc(32);
	int user_id_len=0;
	for(ind; line[ind]!='|'; ind++)
		user_id[user_id_len++]=line[ind];
	user_id[user_id_len]='\0';
	ind++;
	card.user_id=transform_chars_to_integer(user_id);
	
	char *type=malloc(32);
	int type_len=0;
	for(ind; line[ind]!='|'; ind++)
		type[type_len++]=line[ind];
	type[type_len]='\0';
	ind++;
	card.type=transform_chars_to_integer(type);
	
	char *amount=malloc(32);
	int amount_len=0;
	for(ind; line[ind]!='|'; ind++)
		amount[amount_len++]=line[ind];
	amount[amount_len]='\0';
	ind++;
	card.amount=transform_chars_to_integer(amount);
	
	card.desc=malloc(32);
	int desc_len=0;
	for(ind; line[ind]; ind++)
		card.desc[desc_len++]=line[ind];
	card.desc[desc_len]='\0';
	
	return card;
}
struct Transaction create_transaction(char *line){
	struct Transaction transaction;
	int ind=0;
	char *aux_id=malloc(32);
	int transaction_id_len=0;
	for(ind; line[ind]!='|'; ind++)
		aux_id[transaction_id_len++]=line[ind];
	aux_id[transaction_id_len]='\0';
	ind++;
	transaction.id=transform_chars_to_integer(aux_id);
	
	char *card_id=malloc(32);
	int card_id_len=0;
	for(ind; line[ind]!='|'; ind++)
		card_id[card_id_len++]=line[ind];
	card_id[card_id_len]='\0';
	ind++;
	transaction.card_id=transform_chars_to_integer(card_id);
	
	char *type=malloc(32);
	int type_len=0;
	for(ind; line[ind]!='|'; ind++)
		type[type_len++]=line[ind];
	type[type_len]='\0';
	ind++;
	transaction.type=transform_chars_to_integer(type);
	
	char *amount=malloc(32);
	int amount_len=0;
	for(ind; line[ind]!='|'; ind++)
		amount[amount_len++]=line[ind];
	amount[amount_len]='\0';
	ind++;
	transaction.amount=transform_chars_to_integer(amount);
	
	transaction.time=malloc(200);
	int transaction_len=0;
	for(ind; line[ind]!='|'; ind++)
		transaction.time[transaction_len++]=line[ind];
	transaction.time[transaction_len]='\0';
	ind++;
	
	transaction.desc=malloc(32);
	int desc_len=0;
	for(ind; line[ind]; ind++)
		transaction.desc[desc_len++]=line[ind];
	transaction.desc[desc_len]='\0';
	return transaction;
};
#endif
