
#include <stdio.h>
#include <stdlib.h>
#include "./Item/Item.h"
#include "./Util/Util.h"
#include "./Arvore/Arvore.h"

int main(){
  ARVORE_BINARIA *arvore_binaria;
	arvore_binaria = criar_arvore();
  
  char operacao;
  char input [500];
  int i, quantidade;
  

	scanf("%d", &quantidade);

  for(i=0; i<quantidade; i++){
		  char *linha = get_string();
		  adicionar_item(linha, arvore_binaria);
		  free(linha);
  }

  scanf("%s", &operacao);
  getchar();

  switch (operacao){
    
    case 'I' :
      fgets(input, 500, stdin);
      adicionar_item(input, arvore_binaria);
      ordernar_pre_ordem(arvore_binaria);
    break;
    
    case 'R' :
      fgets(input, 15, stdin);
      deletar_node(arvore_binaria, input);
      ordernar_pre_ordem(arvore_binaria);
    break;
    
    case 'B' :
      fgets(input, 15, stdin);
      pesquisar(arvore_binaria, input);
    break;
    
    default :
      printf ("Valor invalido!\n");
  }

  printf("\n");
	ab_apagar_arvore(&arvore_binaria);

	return 0;
}