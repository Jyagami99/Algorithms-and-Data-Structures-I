#ifndef LISTA_H
#define LISTA_H

#include "../Util/Util.h"
#include "../Item/Item.h"

#define TAM_MAX 100 /*estimativa do tamanho máximo da valores*/
#define INICIO 0
#define ERRO (-32000)

typedef struct lista LISTA;
typedef struct node_st NODE;

LISTA * lista_inicia();
boolean lista_vazia(const LISTA *lista);
void lista_insere(LISTA * lista, const ITEM *item);
void lista_imprime_titulo(LISTA * l);
void lista_libera(LISTA * l);
boolean lista_remover_item(LISTA *lista, NODE *node);
LISTA *querry_ano(const LISTA *l, int query, LISTA *result);
LISTA *querry_empresa(const LISTA *l, const char *empresa, LISTA *result);
LISTA *query_posicao(const LISTA *l, int posicao, LISTA *resultado);
void move_item_direita(LISTA *l, int jogo, int casas);
void move_item_esquerda(LISTA *l, int jogo, int casas);;
boolean lista_remove_duplicados(LISTA *l);

#endif //LISTA_H