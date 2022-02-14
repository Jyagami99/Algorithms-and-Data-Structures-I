#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arvore.h"
#include "jogo.h"

int main() {

    FILE* fp;
    fp = fopen("CSV.csv", "r+");

    JOGO *aux;
    AVL *arvore;
    arvore = avl_criar();

    int status = TRUE;
    fseek(fp, 3, SEEK_SET);

    while(!feof(fp)) {
        if((aux = read_line(fp)) != NULL && status != ERRO) {
            status = avl_inserir(arvore, aux);
    
        }
    }

    char menu[5];
    int ordem;
    int ano_remover; 

    scanf("%d", &ordem);


    scanf("%s", menu);

    while(strcmp(menu, "F\0") != 0) {
        ano_remover = atoi(menu);
        remocao_auxiliar(arvore, ano_remover);
        scanf("%s", menu);
        
    }

    switch(ordem) {
        case 1:
            pre_ordem(arvore);
            break;
        case 2:
            em_ordem(arvore);
            break;
        case 3:
            pos_ordem(arvore);
            break;
    }



    fclose(fp);
    avl_apagar(&arvore);


    return 0;
}


