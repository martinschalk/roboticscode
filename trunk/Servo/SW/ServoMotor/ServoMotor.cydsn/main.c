/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#include <project.h>
#include "servo_cds5500.h"
#include "bus.h"
#include "global.h"

int main()
{
	STATUS status; 
    /* Initialization */
	BUS_Init();
	UART_SERVO_Init();
	UART_SERVO_EnableRxInt();
	UART_SERVO_Start();
	
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Bus handler */
		status = BUS_Handler();
    }
}

/* [] END OF FILE */
