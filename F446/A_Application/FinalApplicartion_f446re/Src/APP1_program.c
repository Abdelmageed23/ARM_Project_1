/*
 * APP1_program.c
 *
 *  Created on: Sep 10, 2023
 *      Author: Hanin Anwar
 */

#include <stdint.h>
#include "USART_interface.h"
#include "GPIO_interface.h"

#include "APP1_sctipts.h"

#include "APP1_interface.h"
#include "APP1_private.h"

USARTconfig_t APP1_USART_Cnfg;

void APP1_voidInit(void)
{

	/*********************	GPIO Pins configurations ***********************/
	GPIO_PinConfig_T USARTPinRX =
	{
			.AltFunc = AF7,
			.Mode = ALTER_FUNC,
			.PinNum = PIN2,
			.Port = PORTA,
			.PullType = PUSH_PULL,
			.Speed = SPEED_LOW
	};

	GPIO_PinConfig_T USARTPinTX =
	{
			.AltFunc = AF7,
			.Mode = ALTER_FUNC,
			.PinNum = PIN3,
			.Port = PORTA,
			.PullType = PUSH_PULL,
			.Speed = SPEED_LOW
	};
	/*********************	USART configuration	*************************/

	APP1_USART_Cnfg.DMAresevier = DMAR_DISABLE;
	APP1_USART_Cnfg.DMAtransmitter = DMAT_DISABLE;
	APP1_USART_Cnfg.ErrorTnterrupt = INHIBITED;
	APP1_USART_Cnfg.OverSampling = BY_16;
	APP1_USART_Cnfg.ParityControl = PARITY_CONTROL_DISABLE;
	APP1_USART_Cnfg.RXNEinterrupt = RXNE_INTERRUPT_DISABLE;
	APP1_USART_Cnfg.Receiver = RECEIVER_ENABLE;
	APP1_USART_Cnfg.StopBit_t = ONE_BIT;
	APP1_USART_Cnfg.TXEinterrupt = TXE_INTERRUPT_DISABLE;
	APP1_USART_Cnfg.TransmetCompleteInterrupt = TRANSMITTER_COMPLETE_INTERRUPT_DISABLE;
	APP1_USART_Cnfg.Transmitter = TRANSMITTER_ENABLE;
	APP1_USART_Cnfg.USARTindex = USART_2;
	APP1_USART_Cnfg.WordLength = DATA_8_BITS;
	APP1_USART_Cnfg.ParitySelection = PARITY_SELECTION_EVEN;


	/***********************	MCAL Initialization ***********************/
	MUSART_u8SetConfiguration(&APP1_USART_Cnfg);
	GPIO_u8PinInit(&USARTPinRX);
	GPIO_u8PinInit(&USARTPinTX);
}

APP1_PassStatus APP1_u8LoginSystem(void)
{
	uint8_t Local_u8Trials=0;

	APP1_PassStatus Local_u8PassFlag;

	/* Welcome */
	MUSART_u8TransmitArraySynch(APP1_USART_Cnfg.USARTindex,(uint8_t *)APP1_Script_Welcome);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);

	MUSART_u8TransmitArraySynch(APP1_USART_Cnfg.USARTindex,(uint8_t *)APP1_Script_EnterPass);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);

	do
	{
		if(Local_u8Trials != 0)
		{
			/* Wrong Password*/
			MUSART_u8TransmitArraySynch(APP1_USART_Cnfg.USARTindex,(uint8_t *)APP1_Script_WrongPass);
			MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);
		}
		/* Check password*/
		Local_u8PassFlag = APP1_u8ReceivePass(APP1_USART_Cnfg.USARTindex);
		Local_u8Trials++;
	}
	while((Local_u8PassFlag == PASS_NOT_CORRECT) && (Local_u8Trials < APP1_MAX_TRIALS));

	return Local_u8PassFlag;
}


void APP1_voidFaliedLogin(void)
{
	/*Login Failed*/
	MUSART_u8TransmitArraySynch(APP1_USART_Cnfg.USARTindex,(uint8_t *)APP1_Script_TrailFailed);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);
}

void APP1_voidTimeIsSet(void)
{
	MUSART_u8TransmitArraySynch(APP1_USART_Cnfg.USARTindex,(uint8_t *)APP1_Script_DateUpd);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);
}

APP1_Choice APP1_u8DisplayDashBoard(void)
{
	APP1_Choice Local_u8Choice;

	/* Display Dash-board Selection options*/
	MUSART_u8TransmitArraySynch(APP1_USART_Cnfg.USARTindex,(uint8_t *)APP1_Script_DashBoardChoose);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);

	MUSART_u8TransmitArraySynch(APP1_USART_Cnfg.USARTindex,(uint8_t *)APP1_Script_DashBoard1);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);

	MUSART_u8TransmitArraySynch(APP1_USART_Cnfg.USARTindex,(uint8_t *)APP1_Script_DashBoard2);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);

	MUSART_u8TransmitArraySynch(APP1_USART_Cnfg.USARTindex,(uint8_t *)APP1_Script_DashBoard3);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);

	MUSART_u8TransmitArraySynch(APP1_USART_Cnfg.USARTindex,(uint8_t *)APP1_Script_DashBoard4);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);

	MUSART_u8ReceiveCharSynch(APP1_USART_Cnfg.USARTindex, &Local_u8Choice);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);

	return Local_u8Choice;
}

void APP1_voidReceiveTimeDate(APP1_Alarm_T *Copy_TimeDateCnfg)
{
	uint8_t Local_u8RecVal[APP1_DATE_LENGTH];

	/*Get Date*/
	MUSART_u8TransmitArraySynch(APP1_USART_Cnfg.USARTindex,(uint8_t *)APP1_Script_AlarmDate);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);

	MUSART_u8TransmitArraySynch(APP1_USART_Cnfg.USARTindex,(uint8_t *)APP1_Script_DateTmp);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);

	MUSART_u8ReceiveArraySynch(APP1_USART_Cnfg.USARTindex, &Local_u8RecVal[0], APP1_DAY_LENGTH);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_Slash);

	Copy_TimeDateCnfg->Date[0] = (Local_u8RecVal[0]-'0')*10 + (Local_u8RecVal[1]-'0');

	MUSART_u8ReceiveArraySynch(APP1_USART_Cnfg.USARTindex, &Local_u8RecVal[0], APP1_MONTH_LENGTH);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_Slash);

	Copy_TimeDateCnfg->Date[1] = (Local_u8RecVal[0]-'0')*10 + (Local_u8RecVal[1]-'0');

	MUSART_u8ReceiveArraySynch(APP1_USART_Cnfg.USARTindex, &Local_u8RecVal[0], APP1_YEAR_LENGTH);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);

	Copy_TimeDateCnfg->Date[2] = (Local_u8RecVal[2]-'0')*10 + (Local_u8RecVal[3]-'0');


	/* Get Time*/
	MUSART_u8TransmitArraySynch(APP1_USART_Cnfg.USARTindex,(uint8_t *)APP1_Script_AlarmTime);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);

	MUSART_u8TransmitArraySynch(APP1_USART_Cnfg.USARTindex,(uint8_t *)APP1_Script_TimeTmp);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);

	MUSART_u8ReceiveArraySynch(APP1_USART_Cnfg.USARTindex, &Local_u8RecVal[0], APP1_HOUR_LENGTH);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_DOT);

	MUSART_u8ReceiveArraySynch(APP1_USART_Cnfg.USARTindex, &Local_u8RecVal[2], APP1_MIN_LENGTH);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);


	Copy_TimeDateCnfg->Time[0] = (Local_u8RecVal[0]-'0')*10 + (Local_u8RecVal[1]-'0');
	Copy_TimeDateCnfg->Time[1] = (Local_u8RecVal[2]-'0')*10 + (Local_u8RecVal[3]-'0');

}

APP1_AlarmSelect APP1_u8SetAlarmCnfg(APP1_Alarm_T *Copy_pu8AlarmsArr)
{
	uint8_t Local_u8Counter;
	APP1_AlarmSelect Local_u8AlrmSelect;

	for(Local_u8Counter = 0 ;Local_u8Counter < APP1_MAX_ALRMS ;Local_u8Counter++)
	{
		/* Display Alarms board */
		APP1_u8DisplayAlarms((Local_u8Counter+1),(uint8_t *)(&(Copy_pu8AlarmsArr[Local_u8Counter].Name)));
	}

	/*Select alarm */
	Local_u8AlrmSelect = APP1_u8ReceiveAlarmSelect();

	/* Set alarm configuration*/
	APP1_voidReceiveAlarmCnfg((&Copy_pu8AlarmsArr[Local_u8AlrmSelect-1]));

	return Local_u8AlrmSelect;
}

void APP1_voidReceiveAlarmCnfg(APP1_Alarm_T *Copy_pu8AlarmCnfg)
{
	/* Get date & Time from user*/
	APP1_voidReceiveTimeDate(Copy_pu8AlarmCnfg);

	/*Get ALarm Name*/
	MUSART_u8TransmitArraySynch(APP1_USART_Cnfg.USARTindex,(uint8_t *)APP1_Script_AlarmName);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);

	MUSART_u8TransmitArraySynch(APP1_USART_Cnfg.USARTindex,(uint8_t *)APP1_Script_NameTmp);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);

	MUSART_u8ReceiveArraySynch(APP1_USART_Cnfg.USARTindex, &Copy_pu8AlarmCnfg->Name[0], APP1_MAX_NAME_LENGTH);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);
}

void APP1_u8DisplayAlarms(uint8_t Copy_u8AlarmIndex ,uint8_t *Copy_pu8AlarmName)
{
	/* Display ALarms' name */
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,'\n');
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,(Copy_u8AlarmIndex+'0'));

	if(*Copy_pu8AlarmName != '\0')
	{
		MUSART_u8TransmitArraySynch(APP1_USART_Cnfg.USARTindex,(uint8_t *)Copy_pu8AlarmName);
		MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);

	}
	else
	{
		MUSART_u8TransmitArraySynch(APP1_USART_Cnfg.USARTindex,(uint8_t *)APP1_Script_AlarmNull);
		MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);
	}
}
APP1_AlarmSelect APP1_u8ReceiveAlarmSelect(void)
{
	uint8_t Local_u8Choice;
	APP1_AlarmSelect Local_u8AlrmSelct;

	/* Get alarm index */
	MUSART_u8ReceiveCharSynch(APP1_USART_Cnfg.USARTindex, &Local_u8Choice);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);

	Local_u8AlrmSelct = Local_u8Choice-'0';

	return Local_u8AlrmSelct;
}

void APP1_voidAlarmIsSet(void)
{
	MUSART_u8TransmitArraySynch(APP1_USART_Cnfg.USARTindex,(uint8_t *)APP1_Script_AlarmSet);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);

}
void APP1_voidExit(void)
{
	MUSART_u8TransmitArraySynch(APP1_USART_Cnfg.USARTindex,(uint8_t *)APP1_Script_Exit);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);
}
void APP1_voidInvalidChoice(void)
{
	MUSART_u8TransmitArraySynch(APP1_USART_Cnfg.USARTindex,(uint8_t *)APP1_Script_Invalid);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);
}
APP1_PassStatus APP1_u8ReceivePass(USARTindex_t APP1)
{
	uint8_t Local_u8Counter = 0,
			Local_u8CorrectPass[APP1_PASS_LENGTH] = APP1_CORRECT_PASS,
			Local_u8EnteredPass[APP1_PASS_LENGTH];

	APP1_PassStatus Local_u8PassStatus = PASS_CORRECT;

	/* Get password from user*/
	MUSART_u8ReceiveArraySynch(APP1_USART_Cnfg.USARTindex, Local_u8EnteredPass, APP1_PASS_LENGTH);
	MUSART_u8TransmitCharSynch(APP1_USART_Cnfg.USARTindex,APP1_Script_NewLine);

	/* check password is correct or not*/
	for(Local_u8Counter = 0 ;Local_u8Counter < APP1_PASS_LENGTH ;Local_u8Counter++)
	{
		if(Local_u8CorrectPass[Local_u8Counter] != Local_u8EnteredPass[Local_u8Counter])
		{
			Local_u8PassStatus = PASS_NOT_CORRECT;
		}
	}
	return Local_u8PassStatus;
}
