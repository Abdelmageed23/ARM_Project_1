/**
 ******************************************************************************
 * @file           : NVIC_interface.h
 * @author         : Diea Abdeltwab
 * @layer          : MCAL (Core Peripherals )
 * @brief          : Version 1 For STM32F446 Drivers
 * @date           : 1/8/2023
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
#ifndef  NVIC_INTERFACE_H
#define  NVIC_INTERFACE_H
/******************************************************************************/
/*************************** @IntNumber_t *************************************/
/******************************************************************************/
typedef enum
{
           NVIC_WWDG                           =0,
           NVIC_PVD                              ,
           NVIC_TAMPER                           ,
           NVIC_RTC                              ,
           NVIC_FLASH                            ,
           NVIC_RCC                              ,
           NVIC_EXTI0                            ,
           NVIC_EXTI1                            ,
           NVIC_EXTI2                            ,
           NVIC_EXTI3                            ,
           NVIC_EXTI4                            ,
           NVIC_DMA1_Stream0                     ,
           NVIC_DMA1_Stream1                     ,
           NVIC_DMA1_Stream2                     ,
           NVIC_DMA1_Stream3                     ,
           NVIC_DMA1_Stream4                     ,
           NVIC_DMA1_Stream5                     ,
           NVIC_DMA1_Stream6                     ,
		   NVIC_ADC                              ,
           NVIC_CAN_TX                           ,
           NVIC_CAN_RX0                          ,
           NVIC_CAN1_RX1                         ,
           NVIC_CAN1_SCE                         ,
           NVIC_EXTI9_5                          ,
           NVIC_TIM1_BRK_TIM9                    ,
           NVIC_TIM1_UP_TIM10                    ,
           NVIC_TIM1_TRG_COM_TIM11               ,
           NVIC_TIM1_CC                          ,
           NVIC_TIM2                             ,
           NVIC_TIM3                             ,
           NVIC_TIM4                             ,
           NVIC_I2C1_EV                          ,
           NVIC_I2C1_ER                          ,
           NVIC_I2C2_EV                          ,
           NVIC_I2C2_ER                          ,
           NVIC_SPI1                             ,
           NVIC_SPI2                             ,
           NVIC_USART1                           ,
           NVIC_USART2                           ,
           NVIC_USART3                           ,
           NVIC_EXTI15_10                        ,
           NVIC_RTC_Alarm                        ,
           NVIC_OTG_FS_WKUP                      ,
           NVIC_TIM8_BRK_TIM12                   ,
           NVIC_TIM8_UP_TIM13                    ,
           NVIC_TIM8_TRG_COM_TIM14               ,
           NVIC_TIM8_CC                          ,
           NVIC_DMA1_Stream7                     ,
           NVIC_FMC                              ,
           NVIC_SDIO                             ,
           NVIC_TIM5                             ,
           NVIC_SPI3                             ,
           NVIC_UART4                            ,
           NVIC_UART5                            ,
           NVIC_TIM66_DAC                        ,
           NVIC_TIM7                             ,
           NVIC_DMA2_Stream0                     ,
		   NVIC_DMA2_Stream1                     ,
		   NVIC_DMA2_Stream2                     ,
		   NVIC_DMA2_Stream3                     ,
		   NVIC_DMA2_Stream4                     ,
		   NVIC_CAN2_TX                       =63,
		   NVIC_CAN2_RX0                         ,
		   NVIC_CAN2_RX1                         ,
		   NVIC_CAN2_SCE                         ,
		   NVIC_OTG_FS                           ,
		   NVIC_DMA2_Stream5                     ,
		   NVIC_DMA2_Stream6                     ,
		   NVIC_DMA2_Stream7                     ,
		   NVIC_USART6                           ,
		   NVIC_I2C3_EV                          ,
		   NVIC_I2C3_ER                          ,
		   NVIC_OTG_HS_EP1_OUT                   ,
		   NVIC_OTG_HS_EP1_IN                    ,
		   NVIC_OTG_HS_WKUP                      ,
		   NVIC_OTG_HS                           ,
		   NVIC_DCMI                             ,
		   NVIC_FPU                           =81,
		   NVIC_SPI4                          =84,
		   NVIC_SAI1                          =87,
		   NVIC_SAI2                          =91,
		   NVIC_QuadSPI                          ,
		   NVIC_HDMI_CEC                         ,
		   NVIC_SPDIF_Rx                         ,
		   NVIC_FMPI2C1                          ,
		   NVIC_FMPI2C1_error

}IntNumber_t;
/*************************************************************************************************************************************/
/********************************************************* Functions Prototype *******************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : MNVIC_u8EnableInterrupt
 * @brief          : Enable Interrupt
 * @param[in]      : Copy_IntNumber --> get option from @IntNumber_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MNVIC_u8EnableInterrupt    ( IntNumber_t Copy_IntNumber );
/**
 ******************************************************************************
 * @fn             : MNVIC_u8DisableInterrupt
 * @brief          : Disable Interrupt
 * @param[in]      : Copy_IntNumber --> get option from @IntNumber_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MNVIC_u8DisableInterrupt   ( IntNumber_t Copy_IntNumber );
/**
 ******************************************************************************
 * @fn             : MNVIC_u8SetPendingFlag
 * @brief          : Set Pending Flag
 * @param[in]      : Copy_IntNumber --> get option from @IntNumber_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MNVIC_u8SetPendingFlag     ( IntNumber_t Copy_IntNumber );
/**
 ******************************************************************************
 * @fn             : MNVIC_u8ClearPendingFlag
 * @brief          : Clear Pending Flag
 * @param[in]      : Copy_IntNumber --> get option from @IntNumber_t  enum
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MNVIC_u8ClearPendingFlag   ( IntNumber_t Copy_IntNumber );
/**
 ******************************************************************************
 * @fn             : MNVIC_u8ReadActiveFlag
 * @brief          : Read Active Flag
 * @param[in]      : Copy_IntNumber --> get option from @IntNumber_t  enum
 * @param[OUT]     : Copy_pu8StatusActiveFlag --> get Active Flag
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MNVIC_u8ReadActiveFlag     ( IntNumber_t Copy_IntNumber ,  uint8_t* Copy_pu8StatusActiveFlag );
/**
 ******************************************************************************
 * @fn             : MNVIC_u8SetPriority
 * @brief          : Read Active Flag
 * @param[in]      : Copy_IntNumber --> get option from @IntNumber_t  enum
 * @param[in]      : Copy_u8GroubSubPriority --> Set Group Sub Priority
 * @retval         : ErrorState
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
uint8_t   MNVIC_u8SetPriority ( IntNumber_t Copy_IntNumber ,  uint8_t Copy_u8GroubSubPriority );

/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
#endif
