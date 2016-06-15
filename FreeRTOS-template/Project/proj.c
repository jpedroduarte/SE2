/*
 * main.c
 *
 *  Created on: 07/06/2016
 *      Author: Red
 */

#include "Environment_Tasks.h"


int pmain(){

	//
	//Init
	//
	I2C_config(1, 100);
	KBD_init(layout);
	LED_init(2, 12, 0);
	//TMR0_Init(1000);
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

	//uint32_t ptr[4]={10,11,12,13};

	//FLASH_EraseSectors(13,13);
	//FLASH_WriteBlock(sectorRegister, &ptr ,4*1024);

	LCD_TurnOffDisplay();

	if(verifyBootLoad())
		resetBootLoad();
	//
	//Create tasks
	//

	xTaskCreate(mainTaskFunc, "mainTask", configMINIMAL_STACK_SIZE, NULL, 0 , mainTask );
	xTaskCreate(UserModeTaskFunc, "UserModeTask", configMINIMAL_STACK_SIZE, NULL, 0 , UserModeTask );
	xTaskCreate(AdminModeTaskFunc, "AdminModeTask", configMINIMAL_STACK_SIZE, NULL, 0 , AdminModeTask );

	xTaskCreate(KBD_SetKeyFunc, "KBD_Task", configMINIMAL_STACK_SIZE, NULL, 0 , KBD_SetKey );
#define KBD_queue_size 4
	KBD_queue= xQueueCreate(KBD_queue_size,sizeof(uint32_t)*KBD_queue_size);
/*
#define LCD_queue_size 16
	xTaskCreate(LCD_DisplayFunc, "LCD_Task", configMINIMAL_STACK_SIZE, NULL, 0 , LCD_Display );
	LCD_queue= xQueueCreate(LCD_queue_size,sizeof(char)*LCD_queue_size);
*/
	vTaskStartScheduler();

	return 0;
}


