#include <include/filemanger.h>
#include <include/consoleIO.h>

int main()
{

    ti_file_t *file = (ti_file_t*)malloc(sizeof(ti_file_t)); 
    char* data = "what";
    create_file(&file,"hello",data);
    return 0;
}