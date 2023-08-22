
#ifndef STM32F103xx_h
#define STM32F103xx_h

/************************************************************************************************/
/********************************* SYSTICK Registers ********************************************/
/************************************************************************************************/
#define STK_BASE_ADDRESS                               0xE000E010U

typedef struct
{
	volatile uint32_t CTRL  ;
	volatile uint32_t LOAD  ;
	volatile uint32_t VAL   ;
	volatile uint32_t CALIB ;
}STK_REG;

#define STK                                  ((STK_REG*)STK_BASE_ADDRESS)

/************************************************************************************************/
/******************************** NVIC Registers ************************************************/
/************************************************************************************************/
#define NVIC_BASE_ADDRESS                               0xE000E100U

typedef struct
{
	volatile uint32_t ISER[8];		/*Interrupt set-enable register*/
	uint32_t Reserved1[24];
	volatile uint32_t ICER[8];		/*Interrupt clear-enable register*/
	uint32_t Reserved[24];
	volatile uint32_t ISPR[8];		/*Interrupt set-pending register*/
	uint32_t Reserved2[24];
	volatile uint32_t ICPR[8];		/*Interrupt clear-pending register*/
	uint32_t Reserved4[24];
	volatile uint32_t IABR[8];		/*Interrupt active bit register*/
	uint32_t Reserved3[32];
	volatile uint8_t IPR[240];		/*Interrupt priority register*/
}NVIC_REG;

#define NVIC                                  ((NVIC_REG*)NVIC_BASE_ADDRESS)

/************************************************************************************************/
/******************************** GPIO Registers ************************************************/
/************************************************************************************************/
#define GPIOA_BASE_ADDRESS       	0x40010800U
#define GPIOB_BASE_ADDRESS       	0x40010C00U
#define GPIOC_BASE_ADDRESS       	0x40011000U
#define GPIOD_BASE_ADDRESS       	0x40011400U
#define GPIOE_BASE_ADDRESS       	0x40011800U
#define GPIOF_BASE_ADDRESS       	0x40011C00U
#define GPIOG_BASE_ADDRESS       	0x40012000U


typedef struct
{
    volatile uint32_t CR[2];
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;

}GPIO_RegDef_T;

#define GPIOA            ((GPIO_RegDef_T  *)GPIOA_BASE_ADDRESS)
#define GPIOB            ((GPIO_RegDef_T  *)GPIOB_BASE_ADDRESS)
#define GPIOC            ((GPIO_RegDef_T  *)GPIOC_BASE_ADDRESS)
#define GPIOD            ((GPIO_RegDef_T  *)GPIOD_BASE_ADDRESS)
#define GPIOE            ((GPIO_RegDef_T  *)GPIOE_BASE_ADDRESS)
#define GPIOF            ((GPIO_RegDef_T  *)GPIOF_BASE_ADDRESS)
#define GPIOG            ((GPIO_RegDef_T  *)GPIOG_BASE_ADDRESS)

#endif
