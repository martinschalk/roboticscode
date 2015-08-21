/*******************************************************************************
* File Name: StartBitStatus.h  
* Version 1.80
*
* Description:
*  This file containts Status Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_STATUS_REG_StartBitStatus_H) /* CY_STATUS_REG_StartBitStatus_H */
#define CY_STATUS_REG_StartBitStatus_H

#include "cytypes.h"
#include "CyLib.h"


/***************************************
*        Function Prototypes
***************************************/

uint8 StartBitStatus_Read(void) ;
void StartBitStatus_InterruptEnable(void) ;
void StartBitStatus_InterruptDisable(void) ;
void StartBitStatus_WriteMask(uint8 mask) ;
uint8 StartBitStatus_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define StartBitStatus_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define StartBitStatus_INPUTS              1


/***************************************
*             Registers
***************************************/

/* Status Register */
#define StartBitStatus_Status             (* (reg8 *) StartBitStatus_sts_sts_reg__STATUS_REG )
#define StartBitStatus_Status_PTR         (  (reg8 *) StartBitStatus_sts_sts_reg__STATUS_REG )
#define StartBitStatus_Status_Mask        (* (reg8 *) StartBitStatus_sts_sts_reg__MASK_REG )
#define StartBitStatus_Status_Aux_Ctrl    (* (reg8 *) StartBitStatus_sts_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_StartBitStatus_H */


/* [] END OF FILE */
