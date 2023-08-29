/*****************************
 * @file RCC_program.c 
 * @author Ahmed Tarek
 * @brief the RCC main source file, including functions' definitions
 * 
 */


#include <stdint.h>
#include "stm32f103xx.h"
#include "ERROR_STATE.h"
#include "RCC_prv.h"
#include "RCC_interface.h"
/****************************************************
 * @fn RCC_SetClksts
 * @brief the function change clock state according to the input parameters
 * @param[in]  ClkType  : the clock what it is want to change his state
 * @param[in]  State : the state which the user wants the clock to be OFForON
 * @retval ErrorStatus
 */
uint8_t RCC_SetClksts(SET_CLK_type_ty ClkType,STATE_ty State)
{
	uint8_t Local_State_Error = OK;
    uint32_t Polling=0;
	switch (State)
	{
	case STATE_ON:
		RCC->RCC_CR |=(ONE_BIT_MASKING<<ClkType);
		while ((((RCC->RCC_CR>>ClkType)&1)!=State)||(Polling==CLKYYPE_TIMEOUT))
        {
            Polling++;
        }
		if (Polling == CLKYYPE_TIMEOUT)
		{
			Local_State_Error=NOK;
		}
		break;
	case STATE_OFF:
		RCC->RCC_CR &=~(ONE_BIT_MASKING<<ClkType);
		/*No need for polling*/
		break;
	
	default:
		Local_State_Error=NOK;
		break;
	}
	return Local_State_Error;
}

uint8_t RCC_SetSysClk(SYS_CLK_type_ty ClkType)
{
    uint8_t Local_State_Error = OK;
	if (ClkType<=SYS_PLL)
	{
		RCC->RCC_CFGR &=~(TWO_BITS_MASKING<<RCC_CFGR_SW_0);
		RCC->RCC_CFGR |=(ClkType<<RCC_CFGR_SW_0);
	}
	else
	{
		Local_State_Error = NOK;
	}
	return Local_State_Error;
}
uint8_t RCC_HSE_Config(HSEconfig_type_ty Config)
{
	uint8_t Local_State_Error = OK;
	switch (Config)
	{
	case HSE_diviedby_1:
		RCC->RCC_CFGR &=~(ONE_BIT_MASKING<<RCC_CFGR_PLLXTPRE);
		break;
	case HSE_diviedby_2:
		RCC->RCC_CFGR |=(ONE_BIT_MASKING<<RCC_CFGR_PLLXTPRE);
		break;
	
	default:
		Local_State_Error = NOK;
		break;
	}
    return Local_State_Error;
}
void RCC_PLL_Config(PLL_MUL_type_ty PllMul,PLLSRC_ty PLL_SCR)
{
    //bits musking
    RCC->RCC_CFGR &=~(FOUR_BITS_MASKING<<RCC_CFGR_PLLMUL_0);
    //pll scr
    RCC->RCC_CFGR |= (PllMul<<RCC_CFGR_PLLMUL_0);

    if (PLLHSI==PLL_SCR)
    {
		RCC->RCC_CFGR &=~(ONE_BIT_MASKING<<RCC_CFGR_PLLSRC);
    }
    else if (PLLHSE==PLL_SCR)
    {
		RCC->RCC_CFGR |= (ONE_BIT_MASKING<<RCC_CFGR_PLLSRC);
    }
    
}
//AHB
void RCC_AHBEnableClock(AHBperipheral_ty peripheral)
{
	RCC->RCC_AHBENR |=(ONE_BIT_MASKING<<peripheral);
}
void RCC_AHBDisableClock(AHBperipheral_ty peripheral)
{
    RCC->RCC_AHBENR &=~(ONE_BIT_MASKING<<peripheral);
}
//APB1
void RCC_APB1EnableClock(APB1peripheral_ty peripheral)
{
	RCC->RCC_APB1ENR |=(ONE_BIT_MASKING<<peripheral);
}
void RCC_APB1DisableClock(APB1peripheral_ty peripheral)
{
    RCC->RCC_APB1ENR &=~(ONE_BIT_MASKING<<peripheral);
}
//APB2
void RCC_APB2EnableClock(APB2peripheral_ty peripheral)
{
	RCC->RCC_APB2ENR |=(ONE_BIT_MASKING<<peripheral);
}
void RCC_APB2DisableClock(APB2peripheral_ty peripheral)
{
    RCC->RCC_APB2ENR &=~(ONE_BIT_MASKING<<peripheral);
}
