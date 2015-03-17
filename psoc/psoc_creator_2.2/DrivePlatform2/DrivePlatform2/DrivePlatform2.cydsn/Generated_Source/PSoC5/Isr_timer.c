/*******************************************************************************
* File Name: Isr_timer.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <CYDEVICE_TRM.H>
#include <CYLIB.H>
#include <Isr_timer.H>

#if !defined(Isr_timer__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START Isr_timer_intc` */

/* `#END` */

#ifndef CYINT_IRQ_BASE
#define CYINT_IRQ_BASE      16
#endif /* CYINT_IRQ_BASE */
#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif /* CYINT_VECT_TABLE */

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: Isr_timer_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void Isr_timer_Start(void)
{
    /* For all we know the interrupt is active. */
    Isr_timer_Disable();

    /* Set the ISR to point to the Isr_timer Interrupt. */
    Isr_timer_SetVector(&Isr_timer_Interrupt);

    /* Set the priority. */
    Isr_timer_SetPriority((uint8)Isr_timer_INTC_PRIOR_NUMBER);

    /* Enable it. */
    Isr_timer_Enable();
}


/*******************************************************************************
* Function Name: Isr_timer_StartEx
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void Isr_timer_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    Isr_timer_Disable();

    /* Set the ISR to point to the Isr_timer Interrupt. */
    Isr_timer_SetVector(address);

    /* Set the priority. */
    Isr_timer_SetPriority((uint8)Isr_timer_INTC_PRIOR_NUMBER);

    /* Enable it. */
    Isr_timer_Enable();
}


/*******************************************************************************
* Function Name: Isr_timer_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
void Isr_timer_Stop(void)
{
    /* Disable this interrupt. */
    Isr_timer_Disable();

    /* Set the ISR to point to the passive one. */
    Isr_timer_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: Isr_timer_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for Isr_timer.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(Isr_timer_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START Isr_timer_Interrupt` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: Isr_timer_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling Isr_timer_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use Isr_timer_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void Isr_timer_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)Isr_timer__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: Isr_timer_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress Isr_timer_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)Isr_timer__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: Isr_timer_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling Isr_timer_Start
*   or Isr_timer_StartEx will override any effect this method 
*   would have had. This method should only be called after 
*   Isr_timer_Start or Isr_timer_StartEx has been called. To set 
*   the initial priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void Isr_timer_SetPriority(uint8 priority)
{
    *Isr_timer_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: Isr_timer_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*******************************************************************************/
uint8 Isr_timer_GetPriority(void)
{
    uint8 priority;


    priority = *Isr_timer_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: Isr_timer_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void Isr_timer_Enable(void)
{
    /* Enable the general interrupt. */
    *Isr_timer_INTC_SET_EN = Isr_timer__INTC_MASK;
}


/*******************************************************************************
* Function Name: Isr_timer_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 Isr_timer_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*Isr_timer_INTC_SET_EN & (uint32)Isr_timer__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: Isr_timer_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void Isr_timer_Disable(void)
{
    /* Disable the general interrupt. */
    *Isr_timer_INTC_CLR_EN = Isr_timer__INTC_MASK;
}


/*******************************************************************************
* Function Name: Isr_timer_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void Isr_timer_SetPending(void)
{
    *Isr_timer_INTC_SET_PD = Isr_timer__INTC_MASK;
}


/*******************************************************************************
* Function Name: Isr_timer_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void Isr_timer_ClearPending(void)
{
    *Isr_timer_INTC_CLR_PD = Isr_timer__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
