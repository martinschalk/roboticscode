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
#include "ring_buffer.h"

// buffers
static uint8_t 	BPL_aucReceiveBuffer[BPL_RX_BUFFER_SIZE];
static uint8_t 	BPL_aucTransmitBuffer[BPL_TX_BUFFER_SIZE];

static uint8_t  BPL_ucReceiveBufferIndex;
static uint8_t  BPL_ucTransmitBufferIndex;

/*
static STATUS BplStatus = BPL_STATUS_OK;
*/

/*******************************************************/
STATUS BPL_Init(void)
{
    //register buffers as ring buffers
    BPL_ucReceiveBufferIndex = RBF_ucRegisterBuffer(BPL_aucReceiveBuffer, BPL_RX_BUFFER_SIZE);
    BPL_ucTransmitBufferIndex = RBF_ucRegisterBuffer(BPL_aucTransmitBuffer, BPL_TX_BUFFER_SIZE);
    
    return SUCCESS;	
}


/*******************************************************/
uint8 BPL_GetReceiveMsgCount(void)
{
    return RBF_ucGetByteCount(BPL_ucReceiveBufferIndex);
}

/*******************************************************/
uint8 BPL_GetMessage(uint8* target)
{
    STATUS rbfStatus;
    uint8_t ucNumBytes;
    
    if (RBF_ucGetMsgCount(BPL_ucReceiveBufferIndex) == 0)
        return 0;
    
    rbfStatus = RBF_ucTailMsgOut(BPL_ucReceiveBufferIndex, target, &ucNumBytes);
    
    return ucNumBytes;
}

/*******************************************************/
/**
    Example:    Transmit servo message "CDS5500_INST_PING"
    
        BAL message                              BPL message:
        
        SB0  SB1  MID  LEN  INID PAR CHKS        LEN  SRC                           LEN
        ---------------------------------   ==>  ---------------------------------------
        0xFF 0xFF 0x01 0x02 0x01 -   0xFB        0x06 0xFF 0xFF 0x01 0x02 0x01 0xFB 0x06
    
        -> msgLength = 6
*/
STATUS BPL_TransmitMessage(uint8* source, uint8 msgLength)
{
    STATUS rbfStatus;
    
    // read message into ring buffer
    rbfStatus = RBF_ucMsgIn(BPL_ucTransmitBufferIndex, source, msgLength);

    return rbfStatus;	
}

/*******************************************************/
STATUS BPL_HandleTask(void)
{
    STATUS rbfStatus, BplStatus;
	uint8_t ucNumBytes;
    uint8_t ucByte;
	uint8_t ucMessageBuffer[BPL_MAX_MESSAGE_LENGTH];
    
	/* Handle received bytes */
	/* --------------------- */
	while (HAL_GetRxIsrCount() > 0)
	{
        ucByte = HAL_GetByte();
        rbfStatus = RBF_ucByteIn(BPL_ucReceiveBufferIndex, ucByte);
        
		if (rbfStatus != RBF_SUCCESS)
		{
			//error handling
		}
	}

	
	/* Handle transmission of bytes */
	/* ---------------------------- */
    if (RBF_ucGetMsgCount(BPL_ucTransmitBufferIndex) > 0)
    {
        rbfStatus = RBF_ucTailMsgOut(BPL_ucTransmitBufferIndex, ucMessageBuffer, &ucNumBytes);
        
        // LENGTH | CONTENT | LENGTH
		BplStatus = HAL_TransmitArray(&ucMessageBuffer[0], ucNumBytes);
            
        if (rbfStatus != RBF_SUCCESS)
		{
			//error handling
		}
	}
	
    
    return BplStatus;
}

/*****************************************************************/
/*****************************************************************/
#ifdef BPL_MODULE_TEST

void BPL_ucTest(void)
{
    STATUS status;
    static uint8_t x = 1;
    static uint8_t msg[] = {0x05, 0x06, 0x07, 0x08, 0x09};
    
    if (x)
    {
        status = BPL_TransmitMessage(msg, 5);
    }
}

#endif //BPL_MODULE_TEST


/* [] END OF FILE */
