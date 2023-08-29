
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
/************************************************************************************************/
/******************************** USART Registers ***********************************************/
/************************************************************************************************/
#define USART1_u32_BASE_ADDRESS                                0x40013800U
#define USART2_u32_BASE_ADDRESS                                0x40004400U
#define USART3_u32_BASE_ADDRESS                                0x40004800U
#define  UART4_u32_BASE_ADDRESS                                0x40004C00U
#define  UART5_u32_BASE_ADDRESS                                0x40005000U
 typedef	struct
{
	volatile uint32_t SR     ;
	volatile uint32_t DR     ;
	volatile uint32_t BRR      ;
	volatile uint32_t CR1      ;
	volatile uint32_t CR2   ;
	volatile uint32_t CR3  ;
	volatile uint32_t GTPR  ;

} USART_REG ;

#define  USART1                     ( (  USART_REG *) USART1_u32_BASE_ADDRESS )
#define  USART2                     ( (  USART_REG *) USART2_u32_BASE_ADDRESS )
#define  USART3                     ( (  USART_REG *) USART3_u32_BASE_ADDRESS )
#define   UART4                     ( (  USART_REG *) UART4_u32_BASE_ADDRESS  )
#define   UART5                     ( (  USART_REG *) UART5_u32_BASE_ADDRESS  )


/******************** RCC Register Definition Structure *****************/
#define RCC_BASE_ADDRESS			0x40021000U
typedef struct
{
	uint32_t RCC_CR;
	uint32_t RCC_CFGR;
	uint32_t RCC_CIR;
	uint32_t RCC_APB2STR;
	uint32_t RCC_APB1STR;
	uint32_t RCC_AHBENR;
	uint32_t RCC_APB2ENR;
	uint32_t RCC_APB1ENR;
	uint32_t RCC_BDCR;
	uint32_t RCC_CSR;
}RCC_Reg_t;


#define RCC	((RCC_Reg_t*)RCC_BASE_ADDRESS)

/************************************************************************************************/
/******************************** DMA Registers ***********************************************/
/************************************************************************************************/
#define DMA1_BASE_ADDRESS			0x40020000U
#define DMA2_BASE_ADDRESS			0x40020400U

typedef enum
{
	CCR,
	CNDTR,
	CPAR,
	CMAR,
	RESERVED

}DMA_ChannelReg_T;

typedef struct
{
	volatile uint32_t ISR;
	volatile uint32_t IFCR;
	volatile uint32_t CHNR[7][5];

}DMA_RegDef_T;

#define DMA1			((DMA_RegDef_T *)DMA1_BASE_ADDRESS)
#define DMA2			((DMA_RegDef_T *)DMA2_BASE_ADDRESS)
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
/******************** SPI Peripheral Definition ****************
#define SPI1	((SPI_Reg_t*)SPI1_BASE_ADDRESS)
#define SPI2	((SPI_Reg_t*)SPI2_BASE_ADDRESS)
#define SPI3	((SPI_Reg_t*)SPI3_BASE_ADDRESS)*/
/******************** EXTI Peripheral Definition *****************/
#define EXTI	((EXTI_Reg_t*)EXTI_BASE_ADDRESS)
/******************** Processsor Peripheral Base Addresses *****************/
#define SCB_BASE_ADDRESS      	0xE000E008UL
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

/*********************  AFIO Register Definition Structure   *********************/

#define AFIO_BASE_ADDRESS		 0x40010000U

typedef struct
{
    volatile uint32_t EVCR;
    volatile uint32_t MAPR;
    volatile uint32_t EXTICR[4];
    volatile uint32_t RESERVED;
    volatile uint32_t MAPR2;

}AFIO_RegDef_T;

#define AFIO						((AFIO_RegDef_T *)AFIO_BASE_ADDRESS)

/********************************************************************************************************/
/************************************************************************************************/
/******************************** SPI Registers ************************************************/
/************************************************************************************************/
#define SPI1_u32_BASE_ADDRESS                                0x40013000U
#define SPI2_u32_BASE_ADDRESS                                0x40003800U
#define SPI3_u32_BASE_ADDRESS                                0x40003C00U

 typedef	struct
{
	volatile uint32_t CR1     ;
	volatile uint32_t CR2     ;
	volatile uint32_t SR      ;
	volatile uint32_t DR      ;
	volatile uint32_t CRCPR   ;
	volatile uint32_t RXCRCR  ;
	volatile uint32_t TXCRCR  ;
	volatile uint32_t I2SCFGR ;
	volatile uint32_t I2SPR   ;

} SPI_REG ;

#define  SPI1                     ( ( SPI_REG *) SPI1_u32_BASE_ADDRESS )
#define  SPI2                     ( ( SPI_REG *) SPI2_u32_BASE_ADDRESS )
#define  SPI3                     ( ( SPI_REG *) SPI3_u32_BASE_ADDRESS )

#endif
