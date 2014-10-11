/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

/* BUS STRUCTURE

-------------------------------------------------------------
APPLICATION LAYER			(APPL)
- Message Routines
-------------------------------------------------------------
BUS ABSTRACTION LAYER		(BAL)
- Message Handler
-------------------------------------------------------------
BUS PRESENTATION LAYER		(BPL)
- Ring Buffer
-------------------------------------------------------------
HARDWARE ABSTRACTION LAYER	(HAL)
- UART
-------------------------------------------------------------

*/

#ifndef BUS_H
#define BUS_H

#include <project.h>
#include "global.h"
#include "types.h"

/*
#define BUS_MSG_BUFFER_SIZE	16
#define BUS_LENGTH_ERROR	-1

typedef struct _bus_t_obj
{
	uint8* 	tBuffer;
	uint8	tBytes;
	BOOL	tRequest;
	BOOL	tInProgress;
}T_OBJ;


typedef struct _bus_r_obj
{
	uint8* 	rBuffer;
	uint8	rBytes;
	BOOL	rNewMsg;
	BOOL	rInProgress;
}R_OBJ;


typedef struct _bus
{
	T_OBJ	transmit;
	R_OBJ	receive;
}BUS_OBJ;

extern BUS_OBJ Bus;

STATUS BUS_Init(void);
STATUS BUS_Handler(void);

*/

#endif /* BUS_H */

/* [] END OF FILE */
