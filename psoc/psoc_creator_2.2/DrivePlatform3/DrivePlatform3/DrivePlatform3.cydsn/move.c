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

//#include "bal.h"
#include "global.h"
//#include "tmr.h"

static CDS5500_STATUS Servo1 = {    
    {0x0000, 0x0000},   //uint16_t uiPosition[2];
    {0x0000, 0x0000},   //uint16_t uiVelocity[2]; 
    {0x0000, 0x0000},   //uint16_t uiLoad[2];    
    {0x0000, 0x0000},   //uint16_t uiVoltage[2]; 
    {0x0000, 0x0000},   //uint16_t uiTemperature[2];
    0x00                //uint8_t  ucError;
};

static STATUS MOV_ucGetStatus(uint8_t motorId);

/*****************************************************************/
static STATUS MOV_ucGetStatus(uint8_t motorId)
{
    STATUS status;

    CDS5500_ReadRequest(CDS5500_SERVO_1, CDS5500_P_ID); //TODO: implement waiting for response in bpl before transmitting next message
    //CDS5500_ReadRequest(...)

    return status;
}

/*****************************************************************/
STATUS MOV_Init(void)
{
    STATUS status;
    
    status = MOV_ucGetStatus(CDS5500_SERVO_1);
    
    return SUCCESS;
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
        CDS5500_Ping(CDS5500_SERVO_1);
    }
}

#endif //BPL_MODULE_TEST
