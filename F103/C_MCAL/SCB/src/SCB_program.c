/*
 * SCB_program.c
 *
 *  Created on: 14 Jul 2023
 *      Author: kareem
 */


#include<stdint.h>
#include"stm32f103xx.h"
#include"ERROR_STATE.h"
#include"SCB_interface.h"
#include"SCB_prv.h"

void SCB_voidSetPriorityGroup(uint8_t Copy_u8PriorityGroup)
{
    SCB->SCB_AIRCR = (SCB_VECTKEY<<16)|(Copy_u8PriorityGroup<<8); 
}
uint8_t SCB_u8setIQRprionty(SCB_IQR_ty perpheral,uint8_t prority)
{
    uint8_t Local_u8ErrorStatus= OK;
    if (SCB_SysTick>=perpheral)
    {
        SCB->SCB_SHPR[perpheral] = (prority << 4);
    }
    else
    {
        Local_u8ErrorStatus=NOK;
    }
    return Local_u8ErrorStatus;
}
uint8_t SCB_u8EnableFaultInterrupt(SCB_IQR_ty perpheral)
{
    uint8_t Local_u8ErrorStatus= OK;
    if (SCB_UsageFault>=perpheral)
    {
        SCB->SCB_SHCSR |=(1<<(perpheral+16));
    }
    else
    {
        Local_u8ErrorStatus=NOK;
    }
    return Local_u8ErrorStatus;
}
uint8_t SCB_u8DisableFaultInterrupt(SCB_IQR_ty perpheral)
{
    uint8_t Local_u8ErrorStatus= OK;
    if (SCB_UsageFault>=perpheral)
    {
        SCB->SCB_SHCSR &=~(1<<(perpheral+16));
    }
    else
    {
        Local_u8ErrorStatus=NOK;
    }
    return Local_u8ErrorStatus;
}