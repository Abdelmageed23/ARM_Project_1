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
    DMA1  =0,
    DMA2  =1,
    SRAM  =2,
    FLITF =4,
    CRC   =6,
    FSMC  =8,
    SDIO  =10,
}AHBperipheral_ty;
typedef enum
{
    AFIO    =0,
    IOPA    =2,
    IOPB    =3,
    IOPC    =4,
    IOPD    =5,
    IOPE    =6,
    IOPF    =7,
    IOPG    =8,
    ADC1    =9,
    ADC2    =10,
    TIMER1  =11,
    SPI1    =12,
    TIMER8  =13,
    USART1  =14,
    ADC3    =15,
    TIMER9  =19,
    TIMER10 =20,
    TIMER11 =21,
}APB2peripheral_ty;
typedef enum
{
    TIMER2  =0,
    TIMER3  =1,
    TIMER4  =2,
    TIMER5  =3,
    TIMER6  =4,
    TIMER7  =5,
    TIMER12 =6,
    TIMER13 =7,
    TIMER14 =8,
    WWDG   =11,
    SPI2   =14,
    SPI3   =15,
    USART2 =17,
    USART3 =18,
    UART4  =19,
    UART5  =20,
    I2C1   =21,
    I2C2   =22,
    USB    =23,
    CAN    =25,
    BKP    =27,
    PWR    =28,
    DAC    =29,       
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