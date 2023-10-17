#include<stdio.h>
#include<string.h>
int main()
{
	int i;
	char a[50];
	printf("Enter the plain text:");
	gets(a);
	printf("\nmonoalphabetic cipher:");
	for(i=0;i<strlen(a);i++)
	{printf("%c",a[i]+1);
	
}
}