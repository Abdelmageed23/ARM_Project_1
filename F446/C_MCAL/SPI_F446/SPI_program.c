/**
 ******************************************************************************
 * @file           : SPI_program.c
 * @author         : Diea Abdeltwab
 * @layer          : MCAL
 * @brief          : Version 2 For STM32F446RE Drivers
 * @date           : 25/8/2023
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
/******************************************************************************/
/************************ LIB Layer *******************************************/
/******************************************************************************/
#include <stdint.h>
#include "ERROR_STATE.h"
#include "BIT_MATH.h"
#include "STM32F446xx.h"
/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"
/******************************************************************************/
/************************ Global **********************************************/
/******************************************************************************/
static void (* SPI_ApFunCallBack[SPI_NUMBERS])(uint8_t) = {NULL,NULL,NULL,NULL} ;
/*************************************************************************************************************************************/
/********************************************************* Functions implementations *************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : MSPI_u8SetConfiguration
 * @brief          : initialization Value of SPI Configuration
 * @param[in]      : USARTconfig  --> get option from @SPIconfig_t  struct
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MSPI_u8SetConfiguration ( const SPIconfig_t* SPIconfig )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;
	if (  SPIconfig !=NULL )
	{
		SPI_Index[SPIconfig->SPIindex] -> CR1 &=~ ( SPI_CPHA_MASK         << SPI_CR1_CPHA );
		SPI_Index[SPIconfig->SPIindex] -> CR1 |=  ( SPIconfig->ClockPhase << SPI_CR1_CPHA );

		SPI_Index[SPIconfig->SPIindex] -> CR1 &=~ ( SPI_CPOL_MASK            << SPI_CR1_CPOL );
		SPI_Index[SPIconfig->SPIindex] -> CR1 |=  ( SPIconfig->ClockPolarity << SPI_CR1_CPOL );

		SPI_Index[SPIconfig->SPIindex] -> CR1 &=~ ( SPI_MSTR_MASK           << SPI_CR1_MSTR );
		SPI_Index[SPIconfig->SPIindex] -> CR1 |=  ( SPIconfig->SPI_MCUstate << SPI_CR1_MSTR );

		SPI_Index[SPIconfig->SPIindex] -> CR1 &=~ ( SPI_BR_MASK         << SPI_CR1_BR );
		SPI_Index[SPIconfig->SPIindex] -> CR1 |=  ( SPIconfig->BaudRate << SPI_CR1_BR );

		SPI_Index[SPIconfig->SPIindex] -> CR1 &=~ (SPI_LSBFIRST_MASK      << (SPI_CR1_LSBFIRST));
		SPI_Index[SPIconfig->SPIindex] -> CR1 |=  (SPIconfig->FrameFormat << (SPI_CR1_LSBFIRST));

		SPI_Index[SPIconfig->SPIindex] -> CR1 &=~ (SPI_SSI_MASK                   << (SPI_CR1_SSI));
		SPI_Index[SPIconfig->SPIindex] -> CR1 |=  (SPIconfig->InternalSlaveSelect << (SPI_CR1_SSI));

		SPI_Index[SPIconfig->SPIindex] -> CR1 &=~ (SPI_SSM_MASK                      << (SPI_CR1_SSM));
		SPI_Index[SPIconfig->SPIindex] -> CR1 |=  (SPIconfig->SoftwareSlaveManagment << (SPI_CR1_SSM));

		SPI_Index[SPIconfig->SPIindex] -> CR1 &=~ (SPI_RXONLY_MASK        << (SPI_CR1_RXONLY));
		SPI_Index[SPIconfig->SPIindex] -> CR1 |=  (SPIconfig->ReceiveOnly << (SPI_CR1_RXONLY));

		SPI_Index[SPIconfig->SPIindex] -> CR1 &=~ (SPI_DFF_MASK         << (SPI_CR1_DFF));
		SPI_Index[SPIconfig->SPIindex] -> CR1 |=  (SPIconfig->DataFrame << (SPI_CR1_DFF));
/****************************************************************************************************/

		SPI_Index[SPIconfig->SPIindex] -> CR2 &=~ (SPI_RXDMAEN_MASK << (SPI_CR2_RXDMAEN));
		SPI_Index[SPIconfig->SPIindex] -> CR2 |=  (SPIconfig->RXDMA << (SPI_CR2_RXDMAEN));
	
		SPI_Index[SPIconfig->SPIindex] -> CR2 &=~ (SPI_TXDMAEN_MASK << (SPI_CR2_TXDMAEN));
		SPI_Index[SPIconfig->SPIindex] -> CR2 |=  (SPIconfig->TXDMA << (SPI_CR2_TXDMAEN));
	
		SPI_Index[SPIconfig->SPIindex] -> CR2 &=~ (SPI_SSOE_MASK       << (SPI_CR2_SSOE));
		SPI_Index[SPIconfig->SPIindex] -> CR2 |=  (SPIconfig->SSoutput << (SPI_CR2_SSOE));

		SPI_Index[SPIconfig->SPIindex] -> CR2 &=~ (SPI_RXNEIE_MASK        << (SPI_CR2_RXNEIE));
		SPI_Index[SPIconfig->SPIindex] -> CR2 |=  (SPIconfig->RXinterrupt << (SPI_CR2_RXNEIE));

		SPI_Index[SPIconfig->SPIindex] -> CR2 &=~ (SPI_TXEIE_MASK         << (SPI_CR2_TXEIE));
		SPI_Index[SPIconfig->SPIindex] -> CR2 |=  (SPIconfig->TXinterrupt << (SPI_CR2_TXEIE));

		SET_BIT( SPI_Index[SPIconfig->SPIindex] -> CR1 , SPI_CR1_SPE );
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}
	return Local_u8ErrorState ;

}
/**
 ******************************************************************************
 * @fn             : MSPI_u8SendReceiveSynch
 * @brief          : Send and Receive Synchronization Function
 * @param[in]      : Copy_SPIindex  --> Get option From @SPIindex_t enum
 * @param[in]      : Copy_u8DataToTransmit  --> Set Transmit Data
 * @param[out]     : Copy_u8DataToReceive  --> Get Received Data
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MSPI_u8SendReceiveSynch ( SPIindex_t Copy_SPIindex , uint8_t Copy_u8DataToTransmit , uint8_t *Copy_u8DataToReceive )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if (   Copy_u8DataToReceive != NULL )
	{
		while ( 0==GET_BIT(SPI_Index[Copy_SPIindex]  ->  SR , 1 ) );
		SPI_Index[Copy_SPIindex]  -> DR = Copy_u8DataToTransmit ;
		while ( 1 == GET_BIT( SPI_Index[Copy_SPIindex] ->  SR , 7 ) );
		while ( 0==GET_BIT(SPI_Index[Copy_SPIindex]  ->  SR , 0 ) );
		*Copy_u8DataToReceive = SPI_Index[Copy_SPIindex]  -> DR  ;
	}
	else 
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/**
 ******************************************************************************
 * @fn             : MSPI_u8TransmitArraySynch
 * @brief          : Transmit Array Synch
 * @param[in]      : Copy_SPIindex  --> Get option From @SPIindex_t enum
 * @param[out]     : Copy_pu8DataArray  --> Set Received Data
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MSPI_u8TransmitArraySynch  ( SPIindex_t Copy_SPIindex , uint8_t * Copy_pu8DataArray )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK , Local_u8RxTemp  ;
	volatile uint8_t Local_u8tmp ;
	if ( Copy_pu8DataArray != NULL )
	{
       for (uint8_t Local_u8Counter = 0 ; Copy_pu8DataArray[Local_u8Counter] != '\0' ; Local_u8Counter++ )
	   {
    	   MSPI_u8SendReceiveSynch( Copy_SPIindex , Copy_pu8DataArray[Local_u8Counter] , &Local_u8RxTemp );
		   for (uint32_t i =0 ; i<=1000;i++)
		   {
				 Local_u8tmp=i;
		   }
	   }
       MSPI_u8SendReceiveSynch( Copy_SPIindex , '\0' , &Local_u8RxTemp );
	}
	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}

/**
 ******************************************************************************
 * @fn             : MSPI_u8SendReceiveAsynch
 * @brief          : Send and Receive Synchronization Function
 * @param[in]      : Copy_SPIindex  --> Get option From @SPIindex_t enum
 * @param[in]      : Copy_u8DataToTransmit  --> Set Transmit Data
 * @param[out]     : Copy_pFunNotification  --> Set Address of Call Back Function
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t MSPI_u8SendReceiveAsynch ( SPIindex_t Copy_SPIindex , uint8_t Copy_u8DataToTransmit , void (*Copy_pFunNotification) (uint8_t) )
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK ;
	if (  Copy_pFunNotification != NULL  )
	{
		SPI_ApFunCallBack[Copy_SPIindex]=Copy_pFunNotification;
		SPI_Index[Copy_SPIindex] -> DR = Copy_u8DataToTransmit ;
	}
	else 
	{
		Local_u8ErrorState = ERROR_STATE_NOK ;
	}
	return Local_u8ErrorState ;
}
/*************************************************************************************************************************************/
/********************************************************* Handlers implementations *************************************************/
/*************************************************************************************************************************************/
void SPI1_IRQHandler(void)
{
    if ( SPI_ApFunCallBack[SPI_1] != NULL )
	{
    	SPI_ApFunCallBack[SPI_1]( SPI_Index[SPI_1] -> DR );
	}
}
void SPI2_IRQHandler(void)
{
    if ( SPI_ApFunCallBack[SPI_2] != NULL )
	{
    	SPI_ApFunCallBack[SPI_2]( SPI_Index[SPI_2] -> DR );
	}
}
void SPI3_IRQHandler(void)
{
    if ( SPI_ApFunCallBack[SPI_3] != NULL )
	{
    	SPI_ApFunCallBack[SPI_3]( SPI_Index[SPI_3] -> DR );
	}
}
void SPI4_IRQHandler(void)
{
    if ( SPI_ApFunCallBack[SPI_4] != NULL )
	{
    	SPI_ApFunCallBack[SPI_4]( SPI_Index[SPI_4] -> DR );
	}
}
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/

