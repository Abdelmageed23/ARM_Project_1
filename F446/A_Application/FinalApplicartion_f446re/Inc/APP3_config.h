#ifndef APP3_CONFIG_H
#define APP3_CONFIG_H




/*******************************************************************************/
/************************* SPI and GPIO Configuration **************************/
/*******************************************************************************/
/* Master , Software Management and 8 Bit Frame */
#define APP3_SPI_INDEX           SPI_1            /* Get Option From @SPIindex_t */
#define APP3_SPI_MOSI_PIN        PORTA , PIN7     /* Get Option From @Port_T    , @Pin_T  */
#define APP3_SPI_MISO_PIN        PORTA , PIN6     /* Get Option From @Port_T    , @Pin_T  */
#define APP3_SPI_SCK_PIN         PORTA , PIN5     /* Get Option From @Port_T    , @Pin_T  */
#define APP3_GPIO_NSS_PIN        PORTA , PIN1     /* Get Option From @Port_T    , @Pin_T  */
#define APP3_GPIO_TO_EXTI_PIN    PORTA , PIN0     /* Get Option From @Port_T    , @Pin_T  */
/*******************************************************************************/
/************************* SPI Receive Trigger *********************************/
/*******************************************************************************/
#define APP3_SPI_TRIGGER_GRN_LED             '!'
#define APP3_SPI_TRIGGER_RED_LED             '~'
#define APP3_SPI_TRIGGER_TIME                '@'
#define APP3_SPI_TRIGGER_DATE                '#'
#define APP3_SPI_TRIGGER_ALARM               '$'
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/



#endif
