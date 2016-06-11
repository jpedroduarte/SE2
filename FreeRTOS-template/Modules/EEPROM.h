/*
 * EEPROM.h
 *
 *  Created on: 08/06/2016
 *      Author: Red
 */

#ifndef EEPROM_H_
#define EEPROM_H_


#include "../FreeRTOS-template/Modules/I2C.h"


#define CONTROL_BYTE 0b1010000
#define I2C_CONTROLLER 1
#define ADDRESS_SIZE 2

void EEPROM_Init(uint32_t I2C_controller, uint32_t freq);

void EEPROM_Write(void* buffer, uint32_t size);

void EEPROM_Read(void* addr_buffer, void * data_buffer, uint32_t size);

#endif /* EEPROM_H_ */
