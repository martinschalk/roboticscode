/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#include <project.h>
#include "global.h"
#include "error.h"
#include <stdio.h>



static ERR_VAR Var[ERR_NUM_VARIABLES];



/*****************************************************************/
void ERR_Error(uchar type)
{
    switch(type)
    {
        case ERROR_CRITICAL:        
                                    break;

        case ERROR_MEMORY:          
                                    break;
                                    
        case ERROR_WARNING:         return;
                                    break;
                                    
        case ERROR_DEBUG:           return;
                                    break;                                    
                                    
        default:                    break;                            
    }
    
    while(1)
    {
        /* do nothing */
    }
}


/*****************************************************************/
STATUS ERR_Init(void)
{  
    memset(Var, 0x00, sizeof(Var));
    return SUCCESS; 
}


/*****************************************************************/
uchar ERR_RegisterVariable(const tErrVar* ptrVar, const char* name, const tErrVar min, const tErrVar max)
{  
    uchar idx = 0;
    
    /* search for free index */
    while ((Var[idx].addr != NULL) && (idx < ERR_NUM_VARIABLES))
    {
        idx++;
    }
    
    /* if free index available, save variable pointer */
    if (idx < ERR_NUM_VARIABLES)
    {
        Var[idx].addr = ptrVar;  
        strncpy(Var[idx].name, name, 8);
        Var[idx].min = min;
        Var[idx].max = max;
    }
    /* if not return !SUCCESS */
    else
    {
        idx = !SUCCESS;
    }
    
    return idx;
}


/*****************************************************************/
STATUS ERR_HandleTask(void)
{
    uchar idx = 0;
    volatile tErrVar val;
    
    /* check variables */
    while ((Var[idx].addr != NULL) && (idx < ERR_NUM_VARIABLES))
    {
        val = *(Var[idx].addr);
        if ((val < Var[idx].min) || (val > Var[idx].max))
        {
            ERR_Error(ERROR_MEMORY);
        }
        idx++;
    }

    return SUCCESS;
}