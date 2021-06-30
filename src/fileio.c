#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <fileioc.h>

#include "include/types.h"
#include "include/compare.h"

#define CHUNKSIZE 8

typedef struct ti_file ti_file_t;
struct ti_file
{
    ti_var_t file_ptr;
    char file_mode[3];
    char file_name[];
};

ti_file_t* new_file(char* name)
{
    if(name != NULL)
    {
        ti_var_t var_file = ti_Open(name,"w+");
        ti_file_t* wrap_file = (ti_file_t*)malloc(sizeof(ti_file_t) + strlen(name+1));
        if(var_file != 0 && wrap_file != NULL)
        {
            wrap_file->file_ptr = var_file;
            strcpy(wrap_file->file_mode,"w+");
            strcpy(wrap_file->file_name,name);
            return wrap_file;
        }
    }
    os_ThrowError(-1);
    return NULL;
}

ti_file_t* open_file(char* name)
{
    if(name != NULL)
    {
        ti_var_t var_file = ti_Open(name,"r+");
        ti_file_t* wrap_file = (ti_file_t*)malloc(sizeof(ti_file_t) + strlen(name+1));
        if(var_file != 0 && wrap_file != NULL)
        {
            wrap_file->file_ptr = var_file;
            strcpy(wrap_file->file_mode,"r+");
            strcpy(wrap_file->file_name,name);
            
            return wrap_file;
        }
    }
    os_ThrowError(-1);
    return NULL;
}

void close_file(ti_file_t* file)
{
    if(file != NULL)
    {
        ti_Close(file->file_ptr);
        free(file);
        file = NULL;
    }
    os_ThrowError(-1);
    return;
}

char* read_file(ti_file_t* file,uint16_t count)
{
    if(file != NULL)
    {
        char* mallowed[] = {"r+","w+","a+"};
        if(contain_string(file->file_mode,mallowed,3) == false)
            return NULL;
        if(count > ti_GetSize(file->file_ptr))
            os_ThrowError(-1);
        char* data = (char*)malloc(count);
        if(data != NULL)
        {
            ti_Read(data,CHUNKSIZE,count,file->file_ptr);
            return data;
        }
    }   
    os_ThrowError(-1);
    return NULL;
}

void write_file(ti_file_t* file,char* write,uint32_t size)
{
    if(write != NULL || file == NULL)
    {
        char* mallowed[] = {"r+","w+","a+"};
        if(contain_string(file->file_mode,mallowed,3) == false)
            return NULL;
        if(size > ti_GetSize(file->file_ptr))
            os_ThrowError(-1);
        ti_Write(write,CHUNKSIZE,size,file->file_ptr);
        return;
    }
    os_ThrowError(-1);
    return;
}