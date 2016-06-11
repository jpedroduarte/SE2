/*
 * GPIO_Tests.c
 *
 *  Created on: 20/04/2016
 *      Author: Red
 */

#include "GPIO.h"

uint32_t GPIO_test0(){
	//GPIO_configDigital(uint32_t dir, uint32_t mask, uint32_t initValue)
	//GPIO_configDigital(0, 1, 0);
	//GPIO_configDigitalGeneric(uint32_t gpio_port, uint32_t gpio_func, uint32_t dir, uint32_t mask, uint32_t initValue){
	GPIO_configDigitalGeneric(2,0,0,0x100,0);
	//printf("0x%x",LPC_PINCON->PINMODE4&30000>>16);
	GPIO_configAnalogGeneric(2, 3, 0, 0x100);
	//printf("0x%x",LPC_PINCON->PINMODE4&30000>>16);
	return GPIO_input(2);
}

void GPIO_test1(){
	//GPIO_configDigitalGeneric(uint32_t gpio_port, uint32_t gpio_func, uint32_t dir, uint32_t mask, uint32_t initValue){
	GPIO_configDigitalGeneric(2,0,0x1000,0x1000,0x1000);
	GPIO_configDigitalGeneric(2,0,0x1000,0x1000,0);
	//GPIO_configDigitalGeneric(2,0,0x1000,0x1000,0x1000);
	GPIO_configAnalogGeneric(2, 3, 0, 0x1000);
	//GPIO_configAnalogGeneric(uint32_t gpio_port, uint32_t pins_func, uint32_t open_drain, uint32_t mask);

}

void GPIO_test2(){
	GPIO_config_bitGeneric(2,0,0x1000,0x1000,0);
	GPIO_SetGeneric(2,0x1000);
	GPIO_ClearGeneric(2,0x1000);
}

