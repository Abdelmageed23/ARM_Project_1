
/******************************************************************************/
/************************ LIB Layer *******************************************/
/******************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
#include "RCC_INTERFACE.h"
#include "GPIO_INTERFACE.h"
#include "STK_interface.h"
#include "SCB_interface.h"
#include "NVIC_interface.h"
#include "SYSCFG_interface.h"
#include "EXTI_interface.h"
#include "USART_interface.h"
#include "SPI_interface.h"
#include "I2C_interface.h"
/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
#include "RTC_interface.h"
/********************************************************************************************************************************************/
/**************************************************** Help Function *************************************************************************/
/********************************************************************************************************************************************/
void NumberToString (uint8_t Copy_u8Number , uint8_t* Copy_pu8String )
{
	if(Copy_u8Number <10)
	{
		Copy_pu8String[0]='0';
		Copy_pu8String[1]=Copy_u8Number + 48;
	}
	else if (Copy_u8Number >10 && Copy_u8Number <99 )
	{
		Copy_pu8String[0]= (Copy_u8Number / 10 )+ 48;
		Copy_pu8String[1]= (Copy_u8Number % 10 )+ 48;
	}
}
uint8_t *DataToString(RTC_date_t *Copy_Data)
{
	static uint8_t Local_Au8String[9];
	NumberToString(Copy_Data->date, &Local_Au8String[0]);
	Local_Au8String[2]='/';
	NumberToString(Copy_Data->month,&Local_Au8String[3]);
	Local_Au8String[5]='/';
	NumberToString(Copy_Data->year ,&Local_Au8String[6]);
	Local_Au8String[8]='\0';
	return Local_Au8String;
}
uint8_t *TimeToString(RTC_time_t *Copy_Time)
{
	static uint8_t Local_Au8String[9];
	NumberToString(Copy_Time->hours  ,&Local_Au8String[0]);
	Local_Au8String[2]=':';
	NumberToString(Copy_Time->minutes,&Local_Au8String[3]);
	Local_Au8String[5]=':';
	NumberToString(Copy_Time->seconds,&Local_Au8String[6]);
	Local_Au8String[8]='\0';
	return Local_Au8String;
}
char *GetDay(uint8_t Copy_DayIndex)
{
	char * Local_Au8Days[]={ "SUNDAY","MONDAY","TUESDAY","WEDNESDAY","THURSDAY","FRIDAY", "SATURDAY" };
	return Local_Au8Days[Copy_DayIndex-1];
}
/********************************************************************************************************************************************/
/**************************************************** STK Call Back Function ****************************************************************/
/********************************************************************************************************************************************/
void AlarmFunc (void)
{

}
/********************************************************************************************************************************************/
/**************************************************** Main Function  ************************************************************************/
/********************************************************************************************************************************************/
int main(void)
{
	/********************************************************************************************************************************************/
	/**************************************************** Local Variable ************************************************************************/
	/********************************************************************************************************************************************/
	RTC_time_t   SetTime,GetTime;
	RTC_date_t   SetDate,GetDate;
	volatile uint8_t Local_u8Pulstemp ;
	uint8_t Local_u8ReceiveTemp=0   ;
	RTC_time_t   AlarmTime1 , AlarmTime2 , AlarmTime3 , AlarmTime4 , AlarmTime5 ;
	/********************************************************************************************************************************************/
	/**************************************************** RCC Configuration *********************************************************************/
	/********************************************************************************************************************************************/
	RCC_u8SetClksts(CLK_HSI,STATE_ON);
	RCC_SetSysClk(HSI);
	RCC_voidAHB1EnablePerapheralClock(AHB1_GPIOA);
	RCC_voidAPB2EnablePerapheralClock(APB2_SPI11);
	RCC_voidAHB1EnablePerapheralClock(AHB1_GPIOB);
	RCC_voidAPB1EnablePerapheralClock(APB1_I2C1);
	/********************************************************************************************************************************************/
	/**************************************************** STK Configuration *********************************************************************/
	/********************************************************************************************************************************************/
	MSTK_u8ClockConfig(STK_AHB_DIV_8);
	MSTK_u8SetInterval(2000000, PERIODIC, &AlarmFunc);
	/********************************************************************************************************************************************/
	/**************************************************** SPI Configuration *********************************************************************/
	/********************************************************************************************************************************************/
	GPIO_PinConfig_T MOSI ={ PORTA , PIN7 , ALTER_FUNC , SPEED_LOW , PUSH_PULL , NO_PULL , AF5 };
	GPIO_u8PinInit(&MOSI);
	GPIO_PinConfig_T MISO ={ PORTA , PIN6 , ALTER_FUNC , SPEED_LOW , PUSH_PULL , NO_PULL , AF5 };
	GPIO_u8PinInit(&MISO);
	GPIO_PinConfig_T SCK ={ PORTA , PIN5  , ALTER_FUNC , SPEED_LOW , PUSH_PULL , NO_PULL , AF5 };
	GPIO_u8PinInit(&SCK);
	SPIconfig_t SPI_config ={SPI_1,LEADING_CAPTURE,LEADING_RISING,MASTER,F_CLK_DIV_8,MSB,SELECT_ONE,MANAGMENT_ENABLE,FULL_DUPLEX,FORMAT_8_BIT
				                  ,RX_DMA_DISABLE ,TX_DMA_DISABLE,SS_OUTPUT_DISABLE ,RX_INTERRUPT_MASKED     ,TX_INTERRUPT_MASKED };
	MSPI_u8SetConfiguration(&SPI_config);
	GPIO_PinConfig_T NSS ={PORTA , PIN1 , OUTPUT , SPEED_LOW , PUSH_PULL , NO_PULL , AF0};
	GPIO_u8PinInit(&NSS);
	GPIO_u8SetPinValue(PORTA, PIN1, PIN_HIGH);
	/********************************************************************************************************************************************/
	/**************************************************** RTC Configuration *********************************************************************/
	/********************************************************************************************************************************************/
	HRTC_u8Init();
	/********************************************************************************************************************************************/
	/**************************************************** GPIO-EXTI Configuration ***************************************************************/
	/********************************************************************************************************************************************/
	GPIO_PinConfig_T AlarmNotification ={ PORTA , PIN0 , OUTPUT , SPEED_LOW , PUSH_PULL , NO_PULL , AF0 };
	GPIO_u8PinInit(&AlarmNotification);
	/********************************************************************************************************************************************/
	/**************************************************** 1.1 Login System **********************************************************************/
	/********************************************************************************************************************************************/
	GPIO_u8SetPinValue(PORTA, PIN1, PIN_LOW);
	MSPI_u8SendReceiveSynch(SPI_1,'~',&Local_u8ReceiveTemp);
	GPIO_u8SetPinValue(PORTA, PIN1, PIN_HIGH);

	GPIO_u8SetPinValue(PORTA, PIN1, PIN_LOW);
	MSPI_u8SendReceiveSynch(SPI_1,'!',&Local_u8ReceiveTemp);
	GPIO_u8SetPinValue(PORTA, PIN1, PIN_HIGH);
	/********************************************************************************************************************************************/
	/**************************************************** 2.1 Get Time **************************************************************************/
	/********************************************************************************************************************************************/
	/******************************* Time ********************************/
	HRTC_voidGetCurrentTime(&GetTime);

	GPIO_u8SetPinValue(PORTA, PIN1, PIN_LOW);
	MSPI_u8SendReceiveSynch(SPI_1,'@',&Local_u8ReceiveTemp);
	GPIO_u8SetPinValue(PORTA, PIN1, PIN_HIGH);

	GPIO_u8SetPinValue(PORTA, PIN1, PIN_LOW);
	MSPI_u8TransmitArraySynch(SPI_1,TimeToString(&GetTime));
	GPIO_u8SetPinValue(PORTA, PIN1, PIN_HIGH);
	for (uint32_t Local_u8Counter =0 ; Local_u8Counter<=10000;Local_u8Counter++)
	{
		Local_u8Pulstemp=Local_u8Counter;
	}
	/******************************* Date ********************************/
	HRTC_voidGetCurrentDate(&GetDate);
	GPIO_u8SetPinValue(PORTA, PIN1, PIN_LOW);
	MSPI_u8SendReceiveSynch(SPI_1,'#',&Local_u8ReceiveTemp);
	GPIO_u8SetPinValue(PORTA, PIN1, PIN_HIGH);

	GPIO_u8SetPinValue(PORTA, PIN1, PIN_LOW);
	MSPI_u8TransmitArraySynch(SPI_1,DataToString(&GetDate));
	GPIO_u8SetPinValue(PORTA, PIN1, PIN_HIGH);

	/*********************************************************************/
	/********************************************************************************************************************************************/
	/**************************************************** 2.2 Set Time **************************************************************************/
	/*******************************************************************************************************************************************
	SetDate.day = MONDAY;
	SetDate.date = 28;
	SetDate.month = 8;
	SetDate.year = 23;
	HRTC_voidSetCurrentDate(&SetDate);

	SetTime.hours = 2;
	SetTime.minutes = 25;
	SetTime.seconds = 1;
	SetTime.time_format = _12HRS_PM;
	HRTC_voidSetCurrentTime(&SetTime);*/
	/********************************************************************************************************************************************/
	/**************************************************** 2.2 Set Alarm *************************************************************************/
	/********************************************************************************************************************************************/
	AlarmTime1.hours = 5;
	AlarmTime1.minutes = 30;
	AlarmTime1.seconds = 1;
	AlarmTime1.time_format = _12HRS_AM;
	uint8_t AlarmName1[]="AlarmName1";
/*
	AlarmTime2.hours = 6;
	AlarmTime2.minutes = 32;
	AlarmTime2.seconds = 1;
	AlarmTime2.time_format = _12HRS_AM;
	uint8_t AlarmName2[]="AlarmName2";

	AlarmTime3.hours = 6;
	AlarmTime3.minutes = 32;
	AlarmTime3.seconds = 1;
	AlarmTime3.time_format = _12HRS_AM;
	uint8_t AlarmName3[]="AlarmName3";

	AlarmTime4.hours = 6;
	AlarmTime4.minutes = 32;
	AlarmTime4.seconds = 1;
	AlarmTime4.time_format = _12HRS_AM;
	uint8_t AlarmName4[]="AlarmName4";

	AlarmTime5.hours = 6;
	AlarmTime5.minutes = 32;
	AlarmTime5.seconds = 1;
	AlarmTime5.time_format = _24HRS;
	uint8_t AlarmName5[]="AlarmName3";
	 */
	/********************************************************************************************************************************************/
	/**************************************************** Send Alarm Name ***********************************************************************/
	/********************************************************************************************************************************************/
	GPIO_u8SetPinValue(PORTA, PIN1, PIN_LOW);
	MSPI_u8SendReceiveSynch(SPI_1,'$',&Local_u8ReceiveTemp);
	GPIO_u8SetPinValue(PORTA, PIN1, PIN_HIGH);

	GPIO_u8SetPinValue(PORTA, PIN1, PIN_LOW);
	MSPI_u8TransmitArraySynch(SPI_1,AlarmName1);
	GPIO_u8SetPinValue(PORTA, PIN1, PIN_HIGH);

	GPIO_u8SetPinValue(PORTA, PIN0, PIN_LOW);
	for (uint32_t Local_u8Counter =0 ; Local_u8Counter<=100;Local_u8Counter++)
	{
		Local_u8Pulstemp=Local_u8Counter;
	}
	GPIO_u8SetPinValue(PORTA, PIN0, PIN_HIGH);
	/********************************************************************************************************************************************/
	/**************************************************** Loop **********************************************************************************/
	/********************************************************************************************************************************************/
	for(;;)
	{

	}


}


