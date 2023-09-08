/*
 * APP_2_private.h
 *
 *  Created on: 29 Aug 2023
 *      Author: kareem
 */

#ifndef APP_2_PRIVATE_H_
#define APP_2_PRIVATE_H_
#define NUMBER_OF_ALARMS        5U
#define ALARM_NOT_DEFINED       0U
#define ALAREM_DFINED           1U
#define MAX_SYSTICK_OF_COUNT    10U
#define SYSTICK_RELOAD_VALUE    2000000UL

void APP2_SysTick_ISR(void);


#endif /* APP_2_PRIVATE_H_ */
