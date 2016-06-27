/** @file SPI.c
 *  @brief Drivers for SPI
 *
 *  Function SPI_Init must be called before anything else.
 *	
 *	In this module you can find functionality to transfer
 *	data with SPI protocol.
 *	Using:
 *	P0.4 SCK
 *	P0.6 MOSI
 *	P0.7 SSEL
 *	For communication with LCD Nokia 6610.
 *	@author João Duarte
 */

#include "SPI.h"

/* Faz a iniciação do controlador, configurando os pinos, o ritmo de envio e o
numero de bits de dados. */

//P0.4-> CS ,P0.5-> BL
//P0.6-> SSEL1 ,P0.7->SCK1, P0.8->MISO1

//run LCD Nokia at ~10MHz
void SPI_Init(int frequency, int bitData){		
	LPC_SC->PCONP= LPC_SC->PCONP | PCONP_PCSPI;
	//LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~0x2A000) | 0x2A000; //P0.4,P0.5,P0.6
	//select SPI function 11 for the SPI pins
	LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~0xC0000000) | 0xC0000000;
	LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~0x3C) | 0x3C;
	LPC_PINCON->PINMODE0= (LPC_PINCON->PINMODE0 & ~0xA0000000) | 0xA0000000;
	LPC_PINCON->PINMODE1= (LPC_PINCON->PINMODE1 & ~0x2A) | 0x2A;
	//LPC_SC->PCLKSEL0= (LPC_SC->PCLKSEL0 & ~0x30000) | 0x30000;
	//GPIO_configDigitalGeneric(0,2,0,SPI_PINS_MASK,0);
	LPC_SPI->SPCCR = frequency;
	LPC_SPI->SPCR = 0x34 | bitData<<8; // 0x920 The SPI operates in Master mode.  e meter a 9 pq 8 data e 1 controlo
   unsigned char dummy = LPC_SPI->SPSR; // read SPI status reg to clear the flags.
}

/* Coloca ativo o chip select do dispositivo slave */
void SPI_BeginTransfer(int csBitId){
	//meter csBitId a zero
    //GPIO_output(0,csBitId);
    GPIO_Clear(csBitId);
}

/* Coloca desativo o chip select do dispositivo slave */
void SPI_EndTransfer(int csBitId){
	//meter i csBitId  = 1
     //GPIO_output(csBitId,csBitId);
     GPIO_Set(csBitId);
}

/* Realiza uma transferencia. */
void SPI_Transfer(unsigned short *txBuffer, unsigned short *rxBuffer, int length){
	int i;
	for (i = 0; i < length; i++) {
		LPC_SPI->SPDR = *txBuffer++; // load SPI transmiter register
		while (!(LPC_SPI->SPSR));// wait for transmission to complete
			*rxBuffer++ = LPC_SPI->SPDR; // read data from SPI data register
	}
}
