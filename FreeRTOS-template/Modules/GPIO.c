#include "GPIO.h"

//args: dir-> 0 input / 1 output
// Port0 reserved for GPIO




void GPIO_configDigital(uint32_t dir, uint32_t mask, uint32_t initValue){
	dir&= mask;
	initValue&=mask;
	LPC_GPIO0->FIODIR= ((LPC_GPIO0->FIODIR & ~mask) | dir	  	);
	LPC_GPIO0->FIOPIN= ((LPC_GPIO0->FIOPIN & ~mask) | initValue	);
}

// gpio_port (P0,P1,P2,P3 or P4)
// gpio_func can be 0, 1, 2 or 3
// dir 0 input / 1 output
// mask bits with 1 are to be configured
//
void GPIO_configDigitalGeneric(uint32_t gpio_port, uint32_t gpio_func, uint32_t dir, uint32_t mask, uint32_t initValue){
	if(gpio_func>3)return;
	__IO uint32_t* PINCON= (__IO uint32_t*)LPC_PINCON + gpio_port;
	uint8_t count=0;
	uint32_t curr_bit=0x1;
	uint32_t gpio_func_mask=0x3;
	while(count<=14){
		if(mask & curr_bit)
			*PINCON= ((*PINCON & ~gpio_func_mask) | (gpio_func<<(count*2)));
		++count;
		curr_bit<<=1;
		gpio_func_mask<<=2;
	}
	count=0;
	curr_bit=0x1;
	gpio_func_mask=0x3;
	PINCON+=1;
	while(count<=14){
		if(mask & curr_bit)
			*PINCON= ((*PINCON & ~gpio_func_mask) | (gpio_func<<(count*2)));
		++count;
		curr_bit<<=1;
		gpio_func_mask<<=2;
	}

	LPC_GPIO_TypeDef* GPIO= LPC_GPIO0+gpio_port;
	dir&= mask;
	initValue&=mask;
	//GPIO->FIOMASK=0;
	GPIO->FIODIR= ((GPIO->FIODIR & ~mask) | dir	  		);
	GPIO->FIOPIN= ((GPIO->FIOPIN & ~mask) | initValue	);
}

void GPIO_configAnalogGeneric(uint32_t gpio_port, uint32_t pins_func, uint32_t open_drain, uint32_t mask){
	__IO uint32_t* PINCON= (__IO uint32_t*)(&LPC_PINCON->PINMODE0) + gpio_port*2;
	uint8_t count=0;
	uint32_t curr_bit=0x1;
	uint32_t func_mask=0x3;
	while(count<=14){
		if(mask & curr_bit)
			*PINCON= ((*PINCON & ~func_mask) | (pins_func<<(count*2)));
		++count;
		curr_bit<<=1;
		func_mask<<=2;
	}
	count=0;
	curr_bit=0x1;
	func_mask=0x3;
	PINCON+=1;
	while(count<=14){
		if(mask & curr_bit)
			*PINCON= ((*PINCON & ~func_mask) | (pins_func<<(count*2)));
		++count;
		curr_bit<<=1;
		func_mask<<=2;
	}
	PINCON= (__IO uint32_t*)(&LPC_PINCON->PINMODE_OD0) + gpio_port;
	*PINCON= (*PINCON & ~mask) | (open_drain & mask);
}

void GPIO_output(uint32_t gpio_port, uint32_t value, uint32_t mask){
	LPC_GPIO_TypeDef* GPIO= LPC_GPIO0+gpio_port;
	GPIO->FIOPIN= ((GPIO->FIOPIN & ~mask) | (value & mask));
}

uint32_t GPIO_input(uint32_t gpio_port){
	LPC_GPIO_TypeDef* GPIO= LPC_GPIO0+gpio_port;
	return GPIO->FIOPIN;
}

void GPIO_config_bitGeneric(uint32_t gpio_port, uint32_t gpio_func, uint32_t dir, uint32_t mask, uint32_t initValue){
	LPC_GPIO_TypeDef* GPIO= LPC_GPIO0+gpio_port;
	//GPIO->FIOMASK= ~mask;
	GPIO->FIODIR= ((GPIO->FIODIR & ~mask) | dir	  );
	if(initValue) GPIO_SetGeneric(gpio_port, mask);
	else GPIO_ClearGeneric(gpio_port, mask);
}

void GPIO_config_bit(uint32_t dir, uint32_t mask, uint32_t initValue){
	LPC_GPIO0->FIODIR= (LPC_GPIO0->FIODIR & ~mask) | dir ;
	if(initValue) GPIO_Set(mask);
	else GPIO_Clear(mask);
}

//Sets GPIO pin to HIGH
void GPIO_SetGeneric(uint32_t gpio_port,uint32_t mask){
	LPC_GPIO_TypeDef* GPIO= LPC_GPIO0+gpio_port;
	//GPIO->FIOMASK= ~mask;
	GPIO->FIOSET=(LPC_GPIO0->FIOSET & ~mask) | mask;
}

//Sets GPIO pin to HIGH
void GPIO_Set(uint32_t mask){
	LPC_GPIO0->FIOSET=(LPC_GPIO0->FIOSET & ~mask) | mask;
}

void GPIO_ClearGeneric(uint32_t gpio_port,uint32_t mask){
	LPC_GPIO_TypeDef* GPIO= LPC_GPIO0+gpio_port;
	//GPIO->FIOMASK= ~mask;
	GPIO->FIOCLR=(LPC_GPIO0->FIOCLR & ~mask) | mask;
}

//Sets GPIO pin to LOW
void GPIO_Clear(uint32_t mask){
	LPC_GPIO0->FIOCLR= (LPC_GPIO0->FIOCLR & ~mask) | mask;
}
