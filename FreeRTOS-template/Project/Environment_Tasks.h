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
#include "../../FreeRTOS_Library/include/FreeRTOS.h"
#include "../../FreeRTOS_Library/include/queue.h"
#include "../../FreeRTOS_Library/include/task.h"
#include "../../FreeRTOS_Library/include/timers.h"

#define DEBUGF(x,y) printf(x,y);

/* Tasks */

TaskHandle_t mainTask;
TaskHandle_t AdminModeTask;
TaskHandle_t UserModeTask;

TaskHandle_t KBD_SetKey;
TaskHandle_t LCD_Display;
TaskHandle_t LED_OpenDoor;


/* Queues */
QueueHandle_t  KBD_queue;
QueueHandle_t  LCD_queue;


/* Timers */

TimerHandle_t  Timer_waitDoubleKey;

/* Primary Tasks */

void mainTaskFunc();

void UserModeTaskFunc();

void AdminModeTaskFunc();


/* Keyboard task*/

void KBD_SetKeyFunc();

/* LCD task*/

void LCD_DisplayFunc();

/* LED task */
void LED_OpenDoorFunc();


#endif /* PROJECT_ENVIRONMENT_TASKS_H_ */
