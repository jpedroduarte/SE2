#include "Ethernet.h"
#include <stdio.h>

void Ethernet_init(uint8_t readCycleMode, uint8_t mac_address[6], uint8_t datapath){

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

	LPC_EMAC->Command= (LPC_EMAC->Command & ~Command_RMII_MASK) | RMII_MASK;

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
	if( (Ethernet_ReadFromPHY(1) && 1<<2) == 0)
		puts("PHY Link Status down");

	/* Half-Duplex */
	LPC_EMAC->MAC2= LPC_EMAC->MAC2 & ~0x1;	//set bit 0 to 0

	/* 100 Mbps */
	LPC_EMAC->SUPP= 1<<8;

	/* Set Station Address */
	LPC_EMAC->SA0= mac_address[0]<<8 | mac_address[1];
	LPC_EMAC->SA1= mac_address[2]<<8 | mac_address[3];
	LPC_EMAC->SA2= mac_address[4]<<8 | mac_address[5];

	/* Receive Broadcast and Perfect Match Packets */

	// ???

	/* Enable interrupts MAC Module Control Interrupt Enable Register */
	LPC_EMAC->IntEnable= 0xFFFFFFFF;

	/* Reset all ethernet interrupts in MAC module */
	LPC_EMAC->IntClear= 0xFFFFFFFF;

	/* Enable receive and transmit mode in ethernet core */
	#define TX_RX_MASK 0x3
	LPC_EMAC->Command |= TX_RX_MASK;

}

/*Notas:


*/

#define PHY_DEF_ADR 0b00001
#define MII_WR_TOUT -1
#define MIND_BUSY 0x1
#define MCMD_WRITE 0

void Ethernet_WriteToPHY (int reg, int writeval){
	unsigned int loop;
	LPC_EMAC->MADR= PHY_DEF_ADR<<8 | reg;
	LPC_EMAC->MWTD = writeval;
	for (loop = 0; loop < MII_WR_TOUT; loop++)
		if ((LPC_EMAC->MIND & MIND_BUSY) == 0)
			break;
}

#define MCMD_READ 0x1
#define MII_RD_TOUT -1

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



