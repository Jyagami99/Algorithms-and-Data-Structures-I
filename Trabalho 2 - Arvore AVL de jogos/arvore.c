#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "arvore.h"
#include "jogo.h"

static void avl_apagar_aux(NODE **raiz);
static NODE *avl_inserir_no_e_rotacionar(NODE *raiz, JOGO *jogo);
static bool DesbalanceamentoEhNegativo(NODE *raiz);
static bool DesbalanceamentoEhPositivo(NODE *raiz);
static bool jogoEhMaior(const NODE *raiz, JOGO *jogo);
static bool jogoEhMenor(const NODE *raiz, JOGO *jogo);
static bool jogoEhIgual(const NODE *raiz, JOGO *jogo);
static NODE *selecionar_e_executar_rotacao(NODE *raiz, JOGO *jogo);
static NODE *inserir_no(NODE *raiz, JOGO *jogo);
static NODE *avl_deletar_no_e_rotacionar(NODE *raiz, JOGO *jogo);

struct node_st
{
    JOGO *jogo;
    NODE *direita;
    NODE *esquerda;
    int altura;
};

struct avl
{
    NODE* raiz;
    int profundidade;
};


JOGO* get_jogo(char* line) {

    if(line != NULL) {

        JOGO* jogo = criar_jogo_vazio();

        char* split = strtok(line, ";");
        char* titulo = (char*) malloc(strlen(split)+1);
        strcpy(titulo, split);

        split = strtok(NULL, ";");
        char* ano = (char*) malloc(strlen(split)+1);
        strcpy(ano, split);

        int ano_int = atoi(ano);

        split = strtok(NULL, ";");
        char* produtora = (char*) malloc(strlen(split));
        strcpy(produtora, split);

        jogo = jogo_criar(titulo, produtora, ano_int);

        return jogo;

    }


    return NULL;
}


JOGO* read_line(FILE* fp) {
    char linha[1024];

    JOGO* jogo;

    if(fgets(linha, sizeof(linha), fp) == NULL)
        return NULL;

    if(strcmp(linha, "\n") == 0 || strcmp(linha, "\r\n") == 0)
        return NULL;

    linha[strcspn(linha, "\n")] = 0;
    linha[strcspn(linha, "\r")] = 0;

    jogo = get_jogo(linha);

    return jogo;
}


AVL *avl_criar() {
    AVL *arvore = (AVL *) malloc(sizeof(AVL));
    if (arvore != NULL) {
        arvore->raiz = NULL;
        arvore->profundidade = -1;
    }
    return arvore;
}

static void avl_apagar_aux(NODE **raiz) {
    if (*raiz != NULL) {
        avl_apagar_aux(&((*raiz)->esquerda));
        avl_apagar_aux(&((*raiz)->direita));
        apagar_jogo(&(*raiz)->jogo);
        free(*raiz);
        // printf("free 2");
    }
}

void avl_apagar(AVL **arvore) {
    avl_apagar_aux(&(*arvore)->raiz); 
    free(*arvore);
    // printf("free 3");
    *arvore = NULL;
}

int avl_altura_no(NODE* raiz) {
    if (raiz == NULL) {
        return -1;
    } else {
        return raiz->altura;
    }
}

NODE *avl_cria_no(JOGO *jogo) {
    NODE *no = (NODE *) malloc(sizeof (NODE));
    if (no != NULL) {
        no->altura = 0;
        no->direita = NULL;
        no->esquerda = NULL;
        no->jogo = jogo;
    }
    return no;
}


int getBalance(NODE *N)
{
    if (N == NULL)
        return 0;
    return avl_altura_no(N->esquerda) - avl_altura_no(N->direita);
}


NODE *rodar_direita(NODE *a) {
    NODE *b = a->esquerda;
    a->esquerda = b->direita;
    b->direita = a;

    a->altura = max(avl_altura_no(a->esquerda),
                    avl_altura_no(a->direita)) + 1;
    b->altura = max(avl_altura_no(b->esquerda),
                    a->altura) + 1;
    return b;
}

NODE *rodar_esquerda(NODE *a) {
    NODE *b = a->direita;
    a->direita = b->esquerda;
    b->esquerda = a;

    a->altura = max(avl_altura_no(a->esquerda),
                    avl_altura_no(a->direita)) + 1;
    b->altura = max(avl_altura_no(b->direita),
                    a->altura) + 1;
    return b;
}

NODE *rodar_esquerda_direita(NODE *a)   {
    a->esquerda = rodar_esquerda(a->esquerda);
    return rodar_direita(a);
}

NODE *rodar_direita_esquerda(NODE *a)   {
    a->direita = rodar_direita(a->direita);
    return rodar_esquerda(a);
}

static NODE *avl_inserir_no_e_rotacionar(NODE *raiz, JOGO *jogo) {
    raiz = inserir_no(raiz, jogo);

    raiz->altura = max(avl_altura_no(raiz->esquerda),
                       avl_altura_no(raiz->direita)) + 1;

    raiz = selecionar_e_executar_rotacao(raiz, jogo);

    return raiz;
}

int compare(char *raiz, char *jogo) {
    return strcmp(raiz, jogo);
}

static NODE *inserir_no(NODE *raiz, JOGO *jogo) {
    if (raiz == NULL) {
        raiz = avl_cria_no(jogo);
    }
    else if (jogoEhMaior(raiz, jogo)) {
        raiz->direita = avl_inserir_no_e_rotacionar(raiz->direita, jogo);
    }
    else if (jogoEhMenor(raiz, jogo)) {
        raiz->esquerda = avl_inserir_no_e_rotacionar(raiz->esquerda, jogo);
    }
    else if (jogoEhIgual(raiz, jogo)) {
        char *titulo_raiz = get_titulo(raiz->jogo);
        char *titulo_jogo = get_titulo(jogo);

        int comparacao = compare(titulo_raiz, titulo_jogo);

        if(comparacao < 0) 
            raiz->direita = avl_inserir_no_e_rotacionar(raiz->direita, jogo);
        else if(comparacao > 0)
            raiz->esquerda = avl_inserir_no_e_rotacionar(raiz->esquerda, jogo);
    }
    
    return raiz;
}

static NODE *selecionar_e_executar_rotacao(NODE *raiz, JOGO *jogo) {
    if (DesbalanceamentoEhNegativo(raiz)) {
        if (jogoEhMaior(raiz->direita, jogo)) {
            raiz = rodar_esquerda(raiz);
        }
        else {
            raiz = rodar_direita_esquerda(raiz);
        }
    }

    if (DesbalanceamentoEhPositivo(raiz)) {
        if (jogoEhMenor(raiz->esquerda, jogo))
            raiz = rodar_direita(raiz);
        else
            raiz = rodar_esquerda_direita(raiz);
    }
    return raiz;
}

static bool jogoEhMenor(const NODE *raiz, JOGO *jogo) {
    return get_ano(jogo) < get_ano(raiz->jogo);
}

static bool jogoEhMaior(const NODE *raiz, JOGO *jogo) {
    return get_ano(jogo) > get_ano(raiz->jogo);
}

static bool jogoEhIgual(const NODE *raiz, JOGO *jogo) {
    return get_ano(jogo) == get_ano(raiz->jogo);
}

static bool DesbalanceamentoEhPositivo(NODE *raiz) {
    return avl_altura_no(raiz->esquerda)
               - avl_altura_no(raiz->direita) == 2;
}

static bool DesbalanceamentoEhNegativo(NODE *raiz) {
    return avl_altura_no(raiz->esquerda)
               - avl_altura_no(raiz->direita) == -2;
}

boolean avl_inserir(AVL *arvore, JOGO* jogo) {
    arvore->raiz = avl_inserir_no_e_rotacionar(arvore->raiz, jogo);
    return arvore->raiz != NULL;
}

void pre_ordem_rec(NODE* raiz) {
    if(raiz != NULL) {
        printf("%s\n", get_titulo(raiz->jogo));
        pre_ordem_rec(raiz->esquerda);
        pre_ordem_rec(raiz->direita);
    }
}

void em_ordem_rec(NODE* raiz) {
    if(raiz != NULL) {
        em_ordem_rec(raiz->esquerda);        
        printf("%s\n", get_titulo(raiz->jogo));
        em_ordem_rec(raiz->direita);
    }
}

void pos_ordem_rec(NODE* raiz) {
    if(raiz != NULL ) {
        pos_ordem_rec(raiz->esquerda);
        pos_ordem_rec(raiz->direita);
        printf("%s\n", get_titulo(raiz->jogo));
    }
}

void pre_ordem(AVL* arvore) {
    if(arvore != NULL) {
        pre_ordem_rec(arvore->raiz);    
    }
}

void em_ordem(AVL* arvore) {
    if(arvore != NULL) {      
        em_ordem_rec(arvore->raiz); 
    }
}   

void pos_ordem(AVL* arvore) {
    if(arvore != NULL){
        pos_ordem_rec(arvore->raiz);    
    }
}

NODE *busca(NODE* raiz, int ano) {
    if (raiz == NULL || get_ano(raiz->jogo) == (ano)){
      return raiz;
    }
    
    if (get_ano(raiz->jogo) <(ano))
       return busca(raiz->direita, ano);
 
    return busca(raiz->esquerda, ano);
}

NODE* remocao(NODE *raiz, JOGO* jogo) {
    raiz = avl_deletar_no_e_rotacionar(raiz, jogo);
    return raiz;
}

void remocao_auxiliar(AVL *arvore, int ano) {
    if(arvore != NULL) {
        NODE *raiz = arvore->raiz;
        NODE *to_be_removed = busca(raiz, ano);

        while(to_be_removed != NULL) {
            raiz = remocao(raiz, to_be_removed->jogo);
            to_be_removed = busca(raiz, ano); 
        }
    }
}

NODE *full_esquerda(NODE *node) {
    while (node->esquerda != NULL)
        node = node->esquerda;

    return node;
}

NODE* recursivo_delete_node(NODE *raiz, JOGO *jogo) {
    if (raiz == NULL)
      return raiz;

    if (get_ano(jogo) < get_ano(raiz->jogo))
        raiz->esquerda = recursivo_delete_node(raiz->esquerda, jogo);

    else if (get_ano(jogo) > get_ano(raiz->jogo))
        raiz->direita = recursivo_delete_node(raiz->direita, jogo);

    else {

        if (raiz->esquerda == NULL) {
            NODE *new_raiz = raiz->direita;
            free(raiz);
            // printf("free 4");
            return new_raiz;
        }

        else if (raiz->direita == NULL) {
            NODE *new_raiz = raiz->esquerda;
            free(raiz);
            // printf("free 5");
            return new_raiz;
        }

        NODE *new_raiz = full_esquerda(raiz->direita);

        JOGO *tmp = raiz->jogo;

        raiz->jogo = new_raiz->jogo;

        raiz->direita =  recursivo_delete_node(raiz->direita, new_raiz->jogo);
 
        apagar_jogo(&tmp);
    }
    return raiz;
} 

static NODE *avl_deletar_no_e_rotacionar(NODE *raiz, JOGO *jogo) {
    raiz = recursivo_delete_node(raiz, jogo);

    raiz->altura = max(avl_altura_no(raiz->esquerda),
                       avl_altura_no(raiz->direita)) + 1;

    raiz = selecionar_e_executar_rotacao(raiz, jogo);

    return raiz;
}