#include "planocarte/caminho.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
  
  //Declara as variáveis e armazena o numero de componentes do vetor
  Ponto * v;
  int i, num_componentes;
  float total = 0.0;

  scanf("%d", & num_componentes);

  v = (Ponto * ) malloc(num_componentes * sizeof(Ponto));

  //Armazenando os dados em um vetor
  for (i = 0; i < num_componentes; i++) {
    scanf("%f", & v[i].x);
    scanf("%f", & v[i].y);
  }

  eqc(i, v, num_componentes, total);

  //liberando o espaço de memória alocado
  free(v);

  return 0;
}

// função responsavel por calcular o resultado total da distância dos pontos
void eqc(int i, Ponto * v, int num_componentes, float total) {
  for (i = 0; i < num_componentes - 1; i++) {
    total = total + sqrt(pow((v[i + 1].x - v[i].x), 2) + pow((v[i + 1].y - v[i].y), 2));
  }

  printf("%0.2f\n", total);
};