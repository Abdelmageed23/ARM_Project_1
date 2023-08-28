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
/******************************************************************************************************
 *Static Globle Varaibles 
 *****************************************************************************************************
*/
static SPI_RegDef_t* SPI_NUM[SPI_PERIPHERSL_NUM]={SPI1,SPI2,SPI3,SPI4};
static uint8_t*SPI_pvTxData[SPI_PERIPHERSL_NUM]={0};
static uint8_t*SPI_pvRxDestination[SPI_PERIPHERSL_NUM]={0};
static uint8_t SPI_u8GlobleTxIntCounter[SPI_PERIPHERSL_NUM]={0};
static uint8_t SPI_u8GlobleRxIntCounter[SPI_PERIPHERSL_NUM]={0};
static uint8_t SPI_u8GlobleTxDataSize[SPI_PERIPHERSL_NUM]={0};
static uint8_t SPI_u8GlobleRxDataSize[SPI_PERIPHERSL_NUM]={0};

uint8_t SPI_u8Init(const SPI_Config_ty *Comunication)
{
    uint8_t Local_u8ErrorState =OK;
    if ((Comunication->SpiNumber)<SPI_PERIPHERSL_NUM)
    {
        /*SPI_CR1*/
        SPI_NUM[Comunication->SpiNumber]->SPI_CR1 =0;/*Register masking*/
        SPI_NUM[Comunication->SpiNumber]->SPI_CR1 |=((Comunication->LinesDirections)<<CR1_BIDIMODE);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR1 |=((Comunication->DataFrameLenght)<<CR1_DFF);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR1 |=((Comunication->SPIperiphState)<<CR1_SPE);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR1 |=((Comunication->ClockSpeed)<<CR1_BR);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR1 |=((Comunication->SpiState)<<CR1_MSTR);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR1 |=((Comunication->SLaveSlection)<<CR1_SSM);

        /*set call back funications*/
        SPI_pvTxEmptyCallBackLine[Comunication->SpiNumber] = (Comunication->Copy_pvTxEmptUserFunc);
        SPI_pvRxNotEmptyCallBackLine[Comunication->SpiNumber] = (Comunication->Copy_pvRxNotEmptUserFunc);
        
        /*SPI_CR2*/
        SPI_NUM[Comunication->SpiNumber]->SPI_CR2 =0;/*Register masking*/
        SPI_NUM[Comunication->SpiNumber]->SPI_CR2 |=((Comunication->SSOstate)<<CR2_SSOE);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR2 |=((Comunication->InterruptsStates.TxBufferEmptyInter)<<CR2_TXEIE);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR2 |=((Comunication->InterruptsStates.RxBufferNotEmptyInter)<<CR2_RXNEIE);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR2 |=((Comunication->InterruptsStates.ErrorInter)<<CR2_ERRIE);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR2 |=((Comunication->InterruptsStates.FrameFromateInter)<<CR2_FRF);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR2 |=((Comunication->InterruptsStates.TxBufferDMA)<<CR2_TXDMAEN);
        SPI_NUM[Comunication->SpiNumber]->SPI_CR2 |=((Comunication->InterruptsStates.RxBufferDMA)<<CR2_RXDMAEN);
        
    }
    else
    {
        Local_u8ErrorState = NOK;
    }
    return Local_u8ErrorState;
}
uint8_t SPI_u8AreYouBusy(SPI_Number_t   SpiNumber)
{
    return ((SPI_NUM[SpiNumber]->SPI_SR)>>SR_BSY)&SPI_ONE_BIT_MASKING;
}
/******************************************************************************************************
 *Recive functions
 *****************************************************************************************************
*/
uint8_t SPI_u8ReciveData_IT(SPI_Number_t   SpiNumber,uint8_t DataLegth,uint8_t*pv_u8Distantion)
{
    uint8_t Local_u8ErrorState =OK;
    if (SpiNumber<SPI_PERIPHERSL_NUM)
    {
        SPI_pvRxDestination[SpiNumber]=pv_u8Distantion;
        SPI_u8GlobleRxDataSize[SpiNumber]=DataLegth;
        SPI_u8GlobleRxIntCounter[SpiNumber]=0U;
    }
    else
    {
        Local_u8ErrorState = NOK;
    }
    return Local_u8ErrorState;
}
uint8_t SPI_u8ReciveData_pulling(SPI_Number_t   SpiNumber,uint16_t*pv_u16Distantion)
{
    uint8_t Local_u8ErrorState =OK;
    if (SpiNumber<SPI_PERIPHERSL_NUM)
    {
        /*SPI_DR*/
        while(((SPI_NUM[SpiNumber]->SPI_SR)>>SR_BSY)&SPI_ONE_BIT_MASKING);/*free if it = 0 */
        *pv_u16Distantion = SPI_NUM[SpiNumber]->SPI_DR;
    }
    else
    {
        Local_u8ErrorState = NOK;
    }
    return Local_u8ErrorState;
}
/******************************************************************************************************
 *Send functions
 *****************************************************************************************************
*/
uint8_t SPI_u8SendData_IT(SPI_Number_t   SpiNumber,uint8_t DataLegth,uint8_t* pv_u8Data)
{
    uint8_t Local_u8ErrorState =OK;
    if (SpiNumber<SPI_PERIPHERSL_NUM)
    {
        SPI_pvTxData[SpiNumber]=pv_u8Data;
        SPI_u8GlobleTxDataSize[SpiNumber]=DataLegth;
        SPI_u8GlobleTxIntCounter[SpiNumber]=0U;
    }
    else
    {
        Local_u8ErrorState = NOK;
    }
    return Local_u8ErrorState;
}
uint8_t SPI_u8SendData_polling(SPI_Number_t   SpiNumber,uint16_t Copy_u16Data)
{
    uint8_t Local_u8ErrorState =OK;
    if (SpiNumber<SPI_PERIPHERSL_NUM)
    {
        /*SPI_DR*/
        while(((SPI_NUM[SpiNumber]->SPI_SR)>>SR_BSY)&SPI_ONE_BIT_MASKING);/*free if it = 0 */
        SPI_NUM[SpiNumber]->SPI_DR =Copy_u16Data;
    }
    else
    {
        Local_u8ErrorState = NOK;
    }
    return Local_u8ErrorState;
}
/*******************************************************************************************************
 * ISR functions 
 *******************************************************************************************************
*/
void SPI1_IRQHandler(void)
{
    if (((SPI_NUM[SPI_1]->SPI_SR)>>SR_RXNE)&SPI_ONE_BIT_MASKING)
    {
        if (SPI_u8GlobleRxIntCounter[SPI_1]<SPI_u8GlobleRxDataSize[SPI_1])
        {
            SPI_pvRxDestination[SPI_1][SPI_u8GlobleRxIntCounter[SPI_1]] = SPI_NUM[SPI_1]->SPI_DR;
            SPI_u8GlobleRxIntCounter[SPI_1]++;
        }        
        if (NULL!=SPI_pvRxNotEmptyCallBackLine[SPI_1])
		{
			SPI_pvRxNotEmptyCallBackLine[SPI_1]();
		}
    }
    if (((SPI_NUM[SPI_1]->SPI_SR)>>SR_TXE)&SPI_ONE_BIT_MASKING)
    {
        if (SPI_u8GlobleTxIntCounter[SPI_1]<SPI_u8GlobleTxDataSize[SPI_1])
        {
            SPI_NUM[SPI_1]->SPI_DR = SPI_pvTxData[SPI_1][SPI_u8GlobleTxIntCounter[SPI_1]];
            SPI_u8GlobleTxIntCounter[SPI_1]++;
        }
        if (NULL!=SPI_pvTxEmptyCallBackLine[SPI_1])
		{
			SPI_pvTxEmptyCallBackLine[SPI_1]();
		}
    }
}
void SPI2_IRQHandler(void)
{
    if (((SPI_NUM[SPI_2]->SPI_SR)>>SR_RXNE)&SPI_ONE_BIT_MASKING)
    {
        if (SPI_u8GlobleRxIntCounter[SPI_2]<SPI_u8GlobleRxDataSize[SPI_2])
        {
            SPI_pvRxDestination[SPI_2][SPI_u8GlobleRxIntCounter[SPI_2]] = SPI_NUM[SPI_2]->SPI_DR;
            SPI_u8GlobleRxIntCounter[SPI_2]++;
        }
        if (NULL!=SPI_pvRxNotEmptyCallBackLine[SPI_2])
		{
			SPI_pvRxNotEmptyCallBackLine[SPI_2]();
		}
    }
    if (((SPI_NUM[SPI_2]->SPI_SR)>>SR_TXE)&SPI_ONE_BIT_MASKING)
    {
        if (SPI_u8GlobleTxIntCounter[SPI_2]<SPI_u8GlobleTxDataSize[SPI_2])
        {
            SPI_NUM[SPI_2]->SPI_DR = SPI_pvTxData[SPI_2][SPI_u8GlobleTxIntCounter[SPI_2]];
            SPI_u8GlobleTxIntCounter[SPI_2]++;
        }
        if (NULL!=SPI_pvTxEmptyCallBackLine[SPI_2])
		{
			SPI_pvTxEmptyCallBackLine[SPI_2]();
		}
    }
}
void SPI3_IRQHandler(void)
{
    if (((SPI_NUM[SPI_3]->SPI_SR)>>SR_RXNE)&SPI_ONE_BIT_MASKING)
    {
        if (SPI_u8GlobleRxIntCounter[SPI_3]<SPI_u8GlobleRxDataSize[SPI_3])
        {
            SPI_pvRxDestination[SPI_3][SPI_u8GlobleRxIntCounter[SPI_3]] = SPI_NUM[SPI_3]->SPI_DR;
            SPI_u8GlobleRxIntCounter[SPI_3]++;
        }
        if (NULL!=SPI_pvRxNotEmptyCallBackLine[SPI_3])
		{
			SPI_pvRxNotEmptyCallBackLine[SPI_3]();
		}
    }
    if (((SPI_NUM[SPI_3]->SPI_SR)>>SR_TXE)&SPI_ONE_BIT_MASKING)
    {
        if (SPI_u8GlobleTxIntCounter[SPI_3]<SPI_u8GlobleTxDataSize[SPI_3])
        {
            SPI_NUM[SPI_3]->SPI_DR = SPI_pvTxData[SPI_3][SPI_u8GlobleTxIntCounter[SPI_3]];
            SPI_u8GlobleTxIntCounter[SPI_3]++;
        }
        if (NULL!=SPI_pvTxEmptyCallBackLine[SPI_3])
		{
			SPI_pvTxEmptyCallBackLine[SPI_3]();
		}
    }
}
void SPI4_IRQHandler(void)
{
    if (((SPI_NUM[SPI_4]->SPI_SR)>>SR_RXNE)&SPI_ONE_BIT_MASKING)
    {
        if (SPI_u8GlobleRxIntCounter[SPI_4]<SPI_u8GlobleRxDataSize[SPI_4])
        {
            SPI_pvRxDestination[SPI_4][SPI_u8GlobleRxIntCounter[SPI_4]] = SPI_NUM[SPI_4]->SPI_DR;
            SPI_u8GlobleRxIntCounter[SPI_4]++;
        }
        if (NULL!=SPI_pvRxNotEmptyCallBackLine[SPI_4])
		{
			SPI_pvRxNotEmptyCallBackLine[SPI_4]();
		}
    }
    if (((SPI_NUM[SPI_4]->SPI_SR)>>SR_TXE)&SPI_ONE_BIT_MASKING)
    {
        if (SPI_u8GlobleTxIntCounter[SPI_4]<SPI_u8GlobleTxDataSize[SPI_4])
        {
            SPI_NUM[SPI_4]->SPI_DR = SPI_pvTxData[SPI_4][SPI_u8GlobleTxIntCounter[SPI_4]];
            SPI_u8GlobleTxIntCounter[SPI_4]++;
        }
        if (NULL!=SPI_pvTxEmptyCallBackLine[SPI_4])
		{
			SPI_pvTxEmptyCallBackLine[SPI_4]();
		}
    }
}