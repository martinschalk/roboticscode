/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#include "global.h"
#include "types.h"
#include "tmr.h"
#include "hal.h"



static uint8 TestMsg[] = {0, 1, 2, 3, 0, 4, 5, 6, 7, 0};

/*******************************************************/
void TST_SendTestMsg(void)
{
	UART_PutArray(TestMsg, 10);
}

/*******************************************************/
void TST_Init(void)
{
#ifdef TEST_UART
	
	UART_TEST_Start();
	//UART_EnableRxInt();
	//UART_EnableTxInt();
	TMR_SetTimer(TIMER_0, TIMER_10SEC, TST_SendTestMsg, TIMER_MODE_CONTINUOUS, TIMER_ENABLED);
#endif
}

/* [] END OF FILE */
