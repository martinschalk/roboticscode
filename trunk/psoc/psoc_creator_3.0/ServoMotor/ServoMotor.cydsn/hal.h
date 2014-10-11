/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#include "global.h"
#include "types.h"

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


/* [] END OF FILE */
