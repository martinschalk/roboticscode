/*******************************************************************************
* File Name: UART_SERVO_PM.c
* Version 2.30
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_SERVO.h"


/***************************************
* Local data allocation
***************************************/

static UART_SERVO_BACKUP_STRUCT  UART_SERVO_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: UART_SERVO_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_SERVO_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_SERVO_SaveConfig(void)
{
    #if (CY_UDB_V0)

        #if(UART_SERVO_CONTROL_REG_REMOVED == 0u)
            UART_SERVO_backup.cr = UART_SERVO_CONTROL_REG;
        #endif /* End UART_SERVO_CONTROL_REG_REMOVED */

        #if( (UART_SERVO_RX_ENABLED) || (UART_SERVO_HD_ENABLED) )
            UART_SERVO_backup.rx_period = UART_SERVO_RXBITCTR_PERIOD_REG;
            UART_SERVO_backup.rx_mask = UART_SERVO_RXSTATUS_MASK_REG;
            #if (UART_SERVO_RXHW_ADDRESS_ENABLED)
                UART_SERVO_backup.rx_addr1 = UART_SERVO_RXADDRESS1_REG;
                UART_SERVO_backup.rx_addr2 = UART_SERVO_RXADDRESS2_REG;
            #endif /* End UART_SERVO_RXHW_ADDRESS_ENABLED */
        #endif /* End UART_SERVO_RX_ENABLED | UART_SERVO_HD_ENABLED*/

        #if(UART_SERVO_TX_ENABLED)
            #if(UART_SERVO_TXCLKGEN_DP)
                UART_SERVO_backup.tx_clk_ctr = UART_SERVO_TXBITCLKGEN_CTR_REG;
                UART_SERVO_backup.tx_clk_compl = UART_SERVO_TXBITCLKTX_COMPLETE_REG;
            #else
                UART_SERVO_backup.tx_period = UART_SERVO_TXBITCTR_PERIOD_REG;
            #endif /*End UART_SERVO_TXCLKGEN_DP */
            UART_SERVO_backup.tx_mask = UART_SERVO_TXSTATUS_MASK_REG;
        #endif /*End UART_SERVO_TX_ENABLED */


    #else /* CY_UDB_V1 */

        #if(UART_SERVO_CONTROL_REG_REMOVED == 0u)
            UART_SERVO_backup.cr = UART_SERVO_CONTROL_REG;
        #endif /* End UART_SERVO_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: UART_SERVO_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_SERVO_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_SERVO_RestoreConfig(void)
{

    #if (CY_UDB_V0)

        #if(UART_SERVO_CONTROL_REG_REMOVED == 0u)
            UART_SERVO_CONTROL_REG = UART_SERVO_backup.cr;
        #endif /* End UART_SERVO_CONTROL_REG_REMOVED */

        #if( (UART_SERVO_RX_ENABLED) || (UART_SERVO_HD_ENABLED) )
            UART_SERVO_RXBITCTR_PERIOD_REG = UART_SERVO_backup.rx_period;
            UART_SERVO_RXSTATUS_MASK_REG = UART_SERVO_backup.rx_mask;
            #if (UART_SERVO_RXHW_ADDRESS_ENABLED)
                UART_SERVO_RXADDRESS1_REG = UART_SERVO_backup.rx_addr1;
                UART_SERVO_RXADDRESS2_REG = UART_SERVO_backup.rx_addr2;
            #endif /* End UART_SERVO_RXHW_ADDRESS_ENABLED */
        #endif  /* End (UART_SERVO_RX_ENABLED) || (UART_SERVO_HD_ENABLED) */

        #if(UART_SERVO_TX_ENABLED)
            #if(UART_SERVO_TXCLKGEN_DP)
                UART_SERVO_TXBITCLKGEN_CTR_REG = UART_SERVO_backup.tx_clk_ctr;
                UART_SERVO_TXBITCLKTX_COMPLETE_REG = UART_SERVO_backup.tx_clk_compl;
            #else
                UART_SERVO_TXBITCTR_PERIOD_REG = UART_SERVO_backup.tx_period;
            #endif /*End UART_SERVO_TXCLKGEN_DP */
            UART_SERVO_TXSTATUS_MASK_REG = UART_SERVO_backup.tx_mask;
        #endif /*End UART_SERVO_TX_ENABLED */

    #else /* CY_UDB_V1 */

        #if(UART_SERVO_CONTROL_REG_REMOVED == 0u)
            UART_SERVO_CONTROL_REG = UART_SERVO_backup.cr;
        #endif /* End UART_SERVO_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: UART_SERVO_Sleep
********************************************************************************
*
* Summary:
*  Stops and saves the user configuration. Should be called
*  just prior to entering sleep.
*
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_SERVO_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_SERVO_Sleep(void)
{

    #if(UART_SERVO_RX_ENABLED || UART_SERVO_HD_ENABLED)
        if((UART_SERVO_RXSTATUS_ACTL_REG  & UART_SERVO_INT_ENABLE) != 0u)
        {
            UART_SERVO_backup.enableState = 1u;
        }
        else
        {
            UART_SERVO_backup.enableState = 0u;
        }
    #else
        if((UART_SERVO_TXSTATUS_ACTL_REG  & UART_SERVO_INT_ENABLE) !=0u)
        {
            UART_SERVO_backup.enableState = 1u;
        }
        else
        {
            UART_SERVO_backup.enableState = 0u;
        }
    #endif /* End UART_SERVO_RX_ENABLED || UART_SERVO_HD_ENABLED*/

    UART_SERVO_Stop();
    UART_SERVO_SaveConfig();
}


/*******************************************************************************
* Function Name: UART_SERVO_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_SERVO_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_SERVO_Wakeup(void)
{
    UART_SERVO_RestoreConfig();
    #if( (UART_SERVO_RX_ENABLED) || (UART_SERVO_HD_ENABLED) )
        UART_SERVO_ClearRxBuffer();
    #endif /* End (UART_SERVO_RX_ENABLED) || (UART_SERVO_HD_ENABLED) */
    #if(UART_SERVO_TX_ENABLED || UART_SERVO_HD_ENABLED)
        UART_SERVO_ClearTxBuffer();
    #endif /* End UART_SERVO_TX_ENABLED || UART_SERVO_HD_ENABLED */

    if(UART_SERVO_backup.enableState != 0u)
    {
        UART_SERVO_Enable();
    }
}


/* [] END OF FILE */
