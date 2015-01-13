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
/* | startbyte0 | startbyte1 | motorId | length | instrId | instrParams[8] | checksum | 
     0            1            2         3        4         5                13       
     length = 1(instrId) + number of instrParams + 1(checksum)
*/
STATUS BAL_ServoMsg(CDS5500_MSG* msg)
{
    STATUS status;
    /*
    uint8 buffer[4+msg->length];
    
    memcpy[&buffer[0], &msg[0], 5]; //copy startbyte0, startbyte1, motorId, length, instrId
    memcpy(&buffer[5], msg->instrParams, msg->length-1); // copy instrParams and checksum 
    buffer[4+msg->length-1] = msg->checksum;
    status = BPL_TransmitMessage(buffer, msg->length + 4);
    */
    
    status = BPL_TransmitMessage((uint8*)msg, msg->length + 4);
    
	return SUCCESS;
}

/*****************************************************************/
STATUS BAL_ASendMsg(BAL_MSG* msg)
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
	
	
	return SUCCESS;
}


/*****************************************************************/
void BAL_Handler(void)
{

}

/* [] END OF FILE */
