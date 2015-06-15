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
#include "ring_buffer.h"

#define TST_MSG_BUFFER_SIZE     32
#define TST_MSG_ZERO_COUNT      5


//static TEST_FUNC TST_FuncPtr = NULL;


//static uchar    TST_TestCase;
//static BOOL     TST_IsInitialized = FALSE;
static uint8 TST_MsgBuffer[TST_MSG_BUFFER_SIZE];

static uint8 TST_AckOkMsgBuffer[] = {   (uint8)(BAL_MSG_ID_ACK << 8), 
                            (uint8)(BAL_MSG_ID_ACK),
                            BAL_MSG_LENGTH_ACK, 
                            BAL_ACK_OK
                        };
/*
-------------------------------------------
| id0 | id1 | length | b0 | b1 | ... | bn |
-------------------------------------------
*/
/*******************************************************/
/*
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
*/

/*******************************************************/
/*
static void TST_GetMsg(void)
{
    uint8 i=0;
    STATUS status;
    BOOL motorMsg=FALSE;
    
    // disable rx interrupt during data processing
    UART_TEST_DisableRxInt();
    
    status = UART_TEST_ReadRxStatus();
    
    // if buffer full, parse for 0xff 0xff (only for testing)
    if ((status == UART_RX_STS_OVERRUN) || (status == UART_RX_STS_SOFT_BUFF_OVER))
    {
        while (UART_TEST_GetRxBufferSize() > 0)
        {
            TST_MsgBuffer[i] = UART_TEST_ReadRxData();
            if ((TST_MsgBuffer[i] == 0xFF) && (i>0) && (TST_MsgBuffer[i-1] == 0xFF))
                motorMsg = TRUE;
            i++;
        }
    }
        
    // enable rx interrupt during data processing
    UART_TEST_EnableRxInt();  
    

    // check if message id is registered and acknowledge
    if (motorMsg == TRUE)
    {
        UART_TEST_PutArray(TST_AckOkMsgBuffer, sizeof(TST_AckOkMsgBuffer));
    }
}
*/

/*******************************************************/
static void TST_Blink(void)
{
    static uint8 LedVal=0x00;
	LedVal ^= 0x01;
	DEBUG_LED_1_Write(LedVal);
}

/*******************************************************/
/*
static void TST_SendMotorMsg(void)
{
    STATUS status; 

    Ping(0x01);
    
    (void)status;
}
*/

/*******************************************************/
/*
void TST_SetModuleTest(TEST_FUNC* testFunction)
{
    TST_FuncPtr = testFunction;
    //TMR_SetTimer(TIMER_4, TIMER_1SEC, TST_FuncPtr, TIMER_MODE_CONTINUOUS, TIMER_ENABLED);
}
*/

/*******************************************************/
STATUS TST_Init(void)
{
    /* clear test msg buffer */
    //memset(TST_MsgBuffer, 0x00, TST_MSG_BUFFER_SIZE);   

#ifdef TEST_BLINK
	TMR_SetTimer(TIMER_0, TIMER_1SEC, TST_Blink, TIMER_MODE_CONTINUOUS, TIMER_ENABLED);
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
