#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Util.h"
#include "../Item/Item.h"

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