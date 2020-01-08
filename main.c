#include "isam.c"
#include <stdio.h>



int main()
{   
    puts("-----PROGRAM START-----");
    ISAM DB = new_ISAM("test", 19, 11);
    puts("-----PROGRAM END-----");
    return 0;
}