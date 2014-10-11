/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#include "bal.h"
#include "bpl.h"
#include "servo_cds5500.h"
#include <project.h>
#include "global.h"
#include <stdio.h>

//static uint8 MsgReceiveBuffer[BAL_MSG_RECEIVE_BUFFER_SIZE];
//static uint8 MsgTransmitBuffer[BAL_MSG_RECEIVE_BUFFER_SIZE];

/*****************************************************************/
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

/*****************************************************************/
STATUS BAL_SendServoMsg(CDS5500_MSG* msg)
{
    STATUS status;
    uint8 buffer[4+msg->length];
    
    buffer[0] = msg->startbyte0;
    buffer[1] = msg->startbyte1;
    buffer[2] = msg->motorId;
    buffer[3] = msg->length;
    memcpy(&buffer[4], msg->instruction, msg->length);
        
    buffer[4+msg->length] = msg->checksum;
    
    status = BPL_TransmitMessage(buffer, msg->length + 4);
    
	return SUCCESS;
}

/*****************************************************************/
STATUS BAL_Init(void)
{
	
	
	return SUCCESS;
}


/*****************************************************************/
void BAL_Handler(void)
{

}

/* [] END OF FILE */
