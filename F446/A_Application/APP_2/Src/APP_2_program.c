/*
 * APP_2_program.c
 *
 *  Created on: 29 Aug 2023
 *      Author: kareem
 */
#include<stdint.h>
/*******************************Libarry************************/
#include"../../../D_LIB/ERROR_STATE.h"
/******************************MCAL****************************/
#include "../../../C_MCAL/SysTick/STK_interface.h"
#include "../../../C_MCAL/Inc/I2C_interface.h"
/******************************HAL******************************/
#include"../../../B_HAL/RTC/RTC_interface.h"
/******************************APP*******************************/
#include"../../MegaPrj_APP1/Inc/USR_interface.h"
#include"../inc/APP_2_interface.h"
#include"../inc/APP_2_private.h"
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
    if (NULL!=APP2_pvCurrentDateTimearry)
    {
        GetDate->date= (APP2_pvCurrentDateTimearry->date);
        GetDate->month= (APP2_pvCurrentDateTimearry->month);
        GetDate->year=  (APP2_pvCurrentDateTimearry->year);
    }
}
void APP2_voidWantCurrentTime(RTC_time_t*GetTime)
{
    if (NULL!=APP2_pvCurrentDateTimearry)
    {
        GetTime->hours= (APP2_pvCurrentDateTimearry->hours);
        GetTime->minutes= (APP2_pvCurrentDateTimearry->minutes);
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
        HRTC_voidSetDateTime(I2cCinfig ,APP2_pvCurrentDateTimearry);
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
        static RTC_DateTime_t APP2_CurrentTime=
        {
            .minutes =Current->time[1]-'0',
            .hours   =Current->time[0]-'0',
            .date    =Current->date[0]-'0',
            .month   =Current->date[1]-'0',
            .year    =Current->date[2]-'0',
        };
        BCDToBinary(&APP2_CurrentTime,&APP2_CurrentTime,6);
        APP2_pvCurrentDateTimearry = &APP2_CurrentTime;
        HRTC_voidSetDateTime(I2cCinfig ,APP2_pvCurrentDateTimearry);
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
        APP2_AlarmsTimeDateArry[alarmNumber]=
        {
            .minutes =alarm->time[1]-'0',
            .hours   =alarm->time[0]-'0',
            .date    =alarm->date[0]-'0',
            .month   =alarm->date[1]-'0',
            .year    =alarm->date[2]-'0',
        };
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
        APP2_alarmFlagState |=(1<<APP2_ALARM_1);
        /*Set interrupt && send alarm name to f103 over SPI*/
    }
    else if ((APP2_pvAlarmTimeDatearry[APP2_ALARM_2]!=ALARM_NOT_DEFINED)
        &&((uint64_t)(*APP2_pvCurrentDateTimearry)==(uint64_t)(APP2_AlarmsTimeDateArry[APP2_ALARM_2])))
    {
        APP2_alarmFlagState |=(1<<APP2_ALARM_2);
        /*Set interrupt && send alarm name to f103 over SPI*/
    }
    else if ((APP2_pvAlarmTimeDatearry[APP2_ALARM_3]!=ALARM_NOT_DEFINED)
        &&((uint64_t)(*APP2_pvCurrentDateTimearry)==(uint64_t)(APP2_AlarmsTimeDateArry[APP2_ALARM_3])))
    {
        APP2_alarmFlagState |=(1<<APP2_ALARM_3);
        /*Set interrupt && send alarm name to f103 over SPI*/
    }
    else if ((APP2_pvAlarmTimeDatearry[APP2_ALARM_4]!=ALARM_NOT_DEFINED)
        &&((uint64_t)(*APP2_pvCurrentDateTimearry)==(uint64_t)(APP2_AlarmsTimeDateArry[APP2_ALARM_4])))
    {
        APP2_alarmFlagState |=(1<<APP2_ALARM_4);
        /*Set interrupt && send alarm name to f103 over SPI*/
    }
    else if ((APP2_pvAlarmTimeDatearry[APP2_ALARM_5]!=ALARM_NOT_DEFINED)
        &&((uint64_t)(*APP2_pvCurrentDateTimearry)==(uint64_t)(APP2_AlarmsTimeDateArry[APP2_ALARM_5])))
    {
        APP2_alarmFlagState |=(1<<APP2_ALARM_5);
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
