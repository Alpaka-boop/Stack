#include <stdlib.h>
#include "stack.h"

int main ()
{
    ST st = {};

    STACKINIT(st, START_SIZE_OF_STACK);

    for (int i = 0; i < 100; ++i)
    {
        StackPush(&st, i);
    }

    for (int i = 0; i < 50; ++i)
    {
        int value = 0;

        StackPop(&st, &value);
    }
    
    StackDelete(&st);

    return 0;
}
