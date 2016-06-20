/*
 * main.c
 *
 *  Created on: 07/06/2016
 *      Author: Red
 */

#include "Environment_Tasks.h"

/* Software Timer Functions */

void TimerCallback(xTimerHandle xTimer){
	const uint32_t ulMaxExpiryCountBeforeStopping = 10;
	uint32_t ulCount;

	/* The number of times this timer has expired is saved as the
	timer's ID.  Obtain the count. */
	ulCount = ( uint32_t ) pvTimerGetTimerID( xTimer );

	/* Increment the count, then test to see if the timer has expired
	ulMaxExpiryCountBeforeStopping yet. */
	ulCount++;
	int key;
	if(xQueueReceive(KBD_queue, &key, portMAX_DELAY) == pdFALSE){
		puts("Could not aquire KBD_queue");
		xTimerStop( Timer_waitDoubleKey, 0 );
	}
	printf("Main Task key: %X | Timer: %u\n",key,ulCount);
	if(ulCount > 1 && key!= DOUBLE_KEY){
		/* Normal key */
		//printf("Main Task key: %X\n",key);
		xTaskNotifyGive(UserModeTask);
		xTimerStop( Timer_waitDoubleKey, 0 );
	}

	/* If the timer has expired 10 times then stop it from running. */
	if( ulCount >= ulMaxExpiryCountBeforeStopping )
	{
		/* Do not use a block time if calling a timer API function
		from a timer callback function, as doing so could cause a
		deadlock! */
		xTaskNotifyGive(AdminModeTask);
		xTimerStop( Timer_waitDoubleKey, 0 );

	}
	else
	{
	   /* Store the incremented count back into the timer's ID field
	   so it can be read back again the next time this software timer
	   expires. */
	   vTimerSetTimerID( xTimer, ( void * ) ulCount );
	}
}


int main(){

	//
	//Init
	//
	I2C_config(1, 100);
	KBD_init(layout);
	LED_init(2, 12, 0);
	//TMR0_Init(1000);
	SPI_Init(128,9);
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

	if(!verifyBootLoad()){
		resetBootLoad();
	}

	//
	//Create tasks
	//

	xTaskCreate(mainTaskFunc, "mainTask", configMINIMAL_STACK_SIZE, NULL, 0 , &mainTask );
	xTaskCreate(UserModeTaskFunc, "UserModeTask", configMINIMAL_STACK_SIZE, NULL, 1 , &UserModeTask );
	xTaskCreate(AdminModeTaskFunc, "AdminModeTask", configMINIMAL_STACK_SIZE, NULL, 1 , &AdminModeTask );

	/* Utility tasks */
	xTaskCreate(LED_OpenDoorFunc,"Led_OpenDoorTask",configMINIMAL_STACK_SIZE, NULL, 0 , &LED_OpenDoor);
	xTaskCreate(KBD_SetKeyFunc, "KBD_Task", configMINIMAL_STACK_SIZE, NULL, 0 , &KBD_SetKey );
#define KBD_queue_size 4
	KBD_queue= xQueueCreate(KBD_queue_size,sizeof(uint32_t)*KBD_queue_size);
/*
#define LCD_queue_size 16
	xTaskCreate(LCD_DisplayFunc, "LCD_Task", configMINIMAL_STACK_SIZE, NULL, 0 , LCD_Display );
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


