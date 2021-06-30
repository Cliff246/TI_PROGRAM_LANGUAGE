#pragma once

typedef struct ti_file ti_file_t;

struct ti_file;

ti_file_t* new_file(char* name);

ti_file_t* open_file(char* name);

void close_file(ti_file_t* file);