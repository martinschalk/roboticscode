/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#include <project.h>
#include "servo_cds5500.h"
#include "hal.h"
#include "bpl.h"
#include "tmr.h"
#include "test.h"

#include "global.h"

int main()
{
	STATUS status;
	
	/* Initialization */
	/* -------------- */
	CyGlobalIntEnable; /* Enable interrupts */
	status = HAL_Init();
	status = TMR_Init();
#ifdef TEST_UART
	TST_Init();
#endif

    for(;;)
    {
        /* Bus handler */
		BPL_HandleTask();
        
        /* Bus abstraction layer handler (not yet containing any functionality) */
        BAL_Handler();
		
		/* Timer Handler */
		TMR_HandleTask();

#ifdef TEST_UART        
        /* Test Handler */
        TST_HandleTask();
#endif
    }
	
	(void)status;
}

/* [] END OF FILE */
