/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

/* BUS STRUCTURE
-------------------------------------------------------------
APPLICATION LAYER			(APPL)
- Message Routines
-------------------------------------------------------------
BUS ABSTRACTION LAYER		(BAL)
- Message Handler
-------------------------------------------------------------
BUS PRESENTATION LAYER		(BPL)                           <
- Ring Buffer
-------------------------------------------------------------
HARDWARE ABSTRACTION LAYER	(HAL)
- UART
-------------------------------------------------------------
*/

/* 
BUFFER MESSAGE (RX/TX)
-------------------------------
| length | b0 | b1 | ... | bn |
-------------------------------

BUS MESSAGE
-------------------------------------------
| id0 | id1 | length | b0 | b1 | ... | bn |
-------------------------------------------
(b_i containing check sum)
*/
#ifndef BPL_H
#define BPL_H


#include "servo_cds5500.h"

//#define BPL_MODULE_TEST
#define BPL_DEBUG


/*******************************************************/
#define BPL_TX_BUFFER_SIZE		256
#define BPL_RX_BUFFER_SIZE		256
#define BPL_MAX_MESSAGE_LENGTH  32


/* Error Codes */
/*******************************************************/
#define BPL_STATUS_OK					(uint8)(0)
#define BPL_STATUS_RX_BUFFER_FULL		(uint8)(-1)
#define BPL_STATUS_TX_BUFFER_FULL		(uint8)(-2)
#define BPL_STATUS_TX_DATA_MISMATCH		(uint8)(-3)
#define BPL_STATUS_RX_ERROR				(uint8)(-4)
#define BPL_STATUS_TX_ERROR				(uint8)(-5)

#define BPL_SUCCESS                     (uint8)(0)

typedef uint8_t BPL_STATUS;


/*******************************************************/
extern STATUS BPL_Init(void);
/*******************************************************/
extern uint8_t BPL_CDS5500_ucGetRxMessageCount(void);
/*******************************************************/
extern void BPL_CDS5500_ucSetRxMessageCount(uint8_t ucVal);
/*******************************************************/
extern STATUS BPL_HandleTask(void);
/*******************************************************/
extern uint8 BPL_GetReceiveCount(void);
/*******************************************************/
extern uint8 BPL_GetMessage(uint8* target);
/*******************************************************/
extern STATUS BPL_TransmitMessage(uint8* source, uint8 msgLength);
/*******************************************************/
extern STATUS BPL_CDS5500_GetResponse(CDS5500_MSG* targetAddr);
/*******************************************************/
#ifdef BPL_MODULE_TEST
    extern void BPL_ucTest(void);
#endif




#endif /* BPL_H */
