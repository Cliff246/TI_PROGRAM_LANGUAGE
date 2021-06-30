#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <tice.h>

#include "include/titypes.h"

void* allocate_more(void* rptr,int24_t size)
{
    if(rptr != NULL)
    {
        void* temp = realloc(rptr,size);
        if(temp != NULL)
        {
            rptr = temp;
            return rptr;
        }
    }
    os_ThrowError(-1);
    return NULL;
}
