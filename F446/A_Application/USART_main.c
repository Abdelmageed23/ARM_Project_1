

/******************************************************************************/
/************************ LIB Layer *******************************************/
/******************************************************************************/
#include <stdint.h>
/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
//#include "RCC_INTERFACE.h"
//#include "GPIO_INTERFACE.h"
//#include "STK_interface.h"
//#include "SCB_interface.h"
//#include "NVIC_interface.h"
//#include "SYSCFG_interface.h"
//#include "EXTI_interface.h"
//#include "USART_interface.h"
//#include "SPI_interface.h"
/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
int main(void)
{

	uint8_t a ;
	/**************** Init System Clock and peripheral clock **************************************************/
	//MRCC_u8SetClockState(HSI,ENABLE);
	//MRCC_u8SetSystemClock(HSI);
	//MRCC_u8AHB1PeripheralsClockState(PER_GPIOA,ENABLE);
	//MRCC_u8PeripheralsClockState(APB1,PER_UART2,ENABLE);
	/**************** Nucleo Led  *****************************************************************************/
	//PinConfig_t LED ={PORTA , PIN5 , OUTPUT , SPEED_LOW , PUSH_PULL , NO_PULL , AF0};
	//MGPIO_u8PinInit(&LED);
	//MGPIO_u8TogPinValue(PORTA, PIN5);

	/**************** RX and TX --> Configuration  ALTERNATE_FUNCTION  *****************************************/
	PinConfig_t PIN1 ={PORTA , PIN2 , ALTERNATE_FUNCTION , SPEED_LOW , PUSH_PULL , NO_PULL , AF7};
	//MGPIO_u8PinInit(&PIN1);
	PinConfig_t PIN2 ={PORTA , PIN3 , ALTERNATE_FUNCTION , SPEED_LOW , PUSH_PULL , NO_PULL , AF7};
	//MGPIO_u8PinInit(&PIN2);
	/**************** UART 2 Configuration *********************************************************************/
	USARTconfig_t UART = {USART_2,RECEIVER_ENABLE,TRANSMITTER_ENABLE,RXNE_INTERRUPT_DISABLE
						,TRANSMITTER_COMPLETE_INTERRUPT_DISABLE,TXE_INTERRUPT_DISABLE
						,PARITY_SELECTION_EVEN,PARITY_CONTROL_DISABLE,DATA_8_BITS,BY_16,ONE_BIT
						,INHIBITED,DMAR_DISABLE,DMAT_DISABLE};
	MUSART_u8SetConfiguration(&UART);

	/*************************************************************************************************************/

	MUSART_u8TransmitArraySynch(USART_2, (uint8_t *) "USART Test");
	for(;;)
	{

		MUSART_u8ReceiveCharSynch(USART_2,&a);
		if (a == 'a')
		{
			MGPIO_u8TogPinValue(PORTA, PIN5);
		}
		MUSART_u8TransmitCharSynch(USART_2,a);

	}
}



