#ifndef ERRORS_H
#define ERRORS_H

#include "stack.h"

#define LOGFILENAME "Log.txt"
#define ERR_DUMP(error_code) ErrorPrinter(error_code, __LINE__, __FUNCTION__, __FILE__);\
                             if (st->errors != (st->errors | error_code))\
                             {\
                                st->errors |= error_code;\
                                st->errors_status = NEW;\
                             }\

#define CHECK_ERR(condition, error_code) if(condition) {ERR_DUMP(error_code)}

enum ERROR_NUM {
    ERR_NULL_DATA  = 1 << 0,
    ERR_OVERSIZE   = 1 << 1, 
    ERR_ALL_MEM    = 1 << 2,
    ERR_PUSH_MEM   = 1 << 3,
    ERR_NULL_CAP   = 1 << 4,
    ERR_MINUS_SIZE = 1 << 5,
    ERR_NO_EL      = 1 << 6,
    ERR_FEW_ELL    = 1 << 7,
    ERR_DIV_NULL   = 1 << 8
};

enum ERRORS_STATUS {
    NO_ERRORS,
    NEW,
    WAS_DUMPED
};

void Verificator  (ST *st, int line, const char *fun, const char *file);
void ErrorPrinter (int errors, int line, const char *fun, const char *file);
void StackDump    (ST *st, const char *curr_file, const char *curr_fun, int curr_line);

#endif 
