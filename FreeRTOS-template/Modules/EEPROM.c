/** @file EEPROM.c
 *  @brief Drivers for EEPROM.
 *
 *  Function I2C_config must be called before anything else.
 *	This module provides functionality to write operations such as byte/page write
 *	and also random/sequencial read.
 *
 *
 *  @author João Duarte
 *
 */


#include "EEPROM.h"


void EEPROM_Write(void* addr_buffer, void* buffer, uint32_t size){
	uint8_t aux[size+ADDRESS_SIZE];
	merge(aux, addr_buffer, ADDRESS_SIZE, buffer, size);
	I2C_Transfer(I2C_CONTROLLER, CONTROL_BYTE, aux, size+ADDRESS_SIZE, WRITE, STOP);
	//I2C_Disable(1);
}

void EEPROM_Read(void* addr_buffer, void * data_buffer, uint32_t size){
	//Load adress
	I2C_Transfer(I2C_CONTROLLER, CONTROL_BYTE, addr_buffer, ADDRESS_SIZE, WRITE, REPEATED_START);
	//Start reading
	I2C_Transfer(I2C_CONTROLLER, CONTROL_BYTE, data_buffer, size, READ, STOP);
}


static void merge(void* dst, void* src1, uint32_t size1, void* src2, uint32_t size2){
	memcpy(dst,src1,size1);
	memcpy(dst+size1,src2,size2);
}

