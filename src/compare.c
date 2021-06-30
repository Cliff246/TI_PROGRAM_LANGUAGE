#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "include/types.h"

bool contain_string(char* key,char* index[],uint8_t size)
{
    for(uint8_t i = 0;i < size;i++)
    {
        if(strcmp(key,index[i]) == 0)
            return true;
    }
    return false;
}