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

#define RBF_TEST

#define RBF_FAIL                 (uint8_t)(1U)
#define RBF_SUCCESS              (uint8_t)(0U)

#define RBF_INVALID_PARAMETERS   (uint8_t)(-1U)
#define RBF_NOT_AVAILABLE        (uint8_t)(-2U)
 
#define RBF_NUM                  (uint8_t)(2U)


typedef struct _ring_buffer 
{
  uint8_t idx;
  uint8_t* address;
  uint16_t size;
  uint16_t head;  
  uint16_t tail;
} RING_BUFFER;

uint8_t RBF_sInit(void);
uint8_t RBF_ucRegisterBuffer(uint8_t* pucAddr, uint16_t uiSize);
uint8_t RBF_ucUnregisterBuffer(uint8_t ucIndex);


#endif //RING_BUFFER_H
