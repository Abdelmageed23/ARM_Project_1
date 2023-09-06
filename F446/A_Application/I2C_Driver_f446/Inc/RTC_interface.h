#ifndef  RTC_INTERFACE_H
#define  RTC_INTERFACE_H
/******************************************************************************/
/************************ @TimeFormat_t ***************************************/
/******************************************************************************/
typedef enum{
		_12HRS_AM        =0,
		_12HRS_PM          ,
		_24HRS
}TimeFormat_t;
/******************************************************************************/
/************************ @Days_t *********************************************/
/******************************************************************************/
typedef enum{
			SUNDAY     = 1,
			MONDAY        ,
			TUESDAY       ,
			WEDNESDAY     ,
			THURSDAY      ,
			FRIDAY        ,
			SATURDAY
}Days_t;

typedef struct{


	uint8_t minutes;
    uint8_t	hours ;
    Days_t  day   ;
	uint8_t date  ;
	uint8_t month ;
	uint8_t year  ;

}RTC_DateTime_t;

typedef struct
{

	uint8_t StartAdd;
	uint8_t Mins;
	uint8_t Hrs;
	uint8_t Day;
	uint8_t Date;
	uint8_t Month;
	uint8_t Year;

}RTC_Send_T;

typedef enum
{
	MINS,
	HRS,
	DAY,
	DATE,
	MONTH,
	YEAR,

}RTC_Elemnts;

/*************************************************************************************************************************************/
/********************************************************* Functions Prototype *******************************************************/
/*************************************************************************************************************************************/
/**
 ******************************************************************************
 * @fn             : HRTC_u8Init
 * @brief          : initialization RTC
 * @param[in]      : void
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void HRTC_u8Init( I2Cconfig_t *Copy_I2CCnfg );
/**
 ******************************************************************************
 * @fn             : HRTC_u8GetRtcStatus
 * @brief          : Get Rtc Status
 * @param[in]      : Copy_u8Status --> Get Value
 * @retval         : void
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
void HRTC_u8GetRtcStatus ( I2Cconfig_t *Copy_I2CCnfg,uint8_t *Copy_u8Status );

void HRTC_voidSetDateTime ( I2Cconfig_t *Copy_I2CCnfg,RTC_DateTime_t *RTC_time );

void HRTC_voidGetDateTime ( I2Cconfig_t *Copy_I2CCnfg,RTC_DateTime_t *RTC_time );

void BCDToBinary (uint8_t *Copy_pu8BcdArr , uint8_t *Copy_pu8BinArr ,uint8_t Copy_u8ArrSize);

void BinaryToBCD (uint8_t *Copy_pu8BinArr ,uint8_t *Copy_pu8BcdArr ,uint8_t Copy_u8ArrSize);

/*************************************************************************************************************************************/
/*************************************************************************************************************************************/
/*************************************************************************************************************************************/

#endif
