#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "jogo.h"
#include "arvore.h"

struct jogo {
    char* titulo;
    char* produtora;
    int ano;
};

JOGO* criar_jogo_vazio() {

	JOGO* jogo;
	
	jogo = (JOGO*) malloc(sizeof(JOGO));

	return jogo;
}

JOGO* jogo_criar(char* titulo, char* produtora, int ano) {
    JOGO* jogo;

    jogo = (JOGO*) malloc(sizeof(JOGO));
    jogo->titulo = (char*) malloc(sizeof(titulo));
    jogo->ano = (uintptr_t) malloc(sizeof(int));
    jogo->produtora = (char*) malloc(sizeof(produtora));

    if (jogo != NULL)
    {
        strcpy(jogo->titulo, titulo);
        jogo->ano = ano;
        strcpy(jogo->produtora, produtora);
        return jogo;
    }

    return NULL;
}

void apagar_jogo(JOGO **jogo) {
    if (*jogo != NULL) {
    	// free(*jogo);
      // printf("free 1");
    	*jogo = NULL;
    }

}

char* get_titulo(JOGO* jogo) {

    return jogo->titulo;
}

char* get_produtora(JOGO* jogo) {

    return jogo->produtora;
}

int get_ano(JOGO* jogo) {
	return jogo->ano;
}