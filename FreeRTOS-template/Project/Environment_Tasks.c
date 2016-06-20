/*
 * Environment_Tasks.c
 *
 *  Created on: 07/06/2016
 *      Author: Red
 */

#include "Environment_Tasks.h"

/* Notas
	todo-usar software timer para controlar o estado do LCD (ligado/desligado)
*/

/* Main Task*/

void mainTaskFunc(){
	int key;
	int keyAux;
	while(1){
		//Get a key
		puts("Main Task- GetKey\n");
		if(xQueueReceive(KBD_queue, &key, portMAX_DELAY) == pdTRUE){
			printf("Main Task key: %X\n",key);
			if(key== DOUBLE_KEY){
				/* Double Key */
				printf("-DOUBLE_KEY-\n");
				xTaskNotifyGive(AdminModeTask);
			}else{
				/* Normal key */
				puts("-NORMAL_KEY-");
				xTaskNotifyGive(UserModeTask);
			}
		}
		//block main task until notified
		puts("Block Main Task\n");
		ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		puts("main Task is back");
	}
}

uint32_t keyNum, keyCode=0;
int aux;
uint8_t leave_function=0;
void UserModeTaskFunc(){

	while(1){
		//block Thread until there is a notification
		puts("------Block User Mode.\n");
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		puts("------User Mode. \n");

		puts("\nUser Mode Task key:");
		for(keyNum=0; keyNum<4;++keyNum){
			//Get a key
			if(xQueueReceive(KBD_queue, &aux, 5000) == pdFALSE){
				//timeout occured
				puts("User Mode Key Timeout");
				leave_function=1;
				LCD_Clear(WHITE);
				LCD_BL_State(0);
				LCD_TurnOffDisplay();
				break;
			}else{
				/* Get valid key */
				printf("count:%u | %X \n",keyNum,aux);
				keyCode |= aux<<(keyNum*8);
				turnOnLcdAndWriteTime(keyNum);
			}
		}

		if(leave_function){
			xTaskNotifyGive(mainTask);
			continue;
		}


		printf("Key Code: %X\n",keyCode);
		uint8_t validate= VerifyCode(keyCode);
		if(validate){
			/*Wake up OpenDoor Task */
			puts("Entry valid!\n");
			xTaskNotifyGive(LED_OpenDoor);

		}else{
			puts("Entry Invalid! \n");
			LCD_BL_State(0);
			LCD_Clear(0xFFF);
			LCD_TurnOffDisplay();
		}
		saveEntry(validate);

		/*
		LCD_BL_State(0);
		LCD_Clear(0xFFF);
		LCD_TurnOffDisplay();
		 */

		puts("WakeUp MainTask.\n");
		/* Wake up Main Task */
		xTaskNotifyGive(mainTask);

	}
}

void AdminModeTaskFunc(){

	while(1){
//todo
		//block Thread until there is a notification
		puts("Block Admin Mode. \n");
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		puts("---------Admin Mode\n");

		//Authentication LCD mode todo


		//Admin login todo

		/* Wake up Main Task */
		xTaskNotifyGive(mainTask);
	}
}


/* Keyboard Set task*/
void KBD_SetKeyFunc(){
	int key;
	uint32_t count;
	while(1){
		if((key = KBD_read_nonBlocking()) != INVALID_KEY){

		}
		//puts("\ncount:");
		for(count=0; count<10; ++count){
			if((key = KBD_read_nonBlocking()) != INVALID_KEY){
				if(key == DOUBLE_KEY){
					//printf("%u ",count);
					vTaskDelay(200);
					continue;
				}else{
					/* Normal Key */
					xQueueSend(KBD_queue, &key,300);
					break;
				}

			}else{
				//puts("KBD Task- No key\n");
				break;
			}
			//puts("\n");

		}

		if(key == DOUBLE_KEY){
			/* Double Key */
			xQueueSend(KBD_queue, &key,300);
			printf("DOUBLE_KEY! -- %u ",key);
		}
		vTaskDelay(200);
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
		puts("DOOR OPEN\n");
		LED_SetState(1);
		vTaskDelay(5000);
		LED_SetState(0);
		LCD_BL_State(0);
		LCD_Clear(0xFFF);
		LCD_TurnOffDisplay();
		puts("DOOR CLOSED\n");
	}
}
