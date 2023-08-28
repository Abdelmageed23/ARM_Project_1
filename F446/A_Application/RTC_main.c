
/******************************************************************************/
/************************ LIB Layer *******************************************/
/******************************************************************************/
#include <stdint.h>
/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
#include "RCC_INTERFACE.h"
#include "GPIO_INTERFACE.h"
#include "USART_interface.h"

/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
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
uint8_t *DataToString(RTC_data_t *Copy_Data)
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

/***********************************************************************************/
int main(void)
{

	RCC_u8SetClksts(CLK_HSI,STATE_ON);
	RCC_SetSysClk(HSI);
	RCC_voidAHB1EnablePerapheralClock(AHB1_GPIOA);
    /****************************************************************************************************************************************************/
	RCC_voidAHB1EnablePerapheralClock(AHB1_GPIOB);
	RCC_voidAPB1EnablePerapheralClock(APB1_I2C1);
	uint8_t x =0  ;
	RTC_time_t   SetTime,GetTime;
	RTC_data_t   SetDate,GetDate;
	HRTC_u8Init();

	SetDate.day = MONDAY;
	SetDate.date = 28;
	SetDate.month = 8;
	SetDate.year = 23;
	HRTC_voidSetCurrentDate(&SetDate);

	SetTime.hours = 9;
	SetTime.minutes = 47;
	SetTime.seconds = 1;
	SetTime.time_format = _12HRS_AM;
	HRTC_voidSetCurrentTime(&SetTime);


	for(;;)
	{
			HRTC_voidGetCurrentDate(&GetDate);
			HRTC_voidGetCurrentTime(&GetTime);
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
