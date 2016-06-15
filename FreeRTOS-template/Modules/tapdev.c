/*
 * tapdev.c
 *
 *  Created on: 14/06/2016
 *      Author: Red
 */


#include "tapdev.h"

void tapdev_init(void){
	/* MAC ADDRESS */
	uint8_t mac_addr[6]={0,0,0,0,0,0};
	Ethernet_init(EMAC_NO_READ_NO_SCAN_MODE, mac_addr, EMAC_RX_ENABLE | EMAC_TX_ENABLE);
}

unsigned int tapdev_read(void){
	Ethernet_ReadFromPHY(0x0); // ???
}

void tapdev_send(void){
	Ethernet_WriteToPHY(0x0,0x0); // ???
}
