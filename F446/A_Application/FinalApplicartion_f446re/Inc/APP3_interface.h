/**
 ******************************************************************************
 * @file           : APP3_interface.h
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
#ifndef APP3_INTERFACE_H
#define APP3_INTERFACE_H




/*************************************************************************************************************************************/
/********************************************************* Functions Prototype *******************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : APP3_init
 * @brief          : initialization App3
 * @param[in]      : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *   initialization SPI and GPIO-EXTI
 *   Configure from --> APP3_config.h
 ******************************************************************************
 */
void APP3_voidinit (void);
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
void APP3_voidTurnOnGreenLed(void);
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
void APP3_voidTurnOnRedLed(void);

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
void APP3_voidDisplayTime(RTC_time_t *Copy_u8Time);
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
void APP3_voidDisplayDate(RTC_date_t *Copy_u8Date);
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
 * Used in APP2
 ******************************************************************************
 */
void APP3_voidAlarmCompareMatch(uint8_t *Copy_pu8AlrmName);
/**
 ******************************************************************************
 * @fn             : APP3_voidSendAlarmName
 * @brief          : Display Alarm On LCD on Panda Kit
 * @param[in]      : AlarmName --> Set Alarm Name
 * @retval         : void
 ******************************************************************************
 * @attention
 *   Display Alarm Name on LCD By sending '$'
 *
 *   Used in APP2
 ******************************************************************************
 */
void APP3_voidSendAlarmName(uint8_t *AlarmName);


/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/

#endif 
