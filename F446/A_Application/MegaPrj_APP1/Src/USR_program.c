/*
 * UserInterface.c
 *
 *  Created on: Aug 26, 2023
 *      Author: Hanin Anwar
 */

#include <stdint.h>
#include "USART_interface.h"

#include "USR_sctipts.h"
#include "USR_interface.h"

void USR_voidSendWelcome(USARTindex_t Copy_u8USART)
{
	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_Welcome);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_EnterPass);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

}

void USR_voidSendWrongPass(USARTindex_t Copy_u8USART)
{
	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_WrongPass);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

}
void USR_voidSendLoginFailed(USARTindex_t Copy_u8USART)
{
	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_TrailFailed);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

}

USR_PassStatus USR_u8ReceivePass(USARTindex_t Copy_u8USART)
{
	uint8_t Local_u8Counter = 0,
			Local_u8CorrectPass[USR_PASS_LENGTH] = USR_CORRECT_PASS,
			Local_u8EnteredPass[USR_PASS_LENGTH];

	USR_PassStatus Local_u8PassStatus = PASS_CORRECT;


	MUSART_u8ReceiveArraySynch(Copy_u8USART, Local_u8EnteredPass, USR_PASS_LENGTH);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

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
	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_DashBoardChoose);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_DashBoard1);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_DashBoard2);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_DashBoard3);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

}

void USR_voidReceiveTimeDate(USARTindex_t Copy_u8USART ,uint8_t *Copy_pu8Date ,uint8_t *Copy_pu8Time )
{


	/*Get Date*/
	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_EnterDate);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_DateTmp);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8ReceiveArraySynch(Copy_u8USART, &Copy_pu8Date[0], USR_DAY_LENGTH);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_Slash);

	MUSART_u8ReceiveArraySynch(Copy_u8USART, &Copy_pu8Date[2], USR_MONTH_LENGTH);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_Slash);

	MUSART_u8ReceiveArraySynch(Copy_u8USART, &Copy_pu8Date[4], USR_YEAR_LENGTH);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);


	/* Get Time*/
	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_EnterTime);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8TransmitArraySynch(Copy_u8USART,(uint8_t *)USR_Script_TimeTmp);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);

	MUSART_u8ReceiveArraySynch(Copy_u8USART, &Copy_pu8Time[0], USR_HOUR_LENGTH);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_DOT);

	MUSART_u8ReceiveArraySynch(Copy_u8USART, &Copy_pu8Time[2], USR_MIN_LENGTH);
	MUSART_u8TransmitCharSynch(Copy_u8USART,USR_Script_NewLine);
}
