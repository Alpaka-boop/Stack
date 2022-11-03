#include <assert.h>

#include "errors.h"

const char *errors_descr[] = {"The stack data pointer is null",
                             "The stack size is less than the stack capacity",
                             "Memory was not allocated",
                             "A value was not pushed because memory was not allocated"};

void Verificator (ST *st, int line, const char *fun, const char *file)
{
    assert(st);

    int errors = 0;

    if (st->data == NULL)
    {
        STACKINIT(*st, START_SIZE_OF_STACK);
        errors += ERR_NULL_DATA;
    }

    if (st->capacity < st->size)
    {
        errors += ERR_OVERSIZE;
        // st->data = (elem_t *) realloc(st->data, st->size + 1);

        // if (!st->data)
        //     errors += ERR_ALL_MEM;
        // else 
        //     st->capacity = st->size + 1;
    }

    if (errors)   
        ErrorPrinter(errors, line, fun, file);
}

int near_deg_2 (int num)
{
    int deg = 0;
    int tmp = 1;
    
    while (num > tmp)
    {
        tmp *= 2;
        deg++;
    }
    
    return deg;
}

void ErrorPrinter (int errors, int line, const char *fun, const char *file)
{
    FILE *log_file = NULL;
    bool is_first = true;

    log_file = fopen(LOGFILENAME, "w+");

    fprintf(log_file, "%s: %s: %i: errors:", file, fun, line);
    
    for (int i = 0; i < near_deg_2(errors); ++i)
    {
        if ((errors & (1 << (i + 1))) >> (i + 1))
        {
            if (is_first)
            {
                fprintf(log_file, " %s", errors_descr[i - 1]);
                is_first = false;
            }

            else 
            {
                fprintf(log_file, ", %s", errors_descr[i - 1]);
            }
        }
    }

    fprintf(log_file, "\n");

    fclose(log_file);
}
