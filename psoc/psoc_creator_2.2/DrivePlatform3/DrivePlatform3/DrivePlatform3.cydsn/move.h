/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */
 
#ifndef MOV_H
#define MOV_H

#include "types.h"
#include "servo_cds5500.h"



#define MOV_MODULE_TEST

#define MOV_NUM_SERVOS  4U

typedef enum _move_servo_idx
{
    MOV_SERVO_IDX_FRONT_LEFT = 0,
    MOV_SERVO_IDX_FRONT_RIGHT,
    MOV_SERVO_IDX_BACK_LEFT,
    MOV_SERVO_IDX_BACK_RIGHT,
    MOV_SERVO_IDX_IVALID
}MOV_SERVO_IDX;

typedef struct _move_servo
{
    uint8_t         ucId;
    uint8_t         ucMsgIdResponsePending;
    CDS5500_STATUS  status;
}MOV_SERVO;


/*****************************************************************/

/*****************************************************************/

/*****************************************************************/

/*****************************************************************/
extern MOV_SERVO_IDX MOV_ucGetMotorIdx(uint8_t ucMotorId);
/*****************************************************************/
extern void MOV_vSetMsgIdResponsePending(uint8_t ucMotorId, BOOL val);
/*****************************************************************/
extern uint8_t MOV_ucGetMsgIdResponsePending(uint8_t ucMotorId);
/*****************************************************************/
extern STATUS MOV_ucUpdateContact(uint8_t motorId);
/*****************************************************************/
/*****************************************************************/
extern STATUS MOV_Init(void);
/*****************************************************************/
extern STATUS MOV_HandleTask(void);
/*****************************************************************/
/*****************************************************************/
#ifdef MOV_MODULE_TEST
    extern void MOV_ucTest(void);
#endif



#endif //MOV_H
