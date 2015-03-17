/*******************************************************************************
* File Name: Isr_tx.h
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
#if !defined(CY_ISR_Isr_tx_H)
#define CY_ISR_Isr_tx_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Isr_tx_Start(void);
void Isr_tx_StartEx(cyisraddress address);
void Isr_tx_Stop(void);

CY_ISR_PROTO(Isr_tx_Interrupt);

void Isr_tx_SetVector(cyisraddress address);
cyisraddress Isr_tx_GetVector(void);

void Isr_tx_SetPriority(uint8 priority);
uint8 Isr_tx_GetPriority(void);

void Isr_tx_Enable(void);
uint8 Isr_tx_GetState(void);
void Isr_tx_Disable(void);

void Isr_tx_SetPending(void);
void Isr_tx_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Isr_tx ISR. */
#define Isr_tx_INTC_VECTOR            ((reg32 *) Isr_tx__INTC_VECT)

/* Address of the Isr_tx ISR priority. */
#define Isr_tx_INTC_PRIOR             ((reg8 *) Isr_tx__INTC_PRIOR_REG)

/* Priority of the Isr_tx interrupt. */
#define Isr_tx_INTC_PRIOR_NUMBER      Isr_tx__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Isr_tx interrupt. */
#define Isr_tx_INTC_SET_EN            ((reg32 *) Isr_tx__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Isr_tx interrupt. */
#define Isr_tx_INTC_CLR_EN            ((reg32 *) Isr_tx__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Isr_tx interrupt state to pending. */
#define Isr_tx_INTC_SET_PD            ((reg32 *) Isr_tx__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Isr_tx interrupt. */
#define Isr_tx_INTC_CLR_PD            ((reg32 *) Isr_tx__INTC_CLR_PD_REG)


#endif /* CY_ISR_Isr_tx_H */


/* [] END OF FILE */
