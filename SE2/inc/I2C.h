#ifndef __I2C_H__
#define __I2C_H__

#include "GPIO.h"

void I2C_config(uint8_t controller, uint32_t freq);

void I2C_Start(uint8_t cntroller);

void I2C_Stop(uint8_t controller);

void I2C_Transfer(uint8_t controller, void *data, uint32_t size, uint8_t direction);

void I2C_Write(uint8_t controller, uint8_t addr, void *data, uint32_t size);

void I2C_Read(LPC_I2C_TypeDef* I2C, void* data);

static LPC_I2C_TypeDef* I2C_Get_Controller(uint8_t controller);

/* I2C STATES */

#define BUS_ERROR 0x00
#define START 0x08
#define R_START 0x10

//Master Transmitter states
#define SLAVE_ACK 0x18
#define NOT_SLAVE_ACK 0x20
#define STOP 0x28
#define DATA_TRANSMITED_NOT_ACK 0x30
#define BUS_RELEASED 0x38

//Master Receive States
#define SLAR_AND_READ_ACK 0x40
#define SLAR_AND_READ_NOT_ACK 0x48
#define DATA_RECEIVED_ACK 0x50
#define DATA_RECEIVED_NOT_ACK 0x58

#endif /* __I2C_H__ */
