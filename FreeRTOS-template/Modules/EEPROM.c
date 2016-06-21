/*
 * EEPROM.c
 *
 *  Created on: 08/06/2016
 *      Author: Red
 */


#include "EEPROM.h"

/*
void EEPROM_Init(uint32_t I2C_controller, uint32_t freq){
	I2C_config(I2C_controller,freq);
}
*/
void EEPROM_Write(void* addr_buffer, void* buffer, uint32_t size){
	uint8_t aux[size+ADDRESS_SIZE];
	merge(aux, addr_buffer, ADDRESS_SIZE, buffer, size);
	I2C_Transfer(I2C_CONTROLLER, CONTROL_BYTE, aux, size+ADDRESS_SIZE, WRITE, STOP);
}

void EEPROM_Read(void* addr_buffer, void * data_buffer, uint32_t size){
	//Load adress
	I2C_Transfer(I2C_CONTROLLER, CONTROL_BYTE, addr_buffer, ADDRESS_SIZE, WRITE, REPEATED_START);
	//Start reading
	I2C_Transfer(I2C_CONTROLLER, CONTROL_BYTE, data_buffer, size, READ, STOP);
}

void merge(void* dst, void* src1, uint32_t size1, void* src2, uint32_t size2){
	memcpy(dst,src1,size1);
	memcpy(dst+size1,src2,size2);
}

