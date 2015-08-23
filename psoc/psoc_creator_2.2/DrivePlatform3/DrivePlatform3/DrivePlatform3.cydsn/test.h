/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#ifndef TEST_H
#define TEST_H


#define TEST_BLINK

//typedef void (*TEST_FUNC)(void);

//void TST_SetModuleTest(TEST_FUNC* testFunction);
STATUS TST_Init(void);
STATUS TST_HandleTask(void);

#endif /* TEST_H */

