/*******************************************************************************
* File Name: CharLCD_1_LCDPort.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "CharLCD_1_LCDPort.h"


/*******************************************************************************
* Function Name: CharLCD_1_LCDPort_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void CharLCD_1_LCDPort_Write(uint8 value) 
{
    uint8 staticBits = (CharLCD_1_LCDPort_DR & (uint8)(~CharLCD_1_LCDPort_MASK));
    CharLCD_1_LCDPort_DR = staticBits | ((uint8)(value << CharLCD_1_LCDPort_SHIFT) & CharLCD_1_LCDPort_MASK);
}


/*******************************************************************************
* Function Name: CharLCD_1_LCDPort_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void CharLCD_1_LCDPort_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(CharLCD_1_LCDPort_0, mode);
	CyPins_SetPinDriveMode(CharLCD_1_LCDPort_1, mode);
	CyPins_SetPinDriveMode(CharLCD_1_LCDPort_2, mode);
	CyPins_SetPinDriveMode(CharLCD_1_LCDPort_3, mode);
	CyPins_SetPinDriveMode(CharLCD_1_LCDPort_4, mode);
	CyPins_SetPinDriveMode(CharLCD_1_LCDPort_5, mode);
	CyPins_SetPinDriveMode(CharLCD_1_LCDPort_6, mode);
}


/*******************************************************************************
* Function Name: CharLCD_1_LCDPort_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro CharLCD_1_LCDPort_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 CharLCD_1_LCDPort_Read(void) 
{
    return (CharLCD_1_LCDPort_PS & CharLCD_1_LCDPort_MASK) >> CharLCD_1_LCDPort_SHIFT;
}


/*******************************************************************************
* Function Name: CharLCD_1_LCDPort_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 CharLCD_1_LCDPort_ReadDataReg(void) 
{
    return (CharLCD_1_LCDPort_DR & CharLCD_1_LCDPort_MASK) >> CharLCD_1_LCDPort_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(CharLCD_1_LCDPort_INTSTAT) 

    /*******************************************************************************
    * Function Name: CharLCD_1_LCDPort_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 CharLCD_1_LCDPort_ClearInterrupt(void) 
    {
        return (CharLCD_1_LCDPort_INTSTAT & CharLCD_1_LCDPort_MASK) >> CharLCD_1_LCDPort_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
