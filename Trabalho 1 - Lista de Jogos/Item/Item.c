#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Item.h"

typedef struct item ITEM;

struct item
{
    int chave;
    char titulo[50];
    int ano;
    char empresa[50];
};

ITEM *item_criar_vazio()
{
    ITEM *item;

    item = (ITEM *) calloc(sizeof(ITEM), 1);
    return item;
}

ITEM *item_criar (const char *titulo, int ano, const char *empresa)
{
    ITEM *item;

    item = (ITEM *) malloc(sizeof(ITEM));

    if (item != NULL)
    {
        strcpy(item->titulo, titulo);
        item->ano = ano;
        strcpy(item->empresa, empresa);
        return item;
    }
    return NULL;
}

void item_imprimir_nome(const ITEM *item)
{
    if (item != NULL)
    {
        printf("%s\n", item->titulo);
    }
}

void limpa_ascii(char *string) {
    char *nova_string = malloc(strlen(string));
    int count = 0;
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] > 0) {
            nova_string[count] = string[i];
            count++;
        }
    }
    strcpy(string, nova_string);
    free(nova_string);
}

int item_get_chave(const ITEM *item)
{
    if (item != NULL)
    {
        return item->chave;
    }
    return ERRO;
}


ITEM *item_set_chave(ITEM *item, int chave)
{
    if (item != NULL){
        item->chave = chave;
        return item;
    }
    return NULL;
}

ITEM *le_linha(FILE *fp) {
    char linha[1024];

    if (fgets(linha, sizeof(linha), fp) == NULL)
        return NULL;

    if (strcmp(linha, "\n") == 0 || strcmp(linha, "\r\n") == 0)
        return NULL;

    linha[strcspn(linha, "\n")] = 0;
    linha[strcspn(linha, "\r")] = 0;

    char *split = strtok(linha, ";");
    char *nome = malloc(strlen(split) + 1);
    strcpy(nome, split);
    limpa_ascii(nome);

    split = strtok(NULL, ";");
    char *ano_raw = malloc(strlen(split) + 1);
    strcpy(ano_raw, split);
    int ano = atoi(ano_raw);

    split = strtok(NULL, ";");
    char *empresa = malloc(strlen(split));
    strcpy(empresa, split);

    return item_criar(nome, ano, empresa);
}

int item_retorna_ano(const ITEM *item){
  return item->ano;
}

const char * item_retorna_empresa(const ITEM *item){
  return item->empresa;
}

int comparar_string(const ITEM *item, const char * empresa_filtro){
  return strncmp(item->empresa, empresa_filtro, strlen(empresa_filtro)); 
}

boolean item_comparar(const ITEM *item, const ITEM *itemLista) {
    if ((strncmp(item->titulo, itemLista->titulo, strlen(itemLista->titulo)) == 0) &&
       (item->ano == itemLista->ano) &&
       (strncmp(item->empresa, itemLista->empresa, strlen(itemLista->empresa)) == 0))
    {
      return TRUE;
    }else{
      return FALSE;
    }
}