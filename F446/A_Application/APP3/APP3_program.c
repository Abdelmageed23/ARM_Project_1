/**
 ******************************************************************************
 * @file           : APP3_program.c
 * @author         : Diea Abdeltwab
 * @layer          : APP
 * @brief          :
 * @date           : 28/8/2023
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
#include <string.h>
#include "ERROR_STATE.h"
#include "BIT_MATH.h"
/******************************************************************************/
/************************ MCAL Layer ******************************************/
/******************************************************************************/
#include "GPIO_INTERFACE.h"
#include "SPI_interface.h"
#include "I2C_interface.h"
/******************************************************************************/
/************************ HAL Layer *******************************************/
/******************************************************************************/
#include "RTC_interface.h"
/******************************************************************************/
/************************ APP Layer *******************************************/
/******************************************************************************/
#include "APP3_interface.h"
#include "APP3_private.h"
#include "APP3_config.h"
/********************************************************************************************************************************************/
/**************************************************** Variable ******************************************************************************/
/********************************************************************************************************************************************/
volatile uint8_t Global_u8Pulstemp ;
uint8_t  Global_u8ReceiveTemp=0   ;
/********************************************************************************************************************************************/
/**************************************************** Functions implementations *************************************************************/
/********************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : APP3_init
 * @brief          : initialization App3
 * @param[in]      : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *   initialization SPI  and GPIO-EXTI
 *   Configure from --> APP3_config.h
 ******************************************************************************
 */
void APP3_voidinit (void)
{
	/********************************************************************************************************************************************/
	/**************************************************** SPI Configuration *********************************************************************/
	/********************************************************************************************************************************************/
	GPIO_PinConfig_T MOSI  ={ APP3_SPI_MOSI_PIN , ALTER_FUNC , SPEED_LOW , PUSH_PULL , NO_PULL , AF5 };
	GPIO_u8PinInit(&MOSI);
	GPIO_PinConfig_T MISO  ={ APP3_SPI_MISO_PIN , ALTER_FUNC , SPEED_LOW , PUSH_PULL , NO_PULL , AF5 };
	GPIO_u8PinInit(&MISO);
	GPIO_PinConfig_T SCK   ={ APP3_SPI_SCK_PIN  , ALTER_FUNC , SPEED_LOW , PUSH_PULL , NO_PULL , AF5 };
	GPIO_u8PinInit(&SCK);
	SPIconfig_t SPI_config ={APP3_SPI_INDEX,LEADING_CAPTURE,LEADING_RISING,MASTER,F_CLK_DIV_8,MSB,SELECT_ONE,MANAGMENT_ENABLE,FULL_DUPLEX,FORMAT_8_BIT
				                  ,RX_DMA_DISABLE ,TX_DMA_DISABLE,SS_OUTPUT_DISABLE ,RX_INTERRUPT_MASKED,TX_INTERRUPT_MASKED };
	MSPI_u8SetConfiguration(&SPI_config);
	GPIO_PinConfig_T NSS  ={APP3_GPIO_NSS_PIN , OUTPUT , SPEED_LOW , PUSH_PULL , NO_PULL , AF0};
	GPIO_u8PinInit(&NSS);
	GPIO_u8SetPinValue(APP3_GPIO_NSS_PIN, PIN_HIGH);
	/********************************************************************************************************************************************/
	/**************************************************** GPIO-EXTI Configuration ***************************************************************/
	/********************************************************************************************************************************************/
	GPIO_PinConfig_T AlarmNotification ={ APP3_GPIO_TO_EXTI_PIN , OUTPUT , SPEED_LOW , PUSH_PULL , NO_PULL , AF0 };
	GPIO_u8PinInit(&AlarmNotification);
	GPIO_u8SetPinValue(APP3_GPIO_TO_EXTI_PIN, PIN_LOW);
	/********************************************************************************************************************************************/
	/********************************************************************************************************************************************/
	/********************************************************************************************************************************************/
}
/**
 ******************************************************************************
 * @fn             : APP3_voidTurnOnGreenLed
 * @brief          : Turn On Green Led on Panda Kit
 * @param[in]      : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *   Turn Led By Sending '!' With SPI
 *
 ******************************************************************************
 */
void APP3_voidTurnOnGreenLed(void)
{
	GPIO_u8SetPinValue(APP3_GPIO_NSS_PIN, PIN_LOW);
	MSPI_u8SendReceiveSynch(APP3_SPI_INDEX,APP3_SPI_TRIGGER_GRN_LED,&Global_u8ReceiveTemp);
	GPIO_u8SetPinValue(APP3_GPIO_NSS_PIN, PIN_HIGH);
}
/**
 ******************************************************************************
 * @fn             : APP3_voidTurnOnRedLed
 * @brief          : Turn On Red Led on Panda Kit
 * @param[in]      : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *   Turn Led By Sending '~' With SPI
 *
 ******************************************************************************
 */
void APP3_voidTurnOnRedLed(void)
{
	GPIO_u8SetPinValue(APP3_GPIO_NSS_PIN, PIN_LOW);
	MSPI_u8SendReceiveSynch(APP3_SPI_INDEX,APP3_SPI_TRIGGER_RED_LED,&Global_u8ReceiveTemp);
	GPIO_u8SetPinValue(APP3_GPIO_NSS_PIN, PIN_HIGH);
}
/**
 ******************************************************************************
 * @fn             : APP3_voidAlarmCompareMatch
 * @brief          : Alarm Compare Match
 * @param[in]      : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *   Send Pulse to Generate EXTI to Turn on Buzzer and Blue Led
 *
 ******************************************************************************
 */
void APP3_voidAlarmCompareMatch(void)
{
	GPIO_u8SetPinValue(APP3_GPIO_TO_EXTI_PIN, PIN_HIGH);
	for (uint32_t Local_u8Counter =0 ; Local_u8Counter<=100;Local_u8Counter++)
	{
		Global_u8Pulstemp=Local_u8Counter;
	}
	GPIO_u8SetPinValue(APP3_GPIO_TO_EXTI_PIN, PIN_LOW);
}
/**
 ******************************************************************************
 * @fn             : APP3_voidDisplayTime
 * @brief          : Read Time From RTC then Display it on LCD on Panda Kit
 * @param[in]      : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *   Display Time on LCD By sending '@'
 *
 ******************************************************************************
 */
void APP3_voidDisplayTime(void)
{
	RTC_time_t   GetTime;
	HRTC_voidGetCurrentTime(&GetTime);

	GPIO_u8SetPinValue(APP3_GPIO_NSS_PIN, PIN_LOW);
	MSPI_u8SendReceiveSynch(APP3_SPI_INDEX,APP3_SPI_TRIGGER_TIME,&Global_u8ReceiveTemp);
	GPIO_u8SetPinValue(APP3_GPIO_NSS_PIN, PIN_HIGH);

	GPIO_u8SetPinValue(APP3_GPIO_NSS_PIN, PIN_LOW);
	MSPI_u8TransmitArraySynch(APP3_SPI_INDEX,TimeToString(&GetTime));
	GPIO_u8SetPinValue(APP3_GPIO_NSS_PIN, PIN_HIGH);
}
/**
 ******************************************************************************
 * @fn             : APP3_voidDisplayDate
 * @brief          : Read Date From RTC then Display it on LCD on Panda Kit
 * @param[in]      : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *   Display Date on LCD By sending '#'
 *
 ******************************************************************************
 */
void APP3_voidDisplayDate(void)
{
	RTC_date_t   GetDate;
	HRTC_voidGetCurrentDate(&GetDate);

	GPIO_u8SetPinValue(APP3_GPIO_NSS_PIN, PIN_LOW);
	MSPI_u8SendReceiveSynch(APP3_SPI_INDEX,APP3_SPI_TRIGGER_DATE,&Global_u8ReceiveTemp);
	GPIO_u8SetPinValue(APP3_GPIO_NSS_PIN, PIN_HIGH);

	GPIO_u8SetPinValue(APP3_GPIO_NSS_PIN, PIN_LOW);
	MSPI_u8TransmitArraySynch(APP3_SPI_INDEX,DataToString(&GetDate));
	GPIO_u8SetPinValue(APP3_GPIO_NSS_PIN, PIN_HIGH);
}
/**
 ******************************************************************************
 * @fn             : APP3_voidSendAlarmName
 * @brief          : Display Alarm On LCD on Panda Kit
 * @param[in]      : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *   Display Alarm Name on LCD By sending '$'
 *
 ******************************************************************************
 */
void APP3_voidSendAlarmName(uint8_t *AlarmName)
{
	GPIO_u8SetPinValue(APP3_GPIO_NSS_PIN, PIN_LOW);
	MSPI_u8SendReceiveSynch(APP3_SPI_INDEX,APP3_SPI_TRIGGER_ALARM,&Global_u8ReceiveTemp);
	GPIO_u8SetPinValue(APP3_GPIO_NSS_PIN, PIN_HIGH);

	GPIO_u8SetPinValue(APP3_GPIO_NSS_PIN, PIN_LOW);
	MSPI_u8TransmitArraySynch(APP3_SPI_INDEX,AlarmName);
	GPIO_u8SetPinValue(APP3_GPIO_NSS_PIN, PIN_HIGH);
}
/********************************************************************************************************************************************/
/**************************************************** Static Function ***********************************************************************/
/********************************************************************************************************************************************/
static void NumberToString (uint8_t Copy_u8Number , uint8_t* Copy_pu8String )
{
	if(Copy_u8Number <10)
	{
		Copy_pu8String[0]='0';
		Copy_pu8String[1]=Copy_u8Number + 48;
	}
	else if (Copy_u8Number >10 && Copy_u8Number <99 )
	{
		Copy_pu8String[0]= (Copy_u8Number / 10 )+ 48;
		Copy_pu8String[1]= (Copy_u8Number % 10 )+ 48;
	}
}
static uint8_t *DataToString(RTC_date_t *Copy_Data)
{
	static uint8_t Local_Au8String[9];
	NumberToString(Copy_Data->date, &Local_Au8String[0]);
	Local_Au8String[2]='/';
	NumberToString(Copy_Data->month,&Local_Au8String[3]);
	Local_Au8String[5]='/';
	NumberToString(Copy_Data->year ,&Local_Au8String[6]);
	Local_Au8String[8]='\0';
	return Local_Au8String;
}
static uint8_t *TimeToString(RTC_time_t *Copy_Time)
{
	static uint8_t Local_Au8String[9];
	NumberToString(Copy_Time->hours  ,&Local_Au8String[0]);
	Local_Au8String[2]=':';
	NumberToString(Copy_Time->minutes,&Local_Au8String[3]);
	Local_Au8String[5]=':';
	//NumberToString(Copy_Time->seconds,&Local_Au8String[6]);
	Local_Au8String[6]='0';
	Local_Au8String[7]='0';
	Local_Au8String[8]='\0';
	return Local_Au8String;
}
/********************************************************************************************************************************************/
/********************************************************************************************************************************************/
/********************************************************************************************************************************************/

