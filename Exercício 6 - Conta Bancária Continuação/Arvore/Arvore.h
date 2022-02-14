#ifndef ARVORE_H
#define ARVORE_H

#define FILHO_ESQ 0
#define FILHO_DIR 1

typedef struct node NODE;
typedef struct arvore_binaria ARVORE_BINARIA;

void pesquisar(ARVORE_BINARIA* arvore_binaria, char* cpfInput);
void deletar_node(ARVORE_BINARIA* arvore_binaria, char* cpf_input);
NODE* recursivo_delete_node(NODE *raiz, unsigned long cpf);
ARVORE_BINARIA* criar_arvore();
void ordernar_pre_ordem(ARVORE_BINARIA* arvore_binaria);
void ordernar_pos_ordem(ARVORE_BINARIA* arvore_binaria);
void ordernar_em_ordem(ARVORE_BINARIA* arvore_binaria);
boolean inserir_no(ARVORE_BINARIA* arvore_binaria, NODE* novo_no);
void ab_apagar_arvore(ARVORE_BINARIA **T);
void item_apagar(ITEM **item);
void adicionar_item(char* linha, ARVORE_BINARIA* arvore_binaria);

#endif