#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H
typedef enum
{
    STATE_OFF,
    STATE_ON
}STATE_ty;
typedef enum
{
    SET_CLK_HSI =0,
    SET_CLK_HSE =16,
    SET_CLK_PLL =24,
}SET_CLK_type_ty;
typedef enum
{
    SYS_HSI =0,
    SYS_HSE =0b01,
    SYS_PLL =0b10,
}SYS_CLK_type_ty;
typedef enum
{
    HSE_diviedby_1,
    HSE_diviedby_2
}HSEconfig_type_ty;
typedef enum
{
    PLL_MUL_2  =0b0000,
    PLL_MUL_3  =0b0001,
    PLL_MUL_4  =0b0010,
    PLL_MUL_5  =0b0011,
    PLL_MUL_6  =0b0100,
    PLL_MUL_7  =0b0101,
    PLL_MUL_8  =0b0110,
    PLL_MUL_9  =0b0111,
    PLL_MUL_10 =0b1000,
    PLL_MUL_11 =0b1001,
    PLL_MUL_12 =0b1010,
    PLL_MUL_13 =0b1011,
    PLL_MUL_14 =0b1100,
    PLL_MUL_15 =0b1101,
    PLL_MUL_16 =0b1110,
}PLL_MUL_type_ty;
typedef enum
{
    PLLHSE,
    PLLHSI
}PLLSRC_ty;
typedef enum
{
    AHB_DMA1  =0,
    AHB_DMA2  =1,
    AHB_SRAM  =2,
    AHB_FLITF =4,
    AHB_CRC   =6,
    AHB_FSMC  =8,
    AHB_SDIO  =10,
}AHBperipheral_ty;
typedef enum
{
    APB2_AFIO    =0,
    APB2_IOPA    =2,
    APB2_IOPB    =3,
    APB2_IOPC    =4,
    APB2_IOPD    =5,
    APB2_IOPE    =6,
    APB2_IOPF    =7,
    APB2_IOPG    =8,
    APB2_ADC1    =9,
    APB2_ADC2    =10,
    APB2_TIMER1  =11,
    APB2_SPI1    =12,
    APB2_TIMER8  =13,
    APB2_USART1  =14,
    APB2_ADC3    =15,
    APB2_TIMER9  =19,
    APB2_TIMER10 =20,
    APB2_TIMER11 =21,
}APB2peripheral_ty;
typedef enum
{
    APB1_TIMER2  =0,
    APB1_TIMER3  =1,
    APB1_TIMER4  =2,
    APB1_TIMER5  =3,
    APB1_TIMER6  =4,
    APB1_TIMER7  =5,
    APB1_TIMER12 =6,
    APB1_TIMER13 =7,
    APB1_TIMER14 =8,
    APB1_WWDG   =11,
    APB1_SPI2   =14,
    APB1_SPI3   =15,
    APB1_USART2 =17,
    APB1_USART3 =18,
    APB1_UART4  =19,
    APB1_UART5  =20,
    APB1_I2C1   =21,
    APB1_I2C2   =22,
    APB1_USB    =23,
    APB1_CAN    =25,
    APB1_BKP    =27,
    APB1_PWR    =28,
    APB1_DAC    =29,       
}APB1peripheral_ty;
uint8_t RCC_SetClksts(SET_CLK_type_ty ClkType,STATE_ty State);

uint8_t RCC_SetSysClk(SYS_CLK_type_ty ClkType);

uint8_t RCC_HSE_Config(HSEconfig_type_ty Config);

void RCC_PLL_Config(PLL_MUL_type_ty PllMul,PLLSRC_ty PLL_SCR);

void RCC_AHBEnableClock(AHBperipheral_ty peripheral);
void RCC_AHBDisableClock(AHBperipheral_ty peripheral);

void RCC_APB1EnableClock(APB1peripheral_ty peripheral);
void RCC_APB1DisableClock(APB1peripheral_ty peripheral);

void RCC_APB2EnableClock(APB2peripheral_ty peripheral);
void RCC_APB2DisableClock(APB2peripheral_ty peripheral);


#endif