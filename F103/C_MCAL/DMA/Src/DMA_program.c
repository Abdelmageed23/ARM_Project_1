#include <stdint.h>
#include "ERROR_STATE.h"

#include "stm32f103xx.h"

#include "DMA_private.h"
#include "DMA_interface.h"

static DMA_RegDef_T *DMA_Arr[2] = {DMA1 , DMA2};

static void (*GeneralCallBackFun[DMA_TOT_IRQ_NUM])(void) = {NULL};

uint8_t DMA_u8Init(DMA_Cnfg_T * DMA_Cnfg)
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;

	if(DMA_Cnfg != NULL)
	{

		/* Set data transfer direction*/
		if(DMA_Cnfg->SrcDestMode == MEM_TO_MEM )
		{
			DMA_Arr[DMA_Cnfg->DMA_Type]->CHNR[DMA_Cnfg->ChannelNum][CCR] |= 1 << DMA_MEM2MEM_SHIFT;
		}
		else
		{
			DMA_Arr[DMA_Cnfg->DMA_Type]->CHNR[DMA_Cnfg->ChannelNum][CCR] |= (DMA_Cnfg->SrcDestMode << DMA_DIR_SHIFT);

		}

		/* Set priority level */
		DMA_Arr[DMA_Cnfg->DMA_Type]->CHNR[DMA_Cnfg->ChannelNum][CCR] |= (DMA_Cnfg->PriorityLevel << DMA_PL_SHIFT);

		/* Set Peripheral Increment Mode */
		DMA_Arr[DMA_Cnfg->DMA_Type]->CHNR[DMA_Cnfg->ChannelNum][CCR] |= DMA_Cnfg->PerIncMode << DMA_PINC_SHIFT;

		/* Set Memory Increment Mode*/
		DMA_Arr[DMA_Cnfg->DMA_Type]->CHNR[DMA_Cnfg->ChannelNum][CCR] |= DMA_Cnfg->MemIncMode << DMA_MINC_SHIFT;


		/* Set peripheral data size */
		DMA_Arr[DMA_Cnfg->DMA_Type]->CHNR[DMA_Cnfg->ChannelNum][CCR] |= (DMA_Cnfg->PerIncSize << DMA_PSIZE_SHIFT);

		/* Set memory data size */
		DMA_Arr[DMA_Cnfg->DMA_Type]->CHNR[DMA_Cnfg->ChannelNum][CCR] |= (DMA_Cnfg->MemIncSize << DMA_MSIZE_SHIFT);


		/*Set Callback function */
		if(DMA_Cnfg->DMA_Type == DMA_1)
		{
			GeneralCallBackFun[DMA_Cnfg->ChannelNum] = DMA_Cnfg->CallBackFunc;

		}
		else if(DMA_Cnfg->DMA_Type == DMA_2)
		{
			GeneralCallBackFun[(DMA_Cnfg->ChannelNum)+DMA1_IRQ_NUM] = DMA_Cnfg->CallBackFunc;

		}

		/*Enable Corresponding interrupt*/
		DMA_Arr[DMA_Cnfg->DMA_Type]->CHNR[DMA_Cnfg->ChannelNum][CCR] |= (1 << DMA_Cnfg->InterruptType);


	}

	else
	{
		Local_u8ErrorState = ERROR_STATE_NULL_PTR;
	}

	return Local_u8ErrorState;

}

uint8_t DMA_u8StartTransfer(DMA_Cnfg_T *DMA_Cnfg,uint32_t *Copy_pu32SrcAddress , uint32_t *Copy_pu32DestAddress , uint16_t Copy_u16DataSize)
{
	uint8_t Local_u8ErrorState = ERROR_STATE_OK;

	if((DMA_Cnfg != NULL) && (Copy_pu32DestAddress != NULL) && (Copy_pu32SrcAddress != NULL))
	{
		if (DMA_Cnfg->SrcDestMode == MEM_TO_PERIPH)
		{
			/* Set memory as source address*/
			DMA_Arr[DMA_Cnfg->DMA_Type]->CHNR[DMA_Cnfg->ChannelNum][CMAR] = (uint32_t)Copy_pu32SrcAddress;

			/* Set peripheral as destination address*/
			DMA_Arr[DMA_Cnfg->DMA_Type]->CHNR[DMA_Cnfg->ChannelNum][CPAR]  = (uint32_t)Copy_pu32DestAddress;

		}

		else
		{
			/* Set peripheral as source address*/
			DMA_Arr[DMA_Cnfg->DMA_Type]->CHNR[DMA_Cnfg->ChannelNum][CPAR]  = (uint32_t)Copy_pu32SrcAddress;

			/* Set memory as destination address*/
			DMA_Arr[DMA_Cnfg->DMA_Type]->CHNR[DMA_Cnfg->ChannelNum][CMAR] = (uint32_t)Copy_pu32DestAddress;

		}

		/* Set data size*/
		DMA_Arr[DMA_Cnfg->DMA_Type]->CHNR[DMA_Cnfg->ChannelNum][CNDTR] = 	Copy_u16DataSize;


		/*Enable Stream*/
		DMA_Arr[DMA_Cnfg->DMA_Type]->CHNR[DMA_Cnfg->ChannelNum][CCR] |= 1;


	}

	else
	{
		Local_u8ErrorState = ERROR_STATE_NOK;
	}

	return Local_u8ErrorState;

}


void DMA1_Channel1_IRQHandler(void)
{
	DMA1->IFCR = DMA_ICF_MASK << DMA_ICF_CHANNEL1_SHIFT;

	GeneralCallBackFun[CHANNEL1]();
}
void DMA1_Channel2_IRQHandler(void)
{
	DMA1->IFCR = DMA_ICF_MASK << DMA_ICF_CHANNEL2_SHIFT;

	GeneralCallBackFun[CHANNEL2]();

}
void DMA1_Channel3_IRQHandler(void)
{
	DMA1->IFCR = DMA_ICF_MASK << DMA_ICF_CHANNEL3_SHIFT;

	GeneralCallBackFun[CHANNEL3]();

}
void DMA1_Channel4_IRQHandler(void)
{
	DMA1->IFCR = DMA_ICF_MASK << DMA_ICF_CHANNEL4_SHIFT;

	GeneralCallBackFun[CHANNEL4]();
}
void DMA1_Channel5_IRQHandler(void)
{
	DMA1->IFCR = DMA_ICF_MASK << DMA_ICF_CHANNEL5_SHIFT;

	GeneralCallBackFun[CHANNEL5]();
}
void DMA1_Channel6_IRQHandler(void)
{
	DMA1->IFCR = DMA_ICF_MASK << DMA_ICF_CHANNEL6_SHIFT;

	GeneralCallBackFun[CHANNEL6]();
}
void DMA1_Channel7_IRQHandler(void)
{
	DMA1->IFCR = DMA_ICF_MASK << DMA_ICF_CHANNEL7_SHIFT;

	GeneralCallBackFun[CHANNEL7]();
}

void DMA2_Channel1_IRQHandler(void)
{
	DMA2->IFCR = DMA_ICF_MASK << DMA_ICF_CHANNEL1_SHIFT;

	GeneralCallBackFun[CHANNEL1+DMA1_IRQ_NUM]();
}
void DMA2_Channel2_IRQHandler(void)
{
	DMA2->IFCR = DMA_ICF_MASK << DMA_ICF_CHANNEL2_SHIFT;

	GeneralCallBackFun[CHANNEL2+DMA1_IRQ_NUM]();
}
void DMA2_Channel3_IRQHandler(void)
{
	DMA2->IFCR = DMA_ICF_MASK << DMA_ICF_CHANNEL3_SHIFT;

	GeneralCallBackFun[CHANNEL3+DMA1_IRQ_NUM]();
}
void DMA2_Channel4_5_IRQHandler(void)
{
	if(((DMA2->ISR >> DMA_GIF5_SHIFT)&1) == DMA_FLAG_RISED)
	{
		DMA2->IFCR = DMA_ICF_MASK << DMA_ICF_CHANNEL4_SHIFT;

		GeneralCallBackFun[CHANNEL4+DMA1_IRQ_NUM]();
	}
	else
	{
		DMA2->IFCR = DMA_ICF_MASK << DMA_ICF_CHANNEL5_SHIFT;

		GeneralCallBackFun[CHANNEL5+DMA1_IRQ_NUM]();
	}

}
