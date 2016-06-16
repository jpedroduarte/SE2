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
				xTimerStart(Timer_waitDoubleKey,200);
			}else{
				xTaskNotifyGive(UserModeTask);
			}
			//block main task until notified
			ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		}
	}
}

void UserModeTaskFunc(){

	uint8_t leave_function=0;
	while(1){
		//block Thread until there is a notification
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		puts("User Mode");

		//LCD Autentication State todo
		uint32_t keyCode=0, aux;
		//uint8_t keyCode[4];
		uint8_t count;
		for(count=0; count<4;++count){
			//Get a key
			if(xQueueReceive(KBD_queue, &aux, 5000) == pdFALSE){
				//timeout occured
				leave_function=1;
				LCD_Clear(WHITE);
				LCD_BL_State(0);
				LCD_TurnOffDisplay();
				break;
			}else{
				keyCode |= aux<<(count*8);
				turnOnLcdAndWriteTime(count);
			}
		}

		if(leave_function){
			xTaskNotifyGive(mainTask);
			continue;
		}


		//todo validate key
		uint8_t validate= VerifyCode(keyCode);

		saveEntry(validate);

		LCD_BL_State(0);
		LCD_Clear(0xFFF);
		LCD_TurnOffDisplay();

		xTaskNotifyGive(mainTask);
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
void KBD_SetKeyFunc(){
	int key;
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

/* LED task */

void LED_OpenDoorFunc(){
	while(1){
		//block task until it is notified
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		LED_SetState(1);
		vTaskDelay(5000);
		LED_SetState(0);
	}
}
