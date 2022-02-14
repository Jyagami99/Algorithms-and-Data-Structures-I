#ifndef MATRIZESPARSA_H
#define MATRIZESPARSA_H

typedef struct matriz_esparsa MATRIZ_ESPARSA;
typedef struct celula CELULA;

MATRIZ_ESPARSA *criar_matriz(int nr_linhas, int nr_colunas);
void apagar_matriz(MATRIZ_ESPARSA **matriz);
int verifica_caminho(MATRIZ_ESPARSA *matriz, int origem, int destino);
int set(MATRIZ_ESPARSA *matriz, int linha, int coluna, float valor);
float get(MATRIZ_ESPARSA *matriz, int linha, int coluna);

#endif //MATRIZESPARSA_H