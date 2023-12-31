#ifndef	DMA_PRIVATE_H_
#define DMA_PRIVATE_H_

#define DMA1_IRQ_NUM				7
#define DMA2_IRQ_NUM				4
#define DMA_TOT_IRQ_NUM				11

#define DMA_MEM2MEM_SHIFT			14
#define DMA_PL_SHIFT				12

#define DMA_MSIZE_SHIFT				10
#define DMA_PSIZE_SHIFT				8

#define DMA_MINC_SHIFT				7
#define DMA_PINC_SHIFT				6
#define DMA_DIR_SHIFT				4


#define DMA_ICF_MASK				0b111
#define DMA_ICF_CHANNEL1_SHIFT		0
#define DMA_ICF_CHANNEL2_SHIFT		4
#define DMA_ICF_CHANNEL3_SHIFT		8
#define DMA_ICF_CHANNEL4_SHIFT		12
#define DMA_ICF_CHANNEL5_SHIFT		16
#define DMA_ICF_CHANNEL6_SHIFT		20
#define DMA_ICF_CHANNEL7_SHIFT		24

#define DMA_GIF5_SHIFT				5
#define DMA_FLAG_RISED				1


#endif
