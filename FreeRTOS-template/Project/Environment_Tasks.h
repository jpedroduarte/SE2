/**
* @file		Environment_Tasks.h
* @brief	Module with all Task implementations
* @author	João Duarte
*/
#ifndef PROJECT_ENVIRONMENT_TASKS_H_
#define PROJECT_ENVIRONMENT_TASKS_H_

/** @defgroup Environment_Tasks Environment_Tasks
 * @ingroup Environment_Tasks
 * This module provides Task implementation for the app.
 * @{

 * @defgroup Environment_Tasks_Public_Functions Environment_Tasks Public Functions
 * @{
 */

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

//TimerHandle_t  Timer_waitDoubleKey;

/* Primary Tasks */

/**
 * @brief	Task that waits for a key and then chooses wether to go to Admin mode or User mode.
 * @return	void
 */
void mainTaskFunc();

/**
 * @brief	Task that does the user login and saves that entry in EEPROM.
 * @return	void
 */
void UserModeTaskFunc();

/**
 * @brief	Task that does the admin login and allows various admin related previleges.
 * @return	void
 */
void AdminModeTaskFunc();


/**
 * @brief	Task that constantly is geting a key from the keyboard.
 * @return	void
 */
void KBD_SetKeyFunc();


void LCD_DisplayFunc();

/**
 * @brief	Task that opens the door in case the user login is sucessfull.
 * @return	void
 */
void LED_OpenDoorFunc();

/**
 * @}
  */

/**
 * @}
 */

#endif /* PROJECT_ENVIRONMENT_TASKS_H_ */
