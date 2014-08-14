/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */


#include <project.h>
#include "types.h"
#include "timer.h"
#include "tmr.h"
#include "global.h"

static BOOL 	TimerOverrun = FALSE;
static TIMER 	Timer[MAX_TIMERS];
static uint32	NewTime, OldTime;

/*******************************************************/
CY_ISR(isr_timer_routine)
{
	TimerOverrun = TRUE;
}


/*******************************************************/
STATUS 	TMR_Init(void)
{
	NewTime = OldTime = 0;
	memset(Timer, 0, sizeof(Timer));
	
	TIMER_Init();
	Isr_timer_SetVector(isr_timer_routine);
	Isr_timer_Start();
	TIMER_WritePeriod(TIMER_PERIOD_1000SEC); //clock 1MHz
	TIMER_Enable();
	TIMER_CLOCK_Start();
	
	return SUCCESS;
}

/*******************************************************/
void TMR_SetTimer(uint8 numTimer, uint32 us, TMR_FUNC func, uint8 mode, uint8 status)
{
	Timer[numTimer].count = 0;
	Timer[numTimer].value = us;
	Timer[numTimer].func = func;
	Timer[numTimer].mode = mode;
	Timer[numTimer].status = status;
}



/*******************************************************/
void TMR_HandleTask(void)
{
	uint8 i;
	uint32 timediff;
	
	/* get new time */
	NewTime = TIMER_ReadCounter();
	
	/* this variable is set by isr when timer runs over */
	if (TimerOverrun == TRUE)
	{
		timediff = TIMER_PERIOD_1000SEC - OldTime + NewTime;
		TimerOverrun = FALSE;
	}
	else
	{
		timediff = NewTime - OldTime;
	}
	
	OldTime = NewTime;
	
	/* update timers */
	for (i=0; i<MAX_TIMERS; i++)
	{
		if (Timer[i].status == TIMER_ENABLED)
		{
			/* increase timer */
			Timer[i].count += timediff;
			if (Timer[i].count >= Timer[i].value)
			{
				/* call timer down function */
				Timer[i].func();
				if (Timer[i].mode != TIMER_MODE_CONTINUOUS)
				{
					Timer[i].status = TIMER_DISABLED;
				}
				Timer[i].count = 0;
			}
		}
	}
	
	
}



/* [] END OF FILE */
