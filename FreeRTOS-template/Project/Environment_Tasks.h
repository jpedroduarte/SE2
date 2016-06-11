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

#define DEBUGF(x,y) printf(x,y);

xTaskHandle mainTask;
xTaskHandle AdminModeTask;
xTaskHandle UserModeTask;

xTaskHandle KBD_SetKey;
xTaskHandle LCD_Display;

xQueueHandle KBD_queue;
xQueueHandle LCD_queue;


/* Primary Tasks */

void mainTaskFunc();

void UserModeTaskFunc();

void AdminModeTaskFunc();


/* Keyboard task*/

void KBD_SetKeyFunc();

/* LCD task*/

void LCD_DisplayFunc();


#endif /* PROJECT_ENVIRONMENT_TASKS_H_ */
