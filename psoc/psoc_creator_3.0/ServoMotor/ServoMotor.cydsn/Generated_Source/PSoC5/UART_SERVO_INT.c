/*******************************************************************************
* File Name: UART_SERVO_INT.c
* Version 2.30
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_SERVO.h"
#include "CyLib.h"


/***************************************
* Custom Declratations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if( (UART_SERVO_RX_ENABLED || UART_SERVO_HD_ENABLED) && \
     (UART_SERVO_RXBUFFERSIZE > UART_SERVO_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: UART_SERVO_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UART_SERVO_rxBuffer - RAM buffer pointer for save received data.
    *  UART_SERVO_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  UART_SERVO_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  UART_SERVO_rxBufferOverflow - software overflow flag. Set to one
    *     when UART_SERVO_rxBufferWrite index overtakes
    *     UART_SERVO_rxBufferRead index.
    *  UART_SERVO_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when UART_SERVO_rxBufferWrite is equal to
    *    UART_SERVO_rxBufferRead
    *  UART_SERVO_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  UART_SERVO_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(UART_SERVO_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0u;
        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START UART_SERVO_RXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        readData = UART_SERVO_RXSTATUS_REG;

        if((readData & (UART_SERVO_RX_STS_BREAK | UART_SERVO_RX_STS_PAR_ERROR |
                        UART_SERVO_RX_STS_STOP_ERROR | UART_SERVO_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            /* `#START UART_SERVO_RXISR_ERROR` */

            /* `#END` */
        }

        while((readData & UART_SERVO_RX_STS_FIFO_NOTEMPTY) != 0u)
        {

            #if (UART_SERVO_RXHW_ADDRESS_ENABLED)
                if(UART_SERVO_rxAddressMode == (uint8)UART_SERVO__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readData & UART_SERVO_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readData & UART_SERVO_RX_STS_ADDR_MATCH) != 0u)
                        {
                            UART_SERVO_rxAddressDetected = 1u;
                        }
                        else
                        {
                            UART_SERVO_rxAddressDetected = 0u;
                        }
                    }

                    readData = UART_SERVO_RXDATA_REG;
                    if(UART_SERVO_rxAddressDetected != 0u)
                    {   /* store only addressed data */
                        UART_SERVO_rxBuffer[UART_SERVO_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* without software addressing */
                {
                    UART_SERVO_rxBuffer[UART_SERVO_rxBufferWrite] = UART_SERVO_RXDATA_REG;
                    increment_pointer = 1u;
                }
            #else  /* without addressing */
                UART_SERVO_rxBuffer[UART_SERVO_rxBufferWrite] = UART_SERVO_RXDATA_REG;
                increment_pointer = 1u;
            #endif /* End SW_DETECT_TO_BUFFER */

            /* do not increment buffer pointer when skip not adderessed data */
            if( increment_pointer != 0u )
            {
                if(UART_SERVO_rxBufferLoopDetect != 0u)
                {   /* Set Software Buffer status Overflow */
                    UART_SERVO_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                UART_SERVO_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(UART_SERVO_rxBufferWrite >= UART_SERVO_RXBUFFERSIZE)
                {
                    UART_SERVO_rxBufferWrite = 0u;
                }
                /* Detect pre-overload condition and set flag */
                if(UART_SERVO_rxBufferWrite == UART_SERVO_rxBufferRead)
                {
                    UART_SERVO_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if(UART_SERVO_FLOW_CONTROL != 0u)
                    /* Disable RX interrupt mask, it will be enabled when user read data from the buffer using APIs */
                        UART_SERVO_RXSTATUS_MASK_REG  &= (uint8)~UART_SERVO_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(UART_SERVO_RX_VECT_NUM);
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* End UART_SERVO_FLOW_CONTROL != 0 */
                }
            }

            /* Check again if there is data. */
            readData = UART_SERVO_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START UART_SERVO_RXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End UART_SERVO_RX_ENABLED && (UART_SERVO_RXBUFFERSIZE > UART_SERVO_FIFO_LENGTH) */


#if(UART_SERVO_TX_ENABLED && (UART_SERVO_TXBUFFERSIZE > UART_SERVO_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: UART_SERVO_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UART_SERVO_txBuffer - RAM buffer pointer for transmit data from.
    *  UART_SERVO_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmited byte.
    *  UART_SERVO_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(UART_SERVO_TXISR)
    {

        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START UART_SERVO_TXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        while((UART_SERVO_txBufferRead != UART_SERVO_txBufferWrite) &&
             ((UART_SERVO_TXSTATUS_REG & UART_SERVO_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer. */
            if(UART_SERVO_txBufferRead >= UART_SERVO_TXBUFFERSIZE)
            {
                UART_SERVO_txBufferRead = 0u;
            }

            UART_SERVO_TXDATA_REG = UART_SERVO_txBuffer[UART_SERVO_txBufferRead];

            /* Set next pointer. */
            UART_SERVO_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START UART_SERVO_TXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End UART_SERVO_TX_ENABLED && (UART_SERVO_TXBUFFERSIZE > UART_SERVO_FIFO_LENGTH) */


/* [] END OF FILE */
