
/******************************************************************************/
/************************ LIB Layer *******************************************/
/******************************************************************************/
#include <stdint.h>
#include <stdio.h>
/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
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
uint8_t *DataToString(RTC_date_t *Copy_Date)
{
	static uint8_t Local_Au8String[9];
	NumberToString(Copy_Date->date, &Local_Au8String[0]);
	Local_Au8String[2]='/';
	NumberToString(Copy_Date->month,&Local_Au8String[3]);
	Local_Au8String[5]='/';
	NumberToString(Copy_Date->year ,&Local_Au8String[6]);
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

/***********************************************************************************/
int main(void)
{

	RCC_u8SetClksts(CLK_HSI,STATE_ON);
	RCC_SetSysClk(HSI);
	RCC_voidAHB1EnablePerapheralClock(AHB1_GPIOA);
    /****************************************************************************************************************************************************/
	RCC_voidAHB1EnablePerapheralClock(AHB1_GPIOB);
	RCC_voidAPB1EnablePerapheralClock(APB1_I2C1);

	RCC_voidAHB1EnablePerapheralClock(AHB1_DMA1);


	/*********************************************************************************************/
	GPIO_PinConfig_T sda ={RTC_I2C_PORT , RTC_I2C_SDA_PIN , ALTER_FUNC , SPEED_FAST , OPEN_DRAIN , RTC_I2C_PULL , AF4};
	GPIO_u8PinInit(&sda);
	GPIO_PinConfig_T scl ={RTC_I2C_PORT , RTC_I2C_SCL_PIN , ALTER_FUNC , SPEED_FAST , OPEN_DRAIN , RTC_I2C_PULL , AF4};
	GPIO_u8PinInit(&scl);
	/*********************************************************************************************/

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
			.PriorityLevel = HIGH,
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

	RTC_time_t   SetTime,GetTime;
	RTC_date_t   SetDate,GetDate;
	HRTC_u8Init(&I2cCinfig);




	SetDate.day = MONDAY;
	SetDate.date = 28;
	SetDate.month = 8;
	SetDate.year = 23;
	HRTC_voidSetCurrentDate(&I2cCinfig,&SetDate);

	SetTime.hours = 9;
	SetTime.minutes = 47;
	SetTime.seconds = 1;
	SetTime.time_format = _12HRS_AM;
	HRTC_voidSetCurrentTime(&I2cCinfig,&SetTime);


	for(;;)
	{
			HRTC_voidGetCurrentDate(&I2cCinfig,&GetDate);
			HRTC_voidGetCurrentTime(&I2cCinfig,&GetTime);
			uint8_t *am_or_pm ;
			if ( GetTime.time_format != _24HRS )
			{
				if ( GetTime.time_format == _12HRS_AM )
				{
					am_or_pm="AM";
				}
				else
				{
					am_or_pm="PM";
				}
				printf("Current Time = %s %s\n",TimeToString(&GetTime),am_or_pm);
			}
			else
			{
				printf("Current Time = %s\n",TimeToString(&GetTime));
			}
			printf("Current Data = %s <%s>\n",DataToString(&GetDate),GetDay(GetDate.day) );



	}

}
