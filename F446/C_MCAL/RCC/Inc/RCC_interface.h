#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H
 
typedef enum
{
    STATE_OFF   =0,
    STATE_ON    =1,
}STATE_ty;
typedef enum
{
    CLK_HSI     =0,
    CLK_HSE     =16,
    CLK_PLL     =24,
    CLK_PLLI2S  =26,
    CLK_PLLSAI  =28,
}CLKsSYS_type_ty;

typedef enum
{
    HSI     =0b0,
    HSE     =0b1,
    PLL_P   =0b10,
    PLL_R   =0b11,
}CLK_type_ty;
typedef enum
{
    AHB1_GPIOA      =0,
    AHB1_GPIOB      =1,
    AHB1_GPIOC      =2,
    AHB1_GPIOD      =3,
    AHB1_GPIOE      =4,
    AHB1_GPIOF      =5,
    AHB1_GPIOG      =6,
    AHB1_GPIOH      =7,
    AHB1_CRC        =12,
    AHB1_BKPSRAM    =18,
    AHB1_DMA1       =21,
    AHB1_DMA2       =22,
    AHB1_OTGHS      =29,
    AHB1_OTGHSULPI  =30,   
}AHB1peripheral_ty;

uint8_t RCC_u8SetClksts(CLKsSYS_type_ty ClkType,STATE_ty State);
uint8_t RCC_SetSysClk(CLK_type_ty ClkType);
void RCC_voidAHB1EnablePerapheralClock(AHB1peripheral_ty Copy_Perapheral);
void RCC_voidAHB1DisablePerapheralClock(AHB1peripheral_ty Copy_Perapheral);
#endif