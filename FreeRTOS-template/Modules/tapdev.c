/*
 * tapdev.c
 *
 *  Created on: 14/06/2016
 *      Author: Red
 */


#include "tapdev.h"

void tapdev_init(void){
	/* MAC ADDRESS */
	uint8_t mac_addr[6]={6,5,4,3,2,1};
	Ethernet_init(EMAC_NO_READ_NO_SCAN_MODE, mac_addr, EMAC_RX_ENABLE | EMAC_TX_ENABLE);
}

unsigned int tapdev_read(void){

}

void tapdev_send(void){

}
