/*
 * APP_2_program.c
 *
 *  Created on: 29 Aug 2023
 *      Author: kareem
 */
#include<stdint.h>
/*******************************Libarry************************/
#include"ERROR_STATE.h"
/******************************MCAL****************************/
#include "STK_interface.h"
#include "GPIO_interface.h"
#include "I2C_interface.h"
/******************************HAL******************************/
#include "RTC_interface.h"
#include "RTC_config.h"
/******************************APP*******************************/

#include "APP_2_interface.h"
#include "APP_2_private.h"

#include "APP3_interface.h"

/*****************************************************************************************************
 * Globle Variables
 * ***************************************************************************************************
 */

RTC_DateTime_t APP2_pvCurrentDateTimearry;
static uint8_t APP2_pvAlarmTimeDatearry[NUMBER_OF_ALARMS]={ALARM_NOT_DEFINED};
static RTC_DateTime_t  APP2_AlarmsTimeDateArry[NUMBER_OF_ALARMS];

uint8_t Globla_Alrams_Flags_state = 0;

I2Cconfig_t I2cCinfig;

/*****************************************************************************************************
 * init functions
 * ***************************************************************************************************
 */
/**
 * @fn      APP2_voidInit
 * @brief   Set the callback functions
 * @retval  no return value
 */
void APP2_voidInit(void)
{
	/*pass Systick callback func*/
	MSTK_u8ClockConfig(STK_AHB_DIV_8);
	MSTK_u8SetInterval(SYSTICK_RELOAD_VALUE,PERIODIC,APP2_SysTick_ISR);
}

void APP2_voidWantCurrentDate(RTC_date_t*GetDate)
{
	RTC_DateTime_t temparry;
//	if (NULL!=APP2_pvCurrentDateTimearry)
//	{
//		BinaryToBCD(&APP2_pvCurrentDateTimearry->minutes,&temparry.minutes,6);
//		GetDate->date= (temparry.date);
//		GetDate->month= (temparry.month);
//		GetDate->year=  (temparry.year);
//	}
}
void APP2_voidWantCurrentTime(RTC_time_t*GetTime)
{
	RTC_DateTime_t temparry;
//	if (NULL!=APP2_pvCurrentDateTimearry)
//	{
//		BinaryToBCD(&APP2_pvCurrentDateTimearry->minutes,&temparry.minutes,2);
//		GetTime->hours= (temparry.hours);
//		GetTime->minutes= (temparry.minutes);
//	}
}
/*****************************************************************************************************
 * Time Functions
 * ***************************************************************************************************
 */
/**
 * @fn          APP2_voidReadTime
 * @brief       give the RTC the time and date destination and trigger it to update the time
 * @retval      no return value
 */
void APP2_voidReadDateTime(void)
{
	RTC_date_t Date;
	RTC_time_t Time;

	uint8_t Local_u8Pulstemp;

	HRTC_voidGetCurrentTimeDate(&Time, &Date);

	APP2_pvCurrentDateTimearry.minutes = Time.minutes;
	APP2_pvCurrentDateTimearry.hours = Time.hours;
	APP2_pvCurrentDateTimearry.date = Date.date;
	APP2_pvCurrentDateTimearry.month = Date.month;
	APP2_pvCurrentDateTimearry.year = Date.year;
}

/**
 * @fn          APP2_voidSetTime
 * @brief       set current date and time,and set the RTC time and date
 * @param[in]   Current :pointer to Time and dateo
 * @retval      no return value
 */
void APP2_voidSetTime(APP1_Alarm_T *Current)
{
	RTC_date_t SetDate;
	RTC_time_t SetTime;

	if (Current != NULL)
	{

		SetTime.minutes =Current->Time[1];
		SetTime.hours   =Current->Time[0];
		SetDate.date    =Current->Date[0];
		SetDate.month   =Current->Date[1];
		SetDate.year    =Current->Date[2];

		HRTC_u8Init();
		HRTC_voidSetCurrentTimeDate(&SetTime, &SetDate);


	}
}
/********************************************************************************************************
 * Alarm Functions
 * ******************************************************************************************************
 */
/**
 * @fn          APP2_voidSetAlarm
 * @brief       set alarm time and date
 * @param[in]   alaram :pointer to alarm data (date and time)
 * @param[in]   alarmNumber :pass the the alarm number ons of five alarms[0,1,2,3,4]
 * @retval      No return value 
 */
void APP2_voidSetAlarm(APP1_Alarm_T *alarm,APP2_AlarmNumber_t alarmNumber)
{
	if ((NULL!=alarm)&&(alarmNumber<=APP2_ALARM_5))
	{

		APP2_AlarmsTimeDateArry[alarmNumber].minutes = alarm->Time[1];
		APP2_AlarmsTimeDateArry[alarmNumber].hours   = alarm->Time[0];
		APP2_AlarmsTimeDateArry[alarmNumber].date    = alarm->Date[0];
		APP2_AlarmsTimeDateArry[alarmNumber].month   = alarm->Date[1];
		APP2_AlarmsTimeDateArry[alarmNumber].year    = alarm->Date[2];

//		APP2_AlarmsTimeDateArry[alarmNumber].minutes = BCDToBinary(APP2_AlarmsTimeDateArry[alarmNumber].minutes);
//		APP2_AlarmsTimeDateArry[alarmNumber].hours   = BCDToBinary(APP2_AlarmsTimeDateArry[alarmNumber].hours);
//		APP2_AlarmsTimeDateArry[alarmNumber].date    = BCDToBinary(APP2_AlarmsTimeDateArry[alarmNumber].date );
//		APP2_AlarmsTimeDateArry[alarmNumber].month   = BCDToBinary(APP2_AlarmsTimeDateArry[alarmNumber].month);
//		APP2_AlarmsTimeDateArry[alarmNumber].year    = BCDToBinary(APP2_AlarmsTimeDateArry[alarmNumber].year );

		APP2_pvAlarmTimeDatearry[alarmNumber]=ALAREM_DFINED;
	}
}
/**
 * @fn          APP2_voidAlarmNotification
 * @brief       Comper between the Current Time and Date and Each alarm time and date,if they are squeal rise alram flag
 * @retval      No return value
 */
void APP2_voidAlarmNotification(void)
{
	if ((APP2_pvAlarmTimeDatearry[APP2_ALARM_1]!=ALARM_NOT_DEFINED)
			&&((APP2_pvCurrentDateTimearry.minutes)==(APP2_AlarmsTimeDateArry[APP2_ALARM_1].minutes))
			&&((APP2_pvCurrentDateTimearry.hours)==(APP2_AlarmsTimeDateArry[APP2_ALARM_1].hours))
			&&((APP2_pvCurrentDateTimearry.date)==(APP2_AlarmsTimeDateArry[APP2_ALARM_1].date))
			&&((APP2_pvCurrentDateTimearry.month)==(APP2_AlarmsTimeDateArry[APP2_ALARM_1].month))
			&&((APP2_pvCurrentDateTimearry.year)==(APP2_AlarmsTimeDateArry[APP2_ALARM_1].year)))
	{
		Globla_Alrams_Flags_state |= (1<<APP2_ALARM_1);
		/*Set interrupt && send alarm name to f103 over SPI*/
	}
	else if ((APP2_pvAlarmTimeDatearry[APP2_ALARM_2]!=ALARM_NOT_DEFINED)
			&&((APP2_pvCurrentDateTimearry.minutes)==(APP2_AlarmsTimeDateArry[APP2_ALARM_2].minutes))
			&&((APP2_pvCurrentDateTimearry.hours)==(APP2_AlarmsTimeDateArry[APP2_ALARM_2].hours))
			&&((APP2_pvCurrentDateTimearry.date)==(APP2_AlarmsTimeDateArry[APP2_ALARM_2].date))
			&&((APP2_pvCurrentDateTimearry.month)==(APP2_AlarmsTimeDateArry[APP2_ALARM_2].month))
			&&((APP2_pvCurrentDateTimearry.year)==(APP2_AlarmsTimeDateArry[APP2_ALARM_2].year)))
	{
		Globla_Alrams_Flags_state |=(1<<APP2_ALARM_2);
		/*Set interrupt && send alarm name to f103 over SPI*/
	}
	else if ((APP2_pvAlarmTimeDatearry[APP2_ALARM_3]!=ALARM_NOT_DEFINED)
			&&((APP2_pvCurrentDateTimearry.minutes)==(APP2_AlarmsTimeDateArry[APP2_ALARM_3].minutes))
			&&((APP2_pvCurrentDateTimearry.hours)==(APP2_AlarmsTimeDateArry[APP2_ALARM_3].hours))
			&&((APP2_pvCurrentDateTimearry.date)==(APP2_AlarmsTimeDateArry[APP2_ALARM_3].date))
			&&((APP2_pvCurrentDateTimearry.month)==(APP2_AlarmsTimeDateArry[APP2_ALARM_3].month))
			&&((APP2_pvCurrentDateTimearry.year)==(APP2_AlarmsTimeDateArry[APP2_ALARM_3].year)))
	{
		Globla_Alrams_Flags_state |=(1<<APP2_ALARM_3);
		/*Set interrupt && send alarm name to f103 over SPI*/
	}
	else if ((APP2_pvAlarmTimeDatearry[APP2_ALARM_4]!=ALARM_NOT_DEFINED)
			&&((APP2_pvCurrentDateTimearry.minutes)==(APP2_AlarmsTimeDateArry[APP2_ALARM_4].minutes))
			&&((APP2_pvCurrentDateTimearry.hours)==(APP2_AlarmsTimeDateArry[APP2_ALARM_4].hours))
			&&((APP2_pvCurrentDateTimearry.date)==(APP2_AlarmsTimeDateArry[APP2_ALARM_4].date))
			&&((APP2_pvCurrentDateTimearry.month)==(APP2_AlarmsTimeDateArry[APP2_ALARM_4].month))
			&&((APP2_pvCurrentDateTimearry.year)==(APP2_AlarmsTimeDateArry[APP2_ALARM_4].year)))
	{
		Globla_Alrams_Flags_state |=(1<<APP2_ALARM_4);
		/*Set interrupt && send alarm name to f103 over SPI*/
	}
	else if ((APP2_pvAlarmTimeDatearry[APP2_ALARM_5]!=ALARM_NOT_DEFINED)
			&&((APP2_pvCurrentDateTimearry.minutes)==(APP2_AlarmsTimeDateArry[APP2_ALARM_5].minutes))
			&&((APP2_pvCurrentDateTimearry.hours)==(APP2_AlarmsTimeDateArry[APP2_ALARM_5].hours))
			&&((APP2_pvCurrentDateTimearry.date)==(APP2_AlarmsTimeDateArry[APP2_ALARM_5].date))
			&&((APP2_pvCurrentDateTimearry.month)==(APP2_AlarmsTimeDateArry[APP2_ALARM_5].month))
			&&((APP2_pvCurrentDateTimearry.year)==(APP2_AlarmsTimeDateArry[APP2_ALARM_5].year)))
	{
		Globla_Alrams_Flags_state |=(1<<APP2_ALARM_5);
		/*Set interrupt && send alarm name to f103 over SPI*/
	}
}
/***************************************************************************************************************************************
 * ISR Handler (SysTick,DMA)
 * *************************************************************************************************************************************
 */
void APP2_SysTick_ISR(void)
{
	static uint8_t Local_Static_counter=0;
	if (Local_Static_counter==0)
	{
		APP2_voidReadDateTime();
		Local_Static_counter++;
	}
	else if (Local_Static_counter==1)
	{
		APP2_voidAlarmNotification();
		Local_Static_counter=0;
	}
}
