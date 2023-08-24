/*
 * SPI_prv.h
 *
 *  Created on: Aug 24, 2023
 *      Author: kareem
 */

#ifndef SPI_PRV_H_
#define SPI_PRV_H_

#define SPI_PERIPHERSL_NUM      3U

static void (*SPI_pvTxEmptyCallBackLine[3])(void) = {NULL,NULL,NULL};
static void (*SPI_pvRxNotEmptyCallBackLine[3])(void) = {NULL,NULL,NULL};



#endif /* SPI_PRV_H_ */
