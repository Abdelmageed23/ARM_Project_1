/*
 * SCB_interface.h
 *
 *  Created on: 14 Jul 2023
 *      Author: kareem
 */

#ifndef SCB_INTERFACE_H_
#define SCB_INTERFACE_H_
typedef enum{
    SCB_MemManage = 0U,
    SCB_BusFault,
    SCB_UsageFault,
    SCB_SVCall =7U,
    SCB_SVCal =10U,
    SCB_SysTick,
}SCB_IQR_ty;
void SCB_voidSetPriorityGroup(uint8_t Copy_u8PriorityGroup);
uint8_t SCB_u8setIQRprionty(SCB_IQR_ty perpheral,uint8_t prority);
uint8_t SCB_u8EnableFaultInterrupt(SCB_IQR_ty perpheral);
uint8_t SCB_u8DisableFaultInterrupt(SCB_IQR_ty perpheral);
#endif /* SCB_INTERFACE_H_ */
