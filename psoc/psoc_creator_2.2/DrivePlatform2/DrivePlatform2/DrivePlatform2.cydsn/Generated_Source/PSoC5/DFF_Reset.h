/*******************************************************************************
* File Name: DFF_Reset.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_DFF_Reset_H) /* Pins DFF_Reset_H */
#define CY_PINS_DFF_Reset_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DFF_Reset_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DFF_Reset__PORT == 15 && ((DFF_Reset__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    DFF_Reset_Write(uint8 value) ;
void    DFF_Reset_SetDriveMode(uint8 mode) ;
uint8   DFF_Reset_ReadDataReg(void) ;
uint8   DFF_Reset_Read(void) ;
uint8   DFF_Reset_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define DFF_Reset_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define DFF_Reset_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define DFF_Reset_DM_RES_UP          PIN_DM_RES_UP
#define DFF_Reset_DM_RES_DWN         PIN_DM_RES_DWN
#define DFF_Reset_DM_OD_LO           PIN_DM_OD_LO
#define DFF_Reset_DM_OD_HI           PIN_DM_OD_HI
#define DFF_Reset_DM_STRONG          PIN_DM_STRONG
#define DFF_Reset_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define DFF_Reset_MASK               DFF_Reset__MASK
#define DFF_Reset_SHIFT              DFF_Reset__SHIFT
#define DFF_Reset_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DFF_Reset_PS                     (* (reg8 *) DFF_Reset__PS)
/* Data Register */
#define DFF_Reset_DR                     (* (reg8 *) DFF_Reset__DR)
/* Port Number */
#define DFF_Reset_PRT_NUM                (* (reg8 *) DFF_Reset__PRT) 
/* Connect to Analog Globals */                                                  
#define DFF_Reset_AG                     (* (reg8 *) DFF_Reset__AG)                       
/* Analog MUX bux enable */
#define DFF_Reset_AMUX                   (* (reg8 *) DFF_Reset__AMUX) 
/* Bidirectional Enable */                                                        
#define DFF_Reset_BIE                    (* (reg8 *) DFF_Reset__BIE)
/* Bit-mask for Aliased Register Access */
#define DFF_Reset_BIT_MASK               (* (reg8 *) DFF_Reset__BIT_MASK)
/* Bypass Enable */
#define DFF_Reset_BYP                    (* (reg8 *) DFF_Reset__BYP)
/* Port wide control signals */                                                   
#define DFF_Reset_CTL                    (* (reg8 *) DFF_Reset__CTL)
/* Drive Modes */
#define DFF_Reset_DM0                    (* (reg8 *) DFF_Reset__DM0) 
#define DFF_Reset_DM1                    (* (reg8 *) DFF_Reset__DM1)
#define DFF_Reset_DM2                    (* (reg8 *) DFF_Reset__DM2) 
/* Input Buffer Disable Override */
#define DFF_Reset_INP_DIS                (* (reg8 *) DFF_Reset__INP_DIS)
/* LCD Common or Segment Drive */
#define DFF_Reset_LCD_COM_SEG            (* (reg8 *) DFF_Reset__LCD_COM_SEG)
/* Enable Segment LCD */
#define DFF_Reset_LCD_EN                 (* (reg8 *) DFF_Reset__LCD_EN)
/* Slew Rate Control */
#define DFF_Reset_SLW                    (* (reg8 *) DFF_Reset__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DFF_Reset_PRTDSI__CAPS_SEL       (* (reg8 *) DFF_Reset__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DFF_Reset_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DFF_Reset__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DFF_Reset_PRTDSI__OE_SEL0        (* (reg8 *) DFF_Reset__PRTDSI__OE_SEL0) 
#define DFF_Reset_PRTDSI__OE_SEL1        (* (reg8 *) DFF_Reset__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DFF_Reset_PRTDSI__OUT_SEL0       (* (reg8 *) DFF_Reset__PRTDSI__OUT_SEL0) 
#define DFF_Reset_PRTDSI__OUT_SEL1       (* (reg8 *) DFF_Reset__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DFF_Reset_PRTDSI__SYNC_OUT       (* (reg8 *) DFF_Reset__PRTDSI__SYNC_OUT) 


#if defined(DFF_Reset__INTSTAT)  /* Interrupt Registers */

    #define DFF_Reset_INTSTAT                (* (reg8 *) DFF_Reset__INTSTAT)
    #define DFF_Reset_SNAP                   (* (reg8 *) DFF_Reset__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DFF_Reset_H */


/* [] END OF FILE */
