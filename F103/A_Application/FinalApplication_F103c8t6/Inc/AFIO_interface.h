#ifndef AFIO_INTERFACE_H_
#define AFIO_INTERFACE_H_


typedef enum
{
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_D,
	PORT_E,
	PORT_F,
	PORT_G

}AFIO_Port_T;

typedef enum
{
	EXTI0,
	EXTI1,
	EXTI2,
	EXTI3,
	EXTI4,
	EXTI5,
	EXTI6,
	EXTI7,
	EXTI8,
	EXTI9,
	EXTI10,
	EXTI11,
	EXTI12,
	EXTI13,
	EXTI14,
	EXTI15,

}AFIO_LineNum_T;

void AFIO_voidSetEXTIPort(AFIO_LineNum_T Copy_LineNum, AFIO_Port_T Copy_Port);

#endif
