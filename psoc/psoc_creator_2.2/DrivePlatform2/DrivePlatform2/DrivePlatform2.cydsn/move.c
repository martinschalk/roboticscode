/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */
 
#include <project.h>
#include <stdio.h>
#include "types.h"
#include "move.h"
#include "servo_cds5500.h"

//#include "bal.h"
#include "global.h"
//#include "tmr.h"

//static CDS5500_STATUS Servo1;



/*****************************************************************/
STATUS MOV_Init(void)
{
    return SUCCESS;
}

/*****************************************************************/
STATUS MOV_HandleTask(void)
{
    STATUS balStatus;

    return balStatus;
}

/*****************************************************************/
/*****************************************************************/
#ifdef MOV_MODULE_TEST

void MOV_ucTest(void)
{
    STATUS status;
    static uint8_t x = 1;
    
    if (x)
    {
        CDS5500_Ping(CDS5500_SERVO_1);
    }
}

#endif //BPL_MODULE_TEST
