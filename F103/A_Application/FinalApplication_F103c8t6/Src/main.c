/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Diea Abdeltwab
 * @brief          :
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
#include "NVIC_interface.h"
#include "EXTI_interface.h"
#include "AFIO_interface.h"
#include "SCB_interface.h"
#include "DMA_interface.h"
#include "USART_interface.h"
#include "SPI_interface.h"
/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
#include "LCD_interface.h"
/********************************************************************************************************************************************/
/**************************************************** Global Variable ***********************************************************************/
/********************************************************************************************************************************************/
uint8_t Global_u8Counter           =0;
uint8_t Global_u8ReceieComplateFlag=0;
uint8_t Global_ReceiveFlag         =0;
uint8_t Global_pu8ReceiveArray  [13]="             ";
/********************************************************************************************************************************************/
/**************************************************** Call Back Function ********************************************************************/
/********************************************************************************************************************************************/
void ReceiveSwitchFunc (uint8_t Data)
{
	if (Global_ReceiveFlag==0 )
	{
		switch (Data)
		{
		case '~':
			GPIO_u8SetPinValue(PORTA, PIN1 , PIN_HIGH);
			for(int i = 0; i < 1000000 ;i++);
			GPIO_u8SetPinValue(PORTA, PIN1 , PIN_LOW);
		break;

		case '!':
			GPIO_u8SetPinValue(PORTC, PIN15, PIN_HIGH);
			for(int i = 0; i < 1000000 ;i++);
			GPIO_u8SetPinValue(PORTC, PIN15, PIN_LOW);
		break;

		case '@':   Global_ReceiveFlag=1;break;

		case '#':   Global_ReceiveFlag=2;break;

		case '$':   Global_ReceiveFlag=3;break;

		}
	}
	else
	{
		if (Data != '\0')
		{
			Global_pu8ReceiveArray[Global_u8Counter] = Data;
			Global_u8Counter++;
		}
		else
		{
			Global_pu8ReceiveArray[Global_u8Counter] = '\0';
			Global_u8ReceieComplateFlag=1;
			Global_u8Counter=0;
		}
	}
}
/********************************************************************************************************************************************/
/**************************************************** STK Call Back Function  ***************************************************************/
/********************************************************************************************************************************************/
void AlarmStopNotificationFunc (void)
{
	GPIO_u8SetPinValue(PORTB, PIN4,PIN_LOW);
	GPIO_u8SetPinValue(PORTC, PIN14,PIN_LOW);
}
/********************************************************************************************************************************************/
/**************************************************** EXTI Call Back Function  **************************************************************/
/********************************************************************************************************************************************/
void AlarmNotificationFunc (void)
{
	MSTK_u8SetInterval(5000000,SINGLE,AlarmStopNotificationFunc);
	GPIO_u8SetPinValue(PORTB, PIN4,PIN_HIGH);
	GPIO_u8SetPinValue(PORTC, PIN14,PIN_HIGH);
}
/********************************************************************************************************************************************/
/**************************************************** Main Function  ************************************************************************/
/********************************************************************************************************************************************/
int main(void)
{
	/********************************************************************************************************************************************/
	/**************************************************** RCC Configuration *********************************************************************/
	/********************************************************************************************************************************************/
	RCC_SetClksts(SET_CLK_HSE,STATE_ON);
	RCC_SetSysClk(SYS_HSE);
	RCC_APB2EnableClock(APB2_IOPA);
	RCC_APB2EnableClock(APB2_IOPB);
	RCC_APB2EnableClock(APB2_IOPC);
	RCC_APB2EnableClock(APB2_SPI1);
	/********************************************************************************************************************************************/
	/**************************************************** STK Configuration *********************************************************************/
	/********************************************************************************************************************************************/
	MSTK_u8ClockConfig(STK_AHB_DIV_8);
	/********************************************************************************************************************************************/
	/**************************************************** LCD Configuration *********************************************************************/
	/********************************************************************************************************************************************/
	HLCD_voidInit();
	/********************************************************************************************************************************************/
	/**************************************************** GPIO Configuration ********************************************************************/
	/********************************************************************************************************************************************/
	GPIO_PinConfig_T RedLed ={ PORTA , PIN1 , OUTPUT_2MHZ , GPO_PUSHPULL , PULL_DN  };
	GPIO_u8PinInit(&RedLed);
	GPIO_PinConfig_T GRN    ={ PORTC , PIN15 , OUTPUT_2MHZ , GPO_PUSHPULL , PULL_DN };
	GPIO_u8PinInit(&GRN);
	GPIO_PinConfig_T BUZ    ={ PORTB , PIN4 , OUTPUT_2MHZ , GPO_PUSHPULL , PULL_DN  };
	GPIO_u8PinInit(&BUZ);
	GPIO_u8SetPinValue(BUZ.Port, BUZ.PinNum, PIN_LOW);

	GPIO_PinConfig_T BLU    ={ PORTC , PIN14 , OUTPUT_2MHZ , GPO_PUSHPULL , PULL_DN };
	GPIO_u8PinInit(&BLU);
	/********************************************************************************************************************************************/
	/**************************************************** SPI Configuration *********************************************************************/
	/********************************************************************************************************************************************/
	GPIO_PinConfig_T NSS  ={ PORTA , PIN4 , INPUT , FLOATING , PULL_DN  };
	GPIO_u8PinInit(&NSS);
	GPIO_PinConfig_T SCK  ={ PORTA , PIN5 , INPUT , FLOATING , PULL_DN  };
	GPIO_u8PinInit(&SCK);
	GPIO_PinConfig_T MISO ={ PORTA , PIN6 , OUTPUT_2MHZ , AF_PUSHPULL , PULL_DN  };
	GPIO_u8PinInit(&MISO);
	GPIO_PinConfig_T MOSI ={ PORTA , PIN7 , INPUT , FLOATING , PULL_DN  };
	GPIO_u8PinInit(&MOSI);
	MNVIC_u8EnableInterrupt(NVIC_SPI1);
	SPIconfig_t SPI_config ={SPI_1,LEADING_CAPTURE,LEADING_RISING,SLAVE,F_CLK_DIV_8,MSB,SELECT_ZERO,MANAGMENT_DISABLE,FULL_DUPLEX,FORMAT_8_BIT
			,RX_DMA_DISABLE,TX_DMA_DISABLE,SS_OUTPUT_DISABLE,RX_INTERRUPT_NOT_MASKED,TX_INTERRUPT_MASKED};
	MSPI_u8SetConfiguration(&SPI_config);
	MSPI_u8SendReceiveAsynch  ( SPI_1 ,'.' ,&ReceiveSwitchFunc );
	/********************************************************************************************************************************************/
	/**************************************************** EXTI Configuration ********************************************************************/
	/********************************************************************************************************************************************/
	MNVIC_u8EnableInterrupt(NVIC_EXTI0);
	GPIO_PinConfig_T EXTI_PIN ={ PORTA , PIN0 , INPUT , PULL_UPDN , PULL_UP  };
	GPIO_u8PinInit(&EXTI_PIN);
	EXTI_CONFIG_ty EXTI_Config={ EXTI_PORTA ,EXTI_PIN00,EXTI_ENABLE,EXTI_DISABLE,EXTI_RISING_TRIG, AlarmNotificationFunc };
	EXTI_u8Init(&EXTI_Config);
	/********************************************************************************************************************************************/
	/**************************************************** Loop **********************************************************************************/
	/********************************************************************************************************************************************/
	HLCD_voidInit();

	while(1)
	{

		if( Global_u8ReceieComplateFlag==1)
		{
			switch (Global_ReceiveFlag)
			{
			case 1 :	HLCD_voidClearLCD();
			HLCD_voidSetCursor(Location0, LCD_LINE0);
			HLCD_voidSendString((uint8_t *)"Time:");
			HLCD_voidSetCursor(Location5, LCD_LINE0);
			HLCD_voidSendString(Global_pu8ReceiveArray);
			Global_u8ReceieComplateFlag=0; Global_ReceiveFlag=0; break;
			case 2 :
				HLCD_voidSetCursor(Location0, LCD_LINE1);
				HLCD_voidSendString((uint8_t *)"Date:");
				HLCD_voidSetCursor(Location5, LCD_LINE1);
				HLCD_voidSendString(Global_pu8ReceiveArray);
				Global_u8ReceieComplateFlag=0; Global_ReceiveFlag=0;  break;

			case 3 : 	HLCD_voidClearLCD();
			HLCD_voidSetCursor(Location0, LCD_LINE0);
			HLCD_voidSendString((uint8_t *)"Alarm:");
			HLCD_voidSetCursor(Location5, LCD_LINE1);
			HLCD_voidSendString(Global_pu8ReceiveArray);
			Global_u8ReceieComplateFlag=0; Global_ReceiveFlag=0;  break;
			}
		}


	}
}
