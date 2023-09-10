/*
 * APP1_interface.h
 *
 *  Created on: Sep 10, 2023
 *      Author: Hanin Anwar
 */

#ifndef APP1_INTERFACE_H_
#define APP1_INTERFACE_H_

#define APP1_MAX_TRIALS				3
#define APP1_MAX_ALRMS				5


#define APP1_DATE_LENGTH				4
#define APP1_TIME_LENGTH				2
#define APP1_MAX_NAME_LENGTH			10

#include "USART_interface.h"
typedef enum
{
	PASS_NOT_CORRECT,
	PASS_CORRECT

}APP1_PassStatus;

typedef enum
{
	CHOICE_DISPLAY	='1',
	CHOICE_SET_TIME	='2',
	CHOICE_SET_ALRM	='3',
	CHOICE_EXIT		='4'

}APP1_Choice;

typedef enum
{
	ALRM1=1,
	ALRM2,
	ALRM3,
	ALRM4,
	ALRM5

}APP1_AlarmSelect;

typedef struct
{
	uint8_t Date[APP1_DATE_LENGTH];
	uint8_t Time[APP1_TIME_LENGTH];
	uint8_t Name[APP1_MAX_NAME_LENGTH];

}APP1_Alarm_T;

void APP1_voidInit(void);

APP1_PassStatus APP1_u8LoginSystem(void);

void APP1_voidFaliedLogin(void);

APP1_Choice APP1_u8DisplayDashBoard(void);

void APP1_voidReceiveTimeDate(APP1_Alarm_T *Copy_TimeDateCnfg);

APP1_AlarmSelect APP1_u8SetAlarmCnfg(APP1_Alarm_T *Copy_pu8AlarmsArr);

void APP1_u8DisplayAlarms(uint8_t Copy_u8AlarmIndex ,uint8_t *Copy_pu8AlarmName);

void APP1_voidReceiveAlarmCnfg(APP1_Alarm_T *Copy_pu8AlarmCnfg);

APP1_AlarmSelect APP1_u8ReceiveAlarmSelect(void);

void APP1_voidTimeIsSet(void);

void APP1_voidAlarmIsSet(void);

void APP1_voidInvalidChoice(void);

void APP1_voidExit(void);

APP1_PassStatus APP1_u8ReceivePass(USARTindex_t Copy_u8USART);

#endif
