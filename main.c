
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "sstring.h"

int main (int argc, char *argv[])
{
	// String array...
	sstring *str[] =
	{
		new_sstring("Valor 1 "),
		new_sstring("Valor 2 "),
		new_sstring("Valor 3 "),
	};

	// Normal...
	sstring *stra = new_sstring(NULL);

	// String array test...
	if (str[0]->error(str[0]) == SS_OK && str[1]->error(str[1]) == SS_OK)
	{
		str[0]->value(str[0], "Teste lalala");
		printf("str: %s\nlen: %d\n", str[0]->string(str[0]), str[0]->length(str[0]));

		str[0]->value(str[0], "Teste lelele");
		printf("str: %s\nlen: %d\n", str[0]->string(str[0]), str[0]->length(str[0]));

		str[1]->value(str[1], "Teste lololo");
		printf("str: %s\nlen: %d\n", str[1]->string(str[1]), str[1]->length(str[1]));
	}
	else
		printf("Error code: 0x%d\n", str[0]->error(str[0]));

	// Normal string teste...
	if (stra->error(stra) == SS_OK)
	{
		stra->value(stra, "Teste String normal!");
		printf("str: %s\nlen: %d\n", stra->string(stra), stra->length(stra));

		stra->value(stra, "Teste String normal com tamanho um pouco maior...");
		printf("str: %s\nlen: %d\n", stra->string(stra), stra->length(stra));

		stra->value(stra, "Teste String normal com tamanho menor...");
		printf("str: %s\nlen: %d\n", stra->string(stra), stra->length(stra));
	}
	else
		printf("Error code: 0x%d\n", stra->error(stra));

	return 0;
}
