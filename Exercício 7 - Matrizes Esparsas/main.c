#include <stdio.h>
#include <stdlib.h>
#include "./MatrizEsparsa/MatrizEsparsa.h"
#include "./Util/Util.h"

int main(){
    MATRIZ_ESPARSA *matriz;

    int qtd_estacoes;
    int qtd_conexoes;

    scanf("%d %d", &qtd_estacoes, &qtd_conexoes);

    matriz = criar_matriz(qtd_estacoes, qtd_conexoes);

    int esatacao_origem;
    int estacao_destino;
    int distancia;
    int status = 1; 

    for(int i = 0; i < qtd_conexoes; i++){
        scanf("%d %d %d", &esatacao_origem, &estacao_destino, &distancia);

        status = set(matriz, esatacao_origem, estacao_destino, distancia);

        if(status==0)
            break;
    }

    int destino;
    int origem;
    int caminho_valido = FALSE;

    scanf("%d %d", &origem, &destino);
    
    caminho_valido = verifica_caminho(matriz, origem, destino);

    if(caminho_valido == FALSE){
        for(int i = 1; i <= qtd_estacoes; i++){
            int verificador = verifica_caminho(matriz, origem, i);

            if(verificador == 1)
                caminho_valido = verifica_caminho(matriz, i, destino);

            if(caminho_valido == TRUE)
                break;
        }
    }
    
    if(origem == destino)
        caminho_valido = TRUE;

    if(caminho_valido == TRUE)
        printf("Existe caminho.\n");
    
    else
        printf("Não existe caminho.\n");

    apagar_matriz(&matriz);

    return 0;
}