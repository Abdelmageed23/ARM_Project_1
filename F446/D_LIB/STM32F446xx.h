#ifndef STM32F446XX_H_
#define STM32F446XX_H_
/*********************  AHB1 Peripheral Base Addresses   *********************/
#define DMA1_BASE_ADRESS		 0x40026000U
#define DMA2_BASE_ADRESS		 0x40026400U

/******************** APB2 Peripheral Base Addresses *****************/
#define EXTI_BASE_ADDRESS		    0x40013C00UL
#define SYSCFG_BASE_ADDRESS		  	0x40013800UL
/******************** EXTI Register Definition Structure *****************/
typedef struct
{
	volatile uint32_t EXTI_IMR;
	volatile uint32_t EXTI_EMR;
	volatile uint32_t EXTI_RTSR;
	volatile uint32_t EXTI_FTSR;
	volatile uint32_t EXTI_SWIER;
	volatile uint32_t EXTI_PR;
}EXTI_RegDef_t;
/******************** SYSCFG Register Definition Structure *****************/
typedef struct
{
	volatile uint32_t SYSCFG_MEMRMP;
	volatile uint32_t SYSCFG_PMC;
	volatile uint32_t SYSCFG_EXTICR[4];
  volatile uint32_t Reserved1[2];
	volatile uint32_t SYSCFG_CMPCR;
  volatile uint32_t Reserved2[2];
	volatile uint32_t SYSCFG_CFGR;
}SYSCFG_RegDef_t;

/*********************  DMA Register Definition Structure   *********************/
typedef enum
{
	SCR,
	SNDTR,
	SPAR,
	SM0AR,
	SM1AR,
	SFCR,


}DMA_Stream_Reg_T;

typedef struct
{
	volatile uint32_t ISR[2];
	volatile uint32_t IFCR[2];
	volatile uint32_t STR[8][6];

}DMA_RegDef_T;

/*********************  DMA Register Definition    *********************/
#define DMA1					((DMA_RegDef_T *)DMA1_BASE_ADRESS)
#define DMA2					((DMA_RegDef_T *)DMA2_BASE_ADRESS)
/************************************************************************************************/
/********************************* SYSTICK Registers ********************************************/
/************************************************************************************************/
#define STK_BASE_ADDRESS                                  0xE000E010UL


typedef struct
{
	volatile uint32_t CTRL;
	volatile uint32_t LOAD;
	volatile uint32_t VAL ;
	volatile uint32_t CALIB;
}STK_REG;

#define STK                                  ((STK_REG*)STK_BASE_ADDRESS)

/************************************************************************************************/
/******************************** NVIC Registers ************************************************/
/************************************************************************************************/
#define NVIC_u32_BASE_ADDRESS                               0xE000E100UL

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

#define NVIC                                  ((NVIC_REG*)NVIC_u32_BASE_ADDRESS)
/******************** EXTI Peripheral Definition *****************/
#define EXTI	((EXTI_RegDef_t*)EXTI_BASE_ADDRESS)
/******************** EXTI Peripheral Definition *****************/
#define SYSCFG	((SYSCFG_RegDef_t*)SYSCFG_BASE_ADDRESS)



#endif
