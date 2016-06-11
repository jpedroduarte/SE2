#include "I2C.h"
#include "string.h"

static LPC_I2C_TypeDef* I2C_Controller_table[]={
	LPC_I2C0,
	LPC_I2C1,
	LPC_I2C2
};


void I2C_config(uint32_t controller, uint32_t freq){
	LPC_I2C_TypeDef* I2C= I2C_Get_Controller(controller);
	LPC_SC->PCLKSEL1 |= 0xC0;

	//PINSEL0 : P0.0 SDA1, P0.1 SCL1 - Function 3
	LPC_PINCON->PINSEL0 |= 0xF;
	LPC_PINCON->PINMODE0|= 0xA;
	LPC_PINCON->PINMODE_OD0|= 0x3;
	//enable CLK on PCONP register
	uint32_t PCONP_masks[3]= {0x80,0x80000,0x4000000};
	LPC_SC->PCONP= (LPC_SC->PCONP & ~PCONP_masks[controller]) | PCONP_masks[controller];
	//Clock settings
	//EEPROM 100KHz
	//SCLK= 100 MHz, PCLK= SCLK/4=25 MHz; 2500/100=250;
	//define I2SCLH

	I2C->I2SCLH=125;
	//define I2SCLL
	I2C->I2SCLL=125;
	I2C->I2CONSET= STO;
	I2C->I2CONCLR = SIC;
	I2C->I2CONSET=I2EN; //master mode
}

uint32_t I2C_Transfer(uint32_t controller,uint8_t control_byte, char *data_src, uint32_t size, uint8_t direction, uint8_t repeat){
	//direction = 0 Write , direction = 1 Read
	LPC_I2C_TypeDef* I2C= I2C_Get_Controller(controller);
	char *initialAddr= data_src;
	char *currAddr = data_src;
	char *finalAddr = ((char*)data_src + size * sizeof(char));
	I2C->I2CONSET = STA;
	//I2C->I2CONCLR = SIC;
	while(1){
		if(I2C->I2CONSET & SI){
			switch(I2C->I2STAT){
				case START:
				case R_START:
					//Set slave addr
					//I2C->I2DAT=control_code<<4 | SLA<<1 | direction;
					I2C->I2DAT=control_byte << 1 | direction;
					I2C->I2CONSET = AA;
					I2C->I2CONCLR = SIC;
					break;
				case SLAW_ACK:
					I2C_WriteByte(I2C, currAddr++);
					I2C->I2CONSET = AA;
					I2C->I2CONCLR = SIC|STAC;
					break;
				case SLAW_NOT_ACK:
					if(I2C->I2CONSET & STA){
						I2C->I2DAT=control_byte << 1 | direction;
						I2C->I2CONSET = AA;
						I2C->I2CONCLR = SIC;
						break;
					}
					I2C->I2CONSET= STO;
					I2C->I2CONCLR = SIC;
					return I2C->I2STAT;
				case SLAR_ACK:
					I2C->I2CONSET = AA;
					I2C->I2CONCLR = SIC|STAC;
					break;
				case SLAR_NOT_ACK:
					I2C->I2CONSET = STO | AA;
					I2C->I2CONCLR = SIC;
					break;
				case DATA_RECEIVED_ACK:
					I2C_ReadByte(I2C, currAddr++);
					if(currAddr == finalAddr){ //last byte.
						I2C->I2CONCLR = SIC | AAC;
						return I2C->I2STAT;
					}
					I2C->I2CONSET = AA;
					I2C->I2CONCLR = SIC;
					break;
				case DATA_RECEIVED_NOT_ACK:
					I2C_ReadByte(I2C, currAddr);
					I2C->I2CONSET = STO | AA;
					I2C->I2CONCLR = SIC;
					return I2C->I2STAT;
				case DATA_TRANSMITED_ACK:
					if(currAddr == finalAddr){ //last byte.
						if(repeat==STOP)I2C->I2CONSET = STO;
						I2C->I2CONSET = AA;
						I2C->I2CONCLR = SIC;
						return I2C->I2STAT;
					}else{
						I2C_WriteByte(I2C, currAddr++);
						I2C->I2CONSET = AA;
						I2C->I2CONCLR = SIC;
					}
					break;
				case DATA_TRANSMITED_NOT_ACK:
					I2C->I2CONSET = STO | AA;
					I2C->I2CONCLR = SIC;
					return I2C->I2STAT;
				case BUS_RELEASED:
					I2C->I2CONSET = STA | AA;
					I2C->I2CONCLR = SIC;
					break;
				default:
					case BUS_ERROR:
						I2C->I2CONSET = STO;
					return I2C->I2STAT;
			}
		}
	}
}

static void I2C_WriteByte(LPC_I2C_TypeDef* I2C, char* data){
	I2C->I2DAT=*data;
	//memcpy(data, (void*)&I2C->I2DAT, sizeof(char));
}

static void I2C_ReadByte(LPC_I2C_TypeDef* I2C, char* data){
	*data=I2C->I2DAT;
	//memcpy((void*)&I2C->I2DAT, data, sizeof(char));
}

static LPC_I2C_TypeDef* I2C_Get_Controller(uint8_t controller){
	return I2C_Controller_table[controller];
}
