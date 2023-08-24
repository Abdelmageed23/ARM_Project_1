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

/************************************************************************************************/
/******************************** USART Registers ***********************************************/
/************************************************************************************************/
#define USART1_u32_BASE_ADDRESS                                0x40011000U
#define USART2_u32_BASE_ADDRESS                                0x40004400U
#define USART3_u32_BASE_ADDRESS                                0x40004800U
#define  UART4_u32_BASE_ADDRESS                                0x40004C00U
#define  UART5_u32_BASE_ADDRESS                                0x40005000U
#define USART6_u32_BASE_ADDRESS                                0x40011400U
 typedef	struct
{
	volatile uint32_t SR    ;
	volatile uint32_t DR    ;
	volatile uint32_t BRR   ;
	volatile uint32_t CR1   ;
	volatile uint32_t CR2   ;
	volatile uint32_t CR3   ;
	volatile uint32_t GTPR  ;

} USART_REG ;

#define  USART1                     ( (  USART_REG *) USART1_u32_BASE_ADDRESS )
#define  USART2                     ( (  USART_REG *) USART2_u32_BASE_ADDRESS )
#define  USART3                     ( (  USART_REG *) USART3_u32_BASE_ADDRESS )
#define   UART4                     ( (  USART_REG *) UART4_u32_BASE_ADDRESS  )
#define   UART5                     ( (  USART_REG *) UART5_u32_BASE_ADDRESS  )
#define  USART6                     ( (  USART_REG *) USART6_u32_BASE_ADDRESS )

/******************** RCC Register Definition Structure *****************/
typedef struct
{
  volatile uint32_t RCC_CR;            /*!< RCC clock control register,                                   */
  volatile uint32_t RCC_PLLCFGR;       /*!< RCC PLL configuration register,                               */
  volatile uint32_t RCC_CFGR;          /*!< RCC clock configuration register,                             */
  volatile uint32_t RCC_CIR;           /*!< RCC clock interrupt register,                                 */
  volatile uint32_t RCC_AHB1RSTR;      /*!< RCC AHB1 peripheral reset register,                           */
  volatile uint32_t RCC_AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                           */
  volatile uint32_t RCC_AHB3RSTR;      /*!< RCC AHB3 peripheral reset register,                           */
  uint32_t      RESERVED0;     		/*!< Reserved, 0x1C                                                */
  volatile uint32_t RCC_APB1RSTR;      /*!< RCC APB1 peripheral reset register,                           */
  volatile uint32_t RCC_APB2RSTR;      /*!< RCC APB2 peripheral reset register,                           */
  uint32_t      RESERVED1[2];  		/*!< Reserved, 0x28-0x2C                                           */
  volatile uint32_t RCC_AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                           */
  volatile uint32_t RCC_AHB2ENR;       /*!< RCC AHB2 peripheral clock register,                           */
  volatile uint32_t RCC_AHB3ENR;       /*!< RCC AHB3 peripheral clock register,                           */
  uint32_t      RESERVED2;     		/*!< Reserved, 0x3C                                                */
  volatile uint32_t RCC_APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                    */
  volatile uint32_t RCC_APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                    */
  uint32_t      RESERVED3[2];  		/*!< Reserved, 0x48-0x4C                                           */
  volatile uint32_t RCC_AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register,  */
  volatile uint32_t RCC_AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register,  */
  volatile uint32_t RCC_AHB3LPENR;     /*!< RCC AHB3 peripheral clock enable in low power mode register,  */
  uint32_t      RESERVED4;     		/*!< Reserved, 0x5C                                                */
  volatile uint32_t RCC_APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register,  */
  volatile uint32_t RCC_APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register,  */
  uint32_t      RESERVED5[2];  		/*!< Reserved, 0x68-0x6C                                           */
  volatile uint32_t RCC_BDCR;          /*!< RCC Backup domain control register,                           */
  volatile uint32_t RCC_CSR;           /*!< RCC clock control & status register,                          */
  uint32_t      RESERVED6[2];  		/*!< Reserved, 0x78-0x7C                                           */
  volatile uint32_t RCC_SSCGR;         /*!< RCC spread spectrum clock generation register,                */
  volatile uint32_t RCC_PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,                            */
  volatile uint32_t RCC_PLLSAICFGR;    /*!< RCC PLLSAI configuration register,                            */
  volatile uint32_t RCC_DCKCFGR;       /*!< RCC Dedicated Clocks configuration register,                  */
  volatile uint32_t RCC_CKGATENR;      /*!< RCC Clocks Gated ENable Register,                             */
  volatile uint32_t RCC_DCKCFGR2;      /*!< RCC Dedicated Clocks configuration register 2,                */
}RCC_RegDef_t;

/******************** RCC Peripheral Definition *****************/

#define RCC	((RCC_RegDef_t*)RCC_BASE_ADDRESS)


#endif
