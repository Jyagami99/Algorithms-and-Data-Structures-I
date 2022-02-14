#include <stdio.h>
#include <stdlib.h>
#include "./MatrizEsparsa.h"
#include "../Util/Util.h"


struct celula {
    int linha;
    int coluna;
    int valor;
    CELULA *direita;
    CELULA *abaixo;
};

struct matriz_esparsa {
    CELULA **linhas;
    CELULA **colunas;
    int nr_linhas;
    int nr_colunas;
};

MATRIZ_ESPARSA *criar_matriz(int nr_linhas, int nr_colunas) {
    MATRIZ_ESPARSA *matriz = (MATRIZ_ESPARSA *) malloc(sizeof (MATRIZ_ESPARSA));
    if (matriz != NULL) {
        matriz->nr_colunas = nr_colunas;
        matriz->nr_linhas = nr_linhas;
        matriz->colunas = (CELULA **) malloc(sizeof (CELULA *) * nr_colunas);
        matriz->linhas = (CELULA **) malloc(sizeof (CELULA *) * nr_linhas);
        if (matriz->colunas != NULL && matriz->linhas != NULL) {
            for (int i = 0; i < nr_colunas; i++) {
                matriz->colunas[i] = NULL;
            }
            for (int i = 0; i < nr_linhas; i++) {
                matriz->linhas[i] = NULL;
            }
        }
    }
    
    return matriz;
}

void apagar_matriz(MATRIZ_ESPARSA **matriz) {
    for (int i = 0; i < (*matriz)->nr_linhas; i++) {
        if((*matriz)->linhas[i] != NULL){
            CELULA *celula = (*matriz)->linhas[i]->direita;
            while (celula != NULL) {
                CELULA *celulaAnterior = celula;
                celula = celula->direita;
                free(celulaAnterior);
                celulaAnterior = NULL;
            }
        }
        free((*matriz)->linhas[i]);
        (*matriz)->linhas[i] = NULL;
    }
    free((*matriz)->linhas);
    (*matriz)->linhas = NULL;
    free((*matriz)->colunas);
    (*matriz)->colunas = NULL;
    free((*matriz));
    *matriz = NULL;
}

int verifica_caminho(MATRIZ_ESPARSA *matriz, int origem, int destino) {
    int caminho_valido = FALSE;
    int distancia = get(matriz, origem, destino);

    if(distancia != 0) {
        caminho_valido = TRUE;
    }

    return caminho_valido;
}

int set(MATRIZ_ESPARSA *matriz, int linha, int coluna, float valor) {
    CELULA *celulaAtual;
    CELULA *celulaDaColuna;
    CELULA *celulaAnteriorDaColuna;
    if ((linha > matriz->nr_linhas) || (coluna > matriz->nr_colunas)) {
        return 0;
    }
    celulaAtual = (CELULA *) malloc(sizeof(CELULA));
    if (celulaAtual == NULL) return 0;
    celulaAtual->linha = linha;
    celulaAtual->coluna = coluna;
    celulaAtual->valor = valor;
    celulaDaColuna = matriz->colunas[coluna];
    celulaAnteriorDaColuna = NULL;
    int inseriu = 0;
    while (celulaDaColuna != NULL && !inseriu) {
        if (celulaDaColuna->linha < linha) {
            celulaAnteriorDaColuna = celulaDaColuna;
            celulaDaColuna = celulaDaColuna->abaixo;
        } else {

            if (celulaAnteriorDaColuna == NULL)
                matriz->colunas[coluna] = celulaAtual;
            else
                celulaAnteriorDaColuna->abaixo = celulaAtual;
            celulaAtual->abaixo = celulaDaColuna;
            inseriu = 1;
        }
    }

    if (celulaDaColuna == NULL) {
        if (celulaAnteriorDaColuna == NULL) {
            matriz->colunas[coluna] = celulaAtual;
        }
        else {
            celulaAnteriorDaColuna->abaixo = celulaAtual;
        }
    }

    return 1;
}

float get(MATRIZ_ESPARSA *matriz, int linha, int coluna) {
    if (matriz->nr_linhas < linha || matriz->nr_colunas < coluna)     return 0;

    CELULA *celulaAtual = matriz->colunas[coluna];

    if (celulaAtual == NULL) {
        return 0;
    }

    while (celulaAtual->abaixo != NULL && linha > celulaAtual->abaixo->linha) {
        celulaAtual = celulaAtual->abaixo;
    }
    if (celulaAtual->linha == linha)
        return (celulaAtual->valor);
    return 0;
}