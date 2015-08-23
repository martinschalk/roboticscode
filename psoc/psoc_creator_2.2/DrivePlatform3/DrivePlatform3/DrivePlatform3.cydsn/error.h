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

    #define ERR_NUM_UC_VARIABLES        5
    #define ERR_NUM_UI_VARIABLES        5
    //#define ERR_NUM_UL_VARIABLES        5
    #define ERR_NAME_LENGTH             8

    //typedef unsigned int tErrVar;

    typedef struct _error_uc_variable
    {
        uint8*    ucAddr;
        uchar     ucName[ERR_NAME_LENGTH];
        uint8     ucMax;
        uint8     ucMin;
    }ERR_UC_VAR;

    typedef struct _error_ui_variable
    {
        uint16*   uiAddr;
        uchar     ucName[ERR_NAME_LENGTH];
        uint16    uiMax;
        uint16    uiMin;
    }ERR_UI_VAR;
    /*
    typedef struct _error_ul_variable
    {
        uint32*   ulAddr;
        uchar     ucName[ERR_NAME_LENGTH];
        uint32    ulMax;
        uint32    ulMin;
    }ERR_UL_VAR;
    */

    STATUS  ERR_Init(void);
    STATUS  ERR_HandleTask(void);
    void    ERR_Error(uchar type);
    uchar   ERR_RegisterUcVariable(const uint8* ptrUcVar, const char* name, const uint8 min, const uint8 max);
    uchar   ERR_RegisterUiVariable(const uint16* ptrUiVar, const char* name, const uint16 min, const uint16 max);
#else

    #define ERROR(x)

#endif /* ERROR_MODULE_ENABLE */

#endif /* ERROR_H */