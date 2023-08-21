#ifndef DMA_PRIVATE_H_
#define DMA_PRIVATE_H_

#define DMA_STREAM_NUM			8			/*Number of Streams*/
#define DMA_STREAM_REG_NUM		6			/*Number of SCR registers*/

#define DMA_CHSEL_MASK			0b111		/*Channel bits mask*/
#define DMA_CHSEL_SHIFT			25			/*Channel bits shift*/

#define DMA_PL_MASK				0b11		/*Priority bits mask*/
#define DMA_PL_SHIFT			16			/*Priority bits shift*/

#define	DMA_MINC_SHIFT			10			/*Memory increment shift*/
#define	DMA_PINC_SHIFT			9			/*Peripheral increment shift*/


#define DMA_DIR_MASK			0b11		/*Data transfer direction mask*/
#define DMA_DIR_SHIFT			6			/*Data transfer direction shift*/

#define DMA_DMDIS_SHIFT			2			/*Direct mode disable shift*/

#define DMA_MSIZE_MASK			0b11		/*Memory data size mask*/
#define DMA_MSIZE_SHIFT			13			/*Memory data size shift*/

#define DMA_PSIZE_MASK			0b11		/*Peripheral data size mask*/
#define DMA_PSIZE_SHIFT			11			/*Peripheral data size shift*/

#define DMA_FTH_MASK			0b11		/*FIFO threshold mask*/

#endif

