#ifndef ERRORS_H
#define ERRORS_H

#include "stack.h"

#define LOGFILENAME "Log.txt"


enum ERROR_NUM{
    ERR_NULL_DATA = 1 << 0,
    ERR_OVERSIZE  = 1 << 1, 
    ERR_ALL_MEM   = 1 << 2,
    ERR_PUSH_MEM  = 1 << 3
};

void Verificator     (ST *st, int line, const char *fun, const char *file);
void ErrorPrinter    (int errors, int line, const char *fun, const char *file);

#endif 
