#include <stdio.h>
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