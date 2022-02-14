#ifndef UTIL_H
#define UTIL_H

#define ERRO (-32000)
#define TRUE 1
#define FALSE 0
typedef int boolean;

const char* boolean_print(boolean bool);
unsigned long convert_str_int(char* str);

#endif //UTIL_H