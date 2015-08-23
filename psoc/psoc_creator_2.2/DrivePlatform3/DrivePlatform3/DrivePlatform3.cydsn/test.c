/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#include "global.h"
#include "types.h"
#include "test.h"
#include "tmr.h"
#include "bpl.h"
#include "hal.h"
#include "bal.h"
#include "move.h"
#include "ring_buffer.h"
#include "servo_cds5500.h"

#define TST_MSG_BUFFER_SIZE     32
#define TST_MSG_ZERO_COUNT      5


/*******************************************************/
static void TST_Blink(void)
{
    static uint8 LedVal=0x00;
	LedVal ^= 0x01;
	DEBUG_LED_1_Write(LedVal);
}


/*******************************************************/
STATUS TST_Init(void)
{
    /* clear test msg buffer */
    //memset(TST_MsgBuffer, 0x00, TST_MSG_BUFFER_SIZE);   

#ifdef TEST_BLINK
	TMR_SetTimer(TIMER_0, TIMER_1SEC, TST_Blink, TIMER_MODE_CONTINUOUS, TIMER_ENABLED);
#endif	

#ifdef BPL_MODULE_TEST
    TMR_SetTimer(TIMER_1, 5*TIMER_1SEC, BPL_ucTest, TIMER_MODE_CONTINUOUS, TIMER_ENABLED);
#endif

#ifdef BAL_MODULE_TEST
    TMR_SetTimer(TIMER_4, TIMER_1SEC, BAL_ModuleTest, TIMER_MODE_CONTINUOUS, TIMER_ENABLED);
#endif

#ifdef MOV_MODULE_TEST
    TMR_SetTimer(TIMER_5, 3*TIMER_1SEC, MOV_ucTest, TIMER_MODE_CONTINUOUS, TIMER_ENABLED);
#endif


    return SUCCESS;
}

/*******************************************************/
STATUS TST_HandleTask(void)
{
    STATUS status = SUCCESS;
    
#ifdef RBF_MODULE_TEST
    status = RBF_ucTest();
#endif
    
    return status;
}

/* [] END OF FILE */
