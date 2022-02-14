#ifndef TADGENERICO_AVL_H
#define TADGENERICO_AVL_H

#include "jogo.h"

typedef int boolean;

#define max(a, b) ((a > b) ? a : b)

typedef struct avl AVL;
typedef struct node_st NODE;

JOGO* read_line(FILE* fp);
AVL *avl_criar();
void pre_ordem(AVL* arvore);
void em_ordem(AVL* arvore);
void pos_ordem(AVL* arvore);
boolean avl_inserir(AVL *arvore, JOGO* jogo);
void avl_apagar(AVL **arvore);
void remocao_auxiliar(AVL *arvore, int ano);

#endif //TADGENERICO_AVL_H
