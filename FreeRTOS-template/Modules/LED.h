/** @file LED.h
 *  @brief Contains the LED API.
 *
 *  @author Red
 */

#ifndef __LED_H__
#define __LED_H__
/** @defgroup LED LED
 * @ingroup LED
 *  This package provides the core capabilities such as turning on/off an LED on the desired GPIO port.
 *	LED must be with a pull-down resistor of 60 to 80 Ohms preferably.
 * @{

/** @defgroup LED_Public_Functions LED Public Functions
 * @{
 */
#include "GPIO.h"

/** @brief Configures the GPIO port to the LED use and sets its value based on the state parameter
 *	@param pin_number number of the GPIO pin to use the LED. From 0 to 15 preferably.
 *	@param state 1 for turned on; 0 off
 *  @return none.
 */
void LED_init(uint32_t gpio_port, uint32_t pin_number, uint32_t state);

/** @brief Gets the state of the LED.
 *  @return turned off->0; otherwise-> 1
 */
uint32_t LED_GetState();

/** @brief Sets the LED state.
 *	@param state 1 for turned on; 0 off
 *  @return none.
 */
void LED_SetState(uint32_t state);

/**
 * @}
  */

/**
 * @}
 */
#endif /* LED_H_ */
