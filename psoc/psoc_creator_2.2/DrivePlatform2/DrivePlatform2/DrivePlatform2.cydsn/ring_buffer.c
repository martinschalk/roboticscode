/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

 
 
 
/** COMMENTS

*/

#include "global.h"
#include "types.h"
#include "ring_buffer.h"
#include <stdio.h>
 

static RING_BUFFER RingBuffer[RBF_NUM];
 
/* ----------------------------------------------------------------- */
/* --------------------- STATIC FUNCTIONS -------------------------- */ 
/* ----------------------------------------------------------------- */
static uint8_t IncHead(uint8_t ucIdx);
static uint8_t DecHead(uint8_t ucIdx);
static uint8_t IncTail(uint8_t ucIdx);
//static uint8_t DecTail(uint8_t ucIdx);

/* ----------------------------------------------------------------- */
/* --------------------- GLOBAL FUNCTIONS -------------------------- */
/* ----------------------------------------------------------------- */
/*****************************************************************/
STATUS RBF_sInit(void)
{
    static int stest = sizeof(RingBuffer);
    (void)stest;
     
    memset(RingBuffer, 0x00, sizeof(RingBuffer));
    
    return SUCCESS;
} 

/*****************************************************************/
uint8_t RBF_ucClearBuffer(uint8_t ucIndex)
{
	STATUS status;

    if ((RingBuffer[ucIndex].address != NULLPTR) && (RingBuffer[ucIndex].size > 1))
	{		
		memset(RingBuffer[ucIndex].address, 0x00, RingBuffer[ucIndex].size);
		RingBuffer[ucIndex].size = 0;
		RingBuffer[ucIndex].head = 0;
		RingBuffer[ucIndex].tail = 0;
		RingBuffer[ucIndex].msgcount = 0;
		
		status = RBF_SUCCESS;
	}
	else
    {
        status = RBF_INVALID_PARAMETERS;
    }
	
	return status;
} 
/*****************************************************************/
uint8_t RBF_ucRegisterBuffer(uint8_t* pucAddr, uint16_t uiSize)
{
    uint8_t ucIndex = 0;
    
    if ((pucAddr != NULLPTR) && (uiSize > 1))
    {
        while (ucIndex < RBF_NUM)
        {
            if (RingBuffer[ucIndex].address == 0)
            {
                RingBuffer[ucIndex].address = pucAddr;
                RingBuffer[ucIndex].size = uiSize;
                RingBuffer[ucIndex].head = 0;
                RingBuffer[ucIndex].tail = 0;
				RingBuffer[ucIndex].msgcount = 0;
                
                memset(RingBuffer[ucIndex].address, 0x00, RingBuffer[ucIndex].size);
                
                break;
            }
            else
            {
                ucIndex++;
            }
        }
        
        if (ucIndex == RBF_NUM)
            ucIndex = RBF_NOT_AVAILABLE;
    }
    else
    {
        ucIndex = RBF_INVALID_PARAMETERS;
    }
    
    
    return ucIndex;
}

/*****************************************************************/
uint8_t RBF_ucUnregisterBuffer(uint8_t ucIndex)
{
    STATUS status;
    
    if (RingBuffer[ucIndex].address)
    {
        RingBuffer[ucIndex].address = 0;
        RingBuffer[ucIndex].size = 0;
        RingBuffer[ucIndex].head = 0;
        RingBuffer[ucIndex].tail = 0;
		RingBuffer[ucIndex].msgcount = 0;
        
        memset(RingBuffer[ucIndex].address, 0x00, RingBuffer[ucIndex].size);
        
        status = RBF_SUCCESS;
    }
    else
    {
        status = RBF_FAIL;
    }
    
    return status;
}
/*****************************************************************/
uint8_t RBF_ucByteIn(uint8_t ucIndex, uint8_t byte)
{
    STATUS status;
	
	if (IncHead(ucIndex) == RBF_SUCCESS)
	{
		(RingBuffer[ucIndex].address)[RingBuffer[ucIndex].head] = byte;
		status = RBF_SUCCESS;
	}
	else
    {
        status = RBF_FAIL;
    }
	
	return status;
}
/*****************************************************************/
uint8_t RBF_ucFirstByteOut(uint8_t ucIndex, uint8_t* byte)
{
    STATUS status;
	
	if (RingBuffer[ucIndex].tail != RingBuffer[ucIndex].head)
	{
		*byte = (RingBuffer[ucIndex].address)[RingBuffer[ucIndex].head];
		(RingBuffer[ucIndex].address)[RingBuffer[ucIndex].head] = 0;		//delete byte
        if (DecHead(ucIndex) == RBF_SUCCESS)
        {
            status = RBF_ERROR;
        }
        else
        {
		    status = RBF_SUCCESS;
        }
	}
	else
	{
		status = RBF_FAIL;
	}
	
	return status;
}
/*****************************************************************/
uint8_t RBF_ucLastByteOut(uint8_t ucIndex, uint8_t* byte)
{
    STATUS status;
	
	if (RingBuffer[ucIndex].tail != RingBuffer[ucIndex].head)
	{
		*byte = (RingBuffer[ucIndex].address)[RingBuffer[ucIndex].tail];
		(RingBuffer[ucIndex].address)[RingBuffer[ucIndex].tail] = 0;		//delete byte
		if (IncTail(ucIndex) == RBF_SUCCESS)
        {
            status = RBF_ERROR;
        }
        else
        {
		    status = RBF_SUCCESS;
        }
	}
	else
	{
		status = RBF_FAIL;
	}
	
	return status;
}
/*****************************************************************/
/**
	Message structure:
	| size | d0 | d1 | ... | dn | size |
	
	- no checksum needed because there is no loss of information 
	due to transmission errors etc.
*/
uint8_t RBF_ucMsgIn(uint8_t ucIndex, uint8_t* msg, uint8_t size)
{
    STATUS status;
	int i=0;
	uint8_t temp;
	
	// 1st byte = message size		
	if(RBF_ucByteIn(ucIndex, size) == RBF_SUCCESS)				// | size | d0 | d1 | ... | dn | size |
	{															//	 ^
		while(i < size)
		{
			if(RBF_ucByteIn(ucIndex, msg[i]) == RBF_SUCCESS)	// | size | d0 | d1 | ... | dn | size |
			{													//	 		^        -->       |
				i++;
			}
			else
			{
				break; //no more bytes or buffer full
			}
		}
		
		// check if message complete
		if (i == size)
		{
			// add message size as last byte
			if(RBF_ucByteIn(ucIndex, size) == RBF_SUCCESS)		// | size | d0 | d1 | ... | dn | size |
			{													//	 							 ^
				RingBuffer[ucIndex].msgcount++;
				status = RBF_SUCCESS;
			}
			else
			{
				while(i >= 0)	// delete already written message bytes plus size byte at beginning
				{
					if(RBF_ucFirstByteOut(ucIndex, &temp) == RBF_FAIL)
					{
						status = RBF_ERROR;
						break;
					}
					i--;
				}
			}
		}
		else
		{
			while(i >= 0)	// delete already written message bytes plus size byte at beginning
			{
				if(RBF_ucFirstByteOut(ucIndex, &temp) == RBF_FAIL)
				{
					status = RBF_ERROR;
					break;
				}
				i--;
			}
		}
		
	}
	else
	{
		status = RBF_FAIL;
	}
	
	return status;
}
/*****************************************************************/
/**
	Example:
	
	| size | d0 | d1 | ... | dn | size | size | d0 | d1 | ... | dn | size |
	  ^																 ^
	  tail															 head
																	 ----
*/
uint8_t RBF_ucFirstMsgOut(uint8_t ucIndex, uint8_t* target, uint8_t* size)
{
    STATUS status;
	int i=0;
	uint8_t temp;
	
	// 1st byte = message size		
	if(RBF_ucFirstByteOut(ucIndex, size) == RBF_SUCCESS)		// | size | d0 | d1 | ... | dn | size |
	{																	//	 							 ^
		if (*size > 0)
		{
			while(i < *size)
			{
				// message data bytes
				if(RBF_ucFirstByteOut(ucIndex, &target[*size-i]) == RBF_SUCCESS)	// | size | d0 | d1 | ... | dn | size |
				{																	//	 	  |			<--		^
					i++;
				}
				else
				{
					*size = 0;
					status = RBF_ERROR;	// this should never happen, buffer must be cleared
					break; 
				}
			}
			
			if (i == *size)
			{
				// get size byte at beginning of message 
				if(RBF_ucFirstByteOut(ucIndex, &temp) == RBF_SUCCESS)	// | size | d0 | d1 | ... | dn | size |
				{														//	 ^
					if (temp == *size)
					{
						RingBuffer[ucIndex].msgcount--;
						status = RBF_SUCCESS;
					}
					else
					{
						*size = 0;
						status = RBF_ERROR;	// this should never happen, buffer must be cleared
					}
				}
			}
			else
			{
				*size = 0;
				status = RBF_ERROR;	// this should never happen, buffer must be cleared
			}	
		}
		else
		{
			*size = 0;
			status = RBF_EMPTY;
		}
	}
	
	
	return status;
}
/*****************************************************************/
/**
	Example:
	
	| size | d0 | d1 | ... | dn | size | size | d0 | d1 | ... | dn | size |
	  ^																 ^
	  tail															 head
	  ----
*/
uint8_t RBF_ucLastMsgOut(uint8_t ucIndex, uint8_t* target, uint8_t* size)
{
    STATUS status;
	int i=0;
	uint8_t temp;
	
	// 1st byte = message size		
	if(RBF_ucLastByteOut(ucIndex, size) == RBF_SUCCESS)		// | size | d0 | d1 | ... | dn | size |
	{																	//	 ^
		if (*size > 0)
		{
			while(i < *size)
			{
				// message data bytes
				if(RBF_ucLastByteOut(ucIndex, &target[i]) == RBF_SUCCESS)	// | size | d0 | d1 | ... | dn | size |
				{															//	 	    ^	   -->		   |
					i++;
				}
				else
				{
					*size = 0;
					status = RBF_ERROR;	// this should never happen, buffer must be cleared
					break; 
				}
			}
			
			if (i == *size)
			{
				// get size byte at beginning of message 
				if(RBF_ucLastByteOut(ucIndex, &temp) == RBF_SUCCESS)	// | size | d0 | d1 | ... | dn | size |
				{														//	 							 ^
					if (temp == *size)
					{
						RingBuffer[ucIndex].msgcount--;
						status = RBF_SUCCESS;
					}
					else
					{
						*size = 0;
						status = RBF_ERROR;	// this should never happen, buffer must be cleared
					}
				}
			}
			else
			{
				*size = 0;
				status = RBF_ERROR;	// this should never happen, buffer must be cleared
			}	
		}
		else
		{
			*size = 0;
			status = RBF_EMPTY;
		}
	}
	
	
	return status;
}
/*****************************************************************/
uint8_t RBF_ucGetMsgCount(uint8_t ucIndex)
{
	return RingBuffer[ucIndex].msgcount;
}	

/*****************************************************************/
uint8_t RBF_ucGetByteCount(uint8_t ucIndex)
{
    uint8_t bytecount;
    
    if (RingBuffer[ucIndex].head == RingBuffer[ucIndex].tail)
    {
        bytecount = 0;
    }
    else if (RingBuffer[ucIndex].head > RingBuffer[ucIndex].tail)
    {
        bytecount = RingBuffer[ucIndex].head - RingBuffer[ucIndex].tail;
    }
    else
    {
        bytecount = RingBuffer[ucIndex].head + (RingBuffer[ucIndex].size - RingBuffer[ucIndex].tail);
    }
    
    return bytecount;
}

/* ----------------------------------------------------------------- */
/* --------------------- STATIC FUNCTIONS -------------------------- */ 
/* ----------------------------------------------------------------- */
/*****************************************************************/
static uint8_t IncHead(uint8_t ucIdx)
{
    uint8_t status = RBF_FAIL;
    uint16_t tempHead = RingBuffer[ucIdx].head + 1;
    
    if (tempHead > RingBuffer[ucIdx].size)
    {
        tempHead = 0;
    }
    
    if (tempHead != RingBuffer[ucIdx].tail)
    {
        RingBuffer[ucIdx].head = tempHead;
        status = RBF_SUCCESS;
    }
    
    return status;
} 
/*****************************************************************/
static uint8_t DecHead(uint8_t ucIdx)
{
    uint8_t status = RBF_FAIL;
    
    if(RingBuffer[ucIdx].head != RingBuffer[ucIdx].tail)
    {
        if (RingBuffer[ucIdx].head == 0)
        {
            RingBuffer[ucIdx].head = RingBuffer[ucIdx].size;
        }
        else
        {
            RingBuffer[ucIdx].head--;
        }
        
        status = RBF_SUCCESS;
    }
        
    return status;
}
/*****************************************************************/
static uint8_t IncTail(uint8_t ucIdx)
{
    uint8_t status = RBF_FAIL;
    uint16_t tempTail = RingBuffer[ucIdx].tail + 1;
    
    if (tempTail > RingBuffer[ucIdx].size)
    {
        tempTail = 0;
    }
    
    if (tempTail != RingBuffer[ucIdx].head)
    {
        RingBuffer[ucIdx].tail = tempTail;
        status = RBF_SUCCESS;
    }
    
    return status;
} 
/*****************************************************************/
/*
static uint8_t DecTail(uint8_t ucIdx)
{
    uint8_t status = RBF_FAIL;
    
    if(RingBuffer[ucIdx].head != RingBuffer[ucIdx].tail)
    {
        if (RingBuffer[ucIdx].tail == 0)
        {
            RingBuffer[ucIdx].tail = RingBuffer[ucIdx].size;
        }
        else
        {
            RingBuffer[ucIdx].tail--;
        }
        
        status = RBF_SUCCESS;
    }
        
    return status;
}
*/
/*****************************************************************/
/*****************************************************************/
#ifdef RBF_TEST

uint8_t RBF_ucTest(void)
{
    static uint8_t ucBuffer1[20];
    static uint8_t ucBuffer2[10];
    static uint8_t ucBuffer3[40];
    static uint8_t ucBufferIndex1 = 0xFF;
    static uint8_t ucBufferIndex2 = 0xFF;
    static uint8_t ucBufferIndex3 = 0xFF;
	static uint8_t ucTemp;
	int i;
	static uint8_t Msg1[5] = {0x33, 0x44, 0x55, 0x66, 0x77};
	static uint8_t Msg2[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    static uint8_t Msg3[5] = {0x01, 0x02, 0x03, 0x04, 0x05};
	static uint8_t MsgSize;
	static uint8_t MsgCount;
    static uint8_t ByteCount;
	
    STATUS status = RBF_sInit();
    
    // TEST 1: Register Buffers -------------------------------------------------------------------
    ucBufferIndex1 = RBF_ucRegisterBuffer(ucBuffer1, 20);
    ucBufferIndex2 = RBF_ucRegisterBuffer(ucBuffer2, 10);
    ucBufferIndex3 = RBF_ucRegisterBuffer(ucBuffer3, 40);
    
    status = RBF_ucUnregisterBuffer(ucBufferIndex2);
    
    ucBufferIndex3 = RBF_ucRegisterBuffer(ucBuffer3, 40);
    // END TEST 1
    
    // TEST 2: ByteIn, ByteOut -------------------------------------------------------------------
	status = RBF_ucByteIn(ucBufferIndex1, 0x55);	//Byte 1 of 20
	
	for (i=0; i<18; i++)							//Byte 1..19 of 20
	{
		status = RBF_ucByteIn(ucBufferIndex1, i);
		if (status != RBF_SUCCESS)
		{
			while(1) {};
		}
	}
    
    ByteCount = RBF_ucGetByteCount(ucBufferIndex1);
	
	status = RBF_ucByteIn(ucBufferIndex1, 0x11);	//Byte 20 of 20
	status = RBF_ucByteIn(ucBufferIndex1, 0x22);	//Byte 21 of 20 -> error

	status = RBF_ucFirstByteOut(ucBufferIndex1, &ucTemp);		//Byte 20 of 20
	status = RBF_ucLastByteOut(ucBufferIndex1, &ucTemp);		//Byte 1 of 20
	
	status = RBF_ucClearBuffer(ucBufferIndex1);

	status = RBF_ucFirstByteOut(ucBufferIndex1, &ucTemp);		//Byte 1 of 20 -> error
	status = RBF_ucLastByteOut(ucBufferIndex1, &ucTemp);		//Byte 1 of 20 -> error
    // END TEST 2
    
    // TEST 3: MsgIn, MsgOut  -------------------------------------------------------------------
	status = RBF_ucClearBuffer(ucBufferIndex1);
	
	status = RBF_ucMsgIn(ucBufferIndex1, Msg1, 5);	//Byte 1..7 of 20
	status = RBF_ucMsgIn(ucBufferIndex1, Msg1, 5);	//Byte 8..15 of 20
	status = RBF_ucMsgIn(ucBufferIndex1, Msg1, 5);	//Byte 16..21 of 20 -> error
	
	MsgCount = RBF_ucGetMsgCount(ucBufferIndex1);	//2
    ByteCount = RBF_ucGetByteCount(ucBufferIndex1);
		
	status = RBF_ucFirstMsgOut(ucBufferIndex1, Msg2, &MsgSize);	//Byte 8..15 of 20
	status = RBF_ucMsgIn(ucBufferIndex1, Msg3, 5);			//Byte 8..15 of 20
	
	status =  RBF_ucLastMsgOut(ucBufferIndex1, Msg2, &MsgSize);	//Byte 8..15 of 20
	status =  RBF_ucLastMsgOut(ucBufferIndex1, Msg2, &MsgSize);	//Byte 1..7 of 20 (buffer empty)	
	
	MsgCount = RBF_ucGetMsgCount(ucBufferIndex1); // 0
    ByteCount = RBF_ucGetByteCount(ucBufferIndex1); // 0
    // END TEST 3

    return status;
}    
    
#endif //RBF_TEST
