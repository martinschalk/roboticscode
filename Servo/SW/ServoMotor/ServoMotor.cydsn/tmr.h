/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#include <project.h>
#include "types.h"


#define TIMER_PERIOD_1000SEC		1000000000	//for 1MHz clock
#define TIMER_10SEC					10000000
#define MAX_TIMERS					10
#define TIMER_DISABLED				0
#define TIMER_ENABLED				1
#define TIMER_MODE_CONTINUOUS		2
#define TIMER_MODE_ONE_SHOT			3

#define TIMER_0						0
#define TIMER_1						1
#define TIMER_2						2
#define TIMER_3						3


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
void TMR_HandleTask(void);

/* [] END OF FILE */
