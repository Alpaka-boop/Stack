#include <assert.h>

#include "errors.h"
#include "stack.h"

void StackInit (ST *st, size_t capacity, const char *var_name, const char *func_name, const char *file_name, int line_num)
{
    assert(st);

    //TODO fill var info
    //TODO FILL CAPACITY
    st->size = 0;
    st->data = (elem_t *) calloc(capacity, sizeof(elem_t));
    st->capacity = capacity;
    

    st->var_info.file_name = file_name;
    st->var_info.func_name = func_name;
    st->var_info.line_num  = line_num;
    st->var_info.var_name  = var_name;

    CHECK(st);
}

size_t StackPush (ST *st, int value)
{
    CHECK(st);

    if (st->size < st->capacity)
        st->data[st->size++] = value;
    else 
    {
        StackResize(st);

        if (st->size < st->capacity)
            st->data[st->size++] = value;
        else 
            st->errors |= ERR_PUSH_MEM;
    }

    CHECK(st);

    return st->errors;
}

int StackResize(ST *st)
{
    if (st->size >= st->capacity)
    {
        st->data = (elem_t *) realloc(st->data, st->capacity * 4);
        
        if (st->data != NULL)
            st->capacity *= 4;
    }
    else if (st->size < st->capacity / 2)
    {
        st->data = (elem_t *) realloc(st->data, st->capacity / 2 + 1);

        if (st->data != NULL)
            st->capacity = st->capacity / 2 + 1;
    }

    return st->capacity;
}

//TODO add check if empty
//todo return by pointer
//TODO ewerywhere return code_of_error

int StackPop (ST *st, elem_t *value)
{
    CHECK(st);
    
    int errors = 0;

    *value = st->data[st->size];

    st->data[st->size] = DELITED_NUM;
    st->size--;

    CHECK(st);
    StackResize(st);

    return errors;
}

//add recapacity :2 при попе *4 при пуше dump in 2 functions sump var info dump 

void StackDelete (ST *st)
{
    CHECK(st);

    st->size = 0;
    free(st->data);
    st->capacity = 0;
}

void Add (ST *st)
{
    CHECK(st);
    
    int num1 = 0;
    int num2 = 0;

    StackPop(st, &num1);
    StackPop(st, &num2);
    StackPush(st, num1 + num2);

    CHECK(st);
}

void Sub (ST *st)
{
    CHECK(st);

    int num1 = 0;
    int num2 = 0;

    StackPop(st, &num1);
    StackPop(st, &num2);
    StackPush(st, num2 - num1);

    CHECK(st);
}

void Div (ST *st)
{
    CHECK(st);
    
    int num1 = 0;
    int num2 = 0;

    StackPop(st, &num1);
    StackPop(st, &num2);
    StackPush(st, num2 / num1);

    CHECK(st);
}

int Out (ST *st)
{
    CHECK(st);

    int value = 0;
    
    StackPop(st, &value);

    printf("Last number in the stack: %i\n", value);

    CHECK(st);

    return value;
}
