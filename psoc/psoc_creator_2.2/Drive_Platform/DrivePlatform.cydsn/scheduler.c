/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#include <project.h>
#include "scheduler.h"

#include "hal.h"
#include "tmr.h"
#include "bpl.h"
#include "bal.h"

static int          SCH_TaskIndex = 0;
static SCH_TASK 	SCH_Task[SCH_TASK_NUM] =
{
/*   NAME   STATUS          PRIO    INIT        HANDLER         DEPENDENCY */
/*   --------------------------------------------------------------------- */
    {"HAL", SCH_TASK_NEW,   1,      HAL_Init,   NULL,           DEP_NONE},
    {"TMR", SCH_TASK_NEW,   1,      TMR_Init,   TMR_HandleTask, DEP_NONE},
    {"BPL", SCH_TASK_NEW,   2,      NULL,       BPL_HandleTask, "HAL"},
    {"BAL", SCH_TASK_NEW,   2,      BAL_Init,   BAL_HandleTask, "BPL"}
};
/* currently only one dependency possible */


/*****************************************************************/
static uchar SCH_GetTaskIndex(uchar* taskName)
{
    int i;
    uchar idx = (uchar)(-1);
    
    for (i=0; i<SCH_TASK_NUM; i++)
    {
        if (0 == strcmp(SCH_Task[SCH_TaskIndex].name, taskName))
            idx = i;
    }
    
    return idx;
}


/*****************************************************************/
void SCH_TaskHandler()
{
    STATUS status;
    uchar depTaskIndex;
    BOOL taskInitFlag = FALSE;

    //priority not handled yet

    switch(SCH_Task[SCH_TaskIndex].status)
    {                               
        case SCH_TASK_NEW:          /* check if current task has a dependency */
                                    if (DEP_NONE != (SCH_Task[SCH_TaskIndex].dependency)[0])
                                    {
                                        /* get task index of dependent task and check task status */
                                        depTaskIndex = SCH_GetTaskIndex(SCH_Task[SCH_TaskIndex].dependency);
                                        
                                        /* check if dependent task is initialzed */
                                        if (SCH_Task[depTaskIndex].status != SCH_TASK_NEW)
                                        {
                                            /* current task can be initialized */
                                            taskInitFlag = TRUE;
                                        }
                                        else
                                        {
                                            /* do nothing */
                                        }
                                    }
                                    else
                                    {
                                        /* current task can be initialized */
                                        taskInitFlag = TRUE;
                                    }
                                    
                                    
                                    
                                    
                                    if (taskInitFlag == TRUE)
                                    {
                                        /* call init function of current task */
                                        if (NULL != SCH_Task[SCH_TaskIndex].init)
                                        {
                                            status = SCH_Task[SCH_TaskIndex].init();
                                            if (status == SUCCESS)
                                            {
                                                SCH_Task[SCH_TaskIndex].status = SCH_TASK_READY;
                                            }
                                        }
                                        else
                                        {
                                            SCH_Task[SCH_TaskIndex].status = SCH_TASK_READY;
                                        }
                                    }
                                    

                                    break;

        case SCH_TASK_READY:        SCH_Task[SCH_TaskIndex].status = SCH_TASK_RUNNING;
                                    break;
                               
        case SCH_TASK_RUNNING:      if (NULL != SCH_Task[SCH_TaskIndex].func)
                                    {
                                        status = SCH_Task[SCH_TaskIndex].func();
                                    }
                                    else
                                    {
                                        SCH_Task[SCH_TaskIndex].status = SCH_TASK_TERMINATED;
                                    }
                                    break;

        case SCH_TASK_WAITING:      SCH_Task[SCH_TaskIndex].status = SCH_TASK_RUNNING;
                                    break;
                                    
        case SCH_TASK_TERMINATED:
        default:                    break;
    }
    

    
    SCH_TaskIndex++;
    
    if (SCH_TaskIndex > SCH_TASK_NUM)
        SCH_TaskIndex = 0;
}



/*****************************************************************/
#ifdef SCH_DEBUG
#include <stdio.h>
static uchar SCH_TaskBuffer[1024];
static int n=0;

void SCH_ShowCurrentTasks(void)
{
    int i;
    
    n += sprintf(SCH_TaskBuffer + n, "\n===");
    
    for (i=0; i<SCH_TASK_NUM; i++)
    {
        if (NULL != SCH_Task[i].name)
        {
            n += sprintf(SCH_TaskBuffer + n, "\nTask %i: %s/", i, SCH_Task[i].name);
        
            switch (SCH_Task[i].status)
            {
                case SCH_TASK_NEW:          n += sprintf(SCH_TaskBuffer + n, "NEW");
                                            break;
                case SCH_TASK_READY:        n += sprintf(SCH_TaskBuffer + n, "READY");
                                            break;
                case SCH_TASK_RUNNING:      n += sprintf(SCH_TaskBuffer + n, "RUNNING");
                                            break;
                case SCH_TASK_WAITING:      n += sprintf(SCH_TaskBuffer + n, "WAITING");
                                            break;
                case SCH_TASK_TERMINATED:   n += sprintf(SCH_TaskBuffer + n, "TERMINATED");
                                            break;
                default:                    break;                                
            }
            
            n += sprintf(SCH_TaskBuffer + n, " %s\n", SCH_Task[i].dependency);
            if ((n+64)>1024)
                n=0;
        }
    }
}
#endif