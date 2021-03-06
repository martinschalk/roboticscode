/*******************************************************************************
* File Name: TIMER_CLOCK.h
* Version 2.20
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

#if !defined(CY_CLOCK_TIMER_CLOCK_H)
#define CY_CLOCK_TIMER_CLOCK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void TIMER_CLOCK_Start(void) ;
void TIMER_CLOCK_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void TIMER_CLOCK_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void TIMER_CLOCK_StandbyPower(uint8 state) ;
void TIMER_CLOCK_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 TIMER_CLOCK_GetDividerRegister(void) ;
void TIMER_CLOCK_SetModeRegister(uint8 modeBitMask) ;
void TIMER_CLOCK_ClearModeRegister(uint8 modeBitMask) ;
uint8 TIMER_CLOCK_GetModeRegister(void) ;
void TIMER_CLOCK_SetSourceRegister(uint8 clkSource) ;
uint8 TIMER_CLOCK_GetSourceRegister(void) ;
#if defined(TIMER_CLOCK__CFG3)
void TIMER_CLOCK_SetPhaseRegister(uint8 clkPhase) ;
uint8 TIMER_CLOCK_GetPhaseRegister(void) ;
#endif /* defined(TIMER_CLOCK__CFG3) */

#define TIMER_CLOCK_Enable()                       TIMER_CLOCK_Start()
#define TIMER_CLOCK_Disable()                      TIMER_CLOCK_Stop()
#define TIMER_CLOCK_SetDivider(clkDivider)         TIMER_CLOCK_SetDividerRegister(clkDivider, 1u)
#define TIMER_CLOCK_SetDividerValue(clkDivider)    TIMER_CLOCK_SetDividerRegister((clkDivider) - 1u, 1u)
#define TIMER_CLOCK_SetMode(clkMode)               TIMER_CLOCK_SetModeRegister(clkMode)
#define TIMER_CLOCK_SetSource(clkSource)           TIMER_CLOCK_SetSourceRegister(clkSource)
#if defined(TIMER_CLOCK__CFG3)
#define TIMER_CLOCK_SetPhase(clkPhase)             TIMER_CLOCK_SetPhaseRegister(clkPhase)
#define TIMER_CLOCK_SetPhaseValue(clkPhase)        TIMER_CLOCK_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(TIMER_CLOCK__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define TIMER_CLOCK_CLKEN              (* (reg8 *) TIMER_CLOCK__PM_ACT_CFG)
#define TIMER_CLOCK_CLKEN_PTR          ((reg8 *) TIMER_CLOCK__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define TIMER_CLOCK_CLKSTBY            (* (reg8 *) TIMER_CLOCK__PM_STBY_CFG)
#define TIMER_CLOCK_CLKSTBY_PTR        ((reg8 *) TIMER_CLOCK__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define TIMER_CLOCK_DIV_LSB            (* (reg8 *) TIMER_CLOCK__CFG0)
#define TIMER_CLOCK_DIV_LSB_PTR        ((reg8 *) TIMER_CLOCK__CFG0)
#define TIMER_CLOCK_DIV_PTR            ((reg16 *) TIMER_CLOCK__CFG0)

/* Clock MSB divider configuration register. */
#define TIMER_CLOCK_DIV_MSB            (* (reg8 *) TIMER_CLOCK__CFG1)
#define TIMER_CLOCK_DIV_MSB_PTR        ((reg8 *) TIMER_CLOCK__CFG1)

/* Mode and source configuration register */
#define TIMER_CLOCK_MOD_SRC            (* (reg8 *) TIMER_CLOCK__CFG2)
#define TIMER_CLOCK_MOD_SRC_PTR        ((reg8 *) TIMER_CLOCK__CFG2)

#if defined(TIMER_CLOCK__CFG3)
/* Analog clock phase configuration register */
#define TIMER_CLOCK_PHASE              (* (reg8 *) TIMER_CLOCK__CFG3)
#define TIMER_CLOCK_PHASE_PTR          ((reg8 *) TIMER_CLOCK__CFG3)
#endif /* defined(TIMER_CLOCK__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define TIMER_CLOCK_CLKEN_MASK         TIMER_CLOCK__PM_ACT_MSK
#define TIMER_CLOCK_CLKSTBY_MASK       TIMER_CLOCK__PM_STBY_MSK

/* CFG2 field masks */
#define TIMER_CLOCK_SRC_SEL_MSK        TIMER_CLOCK__CFG2_SRC_SEL_MASK
#define TIMER_CLOCK_MODE_MASK          (~(TIMER_CLOCK_SRC_SEL_MSK))

#if defined(TIMER_CLOCK__CFG3)
/* CFG3 phase mask */
#define TIMER_CLOCK_PHASE_MASK         TIMER_CLOCK__CFG3_PHASE_DLY_MASK
#endif /* defined(TIMER_CLOCK__CFG3) */

#endif /* CY_CLOCK_TIMER_CLOCK_H */


/* [] END OF FILE */
