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
#include "error.h"

/* Ring buffers */
static uint8 	ReceiveBuffer[BPL_RX_BUFFER_SIZE];	//RB
static uint8 	TransmitBuffer[BPL_TX_BUFFER_SIZE];	//TB
static uint8 	ReceiveMsgCount = 0;
static uint8 	TransmitMsgCount = 0;
//static uint8    ReceiveBytesCount = 0;
static uint8    TransmitBytesCount = 0;

static uint8* 	RBHead = ReceiveBuffer;
static uint8* 	RBTail = ReceiveBuffer;
static uint8* 	TBHead = TransmitBuffer;
static uint8* 	TBTail = TransmitBuffer;

static STATUS BplStatus = BPL_STATUS_OK;


/*******************************************************/
STATUS BPL_Init(void)
{
#if defined(BPL_DEBUG) && defined(ERROR_MODULE_ENABLE)
    uchar idx1 = ERR_RegisterUcVariable(&TransmitBytesCount, "TraByCnt", 0, 10);
    (void)idx1;
#endif

    return SUCCESS;	
}


/*******************************************************/
uint8 BPL_GetReceiveMsgCount(void)
{
    return ReceiveMsgCount;	
}

/*******************************************************/
uint8 BPL_GetMessage(uint8* target)
{
    uint8 msgLength;
    
    /* check if messages in pipe */
    if (ReceiveMsgCount==0)
        return 0;
    
    /* get message length and copy data to target */
    msgLength = RBTail[0];
    memcpy(target, RBTail+1, msgLength);
    
    /* update parameters */
    RBTail += msgLength + 1;
    ReceiveMsgCount--;	
    
    return msgLength;
}

/*******************************************************/
/**
    Example:    Transmit servo message "CDS5500_INST_PING"
    
        BAL message                              BPL message:
        
        SB0  SB1  MID  LEN  INID PAR CHKS        LEN  SRC
        ---------------------------------   ==>  ----------------------------------
        0xFF 0xFF 0x01 0x02 0x01 -   0xFB        0x06 0xFF 0xFF 0x01 0x02 0x01 0xFB 
    
        -> msgLength = 6
*/
STATUS BPL_TransmitMessage(uint8* source, uint8 msgLength)
{
    /* check if message fits in transmit buffer */
    if (TransmitBytesCount + msgLength + 1 > BPL_TX_BUFFER_SIZE)
        return BPL_STATUS_TX_BUFFER_FULL;

    /* copy message to transmit buffer, 1st byte = message bytes */
    TBHead[0] = msgLength;
    memcpy(&TBHead[1], source, msgLength); //TODO: Error found! ring buffer overflow
    
    /* update parameters */
    TBHead += msgLength + 1;
    TransmitBytesCount += msgLength + 1;
    TransmitMsgCount++;

    return SUCCESS;	
}

/*******************************************************/
STATUS BPL_HandleTask(void)
{
	uint8 numBytes;
	
	/* Handle received bytes */
	/* --------------------- */
	while ((HAL_GetRxIsrCount() > 0) && (BplStatus == BPL_STATUS_OK))
	{
		/* check for buffer overflow */
		if (RBHead+1 == RBTail)
		{
			BplStatus = BPL_STATUS_RX_BUFFER_FULL;
			break;
		}
		/* check if passing end of ring buffer */
		if (++RBHead == &ReceiveBuffer[BPL_RX_BUFFER_SIZE])
		{
			RBHead = &ReceiveBuffer[0];
		}

		/* copy byte from rx buffer to ring buffer */
		*RBHead = HAL_GetByte();
		ReceiveMsgCount++;	
	}

	
	/* Handle transmission of bytes */
	/* ---------------------------- */
	if ((TransmitMsgCount > 0) && (BplStatus == BPL_STATUS_OK))
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
			BplStatus = HAL_TransmitArray(TBTail+1, numBytes);
            
            /* check if message could be sent */
            if (BplStatus == SUCCESS)
            {
    			TBTail += numBytes+1;
                if (TransmitBytesCount < numBytes+1)
                    ERROR(ERROR_DEBUG);
                TransmitBytesCount -= numBytes+1;
                TransmitMsgCount--;
            }
		}
	}
	
	
	/* Handle errors */
	/* ------------- */
	switch (BplStatus)
	{
		case BPL_STATUS_RX_BUFFER_FULL:		RBHead = RBTail = ReceiveBuffer;
											ReceiveMsgCount = 0;
											break;
		case BPL_STATUS_TX_DATA_MISMATCH:	TBHead = TBTail = TransmitBuffer;
											TransmitMsgCount = 0;
											break;
		default:							break;
	}
    
    return BplStatus;
}

/* [] END OF FILE */
