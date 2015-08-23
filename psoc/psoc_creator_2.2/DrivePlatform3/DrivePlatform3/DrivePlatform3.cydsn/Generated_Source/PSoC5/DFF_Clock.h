/*******************************************************************************
* File Name: DFF_Clock.h
* Version 2.0
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_DFF_Clock_H)
#define CY_CLOCK_DFF_Clock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void DFF_Clock_Start(void) ;
void DFF_Clock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void DFF_Clock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void DFF_Clock_StandbyPower(uint8 state) ;
void DFF_Clock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 DFF_Clock_GetDividerRegister(void) ;
void DFF_Clock_SetModeRegister(uint8 modeBitMask) ;
void DFF_Clock_ClearModeRegister(uint8 modeBitMask) ;
uint8 DFF_Clock_GetModeRegister(void) ;
void DFF_Clock_SetSourceRegister(uint8 clkSource) ;
uint8 DFF_Clock_GetSourceRegister(void) ;
#if defined(DFF_Clock__CFG3)
void DFF_Clock_SetPhaseRegister(uint8 clkPhase) ;
uint8 DFF_Clock_GetPhaseRegister(void) ;
#endif /* defined(DFF_Clock__CFG3) */

#define DFF_Clock_Enable()                       DFF_Clock_Start()
#define DFF_Clock_Disable()                      DFF_Clock_Stop()
#define DFF_Clock_SetDivider(clkDivider)         DFF_Clock_SetDividerRegister(clkDivider, 1)
#define DFF_Clock_SetDividerValue(clkDivider)    DFF_Clock_SetDividerRegister((clkDivider) - 1, 1)
#define DFF_Clock_SetMode(clkMode)               DFF_Clock_SetModeRegister(clkMode)
#define DFF_Clock_SetSource(clkSource)           DFF_Clock_SetSourceRegister(clkSource)
#if defined(DFF_Clock__CFG3)
#define DFF_Clock_SetPhase(clkPhase)             DFF_Clock_SetPhaseRegister(clkPhase)
#define DFF_Clock_SetPhaseValue(clkPhase)        DFF_Clock_SetPhaseRegister((clkPhase) + 1)
#endif /* defined(DFF_Clock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define DFF_Clock_CLKEN              (* (reg8 *) DFF_Clock__PM_ACT_CFG)
#define DFF_Clock_CLKEN_PTR          ((reg8 *) DFF_Clock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define DFF_Clock_CLKSTBY            (* (reg8 *) DFF_Clock__PM_STBY_CFG)
#define DFF_Clock_CLKSTBY_PTR        ((reg8 *) DFF_Clock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define DFF_Clock_DIV_LSB            (* (reg8 *) DFF_Clock__CFG0)
#define DFF_Clock_DIV_LSB_PTR        ((reg8 *) DFF_Clock__CFG0)
#define DFF_Clock_DIV_PTR            ((reg16 *) DFF_Clock__CFG0)

/* Clock MSB divider configuration register. */
#define DFF_Clock_DIV_MSB            (* (reg8 *) DFF_Clock__CFG1)
#define DFF_Clock_DIV_MSB_PTR        ((reg8 *) DFF_Clock__CFG1)

/* Mode and source configuration register */
#define DFF_Clock_MOD_SRC            (* (reg8 *) DFF_Clock__CFG2)
#define DFF_Clock_MOD_SRC_PTR        ((reg8 *) DFF_Clock__CFG2)

#if defined(DFF_Clock__CFG3)
/* Analog clock phase configuration register */
#define DFF_Clock_PHASE              (* (reg8 *) DFF_Clock__CFG3)
#define DFF_Clock_PHASE_PTR          ((reg8 *) DFF_Clock__CFG3)
#endif /* defined(DFF_Clock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define DFF_Clock_CLKEN_MASK         DFF_Clock__PM_ACT_MSK
#define DFF_Clock_CLKSTBY_MASK       DFF_Clock__PM_STBY_MSK

/* CFG2 field masks */
#define DFF_Clock_SRC_SEL_MSK        DFF_Clock__CFG2_SRC_SEL_MASK
#define DFF_Clock_MODE_MASK          (~(DFF_Clock_SRC_SEL_MSK))

#if defined(DFF_Clock__CFG3)
/* CFG3 phase mask */
#define DFF_Clock_PHASE_MASK         DFF_Clock__CFG3_PHASE_DLY_MASK
#endif /* defined(DFF_Clock__CFG3) */

#endif /* CY_CLOCK_DFF_Clock_H */


/* [] END OF FILE */
