#include <stdlib.h>
#include "stack.h"

int main ()
{
    ST st = {};

    STACKINIT(st, START_SIZE_OF_STACK);

    // (5 - (3 + 3 * 4)) / 2 --> -5

    StackPush(&st, 2);
    StackPush(&st, 5);
    StackPush(&st, 3);
    StackPush(&st, 3);
    StackPush(&st, 4);
    Multi(&st);
    Add(&st);
    Sub(&st);
    Div(&st);

    int number = 0;

    Out(&st, &number);

    StackDelete(&st);

    return 0;
}
