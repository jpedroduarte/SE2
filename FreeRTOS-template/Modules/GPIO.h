/** @file GPIO.h
 *  @brief Contains the GPIO API.
 *  @author João Duarte
 */

#ifndef __GPIO_H__
#define __GPIO_H__

/** @defgroup GPIO GPIO
 * @ingroup GPIO
 *	In this module you can find functionalities like 
 *	writing, reading and configuring the GPIO ports.
 * @{

 * @defgroup GPIO_Public_Functions GPIO Public Functions
 * @{
 */

#include "../../CMSIS_CORE_LPC17xx/inc/LPC17xx.h"

/** @brief Configures the GPIO ports.
 *
 *	Starts with initValue in case those ports are configured in output mode.
 *
 *  @param dir
 *  @param mask
 *	@param initValue
 *  @return none
 */

#define GPIO_PULL_UP_REGISTOR 0
#define GPIO_REPEATER_MODE 1
#define GPIO_NO_PULL 2
#define GPIO_PULL_DOWN_REGISTOR 3

#define GPIO_OPEN_DRAIN_ENABLE 1
#define GPIO_OPEN_DRAIN_DISABLE 0

/**
 * @brief	Configures only the digital side for GPIO0.
 * @param	uint32_t dir - direction of the pins
 * @param	uint32_t mask - the mask of the pins to configure.
 * @param	uint32_t initValue - the value in which to start the GPIO's with.
 * @return	void
 */
void GPIO_configDigital(uint32_t dir, uint32_t mask, uint32_t initValue);

/**
 * @brief	Configures only the digital side of a given GPIO port.
 * @param	uint32_t gpio_port - number of the port to configure.
 * @param	uint32_t gpio_func - number of the function to use in the selected pins.
 * @param	uint32_t dir - direction of the pins
 * @param	uint32_t mask - the mask of the pins to configure.
 * @param	uint32_t initValue - the value in which to start the GPIO's with.
 * @return	void
 */
void GPIO_configDigitalGeneric(uint32_t gpio_port, uint32_t gpio_func, uint32_t dir, uint32_t mask, uint32_t initValue);

/**
 * @brief	Configures only the analogic side of a given GPIO port.
 * @param	uint32_t gpio_port - number of the port to configure.
 * @param	uint32_t pins_func - number of the function to use in the selected pins.
 * @param	uint32_t open_drain - the bit mask to select which pins will have open drain mode.
 * @param	uint32_t mask - the mask of the pins to configure.
 * @return	void
 */
void GPIO_configAnalogGeneric(uint32_t gpio_port, uint32_t pins_func, uint32_t open_drain, uint32_t mask);

/**
 * @brief	Writes the given value in the given mask on the given port using FIOPIN.
 * @param	uint32_t gpio_port - number of the port to configure.
 * @param	uint32_t value - the value in which to affect the port.
 * @param	uint32_t mask - the mask of the pins to configure.
 * @return	void
 */
void GPIO_output(uint32_t gpio_port, uint32_t value, uint32_t mask);

/**
 * @brief	Reads the given port.
 * @param	uint32_t gpio_port - number of the port to configure.
 * @return	uint32_t value of the FIOPIN.
 */
uint32_t GPIO_input(uint32_t gpio_port);

/** @brief Clears the GPIO port 0.
 *
 *	Puts LOW in GPIO0.
 *
 *  @param uint32_t mask - the mask of the pin to configure.
 *  @return none
 */
void GPIO_Clear(uint32_t mask);

/**
 * @brief	Configures only the digital side of a given pin in the GPIO port.
 * @param	uint32_t gpio_port - number of the port to configure.
 * @param	uint32_t gpio_func - number of the function to use in the selected pins.
 * @param	uint32_t dir - direction of the pin
 * @param	uint32_t mask - the mask of the pin to configure.
 * @param	uint32_t initValue - the value in which to start the GPIO's with.
 * @return	void
 */
void GPIO_config_bitGeneric(uint32_t gpio_port, uint32_t gpio_func, uint32_t dir, uint32_t mask, uint32_t initValue);

/** @brief Clears the pin in GPIO port.
 *
 *	Puts LOW on the pin in output port.
 *	@param uint32_t gpio_port - number of the port to configure.
 *  @param uint32_t mask - the mask of the pin to clear.
 *  @return none
 */
void GPIO_ClearGeneric(uint32_t gpio_port,uint32_t mask);

/** @brief Sets the pin in GPIO port.
 *
 *	Puts HIGH on the pin in output port.
 *	@param uint32_t gpio_port - number of the port to configure.
 *  @param uint32_t mask - the mask of the pin to set.
 *  @return none
 */
void GPIO_SetGeneric(uint32_t gpio_port,uint32_t mask);

/** @brief Sets the pin in GPIO port 0.
 *
 *	Puts HIGH on the pin in GPIO0.
 *  @param uint32_t mask - the mask of the pin to set.
 *  @return none
 */
void GPIO_Set(uint32_t mask);

/**
 * @brief	Configures only the digital side for GPIO0.
 * @param	uint32_t dir - direction of the pin
 * @param	uint32_t mask - the mask of the pin to configure.
 * @param	uint32_t initValue - the value in which to start the GPIO with.
 * @return	void
 */
void GPIO_config_bit(uint32_t dir, uint32_t mask, uint32_t initValue);

/**
 * @}
  */
  
/**
 * @}
 */
#endif /* __GPIO_H__ */
