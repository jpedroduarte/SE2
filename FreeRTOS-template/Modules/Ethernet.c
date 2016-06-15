#include "Ethernet.h"

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

	//Set Station Address
	LPC_EMAC->SA0= mac_address[0]<<8 | mac_address[1];
	LPC_EMAC->SA1= mac_address[2]<<8 | mac_address[3];
	LPC_EMAC->SA2= mac_address[4]<<8 | mac_address[5];

	//Select RMII
#define RMII_MASK 0x20

	LPC_EMAC->Command= (LPC_EMAC->Command & ~RMII_MASK) | RMII_MASK;
	//configure datapaths
#define TX_RX_MASK 0x3
	LPC_EMAC->Command= (LPC_EMAC->Command & ~TX_RX_MASK) | datapath;

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
}

/*Notas:


*/

#define PHY_DEF_ADR 0b00001	// perguntar
#define MII_WR_TOUT 0		// perguntar
#define MIND_BUSY 0x1

void WriteToPHY (int reg, int writeval){

	unsigned int loop;
	// Set up address to access in MII Mgmt Address Register
	LPC_EMAC->MADR= PHY_DEF_ADR<<12 | reg;
	// Write value into MII Mgmt Write Data Register
	LPC_EMAC->MWTD = writeval;
	// Loop write to PHY completes
	for (loop = 0; loop < MII_WR_TOUT; loop++)
		if ((LPC_EMAC->MIND & MIND_BUSY) == 0)
			break;
}

#define MCMD_READ 0x1
#define MII_RD_TOUT 0	// perguntar

unsigned short ReadFromPHY (unsigned char reg){

	unsigned int loop;
	// Set up address to access in MII Mgmt Address Register
	LPC_EMAC->MADR=PHY_DEF_ADR|reg;
	// Trigger a PHY read via MII Mgmt Command Register
	LPC_EMAC->MCMD = MCMD_READ;
	// Loop read from PHY completes
	for (loop = 0; loop < MII_RD_TOUT; loop++)
		if ((LPC_EMAC->MIND & MIND_BUSY) == 0)
			break;
	LPC_EMAC->MCMD = 0; // Cancel read
	// Returned value is in MII Mgmt Read Data Register
	return (LPC_EMAC->MRDD);
}



