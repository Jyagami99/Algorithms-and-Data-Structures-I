#ifndef _JOGO_
#define _JOGO_H
#include "arvore.h"

#define TRUE 0
#define ERRO (-1)

typedef struct jogo JOGO;

JOGO* criar_jogo_vazio();
JOGO* jogo_criar(char* titulo, char* produtora, int ano);
void apagar_jogo(JOGO **jogo);
char* get_titulo(JOGO* jogo);
char* get_produtora(JOGO* jogo);
int get_ano(JOGO* jogo);

#endif