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
static uint16_t* APP2_pvCurrentTimearry=NULL;
static uint16_t* APP2_pvAlarmTime[NUMBER_OF_ALARMS]={NULL,NULL,NULL,NULL,NULL};
static uint32_t* APP2_pvCurrentDatearry=NULL;
static uint32_t* APP2_pvAlarmDate[NUMBER_OF_ALARMS]={NULL,NULL,NULL,NULL,NULL};

APP2_alarmFlagState APP2_Alarm_1_FlagState = APP2_FLAG_UNRISED;
APP2_alarmFlagState APP2_Alarm_2_FlagState = APP2_FLAG_UNRISED;
APP2_alarmFlagState APP2_Alarm_3_FlagState = APP2_FLAG_UNRISED;
APP2_alarmFlagState APP2_Alarm_4_FlagState = APP2_FLAG_UNRISED;
APP2_alarmFlagState APP2_Alarm_5_FlagState = APP2_FLAG_UNRISED;
/*****************************************************************************************************
 * init functions
 * ***************************************************************************************************
*/
void APP2_voidInit(void)
{
    /*pass DMA callback Func*/

    /*pass Systick callback func*/
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
    HRTC_voidGetCurrentTime(APP2_pvCurrentTimearry);
    HRTC_voidGetCurrentDate(APP2_pvCurrentDatearry);
}
/**
 * @fn          APP2_voidSetTime
 * @brief       set current date and time,and set the RTC time and date
 * @param[in]   alarm :pointer to Time and dateo
 * @retval      no return value
 */
void APP2_voidSetTime(USR_Alarm_T *alarm)
{
    APP2_pvCurrentTimearry=(uint16_t*)(&(alarm->Time));
    APP2_pvCurrentTimearry=(uint32_t*)(&(alarm->Date));
    RTC_time_t RTC_Time=
    {
        .minutes=alarm->Time[1],
        .hours=alarm->Time[0],
    };
    RTC_date_t RTC_Date=
    {
        .date=alarm->Date[0],
        .month=alarm->Date[1],
        .year=alarm->Date[2]
    };
    HRTC_voidSetCurrentTime(&RTC_Time);
    HRTC_voidSetCurrentDate(&RTC_Date);
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
    APP2_pvAlarmTime[alarmNumber]=(uint16_t*)(&(alarm->Time));
    APP2_pvAlarmDate[alarmNumber]=(uint32_t*)(&(alarm->Date));
}
/**
 * @fn          APP2_voidAlarmNotification
 * @brief       Comper between the Current Time and Date and Each alarm time and date,if they are squeal rise alram flag
 * @retval      No return value
*/
void APP2_voidAlarmNotification(void)
{
    if ((APP2_pvAlarmTime[APP2_ALARM_1]!=NULL)  &&(APP2_pvAlarmDate[APP2_ALARM_1]!=NULL)  
        &&((uint16_t)(*APP2_pvCurrentTimearry)==(uint16_t)(*APP2_pvAlarmTime[APP2_ALARM_1]))
        &&((uint32_t)(*APP2_pvCurrentDatearry)==(uint32_t)(*APP2_pvAlarmDate[APP2_ALARM_1])))
    {
        APP2_Alarm_1_FlagState=APP2_FLAG_RISED;
        /*Set interrupt && send alarm name to f103 over SPI*/
    }
    else if ((APP2_pvAlarmTime[APP2_ALARM_2]!=NULL)  &&(APP2_pvAlarmDate[APP2_ALARM_2]!=NULL) 
        &&((uint16_t)(*APP2_pvCurrentTimearry)==(uint16_t)(*APP2_pvAlarmTime[APP2_ALARM_2]))
        &&((uint32_t)(*APP2_pvCurrentDatearry)==(uint32_t)(*APP2_pvAlarmDate[APP2_ALARM_2])))
    {
        APP2_Alarm_2_FlagState=APP2_FLAG_RISED;
        /*Set interrupt && send alarm name to f103 over SPI*/
    }
    else if ((APP2_pvAlarmTime[APP2_ALARM_3]!=NULL)  &&(APP2_pvAlarmDate[APP2_ALARM_3]!=NULL) 
        &&((uint16_t)(*APP2_pvCurrentTimearry)==(uint16_t)(*APP2_pvAlarmTime[APP2_ALARM_3]))
        &&((uint32_t)(*APP2_pvCurrentDatearry)==(uint32_t)(*APP2_pvAlarmDate[APP2_ALARM_3])))
    {
        APP2_Alarm_3_FlagState=APP2_FLAG_RISED;
        /*Set interrupt && send alarm name to f103 over SPI*/
    }
    else if ((APP2_pvAlarmTime[APP2_ALARM_4]!=NULL)  &&(APP2_pvAlarmDate[APP2_ALARM_4]!=NULL) 
        &&((uint16_t)(*APP2_pvCurrentTimearry)==(uint16_t)(*APP2_pvAlarmTime[APP2_ALARM_4]))
        &&((uint32_t)(*APP2_pvCurrentDatearry)==(uint32_t)(*APP2_pvAlarmDate[APP2_ALARM_4])))
    {
        APP2_Alarm_4_FlagState=APP2_FLAG_RISED;
        /*Set interrupt && send alarm name to f103 over SPI*/
    }
    else if ((APP2_pvAlarmTime[APP2_ALARM_5]!=NULL)  &&(APP2_pvAlarmDate[APP2_ALARM_5]!=NULL) 
        &&((uint16_t)(*APP2_pvCurrentTimearry)==(uint16_t)(*APP2_pvAlarmTime[APP2_ALARM_5]))
        &&((uint32_t)(*APP2_pvCurrentDatearry)==(uint32_t)(*APP2_pvAlarmDate[APP2_ALARM_5])))
    {
        APP2_Alarm_5_FlagState=APP2_FLAG_RISED;
        /*Set interrupt && send alarm name to f103 over SPI*/
    }
}
/***************************************************************************************************************************************
 * ISR Handler (SysTick,DMA)
 * *************************************************************************************************************************************
*/

void APP2_SysTick_ISR(void)
{
    static uint8_t Local_u8Counter=1U;
    if (MAX_SYSTICK_OF_COUNT==Local_u8Counter)
    {
        APP2_voidReadTime();
    }
    else
    {
        Local_u8Counter++;
    }
}
void APP2_DMA_ISR(void)
{
    APP2_voidAlarmNotification();
}