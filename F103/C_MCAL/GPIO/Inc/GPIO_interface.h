#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

/****************************************************************************/

/*
 * @Port_T
 * */
typedef enum
{
    PORTA=0,
    PORTB,
    PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG


}Port_T;

/****************************************************************************/

/*
 * @Pin_T
 * */
typedef enum 
{
    PIN0=0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
    PIN8,
    PIN9,
    PIN10,
    PIN11,
    PIN12,
    PIN13,
    PIN14,
    PIN15

}Pin_T;

typedef enum
{
    INPUT=0,
    OUTPUT_10MHZ,
    OUTPUT_2MHZ,
    OUTPUT_50MHZ
}Mode_T;

typedef enum
{
	ANALOG=0,
	FLOATING,
	PULL_UPDN,
	GPO_PUSHPULL=0,
	GPO_OPEN_DRAIN,
	AF_PUSHPULL,
	AF_OPEN_DRAIN

}Config_InOut_T;



/****************************************************************************/
/*
 * @PinVal_T
 * */
typedef enum
{
    PIN_LOW=0,
    PIN_HIGH

}PinVal_T;


typedef enum
{
    PULL_DN=0,
    PULL_UP

}PullUpDn_T;

typedef struct
{
    Port_T Port;
    Pin_T PinNum;
    Mode_T Mode;
    Config_InOut_T InputOutConfig;
    PullUpDn_T PullType;

}GPIO_PinConfig_T;

uint8_t GPIO_u8PinInit(const GPIO_PinConfig_T *PinConfig);

uint8_t GPIO_u8SetPinValue(Port_T Port , Pin_T PinNum , PinVal_T PinValue);

uint8_t GPIO_u8TogglePinValue(Port_T Port , Pin_T PinNum);

uint8_t GPIO_u8ReadPinValue(Port_T Port , Pin_T PinNum , PinVal_T *PinValue);

#endif
