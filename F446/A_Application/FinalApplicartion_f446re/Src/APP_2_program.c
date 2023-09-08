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
#include "I2C_interface.h"
/******************************HAL******************************/
#include "RTC_interface.h"
#include "RTC_config.h"
/******************************APP*******************************/
#include "USR_interface.h"
#include "APP_2_interface.h"
#include "APP_2_private.h"
/*****************************************************************************************************
 * Globle Variables
 * ***************************************************************************************************
*/

static RTC_DateTime_t* APP2_pvCurrentDateTimearry=NULL;
static uint8_t APP2_pvAlarmTimeDatearry[NUMBER_OF_ALARMS]={ALARM_NOT_DEFINED};
static RTC_DateTime_t  APP2_AlarmsTimeDateArry[NUMBER_OF_ALARMS];

uint8_t Globla_Alrams_Flags_state = 0;

I2Cconfig_t I2cCinfig ={RTC_I2C,SM,SCL_SM_100K,STRETCHING_ENABLE,I2C_MODE,ACK_ENABLE,ENGC_ENABLE};

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
    if (NULL!=APP2_pvCurrentDateTimearry)
    {
        BinaryToBCd(APP2_pvCurrentDateTimearry,&temparry,6);
        GetDate->date= (temparry.date);
        GetDate->month= (temparry.month);
        GetDate->year=  (temparry.year);
    }
}
void APP2_voidWantCurrentTime(RTC_time_t*GetTime)
{
    RTC_DateTime_t temparry;
    if (NULL!=APP2_pvCurrentDateTimearry)
    {
        BinaryToBCd(APP2_pvCurrentDateTimearry,&temparry,2);
        GetTime->hours= (temparry.hours);
        GetTime->minutes= (temparry.minutes);
    }
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
void APP2_voidReadTime(void)
{
    if (NULL!=APP2_pvCurrentDateTimearry)
    {
        HRTC_voidSetDateTime(&I2cCinfig ,APP2_pvCurrentDateTimearry);
    }
}

/**
 * @fn          APP2_voidSetTime
 * @brief       set current date and time,and set the RTC time and date
 * @param[in]   Current :pointer to Time and dateo
 * @retval      no return value
 */
void APP2_voidSetTime(USR_Alarm_T *Current)
{
    if (Current != NULL)
    {
        static RTC_DateTime_t APP2_CurrentTime;

        APP2_CurrentTime.minutes =(Current->Time[1])-'0';
        APP2_CurrentTime.hours   =(Current->Time[0])-'0';
        APP2_CurrentTime.date    =(Current->Date[0])-'0';
        APP2_CurrentTime.month   =(Current->Date[1])-'0';
        APP2_CurrentTime.year    =(Current->Date[2])-'0';
        BCDToBinary(&APP2_CurrentTime,&APP2_CurrentTime,6);
        APP2_pvCurrentDateTimearry = &APP2_CurrentTime;
        HRTC_voidSetDateTime(&I2cCinfig ,APP2_pvCurrentDateTimearry);
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
void APP2_voidSetAlarm(USR_Alarm_T *alarm,APP2_AlarmNumber_t alarmNumber)
{
    if ((NULL!=alarm)&&(alarmNumber<=APP2_ALARM_5))
    {

        APP2_AlarmsTimeDateArry[alarmNumber].minutes =(alarm->Time[1])-'0';
		APP2_AlarmsTimeDateArry[alarmNumber].hours   =(alarm->Time[0])-'0';
		APP2_AlarmsTimeDateArry[alarmNumber].date    =(alarm->Date[0])-'0';
		APP2_AlarmsTimeDateArry[alarmNumber].month   =(alarm->Date[1])-'0';
		APP2_AlarmsTimeDateArry[alarmNumber].year    =(alarm->Date[2])-'0';
        BCDToBinary(&APP2_AlarmsTimeDateArry[alarmNumber],&APP2_AlarmsTimeDateArry[alarmNumber],6);
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
        &&((uint64_t)(*APP2_pvCurrentDateTimearry)==(uint64_t)(APP2_AlarmsTimeDateArry[APP2_ALARM_1])))
    {
    	Globla_Alrams_Flags_state |= (1<<APP2_ALARM_1);
        /*Set interrupt && send alarm name to f103 over SPI*/
    }
    else if ((APP2_pvAlarmTimeDatearry[APP2_ALARM_2]!=ALARM_NOT_DEFINED)
        &&((uint64_t)(*APP2_pvCurrentDateTimearry)==(uint64_t)(APP2_AlarmsTimeDateArry[APP2_ALARM_2])))
    {
    	Globla_Alrams_Flags_state |=(1<<APP2_ALARM_2);
        /*Set interrupt && send alarm name to f103 over SPI*/
    }
    else if ((APP2_pvAlarmTimeDatearry[APP2_ALARM_3]!=ALARM_NOT_DEFINED)
        &&((uint64_t)(*APP2_pvCurrentDateTimearry)==(uint64_t)(APP2_AlarmsTimeDateArry[APP2_ALARM_3])))
    {
    	Globla_Alrams_Flags_state |=(1<<APP2_ALARM_3);
        /*Set interrupt && send alarm name to f103 over SPI*/
    }
    else if ((APP2_pvAlarmTimeDatearry[APP2_ALARM_4]!=ALARM_NOT_DEFINED)
        &&((uint64_t)(*APP2_pvCurrentDateTimearry)==(uint64_t)(APP2_AlarmsTimeDateArry[APP2_ALARM_4])))
    {
    	Globla_Alrams_Flags_state |=(1<<APP2_ALARM_4);
        /*Set interrupt && send alarm name to f103 over SPI*/
    }
    else if ((APP2_pvAlarmTimeDatearry[APP2_ALARM_5]!=ALARM_NOT_DEFINED)
        &&((uint64_t)(*APP2_pvCurrentDateTimearry)==(uint64_t)(APP2_AlarmsTimeDateArry[APP2_ALARM_5])))
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
    static Local_Static_counter=0;
    if (Local_Static_counter==0)
    {
        APP2_voidReadTime();
        Local_Static_counter++;
    }
    else if (Local_Static_counter==1)
    {
        APP2_voidAlarmNotification();
        Local_Static_counter=0;
    }
}
