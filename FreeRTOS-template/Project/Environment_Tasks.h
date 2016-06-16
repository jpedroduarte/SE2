/*
 * Environment_Tasks.h
 *
 *  Created on: 07/06/2016
 *      Author: Red
 */

#ifndef PROJECT_ENVIRONMENT_TASKS_H_
#define PROJECT_ENVIRONMENT_TASKS_H_

#include "Utils.h"

/* Kernel includes. */
#include "../FreeRTOS_Library/include/FreeRTOS.h"
#include "../FreeRTOS_Library/include/queue.h"
#include "../FreeRTOS_Library/include/task.h"
#include "../FreeRTOS_Library/include/timers.h"

#define DEBUGF(x,y) printf(x,y);

/* Tasks */
xTaskHandle mainTask;
xTaskHandle AdminModeTask;
xTaskHandle UserModeTask;

xTaskHandle KBD_SetKey;
xTaskHandle LCD_Display;
xTaskHandle LED_OpenDoor;


/* Queues */
xQueueHandle KBD_queue;
xQueueHandle LCD_queue;


/* Timers */

xTimerHandle Timer_waitDoubleKey;

/* Primary Tasks */

void mainTaskFunc();

void UserModeTaskFunc();

void AdminModeTaskFunc();


/* Keyboard task*/

void KBD_SetKeyFunc();

/* LCD task*/

void LCD_DisplayFunc();

/* LED task */
void LED_OpenDoor();


#endif /* PROJECT_ENVIRONMENT_TASKS_H_ */
