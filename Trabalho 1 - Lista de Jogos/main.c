#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Lista/Lista.h"

int main(){
    int index = 0;
	  FILE *fp;
    fp = fopen("CSV.csv", "r");
    if (fp == NULL) {
        printf("Erro ao abrir CSV.\n");
        return 1;
    }

    ITEM *item;
    LISTA *lista = lista_inicia();

    while (!feof(fp)) {
        if ((item = le_linha(fp)) != NULL) {
            item = item_set_chave(item, index);
            lista_insere(lista, item);
        }
        index = index + 1;
    }

    while(1){
      char comando[4];
      // printf("Entre um comando:\n");
      scanf("%s", comando);

      if(strncmp(comando, "f", 1)==0){
        // printf("Encerrando programa\n");
        break;
      }
      
      // 
      else if(strncmp(comando, "p", 1)==0){
        char empresa[35];
        scanf("%s", empresa);
        LISTA *resultado_da_querry = lista_inicia();
        resultado_da_querry = querry_empresa(lista, empresa, resultado_da_querry);
        
        lista_imprime_titulo(resultado_da_querry);

        lista_libera(resultado_da_querry);
       
        // printf("querry por produtora: %s", produtora);
      }
      
      else if(strncmp(comando, "a", 2)==0){
        int ano;
        scanf("%i", &ano);
        LISTA *resultado_da_querry = lista_inicia();
        resultado_da_querry = querry_ano(lista, ano, resultado_da_querry);
        
        lista_imprime_titulo(resultado_da_querry);

        lista_libera(resultado_da_querry);
        
      }

      else if(strncmp(comando, "r", 2)==0){
        lista_remove_duplicados(lista);
      }

      else if(strncmp(comando, "i", 2)==0){
        lista_imprime_titulo(lista);
      }

      else if(strncmp(comando, "u", 2)==0){
        int posicao;
        scanf("%i", &posicao);

        LISTA *resultado = lista_inicia();
        resultado = query_posicao(lista, posicao, resultado);

        lista_imprime_titulo(resultado);
        lista_libera(resultado);
      }

      else if(strncmp(comando, "mr", 2)==0){
        int jogo, casas;
        scanf("%i %i", &jogo, &casas);

        move_item_direita(lista, jogo, casas);

      }

      else if(strncmp(comando, "ml", 2)==0){
        int jogo, casas;
        scanf("%i %i", &jogo, &casas);
        move_item_esquerda(lista, jogo, casas);
      }

      else{
        // limpa o stdin antes de ir ao proximo loop
        char lixo[35];
        fgets(lixo, 35, stdin);
        fflush(stdin);
        // printf("Comando invalido, tente novamente\n");
      }
    }
    lista_libera(lista);
}