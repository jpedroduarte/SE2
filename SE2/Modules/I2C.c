#include "I2C.h"

static LPC_I2C_TypeDef** I2C_Controller_table={
		(LPC_I2C_TypeDef*)	LPC_I2C0,
		(LPC_I2C_TypeDef*)	LPC_I2C1,
		(LPC_I2C_TypeDef*)	LPC_I2C2
};


void I2C_config(uint8_t controller, uint32_t freq){
	// I2CONSET/I2CONCLR
	//bit 6 I2EN interface enable
	LPC_I2C_TypeDef* I2C= I2C_Get_Controller(controller);
	I2C->I2CONSET=0x40; //master mode

	//PINSEL0: P0.0 SDA1, P0.1 SCL1 -Function 11
	LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~0x18000000) | 0x18000000;

	//enable CLK on PCONP register
	uint32_t PCONP_masks[3]= {0x80,0x8000,0x4000000};
	LPC_SC->PCONP= (LPC_SC->PCONP & ~PCONP_masks[controller]) | PCONP_masks[controller];
	//select P0.1 and P0.2 with function 11
	GPIO_configDigitalGeneric(0,3,0x3,0x3,0);
	//select I2C pins with no pull-ups and open drain mode
	GPIO_configAnalogGeneric(0,2,0x3,0x3);

	//Clock settings
	//EEPROM 100KHz
	//SCLK= 100 MHz, PCLK= SCLK/4=25 MHz; 2500/100=250;
	//define I2SCLH
	I2C->I2SCLH=125;
	//define I2SCLL
	I2C->I2SCLL=125;


}

void I2C_Start(uint8_t controller){
	// I2CONSET/I2CONCLR
	//bit 5 STA START flag
	LPC_I2C_TypeDef* I2C= I2C_Get_Controller(controller);
	I2C->I2CONSET=0x20;

}

void I2C_Stop(uint8_t controller){
	// I2CONSET/I2CONCLR
	//bit 4 STO STOP flag
	LPC_I2C_TypeDef* I2C= I2C_Get_Controller(controller);
	I2C->I2CONSET=0x10;
}


void I2C_Write(uint8_t controller, uint8_t addr, void *data, uint32_t size){
	uint8_t* curr=data;
	LPC_I2C_TypeDef* I2C= I2C_Get_Controller(controller);
	I2C_Start(I2C);

	//TODO

}
/*
void* I2C_Transfer(uint8_t controller, void *data, uint32_t size, uint8_t direction){
	//direction = 0 Write , direction = 1 Read
	uint8_t acknowledgeMask = 0x100; //
	uint8_t* curr=data;
	uint8_t* dataResult = (uint32_t) malloc(size);
	uint8_t* dataResultCurr = dataResult;
	LPC_I2C_TypeDef* I2C= I2C_Get_Controller(controller);
	uint8_t waitingState;
	while(size > 0){
		I2C_Start(I2C);
		I2C->I2DAT = SLAVEADRESS || direction;
		waitingState = 1;

		while(waitingState)
		{
			uint8_t auxState = I2C->I2STAT && acknowledgeMask;
			switch(auxState) {
				case REPEATEDSTART :
			    case SLAR_AND_READ_ACK :
					waitingState = 0;
					break;
				case NOT_SLAVE_ACK  :
			    case SLAR_AND_READ_NOT_ACK :
			    case DATA_TRANSMITED_NOT_ACK  :
				case DATA_AND_ACK_False:
					I2C_Stop(I2C);
					waitingState = 0;
					break;
				case LOSTINFO :
					waitingState = 0;
					break;
				case SLAVE_ACK  :
 			    case DATA_RECEIVED_ACK :
			    case DATA_AND_ACK_True :
					I2C->I2DAT = *curr;
					*dataResultCurr = I2C->I2DAT;
					dataResultCurr += sizeOf(char);
					curr += sizeOf(char);
					size -= sizeOf(char) ; //8bits msg
					break;
			}
		}
	}
	I2C_Stop(I2C);
	return dataResult;
}
*/
void I2C_Write_Byte(LPC_I2C_TypeDef* I2C,void* data){
	memcpy(data, (void*)&I2C->I2DAT, sizeof(char));
}

void I2C_Read_Byte(LPC_I2C_TypeDef* I2C, void* data){
	memcpy((void*)&I2C->I2DAT, data, sizeof(char));
}

static LPC_I2C_TypeDef* I2C_Get_Controller(uint8_t controller){
	return (LPC_I2C_TypeDef*) I2C_Controller_table+controller;
}
