/**
 ******************************************************************************
 * @file           : RTC_program.c
 * @author         : Diea Abdeltwab
 * @layer          : HAL
 * @brief          : 
 * @date           : 24/8/2023
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
/******************************************************************************/
/************************ LIB Layer *******************************************/
/******************************************************************************/
#include <stdint.h>
#include <string.h>
#include "ERROR_STATE.h"
#include "BIT_MATH.h"
/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
#include "GPIO_interface.h"
#include "DMA_interface.h"
#include "I2C_interface.h"
/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
#include "RTC_interface.h"
#include "RTC_private.h"
#include "RTC_config.h"
/******************************************************************************/
/************************ Global **********************************************/
/******************************************************************************/

/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : HRTC_u8Init
 * @brief          : initialization RTC
 * @param[in]      : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void HRTC_u8Init( I2Cconfig_t *Copy_I2CCnfg )
{
	uint8_t Local_Au8TransmitArray[2] ;
	Local_Au8TransmitArray[0] = ADDRESS_SEC ;
	Local_Au8TransmitArray[1] = RTC_SEC_MASK ;
	/*********************************************************************************************/
	MI2C_u8Transmit_DMA(Copy_I2CCnfg, RTC_I2C_SLAVE_ADDRESS, Local_Au8TransmitArray,2);

	/*********************************************************************************************/
}

void HRTC_voidSetDateTime ( I2Cconfig_t *Copy_I2CCnfg,RTC_DateTime_t *RTC_time )
{
	uint8_t Local_u8BcdArr[7];

	BinaryToBCD((uint8_t*)RTC_time,Local_u8BcdArr,7);

	Local_u8BcdArr[HRS] &= ~(RTC_HRS_12_24_MASK<<RTC_HRS_12_24_BIT);

	RTC_Send_T NewArr =
	{

		.StartAdd = ADDRESS_MIN,
		.Mins = Local_u8BcdArr[MINS],
		.Hrs = Local_u8BcdArr[HRS],
		.Day = Local_u8BcdArr[DAY],
		.Date = Local_u8BcdArr[DATE],
		.Month = Local_u8BcdArr[MONTH],
		.Year = Local_u8BcdArr[YEAR]
	};
	MI2C_u8Transmit_DMA(Copy_I2CCnfg, RTC_I2C_SLAVE_ADDRESS, &NewArr.StartAdd, 7);

}
void HRTC_voidGetDateTime ( I2Cconfig_t *Copy_I2CCnfg,RTC_DateTime_t *RTC_time )
{
	uint8_t RTC_AddArr[7] = RTC_ADDRESS_ARR;

	MI2C_u8Transmit_DMA(Copy_I2CCnfg, RTC_I2C_SLAVE_ADDRESS, (uint8_t*)(&RTC_AddArr[ADDRESS_MIN]), 1);
	MI2C_u8Receive_DMA(Copy_I2CCnfg, RTC_I2C_SLAVE_ADDRESS,(uint8_t *)RTC_time , 6);
}

/**
 ******************************************************************************
 * @fn             : BinaryToBCD
 * @brief          : Convert From Binary To BCD
 * @param[in]      : Copy_u8Vlaue --> Set Binary Vlaue
 * @retval         : Get BCD Value u8
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void BinaryToBCD  (uint8_t *Copy_pu8BinArr ,uint8_t *Copy_pu8BcdArr ,uint8_t Copy_u8ArrSize)
{
	uint8_t Local_u8Tens , Local_u8Ones ,Local_u8Counter;


	for(Local_u8Counter = 0 ;Local_u8Counter < Copy_u8ArrSize ;Local_u8Counter++)
	{
		if ( Copy_pu8BinArr[Local_u8Counter] >= 10 )
		{
			Local_u8Tens =  Copy_pu8BinArr[Local_u8Counter]/10;
			Local_u8Ones =  Copy_pu8BinArr[Local_u8Counter]%10;
			Copy_pu8BcdArr[Local_u8Counter] = (uint8_t)((Local_u8Tens<<4) | Local_u8Ones) ;
		}
		else
		{
			Copy_pu8BcdArr[Local_u8Counter] = Copy_pu8BinArr[Local_u8Counter];

		}
	}



}
/**
 ******************************************************************************
 * @fn             : BinaryToBCD
 * @brief          : Convert From Binary To BCD
 * @param[in]      : Copy_u8Vlaue --> Set   Vlaue
 * @retval         : Get  Binary Value u8
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
 void BCDToBinary (uint8_t *Copy_pu8BcdArr , uint8_t *Copy_pu8BinArr ,uint8_t Copy_u8ArrSize)
{
	uint8_t Local_u8Tens , Local_u8Ones ,Local_u8Counter;

	for(Local_u8Counter = 0 ;Local_u8Counter < Copy_u8ArrSize ;Local_u8Counter++)
	{
		Local_u8Tens = (uint8_t)((Copy_pu8BcdArr[Local_u8Counter] >> 4) * 10) ;
		Local_u8Ones = Copy_pu8BcdArr[Local_u8Counter] & (uint8_t)0x0F;
		Copy_pu8BinArr[Local_u8Counter] = Local_u8Tens + Local_u8Ones ;
	}

}

/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/

