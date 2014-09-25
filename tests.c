
/* Tests... */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "sstring.h"

int main (int argc, char *argv[])
{
    int a;
    unsigned char *ptr;

    // String array...
    sstring *str[] =
    {
        new_sstring("Valor 1"),
        new_sstring("Meu Valor 2 com tamanho grande!"),
        new_sstring(NULL),
        NULL
    };

    // Normal...
    sstring *stra = new_sstring(NULL);

    // String array test...    
    if (sstring_array_isok(str, 3))
    {
        printf("str: %s\nlen: %d\n", str[0]->string(str[0]), str[0]->length(str[0]));
        str[0]->value(str[0], "Novo valor 1");
        printf("str: %s\nlen: %d\n", str[0]->string(str[0]), str[0]->length(str[0]));

        printf("str: %s\nlen: %d\n", str[1]->string(str[1]), str[1]->length(str[1]));
        str[1]->value(str[1], "Small");
        printf("str: %s\nlen: %d\n", str[1]->string(str[1]), str[1]->length(str[1]));

        str[2]->value(str[2], "Valor 3");
        printf("str: %s\nlen: %d\n", str[2]->string(str[2]), str[2]->length(str[2]));

        // Deleta string da mem�ria.
        str[0]->delete(str[0]);
        str[1]->delete(str[1]);
        str[2]->delete(str[2]);

        for (a = 0; a <= 2; a++)
            printf("Error code: 0x%d\n", str[a]->error(str[a]));

        printf("\n");
    }
    else
    {
        if (stra != (sstring *)NULL)
            printf("Error code: 0x%d\n", stra->error(stra));
        else 
            printf("Struct is NULL!\n");
    }

    if (sstring_isok(stra) == TRUE)
    {
        // Atribui��o e altera��o de valores.
        stra->value(stra, "Minha String normal!");
        printf("str: %s\nlen: %d\n", stra->string(stra), stra->length(stra));

        stra->value(stra, "Minha String normal com tamanho um pouco maior...");
        printf("str: %s\nlen: %d\n", stra->string(stra), stra->length(stra));

        stra->value(stra, "Minha String normal com tamanho menor...");
        printf("str: %s\nlen: %d\n", stra->string(stra), stra->length(stra));
        stra->value(stra, "essa eh minha string normal");

        // Concatena��o.
        printf("ptr: %s - len: %d\n", stra->concat(stra, " e isso foi concatenado no final da string."), stra->length(stra));
        printf("str: %s - len: %d\n", stra->string(stra), stra->length(stra));

        // Seta todos os bytes da string para '\0'
        stra->zero(stra);
        printf("String zerada.\nError code: 0x%d\n", stra->error(stra));

        stra->value(stra, "Minha string com valor novo.");
        printf("str: %s - len: %d\n", stra->string(stra), stra->length(stra));

        // Compara��o.
        stra->value(stra, "Minha string XXX");
        printf("str: %s - len: %d\n", stra->string(stra), stra->length(stra));

        if (stra->compare(stra, "Minha string XXX") == SS_EQUAL)
            printf("Strings sao iguais!\n");
        else
            printf("Strings diferentes.\nError code: 0x%d\n\n", stra->error(stra));
        printf("\n");

        // Procura / Search.
        if ((ptr = stra->search(stra, "string")) != NULL)
        {
            if (stra->error(stra) == SS_STRING_FOUND)
                printf("String encontrada\nstr: %s\nptr: %s\nError code: 0x%d\n", stra->string(stra), ptr, stra->error(stra));
            else if (stra->error(stra) == SS_STRING_NOT_FOUND)
                printf("String nao encontrada.\nError code: 0x%d\n\n", stra->error(stra));
            else
                printf("Erro desconhecido.\nError code: 0x%d\n\n", stra->error(stra));
        }
        else
            printf("String nao encontrada.\nError code: 0x%d\n\n", stra->error(stra));

        // Substitui parte da string ap�s determinada posi��o.
        stra->value(stra, "Minha velha string XX.");
        printf("\n\nstr: %s - len: %d - Error code: 0x%d\n", stra->string(stra), stra->length(stra), stra->error(stra));
        
        printf("\nptr: %s\n", stra->set_value(stra, "YYY", 19));
        printf("\nstr: %s - len: %d - Error code: 0x%d\n", stra->string(stra), stra->length(stra), stra->error(stra));

        // Substitui todas as ocorrencias em uma string.
        stra->value(stra, "velhaxx Minha velhaxx string velhaxx porra velhaxx llalala velhaxx");
        printf("\n\nstr: %s - len: %d - Error code: 0x%d\n", stra->string(stra), stra->length(stra), stra->error(stra));

        // velhaxx
        // novaxxx
        //stra->replace(stra, "velhaxx", "novaxxx");
        //printf("replace...\nstr: %s - len: %d - Error code: 0x%d\n", stra->string(stra), stra->length(stra), stra->error(stra));

        // Deleta string
        stra->delete(stra);
        printf("Error code: 0x%d\n\n", stra->error(stra));
    }
    else
    {
        if (stra != (sstring *)NULL)
            printf("Error code: 0x%d\n", stra->error(stra));
        else 
            printf("Struct is NULL!\n");
    }

    return 0;
}
