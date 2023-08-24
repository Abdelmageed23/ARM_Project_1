#include <stdint.h>
#include "STATUS.h"

#include "STM32F446xx.h"

#include "DMA_private.h"
#include "DMA_interface.h"

static DMA_RegDef_T *DMA_Arr[2] = {DMA1 , DMA2};

static void (*GeneralCallBackFun[DMA_TYPE_NUM*DMA_STREAM_NUM])(void) = {NULL};

uint8_t DMA_u8Init(DMA_Cnfg_T* DMA_Cnfg)
{
	uint8_t Local_u8ErrorState = OK;


	if(DMA_Cnfg != NULL)
	{
		/* Set Channel Number */
		DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SCR] &= ~(DMA_CHSEL_MASK << DMA_CHSEL_SHIFT);
		DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SCR] |= (DMA_Cnfg->ChannelNum << DMA_CHSEL_SHIFT);

		/* Set data transfer direction*/
		DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SCR] &= ~(DMA_DIR_MASK << DMA_DIR_SHIFT);
		DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SCR] |= (DMA_Cnfg->SrcDestMode << DMA_DIR_SHIFT);

		/* Set priority level */
		DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SCR] &= ~(DMA_PL_MASK << DMA_PL_SHIFT);
		DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SCR] |= (DMA_Cnfg->PriorityLevel << DMA_PL_SHIFT);

		/* Set Peripheral Increment Mode */
		DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SCR] &= ~(DMA_MSIZE_MASK << DMA_PINC_SHIFT);
		DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SCR] |= DMA_Cnfg->PerIncMode << DMA_PINC_SHIFT;

		/* Set Memory Increment Mode*/
		DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SCR] &= ~(DMA_PSIZE_MASK << DMA_MINC_SHIFT);
		DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SCR] |= DMA_Cnfg->MemIncMode << DMA_MINC_SHIFT;


		/* Set peripheral data size */
		DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SCR] &= ~(DMA_PSIZE_MASK <<DMA_PSIZE_SHIFT);
		DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SCR] |= (DMA_Cnfg->PerIncSize <<DMA_PSIZE_SHIFT);


		if(DMA_Cnfg->TransferMode == FIFO_MODE)
		{
			/* Disable direct mode*/
			DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SFCR] |= (1 << DMA_DMDIS_SHIFT);

			/* Set memory data size */
			DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SCR] &= ~(DMA_MSIZE_MASK <<DMA_MSIZE_SHIFT);
			DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SCR] |= (DMA_Cnfg->MemIncSize <<DMA_MSIZE_SHIFT);

			/* Set FIFO threshold*/
			DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SCR] &= ~(DMA_FTH_MASK);
			DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SCR] |= (DMA_Cnfg->FIFOThresh);



		}

		/*Set Callback function */
		if(DMA_Cnfg->DMA_Type == DMA_1)
		{
			GeneralCallBackFun[DMA_Cnfg->StreamNum] = DMA_Cnfg->CallBackFunc;

		}
		else if(DMA_Cnfg->DMA_Type == DMA_2)
		{
			GeneralCallBackFun[(DMA_Cnfg->StreamNum)+DMA_STREAM_NUM] = DMA_Cnfg->CallBackFunc;

		}

		/*Enable Corresponding interrupt*/
		if(DMA_Cnfg->InterruptType == FIFO_ERR)
		{
			/* Enable FIFO interrupt*/
			DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SFCR] |= (1 << DMA_FEIE_SHIFT);
		}
		else
		{
			DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SCR] |= (1 << DMA_Cnfg->InterruptType);
		}


	}

	else
	{
		Local_u8ErrorState = NULL_PTR;
	}

	return Local_u8ErrorState;

}

uint8_t DMA_u8StartTransfer(DMA_Cnfg_T *DMA_Cnfg,uint32_t *Copy_pu32SrcAddress , uint32_t *Copy_pu32DestAddress , uint16_t Copy_u32DataSize)
{
	uint8_t Local_u8ErrorState = OK;

	if((DMA_Cnfg != NULL) && (Copy_pu32DestAddress != NULL) && (Copy_pu32SrcAddress != NULL))
	{
		if (DMA_Cnfg->SrcDestMode == MEM_TO_PERIPH)
		{
			/* Set memory as source address*/
			DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SM0AR] = (uint32_t)Copy_pu32SrcAddress;

			/* Set peripheral as destination address*/
			DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SPAR]  = (uint32_t)Copy_pu32DestAddress;

		}

		else
		{
			/* Set peripheral as source address*/
			DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SPAR]  = (uint32_t)Copy_pu32SrcAddress;

			/* Set memory as destination address*/
			DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SM0AR] = (uint32_t)Copy_pu32DestAddress;

		}

		/* Set data size*/
		DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SNDTR] = 	Copy_u32DataSize;

		/*Clear interrupt status registers*/
		DMA_Arr[DMA_Cnfg->DMA_Type]->ISR[0] = 0x00;
		DMA_Arr[DMA_Cnfg->DMA_Type]->ISR[1] = 0x00;

		/*Enable Stream*/
		DMA_Arr[DMA_Cnfg->DMA_Type]->STR[DMA_Cnfg->StreamNum][SCR] |= 1;


	}

	else
	{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;

}


void DMA1_Stream0_IRQHandler(void)
{
	/*Clear Flag*/

	/* Call Callback Function*/
	GeneralCallBackFun[STREAM0]();
}

void DMA1_Stream1_IRQHandler(void)
{
	/*Clear Flag*/

	/* Call Callback Function*/
	GeneralCallBackFun[STREAM1]();
}
void DMA1_Stream2_IRQHandler(void)
{
	/*Clear Flag*/

	/* Call Callback Function*/
	GeneralCallBackFun[STREAM2]();
}
void DMA1_Stream3_IRQHandler(void)
{
	/*Clear Flag*/

	/* Call Callback Function*/
	GeneralCallBackFun[STREAM3]();
}
void DMA1_Stream4_IRQHandler(void)
{
	/*Clear Flag*/

	/* Call Callback Function*/
	GeneralCallBackFun[STREAM4]();
}
void DMA1_Stream5_IRQHandler(void)
{
	/*Clear Flag*/

	/* Call Callback Function*/
	GeneralCallBackFun[STREAM5]();
}
void DMA1_Stream6_IRQHandler(void)
{
	/*Clear Flag*/

	/* Call Callback Function*/
	GeneralCallBackFun[STREAM6]();
}

void DMA1_Stream7_IRQHandler(void)
{
	/*Clear Flag*/

	/* Call Callback Function*/
	GeneralCallBackFun[STREAM7]();
}

void DMA2_Stream0_IRQHandler(void)
{
	/*Clear Flag*/

	/* Call Callback Function*/
	GeneralCallBackFun[(STREAM0 + DMA_STREAM_NUM)]();
}
void DMA2_Stream1_IRQHandler(void)
{
	/*Clear Flag*/

	/* Call Callback Function*/
	GeneralCallBackFun[STREAM1 + DMA_STREAM_NUM]();
}
void DMA2_Stream2_IRQHandler(void)
{
	/*Clear Flag*/

	/* Call Callback Function*/
	GeneralCallBackFun[STREAM2 + DMA_STREAM_NUM]();
}
void DMA2_Stream3_IRQHandler(void)
{
	/*Clear Flag*/

	/* Call Callback Function*/
	GeneralCallBackFun[STREAM3 + DMA_STREAM_NUM]();
}
void DMA2_Stream4_IRQHandler(void)
{
	/*Clear Flag*/

	/* Call Callback Function*/
	GeneralCallBackFun[STREAM4 + DMA_STREAM_NUM]();
}

void DMA2_Stream5_IRQHandler(void)
{
	/*Clear Flag*/

	/* Call Callback Function*/
	GeneralCallBackFun[STREAM5 + DMA_STREAM_NUM]();
}
void DMA2_Stream6_IRQHandler(void)
{
	/*Clear Flag*/

	/* Call Callback Function*/
	GeneralCallBackFun[STREAM6 + DMA_STREAM_NUM]();
}
void DMA2_Stream7_IRQHandler(void)
{
	/*Clear Flag*/

	/* Call Callback Function*/
	GeneralCallBackFun[STREAM7 + DMA_STREAM_NUM]();
}
