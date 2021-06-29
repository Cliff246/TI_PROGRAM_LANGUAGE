#ifndef _MEMORY_H
#define _MEMORY_H

#include <stdint.h>
#include <stdlib.h>
#include <tice.h>

#include "titypes.h"


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
}

#endif e