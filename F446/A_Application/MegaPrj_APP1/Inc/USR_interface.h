/*
 * UserInterface_Script.h
 *
 *  Created on: Aug 26, 2023
 *      Author: Hanin Anwar
 */

#ifndef USR_INTERFACE_H_
#define USR_INTERFACE_H_

#define USR_PASS_LENGTH				4
#define USR_CORRECT_PASS			{'1','2','3','4'}
#define USR_MAX_TRIALS				3

#define USR_DATE_LENGTH				8
#define USR_TIME_LENGTH				4

#define USR_DAY_LENGTH				2
#define USR_MONTH_LENGTH			2
#define USR_YEAR_LENGTH				4

#define USR_HOUR_LENGTH				2
#define USR_MIN_LENGTH				2

typedef enum
{
	PASS_NOT_CORRECT,
	PASS_CORRECT

}USR_PassStatus;

typedef enum
{
	CHOICE_DISPLAY	='1',
	CHOICE_SET_TIME	='2',
	CHOICE_SET_ALRM	='3'

}USR_Choice_T;

USR_PassStatus USR_u8ReceivePass(USARTindex_t Copy_u8USART);
void USR_voidSendWelcome(USARTindex_t Copy_u8USART);
void USR_voidSendWrongPass(USARTindex_t Copy_u8USART);
void USR_voidSendLoginFailed(USARTindex_t Copy_u8USART);
void USR_voidSendDashBoard(USARTindex_t Copy_u8USART);
void USR_voidReceiveTimeDate(USARTindex_t Copy_u8USART ,uint8_t *Copy_pu8Date ,uint8_t *Copy_pu8Time );
#endif /* USR_INTERFACE_H_ */
