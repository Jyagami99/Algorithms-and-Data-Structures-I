#ifndef ITEM_H
#define ITEM_H

#include "../Util/Util.h"
#define ERRO (-32000)

typedef struct item ITEM;

ITEM *item_criar_vazio();
ITEM *item_criar (const char *titulo, int ano, const char *empresa);
void item_imprimir_nome(const ITEM *item);
void limpa_ascii(char *string);
int item_get_chave(const ITEM *item);
ITEM *item_set_chave(ITEM *item, int chave);
ITEM *le_linha(FILE *fp);
int item_retorna_ano(const ITEM *item);
const char * item_retorna_empresa(const ITEM *item);
int comparar_string(const ITEM *item, const char * empresa_filtro);
boolean item_comparar(const ITEM *item, const ITEM *itemLista);

#endif //ITEM_H
