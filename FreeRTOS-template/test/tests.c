/** @file tests.c
 *  @brief Module with all sorts of tests.
 *
 *  @author João Duarte
 *
 */


#include "tests.h"


//
//Ethernet
//


void EthernetTest(){
	uIPmain();
}


/* App */
void KeyTest(){	//Working
	uint32_t layout[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	KBD_init(layout);
	uint32_t keyCode=0, aux;
	uint8_t count;
	for(count=0; count<4;++count){
		//Get a key
		aux= KBD_read();
		keyCode |= aux<<(count*8);
		printf("Key= 0x%X\n",keyCode);
	}
}

//
//RTC
//

int secs = 30, mins = 38, hours = 17, wdays = 1, days = 7, mons = 6, years = 2016, yday = 13;
struct tm dateTime;
void GetDatetimeTask(void){
	while(1){
		RTC_GetValue(&dateTime);
		printf("%u/%u/%u --- %u:%u:%u\n",dateTime.tm_mday,dateTime.tm_mon,dateTime.tm_year,dateTime.tm_hour,dateTime.tm_min,dateTime.tm_sec);
		vTaskDelay(1000);
	}
}

void RTCTest(){		//Working
	dateTime.tm_sec = secs;
	dateTime.tm_min = mins;
	dateTime.tm_hour = hours;
	dateTime.tm_wday = wdays;
	dateTime.tm_mday = days;
	dateTime.tm_mon = mons;
	dateTime.tm_year = years;
	dateTime.tm_yday = yday;

	RTC_Init(&dateTime);
	xTaskCreate(GetDatetimeTask, "RTC_GetDateTime", configMINIMAL_STACK_SIZE, NULL, 0 , NULL);
	vTaskStartScheduler();
	while(1);

}

//
//Tasks
//

uint32_t varExample[]={1,2,3};
void varExampleTask(void * pvParameters){
	int i=0;
	while(i<3){
		//uint32_t aux= (uint32_t)
		printf("var: %u ", *((uint32_t*)pvParameters)+ i++);
		vTaskDelay(1000);
	}
}

void varExampleTaskTest(){	//Working
	xTaskCreate(varExampleTask, "varExample", configMINIMAL_STACK_SIZE, varExample, 0 , NULL);
	vTaskStartScheduler();
	while(1);
}



//
//LED
//

void blinkLed(void)
{
	GPIO_config_bitGeneric(2,0,0x1000,0x1000,0);
	while(1){
		GPIO_SetGeneric(2,0x1000);
		vTaskDelay(500);
		GPIO_ClearGeneric(2,0x1000);
		vTaskDelay(500);
	}
}


void blinkLedLib(void)
{
	LED_init(2,12,0);
	while(1){

		LED_SetState(1);
		printf("LED is: %s --- should be on\n",LED_GetState()==0?"off":"on");
		vTaskDelay(2000);
		LED_SetState(0);
		printf("LED is: %s --- should be off\n",LED_GetState()==0?"off":"on");
		vTaskDelay(2000);
	}
}


void ledTest(){	//working
	xTaskCreate(blinkLedLib, "ledTest", configMINIMAL_STACK_SIZE, NULL, 0 , NULL );
	vTaskStartScheduler();
	while(1);
}


//
//KBD
//

void setKey1(void)
{
	uint32_t key=0;
	while(1){
		if(uxQueueSpacesAvailable(queue) > 0){
			key=KBD_read_nonBlocking();
			if(key!=-1){
				xQueueSend(queue,&key,1000);
				printf("Put %u in queue.\n",key);
			}else puts("No key pressed");
		}else{
			puts("Queue is full.\n");
		}
		vTaskDelay(0);
		//vTaskDelay(0);//taskYIELD();
	}

	//*(uint32_t*)pvParameters=key;
	//taskYIELD();
}
void getKey1(void){
	uint32_t currKey=0;
	uint8_t i =0, l=0;
	while(1){
		if(xQueueReceive(queue,&currKey,1000)){
			printf("Got %u from queue.\n",currKey);
			//printf("Elements in queue: %u\n",uxQueueMessagesWaiting(queue));
		}else{
			puts("No Keys in queue.\n");
		}
		vTaskDelay(1000);
	}
}

void getKey1LCD(void){
	uint32_t currKey=0;
	uint8_t i =0, l=0;
	while(1){
		if(xQueueReceive(queue,&currKey,1000)){
			printf("Get %u from queue.\n",currKey);
			if(i>15*7){
				i=0;
				LCD_Goto(l,i);
			}
			++i;
			LCD_WriteChar('0'+currKey);

			//printf("Elements in queue: %u\n",uxQueueMessagesWaiting(queue));
		}else{
			puts("No Key found.\n");
		}
		vTaskDelay(0);
	}
}


void kbdTest(){	//Working
	uint32_t layout[]={0,1,2,3,4,5,6,7,8,9,17,18,19,20,21,22};
	KBD_init(layout);
	SPI_Init(128,9);
	LCD_Init();
	LCD_TurnOnDisplay();
	LCD_BL_State(1);

	puts("start");
	while(1){
		//int key= KBD_read_nonBlocking();
		int key= KBD_read_nonBlocking();
		if(key != -1){
			printf("Get %u from queue.\n",key);
		}else{
			//puts("No key");
		}
	}

	/*
	queue = xQueueCreate(4,sizeof(uint32_t));
	if(queue==NULL){
		puts("queue init error\n");
	}

	xTaskCreate(setKey1, "setKey", configMINIMAL_STACK_SIZE, NULL, 0 , NULL );
	xTaskCreate(getKey1, "getKey", configMINIMAL_STACK_SIZE, NULL, 0 , NULL );
	vTaskStartScheduler();
	*/
}

void kbdLCDTest(){	//Working
	uint32_t layout[]={0,1,2,3,4,5,6,7,8,9,17,18,19,20,21,22};
	KBD_init(layout);
	SPI_Init(128,9);
	LCD_Init();
	LCD_TurnOnDisplay();
	LCD_BL_State(1);

	puts("start");


	queue = xQueueCreate(4,sizeof(uint32_t));
	if(queue==NULL){
		puts("queue init error\n");
	}

	xTaskCreate(setKey1, "setKey", configMINIMAL_STACK_SIZE, NULL, 0 , NULL );
	xTaskCreate(getKey1LCD, "getKey", configMINIMAL_STACK_SIZE, NULL, 0 , NULL );
	vTaskStartScheduler();

}



//
//LCD
//


void lcdTest(){	//Working
	//SPI_Init(8,9);
	//SPI_Init(254,9);
	SPI_Init(128,9);
	LCD_Init();
	LCD_TurnOnDisplay();
	//LCD_BL_State(0);
	LCD_BL_State(1);

	uint8_t i =0;
	while(1){
		LCD_Goto(0,i++);
		LCD_WriteString("Hello World");
	}
	/*
	while(1){
		LCD_WriteChar('t');
		LCD_Goto(0,i++);
		LCD_WriteChar('t');
		LCD_Goto(0,i++);
	}
	*/
}


//
//EEPROM
//

void eepromTest(){	//Working
	uint32_t freq=0;
	uint8_t ADDRESS_HIGH=0, ADDRESS_LOW=0;
	char control_code=0xA, CS_bits=0x0, Write=0, Read=1;
	char data[10], setAddrRead[2], res[8];
	data[0]= ADDRESS_HIGH;
	data[1]= ADDRESS_LOW;
	data[2]= 0x1;
	data[3]= 0x2;
	data[4]= 0x3;
	data[5]= 0x4;
	data[6]= 0x5;
	data[7]= 0x6;
	data[8]= 0x7;
	data[9]= 0x8;

	setAddrRead[0]= ADDRESS_HIGH;
	setAddrRead[1]= ADDRESS_LOW;

	res[0]= 0x1;
	res[1]= 0x1;
	res[2]= 0x1;
	res[3]= 0x1;
	res[4]= 0x1;
	res[5]= 0x1;
	res[6]= 0x1;
	res[7]= 0x1;

	I2C_config(1, freq);
	EEPROM_Write(setAddrRead, data,10);
	EEPROM_Read(setAddrRead, res, 8);
	/*
	//Write 5 in adress 0
	I2C_Transfer(1, CONTROL_BYTE, data, sizeof(data), Write,STOP);
	//Set random read mode to adress 0
	I2C_Transfer(1, CONTROL_BYTE, setAddrRead, sizeof(setAddrRead), Write, REPEATED_START);
	//Force a repeated start and read from adress 0
	I2C_Transfer(1, CONTROL_BYTE, res, sizeof(res), Read,STOP);
	*/
	int i;
	for(i=0; i<8; ++i)
		printf("Mem[%u]=%u\n", i, res[i]);
}

void projTest(){
	I2C_config(1, 100);
	if(verifyBootLoad()==0){
		puts("Not correct.");
		resetBootLoad();
	}else puts("Correct.");
	uint8_t addr[2]={0,0};
	uint8_t aux[4]={5,5,5,5};
	EEPROM_Write(addr, aux, 4);
	uint8_t read[48];
	EEPROM_Read(addr,read,48);
	int i;
	uint8_t* bla=(uint8_t*)read;
	for(i=0; i<48; ++i){
		printf("Mem[%u]= %X\n",i,*(bla+i));
	}

}

void auxEEPROMTest(){
	I2C_config(1, 100);

	uint8_t addr[2]={0x1,0};
	uint8_t buffer[5]={8,9,10,11,12};
	uint8_t read[5];
	EEPROM_Write(addr, buffer,5);
	EEPROM_Read(addr,read,5);
	uint16_t addr1=8;
	uint32_t wbuf=0x04030201;
	uint32_t rbuf=0xFFFFFFFF;
	//EEPROM_Write(&addr1, &wbuf,4);
	//EEPROM_Read(&addr1,&rbuf,4);
	uint8_t* bla=(uint8_t*)&rbuf;
	int i;
	for(i=0; i<48; ++i){
		printf("Mem[%u]= %X\n",i,*(bla+i));
	}
}

void getBootLoadCode(){

	I2C_config(1, 100);
	//resetFlash();
	uint16_t addr= getFormatedAddress(16);
	uint32_t read= 0x0;
	/*
	uint8_t* aux=(uint8_t*) &addr;
	puts("var:\n");
	printf("mem[0]=0x%X\n",*aux);
	printf("mem[1]=0x%X\n",*(aux+1));
	puts("array\n");
	printf("mem[0]=0x%X\n",addr1[0]);
	printf("mem[1]=0x%X\n",addr1[1]);
	*/
	EEPROM_Read(&addr, &read,4);
	printf("BootLoadCode= 0x%X\n",read);
}

void getKeyCode(){
	uint8_t src[4]={4,3,2,1};
	uint32_t key = getKeyFromArray(src);
	uint32_t count;//= keyCode[0]
	for(count=0; count<4;++count){
		key+=src[count]<<(8*count);
	}
	printf("Key: 0x%X\n",key);
}


void getSettings(){
	I2C_config(1, 100);
	uint16_t addr= 0;
	Settings1 s;

	EEPROM_Read(&addr, &s,sizeof(Settings1));

	uint8_t * bla= (uint8_t*)&s;
	int i=0;
	for(i=0; i<48; ++i){
		printf("Mem[%u]= %X\n",i,*(bla+i));
	}
}

uint8_t address[2]={0,0};
uint8_t read_buffer[10];
	uint8_t buffer[10];
void cleanEEPROM(){
	I2C_config(1,100);
	int ab;

	for(ab=0; ab<5; ++ab){
		puts("\n");
		int add=0;
		for(; add<10; ++add)
			buffer[add]=ab;
		add=0;
		EEPROM_Write(address, buffer, 10);

		/* Read */
		for(add=0; add<10; ++add)
				read_buffer[add]=3;

		EEPROM_Read(address, read_buffer, 10);
		uint8_t * bla= (uint8_t*)read_buffer;
		int i=0;
		for(i=0; i<10; ++i){
			printf("Mem[%u]= %X\n",i,*(bla+i));
		}
	}
}

