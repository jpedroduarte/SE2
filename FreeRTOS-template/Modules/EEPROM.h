/**
* @file		EEPROM.h
* @brief	Drivers for EEPROM.
* @author	João Duarte
*/

#ifndef EEPROM_H_
#define EEPROM_H_

/** @defgroup EEPROM EEPROM
 * @ingroup EEPROM
 * This module provides functionality to write operations such as byte/page write
 *	and also random/sequencial read.
 * @{

 * @defgroup EEPROM_Public_Functions EEPROM Public Functions
 * @{
 */

#include "I2C.h"
#include <string.h>

#define CONTROL_BYTE 0b1010000
#define I2C_CONTROLLER 1
#define ADDRESS_SIZE 2

/**
 * @brief	Write in specified address the buffer data.
 * @param	addr_buffer pointer to the HIGH and LOW addresses, should be of size 2.
 * @param	buffer data pointer.
 * @param	size size of data.
 * @return	void
 */
void EEPROM_Write(void* addr_buffer, void* buffer, uint32_t size);

/**
 * @brief	Read in specified address to the buffer data.
 * @param	addr_buffer pointer to the HIGH and LOW addresses, should be of size 2.
 * @param	data_buffer data pointer in which there will be the result of the read opeartion.
 * @param	size size of data.
 * @return	void
 */
void EEPROM_Read(void* addr_buffer, void * data_buffer, uint32_t size);

/**
 * @brief	Saves in dst the data from src1 and src2 as an whole.
 * @param	dst destination pointer.
 * @param	src1 first data source.
 * @param	size1 size of src1.
 * @param	src2 second data source.
 * @param	size2 size of src2.
 * @return	void
 */
static void merge(void* dst, void* src1, uint32_t size1, void* src2, uint32_t size2);


/**
 * @}
  */

/**
 * @}
 */
#endif /* EEPROM_H_ */
