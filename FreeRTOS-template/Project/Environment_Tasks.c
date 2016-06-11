/*
 * Environment_Tasks.c
 *
 *  Created on: 07/06/2016
 *      Author: Red
 */

#include "Environment_Tasks.h"

/* Main Task*/

void mainTaskFunc(){
	int key;
	while(1){
		//Get a key
		if(xQueueReceive(KBD_queue, &key, portMAX_DELAY) == pdTRUE){
			if(key==DOUBLE_KEY){
				//todo double key

				xTaskNotifyGive(AdminModeTask);
			}else{
				xTaskNotifyGive(UserModeTask);
			}
			ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		}
	}
}

void UserModeTaskFunc(){

	uint8_t leave_function=0;
	while(1){
//todo
		//block Thread until there is a notification
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		puts("User Mode");

		//LCD Autentication State todo

		uint8_t keyCode[4];
		uint8_t i;
		for(i=0; i<4;++i){
			if(xQueueReceive(KBD_queue, keyCode+i, portMAX_DELAY) == pdFALSE){
				//timeout occured
				leave_function=1;
				LCD_Clear(0xFFF);
				LCD_BL_State(0);
				break;
			}
		}
		xTaskNotifyGive(mainTask);
		if(leave_function)
			continue;

		//todo User Login



	}
}

void AdminModeTaskFunc(){

	while(1){
//todo
		//block Thread until there is a notification
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		puts("Admin Mode");

		//Authentication LCD mode todo


		//Admin login todo
	}
}


/* Keyboard task*/
int key;
void KBD_SetKeyFunc(){
	while(1){
		if((key = KBD_read_nonBlocking()) != INVALID_KEY){
			xQueueSend(KBD_queue, &key,100);
			DEBUGF("key inserted in Queue: %u\n",key);
		}
		vTaskDelay(100);
	}
}

/* LCD task*/

void LCD_DisplayFunc(){

	while(1){

	//todo


	}
}
