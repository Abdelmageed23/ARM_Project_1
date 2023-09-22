
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
/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
#include "RTC_interface.h"
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

static void NumberToString (uint8_t Copy_u8Number , uint8_t* Copy_pu8String )
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
static uint8_t *DataToString(RTC_date_t *Copy_Data)
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
static uint8_t *TimeToString(RTC_time_t *Copy_Time)
{
	static uint8_t Local_Au8String[9];
	NumberToString(Copy_Time->hours  ,&Local_Au8String[0]);
	Local_Au8String[2]=':';
	NumberToString(Copy_Time->minutes,&Local_Au8String[3]);
	Local_Au8String[5]=':';
	Local_Au8String[6]='0';
	Local_Au8String[7]='0';
	Local_Au8String[8]='\0';
	return Local_Au8String;
}
/***********************************************************************************/
int main(void)
{
	RTC_time_t   SetTime,GetTime;
	RTC_date_t   SetDate,GetDate;
    /****************************************************/
	RCC_u8SetClksts(CLK_HSI,STATE_ON);
	RCC_SetSysClk(HSI);
	RCC_voidAHB1EnablePerapheralClock(AHB1_GPIOA);
	RCC_voidAHB1EnablePerapheralClock(AHB1_GPIOB);
	RCC_voidAPB1EnablePerapheralClock(APB1_I2C1);
    /****************************************************/
	HRTC_u8Init();
    /****************************************************/
	SetTime.hours   = 6  ;
	SetTime.minutes = 44 ;
	SetDate.date    = 4  ;
	SetDate.month   = 9  ;
	SetDate.year    = 23 ;
	HRTC_voidSetCurrentTimeDate(&SetTime , &SetDate);
	for(;;)
	{
		    HRTC_voidGetCurrentTimeDate(&GetTime , &GetDate);
			printf("Current Time = %s\n",TimeToString(&GetTime));
			printf("Current Data = %s\n",DataToString(&GetDate));

	}

}
