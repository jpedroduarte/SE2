/**
* @file		RTC.h
* @brief	Drivers for RTC.
* @author	João Duarte
*/

#ifndef RTC_H_
#define RTC_H_

/** @defgroup RTC RTC
 * @ingroup RTC
 * This module provides functionality to manage RTC controller from LPC1769 and the likes.
 * RTC_Init must be called before any RTC use.
 * @{

 * @defgroup RTC_Public_Functions RTC Public Functions
 * @{
 */

#include "LPC17xx.h"
#include <time.h>


/**
 * @brief	Initializes the system to allow acess to RTC. It is initialized with the dateTime values.
 * @param	struct tm *dateTime - struct with init values for the RTC.
 * @return	void
 */
void RTC_Init(struct tm *dateTime);

/**
 * @brief	Gets the dateTime values.
 * @param	struct tm *dateTime - struct with dateTime values.
 * @return	void
 */
void RTC_GetValue(struct tm *dateTime);

/**
 * @brief	Sets the dateTime values.
 * @param	struct tm *dateTime - struct with dateTime values.
 * @return	void
 */
void RTC_SetValue(struct tm *dateTime);
/* Realiza a atualização do RTC com os valores do parâmetro dateTime. */


/**
 * @}
  */

/**
 * @}
 */

#endif /* RTC_H_ */
