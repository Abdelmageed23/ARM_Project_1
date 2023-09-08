#ifndef DMA_INTERFACE_H_
#define DMA_INTERFACE_H_


typedef enum
{
	DMA_1,
	DMA_2

}DMA_DMAType;

typedef enum
{
	CHANNEL0,
	CHANNEL1,
	CHANNEL2,
	CHANNEL3,
	CHANNEL4,
	CHANNEL5,
	CHANNEL6,
	CHANNEL7

}DMA_ChannelNum;

typedef enum
{
	STREAM0,
	STREAM1,
	STREAM2,
	STREAM3,
	STREAM4,
	STREAM5,
	STREAM6,
	STREAM7

}DMA_StreamNum;

typedef enum
{
	PERIPH_TO_MEM,
	MEM_TO_PERIPH,
	MEM_TO_MEM

}DMA_SrcDestMode;

typedef enum
{
	LOW,
	MEDUIM,
	HIGH,
	VERY_HIGH

}DMA_PrioLevel;

typedef enum
{
	FIXED,
	INCREMENT

}DMA_IncMode;

typedef enum
{
	BYTE,
	HALF_WORD,
	WORD

}DMA_IncSize;

typedef enum
{
	DIRECT_MODE,
	FIFO_MODE

}DMA_TransferMode;

typedef enum
{
	QUART,
	HALF,
	THREE_QUART,
	FULL

}DMA_FIFOThresh;

typedef enum
{
	DIR_ERR=1,
	ERR_TRANS,
	HALF_TRANS,
	FULL_TRANS,
	FIFO_ERR=7,

}DMA_Interrupt;



typedef struct
{
	DMA_DMAType DMA_Type;

	DMA_IncMode MemIncMode;
	DMA_IncMode PerIncMode;

	DMA_IncSize MemIncSize;
	DMA_IncSize PerIncSize;

	DMA_SrcDestMode SrcDestMode;
	DMA_TransferMode TransferMode;

	DMA_StreamNum StreamNum;
	DMA_ChannelNum ChannelNum;
	DMA_PrioLevel PriorityLevel;

	DMA_FIFOThresh FIFOThresh;

	DMA_Interrupt InterruptType;

	void (*CallBackFunc)(void);

}DMA_Cnfg_T;

uint8_t DMA_u8Init(DMA_Cnfg_T* DMA_Cnfg);

uint8_t DMA_u8StartTransfer(DMA_Cnfg_T *DMA_Cnfg,uint32_t *Copy_pu32SrcAddress , uint32_t *Copy_pu32DestAddress , uint16_t Copy_u32DataSize);

#endif
