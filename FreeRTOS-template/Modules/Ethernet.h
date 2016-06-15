/*
 * Ethernet.h
 *
 *  Created on: 24/05/2016
 *      Author: Red
 */

#ifndef ETHERNET_H_
#define ETHERNET_H_

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

/* Functions */

void Ethernet_init(uint8_t readCycleMode, uint8_t mac_address[6], uint8_t datapath);

void Ethernet_WriteToPHY (int reg, int writeval);

unsigned short Ethernet_ReadFromPHY (unsigned char reg);

#endif /* ETHERNET_H_ */
