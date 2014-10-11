/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#include "bus.h"
#include <project.h>
#include "global.h"
#include <stdio.h>

#if(0)

static uint8 TransmitBuffer[BUS_MSG_BUFFER_SIZE];
static uint8 ReceiveBuffer[BUS_MSG_BUFFER_SIZE];

BUS_OBJ Bus;

/*****************************************************************/
STATUS BUS_Init(void)
{
	Bus.transmit.tBuffer = TransmitBuffer;
	Bus.transmit.tBytes = 0;
	Bus.transmit.tRequest = FALSE;
	Bus.transmit.tInProgress = FALSE;
	Bus.receive.rBuffer = ReceiveBuffer;
	Bus.receive.rBytes = 0;
	Bus.receive.rNewMsg = FALSE;
	Bus.receive.rInProgress = FALSE;
	
	return SUCCESS;
}

/*****************************************************************/
static STATUS BUS_Transmit(void)
{
	STATUS status;
	int i=0;
	uint8 tStatus;
	
	while ((i<BUS_MSG_BUFFER_SIZE) && (i<Bus.transmit.tBytes))
	{
		while (UART_TX_STS_COMPLETE != UART_ReadTxStatus())
		;
		
		UART_WriteTxData(Bus.transmit.tBuffer[i]);
		i++;
	}
	
	if (i != Bus.transmit.tBytes - 1)
		status = BUS_LENGTH_ERROR;
	else
		status = SUCCESS;
	
	return status;
}

//todo: replace by isr
/*****************************************************************/
static STATUS BUS_Receive(void)
{
	STATUS status;
	int i=0;
	
	Bus.receive.rInProgress = TRUE;
	
	//Returns the number of received bytes remaining in the RX buffer and returns the count in bytes
	Bus.receive.rBytes = UART_GetRxBufferSize();
	
	while (Bus.receive.rBytes != 0)
	{
		Bus.receive.rBuffer[i] = UART_ReadRxData(); // Returns the next byte of received data.
		Bus.receive.rBytes --;
	}
	
	Bus.receive.rInProgress = FALSE;
	
	if (i != Bus.receive.rBytes - 1)
		status = BUS_LENGTH_ERROR;
	else
		status = SUCCESS;
	
	return status;
}

/*****************************************************************/
STATUS BUS_Handler(void)
{
	STATUS status;
	
	if ((Bus.transmit.tRequest == TRUE) && (Bus.receive.rInProgress == FALSE))
	{
		if (SUCCESS == BUS_Transmit())
			Bus.transmit.tRequest = FALSE;
	}
	
	if (Bus.receive.rNewMsg == TRUE)
	{
		if (SUCCESS == BUS_Receive())
			Bus.receive.rNewMsg = FALSE;
	}
	
	return status;
}

#endif

/* [] END OF FILE */
