/*******************************************************************************
* File Name: Isr_rx.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Isr_rx_H)
#define CY_ISR_Isr_rx_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Isr_rx_Start(void);
void Isr_rx_StartEx(cyisraddress address);
void Isr_rx_Stop(void);

CY_ISR_PROTO(Isr_rx_Interrupt);

void Isr_rx_SetVector(cyisraddress address);
cyisraddress Isr_rx_GetVector(void);

void Isr_rx_SetPriority(uint8 priority);
uint8 Isr_rx_GetPriority(void);

void Isr_rx_Enable(void);
uint8 Isr_rx_GetState(void);
void Isr_rx_Disable(void);

void Isr_rx_SetPending(void);
void Isr_rx_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Isr_rx ISR. */
#define Isr_rx_INTC_VECTOR            ((reg32 *) Isr_rx__INTC_VECT)

/* Address of the Isr_rx ISR priority. */
#define Isr_rx_INTC_PRIOR             ((reg8 *) Isr_rx__INTC_PRIOR_REG)

/* Priority of the Isr_rx interrupt. */
#define Isr_rx_INTC_PRIOR_NUMBER      Isr_rx__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Isr_rx interrupt. */
#define Isr_rx_INTC_SET_EN            ((reg32 *) Isr_rx__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Isr_rx interrupt. */
#define Isr_rx_INTC_CLR_EN            ((reg32 *) Isr_rx__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Isr_rx interrupt state to pending. */
#define Isr_rx_INTC_SET_PD            ((reg32 *) Isr_rx__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Isr_rx interrupt. */
#define Isr_rx_INTC_CLR_PD            ((reg32 *) Isr_rx__INTC_CLR_PD_REG)


#endif /* CY_ISR_Isr_rx_H */


/* [] END OF FILE */
