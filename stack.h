#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <sys/types.h>

typedef int elem_t;

struct VAR_INFO {
    const char *var_name;
    const char *func_name;
    const char *file_name;
    int         line_num;
};

typedef struct STACK {
    size_t size;
    elem_t *data;
    size_t capacity;
    size_t code_of_errror;
    size_t errors;
    //int left_canary;
    //int right_canary;
    VAR_INFO var_info;
} ST;

#define DELITED_NUM 30

const int START_SIZE_OF_STACK = 30;

#define CHECK(st) Verificator(st, __LINE__, __func__, __FILE__)
#define STACKINIT(st, capacity) StackInit(&st, capacity, #st, __FUNCTION__, __FILE__, __LINE__)

void   StackInit   (ST *st, size_t capacity, const char *var_name, const char *func_name, const char *file_name, int line_num);
size_t StackPush   (ST *st, int value);
int    StackPop    (ST *st, elem_t *value);
void   StackDelete (ST *st);
int    StackResize (ST *st);
void   Add         (ST *st);
void   Sub         (ST *st);
void   Div         (ST *st);
int    Out         (ST *st);

#endif 
