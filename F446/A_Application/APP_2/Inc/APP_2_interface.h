/*
 * APP_2_interface.h
 *
 *  Created on: 29 Aug 2023
 *      Author: kareem
 */

#ifndef APP_2_INTERFACE_H_
#define APP_2_INTERFACE_H_
typedef enum
{
    APP2_FLAG_UNRISED=0,
    APP2_FLAG_RISED
}APP2_alarmFlagState;

typedef enum
{
    APP2_ALARM_1 =0U,
    APP2_ALARM_2,
    APP2_ALARM_3,
    APP2_ALARM_4,
    APP2_ALARM_5,
}APP2_AlarmNumber_t;

void APP2_voidInit(void);
void APP2_voidReadTime(void);
void APP2_voidSetTime(USR_Alarm_T *alarm);
void APP2_voidSetAlarm(USR_Alarm_T* alarm,APP2_AlarmNumber_t alarmNumber);
void APP2_voidAlarmNotification(void);
#endif /* APP_2_INTERFACE_H_ */
