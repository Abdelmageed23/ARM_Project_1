
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
    volatile    uint32_t  CRL ;
    volatile    uint32_t  CRH ;
    volatile    uint32_t  IDR  ;
    volatile    uint32_t  ODR  ;
    volatile    uint32_t  BSRR  ;
    volatile    uint32_t  BRR  ;
    volatile    uint32_t  LCKR  ;

}GPIO_RegDef_T;


#define GPIOA            ((GPIO_RegDef_T  *)GPIOA_BASE_ADDRESS)
#define GPIOB            ((GPIO_RegDef_T  *)GPIOB_BASE_ADDRESS)
#define GPIOC            ((GPIO_RegDef_T  *)GPIOC_BASE_ADDRESS)
#define GPIOD            ((GPIO_RegDef_T  *)GPIOD_BASE_ADDRESS)
#define GPIOE            ((GPIO_RegDef_T  *)GPIOE_BASE_ADDRESS)
#define GPIOF            ((GPIO_RegDef_T  *)GPIOF_BASE_ADDRESS)
#define GPIOG            ((GPIO_RegDef_T  *)GPIOG_BASE_ADDRESS)
/********************************************************************************************************/
/******************** APB1 Peripheral Base Addresses *****************/
#define SPI2_BASE_ADDRESS		0x40003800UL
#define SPI3_BASE_ADDRESS		0x40003C00UL
/******************** APB2 Peripheral Base Addresses *****************/
#define EXTI_BASE_ADDRESS		0x40010400UL
#define SPI1_BASE_ADDRESS		0x40013000UL
/******************** SPI Register Definition Structure *****************/
typedef struct
{
	volatile uint32_t SPI_CR1;
	volatile uint32_t SPI_CR2;
	volatile uint32_t SPI_SR;
	volatile uint32_t SPI_DR;
	volatile uint32_t SPI_CRCPR;
	volatile uint32_t SPI_RXCRCR;
	volatile uint32_t SPI_TXCRCR;
	volatile uint32_t SPI_I2SCFGR;
	volatile uint32_t SPI_I2SPR;
}SPI_Reg_t;
/******************** EXTI Register Definition Structure *****************/
typedef struct
{
	volatile uint32_t EXTI_IMR;
	volatile uint32_t EXTI_EMR;
	volatile uint32_t EXTI_RTSR;
	volatile uint32_t EXTI_FTSR;
	volatile uint32_t EXTI_SWIER;
	volatile uint32_t EXTI_PR;
}EXTI_Reg_t;
/******************** SPI Peripheral Definition *****************/
#define SPI1	((SPI_Reg_t*)SPI1_BASE_ADDRESS)
#define SPI2	((SPI_Reg_t*)SPI2_BASE_ADDRESS)
#define SPI3	((SPI_Reg_t*)SPI3_BASE_ADDRESS)
/******************** EXTI Peripheral Definition *****************/
#define EXTI	((EXTI_Reg_t*)EXTI_BASE_ADDRESS)
/********************************************************************************************************/
#endif
