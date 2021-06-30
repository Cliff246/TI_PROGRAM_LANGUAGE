#pragma once

#include <stdint.h>

typedef struct ti_file ti_file_t;

struct ti_file;

ti_file_t* new_file(char* name);

ti_file_t* open_file(char* name);

void close_file(ti_file_t* file);

char* read_file(ti_file_t* file,uint16_t count);

void write_file(ti_file_t* file,char* write,uint32_t size);