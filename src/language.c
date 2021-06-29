#include <include/filemanger.h>
#include <include/consoleIO.h>

int main()
{
    ti_file_t *file = new_file("hello",NULL);
    
    ti_print_out_s("%s","hello there");
    return 0;
}