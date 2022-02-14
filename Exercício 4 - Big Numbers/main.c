#include <stdio.h>
#include <stdlib.h>

#include "Lista/Lista.h"
#include "Item/Item.h"

void teste();

int main() {
  teste();
}

void teste()
{
    LISTA *lista;
    lista = lista_criar();

    int i;
    int quantidade = 0;
    
    scanf("%d", &quantidade);
   
    for( i = 0; i < quantidade ; i++){
      ITEM *item = item_ler_std_in();
      lista_inserir(lista, item);

      item = NULL;
      free(item);
    }

    lista_resultado(lista);
    limpar(lista);
    free(lista);
}
