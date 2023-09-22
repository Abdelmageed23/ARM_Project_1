/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "SPI_interface.h"

int main(void)
{
    RCC_voidAHB1EnablePerapheralClock(AHB1_GPIOA);
	RCC_voidAPB2EnablePerapheralClock(APB2_SPI11);
	GPIO_PinConfig_T SPI_MOSIpin=
	{
		.AltFunc=AF5,
		.Mode = ALTER_FUNC,
		.OutType=PUSH_PULL,
		.PinNum=PIN7,
		.Port=PORTA,
		.PullType=NO_PULL,
		.Speed=SPEED_LOW,
	};
	GPIO_PinConfig_T SPI_MISOpin=
	{
		.AltFunc=AF5,
		.Mode = ALTER_FUNC,
		.OutType=PUSH_PULL,
		.PinNum=PIN6,
		.Port=PORTA,
		.PullType=NO_PULL,
		.Speed=SPEED_LOW,
	};
	GPIO_PinConfig_T SPI_SCKpin=
	{
		.AltFunc=AF5,
		.Mode = ALTER_FUNC,
		.OutType=PUSH_PULL,
		.PinNum=PIN5,
		.Port=PORTA,
		.PullType=NO_PULL,
		.Speed=SPEED_HIGH,
	};
	GPIO_PinConfig_T SPI_NSSpin=
		{
			.AltFunc=AF5,
			.Mode = ALTER_FUNC,
			.OutType=PUSH_PULL,
			.PinNum=PIN4,
			.Port=PORTA,
			.PullType=NO_PULL,
			.Speed=SPEED_HIGH,
		};
	GPIO_u8PinInit(&SPI_MOSIpin);
	GPIO_u8PinInit(&SPI_MISOpin);
	GPIO_u8PinInit(&SPI_SCKpin);
	GPIO_u8PinInit(&SPI_NSSpin);
	SPI_Config_ty SPI_setting=
	{
		.ClockSpeed=SPI_FclkDiv_256,
		.DataFrameLenght=SPI_8_BIT_DATA_FRAME,
		.InterruptsStates.TxBufferEmptyInter=SPI_INTER_ENABLE,
		.LinesDirections=SPI_2LineUnidirectional,
		.SpiNumber=SPI_1,
		.SPIperiphState=SPI_ENABLE,
		.SpiState=SPI_MASTER,
		.SSOstate=SPI_SSoutputEnableSingleMaster,
	};
	SPI_u8Init(&SPI_setting);
	while(1){
	SPI_u8SendData_polling(SPI_1,'A');
	}
	uint8_t arry[11]="Abdelkareem";
	SPI_u8SendData_IT(SPI_1, 11,&arry[0]);
	for(;;);
}