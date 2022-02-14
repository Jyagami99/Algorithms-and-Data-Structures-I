#include <stdlib.h>
#include "../Lista/Lista.h"
#include "../Item/Item.h"

typedef struct node_st NODE;

struct node_st
{
    ITEM *item;
    NODE* proximo;
};

struct lista {
    NODE* inicio;
    NODE* fim;
    int tamanho;
};

LISTA *lista_criar()
{
    LISTA *lista = (LISTA*) malloc(sizeof(LISTA));
    if(lista != NULL)
    {
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tamanho = 0;
    }
    return lista;
}

boolean lista_vazia(const LISTA *lista)
{
    if(lista != NULL)
    {
        return lista->inicio == NULL;
    }
    return ERRO;
}

int lista_tamanho(const LISTA *lista) {
    if(lista != NULL)
    {
        return lista->tamanho;
    }
    return ERRO;
}

int lista_inserir(LISTA *lista, ITEM *item)
{
    if(lista != NULL)
    {
        NODE *novoNode = (NODE *) malloc(sizeof(NODE));
        if (novoNode != NULL) {
            novoNode->item = item;
            novoNode->proximo = NULL;
            if(lista_vazia(lista))
            {
                lista->inicio = novoNode;
            }
            else
            {
                lista->fim->proximo = novoNode;
            }
            lista->fim = novoNode;
            lista->tamanho++;
            return TRUE;
        }
    }
    return ERRO;
}

ITEM *lista_resultado(const LISTA *lista) {
    if (lista != NULL) {
        NODE *noAtual;
        noAtual = lista->inicio;
        while(noAtual != NULL)
        {
            item_calcular(noAtual->item);
                        
            noAtual = noAtual->proximo;
        }
    }
    return NULL;
}

void limpar(const LISTA *lista) {
    if (lista != NULL) {
        NODE *noAtual;
        noAtual = lista->inicio;
        while(noAtual != NULL)
        {
          item_apagar(&noAtual->item);
          
          noAtual = noAtual->proximo;
        }
    }
}
