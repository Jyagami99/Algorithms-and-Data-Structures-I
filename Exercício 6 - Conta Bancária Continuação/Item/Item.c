#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Item.h"
#include "../Arvore/Arvore.h"
#include "../Util/Util.h"

struct item_st{
  unsigned long cpf;
  char nome[40];
  int idade;
  double saldo;
};

ITEM* item_criar(unsigned long cpf, char* nome, int idade, double saldo);

char* get_string(){
  char *linha = calloc(1024, sizeof(char));

  scanf(" %[^(\r|\n)]*c", linha);

  return linha;
}

unsigned long get_cpf(ITEM *item) {
  return item->cpf;
}


ITEM* cadastra_item(char* linha) {
	if(linha != NULL) {

    char* split = strtok(linha, ";");
    char* cpf_str = (char*) malloc(strlen(split)+1);
    strcpy(cpf_str, split);
    unsigned long cpf = convert_str_int(cpf_str);        

    split = strtok(NULL, ";");
    char* nome = (char*) malloc(strlen(split)+1);
    strcpy(nome, split);

    split = strtok(NULL, ";");
    char* idade_str = (char*) malloc(strlen(split));
    strcpy(idade_str, split);
    int idade = atoi(idade_str);

    split = strtok(NULL, ";");
    char *saldo_str = (char*) malloc(strlen(split));
    strcpy(saldo_str, split);
    char *ptr;
    double saldo = strtod(saldo_str, &ptr);

    ITEM *item = item_criar(cpf, nome, idade, saldo);

    return item;
  }

  return NULL;
}

ITEM* item_criar(unsigned long cpf, char* nome, int idade, double saldo){
	ITEM* item;
	item = (ITEM*) malloc(sizeof(ITEM));

	item->cpf = cpf;
	strcpy(item->nome, nome);
	item->idade = idade;
	item->saldo = saldo;

	return item;
}

void imprimir_cpf(ITEM *item){
  printf("%011lu\n", item->cpf);
}

void imprimir_item(ITEM *item, char* cpf){
  printf("Conta :: %s\n", item->nome);
  printf("CPF :: %s\n", cpf);
  printf("Idade :: %d\n", item->idade);
  printf("Saldo atual :: R$ %.2f\n", item->saldo);
}