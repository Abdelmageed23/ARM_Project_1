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
/******************************************************************************/
/************************ LIB Layer *******************************************/
/******************************************************************************/
#include <stdint.h>
/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
#include "RCC_INTERFACE.h"
#include "GPIO_INTERFACE.h"
#include "STK_interface.h"
/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
#include "LCD_interface.h"


int main(void)
{
	//MRCC_u8SetClockState(HSE,ENABLE);
	//MRCC_u8SetSystemClock(HSE);
	//MRCC_u8PeripheralsClockState(APB2,PER_IOPA,ENABLE);
	//MRCC_u8PeripheralsClockState(APB2,PER_IOPB,ENABLE);

	HLCD_voidInit();
	HLCD_voidClearLCD();
	HLCD_voidSendString((uint8_t *)"LCD Test 3");
	HLCD_voidClearLCD();
	HLCD_voidSetCursor(Location3,LCD_LINE1);
	HLCD_voidSendString((uint8_t *)"Mega Project");
    /* Loop forever */
	for(;;);
}
