#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include <cydevice.h>
#include <cydevice_trm.h>

/* UART_TEST_RXInternalInterrupt */
#define UART_TEST_RXInternalInterrupt__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define UART_TEST_RXInternalInterrupt__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define UART_TEST_RXInternalInterrupt__INTC_MASK 0x20u
#define UART_TEST_RXInternalInterrupt__INTC_NUMBER 5u
#define UART_TEST_RXInternalInterrupt__INTC_PRIOR_NUM 7u
#define UART_TEST_RXInternalInterrupt__INTC_PRIOR_REG CYREG_NVIC_PRI_5
#define UART_TEST_RXInternalInterrupt__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define UART_TEST_RXInternalInterrupt__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* UART_RXInternalInterrupt */
#define UART_RXInternalInterrupt__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define UART_RXInternalInterrupt__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define UART_RXInternalInterrupt__INTC_MASK 0x08u
#define UART_RXInternalInterrupt__INTC_NUMBER 3u
#define UART_RXInternalInterrupt__INTC_PRIOR_NUM 7u
#define UART_RXInternalInterrupt__INTC_PRIOR_REG CYREG_NVIC_PRI_3
#define UART_RXInternalInterrupt__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define UART_RXInternalInterrupt__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* UART_TXInternalInterrupt */
#define UART_TXInternalInterrupt__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define UART_TXInternalInterrupt__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define UART_TXInternalInterrupt__INTC_MASK 0x10u
#define UART_TXInternalInterrupt__INTC_NUMBER 4u
#define UART_TXInternalInterrupt__INTC_PRIOR_NUM 7u
#define UART_TXInternalInterrupt__INTC_PRIOR_REG CYREG_NVIC_PRI_4
#define UART_TXInternalInterrupt__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define UART_TXInternalInterrupt__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* UART_TEST_IntClock */
#define UART_TEST_IntClock__CFG0 CYREG_CLKDIST_DCFG1_CFG0
#define UART_TEST_IntClock__CFG1 CYREG_CLKDIST_DCFG1_CFG1
#define UART_TEST_IntClock__CFG2 CYREG_CLKDIST_DCFG1_CFG2
#define UART_TEST_IntClock__CFG2_SRC_SEL_MASK 0x07u
#define UART_TEST_IntClock__INDEX 0x01u
#define UART_TEST_IntClock__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define UART_TEST_IntClock__PM_ACT_MSK 0x02u
#define UART_TEST_IntClock__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define UART_TEST_IntClock__PM_STBY_MSK 0x02u

/* UART_TEST_BUART */
#define UART_TEST_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_AUX_CTL_REG CYREG_B1_UDB10_11_ACTL
#define UART_TEST_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_REG CYREG_B1_UDB10_11_ST
#define UART_TEST_BUART_sRX_RxBitCounter_ST__MASK_REG CYREG_B1_UDB10_MSK
#define UART_TEST_BUART_sRX_RxBitCounter_ST__MASK_ST_AUX_CTL_REG CYREG_B1_UDB10_MSK_ACTL
#define UART_TEST_BUART_sRX_RxBitCounter_ST__PER_ST_AUX_CTL_REG CYREG_B1_UDB10_MSK_ACTL
#define UART_TEST_BUART_sRX_RxBitCounter_ST__STATUS_AUX_CTL_REG CYREG_B1_UDB10_ACTL
#define UART_TEST_BUART_sRX_RxBitCounter_ST__STATUS_CNT_REG CYREG_B1_UDB10_ST_CTL
#define UART_TEST_BUART_sRX_RxBitCounter_ST__STATUS_CONTROL_REG CYREG_B1_UDB10_ST_CTL
#define UART_TEST_BUART_sRX_RxBitCounter_ST__STATUS_REG CYREG_B1_UDB10_ST
#define UART_TEST_BUART_sRX_RxBitCounter__16BIT_CONTROL_AUX_CTL_REG CYREG_B1_UDB10_11_ACTL
#define UART_TEST_BUART_sRX_RxBitCounter__16BIT_CONTROL_CONTROL_REG CYREG_B1_UDB10_11_CTL
#define UART_TEST_BUART_sRX_RxBitCounter__16BIT_CONTROL_COUNT_REG CYREG_B1_UDB10_11_CTL
#define UART_TEST_BUART_sRX_RxBitCounter__16BIT_COUNT_CONTROL_REG CYREG_B1_UDB10_11_CTL
#define UART_TEST_BUART_sRX_RxBitCounter__16BIT_COUNT_COUNT_REG CYREG_B1_UDB10_11_CTL
#define UART_TEST_BUART_sRX_RxBitCounter__16BIT_MASK_MASK_REG CYREG_B1_UDB10_11_MSK
#define UART_TEST_BUART_sRX_RxBitCounter__16BIT_MASK_PERIOD_REG CYREG_B1_UDB10_11_MSK
#define UART_TEST_BUART_sRX_RxBitCounter__16BIT_PERIOD_MASK_REG CYREG_B1_UDB10_11_MSK
#define UART_TEST_BUART_sRX_RxBitCounter__16BIT_PERIOD_PERIOD_REG CYREG_B1_UDB10_11_MSK
#define UART_TEST_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG CYREG_B1_UDB10_ACTL
#define UART_TEST_BUART_sRX_RxBitCounter__CONTROL_REG CYREG_B1_UDB10_CTL
#define UART_TEST_BUART_sRX_RxBitCounter__CONTROL_ST_REG CYREG_B1_UDB10_ST_CTL
#define UART_TEST_BUART_sRX_RxBitCounter__COUNT_REG CYREG_B1_UDB10_CTL
#define UART_TEST_BUART_sRX_RxBitCounter__COUNT_ST_REG CYREG_B1_UDB10_ST_CTL
#define UART_TEST_BUART_sRX_RxBitCounter__MASK_CTL_AUX_CTL_REG CYREG_B1_UDB10_MSK_ACTL
#define UART_TEST_BUART_sRX_RxBitCounter__PERIOD_REG CYREG_B1_UDB10_MSK
#define UART_TEST_BUART_sRX_RxBitCounter__PER_CTL_AUX_CTL_REG CYREG_B1_UDB10_MSK_ACTL
#define UART_TEST_BUART_sRX_RxShifter_u0__16BIT_A0_REG CYREG_B1_UDB09_10_A0
#define UART_TEST_BUART_sRX_RxShifter_u0__16BIT_A1_REG CYREG_B1_UDB09_10_A1
#define UART_TEST_BUART_sRX_RxShifter_u0__16BIT_D0_REG CYREG_B1_UDB09_10_D0
#define UART_TEST_BUART_sRX_RxShifter_u0__16BIT_D1_REG CYREG_B1_UDB09_10_D1
#define UART_TEST_BUART_sRX_RxShifter_u0__16BIT_DP_AUX_CTL_REG CYREG_B1_UDB09_10_ACTL
#define UART_TEST_BUART_sRX_RxShifter_u0__16BIT_F0_REG CYREG_B1_UDB09_10_F0
#define UART_TEST_BUART_sRX_RxShifter_u0__16BIT_F1_REG CYREG_B1_UDB09_10_F1
#define UART_TEST_BUART_sRX_RxShifter_u0__A0_A1_REG CYREG_B1_UDB09_A0_A1
#define UART_TEST_BUART_sRX_RxShifter_u0__A0_REG CYREG_B1_UDB09_A0
#define UART_TEST_BUART_sRX_RxShifter_u0__A1_REG CYREG_B1_UDB09_A1
#define UART_TEST_BUART_sRX_RxShifter_u0__D0_D1_REG CYREG_B1_UDB09_D0_D1
#define UART_TEST_BUART_sRX_RxShifter_u0__D0_REG CYREG_B1_UDB09_D0
#define UART_TEST_BUART_sRX_RxShifter_u0__D1_REG CYREG_B1_UDB09_D1
#define UART_TEST_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG CYREG_B1_UDB09_ACTL
#define UART_TEST_BUART_sRX_RxShifter_u0__F0_F1_REG CYREG_B1_UDB09_F0_F1
#define UART_TEST_BUART_sRX_RxShifter_u0__F0_REG CYREG_B1_UDB09_F0
#define UART_TEST_BUART_sRX_RxShifter_u0__F1_REG CYREG_B1_UDB09_F1
#define UART_TEST_BUART_sRX_RxSts__16BIT_STATUS_AUX_CTL_REG CYREG_B1_UDB09_10_ACTL
#define UART_TEST_BUART_sRX_RxSts__16BIT_STATUS_REG CYREG_B1_UDB09_10_ST
#define UART_TEST_BUART_sRX_RxSts__3__MASK 0x08u
#define UART_TEST_BUART_sRX_RxSts__3__POS 3
#define UART_TEST_BUART_sRX_RxSts__4__MASK 0x10u
#define UART_TEST_BUART_sRX_RxSts__4__POS 4
#define UART_TEST_BUART_sRX_RxSts__5__MASK 0x20u
#define UART_TEST_BUART_sRX_RxSts__5__POS 5
#define UART_TEST_BUART_sRX_RxSts__MASK 0x38u
#define UART_TEST_BUART_sRX_RxSts__MASK_REG CYREG_B1_UDB09_MSK
#define UART_TEST_BUART_sRX_RxSts__STATUS_AUX_CTL_REG CYREG_B1_UDB09_ACTL
#define UART_TEST_BUART_sRX_RxSts__STATUS_REG CYREG_B1_UDB09_ST
#define UART_TEST_BUART_sTX_TxShifter_u0__16BIT_A0_REG CYREG_B0_UDB11_12_A0
#define UART_TEST_BUART_sTX_TxShifter_u0__16BIT_A1_REG CYREG_B0_UDB11_12_A1
#define UART_TEST_BUART_sTX_TxShifter_u0__16BIT_D0_REG CYREG_B0_UDB11_12_D0
#define UART_TEST_BUART_sTX_TxShifter_u0__16BIT_D1_REG CYREG_B0_UDB11_12_D1
#define UART_TEST_BUART_sTX_TxShifter_u0__16BIT_DP_AUX_CTL_REG CYREG_B0_UDB11_12_ACTL
#define UART_TEST_BUART_sTX_TxShifter_u0__16BIT_F0_REG CYREG_B0_UDB11_12_F0
#define UART_TEST_BUART_sTX_TxShifter_u0__16BIT_F1_REG CYREG_B0_UDB11_12_F1
#define UART_TEST_BUART_sTX_TxShifter_u0__A0_A1_REG CYREG_B0_UDB11_A0_A1
#define UART_TEST_BUART_sTX_TxShifter_u0__A0_REG CYREG_B0_UDB11_A0
#define UART_TEST_BUART_sTX_TxShifter_u0__A1_REG CYREG_B0_UDB11_A1
#define UART_TEST_BUART_sTX_TxShifter_u0__D0_D1_REG CYREG_B0_UDB11_D0_D1
#define UART_TEST_BUART_sTX_TxShifter_u0__D0_REG CYREG_B0_UDB11_D0
#define UART_TEST_BUART_sTX_TxShifter_u0__D1_REG CYREG_B0_UDB11_D1
#define UART_TEST_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG CYREG_B0_UDB11_ACTL
#define UART_TEST_BUART_sTX_TxShifter_u0__F0_F1_REG CYREG_B0_UDB11_F0_F1
#define UART_TEST_BUART_sTX_TxShifter_u0__F0_REG CYREG_B0_UDB11_F0
#define UART_TEST_BUART_sTX_TxShifter_u0__F1_REG CYREG_B0_UDB11_F1
#define UART_TEST_BUART_sTX_TxSts__0__MASK 0x01u
#define UART_TEST_BUART_sTX_TxSts__0__POS 0
#define UART_TEST_BUART_sTX_TxSts__16BIT_STATUS_AUX_CTL_REG CYREG_B0_UDB11_12_ACTL
#define UART_TEST_BUART_sTX_TxSts__16BIT_STATUS_REG CYREG_B0_UDB11_12_ST
#define UART_TEST_BUART_sTX_TxSts__1__MASK 0x02u
#define UART_TEST_BUART_sTX_TxSts__1__POS 1
#define UART_TEST_BUART_sTX_TxSts__2__MASK 0x04u
#define UART_TEST_BUART_sTX_TxSts__2__POS 2
#define UART_TEST_BUART_sTX_TxSts__3__MASK 0x08u
#define UART_TEST_BUART_sTX_TxSts__3__POS 3
#define UART_TEST_BUART_sTX_TxSts__MASK 0x0Fu
#define UART_TEST_BUART_sTX_TxSts__MASK_REG CYREG_B0_UDB11_MSK
#define UART_TEST_BUART_sTX_TxSts__STATUS_AUX_CTL_REG CYREG_B0_UDB11_ACTL
#define UART_TEST_BUART_sTX_TxSts__STATUS_REG CYREG_B0_UDB11_ST
#define UART_TEST_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A0_REG CYREG_B0_UDB10_11_A0
#define UART_TEST_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A1_REG CYREG_B0_UDB10_11_A1
#define UART_TEST_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D0_REG CYREG_B0_UDB10_11_D0
#define UART_TEST_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D1_REG CYREG_B0_UDB10_11_D1
#define UART_TEST_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_DP_AUX_CTL_REG CYREG_B0_UDB10_11_ACTL
#define UART_TEST_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F0_REG CYREG_B0_UDB10_11_F0
#define UART_TEST_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F1_REG CYREG_B0_UDB10_11_F1
#define UART_TEST_BUART_sTX_sCLOCK_TxBitClkGen__A0_A1_REG CYREG_B0_UDB10_A0_A1
#define UART_TEST_BUART_sTX_sCLOCK_TxBitClkGen__A0_REG CYREG_B0_UDB10_A0
#define UART_TEST_BUART_sTX_sCLOCK_TxBitClkGen__A1_REG CYREG_B0_UDB10_A1
#define UART_TEST_BUART_sTX_sCLOCK_TxBitClkGen__D0_D1_REG CYREG_B0_UDB10_D0_D1
#define UART_TEST_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG CYREG_B0_UDB10_D0
#define UART_TEST_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG CYREG_B0_UDB10_D1
#define UART_TEST_BUART_sTX_sCLOCK_TxBitClkGen__DP_AUX_CTL_REG CYREG_B0_UDB10_ACTL
#define UART_TEST_BUART_sTX_sCLOCK_TxBitClkGen__F0_F1_REG CYREG_B0_UDB10_F0_F1
#define UART_TEST_BUART_sTX_sCLOCK_TxBitClkGen__F0_REG CYREG_B0_UDB10_F0
#define UART_TEST_BUART_sTX_sCLOCK_TxBitClkGen__F1_REG CYREG_B0_UDB10_F1

/* TIMER_TimerUDB */
#define TIMER_TimerUDB_nrstSts_stsreg__0__MASK 0x01u
#define TIMER_TimerUDB_nrstSts_stsreg__0__POS 0
#define TIMER_TimerUDB_nrstSts_stsreg__16BIT_STATUS_AUX_CTL_REG CYREG_B1_UDB04_05_ACTL
#define TIMER_TimerUDB_nrstSts_stsreg__16BIT_STATUS_REG CYREG_B1_UDB04_05_ST
#define TIMER_TimerUDB_nrstSts_stsreg__2__MASK 0x04u
#define TIMER_TimerUDB_nrstSts_stsreg__2__POS 2
#define TIMER_TimerUDB_nrstSts_stsreg__3__MASK 0x08u
#define TIMER_TimerUDB_nrstSts_stsreg__3__POS 3
#define TIMER_TimerUDB_nrstSts_stsreg__MASK 0x0Du
#define TIMER_TimerUDB_nrstSts_stsreg__MASK_REG CYREG_B1_UDB04_MSK
#define TIMER_TimerUDB_nrstSts_stsreg__STATUS_AUX_CTL_REG CYREG_B1_UDB04_ACTL
#define TIMER_TimerUDB_nrstSts_stsreg__STATUS_REG CYREG_B1_UDB04_ST
#define TIMER_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__16BIT_CONTROL_AUX_CTL_REG CYREG_B1_UDB05_06_ACTL
#define TIMER_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__16BIT_CONTROL_CONTROL_REG CYREG_B1_UDB05_06_CTL
#define TIMER_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__16BIT_CONTROL_COUNT_REG CYREG_B1_UDB05_06_CTL
#define TIMER_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__16BIT_COUNT_CONTROL_REG CYREG_B1_UDB05_06_CTL
#define TIMER_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__16BIT_COUNT_COUNT_REG CYREG_B1_UDB05_06_CTL
#define TIMER_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__16BIT_MASK_MASK_REG CYREG_B1_UDB05_06_MSK
#define TIMER_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__16BIT_MASK_PERIOD_REG CYREG_B1_UDB05_06_MSK
#define TIMER_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__16BIT_PERIOD_MASK_REG CYREG_B1_UDB05_06_MSK
#define TIMER_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__16BIT_PERIOD_PERIOD_REG CYREG_B1_UDB05_06_MSK
#define TIMER_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__7__MASK 0x80u
#define TIMER_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__7__POS 7
#define TIMER_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__CONTROL_AUX_CTL_REG CYREG_B1_UDB05_ACTL
#define TIMER_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__CONTROL_REG CYREG_B1_UDB05_CTL
#define TIMER_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__CONTROL_ST_REG CYREG_B1_UDB05_ST_CTL
#define TIMER_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__COUNT_REG CYREG_B1_UDB05_CTL
#define TIMER_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__COUNT_ST_REG CYREG_B1_UDB05_ST_CTL
#define TIMER_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__MASK 0x80u
#define TIMER_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__MASK_CTL_AUX_CTL_REG CYREG_B1_UDB05_MSK_ACTL
#define TIMER_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__PERIOD_REG CYREG_B1_UDB05_MSK
#define TIMER_TimerUDB_sCTRLReg_AsyncCtl_ctrlreg__PER_CTL_AUX_CTL_REG CYREG_B1_UDB05_MSK_ACTL
#define TIMER_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG CYREG_B1_UDB04_05_A0
#define TIMER_TimerUDB_sT32_timerdp_u0__16BIT_A1_REG CYREG_B1_UDB04_05_A1
#define TIMER_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG CYREG_B1_UDB04_05_D0
#define TIMER_TimerUDB_sT32_timerdp_u0__16BIT_D1_REG CYREG_B1_UDB04_05_D1
#define TIMER_TimerUDB_sT32_timerdp_u0__16BIT_DP_AUX_CTL_REG CYREG_B1_UDB04_05_ACTL
#define TIMER_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG CYREG_B1_UDB04_05_F0
#define TIMER_TimerUDB_sT32_timerdp_u0__16BIT_F1_REG CYREG_B1_UDB04_05_F1
#define TIMER_TimerUDB_sT32_timerdp_u0__A0_A1_REG CYREG_B1_UDB04_A0_A1
#define TIMER_TimerUDB_sT32_timerdp_u0__A0_REG CYREG_B1_UDB04_A0
#define TIMER_TimerUDB_sT32_timerdp_u0__A1_REG CYREG_B1_UDB04_A1
#define TIMER_TimerUDB_sT32_timerdp_u0__D0_D1_REG CYREG_B1_UDB04_D0_D1
#define TIMER_TimerUDB_sT32_timerdp_u0__D0_REG CYREG_B1_UDB04_D0
#define TIMER_TimerUDB_sT32_timerdp_u0__D1_REG CYREG_B1_UDB04_D1
#define TIMER_TimerUDB_sT32_timerdp_u0__DP_AUX_CTL_REG CYREG_B1_UDB04_ACTL
#define TIMER_TimerUDB_sT32_timerdp_u0__F0_F1_REG CYREG_B1_UDB04_F0_F1
#define TIMER_TimerUDB_sT32_timerdp_u0__F0_REG CYREG_B1_UDB04_F0
#define TIMER_TimerUDB_sT32_timerdp_u0__F1_REG CYREG_B1_UDB04_F1
#define TIMER_TimerUDB_sT32_timerdp_u1__16BIT_A0_REG CYREG_B1_UDB05_06_A0
#define TIMER_TimerUDB_sT32_timerdp_u1__16BIT_A1_REG CYREG_B1_UDB05_06_A1
#define TIMER_TimerUDB_sT32_timerdp_u1__16BIT_D0_REG CYREG_B1_UDB05_06_D0
#define TIMER_TimerUDB_sT32_timerdp_u1__16BIT_D1_REG CYREG_B1_UDB05_06_D1
#define TIMER_TimerUDB_sT32_timerdp_u1__16BIT_DP_AUX_CTL_REG CYREG_B1_UDB05_06_ACTL
#define TIMER_TimerUDB_sT32_timerdp_u1__16BIT_F0_REG CYREG_B1_UDB05_06_F0
#define TIMER_TimerUDB_sT32_timerdp_u1__16BIT_F1_REG CYREG_B1_UDB05_06_F1
#define TIMER_TimerUDB_sT32_timerdp_u1__A0_A1_REG CYREG_B1_UDB05_A0_A1
#define TIMER_TimerUDB_sT32_timerdp_u1__A0_REG CYREG_B1_UDB05_A0
#define TIMER_TimerUDB_sT32_timerdp_u1__A1_REG CYREG_B1_UDB05_A1
#define TIMER_TimerUDB_sT32_timerdp_u1__D0_D1_REG CYREG_B1_UDB05_D0_D1
#define TIMER_TimerUDB_sT32_timerdp_u1__D0_REG CYREG_B1_UDB05_D0
#define TIMER_TimerUDB_sT32_timerdp_u1__D1_REG CYREG_B1_UDB05_D1
#define TIMER_TimerUDB_sT32_timerdp_u1__DP_AUX_CTL_REG CYREG_B1_UDB05_ACTL
#define TIMER_TimerUDB_sT32_timerdp_u1__F0_F1_REG CYREG_B1_UDB05_F0_F1
#define TIMER_TimerUDB_sT32_timerdp_u1__F0_REG CYREG_B1_UDB05_F0
#define TIMER_TimerUDB_sT32_timerdp_u1__F1_REG CYREG_B1_UDB05_F1
#define TIMER_TimerUDB_sT32_timerdp_u1__MSK_DP_AUX_CTL_REG CYREG_B1_UDB05_MSK_ACTL
#define TIMER_TimerUDB_sT32_timerdp_u1__PER_DP_AUX_CTL_REG CYREG_B1_UDB05_MSK_ACTL
#define TIMER_TimerUDB_sT32_timerdp_u2__16BIT_A0_REG CYREG_B1_UDB06_07_A0
#define TIMER_TimerUDB_sT32_timerdp_u2__16BIT_A1_REG CYREG_B1_UDB06_07_A1
#define TIMER_TimerUDB_sT32_timerdp_u2__16BIT_D0_REG CYREG_B1_UDB06_07_D0
#define TIMER_TimerUDB_sT32_timerdp_u2__16BIT_D1_REG CYREG_B1_UDB06_07_D1
#define TIMER_TimerUDB_sT32_timerdp_u2__16BIT_DP_AUX_CTL_REG CYREG_B1_UDB06_07_ACTL
#define TIMER_TimerUDB_sT32_timerdp_u2__16BIT_F0_REG CYREG_B1_UDB06_07_F0
#define TIMER_TimerUDB_sT32_timerdp_u2__16BIT_F1_REG CYREG_B1_UDB06_07_F1
#define TIMER_TimerUDB_sT32_timerdp_u2__A0_A1_REG CYREG_B1_UDB06_A0_A1
#define TIMER_TimerUDB_sT32_timerdp_u2__A0_REG CYREG_B1_UDB06_A0
#define TIMER_TimerUDB_sT32_timerdp_u2__A1_REG CYREG_B1_UDB06_A1
#define TIMER_TimerUDB_sT32_timerdp_u2__D0_D1_REG CYREG_B1_UDB06_D0_D1
#define TIMER_TimerUDB_sT32_timerdp_u2__D0_REG CYREG_B1_UDB06_D0
#define TIMER_TimerUDB_sT32_timerdp_u2__D1_REG CYREG_B1_UDB06_D1
#define TIMER_TimerUDB_sT32_timerdp_u2__DP_AUX_CTL_REG CYREG_B1_UDB06_ACTL
#define TIMER_TimerUDB_sT32_timerdp_u2__F0_F1_REG CYREG_B1_UDB06_F0_F1
#define TIMER_TimerUDB_sT32_timerdp_u2__F0_REG CYREG_B1_UDB06_F0
#define TIMER_TimerUDB_sT32_timerdp_u2__F1_REG CYREG_B1_UDB06_F1
#define TIMER_TimerUDB_sT32_timerdp_u3__16BIT_A0_REG CYREG_B1_UDB07_08_A0
#define TIMER_TimerUDB_sT32_timerdp_u3__16BIT_A1_REG CYREG_B1_UDB07_08_A1
#define TIMER_TimerUDB_sT32_timerdp_u3__16BIT_D0_REG CYREG_B1_UDB07_08_D0
#define TIMER_TimerUDB_sT32_timerdp_u3__16BIT_D1_REG CYREG_B1_UDB07_08_D1
#define TIMER_TimerUDB_sT32_timerdp_u3__16BIT_DP_AUX_CTL_REG CYREG_B1_UDB07_08_ACTL
#define TIMER_TimerUDB_sT32_timerdp_u3__16BIT_F0_REG CYREG_B1_UDB07_08_F0
#define TIMER_TimerUDB_sT32_timerdp_u3__16BIT_F1_REG CYREG_B1_UDB07_08_F1
#define TIMER_TimerUDB_sT32_timerdp_u3__A0_A1_REG CYREG_B1_UDB07_A0_A1
#define TIMER_TimerUDB_sT32_timerdp_u3__A0_REG CYREG_B1_UDB07_A0
#define TIMER_TimerUDB_sT32_timerdp_u3__A1_REG CYREG_B1_UDB07_A1
#define TIMER_TimerUDB_sT32_timerdp_u3__D0_D1_REG CYREG_B1_UDB07_D0_D1
#define TIMER_TimerUDB_sT32_timerdp_u3__D0_REG CYREG_B1_UDB07_D0
#define TIMER_TimerUDB_sT32_timerdp_u3__D1_REG CYREG_B1_UDB07_D1
#define TIMER_TimerUDB_sT32_timerdp_u3__DP_AUX_CTL_REG CYREG_B1_UDB07_ACTL
#define TIMER_TimerUDB_sT32_timerdp_u3__F0_F1_REG CYREG_B1_UDB07_F0_F1
#define TIMER_TimerUDB_sT32_timerdp_u3__F0_REG CYREG_B1_UDB07_F0
#define TIMER_TimerUDB_sT32_timerdp_u3__F1_REG CYREG_B1_UDB07_F1

/* UART_IntClock */
#define UART_IntClock__CFG0 CYREG_CLKDIST_DCFG2_CFG0
#define UART_IntClock__CFG1 CYREG_CLKDIST_DCFG2_CFG1
#define UART_IntClock__CFG2 CYREG_CLKDIST_DCFG2_CFG2
#define UART_IntClock__CFG2_SRC_SEL_MASK 0x07u
#define UART_IntClock__INDEX 0x02u
#define UART_IntClock__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define UART_IntClock__PM_ACT_MSK 0x04u
#define UART_IntClock__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define UART_IntClock__PM_STBY_MSK 0x04u

/* DEBUG_LED_1 */
#define DEBUG_LED_1__0__MASK 0x01u
#define DEBUG_LED_1__0__PC CYREG_PRT2_PC0
#define DEBUG_LED_1__0__PORT 2u
#define DEBUG_LED_1__0__SHIFT 0
#define DEBUG_LED_1__AG CYREG_PRT2_AG
#define DEBUG_LED_1__AMUX CYREG_PRT2_AMUX
#define DEBUG_LED_1__BIE CYREG_PRT2_BIE
#define DEBUG_LED_1__BIT_MASK CYREG_PRT2_BIT_MASK
#define DEBUG_LED_1__BYP CYREG_PRT2_BYP
#define DEBUG_LED_1__CTL CYREG_PRT2_CTL
#define DEBUG_LED_1__DM0 CYREG_PRT2_DM0
#define DEBUG_LED_1__DM1 CYREG_PRT2_DM1
#define DEBUG_LED_1__DM2 CYREG_PRT2_DM2
#define DEBUG_LED_1__DR CYREG_PRT2_DR
#define DEBUG_LED_1__INP_DIS CYREG_PRT2_INP_DIS
#define DEBUG_LED_1__LCD_COM_SEG CYREG_PRT2_LCD_COM_SEG
#define DEBUG_LED_1__LCD_EN CYREG_PRT2_LCD_EN
#define DEBUG_LED_1__MASK 0x01u
#define DEBUG_LED_1__PORT 2u
#define DEBUG_LED_1__PRT CYREG_PRT2_PRT
#define DEBUG_LED_1__PRTDSI__CAPS_SEL CYREG_PRT2_CAPS_SEL
#define DEBUG_LED_1__PRTDSI__DBL_SYNC_IN CYREG_PRT2_DBL_SYNC_IN
#define DEBUG_LED_1__PRTDSI__OE_SEL0 CYREG_PRT2_OE_SEL0
#define DEBUG_LED_1__PRTDSI__OE_SEL1 CYREG_PRT2_OE_SEL1
#define DEBUG_LED_1__PRTDSI__OUT_SEL0 CYREG_PRT2_OUT_SEL0
#define DEBUG_LED_1__PRTDSI__OUT_SEL1 CYREG_PRT2_OUT_SEL1
#define DEBUG_LED_1__PRTDSI__SYNC_OUT CYREG_PRT2_SYNC_OUT
#define DEBUG_LED_1__PS CYREG_PRT2_PS
#define DEBUG_LED_1__SHIFT 0
#define DEBUG_LED_1__SLW CYREG_PRT2_SLW

/* TIMER_CLOCK */
#define TIMER_CLOCK__CFG0 CYREG_CLKDIST_DCFG0_CFG0
#define TIMER_CLOCK__CFG1 CYREG_CLKDIST_DCFG0_CFG1
#define TIMER_CLOCK__CFG2 CYREG_CLKDIST_DCFG0_CFG2
#define TIMER_CLOCK__CFG2_SRC_SEL_MASK 0x07u
#define TIMER_CLOCK__INDEX 0x00u
#define TIMER_CLOCK__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define TIMER_CLOCK__PM_ACT_MSK 0x01u
#define TIMER_CLOCK__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define TIMER_CLOCK__PM_STBY_MSK 0x01u

/* UART_BUART */
#define UART_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_AUX_CTL_REG CYREG_B1_UDB08_09_ACTL
#define UART_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_REG CYREG_B1_UDB08_09_ST
#define UART_BUART_sRX_RxBitCounter_ST__MASK_REG CYREG_B1_UDB08_MSK
#define UART_BUART_sRX_RxBitCounter_ST__MASK_ST_AUX_CTL_REG CYREG_B1_UDB08_MSK_ACTL
#define UART_BUART_sRX_RxBitCounter_ST__PER_ST_AUX_CTL_REG CYREG_B1_UDB08_MSK_ACTL
#define UART_BUART_sRX_RxBitCounter_ST__STATUS_AUX_CTL_REG CYREG_B1_UDB08_ACTL
#define UART_BUART_sRX_RxBitCounter_ST__STATUS_CNT_REG CYREG_B1_UDB08_ST_CTL
#define UART_BUART_sRX_RxBitCounter_ST__STATUS_CONTROL_REG CYREG_B1_UDB08_ST_CTL
#define UART_BUART_sRX_RxBitCounter_ST__STATUS_REG CYREG_B1_UDB08_ST
#define UART_BUART_sRX_RxBitCounter__16BIT_CONTROL_AUX_CTL_REG CYREG_B1_UDB08_09_ACTL
#define UART_BUART_sRX_RxBitCounter__16BIT_CONTROL_CONTROL_REG CYREG_B1_UDB08_09_CTL
#define UART_BUART_sRX_RxBitCounter__16BIT_CONTROL_COUNT_REG CYREG_B1_UDB08_09_CTL
#define UART_BUART_sRX_RxBitCounter__16BIT_COUNT_CONTROL_REG CYREG_B1_UDB08_09_CTL
#define UART_BUART_sRX_RxBitCounter__16BIT_COUNT_COUNT_REG CYREG_B1_UDB08_09_CTL
#define UART_BUART_sRX_RxBitCounter__16BIT_MASK_MASK_REG CYREG_B1_UDB08_09_MSK
#define UART_BUART_sRX_RxBitCounter__16BIT_MASK_PERIOD_REG CYREG_B1_UDB08_09_MSK
#define UART_BUART_sRX_RxBitCounter__16BIT_PERIOD_MASK_REG CYREG_B1_UDB08_09_MSK
#define UART_BUART_sRX_RxBitCounter__16BIT_PERIOD_PERIOD_REG CYREG_B1_UDB08_09_MSK
#define UART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG CYREG_B1_UDB08_ACTL
#define UART_BUART_sRX_RxBitCounter__CONTROL_REG CYREG_B1_UDB08_CTL
#define UART_BUART_sRX_RxBitCounter__CONTROL_ST_REG CYREG_B1_UDB08_ST_CTL
#define UART_BUART_sRX_RxBitCounter__COUNT_REG CYREG_B1_UDB08_CTL
#define UART_BUART_sRX_RxBitCounter__COUNT_ST_REG CYREG_B1_UDB08_ST_CTL
#define UART_BUART_sRX_RxBitCounter__MASK_CTL_AUX_CTL_REG CYREG_B1_UDB08_MSK_ACTL
#define UART_BUART_sRX_RxBitCounter__PERIOD_REG CYREG_B1_UDB08_MSK
#define UART_BUART_sRX_RxBitCounter__PER_CTL_AUX_CTL_REG CYREG_B1_UDB08_MSK_ACTL
#define UART_BUART_sRX_RxShifter_u0__A0_A1_REG CYREG_B1_UDB11_A0_A1
#define UART_BUART_sRX_RxShifter_u0__A0_REG CYREG_B1_UDB11_A0
#define UART_BUART_sRX_RxShifter_u0__A1_REG CYREG_B1_UDB11_A1
#define UART_BUART_sRX_RxShifter_u0__D0_D1_REG CYREG_B1_UDB11_D0_D1
#define UART_BUART_sRX_RxShifter_u0__D0_REG CYREG_B1_UDB11_D0
#define UART_BUART_sRX_RxShifter_u0__D1_REG CYREG_B1_UDB11_D1
#define UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG CYREG_B1_UDB11_ACTL
#define UART_BUART_sRX_RxShifter_u0__F0_F1_REG CYREG_B1_UDB11_F0_F1
#define UART_BUART_sRX_RxShifter_u0__F0_REG CYREG_B1_UDB11_F0
#define UART_BUART_sRX_RxShifter_u0__F1_REG CYREG_B1_UDB11_F1
#define UART_BUART_sRX_RxSts__16BIT_STATUS_AUX_CTL_REG CYREG_B1_UDB07_08_ACTL
#define UART_BUART_sRX_RxSts__16BIT_STATUS_REG CYREG_B1_UDB07_08_ST
#define UART_BUART_sRX_RxSts__3__MASK 0x08u
#define UART_BUART_sRX_RxSts__3__POS 3
#define UART_BUART_sRX_RxSts__4__MASK 0x10u
#define UART_BUART_sRX_RxSts__4__POS 4
#define UART_BUART_sRX_RxSts__5__MASK 0x20u
#define UART_BUART_sRX_RxSts__5__POS 5
#define UART_BUART_sRX_RxSts__MASK 0x38u
#define UART_BUART_sRX_RxSts__MASK_REG CYREG_B1_UDB07_MSK
#define UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG CYREG_B1_UDB07_ACTL
#define UART_BUART_sRX_RxSts__STATUS_REG CYREG_B1_UDB07_ST
#define UART_BUART_sTX_TxShifter_u0__16BIT_A0_REG CYREG_B0_UDB09_10_A0
#define UART_BUART_sTX_TxShifter_u0__16BIT_A1_REG CYREG_B0_UDB09_10_A1
#define UART_BUART_sTX_TxShifter_u0__16BIT_D0_REG CYREG_B0_UDB09_10_D0
#define UART_BUART_sTX_TxShifter_u0__16BIT_D1_REG CYREG_B0_UDB09_10_D1
#define UART_BUART_sTX_TxShifter_u0__16BIT_DP_AUX_CTL_REG CYREG_B0_UDB09_10_ACTL
#define UART_BUART_sTX_TxShifter_u0__16BIT_F0_REG CYREG_B0_UDB09_10_F0
#define UART_BUART_sTX_TxShifter_u0__16BIT_F1_REG CYREG_B0_UDB09_10_F1
#define UART_BUART_sTX_TxShifter_u0__A0_A1_REG CYREG_B0_UDB09_A0_A1
#define UART_BUART_sTX_TxShifter_u0__A0_REG CYREG_B0_UDB09_A0
#define UART_BUART_sTX_TxShifter_u0__A1_REG CYREG_B0_UDB09_A1
#define UART_BUART_sTX_TxShifter_u0__D0_D1_REG CYREG_B0_UDB09_D0_D1
#define UART_BUART_sTX_TxShifter_u0__D0_REG CYREG_B0_UDB09_D0
#define UART_BUART_sTX_TxShifter_u0__D1_REG CYREG_B0_UDB09_D1
#define UART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG CYREG_B0_UDB09_ACTL
#define UART_BUART_sTX_TxShifter_u0__F0_F1_REG CYREG_B0_UDB09_F0_F1
#define UART_BUART_sTX_TxShifter_u0__F0_REG CYREG_B0_UDB09_F0
#define UART_BUART_sTX_TxShifter_u0__F1_REG CYREG_B0_UDB09_F1
#define UART_BUART_sTX_TxSts__0__MASK 0x01u
#define UART_BUART_sTX_TxSts__0__POS 0
#define UART_BUART_sTX_TxSts__16BIT_STATUS_AUX_CTL_REG CYREG_B0_UDB09_10_ACTL
#define UART_BUART_sTX_TxSts__16BIT_STATUS_REG CYREG_B0_UDB09_10_ST
#define UART_BUART_sTX_TxSts__1__MASK 0x02u
#define UART_BUART_sTX_TxSts__1__POS 1
#define UART_BUART_sTX_TxSts__2__MASK 0x04u
#define UART_BUART_sTX_TxSts__2__POS 2
#define UART_BUART_sTX_TxSts__3__MASK 0x08u
#define UART_BUART_sTX_TxSts__3__POS 3
#define UART_BUART_sTX_TxSts__MASK 0x0Fu
#define UART_BUART_sTX_TxSts__MASK_REG CYREG_B0_UDB09_MSK
#define UART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG CYREG_B0_UDB09_ACTL
#define UART_BUART_sTX_TxSts__STATUS_REG CYREG_B0_UDB09_ST
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A0_REG CYREG_B0_UDB08_09_A0
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A1_REG CYREG_B0_UDB08_09_A1
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D0_REG CYREG_B0_UDB08_09_D0
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D1_REG CYREG_B0_UDB08_09_D1
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_DP_AUX_CTL_REG CYREG_B0_UDB08_09_ACTL
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F0_REG CYREG_B0_UDB08_09_F0
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F1_REG CYREG_B0_UDB08_09_F1
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__A0_A1_REG CYREG_B0_UDB08_A0_A1
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__A0_REG CYREG_B0_UDB08_A0
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__A1_REG CYREG_B0_UDB08_A1
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_D1_REG CYREG_B0_UDB08_D0_D1
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG CYREG_B0_UDB08_D0
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG CYREG_B0_UDB08_D1
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__DP_AUX_CTL_REG CYREG_B0_UDB08_ACTL
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__F0_F1_REG CYREG_B0_UDB08_F0_F1
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__F0_REG CYREG_B0_UDB08_F0
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__F1_REG CYREG_B0_UDB08_F1

/* Isr_timer */
#define Isr_timer__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define Isr_timer__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define Isr_timer__INTC_MASK 0x02u
#define Isr_timer__INTC_NUMBER 1u
#define Isr_timer__INTC_PRIOR_NUM 7u
#define Isr_timer__INTC_PRIOR_REG CYREG_NVIC_PRI_1
#define Isr_timer__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define Isr_timer__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* Isr_rx */
#define Isr_rx__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define Isr_rx__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define Isr_rx__INTC_MASK 0x01u
#define Isr_rx__INTC_NUMBER 0u
#define Isr_rx__INTC_PRIOR_NUM 7u
#define Isr_rx__INTC_PRIOR_REG CYREG_NVIC_PRI_0
#define Isr_rx__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define Isr_rx__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* Isr_tx */
#define Isr_tx__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define Isr_tx__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define Isr_tx__INTC_MASK 0x04u
#define Isr_tx__INTC_NUMBER 2u
#define Isr_tx__INTC_PRIOR_NUM 7u
#define Isr_tx__INTC_PRIOR_REG CYREG_NVIC_PRI_2
#define Isr_tx__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define Isr_tx__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* Rx_1 */
#define Rx_1__0__MASK 0x02u
#define Rx_1__0__PC CYREG_PRT0_PC1
#define Rx_1__0__PORT 0u
#define Rx_1__0__SHIFT 1
#define Rx_1__AG CYREG_PRT0_AG
#define Rx_1__AMUX CYREG_PRT0_AMUX
#define Rx_1__BIE CYREG_PRT0_BIE
#define Rx_1__BIT_MASK CYREG_PRT0_BIT_MASK
#define Rx_1__BYP CYREG_PRT0_BYP
#define Rx_1__CTL CYREG_PRT0_CTL
#define Rx_1__DM0 CYREG_PRT0_DM0
#define Rx_1__DM1 CYREG_PRT0_DM1
#define Rx_1__DM2 CYREG_PRT0_DM2
#define Rx_1__DR CYREG_PRT0_DR
#define Rx_1__INP_DIS CYREG_PRT0_INP_DIS
#define Rx_1__LCD_COM_SEG CYREG_PRT0_LCD_COM_SEG
#define Rx_1__LCD_EN CYREG_PRT0_LCD_EN
#define Rx_1__MASK 0x02u
#define Rx_1__PORT 0u
#define Rx_1__PRT CYREG_PRT0_PRT
#define Rx_1__PRTDSI__CAPS_SEL CYREG_PRT0_CAPS_SEL
#define Rx_1__PRTDSI__DBL_SYNC_IN CYREG_PRT0_DBL_SYNC_IN
#define Rx_1__PRTDSI__OE_SEL0 CYREG_PRT0_OE_SEL0
#define Rx_1__PRTDSI__OE_SEL1 CYREG_PRT0_OE_SEL1
#define Rx_1__PRTDSI__OUT_SEL0 CYREG_PRT0_OUT_SEL0
#define Rx_1__PRTDSI__OUT_SEL1 CYREG_PRT0_OUT_SEL1
#define Rx_1__PRTDSI__SYNC_OUT CYREG_PRT0_SYNC_OUT
#define Rx_1__PS CYREG_PRT0_PS
#define Rx_1__SHIFT 1
#define Rx_1__SLW CYREG_PRT0_SLW

/* Tx_1 */
#define Tx_1__0__MASK 0x01u
#define Tx_1__0__PC CYREG_PRT0_PC0
#define Tx_1__0__PORT 0u
#define Tx_1__0__SHIFT 0
#define Tx_1__AG CYREG_PRT0_AG
#define Tx_1__AMUX CYREG_PRT0_AMUX
#define Tx_1__BIE CYREG_PRT0_BIE
#define Tx_1__BIT_MASK CYREG_PRT0_BIT_MASK
#define Tx_1__BYP CYREG_PRT0_BYP
#define Tx_1__CTL CYREG_PRT0_CTL
#define Tx_1__DM0 CYREG_PRT0_DM0
#define Tx_1__DM1 CYREG_PRT0_DM1
#define Tx_1__DM2 CYREG_PRT0_DM2
#define Tx_1__DR CYREG_PRT0_DR
#define Tx_1__INP_DIS CYREG_PRT0_INP_DIS
#define Tx_1__LCD_COM_SEG CYREG_PRT0_LCD_COM_SEG
#define Tx_1__LCD_EN CYREG_PRT0_LCD_EN
#define Tx_1__MASK 0x01u
#define Tx_1__PORT 0u
#define Tx_1__PRT CYREG_PRT0_PRT
#define Tx_1__PRTDSI__CAPS_SEL CYREG_PRT0_CAPS_SEL
#define Tx_1__PRTDSI__DBL_SYNC_IN CYREG_PRT0_DBL_SYNC_IN
#define Tx_1__PRTDSI__OE_SEL0 CYREG_PRT0_OE_SEL0
#define Tx_1__PRTDSI__OE_SEL1 CYREG_PRT0_OE_SEL1
#define Tx_1__PRTDSI__OUT_SEL0 CYREG_PRT0_OUT_SEL0
#define Tx_1__PRTDSI__OUT_SEL1 CYREG_PRT0_OUT_SEL1
#define Tx_1__PRTDSI__SYNC_OUT CYREG_PRT0_SYNC_OUT
#define Tx_1__PS CYREG_PRT0_PS
#define Tx_1__SHIFT 0
#define Tx_1__SLW CYREG_PRT0_SLW

/* Miscellaneous */
/* -- WARNING: define names containing LEOPARD or PANTHER are deprecated and will be removed in a future release */
#define CYDEV_DEBUGGING_DPS_SWD_SWV 6
#define CYDEV_CONFIG_UNUSED_IO_AllowButWarn 0
#define CYDEV_CONFIGURATION_MODE_COMPRESSED 0
#define CYDEV_CONFIG_FASTBOOT_ENABLED 0
#define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1u
#define CYDEV_CHIP_REVISION_5A_PRODUCTION 1u
#define CYDEV_CHIP_MEMBER_5A 3u
#define CYDEV_CHIP_FAMILY_PSOC5 3u
#define CYDEV_CHIP_DIE_PANTHER 3u
#define CYDEV_CHIP_DIE_EXPECT CYDEV_CHIP_DIE_PANTHER
#define BCLK__BUS_CLK__HZ 24000000U
#define BCLK__BUS_CLK__KHZ 24000U
#define BCLK__BUS_CLK__MHZ 24U
#define CYDEV_CHIP_DIE_ACTUAL CYDEV_CHIP_DIE_EXPECT
#define CYDEV_CHIP_DIE_LEOPARD 1u
#define CYDEV_CHIP_DIE_PSOC4A 2u
#define CYDEV_CHIP_DIE_PSOC5LP 4u
#define CYDEV_CHIP_DIE_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_PSOC3 1u
#define CYDEV_CHIP_FAMILY_PSOC4 2u
#define CYDEV_CHIP_FAMILY_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_USED CYDEV_CHIP_FAMILY_PSOC5
#define CYDEV_CHIP_JTAG_ID 0x0E13C069u
#define CYDEV_CHIP_MEMBER_3A 1u
#define CYDEV_CHIP_MEMBER_4A 2u
#define CYDEV_CHIP_MEMBER_5B 4u
#define CYDEV_CHIP_MEMBER_UNKNOWN 0u
#define CYDEV_CHIP_MEMBER_USED CYDEV_CHIP_MEMBER_5A
#define CYDEV_CHIP_REVISION_3A_ES1 0u
#define CYDEV_CHIP_REVISION_3A_ES2 1u
#define CYDEV_CHIP_REVISION_3A_ES3 3u
#define CYDEV_CHIP_REVISION_3A_PRODUCTION 3u
#define CYDEV_CHIP_REVISION_4A_ES0 17u
#define CYDEV_CHIP_REVISION_4A_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_5A_ES0 0u
#define CYDEV_CHIP_REVISION_5A_ES1 1u
#define CYDEV_CHIP_REVISION_5B_ES0 0u
#define CYDEV_CHIP_REVISION_5B_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_USED CYDEV_CHIP_REVISION_5A_PRODUCTION
#define CYDEV_CHIP_REV_EXPECT CYDEV_CHIP_REV_PANTHER_PRODUCTION
#define CYDEV_CHIP_REV_LEOPARD_ES1 0u
#define CYDEV_CHIP_REV_LEOPARD_ES2 1u
#define CYDEV_CHIP_REV_LEOPARD_ES3 3u
#define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3u
#define CYDEV_CHIP_REV_PANTHER_ES0 0u
#define CYDEV_CHIP_REV_PANTHER_ES1 1u
#define CYDEV_CHIP_REV_PSOC4A_ES0 17u
#define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17u
#define CYDEV_CHIP_REV_PSOC5LP_ES0 0u
#define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0u
#define CYDEV_CONFIGURATION_COMPRESSED 1
#define CYDEV_CONFIGURATION_DMA 0
#define CYDEV_CONFIGURATION_ECC 1
#define CYDEV_CONFIGURATION_IMOENABLED CYDEV_CONFIG_FASTBOOT_ENABLED
#define CYDEV_CONFIGURATION_MODE CYDEV_CONFIGURATION_MODE_COMPRESSED
#define CYDEV_CONFIGURATION_MODE_DMA 2
#define CYDEV_CONFIGURATION_MODE_UNCOMPRESSED 1
#define CYDEV_CONFIG_UNUSED_IO CYDEV_CONFIG_UNUSED_IO_AllowButWarn
#define CYDEV_CONFIG_UNUSED_IO_AllowWithInfo 1
#define CYDEV_CONFIG_UNUSED_IO_Disallowed 2
#define CYDEV_DATA_CACHE_ENABLED 0
#define CYDEV_DEBUGGING_DPS CYDEV_DEBUGGING_DPS_SWD_SWV
#define CYDEV_DEBUGGING_DPS_Disable 3
#define CYDEV_DEBUGGING_ENABLE 1
#define CYDEV_DEBUGGING_REQXRES 1
#define CYDEV_DEBUGGING_XRES 0
#define CYDEV_DEBUG_ENABLE_MASK 0x01u
#define CYDEV_DEBUG_ENABLE_REGISTER CYREG_MLOGIC_DBG_DBE
#define CYDEV_DMA_CHANNELS_AVAILABLE 24u
#define CYDEV_ECC_ENABLE 0
#define CYDEV_HEAP_SIZE 0x1000
#define CYDEV_INSTRUCT_CACHE_ENABLED 1
#define CYDEV_INTR_RISING 0x0000003Fu
#define CYDEV_PROJ_TYPE 0
#define CYDEV_PROJ_TYPE_BOOTLOADER 1
#define CYDEV_PROJ_TYPE_LOADABLE 2
#define CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER 3
#define CYDEV_PROJ_TYPE_STANDARD 0
#define CYDEV_PROTECTION_ENABLE 0
#define CYDEV_STACK_SIZE 0x4000
#define CYDEV_USE_BUNDLED_CMSIS 1
#define CYDEV_VDDA 5.0
#define CYDEV_VDDA_MV 5000
#define CYDEV_VDDD 5.0
#define CYDEV_VDDD_MV 5000
#define CYDEV_VDDIO0 5.0
#define CYDEV_VDDIO0_MV 5000
#define CYDEV_VDDIO1 5.0
#define CYDEV_VDDIO1_MV 5000
#define CYDEV_VDDIO2 5.0
#define CYDEV_VDDIO2_MV 5000
#define CYDEV_VDDIO3 5.0
#define CYDEV_VDDIO3_MV 5000
#define CYDEV_VIO0 5
#define CYDEV_VIO0_MV 5000
#define CYDEV_VIO1 5
#define CYDEV_VIO1_MV 5000
#define CYDEV_VIO2 5
#define CYDEV_VIO2_MV 5000
#define CYDEV_VIO3 5
#define CYDEV_VIO3_MV 5000
#define DMA_CHANNELS_USED__MASK0 0x00000000u
#define CYDEV_BOOTLOADER_ENABLE 0

#endif /* INCLUDED_CYFITTER_H */
