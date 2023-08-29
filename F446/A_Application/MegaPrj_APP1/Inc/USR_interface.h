/*
 * UserInterface_Script.h
 *
 *  Created on: Aug 26, 2023
 *      Author: Hanin Anwar
 */

#ifndef USR_INTERFACE_H_
#define USR_INTERFACE_H_

#define USR_MAX_TRIALS				3
#define USR_MAX_ALRMS				5


#define USR_DATE_LENGTH				4
#define USR_TIME_LENGTH				2
#define USR_MAX_NAME_LENGTH			10

typedef enum
{
	PASS_NOT_CORRECT,
	PASS_CORRECT

}USR_PassStatus;

typedef enum
{
	CHOICE_DISPLAY	='1',
	CHOICE_SET_TIME	='2',
	CHOICE_SET_ALRM	='3',
	CHOICE_EXIT		='4'

}USR_Choice;

typedef enum
{
	ALRM1=1,
	ALRM2,
	ALRM3,
	ALRM4,
	ALRM5

}USR_AlarmSelect;

typedef struct
{
	uint8_t Date[USR_DATE_LENGTH];
	uint8_t Time[USR_TIME_LENGTH];
	uint8_t Name[USR_MAX_NAME_LENGTH];

}USR_Alarm_T;

//typedef struct
//{
//	uint8_t Date[USR_DATE_LENGTH];
//	uint8_t Time[USR_TIME_LENGTH];
//
//}USR_NewDateTime_T;

USR_PassStatus USR_u8ReceivePass(USARTindex_t Copy_u8USART);

void USR_voidSendDashBoard(USARTindex_t Copy_u8USART);

void USR_voidReceiveTimeDate(USARTindex_t Copy_u8USART ,USR_Alarm_T *Copy_TimeDateCnfg );

void USR_voidReceiveAlarm(USARTindex_t Copy_u8USART ,USR_Alarm_T *Copy_AlarmCnfg);

void USR_u8DisplayAlarms(USARTindex_t Copy_u8USART ,uint8_t Copy_u8AlarmIndex ,uint8_t *Copy_pu8AlarmName);

USR_AlarmSelect USR_u8ReceiveAlarmSelect(USARTindex_t Copy_u8USART);

void USR_voidReceiveAlarmCnfg(USARTindex_t Copy_u8USART ,USR_Alarm_T *Copy_AlarmCnfg);


#endif /* USR_INTERFACE_H_ */
