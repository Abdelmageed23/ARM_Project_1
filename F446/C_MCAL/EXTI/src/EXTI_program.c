/*
 * EXTI_program.c
 *
 *  Created on: 15 Jul 2023
 *      Author: kareem
 */


#include <stdint.h>
#include "stm32f446xx.h"
#include "ERROR_STATE.h"

#include "EXTI_interface.h"
#include "EXTI_prv.h"

uint8_t EXTI_u8Init(EXTI_CONFIG_ty *Config)
{
    uint8_t Local_u8ErrorState = OK;
	if((Config != NULL)&&(NULL!=(Config->Copy_pvUserFunc)))
	{
		if(((Config->Port) <= EXTI_PORTH)&&((Config->Line) <= EXTI_PIN15)&&((Config->InterruptState)<=EXTI_ENABLE))
		{
			switch ((Config->Trig_Src))
			{
			case EXTI_RISING_TRIG:
				EXTI->EXTI_RTSR |= (1<<(Config->Line));
				EXTI->EXTI_FTSR &=~(1<<(Config->Line));
				break;
			case EXTI_FALLING_TRIG:
				EXTI->EXTI_RTSR &=~(1<<(Config->Line));
				EXTI->EXTI_FTSR |= (1<<(Config->Line));
				break;
			case EXTI_FALLING_RISING_TRIG:
				EXTI->EXTI_RTSR |= (1<<(Config->Line));
				EXTI->EXTI_FTSR |= (1<<(Config->Line));
				break;
			
			default:
				Local_u8ErrorState = NOK;
				break;
			}
			EXTI_pvGlobCallBackLine[Config->Line] = (Config->Copy_pvUserFunc);
			/*Interrupt set*/
			EXTI->EXTI_IMR &=~(1<<(Config->Line));/*Bit Masking*/
			EXTI->EXTI_IMR |=((Config->InterruptState)<<(Config->Line));
			/*event Set*/
			/*
			EXTI->EXTI_EMR &=~(1<<(Config->Line));/*Bit Masking
			EXTI->EXTI_EMR |=((Config->EventState)<<(Config->Line));
			*/
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return  Local_u8ErrorState ;
}
uint8_t EXTI_u8SetTrigSrc(EXTI_Trig_Src_ty Copy_Trig_Src,EXTI_Line_ty Copy_Line)
{
	uint8_t Local_u8ErrorState = OK;
	if (Copy_Line<= EXTI_PIN15)
	{
		switch ((Copy_Trig_Src))
		{
		case EXTI_RISING_TRIG:
			EXTI->EXTI_RTSR |= (1<<(Copy_Line));
			EXTI->EXTI_FTSR &=~(1<<(Copy_Line));
			break;
		case EXTI_FALLING_TRIG:
			EXTI->EXTI_RTSR &=~(1<<(Copy_Line));
			EXTI->EXTI_FTSR |= (1<<(Copy_Line));
			break;
		case EXTI_FALLING_RISING_TRIG:
			EXTI->EXTI_RTSR |= (1<<(Copy_Line));
			EXTI->EXTI_FTSR |= (1<<(Copy_Line));
			break;
		
		default:
			Local_u8ErrorState = NOK;
			break;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return  Local_u8ErrorState ;
}
uint8_t EXTI_u8EnableInterrupt(EXTI_Line_ty Copy_Line)
{
	uint8_t Local_u8ErrorState = OK;
	if (Copy_Line<= EXTI_PIN15)
	{
		EXTI->EXTI_IMR |=(1<<Copy_Line);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return  Local_u8ErrorState ;
}
uint8_t EXTI_u8DisableInterrupt(EXTI_Line_ty Copy_Line)
{
	uint8_t Local_u8ErrorState = OK;
	if (Copy_Line<= EXTI_PIN15)
	{
		EXTI->EXTI_IMR &=~(1<<Copy_Line);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return  Local_u8ErrorState ;
}
uint8_t EXTI_u8DoSoftwareInterrupt(EXTI_Line_ty Line)
{
	uint8_t Local_u8ErrorState = OK;
	if(((Line) <= EXTI_PIN15))
	{
		/*Software Inturrept set*/
		EXTI->EXTI_SWIER =(1<<Line);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return  Local_u8ErrorState ;
}
uint8_t EXTI_u8ClearPendingFlag(EXTI_Line_ty Line)
{
	uint8_t Local_u8ErrorState = OK;
	if(((Line) <= EXTI_PIN15))
	{
		/*Clear Pending Flag*/
		EXTI->EXTI_PR =(1<<Line);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return  Local_u8ErrorState ;
}
uint8_t EXTI_u8ReadPendingFlag(EXTI_Line_ty Line,EXTI_Flag_STATUS_ty *FlagValue)
{
	uint8_t Local_u8ErrorState = OK;
	if(((Line) <= EXTI_PIN15))
	{
		/*Clear Pending Flag*/
		*FlagValue = ((EXTI->EXTI_PR) >>Line) & 1U;
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return  Local_u8ErrorState ;
}
void EXTI_voidReadAllPendingFlag(uint32_t *RegisterValue)
{
	*RegisterValue = (EXTI->EXTI_PR);
}
/*ISR Functions*/
void EXTI0_IRQHandler(void)
{
	if (NULL!=EXTI_pvGlobCallBackLine[0])
	{
		EXTI_pvGlobCallBackLine[0]();
	}
	
}
void EXTI1_IRQHandler(void)
{
	if (NULL!=EXTI_pvGlobCallBackLine[1])
	{
		EXTI_pvGlobCallBackLine[1]();
	}
	
}
void EXTI2_IRQHandler(void)
{
	if (NULL!=EXTI_pvGlobCallBackLine[2])
	{
		EXTI_pvGlobCallBackLine[2]();
	}
	
}
void EXTI3_IRQHandler(void)
{
	if (NULL!=EXTI_pvGlobCallBackLine[3])
	{
		EXTI_pvGlobCallBackLine[3]();
	}
	
}
void EXTI4_IRQHandler(void)
{
	if (NULL!=EXTI_pvGlobCallBackLine[4])
	{
		EXTI_pvGlobCallBackLine[4]();
	}
	
}
void EXTI9_5_IRQHandler(void)
{
	if(((EXTI->EXTI_PR)>>5)& 1)
	{
		if (NULL!=EXTI_pvGlobCallBackLine[5])
		{
			EXTI_pvGlobCallBackLine[5]();
		}
	}
	if(((EXTI->EXTI_PR)>>6)& 1)
	{
		if (NULL!=EXTI_pvGlobCallBackLine[6])
		{
			EXTI_pvGlobCallBackLine[6]();
		}
	}
	if(((EXTI->EXTI_PR)>>7)& 1)
	{
		if (NULL!=EXTI_pvGlobCallBackLine[7])
		{
			EXTI_pvGlobCallBackLine[7]();
		}
	}
	if(((EXTI->EXTI_PR)>>8)& 1)
	{
		if (NULL!=EXTI_pvGlobCallBackLine[8])
		{
			EXTI_pvGlobCallBackLine[8]();
		}
	}
	if(((EXTI->EXTI_PR)>>9)& 1)
	{
		if (NULL!=EXTI_pvGlobCallBackLine[9])
		{
			EXTI_pvGlobCallBackLine[9]();
		}
	}
}
void EXTI15_10_IRQHandler(void)
{
	if(((EXTI->EXTI_PR)>>10)& 1)
	{
		if (NULL!=EXTI_pvGlobCallBackLine[10])
		{
			EXTI_pvGlobCallBackLine[10]();
		}
	}
	if(((EXTI->EXTI_PR)>>11)& 1)
	{
		if (NULL!=EXTI_pvGlobCallBackLine[11])
		{
			EXTI_pvGlobCallBackLine[11]();
		}
	}
	if(((EXTI->EXTI_PR)>>12)& 1)
	{
		if (NULL!=EXTI_pvGlobCallBackLine[12])
		{
			EXTI_pvGlobCallBackLine[12]();
		}
	}
	if(((EXTI->EXTI_PR)>>13)& 1)
	{
		if (NULL!=EXTI_pvGlobCallBackLine[13])
		{
			EXTI_pvGlobCallBackLine[13]();
		}
	}
	if(((EXTI->EXTI_PR)>>14)& 1)
	{
		if (NULL!=EXTI_pvGlobCallBackLine[14])
		{
			EXTI_pvGlobCallBackLine[14]();
		}
	}if(((EXTI->EXTI_PR)>>15)& 1)
	{
		if (NULL!=EXTI_pvGlobCallBackLine[15])
		{
			EXTI_pvGlobCallBackLine[15]();
		}
	}
}