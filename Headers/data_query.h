#ifndef data_query
#define data_query
#include "algorithm.h"
int get_last_user_id()
{
	FILE *file=fopen("Data/user.in", "r");
	char *line=malloc(200);
	int id=0;
	while(fgets(line, 150, file) != NULL)
	{
		line[strlen(line)-1]='\0';
		struct User user=create_user(line);
		id=user.id;
	}
	fclose(file);
	return id;
}
int get_last_card_id()
{
	FILE *file=fopen("Data/card.in", "r");
	char *line=malloc(200);
	int id=0;
	while(fgets(line, 150, file) != NULL)
	{
		line[strlen(line)-1]='\0';
		struct Card card=create_card(line);
		id=card.id;
	}
	fclose(file);
	return id;
}
int get_last_transaction_id()
{
	FILE *file=fopen("Data/transaction.in", "r");
	char *line=malloc(200);
	int id=0;
	while (fgets(line, 150, file) != NULL) {
		line[strlen(line)-1]='\0';
		struct Transaction transaction=create_transaction(line);
		id=transaction.id;
	}
	fclose(file);
	return id;
}
int get_count_transaction_id(int card_id)
{
	FILE *file=fopen("Data/transaction.in", "r");
	char *line=malloc(200);
	int cnt=0;
	while(fgets(line, 150, file) != NULL)
	{
		line[strlen(line)-1]='\0';
		struct Transaction transaction=create_transaction(line);
		if(transaction.card_id==card_id)
			cnt++;
		else if(transaction.type==4 && check_number_string(transaction.desc) && transform_chars_to_integer(transaction.desc)==card_id)
			cnt++;
	}
	fclose(file);
	return cnt;
}
void insert_user(int id, const char*prenume, const char*nume, const char*phone, const char*email, const char*password)
{
	FILE *file=fopen("Data/user.in", "a");
	fprintf(file, "%d|%s|%s|%s|%s|%s\n", id, prenume, nume, phone, email, password);
	fclose(file);
}
void insert_card(int id, int id_user, int type, int amount, const char*desc)
{
	FILE *file=fopen("Data/card.in", "a");
	fprintf(file, "%d|%d|%d|%d|%s\n", id, id_user, type, amount, desc);
	fclose(file);
}
void insert_transaction(int id, int id_card, int type, int amount, const char*time, const char*desc)
{
	FILE *file=fopen("Data/transaction.in", "a");
	fprintf(file, "%d|%d|%d|%d|%s|%s\n", id, id_card, type, amount, time, desc);
	fclose(file);
}
int get_id_by_phone_and_password(const char *phone, const char*password)
{
	FILE *file=fopen("Data/user.in", "r");
	char *line=malloc(200);
	while(fgets(line, 150, file) != NULL)
	{
		line[strlen(line)-1]='\0';
		struct User user=create_user(line);
		if(check_equ_string(phone, user.phone) && check_equ_string(password, user.password))
		{
			fclose(file);
			return user.id;
		}
	}
	fclose(file);
	return -1;
}
void change_user(struct User current_user)
{
	FILE *file=fopen("Data/user.in", "r");
	char *line=malloc(200);
	struct User user[2000];
	int user_size=0;
	while(fgets(line, 150, file) != NULL)
	{
		user_size++;
		line[strlen(line)-1]='\0';
		user[user_size]=create_user(line);
		if(user[user_size].id==current_user.id)
			user[user_size]=current_user;
	}
	fclose(file);
	file=fopen("Data/user.in", "w");
	for(int i=1; i<=user_size; i++)
		fprintf(file, "%d|%s|%s|%s|%s|%s\n", user[i].id, user[i].prenume, user[i].nume, user[i].phone, user[i].email, user[i].password);
	fclose(file);
}
void change_card(struct Card current_card)
{
	FILE *file=fopen("Data/card.in", "r");
	char *line=malloc(200);
	struct Card card[2000];
	int card_size=0;
	while(fgets(line, 150, file) != NULL)
	{
		card_size++;
		line[strlen(line)-1]='\0';
		card[card_size]=create_card(line);
		if(card[card_size].id==current_card.id)
			card[card_size]=current_card;
	}
	fclose(file);
	file=fopen("Data/card.in", "w");
	for(int i=1; i<=card_size; i++)
		fprintf(file, "%d|%d|%d|%d|%s\n", card[i].id, card[i].user_id, card[i].type, card[i].amount, card[i].desc);
	fclose(file);
}
void delete_card(struct Card current_card)
{
	FILE *file=fopen("Data/card.in", "r");
	char *line=malloc(200);
	struct Card card[2000];
	int card_size=0;
	while(fgets(line, 150, file) != NULL)
	{
		line[strlen(line)-1]='\0';
		struct Card toadd_card=create_card(line);
		if(toadd_card.id!=current_card.id)
		{
			card_size++;
			card[card_size]=toadd_card;
		}
	}
	fclose(file);
	file=fopen("Data/card.in", "w");
	for(int i=1; i<=card_size; i++)
		fprintf(file, "%d|%d|%d|%d|%s\n", card[i].id, card[i].user_id, card[i].type, card[i].amount, card[i].desc);
	fclose(file);
}
struct User get_user_by_id(int id)
{
	FILE *file=fopen("Data/user.in", "r");
	char *line=malloc(200);
	while(fgets(line, 150, file) != NULL)
	{
		line[strlen(line)-1]='\0';
		struct User user=create_user(line);
		if(user.id==id)
		{
			fclose(file);
			return user;
		}
	}
	struct User user;
	user.id=-1;
	fclose(file);
	return user;
}
struct Card get_card_by_id(int id)
{
	FILE *file=fopen("Data/card.in", "r");
	char *line=malloc(200);
	while(fgets(line, 150, file) != NULL)
	{
		line[strlen(line)-1]='\0';
		struct Card card=create_card(line);
		if(card.id==id)
		{
			fclose(file);
			return card;
		}
	}
	struct Card card;
	card.id=-1;
	fclose(file);
	return card;
}
struct Transaction get_transaction_by_id(int id)
{
	FILE *file=fopen("Data/transaction.in", "r");
	char *line=malloc(200);
	while(fgets(line, 150, file) != NULL)
	{
		line[strlen(line)-1]='\0';
		struct Transaction transaction=create_transaction(line);
		if(transaction.id==id)
		{
			fclose(file);
			return transaction;
		}
	}
	struct Transaction transaction;
	transaction.id=-1;
	fclose(file);
	return transaction;
}
#endif
