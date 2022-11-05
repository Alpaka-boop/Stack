#include <assert.h>

#include "errors.h"

const char *errors_descr[] = {"The stack data pointer is null",
                             "The stack size is less than the stack capacity",
                             "Memory was not allocated",
                             "A value was not pushed because memory was not allocated", 
                             "The capacity of the stack is 0",
                             "The stack size is less than 0",
                             "No elements in the stack to pop",
                             "There are few elements in the stack to do some operations",
                             "Try to devide by 0 was made"};

void Verificator (ST *st, int line, const char *fun, const char *file)
{
    assert(st);

    CHECK_ERR(st->data == NULL, ERR_NULL_DATA);

    CHECK_ERR(st->capacity < st->size, ERR_OVERSIZE);
    
    CHECK_ERR(st->size < 0, ERR_MINUS_SIZE)

    if (st->errors != 0 && st->errors_status != WAS_DUMPED)
    {
        StackDump(st, file, fun, line);
        st->errors_status = WAS_DUMPED;
    }
}

void ErrorPrinter (int errors, int line, const char *fun, const char *file)
{
    FILE *log_file = NULL;
    int   err_num  = 0;

    log_file = fopen(LOGFILENAME, "a");
    assert(log_file);
    
    while (errors > 0)
    {
        if (errors % 2)
            fprintf(log_file, "%s: %s: %i: error: %s\n", file, fun, line, errors_descr[err_num]);

        errors /= 2;
        err_num++;
    }

    fprintf(log_file, "\n");

    fclose(log_file);
}

void StackDump (ST *st, const char *curr_file, const char *curr_fun, int curr_line)
{
    FILE *file = nullptr;

    file = fopen(LOGFILENAME, "a");

    fprintf(file, "=======================================================\n");
    fprintf(file, "%s: %s: %i:\n", curr_file, curr_fun, curr_line);
    fprintf(file, "Stack info:\n");
    fprintf(file, "\tCapacity: %lu\n", st->capacity);
    fprintf(file, "\tSize: %lu\n", st->size);
    fprintf(file, "\tErrors: %lu\n", st->errors);
    fprintf(file, "\tVariable info:\n");
    fprintf(file, "\t\tFile: %s\n", st->var_info.file_name);
    fprintf(file, "\t\tFunc: %s\n", st->var_info.func_name);
    fprintf(file, "\t\tLine: %i\n", st->var_info.line_num);
    fprintf(file, "\t\tName: %s\n", st->var_info.var_name);
    fprintf(file, "=======================================================\n\n");

    fclose(file);
}
