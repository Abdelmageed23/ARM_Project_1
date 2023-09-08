/*
 * SYSCFG_program.c
 *
 *  Created on: 15 Jul 2023
 *      Author: kareem
 */
#include <stdint.h>
#include "stm32f446xx.h"
#include "ERROR_STATE.h"

#include "SYSCFG_interface.h"
#include "SYSCFG_prv.h"

uint8_t SYSCFG_u8SetEXTIPort(SYSCFG_line_ty Line,SYSCFG_port_ty Port)
{
    uint8_t Local_u8ErrorState = OK;
    uint8_t Local_u8BitNumber = (Line%SYSCFG_BITACCESS)*SYSCFG_BITACCESS;
    uint8_t Local_u8RegNumber = Line/SYSCFG_BITACCESS;
    
	if((Port <= SYSCFG_PORTH)&&(Line<=SYSCFG_LINE15))
	{
		SYSCFG->SYSCFG_EXTICR[Local_u8RegNumber] &=~(SYSCFG_MASK<<Local_u8BitNumber);
        SYSCFG->SYSCFG_EXTICR[Local_u8RegNumber] |=(Port<<Local_u8BitNumber);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return  Local_u8ErrorState ;
}
