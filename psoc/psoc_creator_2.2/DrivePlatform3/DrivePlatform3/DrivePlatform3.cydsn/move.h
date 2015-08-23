/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */
 
#ifndef MOV_H
#define MOV_H

#include "types.h"

#define MOV_MODULE_TEST


/*****************************************************************/
extern STATUS MOV_Init(void);
/*****************************************************************/
extern STATUS MOV_HandleTask(void);
/*****************************************************************/
#ifdef MOV_MODULE_TEST
    extern void MOV_ucTest(void);
#endif



#endif //MOV_H
