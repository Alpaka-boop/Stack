#include <assert.h>
#include <stdlib.h>

#include "errors.h"
#include "stack.h"

size_t StackInit (ST *st, size_t capacity, const char *var_name, const char *func_name, const char *file_name, int line_num)
{
    assert(st);

    CHECK_ERR(capacity == 0, ERR_NULL_CAP);

    st->size = 0;
    st->data = (elem_t *) calloc(capacity, sizeof(elem_t));
    st->capacity = capacity * (st->data != NULL);
    st->errors_status = NO_ERRORS;

    CHECK_ERR(st->data == NULL, ERR_ALL_MEM);

    st->var_info.file_name = file_name;
    st->var_info.func_name = func_name;
    st->var_info.line_num  = line_num;
    st->var_info.var_name  = var_name;

    CHECK(st);

    return st->errors;
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
            CHECK_ERR(st->size >= st->capacity, ERR_PUSH_MEM);
    }

    CHECK(st);

    return st->errors;
}

size_t StackResize(ST *st)
{
    assert(st);
    if (st->capacity == 0)
    {
        if (st->data == NULL)
        {
            st->data = (elem_t *) calloc(START_SIZE_OF_STACK, sizeof(elem_t));
            CHECK_ERR(st->data == NULL, ERR_ALL_MEM);
            st->capacity = START_SIZE_OF_STACK * (st->data != NULL);
        }
        else
        {
            st->data = (elem_t *) realloc(st->data, START_SIZE_OF_STACK);
            CHECK_ERR(st->data == NULL, ERR_ALL_MEM);
            st->capacity = START_SIZE_OF_STACK * (st->data != NULL);
        }
    }

    else if (st->size >= st->capacity)
    {
        st->data = (elem_t *) realloc(st->data, st->capacity * 4);

        CHECK_ERR(st->data == NULL, ERR_ALL_MEM);
        
        if (st->data != NULL)
            st->capacity *= 4;
    }

    else if (st->size < st->capacity / 2)
    {
        st->data = (elem_t *) realloc(st->data, st->capacity / 2 + 1);

        CHECK_ERR(st->data == NULL, ERR_ALL_MEM);

        if (st->data != NULL)
            st->capacity = st->capacity / 2 + 1;
    }

    return st->errors;
}

size_t StackPop (ST *st, elem_t *value)
{
    CHECK(st);

    CHECK_ERR(st->size == 0, ERR_NO_EL);

    if (st->data != NULL && st->size >= 1)
    {
        *value = st->data[st->size - 1];
        st->data[st->size - 1] = DELITED_NUM;
        st->size--;
    }

    CHECK(st);
    StackResize(st);

    return st->errors;
}

size_t StackDelete (ST *st)
{
    CHECK(st);

    if (st->data != NULL)
    {
        st->size = 0;
        free(st->data);
        st->capacity = 0;
    }

    return st->errors;
}

size_t Add (ST *st)
{
    CHECK(st);
    CHECK_ERR(st->size < 2, ERR_FEW_ELL);
    
    if (st->size > 1 && st->data != NULL)
    {
        int num1 = 0;
        int num2 = 0;

        StackPop(st, &num1);
        StackPop(st, &num2);
        StackPush(st, num1 + num2);
    }

    CHECK(st);
    StackResize(st);

    return st->errors;
}

size_t Sub (ST *st)
{
    CHECK(st);
    CHECK_ERR(st->size < 2, ERR_FEW_ELL);
    
    if (st->size > 1 && st->data != NULL)
    {
        int num1 = 0;
        int num2 = 0;

        StackPop(st, &num1);
        StackPop(st, &num2);
        StackPush(st, num1 - num2);
    }

    CHECK(st);
    StackResize(st);

    return st->errors;
}

size_t Multi (ST *st)
{
    CHECK(st);
    CHECK_ERR(st->size < 2, ERR_FEW_ELL);
    
    if (st->size > 1 && st->data != NULL)
    {
        int num1 = 0;
        int num2 = 0;

        StackPop(st, &num1);
        StackPop(st, &num2);
        StackPush(st, num1 * num2);
    }

    CHECK(st);
    StackResize(st);

    return st->errors;
}

size_t Div (ST *st)
{
    CHECK(st);
    CHECK_ERR(st->size < 2, ERR_FEW_ELL);
    
    if (st->size > 1 && st->data != NULL)
    {
        int num1 = 0;
        int num2 = 0;

        StackPop(st, &num1);
        StackPop(st, &num2);

        CHECK_ERR(num1 == 0, ERR_DIV_NULL);

        if (num1 != 0)
        {
            StackPush(st, num1 / num2);
        }
        else
        {
            StackPush(st, num2);
            StackPush(st, num1);
        }
    }

    StackResize(st);
    CHECK(st);

    return st->errors;
}

size_t Out (ST *st, int *value)
{
    CHECK(st);
    
    size_t errors = StackPop(st, value);

    if (errors == 0)
        printf("Last number in the stack: %i\n", *value);

    CHECK(st);

    return st->errors;
}
