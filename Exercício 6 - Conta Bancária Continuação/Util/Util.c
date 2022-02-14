#include <stdio.h>
#include <string.h>
#include "Util.h"

const char* boolean_print(boolean bool)
{
    if(bool == TRUE)
    {
        return "True";
    }
    else if(bool == FALSE)
    {
        return "False";
    }
    else
    {
        return "ERRO";
    }
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