#ifndef pre_process
#define pre_process
#include "domain.h"
const char *validate_prenume(const char*s)
{
	for(int i=0; i<strlen(s); i++)
		if(s[i]=='|')
			return "Invalid prenume!";
	if(strlen(s)<=3)
		return "Invalid prenume length! The prenume must have minimum 4 characters";
	if(strlen(s)>=21)
		return "Invalid prenume length! The prenume must have maximum 20 characters";
	return "OK";
}
const char *validate_nume(const char*s)
{
	for(int i=0; i<strlen(s); i++)
		if(s[i]=='|')
			return "Invalid nume!";
	if(strlen(s)<=3)
		return "Invalid nume length! The prenume must have minimum 4 characters";
	if(strlen(s)>=21)
		return "Invalid nume length! The prenume must have maximum 20 characters";
	return "OK";
}
const char *validate_phone(const char*s)
{
	for(int i=0; i<strlen(s); i++)
		if(s[i]=='|')
			return "Invalid phone number!";
	if(strlen(s)!=10)
		return "Invalid phone length!";
	if(s[0]!='0')
		return "Invalid phone number!";
	return "OK";
}
const char *validate_email(const char*s)
{
	for(int i=0; i<strlen(s); i++)
		if(s[i]=='|')
			return "Invalid email!";
	int arond=-1, punct=-1;
	for(int i=0; i<strlen(s); i++)
	{
		if(s[i]=='@')
			arond=i;
		if(s[i]=='.')
			punct=i;
	}
	if(arond==-1)
		return "Invalid email";
	if(punct==-1)
		return "Invalid email";
		
	int pana_la_arond=0;
	for(int i=0; i<arond; i++)
		if(s[i]>='a' && s[i]<='z')
			pana_la_arond=1;
		else if(s[i]>='A' && s[i]<='Z')
			pana_la_arond=1;
	if(!pana_la_arond)
		return "Invalid email";
		
	int pana_la_punct=0;
	for(int i=arond+1; i<punct; i++)
		if(s[i]>='a' && s[i]<='z')
			pana_la_punct=1;
		else if(s[i]>='A' && s[i]<='Z')
			pana_la_punct=1;
	if(!pana_la_punct)
		return "Invalid email";
	
	int pana_la_sfarsit=0;
	for(int i=punct+1; i<strlen(s); i++)
		if(s[i]>='a' && s[i]<='z')
			pana_la_sfarsit=1;
		else if(s[i]>='A' && s[i]<='Z')
			pana_la_sfarsit=1;
	if(!pana_la_sfarsit)
		return "Invalid email";
	return "OK";
}
const char *validate_password(const char*s)
{
	for(int i=0; i<strlen(s); i++)
		if(s[i]=='|')
			return "Invalid password!";
	if(strlen(s)<=7)
		return "Invalid password length! The password must have minimum 8 characters";
	if(strlen(s)>=17)
		return "Invalid password length! The password must have maximum 16 characters";
	int mare=0;
	int mica=0;
	int special=0;
	for(int i=0; i<strlen(s); i++)
	{
		if(s[i]>='a' && s[i]<='z')
			mica=1;
		else if(s[i]>='A' && s[i]<='Z')
			mare=1;
		else special=1;
	}
	if(!mica)
		return "Unsafe password! You must use a combination of lowercase, uppercase and special characters";
	if(!mare)
		return "Unsafe password! You must use a combination of lowercase, uppercase and special characters";
	if(!special)
		return "Unsafe password! You must use a combination of lowercase, uppercase and special characters";
	return "OK";
}
int find_email_in_database(const char *email)
{
	FILE *file=fopen("Data/user.in", "r");
	char *line=malloc(200);
	while(fscanf(file, "%100s", line)==1)
	{
		struct User user=create_user(line);
		if(check_equ_string(user.email, email))
		{
			fclose(file);
			return 1;
		}
	}
	fclose(file);
	return 0;
}
int find_phone_in_database(const char *phone)
{
	FILE *file=fopen("Data/user.in", "r");
	char *line=malloc(200);
	while(fscanf(file, "%100s", line)==1)
	{
		struct User user=create_user(line);
		if(check_equ_string(user.phone, phone))
		{
			fclose(file);
			return 1;
		}
	}
	fclose(file);
	return 0;
}
#endif
