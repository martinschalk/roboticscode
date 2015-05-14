/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

/*
SERVO MESSAGE
---------------------------------------------------------------
| sb0 | sb1 | id0 | Length | b0 | b1 | ... | bn | crc0 | crc1 |
---------------------------------------------------------------
*/

#include <project.h>
#include <types.h>
#include "global.h"

#ifndef CDS5500_h
#define CDS5500_h
	
/* send both at beginning of each message */
#define START_BYTE_0_VALUE 0xFF	
#define START_BYTE_1_VALUE 0xFF	
	
/* error codes */
#define CDS5500_ERROR_INSTRUCTION_BIT       (uint8)(1<<6)
#define CDS5500_ERROR_OVERLOAD_BIT          (uint8)(1<<5)
#define CDS5500_ERROR_CHECKSUM_BIT          (uint8)(1<<4)
#define CDS5500_ERROR_RANGE_BIT             (uint8)(1<<3)
#define CDS5500_ERROR_OVERHEATING_BIT       (uint8)(1<<2)
#define CDS5500_ERROR_POSITION_LIMIT_BIT    (uint8)(1<<1)
#define CDS5500_ERROR_INPUT_VOLTAGE_BIT     (uint8)(1<<0)


#define ERROR_INSTRUCTION                   (STATUS)(-1)
#define ERROR_RECEIVED_CHECKSUM             (STATUS)(-2)
#define ERROR_SENT_CHECKSUM                 (STATUS)(-3)
#define ERROR_OVERLOAD                      (STATUS)(-4)
#define ERROR_RANGE                         (STATUS)(-5)
#define ERROR_OVERHEATING                   (STATUS)(-6)
#define ERROR_POSITION_LIMIT                (STATUS)(-7)
#define ERROR_INPUT_VOLTAGE                 (STATUS)(-8)

/*
Triggers the action registered by the
http://www.dfrobot.com/image/data/SER0026/CDS55XX_Robot_Servo_User_Manual_EN.pdf

BIT7 0 --- 
BIT6 Instruction Error Set to 1 if an undefined instruction is sent or an action instruction is 
sent without a Reg_Write instruction. 
BIT5 Overload Error Set to 1 if the specified maximum torque can't control the applied 
load. 
BIT4 Checksum Error Set to 1 if the checksum of the instruction packet is incorrect. 
BIT3 Range Error Set to 1 if the instruction sent is out of the defined range. 
BIT2 Overheating Error 
Set to 1 if the internal temperature of the CDS55xx unit is above the 
operating temperature range as defined in the control table. 
BIT1 Position Limit Error 
Set as 1 if the Goal Position is set outside of the range between CW 
Angle Limit and CCW Angle Limit. 
BIT0 Input Voltage Error 
Set to 1 if the voltage is out of the operating voltage range as defined 
in the control table. 

HEADER ID LENGTH ERROR PARAMETER CHECK SUM 
*/  

/*
HEADER ID LENGTH INSTRUCTION PARAMETER CHECK SUM 
*/  
/* | startbyte0 | startbyte1 | motorId | length | instrId | instrParams[8] | checksum | 
     0            1            2         3        4         5                13       
     length = 1(instrId) + number of instrParams + 1(checksum)
*/
typedef struct _servo_msg
{
	uint8 startbyte0;
	uint8 startbyte1;
	uint8 motorId;			//0-253, 254 is broadcast
	uint8 length;           //number of params + 1 (instrId) + 1 (checksum)
    uint8 instrId;
	uint8 instrParams[8];
	uint8 checksum;
}CDS5500_MSG;


#define SERVO_1                         0x01
#define SERVO_2                         0x02
#define SERVO_3                         0x03
#define SERVO_4                         0x04

//Register Address
#define P_MODEL_NUMBER_L                0
#define P_MODEL_NUMBER_H                1
#define P_VERSION                       2
#define P_ID                            3
#define P_BAUD_RATE                     4
#define P_RETURN_DELAY_TIME             5
#define P_CW_ANGLE_LIMIT_L              6
#define P_CW_ANGLE_LIMIT_H              7
#define P_CCW_ANGLE_LIMIT_L             8
#define P_CCW_ANGLE_LIMIT_H             9
#define P_SYSTEM_DATA2                  10
#define P_LIMIT_TEMPERATURE             11
#define P_DOWN_LIMIT_VOLTAGE            12
#define P_UP_LIMIT_VOLTAGE              13
#define P_MAX_TORQUE_L                  14
#define P_MAX_TORQUE_H                  15
#define P_RETURN_LEVEL                  16
#define P_ALARM_LED                     17
#define P_ALARM_SHUTDOWN                18
#define P_OPERATING_MODE 19
#define P_DOWN_CALIBRATION_L 20
#define P_DOWN_CALIBRATION_H 21
#define P_UP_CALIBRATION_L 22
#define P_UP_CALIBRATION_H 23
#define P_TORQUE_ENABLE (24)
#define P_LED (25)
#define P_CW_COMPLIANCE_MARGIN (26)
#define P_CCW_COMPLIANCE_MARGIN (27)
#define P_CW_COMPLIANCE_SLOPE (28)
#define P_CCW_COMPLIANCE_SLOPE (29)
#define P_GOAL_POSITION_L (30)
#define P_GOAL_POSITION_H (31)
#define P_GOAL_SPEED_L (32)
#define P_GOAL_SPEED_H (33)
#define P_TORQUE_LIMIT_L (34)
#define P_TORQUE_LIMIT_H (35)
#define P_PRESENT_POSITION_L (36)
#define P_PRESENT_POSITION_H (37)
#define P_PRESENT_SPEED_L (38)
#define P_PRESENT_SPEED_H (39)
#define P_PRESENT_LOAD_L (40)
#define P_PRESENT_LOAD_H (41)
#define P_PRESENT_VOLTAGE (42)
#define P_PRESENT_TEMPERATURE (43)
#define P_REGISTERED_INSTRUCTION (44)
#define P_PAUSE_TIME (45)
#define P_MOVING (46)
#define P_LOCK (47)
#define P_PUNCH_L (48)
#define P_PUNCH_H (49)


//Instruction IDs:
#define INST_PING                       0x01    //No action. Used for obtaining a Status Packet
#define INST_READ                       0x02    //Reading values in the Control Table
#define INST_WRITE                      0x03    //Writing values to the Control Table
#define INST_REG_WRITE                  0x04    //Similar to WRITE_DATA, but stays in standby mode until the ACION instruction is given
#define INST_ACTION                     0x05    //Triggers the action registered by the REG_WRITE instruction
#define INST_RESET                      0x06	//Changes the control table values of the CDS55xx servos to the Factory default values 
#define INST_DIGITAL_RESET              0x07    //
#define INST_SYSTEM_READ                0x0C    //
#define INST_SYSTEM_WRITE               0x0D    //
#define INST_SYNC_WRITE                 0x83    //Used for controlling multiple CDS55xx servos simultaneously
#define INST_SYNC_REG_WRITE             0x84    //

/* Instruction Length */
#define INST_PING_LENGTH                0x00
#define INST_READ_LENGTH                0x02
#define INST_WRITE_LENGTH               0x02    //Not less than 2
#define INST_REG_WRITE_LENGTH           0x02    //Not less than 2
#define INST_ACTION_LENGTH              0x00
#define INST_RESET_LENGTH               0x00	
#define INST_DIGITAL_RESET_LENGTH       0x01
#define INST_SYSTEM_READ_LENGTH         0x01
#define INST_SYSTEM_WRITE_LENGTH        0x01
#define INST_SYNC_WRITE_LENGTH          0x04    //Not less than 4
#define INST_SYNC_REG_WRITE_LENGTH      0x01	
    
    

STATUS CheckResponse(CDS5500_MSG* response);
void ServoTest(void);


void Ping(uint8 motorId);
void WritePos(int ID, int pos, int vel);
void RegWritePos(int ID, int position, int velocity);
void RegWriteAction();
void SetID(int defaultID, int newID);
void SetAngleLimit(int ID, int low, int high);
void tempMethod();
void Reset(int ID);
void SetTempLimit(int ID, int temperature);
 
    
STATUS CDS5500_SendServoMsg(uint8 ucMotorId, uint8 ucInstrId, uint8 ucNumParams, uint8* pucInstrParams);
    
#endif

/* [] END OF FILE */
