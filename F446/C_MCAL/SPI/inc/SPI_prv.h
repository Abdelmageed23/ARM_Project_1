/*
 * SPI_prv.h
 *
 *  Created on: Aug 24, 2023
 *      Author: kareem
 */

#ifndef SPI_PRV_H_
#define SPI_PRV_H_
/*****************************************************************************************
 * CR1 Bits
 ****************************************************************************************
*/
#define CR1_BIDIMODE        15U
#define CR1_BIDIOE          14U
#define CR1_CRCEN           13U
#define CR1_CRCNEXT         12U
#define CR1_DFF             11U
#define CR1_RXONLY          10U
#define CR1_SSM             9U
#define CR1_SSI             8U
#define CR1_LSBFIRST        7U
#define CR1_SPE             6U
#define CR1_BR              3U
#define CR1_MSTR            2U
#define CR1_CPOL            1U
#define CR1_CPHA            0U
/*****************************************************************************************
 * CR2 Bits
 ****************************************************************************************
*/
#define CR2_TXEIE           7U
#define CR2_RXNEIE          6U
#define CR2_ERRIE           5U
#define CR2_FRF             4U
#define CR2_SSOE            2U
#define CR2_TXDMAEN         1U
#define CR2_RXDMAEN         0U
/*****************************************************************************************
 * SR Bits
 ****************************************************************************************
*/
#define SR_FRF             8U
#define SR_BSY             7U
#define SR_OVR             6U
#define SR_MODF            5U
#define SR_CRCERR          4U
#define SR_UDR             3U
#define SR_CHSIDE          2U
#define SR_TXE             1U
#define SR_RXNE            0U

/******************************************************************************************
 
 ********************************************************************************************
*/
#define SPI_ONE_BIT_MASKING     1U
#define SPI_PERIPHERSL_NUM      4U

static void (*SPI_pvTxEmptyCallBackLine[4])(void) = {NULL,NULL,NULL,NULL};
static void (*SPI_pvRxNotEmptyCallBackLine[4])(void) = {NULL,NULL,NULL,NULL};


#endif /* SPI_PRV_H_ */
