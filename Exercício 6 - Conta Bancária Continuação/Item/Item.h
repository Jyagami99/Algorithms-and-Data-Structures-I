#ifndef ITEM_H
#define ITEM_H

#define ERRO (-32000)
#define TRUE 1
#define FALSE 0

typedef int boolean;
typedef struct item_st ITEM;

ITEM* item_criar(unsigned long cpf, char* nome, int idade, double saldo);
ITEM* cadastra_item(char* line);
char* get_string();
unsigned long get_cpf(ITEM *item);
void imprimir_cpf(ITEM *item);
void imprimir_item(ITEM *item, char* cpf);

#endif