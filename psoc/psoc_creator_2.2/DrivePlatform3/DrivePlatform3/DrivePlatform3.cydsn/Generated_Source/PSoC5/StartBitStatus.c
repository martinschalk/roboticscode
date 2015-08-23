/*******************************************************************************
* File Name: StartBitStatus.c  
* Version 1.80
*
* Description:
*  This file contains API to enable firmware to read the value of a Status 
*  Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "StartBitStatus.h"

#if !defined(StartBitStatus_sts_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: StartBitStatus_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The current value in the Status Register.
*
*******************************************************************************/
uint8 StartBitStatus_Read(void) 
{ 
    return StartBitStatus_Status;
}


/*******************************************************************************
* Function Name: StartBitStatus_InterruptEnable
********************************************************************************
*
* Summary:
*  Enables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void StartBitStatus_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    StartBitStatus_Status_Aux_Ctrl |= StartBitStatus_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: StartBitStatus_InterruptDisable
********************************************************************************
*
* Summary:
*  Disables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void StartBitStatus_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    StartBitStatus_Status_Aux_Ctrl &= (uint8)(~StartBitStatus_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: StartBitStatus_WriteMask
********************************************************************************
*
* Summary:
*  Writes the current mask value assigned to the Status Register.
*
* Parameters:
*  mask:  Value to write into the mask register.
*
* Return:
*  None.
*
*******************************************************************************/
void StartBitStatus_WriteMask(uint8 mask) 
{
    #if(StartBitStatus_INPUTS < 8u)
    	mask &= (uint8)((((uint8)1u) << StartBitStatus_INPUTS) - 1u);
	#endif /* End StartBitStatus_INPUTS < 8u */
    StartBitStatus_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: StartBitStatus_ReadMask
********************************************************************************
*
* Summary:
*  Reads the current interrupt mask assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the interrupt mask of the Status Register.
*
*******************************************************************************/
uint8 StartBitStatus_ReadMask(void) 
{
    return StartBitStatus_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
