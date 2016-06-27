/**
* @file		I2C.h
* @brief	Drivers for I2C.
* @author	João Duarte
*/
#ifndef __I2C_H__
#define __I2C_H__

/** @defgroup I2C I2C
 * @ingroup I2C
 * This module provides functionality to manage any I2C controller from LPC1769 and the likes.
 * I2C_config must be called before any I2C use.
 * @{

 * @defgroup I2C_Public_Functions I2C Public Functions
 * @{
 */

#include "GPIO.h"

/**
 * @brief	Configures the specific I2C controller to be ready for use.
 * @param	uint32_t controller - the controller number to
 * @param	uint32_t freq - The frequency to set in the I2C controller.
 * @return	void
 */
void I2C_config(uint32_t controller, uint32_t freq);

/**
 * @brief	Produces a I2C transfer.
 * @param	uint32_t controller - the controller number to
 * @param	uint8_t control_byte - the control code and chip select bits
 * @param	uint8_t *data - the buffer to read/write from/to.
 * @param	uint32_t size - the size of the data buffer.
 * @param	uint8_t WriteNotRead - !0 is Write, 0 is Read
 * @param	uint8_t repeat - !0 is a transfer that ends with a REPEATED START, 0 ends with a STOP.
 * @return	returns the value of the I2C status register.
 */
uint32_t I2C_Transfer(uint32_t controller, uint8_t control_byte, uint8_t *data, uint32_t size, uint8_t WriteNotRead, uint8_t repeat);

/**
 * @brief	Writes a byte in I2DAT register.
 * @param	LPC_I2C_TypeDef* I2C - pointer to I2C controller struct.
 * @param	uint8_t *data - pointer to data byte.
 * @return	void
 */
static void I2C_WriteByte(LPC_I2C_TypeDef* I2C, uint8_t *data);

/**
 * @brief	Reads a byte from I2DAT register.
 * @param	LPC_I2C_TypeDef* I2C - pointer to I2C controller struct.
 * @param	uint8_t *data - pointer to data byte.
 * @return	void
 */
static void I2C_ReadByte(LPC_I2C_TypeDef* I2C, uint8_t* data);

/**
 * @brief	Gets a pointer to the I2C controller struct given the number.
 * @param	uint8_t controller - the number os the I2C controller.
 * @return	pointer to I2C controller struct.
 */
static LPC_I2C_TypeDef* I2C_Get_Controller(uint8_t controller);

/**
 * @brief	Clear I2CEN bit.
 * @param	uint8_t controller - the number os the I2C controller.
 * @return	void
 */
void I2C_Disable(uint8_t controller);

/* I2C STATES */

#define READ 1
#define WRITE 0
#define REPEATED_START 1
#define STOP 0

//CONSET States

#define AA 0x4
#define SI 0x8
#define STO 0x10
#define STA 0x20
#define I2EN 0x40

//CONCLR States
#define AAC 0x4
#define SIC 0x8
#define STAC 0x20
#define I2ENC 0x40


#define BUS_ERROR 0x00
#define START 0x08
#define R_START 0x10

//Master Transmitter states
#define SLAW_ACK 0x18
#define SLAW_NOT_ACK 0x20
#define DATA_TRANSMITED_ACK 0x28
#define DATA_TRANSMITED_NOT_ACK 0x30
#define BUS_RELEASED 0x38

//Master Receive States
#define SLAR_ACK 0x40
#define SLAR_NOT_ACK 0x48
#define DATA_RECEIVED_ACK 0x50
#define DATA_RECEIVED_NOT_ACK 0x58

/**
 * @}
  */

/**
 * @}
 */

#endif /* __I2C_H__ */
