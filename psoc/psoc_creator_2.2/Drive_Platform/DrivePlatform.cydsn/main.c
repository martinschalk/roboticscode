/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#include <project.h>
#include "servo_cds5500.h"
#include "bal.h"
#include "hal.h"
#include "bpl.h"
#include "tmr.h"
#include "test.h"
#include "scheduler.h"

#include "global.h"

int main()
{
	STATUS status;
    
#ifdef SCH_DEBUG    
    int loopCount=0;
    uchar debug = 1;
#endif

	/* Initialization */
	/* -------------- */
	CyGlobalIntEnable; /* Enable interrupts */


#ifdef SCH_DEBUG
    SCH_ShowCurrentTasks();
#endif

    for(;;)
    {
        SCH_TaskHandler();

#ifdef SCH_DEBUG
        if ((debug == 1) && (++loopCount > 10)) 
        {
            SCH_ShowCurrentTasks();
            debug = 0;
        }
#endif


    }
	
	(void)status;
}

/* [] END OF FILE */
