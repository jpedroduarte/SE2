/*
 * main.c
 *
 *  Created on: 07/06/2016
 *      Author: Red
 */

#include "Environment_Tasks.h"


int main(){

	//
	//Init
	//
	printf("Start");
	I2C_config(1, 100);
	KBD_init(layout);
	LED_init(2, 12, 0);
	SPI_Init(8,9);
	LCD_Init();
	//char time[time_len], date[date_len];
	//itot(time, 13, 50);
	//itod(date, 17, 1, 2016);
	int secs = 00, mins = 0, hours = 0, wdays = 1,
			days = 1, mons = 01, years = 2016, yday = 01;
	dateTime.tm_sec 	= secs;
	dateTime.tm_min 	= mins;
	dateTime.tm_hour 	= hours;
	dateTime.tm_wday 	= wdays;
	dateTime.tm_mday 	= days;
	dateTime.tm_mon 	= mons;
	dateTime.tm_year 	= years;
	dateTime.tm_yday 	= yday;
	RTC_Init(&dateTime);
	LCD_BL_State(0); //Apagar LCD light

	LCD_TurnOffDisplay();
	//todo
	resetBootLoad();
	//printf("Reset EEPROM!");
	//resetBootLoad();
	if(!verifyBootLoad()){
		resetBootLoad();
		printf("Reset EEPROM!");
	}
	//VerifyAdminCode(0);
	//
	//Create tasks
	//

	xTaskCreate(mainTaskFunc, "mainTask", configMINIMAL_STACK_SIZE, NULL, 0 , &mainTask );
	xTaskCreate(UserModeTaskFunc, "UserModeTask", configMINIMAL_STACK_SIZE*2, NULL, 0 , &UserModeTask );
	xTaskCreate(AdminModeTaskFunc, "AdminModeTask", configMINIMAL_STACK_SIZE*2, NULL, 0 , &AdminModeTask );

	/* Utility tasks */
	xTaskCreate(LED_OpenDoorFunc,"Led_OpenDoorTask",configMINIMAL_STACK_SIZE, NULL, 2 , &LED_OpenDoor);
	xTaskCreate(KBD_SetKeyFunc, "KBD_Task", configMINIMAL_STACK_SIZE, NULL, 2 , &KBD_SetKey );
#define KBD_queue_size 4
	KBD_queue= xQueueCreate(KBD_queue_size,sizeof(uint32_t)*KBD_queue_size);
/*
#define LCD_queue_size 16
	xTaskCreate(LCD_DisplayFunc, "LCD_Task", configMINIMAL_STACK_SIZE, NULL, 2 , LCD_Display );
	LCD_queue= xQueueCreate(LCD_queue_size,sizeof(char)*LCD_queue_size);
*/

	/* Create Timers */
	/*
	Timer_waitDoubleKey= xTimerCreate(
		 "Timer",
		 200,
		 pdTRUE,
		 ( void * ) 0,
		 TimerCallback
	 );

	if(Timer_waitDoubleKey == NULL)
	{
		puts("Failed to create FREERTOS Timer");
		return 0;
	}
	*/
	puts("Init completed.");
	/* Start Scheduler */
	vTaskStartScheduler();

	return 0;
}


