#pragma once

#include <tice.h>
#include <fileioc.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "include/tistring.h"

//you could adjust this but dont. dealing with character array is just easier.
#define CHUNKSIZE 8

typedef struct ti_file ti_file_t;

struct ti_file
{
    ti_var_t ti_var_file;
    char ti_mode[3];
    char ti_file_name[];
};

ti_file_t* ti_open_file(char* file_name,char* file_mode) 
{
    //custom wrapper for open file 
    if(file_name == NULL || file_mode == NULL)
        return 0;
    uint16_t size_name = strlen(file_name);
    ti_file_t *file_object = (ti_file_t*)calloc(1,sizeof(ti_file_t) + size_name);
    if(file_object != NULL)
    {
        ti_var_t temp = ti_Open(file_name,file_mode);

        if(temp == 0)
            os_ThrowError(-1);

        file_object->ti_var_file = temp; 
        
        void* mode_cpy = memcpy(file_object->ti_mode,file_mode,3);
        void* name_cpy = memcpy(file_object->ti_file_name,file_name,size_name);

        if(mode_cpy == NULL || name_cpy == NULL)
            os_ThrowError(-1);
        return file_object;
    }
    os_ThrowError(-1);
    return NULL;
}

char* pull_file(ti_file_t* file)
{
    //free memory afterwords 
    //pull data from file
    if(file != NULL)
    {   
        /*goto is dangerous but quote this if i am wrong.
         every thing that could is in the scope of the goto is on the stack so it should be fine? 
         even if it did cause a memory leak then who cares its only a few bytes :)*/
        char* pmodes[4] = {"r","r+","w+","a+"};
        file_reset:
        if(compare_strings(file->ti_mode,pmodes,4) == 0)
        {
            uint16_t isize = ti_GetSize(file->ti_var_file);
            char* data = (char*)malloc(isize);
            if(data == NULL || file->ti_var_file == 0)
                os_ThrowError(-1);
            else
            {
                size_t rsize = ti_Read(data,CHUNKSIZE,isize,file->ti_var_file);
                if(rsize == isize)
                    return data;
                else
                    os_ThrowError(-1);
            }
        }
        else
        {
            ti_Close(file->ti_var_file);
            ti_var_t reset = ti_Open(file->ti_file_name,"r+");
            if(reset == 0)
                os_ThrowError(-1);
            else
            {
                void* copy = strcpy(file->ti_mode,"r+");
                if(copy == NULL)
                    os_ThrowError(-1);
                else
                {
                    file->ti_var_file = reset;
                    //super scary
                    goto file_reset;
                }
            }
        }
    }
    os_ThrowError(-1);
    return NULL;
}

void write_file(ti_file_t *file,char* data)
{

    if(file == NULL || data == NULL)
        os_ThrowError(-1);
    else
    {
        char* pmode[5] = {"w","a","r+","w+","a+"};
        file_reset:
        if(compare_strings(file->ti_mode,pmode,5) == 0)
        {
            uint16_t isize = ti_GetSize(file->ti_var_file);
            if(file->ti_var_file == 0)
                os_ThrowError(-1);
            else
            {
                uint16_t rsize = ti_Write(data,CHUNKSIZE,isize,file->ti_var_file);
                if(rsize == isize)
                    return;
                else
                    os_ThrowError(-1);
            }
        }
        else
        {
            ti_Close(file->ti_var_file);
            ti_var_t reset = ti_Open(file->ti_file_name,"w+");
                if(reset == 0)
                    os_ThrowError(-1);
                else
                {
                    void* copy = strcpy(file->ti_mode,"w");
                    if(copy == NULL)
                        os_ThrowError(-1);
                    else
                    {
                        file->ti_var_file = reset;
                        //super scary
                        goto file_reset;
                    }
                }
        }
    }
}

void create_file(ti_file_t **rfile,char* name,char* data)
{
    /*create file
    //rfile is if you want to MAKE and GET the file
    leave rfile NULL if you only want to create*/
    if(name == NULL || data == NULL)
        os_ThrowError(-1);
    ti_var_t new_file = ti_Open(name,"w");
    if(new_file != 0)
    {
        size_t isize = strlen(data);
        size_t rsize = ti_Write(data,CHUNKSIZE,isize+1,new_file);
        if(isize == rsize && rsize != 0)
        {
            if(rfile != NULL)
            {
                size_t name_size = strlen(name);
                ti_file_t *temp = (ti_file_t*)realloc(*rfile,sizeof(ti_file_t) + name_size);
                if(temp != NULL && *rfile != NULL) 
                {
                    *rfile = temp;

                    //using memcpy because we already have the length of name
                    void* name_cpy = memcpy((*rfile)->ti_file_name,name,name_size);
                    void* mode_cpy = strcpy((*rfile)->ti_mode,"w");

                    (*rfile)->ti_var_file = new_file;

                    if(name_cpy == NULL || mode_cpy == NULL)
                        os_ThrowError(-1);
                    return;
                }
                free(temp);
            }
            else
                return;
        }
    }
    os_ThrowError(-1);
}

void close_file(ti_file_t* file)
{
    //close and free a file
    if(file != NULL)
    {
        ti_Close(file->ti_var_file);
        free(file);
        file = NULL;
    }
    else
        os_ThrowError(-1);
}

ti_file_t* new_file(char* name,char* data)
{
    if(name != NULL && data != NULL)
    {
        ti_file_t* file = (ti_file_t*)malloc(sizeof(ti_file_t)); 
        if(file != NULL)
        {
            create_file(&file,name,data);
            return file;
        }
    }
    os_ThrowError(-1);
    return NULL;
}