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

//#define BAL_MODULE_TEST

#ifdef BAL_MODULE_TEST
    enum 
    {
        BAL_MODULE_TEST_CASE_SEND_MSG = 0,
        BAL_MODULE_TEST_CASE_RECEIVE_MSG,
    };
    #define BAL_MODULE_TEST_CASE    BAL_MODULE_TEST_CASE_SEND_MSG
#endif



#define BAL_MSG_MAX_DATA_SIZE           10
#define BAL_MSG_RECEIVE_BUFFER_SIZE	    32
#define BAL_NODE                        0xF0

#define BAL_ACK_OK                      0x01
#define BAL_ACK_NOK                     0x02

#define BAL_SUCCESS                     (uint8)(0)

enum
{
    BAL_MSG_ID_ACK = 1,
    BAL_MSG_ID_1,
    BAL_MSG_ID_2,
};

#define BAL_MSG_LENGTH_ACK              1
#define BAL_MSG_LENGTH_1                1
#define BAL_MSG_LENGTH_1                1


/* message structure */
typedef struct _bal_msg
{
    uint16  id;
    uint8   length;
    uint8*  content;
}BAL_MSG;


extern STATUS  BAL_Init(void);
extern STATUS  BAL_HandleTask(void);
//extern STATUS  BAL_SendMsg(BAL_MSG* msg);
extern STATUS  BAL_ServoMsg(CDS5500_MSG* msg);
extern STATUS  BAL_SendAck(uint8 val);

#ifdef BAL_MODULE_TEST  
    extern void BAL_ModuleTest(void);
#endif

#endif /* BAL_H */

