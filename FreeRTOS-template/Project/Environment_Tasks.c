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

/*-------------------------------------------------------------------------------*/

/* Main Task*/
int firstKey;
uint8_t mainTaskExit;
void mainTaskFunc(){
	int key;
	int keyAux;

	while(1){
		//Get a key
		puts("Main Task- GetKey\n");
		LCD_Off();
		for(mainTaskExit=0; xQueueReceive(KBD_queue, &key, portMAX_DELAY) == pdTRUE; ++mainTaskExit){
			if(key == DOUBLE_KEY){
				if(mainTaskExit>=5){
					/* Double Key */
					printf("-DOUBLE_KEY- exitCounter: %u\n",mainTaskExit);
					xTaskNotifyGive(AdminModeTask);
					break;
				}
				vTaskDelay(400);
				continue;
			}else{
				if(mainTaskExit>0){
					/* Normal key */
					puts("-NORMAL_KEY-");
					xTaskNotifyGive(UserModeTask);
					break;
				}
			}
		}

		/* Save the first key pressed */
		firstKey=key;

		//block main task until notified
		puts("Block Main Task\n");
		int aux= ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		printf("main Task is back : 0x%X\n", aux);
		//VerifyAdminCode(0);
	}
}

/*-------------------------------------------------------------------------------*/

uint32_t keyNum, keyCode;
int aux;
uint8_t leave_function;
void UserModeTaskFunc(){

	while(1){
		//block Thread until there is a notification
		puts("------Block User Mode.\n");
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		puts("------User Mode. \n");
		//VerifyAdminCode(0);
		turnOnLcdAndWriteTime();
		keyCode=0;
		leave_function=0;
		puts("\nUser Mode Task key:");
		keyNum=0;
		/* Get the key from Main Task */
		keyCode |= firstKey<<(keyNum*8);
		++keyNum;
		LCD_WriteChar('*');

		for(;keyNum<4;++keyNum){
			//Get a key
			if(xQueueReceive(KBD_queue, &aux, 5000) == pdFALSE){
				//timeout occured
				puts("User Mode Key Timeout");
				leave_function=1;
				break;
			}else{
				/* Get valid key */
				printf("count:%u | %X \n",keyNum,aux);
				keyCode |= aux<<(keyNum*8);
				LCD_WriteChar('*');
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
			LCD_Goto(2,5); LCD_WriteString("INVALID CODE!");
			vTaskDelay(2000);
			puts("Entry Invalid! \n");
		}
		VerifyAdminCode(0);
		saveEntry(validate);

		puts("WakeUp MainTask.\n");
		/* Try Wake up Main Task */
		xTaskNotifyGive(mainTask);
	}
}

/*-------------------------------------------------------------------------------*/

void AdminModeTaskFunc(){

	while(1){
		//block Thread until there is a notification
		puts("Block Admin Mode. \n");
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		puts("---------Admin Mode\n");
		//VerifyAdminCode(0);
		turnOnLcdAndWriteTimeAdmin();
		/* Polling for a key which is not DOUBLE_KEY */
		while(1){
			if(xQueueReceive(KBD_queue, &aux, 500) == pdFALSE)
				break;
			else if(aux!=DOUBLE_KEY){
				break;
			}
		}
		/* Reset Queue because it is full with DOUBLE_KEY */
		xQueueReset(KBD_queue);

		keyCode=0;
		leave_function=0;
		for(keyNum=0; keyNum<4;++keyNum){
			//Get a key
			if(xQueueReceive(KBD_queue, &aux, 5000) == pdFALSE){
				//timeout occured
				puts("Admin Mode Key Timeout");
				leave_function=1;
				break;
			}else{
				/* Get valid key */
				printf("count:%u | %X \n",keyNum,aux);
				keyCode |= aux<<(keyNum*8);
				LCD_WriteChar('*');
			}
		}

		if(leave_function){
			xTaskNotifyGive(mainTask);
			continue;
		}

		printf("Key Code: %X\n",keyCode);
		uint8_t validate= VerifyAdminCode(keyCode);
		if(!validate){
			LCD_Goto(2,6); LCD_WriteString("INVALID CODE!");
			vTaskDelay(2000);
			puts("Entry Invalid! \n");
		}else{
			/* Enter Admin Mode */
			puts("Entry valid!\n");
			printLCDMaintenanceMenu();
			/* Stay in Maintenance Mode until # is pressed */
			while(1){
				if(gotoAdminOption()) //Returns 1 in case of exit key
					break;
				printLCDMaintenanceMenu();
			}
		}
		puts("WakeUp MainTask.\n");
		/* Try Wake up Main Task */
		xTaskNotifyGive(mainTask);
	}
}

/*-------------------------------------------------------------------------------*/

/* Keyboard Set task*/

int key;
void KBD_SetKeyFunc(){

	while(1){

		if((key = KBD_read_nonBlocking()) != INVALID_KEY){
			xQueueSend(KBD_queue, &key,200);

		}
		//printf("*");
		vTaskDelay(200);
	}
}

/*-------------------------------------------------------------------------------*/

/* LCD task*/

void LCD_DisplayFunc(){

	while(1){

	//todo


	}
}

/*-------------------------------------------------------------------------------*/

/* LED task */

void LED_OpenDoorFunc(){
	while(1){
		//block task until it is notified
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		puts("DOOR OPEN\n");
		LCD_Goto(3,5); LCD_WriteString("DOOR OPEN!");
		LED_SetState(1);
		vTaskDelay(5000);
		puts("DOOR CLOSED\n");
		LED_SetState(0);
	}
}
