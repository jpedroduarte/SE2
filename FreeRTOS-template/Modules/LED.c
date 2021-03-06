/** @file LED.c
 *  @brief Drivers for LED on LPC2106
 *
 *  Function LED_init must be called before anything else.
 *	In this module you can find functions to turn on/off
 *	and LED.
 *
 *	LED must be with a pull-down resistor of 60 to 80 Ohms preferably.
 *
 *  @author João Duarte
 *
 */

#include "LED.h"

unsigned pin;
unsigned mask;
unsigned GPIOport;

//
// Led must be with a pull-down resistor of 60 to 80 Ohms
//
void LED_init(uint32_t gpio_port, uint32_t pin_number, uint32_t state){
	pin = pin_number;
	GPIOport=gpio_port;
	mask=1<<pin;
	//state=(~state)<<pin;
	//GPIO_config(mask, mask , state<<pin );
	GPIO_config_bitGeneric(gpio_port, 0, mask, mask, state<<pin );
}

uint32_t LED_GetState(){
	return (GPIO_input(GPIOport)) & mask;
}

void LED_SetState(uint32_t state){
	if(state)
		GPIO_SetGeneric(GPIOport, 1<<pin);
	else GPIO_ClearGeneric(GPIOport, 1<<pin);

	//pull-up before
	//state=(~state)<<pin;
	//GPIO_output(mask & state, mask);
}

