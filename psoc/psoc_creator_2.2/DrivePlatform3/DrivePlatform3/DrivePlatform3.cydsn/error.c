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



static ERR_UC_VAR UcVar[ERR_NUM_UC_VARIABLES];
static ERR_UI_VAR UiVar[ERR_NUM_UI_VARIABLES];
//static ERR_UL_VAR UlVar[ERR_NUM_UL_VARIABLES];

/*****************************************************************/
void ERR_Error(uchar type)
{
    switch(type)
    {
        case ERROR_CRITICAL:        while(1)
                                    {
                                        /* do nothing */
                                    }
                                    break;

        case ERROR_MEMORY:          
                                    break;
                                    
        case ERROR_WARNING:         return;
                                    break;
                                    
        case ERROR_DEBUG:           return;
                                    break;                                    
                                    
        default:                    break;                            
    }
    
    
}


/*****************************************************************/
STATUS ERR_Init(void)
{  
    memset(UcVar, 0x00, sizeof(UcVar));
    memset(UiVar, 0x00, sizeof(UcVar));
    //memset(UlVar, 0x00, sizeof(UcVar));
    
    return SUCCESS; 
}


/*****************************************************************/
uchar ERR_RegisterUcVariable(const uint8* ptrUcVar, const char* name, const uint8 min, const uint8 max)
{  
    uchar idx = 0;
    
    /* search for free index */
    while ((UcVar[idx].ucAddr != NULL) && (idx < ERR_NUM_UC_VARIABLES))
    {
        idx++;
    }
    
    /* if free index available, save variable pointer */
    if (idx < ERR_NUM_UC_VARIABLES)
    {
        UcVar[idx].ucAddr = (uint8*)ptrUcVar;
        strncpy((char*)UcVar[idx].ucName, name, ERR_NAME_LENGTH);
        UcVar[idx].ucMin = min;
        UcVar[idx].ucMax = max;
    }
    /* if not return !SUCCESS */
    else
    {
        idx = !SUCCESS;
    }
    
    return idx;
}

/*****************************************************************/
uchar ERR_RegisterUiVariable(const uint16* ptrUiVar, const char* name, const uint16 min, const uint16 max)
{  
    uchar idx = 0;
    
    /* search for free index */
    while ((UiVar[idx].uiAddr != NULL) && (idx < ERR_NUM_UI_VARIABLES))
    {
        idx++;
    }
    
    /* if free index available, save variable pointer */
    if (idx < ERR_NUM_UI_VARIABLES)
    {
        UiVar[idx].uiAddr = (uint16*)ptrUiVar;
        strncpy((char*)UiVar[idx].ucName, name, ERR_NAME_LENGTH);
        UiVar[idx].uiMin = min;
        UiVar[idx].uiMax = max;
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
    uint8 ucVal;
    uint16 uiVal;
    
    /* check uc variables */
    while ((UcVar[idx].ucAddr != NULL) && (idx < ERR_NUM_UC_VARIABLES))
    {
        ucVal = *(UcVar[idx].ucAddr);
        if ((ucVal < UcVar[idx].ucMin) || (ucVal > UcVar[idx].ucMax))
        {
            ERR_Error(ERROR_MEMORY);
        }
        idx++;
    }
    
    /* check ui variables */
    while ((UiVar[idx].uiAddr != NULL) && (idx < ERR_NUM_UI_VARIABLES))
    {
        uiVal = *(UiVar[idx].uiAddr);
        if ((uiVal < UiVar[idx].uiMin) || (uiVal > UiVar[idx].uiMax))
        {
            ERR_Error(ERROR_MEMORY);
        }
        idx++;
    }

    return SUCCESS;
}