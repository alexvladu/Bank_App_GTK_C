#ifndef algorithm
#define algorithm
#include <string.h>
int check_number(char ch)
{
	return ch>='0' && ch<='9';
}
int transform_chars_to_integer(const char *amount_text)
{
	if(!strlen(amount_text))
		return -1;
	for(int i=0; i<strlen(amount_text); i++)
		if(!check_number(amount_text[i]))
			return -1;
	long long nr=0;
	for(int i=0; i<strlen(amount_text); i++)
		nr*=10, nr+=amount_text[i]-'0';
	return nr;
}
int transform_integer_to_chars(char *string, int number, int poz)
{
	if(!number && poz==0)
	{
		string[0]='0';
		string[1]='\0';
		return 1;
	}
	if(!number)
	{
		string[poz]='\0';
		return poz;
	}
	int len=transform_integer_to_chars(string, number/10, poz+1);
	string[len-poz-1]=number%10+'0';
	return len;
}
int check_equ_string(const char *string1, const char *string2)
{
	if(strlen(string1)!=strlen(string2))
		return 0;
	for(int i=0; i<strlen(string1); i++)
		if(string1[i]!=string2[i])
			return 0;
	return 1;
}
int check_ok_string(const char *string)
{
	if(strlen(string)!=2)
		return 0;
	if(string[0]!='O')
		return 0;
	if(string[1]!='K')
		return 0;
	return 1;
}
int check_number_string(const char*string)
{
	for(int i=0; i<strlen(string); i++)
		if(!check_number(string[i]))
			return 0;
	return 1;
}
char *display_pages_count(int page, int nr)
{
    char *string=malloc(50);
    strcpy(string, "Page ");
    char *string_pages=malloc(50);
    transform_integer_to_chars(string_pages, page, 0);
    strcat(string, string_pages);
    strcat(string, "/");
    if(nr%5==0)
    	nr/=5;
    else nr=nr/5+1;
    char *string_pages_total=malloc(50);
    transform_integer_to_chars(string_pages_total, nr, 0);
    strcat(string, string_pages_total);
    strcat(string, "  ");
    return string;
}
#endif
