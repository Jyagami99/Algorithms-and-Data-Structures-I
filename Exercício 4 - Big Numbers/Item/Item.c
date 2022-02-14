#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Item.h"

struct item_st
{
    char operacao[5];
    long long int valor1;
    long long int valor2;
};

ITEM *item_criar (const char *operacao, long long int valor1, long long int valor2)
{
    ITEM *item;

    item = (ITEM *) malloc(sizeof(ITEM));

    if (item != NULL)
    {
        strcpy(item->operacao, operacao);
        item->valor1 = valor1;
        item->valor2 = valor2;
        return item;
    }
    return NULL;
}

ITEM *item_ler_std_in()
{
  char sTexto[1024];
  char operacao[5];
  long long int numero1, numero2 = 0L;

  scanf(" %[^(\r|\n)]*c", sTexto);
 
  sscanf(sTexto, "%s%lld%lld", operacao, &numero1, &numero2);

  return item_criar(operacao, numero1, numero2);    
}

void item_calcular(const ITEM *item){
    if(strcmp(item->operacao,"soma") == 0)
    {
        printf("Resultado :: %lld \n", item->valor1 + item->valor2);
    }
    if(strcmp(item->operacao,"maior") == 0)
    {
        printf("Resultado :: %s \n", boolean_print(item->valor1 > item->valor2));
    }
    if(strcmp(item->operacao,"menor") == 0)
    {
        printf("Resultado :: %s \n", boolean_print(item->valor1 < item->valor2));
    }
    if(strcmp(item->operacao,"igual") == 0)
    {
        printf("Resultado :: %s \n", boolean_print(item->valor1 == item->valor2));
    }
}

boolean item_apagar(ITEM **item)
{
    if (*item != NULL)
    {
        free (*item);
        *item = NULL;
        return TRUE;
    }
    return FALSE;
}