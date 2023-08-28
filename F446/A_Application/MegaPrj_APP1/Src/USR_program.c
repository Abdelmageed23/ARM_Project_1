/*
 * UserInterface.c
 *
 *  Created on: Aug 26, 2023
 *      Author: Hanin Anwar
 */

#include <stdint.h>
#include "ERROR_STATE.h"

#include "USART_interface.h"

#include "USR_sctipts.h"
#include "USR_private.h"
#include "USR_interface.h"


USR_PassStatus USR_u8ReceivePass(USARTindex_t Copy_u8USART)
{
	uint8_t Local_u8Counter = 0,
			Local_u8CorrectPass[USR_PASS_LENGTH] = USR_CORRECT_PASS,
			Local_u8EnteredPass[USR_PASS_LENGTH];

	USR_PassStatus Local_u8PassStatus = PASS_CORRECT;

	/* Get password from user*/
	MUSART_u8ReceiveArraySynch(Copy_u8USART, Local_u8EnteredPass, USR_PASS_LENGTH);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	/* check password is correct or not*/
	for(Local_u8Counter = 0 ;Local_u8Counter < USR_PASS_LENGTH ;Local_u8Counter++)
	{
		if(Local_u8CorrectPass[Local_u8Counter] != Local_u8EnteredPass[Local_u8Counter])
		{
			Local_u8PassStatus = PASS_NOT_CORRECT;
		}
	}
	return Local_u8PassStatus;
}
void USR_voidSendDashBoard(USARTindex_t Copy_u8USART)
{
	/* Display Dash-board Selection options*/
	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_DashBoardChoose);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_DashBoard1);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_DashBoard2);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_DashBoard3);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_DashBoard4);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);
}

void USR_voidReceiveTimeDate(USARTindex_t Copy_u8USART ,USR_NewDateTime_T *Copy_TimeDateCnfg )
{


	/*Get Date from user*/
	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_NewDate);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_DateTmp);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8ReceiveArraySynch(Copy_u8USART,&Copy_TimeDateCnfg->Date[0], USR_DAY_LENGTH);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_Slash);

	MUSART_u8ReceiveArraySynch(Copy_u8USART, &Copy_TimeDateCnfg->Date[2], USR_MONTH_LENGTH);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_Slash);

	MUSART_u8ReceiveArraySynch(Copy_u8USART,  &Copy_TimeDateCnfg->Date[4], USR_YEAR_LENGTH);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);


	/* Get Time from user*/
	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_NewTime);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_TimeTmp);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8ReceiveArraySynch(Copy_u8USART,  &Copy_TimeDateCnfg->Time[0], USR_HOUR_LENGTH);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_DOT);

	MUSART_u8ReceiveArraySynch(Copy_u8USART,&Copy_TimeDateCnfg->Time[2], USR_MIN_LENGTH);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_DOT);

	MUSART_u8ReceiveArraySynch(Copy_u8USART, &Copy_TimeDateCnfg->Time[4], USR_SEC_LENGTH);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);


}
void USR_u8DisplayAlarms(USARTindex_t Copy_u8USART ,uint8_t Copy_u8AlarmIndex ,uint8_t *Copy_pu8AlarmName)
{
	/* Display ALarms' name */
	MUSART_u8TransmitCharSynch(Copy_u8USART,'\n');
	MUSART_u8TransmitCharSynch(Copy_u8USART,(Copy_u8AlarmIndex+'0'));

	if(*Copy_pu8AlarmName != '\0')
	{
		MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)Copy_pu8AlarmName);
		MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	}
	else
	{
		MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_AlarmNull);
		MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);
	}
}
USR_AlarmSelect USR_u8ReceiveAlarmSelect(USARTindex_t Copy_u8USART)
{
	uint8_t Local_u8Choice;
	USR_AlarmSelect Local_u8AlrmSelct;

	/* Get alarm index */
	MUSART_u8ReceiveCharSynch(Copy_u8USART, &Local_u8Choice);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	Local_u8AlrmSelct = Local_u8Choice-'0';

	return Local_u8AlrmSelct;
}
void USR_voidReceiveAlarmCnfg(USARTindex_t Copy_u8USART ,USR_Alarm_T *Copy_AlarmCnfg)
{
	/*Get Date*/
	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_AlarmDate);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_DateTmp);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8ReceiveArraySynch(Copy_u8USART, &Copy_AlarmCnfg->Date[0], USR_DAY_LENGTH);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_Slash);

	MUSART_u8ReceiveArraySynch(Copy_u8USART, &Copy_AlarmCnfg->Date[2], USR_MONTH_LENGTH);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_Slash);

	MUSART_u8ReceiveArraySynch(Copy_u8USART, &Copy_AlarmCnfg->Date[4], USR_YEAR_LENGTH);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);


	/* Get Time*/
	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_AlarmTime);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_TimeTmp);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8ReceiveArraySynch(Copy_u8USART, &Copy_AlarmCnfg->Time[0], USR_HOUR_LENGTH);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_DOT);

	MUSART_u8ReceiveArraySynch(Copy_u8USART, &Copy_AlarmCnfg->Time[2], USR_MIN_LENGTH);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_DOT);

	MUSART_u8ReceiveArraySynch(Copy_u8USART, &Copy_AlarmCnfg->Time[4], USR_SEC_LENGTH);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);


	/*Get ALarm Name*/
	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_AlarmName);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_NameTmp);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8ReceiveArraySynch(Copy_u8USART, &Copy_AlarmCnfg->Name[0], USR_MAX_NAME_LENGTH);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);
}
