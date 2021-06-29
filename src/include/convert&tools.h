#pragma once


#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "include/titypes.h"

/* A utility function to reverse a string */
void reverse(char *buffer, uint16_t length)
{
    if(buffer == NULL)
        return;
    for(uint16_t start = 0,end = length-1;start < end;start++,end--)
    {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
    }
}


// Implementation of itoa()
int32_t itoa_32(char** buffer,int32_t num, uint8_t base,uint16_t rdecimal)
{
	int32_t i = 0;
	bool negative = false;
	if (num == 0)
	{
		(*buffer)[i++] = '0';
		(*buffer)[i] = '\0';
        return 0;
	}

	if (num < 0 && base == 10)
	{
		negative = true;
		num = -num;
	}

	while (num != 0)
	{
		int rem = num % base;
		(*buffer)[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
		num /= base;
	}

    while(i < rdecimal)
    {
        (*buffer)[i++] = '0';
    }

	if(negative == true)
    {
		(*buffer)[i++] = '-';
    }
    (*buffer)[i] = '\0'; 
	reverse(*buffer, i);

    return i;
}

/*
i dont know copy right law but this was taken from Anton Gusev (github)antongus
https://github.com/antongus/stm32tpl/blob/master/ftoa.c
I am really sorry dude 
*/


//ftoa 
char* ftoa_32(char* buffer,float num)
{
    float precision = 0.000005f;
	char* buf_ptr = buffer, *buf_p_x2 = buf_ptr,*buf_p_x3;
    int32_t int_p;

    if(num < 0)
    {
        num = -num;
        *buf_ptr++ = '-';
    }

    num += precision;
    int_p = (int32_t)num;
    num -= (float)int_p;

    if(!int_p)
        *buf_ptr++ = '0';
    else
    {
        buf_p_x2 = buf_ptr;
        while(int_p > 0)
        {
            *buf_p_x2 = '0' + int_p % 10;
            int_p /= 10;
        }

        buf_p_x3 = buf_p_x2;
        char character;

        while(buf_p_x2 > buf_ptr)
        {
            character = *--buf_p_x2;
            *buf_p_x2 = *buf_ptr;
            *buf_ptr++ = character;
        }

        buf_ptr = buf_p_x3;

        // place decimal point
		*buf_ptr++ = '.';

		// convert
		for(;precision > 0;precision--)
		{
			num *= 10.0;
			character = num;
			*buf_ptr++ = '0' + character;
			num -= character;
		}
    }
    *buf_ptr = 0;
    return buffer;
}

