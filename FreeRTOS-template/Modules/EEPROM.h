/*
 * EEPROM.h
 *
 *  Created on: 08/06/2016
 *      Author: Red
 */

#ifndef EEPROM_H_
#define EEPROM_H_


#include "I2C.h"
#include <string.h>

#define CONTROL_BYTE 0b1010000
#define I2C_CONTROLLER 1
#define ADDRESS_SIZE 2

//void EEPROM_Init(uint32_t I2C_controller, uint32_t freq);

void EEPROM_Write(void* addr_buffer, void* buffer, uint32_t size);

void EEPROM_Read(void* addr_buffer, void * data_buffer, uint32_t size);

void merge(void* dst, void* src1, uint32_t size1, void* src2, uint32_t size2);

#endif /* EEPROM_H_ */
