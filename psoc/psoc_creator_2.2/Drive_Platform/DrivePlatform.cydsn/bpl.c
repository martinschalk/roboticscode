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
#include "servo_cds5500.h"


// buffers
static uint8_t 	BPL_aucReceiveBuffer[BPL_RX_BUFFER_SIZE];
static uint8_t 	BPL_aucTransmitBuffer[BPL_TX_BUFFER_SIZE];

static uint8_t  BPL_ucReceiveBufferIndex;
static uint8_t  BPL_ucTransmitBufferIndex;

static uint8_t  BPL_CDS5500_ucRxMessageCount = 0;
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
uint8_t BPL_CDS5500_ucGetRxMessageCount(void)
{
    return BPL_CDS5500_ucRxMessageCount;
}

/*******************************************************/
void BPL_CDS5500_ucSetRxMessageCount(uint8_t ucVal)
{
    BPL_CDS5500_ucRxMessageCount = ucVal;
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
Status packet:
| 0XFF | 0XFF | ID | Length | Status | Parameter1 ...Parameter N | Check Sum | 
*/
STATUS BPL_CDS5500_GetResponse(CDS5500_MSG* targetAddr)
{
    STATUS rbfStatus, bplStatus;
    CDS5500_MSG msg;
    uint8_t ucTempChecksum;
    uint8_t ucNumBytes = RBF_ucGetByteCount(BPL_ucReceiveBufferIndex);
    int i;
    
    // First check if any bytes received
    if ((ucNumBytes == 0) || (ucNumBytes < CDS5500_STATUS_PACKET_MIN_LENGTH))
        return BPL_STATUS_RX_ERROR;
    
    rbfStatus = RBF_ucTailByteOut(BPL_ucReceiveBufferIndex, &(msg.startbyte0)); //FF
    rbfStatus = RBF_ucTailByteOut(BPL_ucReceiveBufferIndex, &(msg.startbyte1)); //FF
    rbfStatus = RBF_ucTailByteOut(BPL_ucReceiveBufferIndex, &(msg.motorId));    //ID
    rbfStatus = RBF_ucTailByteOut(BPL_ucReceiveBufferIndex, &(msg.length));     //Length
    rbfStatus = RBF_ucTailByteOut(BPL_ucReceiveBufferIndex, &(msg.instrId));    //Status
    
    for (i=0; i<msg.length-CDS5500_COMPLEMENTARY_BYTES; i++)
    {
        rbfStatus = RBF_ucTailByteOut(BPL_ucReceiveBufferIndex, &(msg.instrParams[i]));    //Parameter1 ...Parameter N  
    }
    
    rbfStatus = RBF_ucTailByteOut(BPL_ucReceiveBufferIndex, &(msg.checksum));    //checksum
    
    ucTempChecksum = CDS5500_GetChecksum(&msg);
        
    if (rbfStatus != RBF_SUCCESS)
    {
        //better clear whole buffer now, something went wrong ...
        rbfStatus = RBF_ucClearBuffer(BPL_ucReceiveBufferIndex);
        BPL_CDS5500_ucRxMessageCount--;
        ERR_Error(ERROR_WARNING);
        bplStatus = !SUCCESS;
    }
    else 
    {
        // decrease message count
        BPL_CDS5500_ucRxMessageCount--;
        
        *targetAddr = msg;
        
        if (ucTempChecksum == msg.checksum)
        {
            bplStatus = BPL_SUCCESS;
        }
        else
        {
            bplStatus = BPL_STATUS_RX_ERROR; // wrong checksum
        }
    }
   
    
    return bplStatus;
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
    uint8_t ucStartByte1, ucStartByte2;
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

    // Check if (complete) CDS5500 message received
    // --------------------------------------------
    if (RBF_ucGetByteCount(BPL_ucReceiveBufferIndex) >= CDS5500_STATUS_PACKET_MIN_LENGTH)
    {
        rbfStatus = RBF_ucReadOnlyFromTail(BPL_ucReceiveBufferIndex, &ucStartByte1, 0);
        rbfStatus |= RBF_ucReadOnlyFromTail(BPL_ucReceiveBufferIndex, &ucStartByte2, 1);
        rbfStatus |= RBF_ucReadOnlyFromTail(BPL_ucReceiveBufferIndex, &ucNumBytes, 3);
        
        if (        (ucStartByte1 == 0xFF) && (ucStartByte2 == 0xFF) 
                &&  (RBF_ucGetByteCount(BPL_ucReceiveBufferIndex) >= (ucNumBytes + 4)) //(0XFF 0XFF ID Length)
           )
        {
            BPL_CDS5500_ucRxMessageCount++; //Message can now be picked up using BPL_CDS5500_GetResponse()
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
