
/******************************************************************************/
/************************ LIB Layer *******************************************/
/******************************************************************************/
#include <stdint.h>
#include <stdio.h>
/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
#include "STM32F446xx.h"

#include "RCC_INTERFACE.h"
#include "GPIO_INTERFACE.h"
#include "DMA_interface.h"
#include "I2C_interface.h"
#include "NVIC_interface.h"

/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
#include "RTC_config.h"
#include "RTC_private.h"
#include "RTC_interface.h"
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
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
//uint8_t *DataToString(RTC_date_t *Copy_Date)
//{
//	static uint8_t Local_Au8String[9];
//	NumberToString(Copy_Date->date, &Local_Au8String[0]);
//	Local_Au8String[2]='/';
//	NumberToString(Copy_Date->month,&Local_Au8String[3]);
//	Local_Au8String[5]='/';
//	NumberToString(Copy_Date->year ,&Local_Au8String[6]);
//	Local_Au8String[8]='\0';
//	return Local_Au8String;
//}
//uint8_t *TimeToString(RTC_time_t *Copy_Time)
//{
//	static uint8_t Local_Au8String[9];
//	NumberToString(Copy_Time->hours  ,&Local_Au8String[0]);
//	Local_Au8String[2]=':';
//	NumberToString(Copy_Time->minutes,&Local_Au8String[3]);
//	Local_Au8String[5]=':';
//	NumberToString(Copy_Time->seconds,&Local_Au8String[6]);
//	Local_Au8String[8]='\0';
//	return Local_Au8String;
//}
//char *GetDay(uint8_t Copy_DayIndex)
//{
//	char * Local_Au8Days[]={ "SUNDAY","MONDAY","TUESDAY","WEDNESDAY","THURSDAY","FRIDAY", "SATURDAY" };
//	return Local_Au8Days[Copy_DayIndex-1];
//}

/***********************************************************************************/
int main(void)
{

	RCC_u8SetClksts(CLK_HSI,STATE_ON);
	RCC_SetSysClk(HSI);
	RCC_voidAHB1EnablePerapheralClock(AHB1_GPIOA);
	/****************************************************************************************************************************************************/
	RCC_voidAHB1EnablePerapheralClock(AHB1_GPIOB);

	RCC_voidAHB1EnablePerapheralClock(AHB1_DMA1);


	/*********************************************************************************************/
	GPIO_PinConfig_T sda ={RTC_I2C_PORT , RTC_I2C_SDA_PIN , ALTER_FUNC , SPEED_FAST , OPEN_DRAIN , RTC_I2C_PULL , AF4};
	GPIO_u8PinInit(&sda);
	GPIO_PinConfig_T scl ={RTC_I2C_PORT , RTC_I2C_SCL_PIN , ALTER_FUNC , SPEED_FAST , OPEN_DRAIN , RTC_I2C_PULL , AF4};
	GPIO_u8PinInit(&scl);

	GPIO_u8SetPinValue(sda.Port, sda.PinNum, PIN_HIGH);
	GPIO_u8SetPinValue(scl.Port, scl.PinNum, PIN_HIGH);

	/*********************************************************************************************/

	RCC_voidAPB1EnablePerapheralClock(APB1_I2C1);


	I2Cconfig_t I2cCinfig ={RTC_I2C,SM,SCL_SM_100K,STRETCHING_ENABLE,I2C_MODE,ACK_ENABLE,ENGC_ENABLE};

	DMA_Cnfg_T I2C_DMA_Rx =
	{
			.CallBackFunc = &MI2C_u8ACallbackRx,
			.ChannelNum = CHANNEL1,
			.DMA_Type = DMA_1,
			.InterruptType = FULL_TRANS,
			.MemIncMode = INCREMENT,
			.MemIncSize = BYTE,
			.PerIncMode = FIXED,
			.PerIncSize = BYTE,
			.PriorityLevel = HIGH,
			.SrcDestMode = PERIPH_TO_MEM,
			.StreamNum = STREAM0,
			.TransferMode = DIRECT_MODE
	};

	DMA_Cnfg_T I2C_DMA_Tx =
	{
			.CallBackFunc = &MI2C_u8ACallbackTx,
			.ChannelNum = CHANNEL1,
			.DMA_Type = DMA_1,
			.InterruptType = FULL_TRANS,
			.MemIncMode = INCREMENT,
			.MemIncSize = BYTE,
			.PerIncMode = FIXED,
			.PerIncSize = BYTE,
			.PriorityLevel = VERY_HIGH,
			.SrcDestMode = MEM_TO_PERIPH,
			.StreamNum = STREAM7,
			.TransferMode = DIRECT_MODE
	};


	I2cCinfig.DMA_Rx = I2C_DMA_Rx;
	I2cCinfig.DMA_Tx = I2C_DMA_Tx;

	DMA_u8Init(&I2C_DMA_Tx);
	DMA_u8Init(&I2C_DMA_Rx);

	MI2C_u8SetConfiguration(&I2cCinfig);

	MNVIC_u8EnableInterrupt(NVIC_DMA1_Stream0);
	MNVIC_u8EnableInterrupt(NVIC_DMA1_Stream7);

	RTC_DateTime_t SetNewDateTime =
	{
			.day = MONDAY,
			.date = 4,
			.month = 9,
			.year = 23,
			.minutes = 44,
			.hours = 6,
	};
	RTC_DateTime_t GetBcd,GetDateTime;

	HRTC_u8Init(&I2cCinfig);

	HRTC_voidSetDateTime(&I2cCinfig, &SetNewDateTime);


	HRTC_voidGetDateTime(&I2cCinfig, &GetBcd);


	for(;;)
	{

		BCDToBinary(&GetBcd.minutes,&GetDateTime.minutes, 6);

	}

}
