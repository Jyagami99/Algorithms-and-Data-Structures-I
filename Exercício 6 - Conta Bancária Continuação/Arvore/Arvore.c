#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../Item/Item.h"
#include "../Util/Util.h"
#include "Arvore.h"

struct node{
	ITEM* item;
	NODE* direita;
	NODE* esquerda;
};

struct arvore_binaria{
	NODE* raiz;
	int profundidade;
};

void item_apagar(ITEM **item);
NODE *busca(NODE* raiz, char* cpf);
NODE *node_valor_minimo(NODE *node);

void pesquisar(ARVORE_BINARIA* arvore_binaria, char* cpfInput){
  NODE* raiz = arvore_binaria->raiz;
  NODE* elem =  busca(raiz, cpfInput);
  imprimir_item(elem->item, cpfInput); 
}

NODE *busca(NODE* raiz, char* cpf){
    if (raiz == NULL || get_cpf(raiz->item) == convert_str_int(cpf)){
      return raiz;
    }
    
    if (get_cpf(raiz->item) < convert_str_int(cpf))
       return busca(raiz->direita, cpf);
 
    return busca(raiz->esquerda, cpf);
}

NODE *node_valor_minimo(NODE *node){
	while (node->esquerda != NULL)
		node = node->esquerda;

	return node;
}

void deletar_node(ARVORE_BINARIA* arvore_binaria, char* cpf_input){
  NODE* no_deletado = busca(arvore_binaria->raiz, cpf_input);
  if(no_deletado != NULL){
    imprimir_item(no_deletado->item, cpf_input);
    
    unsigned long cpf = get_cpf(no_deletado->item);
    arvore_binaria->raiz = recursivo_delete_node(arvore_binaria->raiz, cpf);
  }
}

NODE* recursivo_delete_node(NODE *raiz, unsigned long cpf){
	if (raiz == NULL)
	  return raiz;

	if (cpf < get_cpf(raiz->item))
		raiz->esquerda = recursivo_delete_node(raiz->esquerda, cpf);
  else if (cpf > get_cpf(raiz->item))
		raiz->direita = recursivo_delete_node(raiz->direita, cpf);
	else {
		if (raiz->esquerda == NULL) {
			NODE *new_raiz = raiz->direita;
			free(raiz);
			return new_raiz;
		}
		else if (raiz->direita == NULL) {
			NODE *new_raiz = raiz->esquerda;
			free(raiz);
			return new_raiz;
		}

		NODE *new_raiz = node_valor_minimo(raiz->direita);

    ITEM *tmp = raiz->item;

    raiz->item = new_raiz->item;

    raiz->direita =  recursivo_delete_node(raiz->direita,get_cpf(new_raiz->item));

		item_apagar(&tmp);
	}
	return raiz;
}

static NODE* cria_no(ITEM *item){
    NODE* novoNode = (NODE *) malloc(sizeof(NODE));
    if (novoNode != NULL) {
        novoNode->item = item;
        novoNode->direita = NULL;
        novoNode->esquerda = NULL;
    }
    return novoNode;
}

ARVORE_BINARIA* criar_arvore(){
	ARVORE_BINARIA* arvore_binaria;
	arvore_binaria = (ARVORE_BINARIA*) malloc(sizeof(ARVORE_BINARIA));

	if(arvore_binaria != NULL){
		arvore_binaria->raiz = NULL;
		arvore_binaria->profundidade = -1;
	}
	return arvore_binaria;
}

void pre_ordem_recursao(NODE* raiz){
	if(raiz != NULL){
		imprimir_cpf(raiz->item);
		pre_ordem_recursao(raiz->esquerda);
		pre_ordem_recursao(raiz->direita);
	}
}

void em_ordem_recursao(NODE* raiz){
	if(raiz != NULL){
		em_ordem_recursao(raiz->esquerda);
		imprimir_cpf(raiz->item);
		em_ordem_recursao(raiz->direita);
	}
}

void pos_ordem_recursao(NODE* raiz){
	if(raiz != NULL ){
		pos_ordem_recursao(raiz->esquerda);
		pos_ordem_recursao(raiz->direita);
		imprimir_cpf(raiz->item);
	}
}

void ordernar_pre_ordem(ARVORE_BINARIA* arvore_binaria){
	if(arvore_binaria != NULL){
		printf("Preorder\n");
		pre_ordem_recursao(arvore_binaria->raiz);
	}
}

void ordernar_em_ordem(ARVORE_BINARIA* arvore_binaria){
	if(arvore_binaria != NULL){
		printf("Inorder\n");
		em_ordem_recursao(arvore_binaria->raiz);
	}
}	

void ordernar_pos_ordem(ARVORE_BINARIA* arvore_binaria){
	if(arvore_binaria != NULL){
		printf("Postorder\n");
		pos_ordem_recursao(arvore_binaria->raiz);	
	}
}

boolean inserir_no(ARVORE_BINARIA *arvore_binaria, NODE* novo_node){
  
	if(arvore_binaria != NULL && novo_node != NULL){
		NODE *x = arvore_binaria->raiz;
		NODE *y = NULL;

		unsigned long cpf = get_cpf(novo_node->item);

		while (x != NULL){
	        y = x;
	        if (cpf < get_cpf(x->item))
	            x = x->esquerda;
	        else
	            x = x->direita;
	    }
 
	    if (y == NULL)
	        arvore_binaria->raiz = novo_node;
	 
	    else if (cpf < get_cpf(y->item))
	        y->esquerda = novo_node;	

		 else
	        y->direita = novo_node;

    	return TRUE;
	}	

	return ERRO;
}

void apagar_arvore(NODE **raiz){
    if (*raiz != NULL){
        apagar_arvore(&(*raiz)->esquerda);
        apagar_arvore(&(*raiz)->direita);
        item_apagar(&(*raiz)->item);
        free(*raiz);
        *raiz = NULL;
    }
}

void ab_apagar_arvore(ARVORE_BINARIA **T){
    apagar_arvore(&(*T)->raiz);
    free(*T);
    *T = NULL;
}

void item_apagar(ITEM **item){
	if (*item != NULL){
        free (*item);
        *item = NULL;
    }
}

void adicionar_item(char* linha, ARVORE_BINARIA* arvore){
	if(arvore != NULL){
		ITEM* item;
		item = cadastra_item(linha);
		NODE* node = cria_no(item);
		inserir_no(arvore, node);
	}
}