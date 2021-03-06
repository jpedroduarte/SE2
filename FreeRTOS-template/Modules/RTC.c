/** @file RTC.c
 *  @brief Drivers for RTC.
 *
 *  Function RTC_Init must be called before anything else.
 *	This module provides functionality to control the RTC.
 *
 *
 *  @author João Duarte
 *
 */

#include "RTC.h"

#define mask_SEC    0x3F
#define mask_MIN	0x3F00
#define mask_HOUR 	0x1F0000
#define mask_DOM    0X1F
#define mask_DOW    0X7000000
#define mask_DOY	0XFFF
#define mask_MONTH  0XF00
#define mask_YEAR	0XFFF0000

#define mask_RTC_PCONP 0x200

/* Faz a iniciação do sistema para permitir o acesso ao periférico RTC. O RTC é
iniciado com os valores do parâmetro. */
void RTC_Init(struct tm *dateTime) {
	LPC_SC->PCONP |= 	mask_RTC_PCONP;
	LPC_RTC->CCR = 		0x2; /* Disable time counters and reset CTC */
	LPC_RTC->ILR = 		0x3; /* Clear interrupts */
	LPC_RTC->ILR = 		0x0; /* Disable interrupts */
	LPC_RTC->CIIR = 	0x0; /* CIIR disabled */
	LPC_RTC->AMR = 		0xFF; /* Alarm disabled */
	RTC_SetValue(dateTime);
	LPC_RTC->CCR = 		0x1; /* Enable time counters and CTC */
}

/* Realiza a atualização do RTC com os valores do parâmetro dateTime. */
void RTC_SetValue(struct tm *dateTime){
	LPC_RTC->CCR = 0x2; /* Disable time counters and reset CTC */
	LPC_RTC->SEC = dateTime-> 	tm_sec;
	LPC_RTC->MIN = dateTime-> 	tm_min;
	LPC_RTC->HOUR = dateTime-> 	tm_hour;
	LPC_RTC->DOM = dateTime-> 	tm_mday;
	LPC_RTC->MONTH = dateTime-> tm_mon;
	LPC_RTC->YEAR = dateTime-> 	tm_year;
	LPC_RTC->DOW = dateTime-> 	tm_wday;
	LPC_RTC->DOY = dateTime-> 	tm_yday;
	LPC_RTC->CCR = 0x1; /* Enable time counters and CTC */
}



/* Devolve em dateTime o valor corrente do RTC. */
void RTC_GetValue(struct tm *dateTime){
   dateTime-> tm_sec   =  LPC_RTC->CTIME0 & mask_SEC;         	/* seconds,  range 0 to 59          */
   dateTime-> tm_min   = (LPC_RTC->CTIME0 & mask_MIN) 	>> 8 ;	/* minutes, range 0 to 59           */
   dateTime-> tm_hour  = (LPC_RTC->CTIME0 & mask_MIN) 	>> 16;	/* hours, range 0 to 23             */
   dateTime-> tm_mday  =  LPC_RTC->CTIME1 & mask_DOM;        	/* day of the month, range 1 to 31  */
   dateTime-> tm_mon   = (LPC_RTC->CTIME1 & mask_MONTH) >> 8 ;	/* month, range 0 to 11             */
   dateTime-> tm_year  = (LPC_RTC->CTIME1 & mask_YEAR) 	>> 16;	/* The number of years since 1900   */
   dateTime-> tm_wday  = (LPC_RTC->CTIME0 & mask_DOW) 	>> 24;	/* day of the week, range 0 to 6    */
   dateTime-> tm_yday  = (LPC_RTC->CTIME2 & mask_DOY);        	/* day in the year, range 0 to 365  */
}
