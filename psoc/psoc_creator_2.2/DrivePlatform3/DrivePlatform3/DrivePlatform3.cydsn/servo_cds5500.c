/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#include <project.h>
#include <stdio.h>
#include "servo_cds5500.h"

#include "bal.h"
#include "types.h"
#include "move.h"

/*------------------------ LOCAL FUNCTIONS -------------------------------*/

/**************************************************************************/
uint8 CDS5500_GetChecksum(CDS5500_MSG* msg)
{
	uint8 checksum = 0;
    uint8 i;
        
    /* add first 3 bytes of motor message */    
    checksum = msg->motorId + msg->length + msg->instrId;
    
    /* add parameter bytes of motor message */   
    for (i=0; i<msg->length-CDS5500_COMPLEMENTARY_BYTES; i++)
        checksum += msg->instrParams[i];
      
    /* invert checksum */    
    checksum = ~checksum & 0xFF; //    printf((~(ID + (messageLength) + INST_WRITE + P_GOAL_POSITION_L + pos + pos2 + vel + vel2))&0xFF)
	
	return checksum;
}

/**************************************************************************/
static STATUS SendServoMsg(uint8 ucMotorId, uint8 ucInstrId, uint8 ucNumParams, uint8* pucInstrParams)
{
    CDS5500_MSG msg;
    
    msg.startbyte0      = START_BYTE_0_VALUE;
    msg.startbyte1      = START_BYTE_1_VALUE;
    msg.motorId         = ucMotorId;
    msg.instrId         = ucInstrId;
    
    if ((ucNumParams > 0) && (pucInstrParams != NULL))
        memcpy(msg.instrParams, pucInstrParams, ucNumParams);

    msg.length          = ucNumParams + 2; //number of params + 1 (instrId) + 1 (checksum)
    msg.checksum        = CDS5500_GetChecksum(&msg);  
    
    return BAL_ServoMsg(&msg);
}

/**************************************************************************
CheckResponse
http://www.dfrobot.com/image/data/SER0026/CDS55XX_Robot_Servo_User_Manual_EN.pdf
HEADER ID LENGTH ERROR PARAMETER CHECK SUM
**************************************************************************/
STATUS CDS5500_CheckResponse(CDS5500_MSG* response)
{
    STATUS status=SUCCESS;
    uint8 msgCkecksum = response->checksum;
    uint8 calcChecksum = CDS5500_GetChecksum(response); 
    
    /* compare calculated with received checksum */
    if (msgCkecksum != calcChecksum)
        return CDS5500_ERROR_RECEIVED_CHECKSUM;
    
    /* check if error bits are set */
    if (response->instrParams[0] & CDS5500_ERROR_INSTRUCTION_BIT) 
        status = CDS5500_ERROR_INSTRUCTION;
        
    return status;
}


/**************************************************************************
**************************************************************************/
void CDS5500_ReadRequest(uint8_t ucMotorId, uint8_t ucAddr)
{
    STATUS status;

    CDS5500_MSG msg = { START_BYTE_0_VALUE, 
                        START_BYTE_1_VALUE, 
                        ucMotorId,
                        CDS5500_INST_LENGTH_READ,
                        CDS5500_INST_ID_READ,
                        {ucAddr},
                        0x00,
                      };
                      
    msg.instrParams[msg.length - CDS5500_COMPLEMENTARY_BYTES] = CDS5500_GetChecksum(&msg); 
    
    status = BAL_ServoMsg(&msg);  
    
    //Notify upper layer 
    if (status == SUCCESS)
        MOV_vSetMsgIdResponsePending(ucMotorId, CDS5500_INST_ID_READ);
    
    (void)status;
}

/**************************************************************************
Does not command any operations. Used for requesting a status 
packet or to check the existence of a CDS55xx servo with a specific 
ID. 
**************************************************************************/
void CDS5500_Ping(uint8 motorId)
{
    STATUS status;

    CDS5500_MSG msg = { START_BYTE_0_VALUE, 
                        START_BYTE_1_VALUE, 
                        motorId,
                        CDS5500_MSG_LENGTH_PING,
                        CDS5500_INST_ID_PING,
                        {0x00},
                        0x00,
                      };
    
    //msg.checksum = CDS5500_GetChecksum(&msg);
    msg.instrParams[msg.length - CDS5500_COMPLEMENTARY_BYTES] = CDS5500_GetChecksum(&msg);
                
    // SB0  SB1  MID  LEN  INID PAR CHKS
    // 0xFF 0xFF 0x01 0x02 0x01 -   0xFB                 
    status = BAL_ServoMsg(&msg);

    (void)status;
}



/**************************************************************************/
void CDS5500_WritePos(int id, int position, int velocity)
{
	int messageLength = 7;
    (void)messageLength;

	/*
	printf(startByte0);              // send some data
	printf(startByte1);
	printf(id);
	printf(messageLength);
	printf(INST_WRITE);
	printf(P_GOAL_POSITION_L);
	printf(pos);
	printf(pos2);
	printf(vel);
	printf(vel2);
	printf((~(ID + (messageLength) + INST_WRITE + P_GOAL_POSITION_L + pos + pos2 + vel + vel2))&0xFF);
	*/
}

/**************************************************************************/
/*
void CDS5500:: RegWritePos(int ID, int position, int velocity){
	int messageLength = 5;
	byte pos2 =  position/255;
	byte pos =  position%255;	
	
	byte vel2 =  velocity/255;
	byte vel =  velocity%255;

	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(messageLength);
	printf(INST_REG_WRITE);
	printf(P_GOAL_POSITION_L);
	printf(pos);
	printf(pos2);
//	printf(vel);
//	printf(vel2);
	printf((~(ID + (messageLength) + INST_WRITE + P_GOAL_POSITION_L + pos + pos2 + vel + vel2))&0xFF);
}

void CDS5500:: RegWriteAction(){
	int messageLength = 2;
	byte ID =  0xFE; 

	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(messageLength);
	printf(INST_ACTION);
	printf((~(ID + (messageLength) + INST_ACTION))&0xFF);



}

void CDS5500:: SetID(int ID, int newID){
	int messageLength = 4;
	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(messageLength);
	printf(INST_WRITE);
	printf(P_ID);
	printf(newID);
	printf((~(ID + (messageLength) + INST_WRITE+ P_ID + newID))&0xFF);
}

void CDS5500:: SetAngleLimit(int ID, int lowerLimit, int upperLimit){
	int messageLength = 8;
	byte lowerLimitB = lowerLimit%255;
	byte lowerLimitS = lowerLimit/255;
	byte upperLimitB = upperLimit%255;
	byte upperLimitS = upperLimit/255;
	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(messageLength);
	printf(INST_WRITE);
	printf(0x08);
	printf(upperLimitB);
	printf(0x09);
	printf(upperLimitS);
	printf(0x06);
	printf(lowerLimitB);
	printf(0x07);
	printf(lowerLimitS);	
	printf((~(ID + (messageLength) + INST_WRITE+ 0x08 + 0x09 + 0x06 + 0x07 + upperLimitB+ upperLimitS+
					 lowerLimitB + lowerLimitS))&0xFF);
}

//void CDS5500:: SyncWritePos(int[] ID, int[] pos; int[] vel){
//	int messageLength = ()*sizeof(ID);
//}
//
//
//void CDS5500:: SyncWritePos(int[] ID, int pos; int vel){
//	
//}
//

void CDS5500:: tempMethod(){
	
	printf(startByte);              // send some data
	printf(startByte);
	printf(0x01);
	printf(0x05);
	printf(0x03);
	printf(0x08);
	printf(0xFF);
	printf(0x01);
	printf(0xF4);
	printf(0xef);
	
}

void CDS5500:: Reset(int ID){
	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(0x02);
	printf(0x06);
	printf((~(ID + 0x02 +0x06))&0xFF);
}

void CDS5500::SetTempLimit(int ID, int temperature){
	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(0x04);
	printf(0x03);
	printf(0x0B);
	printf(temperature);
	printf((~(ID + 0x04 +0x03 + 0x0B + temperature))&0xFF);
}

*/

/**************************************************************************/
void ServoTest(void)
{
    STATUS status;
    
    status = SendServoMsg(  CDS5500_SERVO_ID_1,    CDS5500_INST_LENGTH_PING,   CDS5500_INST_ID_PING,      0);
    /*
                        HEADER      ID      LENGTH      INSTRUCTION     PARAMETERS
            SEND:       0XFF 0XFF   0X01    0X02        0X01            0XFB 
            RETURN:     0XFF 0XFF   0X01    0X02        0X00            0XFC
    */

}
