#ifndef ITEM_H
#define ITEM_H

#define ERRO (-32000)
#define TRUE 1
#define FALSE 0

typedef int boolean;

typedef struct item_st ITEM;

char* get_string();
unsigned long get_cpf(ITEM *item);
void le_linha();
ITEM* cadastra_item(char* line);
ITEM* item_criar(unsigned long cpf, char* nome, int idade, double saldo);
void imprimir_cpf(ITEM *item);

#endif