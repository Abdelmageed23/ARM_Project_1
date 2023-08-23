#ifndef STM32F446XX_H_
#define STM32F446XX_H_
/*********************  AHB1 Peripheral Base Addresses   *********************/
#define DMA1_BASE_ADRESS		 0x40026000U
#define DMA2_BASE_ADRESS		 0x40026400U
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
/****************************************************************************/
/******************** Core peripherals Base Addresses *****************/
#define SCB_BASE_ADDRESS      		0xE000E008UL
/******************** APB1 Peripheral Base Addresses *****************/
#define SPI3_BASE_ADDRESS		    0x40003C00UL
#define SPI2_BASE_ADDRESS		    0x40003800UL
/******************** APB2 Peripheral Base Addresses *****************/
#define EXTI_BASE_ADDRESS		    0x40013C00UL
#define SYSCFG_BASE_ADDRESS		  	0x40013800UL
#define SPI4_BASE_ADDRESS		    0x40013400UL
#define SPI1_BASE_ADDRESS		    0x40013000UL
/******************** SPI Register Definition Structure *****************/
typedef struct
{
	volatile uint32_t SPI_CR1;/*All last 16 bits(16:31) of all registers is Reserved*/
	volatile uint32_t SPI_CR2;
	volatile uint32_t SPI_SR;
	volatile uint32_t SPI_DR;
	volatile uint32_t SPI_CRCPR;
	volatile uint32_t SPI_RXCRCR;
  	volatile uint32_t SPI_TXCRCR;
  	volatile uint32_t SPI_I2SCFGR;
  	volatile uint32_t SPI_I2SPR;
}SPI_RegDef_t;
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
/******************** SCB Register Definition Structure *****************/
typedef struct
{
 	volatile uint32_t SCB_ACTLR;
  	volatile uint32_t Reserved1[829];
	volatile uint32_t SCB_CPUID;
  	volatile uint32_t SCB_ICSR;
  	volatile uint32_t SCB_VTOR;
  	volatile uint32_t SCB_AIRCR;
  	volatile uint32_t SCB_SCR;
  	volatile uint32_t SCB_CCR;
  	volatile uint8_t SCB_SHPR[12];
  	volatile uint32_t SCB_SHCSR;
  	volatile uint32_t SCB_CFSR;
  	volatile uint32_t SCB_HFSR;
  	volatile uint32_t Reserved2;
  	volatile uint32_t SCB_MMAR;
  	volatile uint32_t SCB_BFAR;
  	volatile uint32_t SCB_AFSR;
}SCB_RegDef_t;
/******************** SCB Peripheral Definition *****************/
#define SCB	((SCB_RegDef_t*)SCB_BASE_ADDRESS)
/******************** EXTI Peripheral Definition *****************/
#define EXTI	((EXTI_RegDef_t*)EXTI_BASE_ADDRESS)
/******************** EXTI Peripheral Definition *****************/
#define SYSCFG	((SYSCFG_RegDef_t*)SYSCFG_BASE_ADDRESS)
/******************** SPI Peripheral Definition *****************/
#define SPI1	((SPI_RegDef_t*)SPI1_BASE_ADDRESS)
#define SPI2	((SPI_RegDef_t*)SPI2_BASE_ADDRESS)
#define SPI3	((SPI_RegDef_t*)SPI3_BASE_ADDRESS)
#define SPI4	((SPI_RegDef_t*)SPI4_BASE_ADDRESS)
/**************************************************************************************************/

#define NVIC                                  ((NVIC_REG*)NVIC_u32_BASE_ADDRESS)



#endif
