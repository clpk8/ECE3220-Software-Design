#include<stdio.h>
#include<string.h>
#include<malloc.h>
int main(void)
{
	char *s, *dyn_s;
	int ln;
	//s = (char*)malloc(sizeof(char*));
	printf("Enter the input string\n");
	scanf("%s",s);
	ln = strlen(s);
	dyn_s = (char*)malloc(ln+1);
	strncpy(dyn_s,s,ln);
	dyn_s[ln]='\0';
	printf("%s",dyn_s);
	free(dyn_s);
	//free(s);
	return 0;
}

