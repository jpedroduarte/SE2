/** @file GPIO.h
 *  @brief Contains the GPIO API.
 *  @author G6
 */

#ifndef __GPIO_H__
#define __GPIO_H__

/** @defgroup GPIO GPIO
 * @ingroup GPIO
 *	In this module you can find functionalities like 
 *	writing and reading from the LPC2106 GPIO ports. 
 * @{

 * @defgroup GPIO_Public_Functions GPIO Public Functions
 * @{
 */

#include "LPC17xx.h"

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

void GPIO_configDigital(uint32_t dir, uint32_t mask, uint32_t initValue);

/** @brief Configures the GPIO port in the pins given by mask and with I/O given by dir.
 *
 *	Puts value in output ports described by mask. 
 *	dir=0 input
 *	dir=1 output
 *
 *	@param dir
 *  @param mask
 *  @param value
 *  @return none
 */

void GPIO_configDigitalGeneric(uint32_t gpio_port, uint32_t gpio_func, uint32_t dir, uint32_t mask, uint32_t initValue);

void GPIO_configAnalogGeneric(uint32_t gpio_port, uint32_t pins_func, uint32_t open_drain, uint32_t mask);
/** @brief Configures the GPIO port pins given by mask and configures the pins function.
 *
 *	Puts value in output ports described by mask.
 *	dir=0 input
 *	dir=1 output
 *
 *	@param pinsel
 *  @param func
 *  @param mask
 *  @return none
 */

void GPIO_output(uint32_t gpio_port, uint32_t value, uint32_t mask);

/** @brief Configures the GPIO ports.
 *
 *	Puts value in output ports described by mask. 
 *
 *  @return value of IOPIN
 */
uint32_t GPIO_input(uint32_t gpio_port);

/** @brief Clears the GPIO port.
 *
 *	Puts LOW in output port.
 *
 *  @param mask
 *  @return none
 */
void GPIO_Clear(uint32_t mask);

/** @brief Sets the GPIO port.
 *
 *	Puts HIGH in output port. 
 *
 *  @param mask 
 *  @return none
 */

void GPIO_config_bitGeneric(uint32_t gpio_port, uint32_t gpio_func, uint32_t dir, uint32_t mask, uint32_t initValue);

void GPIO_ClearGeneric(uint32_t gpio_port,uint32_t mask);

void GPIO_SetGeneric(uint32_t gpio_port,uint32_t mask);

void GPIO_Set(uint32_t mask);

/** @brief Configures the mode of the GPIO port.
 *
 *	Starts with initValue in case the port is configured in output mode.
 *
 *  @param dir
 *  @param mask
 *	@param initValue
 *  @return none
 */
void GPIO_config_bit(uint32_t dir, uint32_t mask, uint32_t initValue);

/**
 * @}
  */
  
/**
 * @}
 */
#endif /* __GPIO_H__ */
