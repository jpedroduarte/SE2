/** @file Ethernet.c
 *  @brief Drivers for Ethernet.
 *
 *  Function Ethernet_init must be called before anything else.
 *
 *
 *  @author João Duarte
 *
 */

#include "Ethernet.h"
#include <stdio.h>

/// todo Teste do professor
#include "tapdev.h"

/*-------------------------------------------------------------------------------------*/

void Ethernet_init(uint8_t readCycleMode, uint8_t mac_address[6], uint8_t datapath){

	int timeout;
	uint32_t reg;
	//set PCENET in PCONP
	LPC_SC->PCONP |=PCONP_PCENET_MASK;

	// clock config

	//PINSEL config
	#define GPIO_PORT 1
	#define GPIO_FUNC 1
	#define OUTPUT 1
	#define MASK 0x3C713
	#define INIT_VALUE 0
	GPIO_configDigitalGeneric(GPIO_PORT, GPIO_FUNC, OUTPUT, MASK, INIT_VALUE);

	//PINMODE config
	#define PINMODE_FUNC GPIO_NO_PULL
	#define OPEN_DRAIN GPIO_OPEN_DRAIN_DISABLE
	GPIO_configAnalogGeneric(GPIO_PORT, PINMODE_FUNC, OPEN_DRAIN, MASK);

	//Initialization
#define MAC_SOFT_RESET 0x8000
	LPC_EMAC->MAC1= LPC_EMAC->MAC1 & ~MAC_SOFT_RESET;

	//configure read cycle mode
	LPC_EMAC->MCMD= (LPC_EMAC->MCMD & ~0x3) | readCycleMode;



	//Select RMII
#define Command_RMII_MASK 0x20

	LPC_EMAC->Command |= Command_RMII_MASK;

	LPC_EMAC->RxDescriptor= RX_DESC_BASE;
	LPC_EMAC->RxStatus= RX_STAT_BASE;
	LPC_EMAC->RxDescriptorNumber= NUM_RX_FRAG;
	//RxProduceIndex=0;
	//__IO uint32_t RxConsumeIndex;
	LPC_EMAC->TxDescriptor=TX_DESC_BASE;
	LPC_EMAC->TxStatus= TX_STAT_BASE;
	//__IO uint32_t TxDescriptorNumber;
	LPC_EMAC->TxProduceIndex=0;
	//LPC_EMAC->TxConsumeIndex=0;

	/* restart */
	Ethernet_WriteToPHY (0, 1<<15);

	/* wait for restart to complete */
	while(1)
		if( (Ethernet_ReadFromPHY(0) && 1<<15) == 0)
			break;

	/* enable auto-negotiation */
	Ethernet_WriteToPHY(0,1<<12);

	/* wait for auto-negotiation to complete */
	while(1)
		if( (Ethernet_ReadFromPHY(1) && 1<<5) == 0)
			break;

	/* check link status */
	for(timeout=0; timeout< 0x100000; timeout++){
		reg=Ethernet_ReadFromPHY(1);
		if(reg & 1<<2)
			break;
	}

	if (timeout >= 0x100000){
		//puts("Link status off. Shutting down Ethernet_init.");
		return;
	}

	/* Configure Full/Half Duplex mode. */
	if(reg & 0x4){
		/* Full Duplex */
		LPC_EMAC->MAC2 		|= 1<<0;
		LPC_EMAC->Command 	|= 1<<10;
		LPC_EMAC->IPGT 		 = 0x15;
	}else{
		/* Half Duplex */
		LPC_EMAC->IPGT = 0x12;
	}

	/* Configure 100MBit or 10MBit mode. */
	if(reg & 0x2){
		/* 10MBit mode*/
		LPC_EMAC->SUPP= 0;
	}else{
		/* 100MBit mode*/
		LPC_EMAC->SUPP= 1<<8;
	}

	/* Set Station Address */
	LPC_EMAC->SA0= mac_address[0]<<8 | mac_address[1];
	LPC_EMAC->SA1= mac_address[2]<<8 | mac_address[3];
	LPC_EMAC->SA2= mac_address[4]<<8 | mac_address[5];

	/* Receive Broadcast and Perfect Match Packets */
#define ACCEPT_BROADCAST_EN 1<<0
#define ACCEPT_PERFECT_EN 1<<5
	LPC_EMAC->RxFilterCtrl= ACCEPT_PERFECT_EN | ACCEPT_BROADCAST_EN;

	/* Enable interrupts MAC Module Control Interrupt Enable Register */
	LPC_EMAC->IntEnable= 1<<7 | 1<<3;

	/* Reset all ethernet interrupts in MAC module */
	LPC_EMAC->IntClear= 0xFFFFFFFF;

	/* Enable receive and transmit mode in ethernet core */
	#define TX_RX_MASK 0x3
	LPC_EMAC->Command |= TX_RX_MASK;
	#define RECEIVE_ENABLE 0x1
	LPC_EMAC->MAC1 |= RECEIVE_ENABLE;
}

/*-------------------------------------------------------------------------------------*/


void Ethernet_WriteToPHY (int reg, int writeval){
	unsigned int loop;
	LPC_EMAC->MADR= PHY_DEF_ADR<<8 | reg;
	LPC_EMAC->MWTD = writeval;
	for (loop = 0; loop < MII_WR_TOUT; loop++)
		if ((LPC_EMAC->MIND & MIND_BUSY) == 0)
			break;
}

/*-------------------------------------------------------------------------------------*/

unsigned short Ethernet_ReadFromPHY (unsigned char reg){
	unsigned int loop;
	LPC_EMAC->MADR=PHY_DEF_ADR|reg;
	LPC_EMAC->MCMD = MCMD_READ;
	for (loop = 0; loop < MII_RD_TOUT; loop++)
		if ((LPC_EMAC->MIND & MIND_BUSY) == 0)
			break;
	LPC_EMAC->MCMD = 0; // Cancel read
	// Returned value is in MII Mgmt Read Data Register
	return (LPC_EMAC->MRDD);
}

/*-------------------------------------------------------------------------------------*/

void tapdev_init(void){
	/* MAC ADDRESS */
	uint8_t mac_addr[6]={6,5,4,3,2,1};
	Ethernet_init(EMAC_NO_READ_NO_SCAN_MODE, mac_addr, EMAC_RX_ENABLE | EMAC_TX_ENABLE);
}

/*-------------------------------------------------------------------------------------*/

unsigned int tapdev_read(void){
	//todo
}

/*-------------------------------------------------------------------------------------*/


/*Transmite um pacote Ethernet para o controlador.
A variavel global uip_buf contem os dados, uip_len a dimensão.*/


uint32_t * Txpointer;

void tapdev_send(void){

	/* TX array is full? */
	//If the RxProduceIndex equals
	//RxConsumeIndex - 1, the array is full and any

	/* Set up the descriptor */
	uint32_t pi= LPC_EMAC->TxProduceIndex;
	//Txpointer=

	/* Update TxProduceIndex */


}

/*-------------------------------------------------------------------------------------*/


