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
BUS PRESENTATION LAYER		(BPL)
- Ring Buffer
-------------------------------------------------------------
HARDWARE ABSTRACTION LAYER	(HAL)                           <
- UART
-------------------------------------------------------------
*/

#ifndef HAL_H
#define HAL_H

#include "global.h"
#include "types.h"

/* Settings */
/*******************************************************/
#define HAL_START_BIT_DETECTION_SUPPORT

/* Error codes */
/*******************************************************/
#define	HAL_RX_COUNT_MISMATCH	-1

/* Hal status */
/*******************************************************/
#define HAL_TRANSMISSION_READY	0u
#define HAL_TRANSMISSION_BUSY	1u


/* Global functions */
/*******************************************************/
STATUS 	HAL_Init(void);
STATUS 	HAL_GetHalStatus(void);
void 	HAL_SetHalStatus(STATUS value);
uint8 	HAL_GetRxIsrCount();
uint8 	HAL_GetRxBufferCount();
uint8 	HAL_GetByte();
STATUS 	HAL_TransmitByte(uint8 value);
STATUS 	HAL_TransmitArray(const uint8* source, uint8 numBytes);

#ifdef TEST_UART
    BOOL GetHalBusIdleState(void);
    void SetHalBusIdleState(BOOL state);
#endif

#endif /* HAL_H */

/* [] END OF FILE */
