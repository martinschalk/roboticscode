/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */


#include <project.h>
#include "global.h"
#include <stdio.h>

#include "hal.h"
#include "bpl.h"

/* Ring buffers */
static uint8 	ReceiveBuffer[RX_BUFFER_SIZE];	//RB
static uint8 	TransmitBuffer[TX_BUFFER_SIZE];	//TB
static uint8 	ReceiveCount = 0;
static uint8 	TransmitCount = 0;

static uint8* 	RBHead = ReceiveBuffer;
static uint8* 	RBTail = ReceiveBuffer;
static uint8* 	TBHead = TransmitBuffer;
static uint8* 	TBTail = TransmitBuffer;

static STATUS BplStatus = BPL_STATUS_OK;

/*******************************************************/
void BPL_HandleTask(void)
{
	uint8 numBytes;
	
	/* Handle received bytes */
	/* --------------------- */
	while ((HAL_GetRxIsrCount() > 0) && (BplStatus == BPL_STATUS_OK))
	{
		/* check for buffer overflow */
		if (RBHead++ > RBTail)
		{
			BplStatus = BPL_STATUS_RX_BUFFER_FULL;
			break;
		}
		/* check if passing end of ring buffer */
		if (++RBHead == &ReceiveBuffer[RX_BUFFER_SIZE])
		{
			RBHead = &ReceiveBuffer[0];
		}

		/* copy byte from rx buffer to ring buffer */
		*RBHead = HAL_GetByte();
		ReceiveCount++;	
	}

	
	/* Handle transmission of bytes */
	/* ---------------------------- */
	if ((TransmitCount > 0) && (BplStatus == BPL_STATUS_OK))
	{
		numBytes = *TBTail; //message length
		
		/* check for buffer overflow */
		if (TBTail + numBytes > TBHead)
		{
			BplStatus = BPL_STATUS_TX_DATA_MISMATCH;
		}
		else
		{
			/* transmit byte */
			BplStatus = HAL_TransmitArray(TBTail, numBytes);
			TBTail += + numBytes;
		}
	}
	
	
	/* Handle errors */
	/* ------------- */
	switch (BplStatus)
	{
		case BPL_STATUS_RX_BUFFER_FULL:		RBHead = RBTail = ReceiveBuffer;
											ReceiveCount = 0;
											break;
		case BPL_STATUS_TX_DATA_MISMATCH:	TBHead = TBTail = TransmitBuffer;
											TransmitCount = 0;
											break;
		default:							break;
	}
}

/* [] END OF FILE */
