#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main()
{
	int i;
	/*Tabela ASCII*/
	for (i = 32; i < 126; i++)
	{
		printf("[%i -> %c]\t", i, i);
	}

	printf("\n\n\n");

	char /*a, */ str[5];
	int b = 0;

	scanf("%s", str);

	/*scanf("%c", &a);
	a esta entre 48 e 57
	b = a - 48;
	printf("a=%c\tb=%d\n", a, b);*/

	for (i = 0; i < strlen(str); i++)
	{
		b = b + (pow(10, (strlen(str)-i-1)))*((str[i])-48);
	}
	printf("%s %d\n", str, b);

	return 0;
}