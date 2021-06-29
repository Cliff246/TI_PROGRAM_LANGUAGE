#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

char compare_strings(char* key,char** string,uint8_t length)
{
    for(uint8_t i = 0; i < length;i++)
    {
        uint24_t cmp = strcmp(key,string[i]);
        if(cmp != 0)
            return cmp;
    }
    return 0;

}