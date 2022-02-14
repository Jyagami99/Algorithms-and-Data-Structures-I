#include <stdio.h>
#include <stdlib.h>
#include "./Item/Item.h"
#include "./Arvore/Arvore.h"

int main(){
  ARVORE_BINARIA *arvore_binaria;
	arvore_binaria = criar_arvore();
  
  int i, quantidade;

	scanf("%d", &quantidade);

  for(i=0; i<quantidade; i++){
		  char *linha = get_string();
		  adicionar_item(linha, arvore_binaria);
		  free(linha);
  }

	ordernar_em_ordem(arvore_binaria);
	ordernar_pre_ordem(arvore_binaria);
	ordernar_pos_ordem(arvore_binaria);
	ab_apagar_arvore(&arvore_binaria);

	return 0;
}