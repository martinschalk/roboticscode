/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#ifndef ERROR_H
#define ERROR_H

#include "types.h"

#define ERROR_MODULE_ENABLE

#ifdef ERROR_MODULE_ENABLE

    #define ERROR(x)   ERR_Error(x)

    #define ERROR_CRITICAL      (uchar)(-1)
    #define ERROR_MEMORY        (uchar)(-2)
    #define ERROR_WARNING       (uchar)(-3)
    #define ERROR_DEBUG         (uchar)(-4)

    #define ERR_NUM_VARIABLES   5

    typedef unsigned int tErrVar;

    typedef struct _error_variable
    {
        tErrVar*    addr;
        uchar       name[8];
        tErrVar     max;
        tErrVar     min;
    }ERR_VAR;


    STATUS ERR_Init(void);
    STATUS ERR_HandleTask(void);
    uchar ERR_RegisterVariable(const tErrVar* ptrVar, const char* name, const tErrVar min, const tErrVar max);

#else

    #define ERROR(x)

#endif /* ERROR_MODULE_ENABLE */

#endif /* ERROR_H */