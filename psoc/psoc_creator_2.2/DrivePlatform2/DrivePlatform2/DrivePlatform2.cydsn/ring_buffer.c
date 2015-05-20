/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
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
static uint8_t DecTail(uint8_t ucIdx);



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
    STATUS status;
    
    // TEST 1: Register Buffers
    ucBufferIndex1 = RBF_ucRegisterBuffer(ucBuffer1, 20);
    ucBufferIndex2 = RBF_ucRegisterBuffer(ucBuffer2, 10);
    ucBufferIndex3 = RBF_ucRegisterBuffer(ucBuffer3, 40);
    
    status = RBF_ucUnregisterBuffer(ucBufferIndex2);
    
    ucBufferIndex3 = RBF_ucRegisterBuffer(ucBuffer3, 40);
    // END TEST 1
    
    // TEST 2: ByteIn, ByteOut
    // END TEST 2
    
    // TEST 3: MsgIn, MsgOut
    // END TEST 3
    
    return status;
}    
    
#endif //RBF_TEST
