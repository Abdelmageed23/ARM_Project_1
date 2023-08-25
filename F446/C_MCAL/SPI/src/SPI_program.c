/*
 * SPI_program.c
 *
 *  Created on: Aug 24, 2023
 *      Author: kareem
 */

#include <stdint.h>
#include "../../../Library/stm32f446xx.h"
#include "../../../Library/ErrType.h"
#include "../inc/SPI_interface.h"
#include "../inc/SPI_prv.h"
static SPI_RegDef_t* SPI_NUM[SPI_PERIPHERSL_NUM]={SPI1,SPI2,SPI3,SPI4};

uint8_t SPI_u8Init(const SPI_Config_ty *Comunication)
{
    uint8_t Local_u8ErrorState =OK;
    if ((Comunication->SpiNumber)<SPI_PERIPHERSL_NUM)
    {
        /*SPI_CR1*/
        SPI_NUM[Comunication->SpiNumber]->SPI_CR1 =0;/*Register masking*/
        SPI_NUM[Comunication->SpiNumber]->SPI_CR1 |=((Comunication->LinesDirections)<<15);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR1 |=((Comunication->DataFrameLenght)<<11);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR1 |=((Comunication->SPIperiphState)<<6);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR1 |=((Comunication->ClockSpeed)<<3);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR1 |=((Comunication->SpiState)<<2);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR1 |=((Comunication->SLaveSlection)<<9);

        /*set call back funications*/
        SPI_pvTxEmptyCallBackLine[Comunication->SpiNumber] = (Comunication->Copy_pvTxEmptUserFunc);
        SPI_pvRxNotEmptyCallBackLine[Comunication->SpiNumber] = (Comunication->Copy_pvRxNotEmptUserFunc);
        
        /*SPI_CR2*/
        SPI_NUM[Comunication->SpiNumber]->SPI_CR2 =0;/*Register masking*/
        SPI_NUM[Comunication->SpiNumber]->SPI_CR2 |=((Comunication->SSOstate)<<2);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR2 |=((Comunication->InterruptsStates.TxBufferEmptyInter)<<7);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR2 |=((Comunication->InterruptsStates.RxBufferNotEmptyInter)<<6);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR2 |=((Comunication->InterruptsStates.ErrorInter)<<5);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR2 |=((Comunication->InterruptsStates.FrameFromateInter)<<4);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR2 |=((Comunication->InterruptsStates.TxBufferDMA)<<1);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR2 |=((Comunication->InterruptsStates.RxBufferDMA)<<0);
        
    }
    else
    {
        Local_u8ErrorState = NOK;
    }
    return Local_u8ErrorState;
}
uint8_t SPI_u8ReadData(SPI_Number_t   SpiNumber,uint16_t*pv_u16Distantion)
{
    uint8_t Local_u8ErrorState =OK;
    if (SpiNumber<SPI_PERIPHERSL_NUM)
    {
        /*SPI_DR*/
        *pv_u16Distantion = SPI_NUM[SpiNumber]->SPI_DR;
    }
    else
    {
        Local_u8ErrorState = NOK;
    }
    return Local_u8ErrorState;
}
uint8_t SPI_u8WriteData(SPI_Number_t   SpiNumber,uint16_t pv_u16Data)
{
    uint8_t Local_u8ErrorState =OK;
    if (SpiNumber<SPI_PERIPHERSL_NUM)
    {
        /*SPI_DR*/
        SPI_NUM[SpiNumber]->SPI_DR =pv_u16Data;
    }
    else
    {
        Local_u8ErrorState = NOK;
    }
    return Local_u8ErrorState;
}

void SPI1_IRQHandler(void)
{
    if (((SPI_NUM[SPI_1]->SPI_SR)>>0)&1)
    {
        SPI_pvRxNotEmptyCallBackLine[SPI_1]();
    }
    if (((SPI_NUM[SPI_1]->SPI_SR)>>1)&1)
    {
        SPI_pvTxEmptyCallBackLine[SPI_1]();
    }
}
void SPI2_IRQHandler(void)
{
    if (((SPI_NUM[SPI_2]->SPI_SR)>>0)&1)
    {
        SPI_pvRxNotEmptyCallBackLine[SPI_2]();
    }
    if (((SPI_NUM[SPI_2]->SPI_SR)>>1)&1)
    {
        SPI_pvTxEmptyCallBackLine[SPI_2]();
    }
}
void SPI3_IRQHandler(void)
{
    if (((SPI_NUM[SPI_3]->SPI_SR)>>0)&1)
    {
        SPI_pvRxNotEmptyCallBackLine[SPI_3]();
    }
    if (((SPI_NUM[SPI_3]->SPI_SR)>>1)&1)
    {
        SPI_pvTxEmptyCallBackLine[SPI_3]();
    }
}
void SPI4_IRQHandler(void)
{
    if (((SPI_NUM[SPI_4]->SPI_SR)>>0)&1)
    {
        SPI_pvRxNotEmptyCallBackLine[SPI_4]();
    }
    if (((SPI_NUM[SPI_4]->SPI_SR)>>1)&1)
    {
        SPI_pvTxEmptyCallBackLine[SPI_4]();
    }
}