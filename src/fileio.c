#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <tice.h>

typedef struct ti_file ti_file_t;
struct ti_file
{
    ti_var_t file_var;
    char file_mode[3];
    char file_name[];
};