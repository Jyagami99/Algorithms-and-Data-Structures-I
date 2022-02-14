#ifndef LISTA_H
#define LISTA_H

#include "../Util/Util.h"
#include "../Item/Item.h"

#define TAM_MAX 100 /*estimativa do tamanho máximo da valores*/
#define INICIO 0
#define ERRO (-32000)

typedef struct lista LISTA;

LISTA* lista_criar();
boolean lista_vazia(const LISTA* lista);
int lista_tamanho(const LISTA *lista);
int lista_inserir(LISTA *lista, ITEM* item);
ITEM *lista_resultado(const LISTA *lista);
void limpar(const LISTA *lista);

#endif //LISTA_H