#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Lista.h"

typedef struct node_st NODE;

struct node_st{
  ITEM *item;
	NODE * proximo;
  NODE * anterior;
};

struct lista{
	NODE * inicio;
	NODE * fim;
	int tamanho;
};

boolean is_list_start(const LISTA *l, const NODE *nodeAtual);

NODE *getNodeWithKey(int chave, NODE *nodeAtual);

boolean deleteNode(LISTA *l, NODE *nodeAtual);

boolean listContainsSomething(const LISTA *l);

boolean deleteNodeIfPossible(LISTA *l, NODE *nodeAtual);

LISTA * lista_inicia(){
	LISTA * novo = (LISTA *)malloc(sizeof(LISTA));
	novo->inicio = NULL;
	novo->fim = NULL;
	novo->tamanho = 0;
	return novo;
}

boolean lista_vazia(const LISTA *lista){
    if(lista != NULL)
    {
        return lista->inicio == NULL;
    }
    return ERRO;
}

void lista_insere(LISTA * l, const ITEM *item){
	NODE * novo = (NODE*)malloc(sizeof(NODE));
  memcpy( (void*)&novo->item, (void*)&item, sizeof(item) );
	if(l->tamanho == 0){
		l->inicio = novo;
		l->fim = novo;
		l->tamanho++;
	}
	else if(l->tamanho == 1){
		l->inicio->proximo = novo;
		l->inicio->anterior = novo;
		l->fim = novo;
		novo->anterior = l->inicio;
		novo->proximo = l->inicio;
		l->tamanho++;
	}else{
		l->inicio->anterior = novo;
		novo->proximo = l->inicio;
		novo->anterior = l->fim;
		l->fim->proximo = novo;
		l->fim = novo;
		l->tamanho++;
	}
}

void lista_imprime_titulo(LISTA * l){
  if (l->inicio == NULL){
    printf("Não há items a serem impressos\n");
    return;
  }
	NODE * percorre = l->inicio;
  item_imprimir_nome(percorre->item);

	while(percorre!=l->fim){
    percorre = percorre->proximo;
    item_imprimir_nome(percorre->item);
	}
}


void lista_libera(LISTA * l){
	NODE * percorre = l->inicio;
  while(percorre != NULL && percorre != l->fim){
		NODE * libera = percorre;
		percorre = percorre->proximo;
    free(libera);
	}
  free(percorre);
  free(l);
  // printf("freed\n");
}

boolean lista_remover_item(LISTA *l, NODE *node){
    NODE *nodeAtual = node;
    if (listContainsSomething(l)){
      boolean result = deleteNodeIfPossible(l, nodeAtual);
      if(result == TRUE)
        return TRUE;
   }
   return FALSE; /*elemento (chave) não está na lista ou lista vazia*/
}

boolean deleteNodeIfPossible(LISTA *l, NODE *nodeAtual){
    boolean result;
    if(nodeAtual != NULL)
    {
        result = deleteNode(l, nodeAtual);
    }
    else
    {
        result = FALSE;
    }
    return result;
}

boolean listContainsSomething(const LISTA *l)
{
    return (l != NULL) && (!lista_vazia(l));
}

boolean deleteNode(LISTA *l, NODE *nodeAtual) {/*Se é o 1º da lista basta acertar o ptr inicio*/
    if(is_list_start(l, nodeAtual))
    {
        l->inicio = nodeAtual->proximo;
    }
    /*Se não é o 1º da lista, há alguém antes dele para acertar o ptr*/
    else
    {
        nodeAtual->anterior->proximo = nodeAtual->proximo;
    }
    /* Ideia do if/else anterior para o fim da lista */
    if(nodeAtual == l->fim)
    {
        l->fim = nodeAtual->anterior;
    }
    else
    {
        nodeAtual->proximo->anterior = nodeAtual->anterior;
    }
    nodeAtual->proximo = NULL;
    nodeAtual->anterior = NULL;
    free(nodeAtual);
    l->tamanho--;
    return TRUE;
}

NODE *getNodeWithKey(int chave, NODE *nodeAtual){
    while(nodeAtual != NULL && (item_get_chave(nodeAtual->item) != chave) ) {
        nodeAtual = nodeAtual->proximo;
    }
    return nodeAtual;
}

boolean is_list_start(const LISTA *l, const NODE *nodeAtual) {
    return nodeAtual == l->inicio;
}

// Retorna uma lista com todos os jogos do ano da query.
LISTA *querry_ano(const LISTA *l, int ano, LISTA *result) {
    if (l == NULL) return NULL;
    NODE *nodeAtual = l->inicio;
  
    if (item_retorna_ano(nodeAtual->item) == ano) {
            lista_insere(result, nodeAtual->item);
    }

    while (nodeAtual != l->fim) {
        nodeAtual = nodeAtual->proximo;
        if (item_retorna_ano(nodeAtual->item) == ano) {
            lista_insere(result, nodeAtual->item);
        }
    }
    return result;
}

// Retorna uma lista com todos os jogos da empresa da query.
LISTA *querry_empresa(const LISTA *l, const char *empresa, LISTA *result) {
    if (l == NULL) return NULL;
    NODE *nodeAtual = l->inicio;

    if(comparar_string( nodeAtual->item, empresa) == 0){
        lista_insere(result, nodeAtual->item);
    }

    while (nodeAtual != l->fim) {
    nodeAtual = nodeAtual->proximo;

    if(comparar_string( nodeAtual->item, empresa) == 0) {
        lista_insere(result, nodeAtual->item);
        }
    }

    return result;
}

// retorna lista de apenas um item com o item da posição indicada
LISTA *query_posicao(const LISTA *l, int posicao, LISTA *resultado){
  NODE *percorre = l->inicio;
  for(int i=0; i < posicao; i++){
    percorre = percorre->proximo;
  }
  lista_insere(resultado, percorre->item);
  return resultado;
}

void move_item_direita(LISTA *l, int jogo, int casas){
  NODE *percorre = l->inicio;
  // percorre a lista até o jogo que quiser mudar de posição
  for(int i=0; i < jogo; i++){
    percorre = percorre->proximo;
  }

  // estrutura da troca (moveremos o 2 para a direita)
  // inicio   1 ; 2 ; 3 ; 4 ; 5 ; 6
  //
  // final    1 ; 3 ; 2 ; 4 ; 5 ; 6
  //         |______________| -> tiveram alteração em pelo menos algum componente
  //                             sejam eles node->proximo ou node->anterior
  //
  //   from      1 ->2      to         1-> 3 
  //   from  1<- 2 ->3      to     3<- 2 ->4
  //   from  2<- 3 ->4      to     1<- 3 ->2
  //   from  3<- 4          to     2<- 4   
  
  for(int i=0;i<casas;i++){
    NODE *primeiro = percorre->anterior;
    NODE *segundo = percorre;              

    NODE *terceiro = percorre->proximo; 

    NODE *quarto = terceiro->proximo;

    // casos especiais -> necessaria atualização de inicio e fim da lista
    if(segundo == l->inicio){
      l->inicio = terceiro;
    }
    else if(segundo == l->fim){
      l->inicio = segundo;
      l->fim = terceiro;
    }
    else if(segundo->proximo== l->fim){
      l->fim=segundo;
    }

    primeiro->proximo = terceiro; 

    segundo->proximo = quarto;    
    segundo->anterior = terceiro; 
    
    terceiro->proximo = segundo;  
    terceiro->anterior = primeiro;
    
    quarto->anterior=segundo;
  }
}

void move_item_esquerda(LISTA *l, int jogo, int casas){
  NODE *percorre = l->inicio;
  // percorre a lista até o jogo que quiser mudar de posição
  for(int i=0; i < jogo; i++){
    percorre = percorre->proximo;
  }

  // estrutura da troca (moveremos o 3 para a esquerda)
  // inicio   1 ; 2 ; 3 ; 4 ; 5 ; 6
  //
  // final    1 ; 3 ; 2 ; 4 ; 5 ; 6
  //         |______________| -> tiveram alteração em pelo menos algum componente
  //                             sejam eles node->proximo ou node->anterior
  //
  //   from      1 ->2      to         1-> 3 
  //   from  1<- 2 ->3      to     3<- 2 ->4
  //   from  2<- 3 ->4      to     1<- 3 ->2
  //   from  3<- 4          to     2<- 4   
  
  for(int i=0;i<casas;i++){
    NODE *primeiro = percorre->anterior->anterior;
    NODE *segundo = percorre->anterior;             

    NODE *terceiro = percorre;    

    NODE *quarto = percorre->proximo;

    // casos especiais -> necessaria atualização de inicio e fim da lista

    if(terceiro == l->fim){
      l->fim = segundo;
    }
    else if(terceiro == l->inicio){
      l->inicio = segundo;
      l->fim    = terceiro; 
    }
    else if(terceiro->anterior== l->inicio){
      l->inicio=terceiro;
    }

    primeiro->proximo = terceiro; 

    segundo->proximo = quarto;    
    segundo->anterior = terceiro; 
    
    terceiro->proximo = segundo;  
    terceiro->anterior = primeiro;
    
    quarto->anterior=segundo;
  }
}

// Remove os ITEMs que são comparativamente iguais ao ITEM passado por parâmetro
boolean lista_remove_item_duplicado(LISTA *l, const ITEM *item, NODE *nodeAtual) {
    if (l == NULL || item == NULL) return FALSE;
    NODE *node = nodeAtual;
    boolean removed = FALSE;

    do {
        node = node->proximo;
        if (item_comparar(node->item, item)) {
            lista_remover_item(l, node);
            removed = TRUE;
        }
    } while (node != l->fim);

    return removed;
}

// Remove todos os ITEMs duplicados da lista

// Não foi possivel implementar essa última função, em determinado
// momento o nó aponta para ele mesmo e acaba apagando a lista 
// inteira, resultando em um Segmentation fault (core dumped)

boolean lista_remove_duplicados(LISTA *l) {
    if (l == NULL) return FALSE;
    NODE *nodeAtual = l->inicio;
    boolean removed = FALSE;

    do {
        nodeAtual = nodeAtual->proximo;
        if (lista_remove_item_duplicado(l, nodeAtual->item, nodeAtual)) {
            removed = TRUE;
        }
    } while (nodeAtual != l->fim);

    return removed;
}