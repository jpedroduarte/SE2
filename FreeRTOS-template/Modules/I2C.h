#ifndef __I2C_H__
#define __I2C_H__

#include "GPIO.h"

void I2C_config(uint32_t controller, uint32_t freq);

uint32_t I2C_Transfer(uint32_t controller, uint8_t control_byte, char *data, uint32_t size, uint8_t WriteNotRead, uint8_t repeat);

static void I2C_WriteByte(LPC_I2C_TypeDef* I2C, char *data);

static void I2C_ReadByte(LPC_I2C_TypeDef* I2C, char* data);

static LPC_I2C_TypeDef* I2C_Get_Controller(uint8_t controller);

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

#endif /* __I2C_H__ */
