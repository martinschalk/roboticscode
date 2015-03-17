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
*/

#ifndef BPL_H
#define BPL_H

/*******************************************************/
#define TX_BUFFER_SIZE		256
#define RX_BUFFER_SIZE		256



/* Error Codes */
/*******************************************************/
#define BPL_STATUS_OK					0
#define BPL_STATUS_RX_BUFFER_FULL		(uint8)(-1)
#define BPL_STATUS_TX_BUFFER_FULL		(uint8)(-2)
#define BPL_STATUS_TX_DATA_MISMATCH		(uint8)(-3)
#define BPL_STATUS_     				(uint8)(-4)
/*******************************************************/
extern STATUS BPL_HandleTask(void);
extern uint8 BPL_GetReceiveCount(void);
extern uint8 BPL_GetMessage(uint8* target);
extern STATUS BPL_TransmitMessage(uint8* source, uint8 msgLength);

#endif /* BPL_H */

/* [] END OF FILE */
