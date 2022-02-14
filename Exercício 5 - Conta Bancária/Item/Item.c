#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Item.h"
#include "../Arvore/Arvore.h"

struct item_st{
  unsigned long cpf;
  char nome[40];
  int idade;
  double saldo;
};

ITEM* item_criar(unsigned long cpf, char* nome, int idade, double saldo);
unsigned long convert_to_int(char* str);

char* get_string(){
  char *linha = calloc(1024, sizeof(char));

  scanf(" %[^(\r|\n)]*c", linha);

  return linha;
}

unsigned long get_cpf(ITEM *item) {
  return item->cpf;
}

unsigned long convert_str_int(char* str){
	if(str != NULL) {
    char cpf[12];
    int i, j;
    
    for(i=0, j=0; i<15; i++){
      if(str[i] != '.' && str[i] != '-'){
        cpf[j] = str[i];
        j++;
      }
    }

    unsigned long cpf_num = convert_to_int(cpf);
        
    return cpf_num;
	}

	return -1;
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

unsigned long convert_to_int(char* str){
  unsigned long result = 0;
  unsigned long multiplier = 1;
  int i, tam = strlen(str); 

  for(i = tam -1 ; i >= 0 ; i--){
    result = result + ((int)str[i] -48)*multiplier;
    multiplier = multiplier*10;
  }

  return result;
}

void imprimir_cpf(ITEM *item){
  printf("%lu\n", item->cpf);
}