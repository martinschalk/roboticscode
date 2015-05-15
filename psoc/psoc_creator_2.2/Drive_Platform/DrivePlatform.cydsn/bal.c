/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#include <project.h>
#include <stdio.h>
#include "bal.h"
#include "bpl.h"

#include "servo_cds5500.h"
#include "global.h"
#include "tmr.h"

//static uint8 MsgReceiveBuffer[BAL_MSG_RECEIVE_BUFFER_SIZE];
//static uint8 MsgTransmitBuffer[BAL_MSG_RECEIVE_BUFFER_SIZE];

#ifdef BAL_MODULE_TEST   
    static void BAL_ModuleTest();
#endif
/*****************************************************************/
/* | startbyte0 | startbyte1 | motorId | length | instrId | instrParams[8] | checksum | 
     0            1            2         3        4         5                13       
     length = 1(instrId) + sizeof(instrParams) + 1(checksum)
*/
STATUS BAL_ServoMsg(CDS5500_MSG* msg)
{
    STATUS status;
            
    if (msg->motorId > 254)
        status = CDS5500_ERROR_MOTOR_ID;
    else  if (msg->length > CDS5500_INST_LENGTH_MAX) 
        status = CDS5500_ERROR_LENGTH;
    else  if (msg->instrId == 0) 
        status = CDS5500_ERROR_INSTR_ID;
    else  if ((msg->instrParams)[msg->length - CDS5500_INST_LENGTH_MAX] == 0) 
        status = CDS5500_ERROR_CHKSUM;
    else
    {
        status = BPL_TransmitMessage((uint8*)msg, msg->length + 4); 
        // 1(startbyte0) + 1(startbyte1) + 1(motorId) + 1(length) = +4
        // 1(instrId) + 1(checksum) = +2
    }
    
	return status;
}


/*****************************************************************/
/* | id0 | id1 | length | *content | 
     0     1     2        3     
     length = sizeof(content)
*/
/*
!!!  if compiled, calling BAL_ServoMsg causes call of BAL_SendMsg instead 
       reason not yet found !!!

STATUS BAL_SendMsg(BAL_MSG* msg)
{
    STATUS status;
    uint8 buffer[3+msg->length];
    
    buffer[0] = (uint8)(msg->id << 8);
    buffer[1] = (uint8)(msg->id);
    buffer[2] = msg->length;
    memcpy(&buffer[3], msg->content, msg->length);
    
    status = BPL_TransmitMessage(buffer, msg->length + 3);
    
	return SUCCESS;
}
*/


/*****************************************************************/
/* range of val: BAL_ACK_OK, BAL_ACK_NOK */
STATUS BAL_SendAck(uint8 val)
{
    uint8 buffer[] = {  (uint8)(BAL_MSG_ID_ACK << 8), 
                        (uint8)(BAL_MSG_ID_ACK),
                        BAL_MSG_LENGTH_ACK, 
                        val
                     };
    
    
    return BPL_TransmitMessage(buffer, 4);
}

/*****************************************************************/
STATUS BAL_Init(void)
{
#ifdef BAL_MODULE_TEST
    //TST_SetModuleTest(BAL_ModuleTest);
    TMR_SetTimer(TIMER_4, TIMER_1SEC, BAL_ModuleTest, TIMER_MODE_CONTINUOUS, TIMER_ENABLED);
#endif
    
	return SUCCESS;
}


/*****************************************************************/
STATUS BAL_HandleTask(void)
{
    return SUCCESS;
}


/*****************************************************************/
#ifdef BAL_MODULE_TEST   
static void BAL_ModuleTest(void)
{
    CDS5500_Ping(0x01);
}
#endif
/* [] END OF FILE */
