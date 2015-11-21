/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */
 
#include <project.h>
#include <stdio.h>
#include "types.h"
#include "move.h"
#include "servo_cds5500.h"
#include "tmr.h"

//#include "bal.h"
#include "global.h"
//#include "tmr.h"

static MOV_SERVO MOV_Servo[MOV_NUM_SERVOS];

static STATUS MOV_ucGetStatus(uint8_t ucMotorIdx);





/*****************************************************************/
static STATUS MOV_ucGetStatus(uint8_t ucMotorIdx)
{
    STATUS status = SUCCESS;
           
    if (MOV_Servo[ucMotorIdx].ucMsgIdResponsePending == CDS5500_INST_ID_NONE)
    {
        CDS5500_ReadRequest(MOV_Servo[ucMotorIdx].ucId, CDS5500_P_ID); //get motor id
    }
    
    return status;
}



/*****************************************************************/
/**
Function is called, if no response within TIMER_2SEC received.
*/
void MOV_vTimeout(void)
{
    //error
}





/*****************************************************************/
MOV_SERVO_IDX MOV_ucGetMotorIdx(uint8_t ucMotorId)
{
    MOV_SERVO_IDX tServoIdx;

    switch(ucMotorId)
    {
        case CDS5500_SERVO_ID_1:    tServoIdx = MOV_SERVO_IDX_FRONT_LEFT;
                                    break;
        case CDS5500_SERVO_ID_2:    tServoIdx = MOV_SERVO_IDX_FRONT_RIGHT;
                                    break;
        case CDS5500_SERVO_ID_3:    tServoIdx = MOV_SERVO_IDX_BACK_LEFT;
                                    break;
        case CDS5500_SERVO_ID_4:    tServoIdx = MOV_SERVO_IDX_BACK_RIGHT;
                                    break;
        default:                    tServoIdx = MOV_SERVO_IDX_IVALID;
                                    break;                                    
    }
    
    return tServoIdx;
}


/*****************************************************************/
/**
This function is called for any received message to update last motor contact data.
*/
STATUS MOV_ucUpdateContact(uint8_t ucMotorId)
{
    STATUS status = SUCCESS;
    //MOV_SERVO_IDX tMotorIdx = MOV_ucGetMotorIdx(ucMotorId);
    
    TMR_StartTimer(TIMER_2);    //reset timeout timer
    
    
    
    return status;
}

/*****************************************************************/
void MOV_vSetMsgIdResponsePending(uint8_t ucMotorId, BOOL val)
{
    MOV_SERVO_IDX tMotorIdx = MOV_ucGetMotorIdx(ucMotorId);
     
    MOV_Servo[tMotorIdx].ucMsgIdResponsePending = val;
}

/*****************************************************************/
uint8_t MOV_ucGetMsgIdResponsePending(uint8_t ucMotorId)
{
    MOV_SERVO_IDX tMotorIdx = MOV_ucGetMotorIdx(ucMotorId);
     
    return MOV_Servo[tMotorIdx].ucMsgIdResponsePending;
}








/*****************************************************************/
/*****************************************************************/
STATUS MOV_Init(void)
{
    STATUS status = SUCCESS;
    
    //clear all motor data
    memset(MOV_Servo, 0x00, MOV_NUM_SERVOS * sizeof(MOV_SERVO));    
    
    //set motor IDs
    MOV_Servo[MOV_SERVO_IDX_FRONT_LEFT].ucId = CDS5500_SERVO_ID_1;  
    MOV_Servo[MOV_SERVO_IDX_FRONT_RIGHT].ucId = CDS5500_SERVO_ID_2;
    MOV_Servo[MOV_SERVO_IDX_BACK_LEFT].ucId = CDS5500_SERVO_ID_2;
    MOV_Servo[MOV_SERVO_IDX_BACK_RIGHT].ucId = CDS5500_SERVO_ID_3;
    
    //start timeout timer
    TMR_SetTimer(TIMER_2, TIMER_2SEC, MOV_vTimeout, TIMER_MODE_CONTINUOUS, TIMER_ENABLED);
    
    //status = MOV_ucGetStatus(CDS5500_SERVO_ID_1);
    
    return status;
}

/*****************************************************************/
STATUS MOV_HandleTask(void)
{
    STATUS balStatus;

    return balStatus;
}

/*****************************************************************/
/*****************************************************************/
#ifdef MOV_MODULE_TEST

void MOV_ucTest(void)
{
    STATUS status;
    static uint8_t x = 1;
    
    if (x)
    {
        CDS5500_Ping(CDS5500_SERVO_ID_1);
    }
}

#endif //BPL_MODULE_TEST
