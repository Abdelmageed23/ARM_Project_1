/****************************************************************************/
/*
 * @file 		GPIO_program.c
 * @author		Hanin Anwar
 * @brief		the GPIO main source file, including functions' definitions
 *
 * */

#include <stdint.h>

#include "../Inc/STATUS.h"

#include "../Inc/STM32F103xx.h"
#include "../Inc/GPIO_private.h"
#include "../Inc/GPIO_interface.h"

static GPIO_RegDef_T *GPIOPort[GPIO_PERIPHERAL_NUM] = {GPIOA ,GPIOB ,GPIOC };

/****************************************************************************/
/*
 * @fn 			GPIO_u8PinInit
 * @brief 		the function initializes the GPIO pin according to the input parameters
 * @param[in]	PinConfig : the initialization values of the pin
 * @retval		ErrorStatus
 * */
uint8_t GPIO_u8PinInit(const GPIO_PinConfig_T *PinConfig)
{
	uint8_t Local_u8ErrorState = OK,
			Local_u8RegNum,
			Local_u8ModeBitNum,
			Local_u8ConfBitNum;

	/*Check pointer is not NULL*/
	if(PinConfig != NULL)
	{


		/*1. Set Pin Mode : Input , Output, Speed : 2MHZ,10MHZ,50MHZ*/
		Local_u8RegNum = (PinConfig->PinNum)/CLR_DIV_REM;
		Local_u8ModeBitNum = ((PinConfig->PinNum)%CLR_DIV_REM)*CLR_MODE_PIN_ACCESS;

		GPIOPort[PinConfig->Port]->CR[Local_u8RegNum] &= ~(CLR_MODE_SHIFT << Local_u8ModeBitNum);
		GPIOPort[PinConfig->Port]->CR[Local_u8RegNum] |=  (PinConfig->Mode << Local_u8ModeBitNum);

		/*2. Set Configuration Of Pin : Input : Analog,Floating,Input with PullUp/DN
		 * 								Output: GO PushPull , GO Open Drain , AF PushPull , AF Open Drain*/
		Local_u8ConfBitNum = ((PinConfig->PinNum)%CLR_DIV_REM)*CLR_MODE_PIN_ACCESS+CLR_CNF_PIN_ACCESS;
		GPIOPort[PinConfig->Port]->CR[Local_u8RegNum] &= ~(CLR_MODE_SHIFT << Local_u8ConfBitNum);
		GPIOPort[PinConfig->Port]->CR[Local_u8RegNum] |= (PinConfig->InputOutConfig << Local_u8ConfBitNum);

		/*3. Set PullUp & PullDn*/
		if(PinConfig->Mode == INPUT)
		{
			GPIOPort[PinConfig->Port]->ODR &= ~(ODR_MASK << PinConfig->PinNum  );
			GPIOPort[PinConfig->Port]->ODR |=  (PinConfig->PullType << PinConfig->PinNum  );
		}

	}
	else
	{
		Local_u8ErrorState = NULL_PTR;
	}
	return Local_u8ErrorState;

}

/****************************************************************************/
/*
 * @fn 			GPIO_u8SetPinValue
 * @brief 		the function set the GPIO pin according to the input value
 * @param[in]	Port : the port number, get options @Port_T enum
 * @param[in]	PinNum : the pin number ,get options @Pin_T enum
 * @param[in]	PinValue : the output value ,get options @PinVal_T
 * @retval		ErrorStatus
 * */
uint8_t GPIO_u8SetPinValue(Port_T Port , Pin_T PinNum , PinVal_T PinValue)
{
	uint8_t  Local_u8ErrorState = OK;

	/*Check Valid Inputs Configuration*/
	if((Port <= PORTC) && (PinNum <= PIN15)
			&& (PinValue <= PIN_HIGH))
	{
		(GPIOPort[Port])->ODR &= ~(ODR_MASK << PinNum);
		(GPIOPort[Port])->ODR |= (PinValue << PinNum);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}

/****************************************************************************/
/*
 * @fn 			GPIO_u8TogglePinValue
 * @brief 		the function toggle the GPIO pin
 * @param[in]	Port : the port number, get options @Port_T enum
 * @param[in]	PinNum : the pin number ,get options @Pin_T enum
 * @retval		ErrorStatus
 * */
uint8_t GPIO_u8TogglePinValue(Port_T Port , Pin_T PinNum)
{
	uint8_t  Local_u8ErrorState = OK;

	/*Check Valid Inputs Configuration*/
	if((Port <= PORTC) && (PinNum <= PIN15))
	{
		(GPIOPort[Port])->ODR ^= (ODR_MASK << PinNum);
	}

	else
	{
		Local_u8ErrorState = NOK;
	}


	return Local_u8ErrorState;
}

/****************************************************************************/
/*
 * @fn 			GPIO_u8ReadPinValue
 * @brief 		the function read the GPIO input pin
 * @param[in]	Port : the port number, get options @Port_T enum
 * @param[in]	PinNum : the pin number ,get options @Pin_T enum
 * @param[out]	PinValue : the reading pin value ,get options @PinVal_T
 * @retval		ErrorStatus
 * */
uint8_t GPIO_u8ReadPinValue(Port_T Port , Pin_T PinNum , PinVal_T *PinValue)
{
	uint8_t  Local_u8ErrorState = OK;

	/*Check Valid Inputs Configuration*/
	if((Port <= PORTC) && ((PinNum) <= PIN15))
	{
		*PinValue = (((GPIOPort[Port])->IDR >> PinNum)&IDR_ANDING);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}
