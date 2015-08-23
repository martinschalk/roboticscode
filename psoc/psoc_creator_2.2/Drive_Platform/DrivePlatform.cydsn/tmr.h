/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#ifndef TMR_H
#define TMR_H

#include <project.h>
#include "types.h"


#define TIMER_PERIOD_1000SEC		1000000000	//for 1MHz clock
#define TIMER_10SEC					10000000
#define TIMER_1SEC					1000000
#define TIMER_2SEC					2000000
#define TIMER_DISABLED				0
#define TIMER_ENABLED				1
#define TIMER_MODE_CONTINUOUS		2
#define TIMER_MODE_ONE_SHOT			3

enum
{
    TIMER_0	= 0,
    TIMER_1, //BPL module test
    TIMER_2,
    TIMER_3,
    TIMER_4, //BAL module test
    TIMER_5, //MOV module test
    TIMER_NUM
};

/* timer function to be called if timer down */
typedef void (*TMR_FUNC)(void);

/* timer structure */
typedef struct _timer
{
	uint32		count;
	uint32 		value;
	TMR_FUNC 	func;
	uint8 		mode;
	uint8 		status;
}TIMER;

/* Global functions */
/*******************************************************/
STATUS 	TMR_Init(void);
void TMR_SetTimer(uint8 numTimer, uint32 us, TMR_FUNC func, uint8 mode, uint8 status);
void TMR_StartTimer(uint8 numTimer);
void TMR_StopTimer(uint8 numTimer);
STATUS TMR_HandleTask(void);

#endif /* TMR_H */

/* [] END OF FILE */
