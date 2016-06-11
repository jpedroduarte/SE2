/** @file SPI.h
 *  @brief Drivers for SPI on LPC2106
 *  @author G6
 */

#ifndef __SPI_H__
#define __SPI_H__
/** @defgroup SPI SPI
 * @ingroup SPI
 *  Function SPI_Init must be called before anything else.
 *	
 *	In this module you can find functionality to transfer
 *	data with SPI protocol.
 *	Using:
 *	P0.4 SCK
 *	P0.6 MOSI
 *	P0.7 SSEL
 *	For communication with LCD Nokia 6610.
 * @{

 * @defgroup SPI_Public_Functions SPI Public Functions
 * @{
 */
#include "GPIO.h"

#define SPI_PINS_MASK 0x38000
#define PCONP_PCSPI 0x100

 /** @brief Faz a iniciação do controlador, configurando os pinos, o ritmo de envio e o
 *	numero de bits de dados.Sets the current date and time values
 *  @return none
 */
void SPI_Init(int frequency, int bitData);

 /** @brief Coloca ativo o chip select do dispositivo slave
 *  @return none
 */
void SPI_BeginTransfer(int csBitId);

 /** @brief Coloca desativo o chip select do dispositivo slave
 *  @return none
 */
void SPI_EndTransfer(int csBitId);


 /** @brief Realiza uma transferencia.
 *  @return none
 */
void SPI_Transfer(unsigned short *txBuffer, unsigned short* arxBuffer, int lenght);


/**
 * @}
  */
  
/**
 * @}
 */
#endif /* __SPI_H__ */
