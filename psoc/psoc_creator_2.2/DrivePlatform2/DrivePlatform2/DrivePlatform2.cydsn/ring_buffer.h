/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */
 
#ifndef RING_BUFFER_H
#define RING_BUFFER_H 
 
#include "global.h"
#include "types.h"

#define RBF_MODULE_TEST

#define RBF_FAIL                 (uint8_t)(1U)
#define RBF_SUCCESS              (uint8_t)(0U)

#define RBF_ERROR        		 (uint8_t)(-1U)
#define RBF_INVALID_PARAMETERS   (uint8_t)(-2U)
#define RBF_NOT_AVAILABLE        (uint8_t)(-3U)
#define RBF_EMPTY				 (uint8_t)(-4U)

#define RBF_NUM                  (uint8_t)(2U)


typedef struct _ring_buffer 
{
  uint8_t idx;
  uint8_t* address;
  uint16_t size;
  uint16_t head;  
  uint16_t tail;
  uint8_t zb;
  uint16_t msgcount;
} RING_BUFFER;


uint8_t RBF_ucInit(void);
uint8_t RBF_ucClearBuffer(uint8_t ucIndex);
uint8_t RBF_ucRegisterBuffer(uint8_t* pucAddr, uint16_t uiSize);
uint8_t RBF_ucUnregisterBuffer(uint8_t ucIndex);
uint8_t RBF_ucByteIn(uint8_t ucIndex, uint8_t byte);
uint8_t RBF_ucHeadByteOut(uint8_t ucIndex, uint8_t* byte);
uint8_t RBF_ucTailByteOut(uint8_t ucIndex, uint8_t* byte);
uint8_t RBF_ucMsgIn(uint8_t ucIndex, uint8_t* msg, uint8_t size);
uint8_t RBF_ucHeadMsgOut(uint8_t ucIndex, uint8_t* target, uint8_t* size);
uint8_t RBF_ucTailMsgOut(uint8_t ucIndex, uint8_t* target, uint8_t* size);
uint8_t RBF_ucGetMsgCount(uint8_t ucIndex);
uint8_t RBF_ucGetByteCount(uint8_t ucIndex);


#endif //RING_BUFFER_H
