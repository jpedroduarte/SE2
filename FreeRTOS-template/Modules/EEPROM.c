/*
 * EEPROM.c
 *
 *  Created on: 08/06/2016
 *      Author: Red
 */


#include "../FreeRTOS-template/Modules/EEPROM.h"

void EEPROM_Init(uint32_t I2C_controller, uint32_t freq){
	I2C_config(I2C_controller,freq);
}

void EEPROM_Write(void* buffer, uint32_t size){
	I2C_Transfer(I2C_CONTROLLER, CONTROL_BYTE, buffer, size, WRITE, STOP);
}

void EEPROM_Read(void* addr_buffer, void * data_buffer, uint32_t size){
	//Load adress
	I2C_Transfer(I2C_CONTROLLER, CONTROL_BYTE, addr_buffer, ADDRESS_SIZE, WRITE, REPEATED_START);
	//Start reading
	I2C_Transfer(I2C_CONTROLLER, CONTROL_BYTE, data_buffer, size, READ, STOP);
}

