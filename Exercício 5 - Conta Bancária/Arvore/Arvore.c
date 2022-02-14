#include <stdlib.h>
#include <stdio.h>
#include "../Item/Item.h"
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
    printf("\n");
	}
}

void ordernar_em_ordem(ARVORE_BINARIA* arvore_binaria){
	if(arvore_binaria != NULL){
		printf("Inorder\n");
		em_ordem_recursao(arvore_binaria->raiz);
    printf("\n");
	}
}	

void ordernar_pos_ordem(ARVORE_BINARIA* arvore_binaria){
	if(arvore_binaria != NULL){
		printf("Postorder\n");
		pos_ordem_recursao(arvore_binaria->raiz);	
    printf("\n");
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