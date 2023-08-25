/*
 * SPI_interface.h
 *
 *  Created on: Aug 24, 2023
 *      Author: kareem
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_
typedef enum
{
    SPI_FclkDiv_2 =0U,
    SPI_FclkDiv_4,
    SPI_FclkDiv_8,
    SPI_FclkDiv_16,
    SPI_FclkDiv_32,
    SPI_FclkDiv_64,
    SPI_FclkDiv_128,
    SPI_FclkDiv_256,
}SPI_clkSpeed_t;
typedef enum
{
    SPI_1=0U,
    SPI_2,
    SPI_3,
}SPI_Number_t;
typedef enum
{
    SPI_SlAVE=0U,
    SPI_MASTER
}SPI_MCstate_t;
typedef enum
{
    SPI_SlaveSlection_HW=0U,
    SPI_SlaveSlection_SW=1U,
}SPI_SlaveSlection_t;
typedef enum
{
    SPI_SSoutputDisableMultiMaster = 0U,
    SPI_SSoutputEnableSingleMaster,
}SPI_SlaveOutputPINState_t;
typedef enum
{
    SPI_2LineUnidirectional=0U,
    SPI_1LineBidirectional,
}SPI_NumberOfDricaton_t;
typedef enum
{
    SPI_INTER_DISABLE=0U,
    SPI_INTER_ENABLE
}SPI_InterState_t;
typedef struct
{
    SPI_InterState_t TxBufferEmptyInter;
    SPI_InterState_t RxBufferNotEmptyInter;
    SPI_InterState_t ErrorInter;
    SPI_InterState_t FrameFromateInter;
    SPI_InterState_t TxBufferDMA;
    SPI_InterState_t RxBufferDMA;
}SPI_InterruptsStates_ty;
typedef enum
{
    SPI_DISABLE=0U,
    SPI_ENABLE
}SPI_state_t;
typedef enum
{
    SPI_8_BIT_DATA_FRAME=0U,
    SPI_16_BIT_DATA_FRAME
}SPI_Dataframe_t;
typedef struct
{
    SPI_Number_t   SpiNumber;
    SPI_MCstate_t SpiState;
    SPI_NumberOfDricaton_t LinesDirections;
    SPI_SlaveSlection_t SLaveSlection;
    SPI_clkSpeed_t ClockSpeed;
    SPI_state_t SPIperiphState;
    SPI_SlaveOutputPINState_t SSOstate;
    SPI_InterruptsStates_ty InterruptsStates;
    SPI_Dataframe_t DataFrameLenght;
    void (*Copy_pvTxEmptUserFunc)(void);
    void (*Copy_pvRxNotEmptUserFunc)(void);
}SPI_Config_ty;

uint8_t SPI_u8Init(const SPI_Config_ty *Comunication);
uint8_t SPI_u8ReadData(SPI_Number_t   SpiNumber,uint16_t*pv_u16Distantion);
uint8_t SPI_u8WriteData(SPI_Number_t   SpiNumber,uint16_t pv_u16Data);



#endif /* SPI_INTERFACE_H_ */
