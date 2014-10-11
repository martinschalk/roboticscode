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
BUS ABSTRACTION LAYER		(BAL)                           <
- Message Handler
-------------------------------------------------------------
BUS PRESENTATION LAYER		(BPL)
- Ring Buffer
-------------------------------------------------------------
HARDWARE ABSTRACTION LAYER	(HAL)
- UART
-------------------------------------------------------------
*/

#ifndef BAL_H
#define BAL_H

#include <project.h>
#include "types.h"
#include "servo_cds5500.h"

#define BAL_MSG_MAX_DATA_SIZE           10
#define BAL_MSG_RECEIVE_BUFFER_SIZE	    32
#define BAL_NODE                        0xF0

/* message structure */
typedef struct _bal_msg
{
    uint16  id;
    uint8   length;
    uint8*  content;
}BAL_MSG;


STATUS  BAL_Init(void);
void    BAL_Handler(void);
STATUS  BAL_SendMsg(BAL_MSG* msg);
STATUS  BAL_SendServoMsg(CDS5500_MSG* msg);

#endif /* BAL_H */

/* [] END OF FILE */
