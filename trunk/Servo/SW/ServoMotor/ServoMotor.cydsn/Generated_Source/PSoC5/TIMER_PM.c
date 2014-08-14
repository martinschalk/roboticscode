/*******************************************************************************
* File Name: TIMER_PM.c
* Version 2.50
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "TIMER.h"
static TIMER_backupStruct TIMER_backup;


/*******************************************************************************
* Function Name: TIMER_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TIMER_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void TIMER_SaveConfig(void) 
{
    #if (!TIMER_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            TIMER_backup.TimerUdb = TIMER_ReadCounter();
            TIMER_backup.TimerPeriod = TIMER_ReadPeriod();
            TIMER_backup.InterruptMaskValue = TIMER_STATUS_MASK;
            #if (TIMER_UsingHWCaptureCounter)
                TIMER_backup.TimerCaptureCounter = TIMER_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Backup the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            TIMER_backup.TimerUdb = TIMER_ReadCounter();
            TIMER_backup.InterruptMaskValue = TIMER_STATUS_MASK;
            #if (TIMER_UsingHWCaptureCounter)
                TIMER_backup.TimerCaptureCounter = TIMER_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!TIMER_ControlRegRemoved)
            TIMER_backup.TimerControlRegister = TIMER_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: TIMER_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TIMER_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TIMER_RestoreConfig(void) 
{   
    #if (!TIMER_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            /* Interrupt State Backup for Critical Region*/
            uint8 TIMER_interruptState;

            TIMER_WriteCounter(TIMER_backup.TimerUdb);
            TIMER_WritePeriod(TIMER_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            TIMER_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            TIMER_STATUS_AUX_CTRL |= TIMER_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(TIMER_interruptState);
            TIMER_STATUS_MASK =TIMER_backup.InterruptMaskValue;
            #if (TIMER_UsingHWCaptureCounter)
                TIMER_SetCaptureCount(TIMER_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Restore the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            TIMER_WriteCounter(TIMER_backup.TimerUdb);
            TIMER_STATUS_MASK =TIMER_backup.InterruptMaskValue;
            #if (TIMER_UsingHWCaptureCounter)
                TIMER_SetCaptureCount(TIMER_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!TIMER_ControlRegRemoved)
            TIMER_WriteControlRegister(TIMER_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: TIMER_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TIMER_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void TIMER_Sleep(void) 
{
    #if(!TIMER_ControlRegRemoved)
        /* Save Counter's enable state */
        if(TIMER_CTRL_ENABLE == (TIMER_CONTROL & TIMER_CTRL_ENABLE))
        {
            /* Timer is enabled */
            TIMER_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            TIMER_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    TIMER_Stop();
    TIMER_SaveConfig();
}


/*******************************************************************************
* Function Name: TIMER_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TIMER_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TIMER_Wakeup(void) 
{
    TIMER_RestoreConfig();
    #if(!TIMER_ControlRegRemoved)
        if(TIMER_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                TIMER_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
