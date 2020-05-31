#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char s1[20];
	char s2[20];

	printf("Enter your first sentence (at max 20 characters)\n");
	scanf("%[^\n]s", s1); // %[^n]s will take the whole line and accept white space
	printf("s1: %s \n", s1);

	printf("Enter search query\n");
	scanf("%s", s2);
	printf("s2: %s \n", s2);
	char *pch = strstr(s1, s2);

	if(pch) {
	printf("FOUND\n");
	}
	else {
	printf("NOT FOUND\n");
	}
return 0;
}
