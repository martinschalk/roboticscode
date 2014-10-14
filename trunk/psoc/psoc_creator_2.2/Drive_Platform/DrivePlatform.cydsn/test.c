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
#include "hal.h"
#include "bal.h"

#define TST_MSG_BUFFER_SIZE     0xFF
#define TST_MSG_ZERO_COUNT      5

static uint8    TST_MsgBuffer[TST_MSG_BUFFER_SIZE];

/*
-------------------------------------------
| id0 | id1 | length | b0 | b1 | ... | bn |
-------------------------------------------
*/
/*******************************************************/
static void TST_SendTestMsg(void)
{
//#define UART_TEST_MSG
//#define BAL_TEST_MSG

#if defined(UART_TEST_MSG)
    static uint8 TestMsg[] = {0xFF, 0x01, 5, 2, 3, 0, 4, 5};
    
    UART_TEST_PutArray(TestMsg, sizeof(TestMsg));
#elif defined(BAL_TEST_MSG)
    STATUS status; 
    uint8 msgdata[4] = {1, 2, 3, 4};
    
    BAL_MSG testmsg = {0x0001, 4, msgdata};
    status = BAL_SendMsg(&testmsg);
    (void)status;
#endif
}

/*******************************************************/
static void TST_GetMsg(void)
{
    int i=0, count=0;
    BOOL motorMsg=FALSE;
    
    do
    {
        TST_MsgBuffer[i] = UART_TEST_GetChar();
        
        if (TST_MsgBuffer[i] == 0x00)
            count++;
        else
        {
            /* check if message beginns with 0xFF 0xFF */    
            if ((TST_MsgBuffer[i] == 0xFF) && (i>0))
            {
                if (TST_MsgBuffer[i-1] == 0xFF)
                {
                    motorMsg = TRUE;
                }
            }
        }
        i++;
    } while (i<TST_MSG_ZERO_COUNT);
      
}

/*******************************************************/
static void TST_Blink(void)
{
    static uint8 LedVal=0x00;
	LedVal ^= 0x01;
	DEBUG_LED_1_Write(LedVal);
}

/*******************************************************/
static void TST_SendMotorMsg(void)
{
    STATUS status; 

    Ping(0x01);
    
    (void)status;
}

/*******************************************************/
void TST_Init(void)
{
    /* clear test msg buffer */
    memset(TST_MsgBuffer, 0x00, TST_MSG_BUFFER_SIZE);
    

#ifdef TEST_BLINK
	TMR_SetTimer(TIMER_0, TIMER_1SEC, TST_Blink, TIMER_MODE_CONTINUOUS, TIMER_ENABLED);
#endif	
	
#ifdef TEST_UART
	UART_TEST_Start();
	//UART_TEST_EnableRxInt();
	//UART_TEST_EnableTxInt();
	//TMR_SetTimer(TIMER_1, TIMER_1SEC, TST_SendTestMsg, TIMER_MODE_CONTINUOUS, TIMER_ENABLED);
    TMR_SetTimer(TIMER_2, TIMER_1SEC, TST_SendMotorMsg, TIMER_MODE_CONTINUOUS, TIMER_ENABLED);
#endif
}

/*******************************************************/
void TST_HandleTask(void)
{
    /* analyze received messages */
    TST_GetMsg();
}

/* [] END OF FILE */
