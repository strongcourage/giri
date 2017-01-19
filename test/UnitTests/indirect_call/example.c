#include <stdio.h>
#include <stdlib.h>

#include "call.h"

int main(int argc, char *argv[])
{
    int x = 10; 
    int y = 5;
    void(*indirect_call)(int, int);
    if (argc == 2) {
        indirect_call = &foo;
    } else {
        indirect_call = &bar;
    }
    indirect_call(x, y);
    return 0;
}
