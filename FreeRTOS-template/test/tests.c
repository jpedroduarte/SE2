/*
 * tests.c
 *
 *  Created on: 07/06/2016
 *      Author: Red
 */

#include "../../FreeRTOS_Library/include/FreeRTOS.h"
#include "../../FreeRTOS_Library/include/task.h"

#include <stdio.h>
#include "LPC17xx.h"
#include "../Modules/GPIO.h"
#include "../Modules/KBD.h"
#include "../Modules/LCD.h"
#include "../Modules/SPI.h"
#include "../Modules/EEPROM.h"
#include "../Modules/RTC.h"
#include "../Modules/LED.h"

#include "queue.h"
#include "semphr.h"



//
//Ethernet
//
#include "../FreeRTOS-template/Ethernet_Prof_Test/tapdev.h"


void EthernetTest(){
	//uIPmain();
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
		if(uxQueueMessagesWaiting(queue)==0){
			key=KBD_read();
			if(key!=0){
				xQueueSend(queue,&key,1000);
				printf("Put %u in queue.\n",key);
			}else puts("No key pressed");
		}else{
			puts("Key still in queue\n");
		}
		vTaskDelay(0);//taskYIELD();
	}

	//*(uint32_t*)pvParameters=key;
	//taskYIELD();
}

void setKey(void)
{
	uint32_t key=0;
	while(1){
		if(uxQueueMessagesWaiting(queue)==0){
			if(xSemaphoreTake(keysMutex,1000)){
				key=KBD_read();
				xQueueSend(queue,&key,1000);
				xSemaphoreGive(keysMutex);
			}
		}
		taskYIELD();
	}

	//*(uint32_t*)pvParameters=key;
	//taskYIELD();
}

void getKey1(void){
	uint32_t currKey=0;
	while(1){
		if(xQueueReceive(queue,&currKey,1000)){
			printf("Get %u from queue.\n",currKey);
			//printf("Elements in queue: %u\n",uxQueueMessagesWaiting(queue));
		}else{
			puts("Could not get Key.\n");
		}
		vTaskDelay(0);
	}
}

void getKey(void){
	uint32_t currKey=0;
	while(1){
		if(uxQueueMessagesWaiting(queue)!=0){
			if(xSemaphoreTake(keysMutex,1000)){
				if(xQueueReceive(queue,&currKey,1000)){
					GPIO_config_bitGeneric(2,0,0x1000,0x1000,0);
					while(currKey!=0){
						GPIO_SetGeneric(2,0x1000);
						vTaskDelay(500);
						GPIO_ClearGeneric(2,0x1000);
						vTaskDelay(500);
						--currKey;
					}
				}
				xSemaphoreGive(keysMutex);
			}
		}
		taskYIELD();
	}
}

void kbdTest(){	//Working
	uint32_t layout[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	KBD_init(layout);
	xTaskCreate(setKey1, "setKey", configMINIMAL_STACK_SIZE, NULL, 0 , NULL );
	xTaskCreate(getKey1, "getKey", configMINIMAL_STACK_SIZE, NULL, 0 , NULL );
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
	LCD_BL_State(0);
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
