/*
 * SPI_prv.h
 *
 *  Created on: Aug 24, 2023
 *      Author: kareem
 */

#ifndef SPI_PRV_H_
#define SPI_PRV_H_

#define SPI_PERIPHERSL_NUM      4U

static void (*SPI_pvTxEmptyCallBackLine[4])(void) = {NULL,NULL,NULL,NULL};
static void (*SPI_pvRxNotEmptyCallBackLine[4])(void) = {NULL,NULL,NULL,NULL};


#endif /* SPI_PRV_H_ */
