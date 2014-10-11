/*******************************************************************************
* File Name: UART_TEST.h
* Version 2.30
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_UART_TEST_H)
#define CY_UART_UART_TEST_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define UART_TEST_RX_ENABLED                     (0u)
#define UART_TEST_TX_ENABLED                     (1u)
#define UART_TEST_HD_ENABLED                     (0u)
#define UART_TEST_RX_INTERRUPT_ENABLED           (1u)
#define UART_TEST_TX_INTERRUPT_ENABLED           (1u)
#define UART_TEST_INTERNAL_CLOCK_USED            (1u)
#define UART_TEST_RXHW_ADDRESS_ENABLED           (0u)
#define UART_TEST_OVER_SAMPLE_COUNT              (8u)
#define UART_TEST_PARITY_TYPE                    (0u)
#define UART_TEST_PARITY_TYPE_SW                 (0u)
#define UART_TEST_BREAK_DETECT                   (0u)
#define UART_TEST_BREAK_BITS_TX                  (13u)
#define UART_TEST_BREAK_BITS_RX                  (13u)
#define UART_TEST_TXCLKGEN_DP                    (1u)
#define UART_TEST_USE23POLLING                   (1u)
#define UART_TEST_FLOW_CONTROL                   (0u)
#define UART_TEST_CLK_FREQ                       (0u)
#define UART_TEST_TXBUFFERSIZE                   (32u)
#define UART_TEST_RXBUFFERSIZE                   (32u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_30 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#ifdef UART_TEST_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define UART_TEST_CONTROL_REG_REMOVED            (0u)
#else
    #define UART_TEST_CONTROL_REG_REMOVED            (1u)
#endif /* End UART_TEST_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct UART_TEST_backupStruct_
{
    uint8 enableState;

    #if(UART_TEST_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End UART_TEST_CONTROL_REG_REMOVED */
    #if( (UART_TEST_RX_ENABLED) || (UART_TEST_HD_ENABLED) )
        uint8 rx_period;
        #if (CY_UDB_V0)
            uint8 rx_mask;
            #if (UART_TEST_RXHW_ADDRESS_ENABLED)
                uint8 rx_addr1;
                uint8 rx_addr2;
            #endif /* End UART_TEST_RXHW_ADDRESS_ENABLED */
        #endif /* End CY_UDB_V0 */
    #endif  /* End (UART_TEST_RX_ENABLED) || (UART_TEST_HD_ENABLED)*/

    #if(UART_TEST_TX_ENABLED)
        #if(UART_TEST_TXCLKGEN_DP)
            uint8 tx_clk_ctr;
            #if (CY_UDB_V0)
                uint8 tx_clk_compl;
            #endif  /* End CY_UDB_V0 */
        #else
            uint8 tx_period;
        #endif /*End UART_TEST_TXCLKGEN_DP */
        #if (CY_UDB_V0)
            uint8 tx_mask;
        #endif  /* End CY_UDB_V0 */
    #endif /*End UART_TEST_TX_ENABLED */
} UART_TEST_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void UART_TEST_Start(void) ;
void UART_TEST_Stop(void) ;
uint8 UART_TEST_ReadControlRegister(void) ;
void UART_TEST_WriteControlRegister(uint8 control) ;

void UART_TEST_Init(void) ;
void UART_TEST_Enable(void) ;
void UART_TEST_SaveConfig(void) ;
void UART_TEST_RestoreConfig(void) ;
void UART_TEST_Sleep(void) ;
void UART_TEST_Wakeup(void) ;

/* Only if RX is enabled */
#if( (UART_TEST_RX_ENABLED) || (UART_TEST_HD_ENABLED) )

    #if(UART_TEST_RX_INTERRUPT_ENABLED)
        void  UART_TEST_EnableRxInt(void) ;
        void  UART_TEST_DisableRxInt(void) ;
        CY_ISR_PROTO(UART_TEST_RXISR);
    #endif /* UART_TEST_RX_INTERRUPT_ENABLED */

    void UART_TEST_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void UART_TEST_SetRxAddress1(uint8 address) ;
    void UART_TEST_SetRxAddress2(uint8 address) ;

    void  UART_TEST_SetRxInterruptMode(uint8 intSrc) ;
    uint8 UART_TEST_ReadRxData(void) ;
    uint8 UART_TEST_ReadRxStatus(void) ;
    uint8 UART_TEST_GetChar(void) ;
    uint16 UART_TEST_GetByte(void) ;
    uint8 UART_TEST_GetRxBufferSize(void)
                                                            ;
    void UART_TEST_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define UART_TEST_GetRxInterruptSource   UART_TEST_ReadRxStatus

#endif /* End (UART_TEST_RX_ENABLED) || (UART_TEST_HD_ENABLED) */

/* Only if TX is enabled */
#if(UART_TEST_TX_ENABLED || UART_TEST_HD_ENABLED)

    #if(UART_TEST_TX_INTERRUPT_ENABLED)
        void UART_TEST_EnableTxInt(void) ;
        void UART_TEST_DisableTxInt(void) ;
        CY_ISR_PROTO(UART_TEST_TXISR);
    #endif /* UART_TEST_TX_INTERRUPT_ENABLED */

    void UART_TEST_SetTxInterruptMode(uint8 intSrc) ;
    void UART_TEST_WriteTxData(uint8 txDataByte) ;
    uint8 UART_TEST_ReadTxStatus(void) ;
    void UART_TEST_PutChar(uint8 txDataByte) ;
    void UART_TEST_PutString(const char8 string[]) ;
    void UART_TEST_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void UART_TEST_PutCRLF(uint8 txDataByte) ;
    void UART_TEST_ClearTxBuffer(void) ;
    void UART_TEST_SetTxAddressMode(uint8 addressMode) ;
    void UART_TEST_SendBreak(uint8 retMode) ;
    uint8 UART_TEST_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define UART_TEST_PutStringConst         UART_TEST_PutString
    #define UART_TEST_PutArrayConst          UART_TEST_PutArray
    #define UART_TEST_GetTxInterruptSource   UART_TEST_ReadTxStatus

#endif /* End UART_TEST_TX_ENABLED || UART_TEST_HD_ENABLED */

#if(UART_TEST_HD_ENABLED)
    void UART_TEST_LoadRxConfig(void) ;
    void UART_TEST_LoadTxConfig(void) ;
#endif /* End UART_TEST_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_TEST) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    UART_TEST_CyBtldrCommStart(void) CYSMALL ;
    void    UART_TEST_CyBtldrCommStop(void) CYSMALL ;
    void    UART_TEST_CyBtldrCommReset(void) CYSMALL ;
    cystatus UART_TEST_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus UART_TEST_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_TEST)
        #define CyBtldrCommStart    UART_TEST_CyBtldrCommStart
        #define CyBtldrCommStop     UART_TEST_CyBtldrCommStop
        #define CyBtldrCommReset    UART_TEST_CyBtldrCommReset
        #define CyBtldrCommWrite    UART_TEST_CyBtldrCommWrite
        #define CyBtldrCommRead     UART_TEST_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_TEST) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define UART_TEST_BYTE2BYTE_TIME_OUT (25u)

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define UART_TEST_SET_SPACE                              (0x00u)
#define UART_TEST_SET_MARK                               (0x01u)

/* Status Register definitions */
#if( (UART_TEST_TX_ENABLED) || (UART_TEST_HD_ENABLED) )
    #if(UART_TEST_TX_INTERRUPT_ENABLED)
        #define UART_TEST_TX_VECT_NUM            (uint8)UART_TEST_TXInternalInterrupt__INTC_NUMBER
        #define UART_TEST_TX_PRIOR_NUM           (uint8)UART_TEST_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UART_TEST_TX_INTERRUPT_ENABLED */
    #if(UART_TEST_TX_ENABLED)
        #define UART_TEST_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define UART_TEST_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define UART_TEST_TX_STS_FIFO_FULL_SHIFT         (0x02u)
        #define UART_TEST_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* UART_TEST_TX_ENABLED */
    #if(UART_TEST_HD_ENABLED)
        #define UART_TEST_TX_STS_COMPLETE_SHIFT          (0x00u)
        #define UART_TEST_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
        #define UART_TEST_TX_STS_FIFO_FULL_SHIFT         (0x05u)  /*needs MD=0*/
        #define UART_TEST_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #endif /* UART_TEST_HD_ENABLED */
    #define UART_TEST_TX_STS_COMPLETE            (uint8)(0x01u << UART_TEST_TX_STS_COMPLETE_SHIFT)
    #define UART_TEST_TX_STS_FIFO_EMPTY          (uint8)(0x01u << UART_TEST_TX_STS_FIFO_EMPTY_SHIFT)
    #define UART_TEST_TX_STS_FIFO_FULL           (uint8)(0x01u << UART_TEST_TX_STS_FIFO_FULL_SHIFT)
    #define UART_TEST_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << UART_TEST_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (UART_TEST_TX_ENABLED) || (UART_TEST_HD_ENABLED)*/

#if( (UART_TEST_RX_ENABLED) || (UART_TEST_HD_ENABLED) )
    #if(UART_TEST_RX_INTERRUPT_ENABLED)
        #define UART_TEST_RX_VECT_NUM            (uint8)UART_TEST_RXInternalInterrupt__INTC_NUMBER
        #define UART_TEST_RX_PRIOR_NUM           (uint8)UART_TEST_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UART_TEST_RX_INTERRUPT_ENABLED */
    #define UART_TEST_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define UART_TEST_RX_STS_BREAK_SHIFT             (0x01u)
    #define UART_TEST_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define UART_TEST_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define UART_TEST_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define UART_TEST_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define UART_TEST_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define UART_TEST_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define UART_TEST_RX_STS_MRKSPC           (uint8)(0x01u << UART_TEST_RX_STS_MRKSPC_SHIFT)
    #define UART_TEST_RX_STS_BREAK            (uint8)(0x01u << UART_TEST_RX_STS_BREAK_SHIFT)
    #define UART_TEST_RX_STS_PAR_ERROR        (uint8)(0x01u << UART_TEST_RX_STS_PAR_ERROR_SHIFT)
    #define UART_TEST_RX_STS_STOP_ERROR       (uint8)(0x01u << UART_TEST_RX_STS_STOP_ERROR_SHIFT)
    #define UART_TEST_RX_STS_OVERRUN          (uint8)(0x01u << UART_TEST_RX_STS_OVERRUN_SHIFT)
    #define UART_TEST_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << UART_TEST_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define UART_TEST_RX_STS_ADDR_MATCH       (uint8)(0x01u << UART_TEST_RX_STS_ADDR_MATCH_SHIFT)
    #define UART_TEST_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << UART_TEST_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define UART_TEST_RX_HW_MASK                     (0x7Fu)
#endif /* End (UART_TEST_RX_ENABLED) || (UART_TEST_HD_ENABLED) */

/* Control Register definitions */
#define UART_TEST_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define UART_TEST_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define UART_TEST_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define UART_TEST_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define UART_TEST_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define UART_TEST_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define UART_TEST_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define UART_TEST_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define UART_TEST_CTRL_HD_SEND               (uint8)(0x01u << UART_TEST_CTRL_HD_SEND_SHIFT)
#define UART_TEST_CTRL_HD_SEND_BREAK         (uint8)(0x01u << UART_TEST_CTRL_HD_SEND_BREAK_SHIFT)
#define UART_TEST_CTRL_MARK                  (uint8)(0x01u << UART_TEST_CTRL_MARK_SHIFT)
#define UART_TEST_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << UART_TEST_CTRL_PARITY_TYPE0_SHIFT)
#define UART_TEST_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << UART_TEST_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define UART_TEST_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define UART_TEST_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define UART_TEST_SEND_BREAK                         (0x00u)
#define UART_TEST_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define UART_TEST_REINIT                             (0x02u)
#define UART_TEST_SEND_WAIT_REINIT                   (0x03u)

#define UART_TEST_OVER_SAMPLE_8                      (8u)
#define UART_TEST_OVER_SAMPLE_16                     (16u)

#define UART_TEST_BIT_CENTER                         (UART_TEST_OVER_SAMPLE_COUNT - 1u)

#define UART_TEST_FIFO_LENGTH                        (4u)
#define UART_TEST_NUMBER_OF_START_BIT                (1u)
#define UART_TEST_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation*/
#define UART_TEST_TXBITCTR_BREAKBITS8X   ((UART_TEST_BREAK_BITS_TX * UART_TEST_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation*/
#define UART_TEST_TXBITCTR_BREAKBITS ((UART_TEST_BREAK_BITS_TX * UART_TEST_OVER_SAMPLE_COUNT) - 1u)

#define UART_TEST_HALF_BIT_COUNT   \
                            (((UART_TEST_OVER_SAMPLE_COUNT / 2u) + (UART_TEST_USE23POLLING * 1u)) - 2u)
#if (UART_TEST_OVER_SAMPLE_COUNT == UART_TEST_OVER_SAMPLE_8)
    #define UART_TEST_HD_TXBITCTR_INIT   (((UART_TEST_BREAK_BITS_TX + \
                            UART_TEST_NUMBER_OF_START_BIT) * UART_TEST_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define UART_TEST_RXBITCTR_INIT  ((((UART_TEST_BREAK_BITS_RX + UART_TEST_NUMBER_OF_START_BIT) \
                            * UART_TEST_OVER_SAMPLE_COUNT) + UART_TEST_HALF_BIT_COUNT) - 1u)


#else /* UART_TEST_OVER_SAMPLE_COUNT == UART_TEST_OVER_SAMPLE_16 */
    #define UART_TEST_HD_TXBITCTR_INIT   ((8u * UART_TEST_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount=16 */
    #define UART_TEST_RXBITCTR_INIT      (((7u * UART_TEST_OVER_SAMPLE_COUNT) - 1u) + \
                                                      UART_TEST_HALF_BIT_COUNT)
#endif /* End UART_TEST_OVER_SAMPLE_COUNT */
#define UART_TEST_HD_RXBITCTR_INIT                   UART_TEST_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 UART_TEST_initVar;
#if( UART_TEST_TX_ENABLED && (UART_TEST_TXBUFFERSIZE > UART_TEST_FIFO_LENGTH))
    extern volatile uint8 UART_TEST_txBuffer[UART_TEST_TXBUFFERSIZE];
    extern volatile uint8 UART_TEST_txBufferRead;
    extern uint8 UART_TEST_txBufferWrite;
#endif /* End UART_TEST_TX_ENABLED */
#if( ( UART_TEST_RX_ENABLED || UART_TEST_HD_ENABLED ) && \
     (UART_TEST_RXBUFFERSIZE > UART_TEST_FIFO_LENGTH) )
    extern volatile uint8 UART_TEST_rxBuffer[UART_TEST_RXBUFFERSIZE];
    extern volatile uint8 UART_TEST_rxBufferRead;
    extern volatile uint8 UART_TEST_rxBufferWrite;
    extern volatile uint8 UART_TEST_rxBufferLoopDetect;
    extern volatile uint8 UART_TEST_rxBufferOverflow;
    #if (UART_TEST_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 UART_TEST_rxAddressMode;
        extern volatile uint8 UART_TEST_rxAddressDetected;
    #endif /* End EnableHWAddress */
#endif /* End UART_TEST_RX_ENABLED */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define UART_TEST__B_UART__AM_SW_BYTE_BYTE 1
#define UART_TEST__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define UART_TEST__B_UART__AM_HW_BYTE_BY_BYTE 3
#define UART_TEST__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define UART_TEST__B_UART__AM_NONE 0

#define UART_TEST__B_UART__NONE_REVB 0
#define UART_TEST__B_UART__EVEN_REVB 1
#define UART_TEST__B_UART__ODD_REVB 2
#define UART_TEST__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define UART_TEST_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define UART_TEST_NUMBER_OF_STOP_BITS    (1u)

#if (UART_TEST_RXHW_ADDRESS_ENABLED)
    #define UART_TEST_RXADDRESSMODE      (0u)
    #define UART_TEST_RXHWADDRESS1       (0u)
    #define UART_TEST_RXHWADDRESS2       (0u)
    /* Backward compatible define */
    #define UART_TEST_RXAddressMode      UART_TEST_RXADDRESSMODE
#endif /* End EnableHWAddress */

#define UART_TEST_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((0 << UART_TEST_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << UART_TEST_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << UART_TEST_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << UART_TEST_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << UART_TEST_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << UART_TEST_RX_STS_BREAK_SHIFT) \
                                        | (0 << UART_TEST_RX_STS_OVERRUN_SHIFT))

#define UART_TEST_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((1 << UART_TEST_TX_STS_COMPLETE_SHIFT) \
                                        | (1 << UART_TEST_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << UART_TEST_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << UART_TEST_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef UART_TEST_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define UART_TEST_CONTROL_REG \
                            (* (reg8 *) UART_TEST_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define UART_TEST_CONTROL_PTR \
                            (  (reg8 *) UART_TEST_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End UART_TEST_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(UART_TEST_TX_ENABLED)
    #define UART_TEST_TXDATA_REG          (* (reg8 *) UART_TEST_BUART_sTX_TxShifter_u0__F0_REG)
    #define UART_TEST_TXDATA_PTR          (  (reg8 *) UART_TEST_BUART_sTX_TxShifter_u0__F0_REG)
    #define UART_TEST_TXDATA_AUX_CTL_REG  (* (reg8 *) UART_TEST_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UART_TEST_TXDATA_AUX_CTL_PTR  (  (reg8 *) UART_TEST_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UART_TEST_TXSTATUS_REG        (* (reg8 *) UART_TEST_BUART_sTX_TxSts__STATUS_REG)
    #define UART_TEST_TXSTATUS_PTR        (  (reg8 *) UART_TEST_BUART_sTX_TxSts__STATUS_REG)
    #define UART_TEST_TXSTATUS_MASK_REG   (* (reg8 *) UART_TEST_BUART_sTX_TxSts__MASK_REG)
    #define UART_TEST_TXSTATUS_MASK_PTR   (  (reg8 *) UART_TEST_BUART_sTX_TxSts__MASK_REG)
    #define UART_TEST_TXSTATUS_ACTL_REG   (* (reg8 *) UART_TEST_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define UART_TEST_TXSTATUS_ACTL_PTR   (  (reg8 *) UART_TEST_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(UART_TEST_TXCLKGEN_DP)
        #define UART_TEST_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) UART_TEST_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UART_TEST_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) UART_TEST_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UART_TEST_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) UART_TEST_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define UART_TEST_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) UART_TEST_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define UART_TEST_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) UART_TEST_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UART_TEST_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) UART_TEST_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UART_TEST_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UART_TEST_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UART_TEST_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UART_TEST_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UART_TEST_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) UART_TEST_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define UART_TEST_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) UART_TEST_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* UART_TEST_TXCLKGEN_DP */

#endif /* End UART_TEST_TX_ENABLED */

#if(UART_TEST_HD_ENABLED)

    #define UART_TEST_TXDATA_REG             (* (reg8 *) UART_TEST_BUART_sRX_RxShifter_u0__F1_REG )
    #define UART_TEST_TXDATA_PTR             (  (reg8 *) UART_TEST_BUART_sRX_RxShifter_u0__F1_REG )
    #define UART_TEST_TXDATA_AUX_CTL_REG     (* (reg8 *) UART_TEST_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define UART_TEST_TXDATA_AUX_CTL_PTR     (  (reg8 *) UART_TEST_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UART_TEST_TXSTATUS_REG           (* (reg8 *) UART_TEST_BUART_sRX_RxSts__STATUS_REG )
    #define UART_TEST_TXSTATUS_PTR           (  (reg8 *) UART_TEST_BUART_sRX_RxSts__STATUS_REG )
    #define UART_TEST_TXSTATUS_MASK_REG      (* (reg8 *) UART_TEST_BUART_sRX_RxSts__MASK_REG )
    #define UART_TEST_TXSTATUS_MASK_PTR      (  (reg8 *) UART_TEST_BUART_sRX_RxSts__MASK_REG )
    #define UART_TEST_TXSTATUS_ACTL_REG      (* (reg8 *) UART_TEST_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UART_TEST_TXSTATUS_ACTL_PTR      (  (reg8 *) UART_TEST_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End UART_TEST_HD_ENABLED */

#if( (UART_TEST_RX_ENABLED) || (UART_TEST_HD_ENABLED) )
    #define UART_TEST_RXDATA_REG             (* (reg8 *) UART_TEST_BUART_sRX_RxShifter_u0__F0_REG )
    #define UART_TEST_RXDATA_PTR             (  (reg8 *) UART_TEST_BUART_sRX_RxShifter_u0__F0_REG )
    #define UART_TEST_RXADDRESS1_REG         (* (reg8 *) UART_TEST_BUART_sRX_RxShifter_u0__D0_REG )
    #define UART_TEST_RXADDRESS1_PTR         (  (reg8 *) UART_TEST_BUART_sRX_RxShifter_u0__D0_REG )
    #define UART_TEST_RXADDRESS2_REG         (* (reg8 *) UART_TEST_BUART_sRX_RxShifter_u0__D1_REG )
    #define UART_TEST_RXADDRESS2_PTR         (  (reg8 *) UART_TEST_BUART_sRX_RxShifter_u0__D1_REG )
    #define UART_TEST_RXDATA_AUX_CTL_REG     (* (reg8 *) UART_TEST_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UART_TEST_RXBITCTR_PERIOD_REG    (* (reg8 *) UART_TEST_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UART_TEST_RXBITCTR_PERIOD_PTR    (  (reg8 *) UART_TEST_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UART_TEST_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UART_TEST_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UART_TEST_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UART_TEST_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UART_TEST_RXBITCTR_COUNTER_REG   (* (reg8 *) UART_TEST_BUART_sRX_RxBitCounter__COUNT_REG )
    #define UART_TEST_RXBITCTR_COUNTER_PTR   (  (reg8 *) UART_TEST_BUART_sRX_RxBitCounter__COUNT_REG )

    #define UART_TEST_RXSTATUS_REG           (* (reg8 *) UART_TEST_BUART_sRX_RxSts__STATUS_REG )
    #define UART_TEST_RXSTATUS_PTR           (  (reg8 *) UART_TEST_BUART_sRX_RxSts__STATUS_REG )
    #define UART_TEST_RXSTATUS_MASK_REG      (* (reg8 *) UART_TEST_BUART_sRX_RxSts__MASK_REG )
    #define UART_TEST_RXSTATUS_MASK_PTR      (  (reg8 *) UART_TEST_BUART_sRX_RxSts__MASK_REG )
    #define UART_TEST_RXSTATUS_ACTL_REG      (* (reg8 *) UART_TEST_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UART_TEST_RXSTATUS_ACTL_PTR      (  (reg8 *) UART_TEST_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (UART_TEST_RX_ENABLED) || (UART_TEST_HD_ENABLED) */

#if(UART_TEST_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define UART_TEST_INTCLOCK_CLKEN_REG     (* (reg8 *) UART_TEST_IntClock__PM_ACT_CFG)
    #define UART_TEST_INTCLOCK_CLKEN_PTR     (  (reg8 *) UART_TEST_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define UART_TEST_INTCLOCK_CLKEN_MASK    UART_TEST_IntClock__PM_ACT_MSK
#endif /* End UART_TEST_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(UART_TEST_TX_ENABLED)
    #define UART_TEST_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End UART_TEST_TX_ENABLED */

#if(UART_TEST_HD_ENABLED)
    #define UART_TEST_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End UART_TEST_HD_ENABLED */

#if( (UART_TEST_RX_ENABLED) || (UART_TEST_HD_ENABLED) )
    #define UART_TEST_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (UART_TEST_RX_ENABLED) || (UART_TEST_HD_ENABLED) */


/***************************************
* Renamed global variables or defines
* for backward compatible
***************************************/

#define UART_TEST_initvar                    UART_TEST_initVar

#define UART_TEST_RX_Enabled                 UART_TEST_RX_ENABLED
#define UART_TEST_TX_Enabled                 UART_TEST_TX_ENABLED
#define UART_TEST_HD_Enabled                 UART_TEST_HD_ENABLED
#define UART_TEST_RX_IntInterruptEnabled     UART_TEST_RX_INTERRUPT_ENABLED
#define UART_TEST_TX_IntInterruptEnabled     UART_TEST_TX_INTERRUPT_ENABLED
#define UART_TEST_InternalClockUsed          UART_TEST_INTERNAL_CLOCK_USED
#define UART_TEST_RXHW_Address_Enabled       UART_TEST_RXHW_ADDRESS_ENABLED
#define UART_TEST_OverSampleCount            UART_TEST_OVER_SAMPLE_COUNT
#define UART_TEST_ParityType                 UART_TEST_PARITY_TYPE

#if( UART_TEST_TX_ENABLED && (UART_TEST_TXBUFFERSIZE > UART_TEST_FIFO_LENGTH))
    #define UART_TEST_TXBUFFER               UART_TEST_txBuffer
    #define UART_TEST_TXBUFFERREAD           UART_TEST_txBufferRead
    #define UART_TEST_TXBUFFERWRITE          UART_TEST_txBufferWrite
#endif /* End UART_TEST_TX_ENABLED */
#if( ( UART_TEST_RX_ENABLED || UART_TEST_HD_ENABLED ) && \
     (UART_TEST_RXBUFFERSIZE > UART_TEST_FIFO_LENGTH) )
    #define UART_TEST_RXBUFFER               UART_TEST_rxBuffer
    #define UART_TEST_RXBUFFERREAD           UART_TEST_rxBufferRead
    #define UART_TEST_RXBUFFERWRITE          UART_TEST_rxBufferWrite
    #define UART_TEST_RXBUFFERLOOPDETECT     UART_TEST_rxBufferLoopDetect
    #define UART_TEST_RXBUFFER_OVERFLOW      UART_TEST_rxBufferOverflow
#endif /* End UART_TEST_RX_ENABLED */

#ifdef UART_TEST_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define UART_TEST_CONTROL                UART_TEST_CONTROL_REG
#endif /* End UART_TEST_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(UART_TEST_TX_ENABLED)
    #define UART_TEST_TXDATA                 UART_TEST_TXDATA_REG
    #define UART_TEST_TXSTATUS               UART_TEST_TXSTATUS_REG
    #define UART_TEST_TXSTATUS_MASK          UART_TEST_TXSTATUS_MASK_REG
    #define UART_TEST_TXSTATUS_ACTL          UART_TEST_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(UART_TEST_TXCLKGEN_DP)
        #define UART_TEST_TXBITCLKGEN_CTR        UART_TEST_TXBITCLKGEN_CTR_REG
        #define UART_TEST_TXBITCLKTX_COMPLETE    UART_TEST_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define UART_TEST_TXBITCTR_PERIOD        UART_TEST_TXBITCTR_PERIOD_REG
        #define UART_TEST_TXBITCTR_CONTROL       UART_TEST_TXBITCTR_CONTROL_REG
        #define UART_TEST_TXBITCTR_COUNTER       UART_TEST_TXBITCTR_COUNTER_REG
    #endif /* UART_TEST_TXCLKGEN_DP */
#endif /* End UART_TEST_TX_ENABLED */

#if(UART_TEST_HD_ENABLED)
    #define UART_TEST_TXDATA                 UART_TEST_TXDATA_REG
    #define UART_TEST_TXSTATUS               UART_TEST_TXSTATUS_REG
    #define UART_TEST_TXSTATUS_MASK          UART_TEST_TXSTATUS_MASK_REG
    #define UART_TEST_TXSTATUS_ACTL          UART_TEST_TXSTATUS_ACTL_REG
#endif /* End UART_TEST_HD_ENABLED */

#if( (UART_TEST_RX_ENABLED) || (UART_TEST_HD_ENABLED) )
    #define UART_TEST_RXDATA                 UART_TEST_RXDATA_REG
    #define UART_TEST_RXADDRESS1             UART_TEST_RXADDRESS1_REG
    #define UART_TEST_RXADDRESS2             UART_TEST_RXADDRESS2_REG
    #define UART_TEST_RXBITCTR_PERIOD        UART_TEST_RXBITCTR_PERIOD_REG
    #define UART_TEST_RXBITCTR_CONTROL       UART_TEST_RXBITCTR_CONTROL_REG
    #define UART_TEST_RXBITCTR_COUNTER       UART_TEST_RXBITCTR_COUNTER_REG
    #define UART_TEST_RXSTATUS               UART_TEST_RXSTATUS_REG
    #define UART_TEST_RXSTATUS_MASK          UART_TEST_RXSTATUS_MASK_REG
    #define UART_TEST_RXSTATUS_ACTL          UART_TEST_RXSTATUS_ACTL_REG
#endif /* End  (UART_TEST_RX_ENABLED) || (UART_TEST_HD_ENABLED) */

#if(UART_TEST_INTERNAL_CLOCK_USED)
    #define UART_TEST_INTCLOCK_CLKEN         UART_TEST_INTCLOCK_CLKEN_REG
#endif /* End UART_TEST_INTERNAL_CLOCK_USED */

#define UART_TEST_WAIT_FOR_COMLETE_REINIT    UART_TEST_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_UART_TEST_H */


/* [] END OF FILE */
