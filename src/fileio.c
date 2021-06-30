#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <tice.h>
#include <fileioc.h>

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

}