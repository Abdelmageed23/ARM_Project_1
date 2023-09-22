///*
// * UserInterface.c
// *
// *  Created on: Aug 26, 2023
// *      Author: Hanin Anwar
// */
//
//#include <APP1_sctipts.h>
//#include <stdint.h>
//#include "ERROR_STATE.h"
//
//#include "USART_interface.h"
//
//#include "USR_private.h"
//#include "USR_interface.h"
//
//
//
//void USR_voidSendDashBoard(USARTindex_t Copy_u8USART)
//{
//	/* Display Dash-board Selection options*/
//	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_DashBoardChoose);
//	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);
//
//	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_DashBoard1);
//	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);
//
//	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_DashBoard2);
//	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);
//
//	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_DashBoard3);
//	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);
//
//	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_DashBoard4);
//	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);
//}
//
//void USR_voidReceiveTimeDate(USARTindex_t Copy_u8USART ,USR_Alarm_T *Copy_TimeDateCnfg )
//{
//
//	uint8_t Local_u8RecVal[USR_DATE_LENGTH];
//
//	/*Get Date*/
//	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_AlarmDate);
//	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);
//
//	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_DateTmp);
//	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);
//
//	MUSART_u8ReceiveArraySynch(Copy_u8USART, &Local_u8RecVal[0], USR_DAY_LENGTH);
//	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_Slash);
//
//	Copy_TimeDateCnfg->Date[0] = (Local_u8RecVal[0]-'0')*10 + (Local_u8RecVal[1]-'0');
//
//	MUSART_u8ReceiveArraySynch(Copy_u8USART, &Local_u8RecVal[0], USR_MONTH_LENGTH);
//	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_Slash);
//
//	Copy_TimeDateCnfg->Date[1] = (Local_u8RecVal[0]-'0')*10 + (Local_u8RecVal[1]-'0');
//
//	MUSART_u8ReceiveArraySynch(Copy_u8USART, &Local_u8RecVal[0], USR_YEAR_LENGTH);
//	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);
//
//	Copy_TimeDateCnfg->Date[2] = (Local_u8RecVal[2]-'0')*10 + (Local_u8RecVal[3]-'0');
//
//
//	/* Get Time*/
//	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_AlarmTime);
//	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);
//
//	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_TimeTmp);
//	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);
//
//	MUSART_u8ReceiveArraySynch(Copy_u8USART, &Local_u8RecVal[0], USR_HOUR_LENGTH);
//	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_DOT);
//
//	MUSART_u8ReceiveArraySynch(Copy_u8USART, &Local_u8RecVal[2], USR_MIN_LENGTH);
//	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);
//
//
//	Copy_TimeDateCnfg->Time[0] = (Local_u8RecVal[0]-'0')*10 + (Local_u8RecVal[1]-'0');
//	Copy_TimeDateCnfg->Time[1] = (Local_u8RecVal[2]-'0')*10 + (Local_u8RecVal[3]-'0');
//
//}
//void USR_u8DisplayAlarms(USARTindex_t Copy_u8USART ,uint8_t Copy_u8AlarmIndex ,uint8_t *Copy_pu8AlarmName)
//{
//	/* Display ALarms' name */
//	MUSART_u8TransmitCharSynch(Copy_u8USART,'\n');
//	MUSART_u8TransmitCharSynch(Copy_u8USART,(Copy_u8AlarmIndex+'0'));
//
//	if(*Copy_pu8AlarmName != '\0')
//	{
//		MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)Copy_pu8AlarmName);
//		MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);
//
//	}
//	else
//	{
//		MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_AlarmNull);
//		MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);
//	}
//}
//USR_AlarmSelect USR_u8ReceiveAlarmSelect(USARTindex_t Copy_u8USART)
//{
//	uint8_t Local_u8Choice;
//	USR_AlarmSelect Local_u8AlrmSelct;
//
//	/* Get alarm index */
//	MUSART_u8ReceiveCharSynch(Copy_u8USART, &Local_u8Choice);
//	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);
//
//	Local_u8AlrmSelct = Local_u8Choice-'0';
//
//	return Local_u8AlrmSelct;
//}
//void USR_voidReceiveAlarmCnfg(USARTindex_t Copy_u8USART ,USR_Alarm_T *Copy_AlarmCnfg)
//{
//
//	/* Get date & Time from user*/
//	USR_voidReceiveTimeDate(Copy_u8USART, Copy_AlarmCnfg);
//
//	/*Get ALarm Name*/
//	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_AlarmName);
//	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);
//
//	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_NameTmp);
//	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);
//
//	MUSART_u8ReceiveArraySynch(Copy_u8USART, &Copy_AlarmCnfg->Name[0], USR_MAX_NAME_LENGTH);
//	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);
//}
