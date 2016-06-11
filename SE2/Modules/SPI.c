/** @file SPI.c
 *  @brief Drivers for SPI on LPC2106
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
 */

#include "SPI.h"

/* Faz a iniciação do controlador, configurando os pinos, o ritmo de envio e o
numero de bits de dados. */

void SPI_Init(int frequency, int bitData){		
	LPC_PINCON->PINSEL0 = 0; // P0.4,P0.6,P0.7
	LPC_SC->PCONP= LPC_SC->PCONP | PCONP_PCSPI;
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
