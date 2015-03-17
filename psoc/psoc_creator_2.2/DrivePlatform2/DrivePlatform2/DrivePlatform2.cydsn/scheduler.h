/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */
 
#ifndef SCHEDULER_H
#define SCHEDULER_H
 
 
#include "types.h" 


#define SCH_DEBUG

 
#define SCH_TASK_NEW            (uchar)(1<<1)
#define SCH_TASK_READY          (uchar)(1<<2)
#define SCH_TASK_RUNNING        (uchar)(1<<3)
#define SCH_TASK_WAITING        (uchar)(1<<4)
#define SCH_TASK_TERMINATED     (uchar)(1<<5)

//#define SCH_TASK_NUM            5

#define DEP_NONE                0//""



typedef STATUS (*SCH_TASK_FUNC)(void);

/* task structure */
typedef struct _scheduler_task
{
    uchar           name[8];
	uchar		    status;
    uchar           priority;
    SCH_TASK_FUNC   init;
	SCH_TASK_FUNC 	func;
    uchar           dependency[8];
}SCH_TASK;



#ifdef SCH_DEBUG
    void SCH_ShowCurrentTasks(void);
#endif

void SCH_TaskHandler(void);

#endif /* SCHEDULER_H */
