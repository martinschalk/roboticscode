/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#include "global.h"
#include "types.h"
#include "hal.h"



static STATUS   HalStatus = HAL_TRANSMISSION_READY;
static BOOL     HalIsBusIdle = TRUE;
static uint8    RxCount;
static uint8    TxCount;

/*******************************************************/
STATUS HAL_GetHalStatus(void)
{
	return HalStatus;
}

/*******************************************************/
void HAL_SetHalStatus(STATUS value)
{
	HalStatus = value;
}

/*******************************************************/
CY_ISR(isr_rx_routine)
{
	RxCount++;
}

/*******************************************************/
CY_ISR(isr_tx_routine)
{
	TxCount = 0;
	HalStatus = HAL_TRANSMISSION_READY;
	UART_EnableRxInt();
}

/*******************************************************/
STATUS 	HAL_Init(void)
{
	RxCount = 0;
	UART_Start();
    Isr_rx_Start();
	Isr_tx_Start();	
	Isr_rx_SetVector(isr_rx_routine);
	Isr_tx_SetVector(isr_tx_routine);
	Isr_rx_Enable();
	Isr_tx_Enable();
	UART_EnableRxInt();
	UART_EnableTxInt();
	
	return SUCCESS;
}

/*******************************************************/
uint8 	HAL_GetRxIsrCount()
{
	return RxCount;
}

/*******************************************************/
uint8 	HAL_GetRxBufferCount()
{
	return UART_GetRxBufferSize();
}


/* check, if FIFO has data available.*/
	//if ((UART_ReadRxStatus() & UART_RX_STS_FIFO_NOTEMPTY) == UART_RX_STS_FIFO_NOTEMPTY)
/*******************************************************/
uint8 	HAL_GetByte()
{
	uint8 value;
	
	UART_DisableRxInt();
	
	/* chech if data available */
	if (UART_GetRxBufferSize > 0)
	{
		value = UART_ReadRxData();
		RxCount--;
	}
	else
	{
		value = 0;
	}

	UART_EnableRxInt();
	
	return value;
}

/*******************************************************/
STATUS 	HAL_TransmitByte(uint8 value)
{
    /* Check if bus is idle */
    if (HalIsBusIdle == TRUE)
    {
    	UART_DisableRxInt();
    	HalStatus = HAL_TRANSMISSION_BUSY;
    	
    	/* wait until uart read to transmitted */
    	while (UART_ReadTxStatus() != UART_TX_STS_COMPLETE)
    	;
    	TxCount++;
    	UART_WriteTxData(value);
    	
    	HalStatus = HAL_TRANSMISSION_READY;
        
        return SUCCESS;
	}
	else
    {
        return !SUCCESS;
    }
}

/*******************************************************/
STATUS 	HAL_TransmitArray(const uint8* source, uint8 numBytes)
{
	UART_DisableRxInt();
	HalStatus = HAL_TRANSMISSION_BUSY;
	TxCount += numBytes;
	UART_PutArray(source, numBytes); //function can be interrupted by <isr_tx_routine>
	HalStatus = HAL_TRANSMISSION_READY;
	// UART_EnableRxInt(); => done in <isr_tx_routine> if last byte transmitted
	return SUCCESS;
}

/*******************************************************/
#ifdef TEST_UART
BOOL GetHalBusIdleState(void)
{
    return HalIsBusIdle;
}

void SetHalBusIdleState(BOOL state)
{
    HalIsBusIdle = state;
}

#endif

/* [] END OF FILE */
