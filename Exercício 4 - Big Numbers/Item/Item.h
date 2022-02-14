#ifndef ITEM_H
#define ITEM_H

#include "../Util/Util.h"

#define ERRO (-32000)

typedef struct item_st ITEM;
ITEM *item_criar (const char *operacao, long long int valor1, long long int valor2);
ITEM *item_ler_std_in();
void item_calcular(const ITEM *item);
boolean item_apagar(ITEM **item);

#endif //ITEM_H
