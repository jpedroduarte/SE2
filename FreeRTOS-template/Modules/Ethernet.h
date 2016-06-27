/**
* @file		Ethernet.h
* @brief	Drivers for Ethernet.
* @author	João Duarte
*/

#ifndef ETHERNET_H_
#define ETHERNET_H_

/** @defgroup Ethernet Ethernet
 * @ingroup Ethernet
 * This module provides functionality to manage the Ethernet controller from LPC1769 and the likes.
 * Ethernet_init must be called before any Ethernet use.
 * @{

 * @defgroup Ethernet_Public_Functions Ethernet Public Functions
 * @{
 */

#include "GPIO.h"


/* EMAC Memory Buffer configuration for 16K Ethernet RAM. */
#define NUM_RX_FRAG 4 /* Num.of RX Fragments 4*1536= 6.0kB */
#define NUM_TX_FRAG 2 /* Num.of TX Fragments 3*1536= 4.6kB */
#define ETH_FRAG_SIZE 1536 /* Packet Fragment size 1536 Bytes */
#define ETH_MAX_FLEN 1536 /* Max. Ethernet Frame Size */
/* EMAC variables located in AHB SRAM bank 1 */
#define RX_DESC_BASE 0x2007c000

#define RX_STAT_BASE (RX_DESC_BASE + NUM_RX_FRAG*8)

#define TX_DESC_BASE (RX_STAT_BASE + NUM_RX_FRAG*8)
#define TX_STAT_BASE (TX_DESC_BASE + NUM_TX_FRAG*8)

#define RX_BUF_BASE (TX_STAT_BASE + NUM_TX_FRAG*4)
#define TX_BUF_BASE (RX_BUF_BASE + NUM_RX_FRAG*ETH_FRAG_SIZE)

/* Masks */

#define PCONP_PCENET_MASK 40000000


/*Modes*/

#define EMAC_NO_READ_NO_SCAN_MODE 0
#define EMAC_READ_MODE 1
#define EMAC_SCAN_MODE 2

//Datapaths

#define EMAC_DATA_DISABLED 0
#define EMAC_TX_ENABLE 2
#define EMAC_RX_ENABLE 1

/* Read/Write PHY macros */

#define PHY_DEF_ADR 0b00001
#define MII_WR_TOUT 0xFFFFFFFF
#define MIND_BUSY 0x1
#define MCMD_WRITE 0

#define MCMD_READ 0x1
#define MII_RD_TOUT 0xFFFFFFFF

/* Functions */

/**
 * @brief	Configures Ethernet controller and the LAN chip
 * @param	uint8_t readCycleMode
 * @param	uint8_t mac_address[6]
 * @param	uint8_t datapath
 * @return	void
 */
void Ethernet_init(uint8_t readCycleMode, uint8_t mac_address[6], uint8_t datapath);

/**
 * @brief	Writes to LAN chip
 * @param	int reg
 * @param	int writeval
 * @return	void
 */
void Ethernet_WriteToPHY (int reg, int writeval);

/**
 * @brief	Reads from LAN chip
 * @param	int reg
 * @return	value of the register.
 */
unsigned short Ethernet_ReadFromPHY (unsigned char reg);

/**
 * @brief	Transmits an Ethernet packet.
 * @return	void
 */
void tapdev_send(void);

/**
 * @brief	Receives an Ethernet packet.
 * @return	unsigned int - the length of the packet.
 */
unsigned int tapdev_read(void);

/**
 * @}
  */

/**
 * @}
 */

#endif /* ETHERNET_H_ */
