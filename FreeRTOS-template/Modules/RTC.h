/*
 * RTC.h
 *
 *  Created on: 07/06/2016
 *      Author: Red
 */

#ifndef RTC_H_
#define RTC_H_

#include "LPC17xx.h"
#include <time.h>

void RTC_Init(struct tm *dateTime);
/* Faz a iniciação do sistema para permitir o acesso ao periférico RTC. O RTC é
iniciado com os valores do parâmetro. */
void RTC_GetValue(struct tm *dateTime);
/* Devolve em dateTime o valor corrente do RTC. */
void RTC_SetValue(struct tm *dateTime);
/* Realiza a atualização do RTC com os valores do parâmetro dateTime. */
void RTC_GetAlarmValue(struct tm *dateTime);
/* Devolve em dateTime o valor corrente do alarme do RTC. */
void RTC_SetAlarmValue(struct tm *dateTime);
/* Realiza a atualização do alarme do RTC com os valores do parâmetro dateTime.
*/

#endif /* RTC_H_ */
