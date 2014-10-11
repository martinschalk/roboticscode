/* Copyright (C) <2014> <Martin Schalk>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */


/* 
BUFFER MESSAGE (RX/TX)
-------------------------------
| Length | b0 | b1 | ... | bn |
-------------------------------
*/

/*******************************************************/
#define TX_BUFFER_SIZE		256
#define RX_BUFFER_SIZE		256



/* Error Codes */
/*******************************************************/
#define BPL_STATUS_OK					0
#define BPL_STATUS_RX_BUFFER_FULL		(uint8)(-1)
#define BPL_STATUS_TX_BUFFER_FULL		(uint8)(-2)
#define BPL_STATUS_TX_DATA_MISMATCH		(uint8)(-3)

/*******************************************************/
void BPL_HandleTask(void);



/* [] END OF FILE */
