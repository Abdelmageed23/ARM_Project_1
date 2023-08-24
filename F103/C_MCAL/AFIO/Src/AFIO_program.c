#include "stdint.h"
#include "STM32F103xx.h"

#include "AFIO_private.h"
#include "AFIO_interface.h"


void AFIO_voidSetEXTIPort(AFIO_LineNum_T Copy_LineNum, AFIO_Port_T Copy_Port)
{
	uint8_t Local_u8RegisterNum = Copy_LineNum / AFIO_EXTICR_REG_LINEBITS;
	uint8_t Local_u8BitNum = (Copy_LineNum % AFIO_EXTICR_REG_LINEBITS)*AFIO_EXTICR_REG_LINEBITS;

	AFIO->EXTICR[Local_u8RegisterNum] &= ~(AFIO_EXTICR_REG_MASK << Local_u8BitNum);
	AFIO->EXTICR[Local_u8RegisterNum] |= (Copy_Port << Local_u8BitNum);

}
