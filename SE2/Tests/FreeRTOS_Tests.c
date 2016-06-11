/*
 * FreeRTOS_Tests.c
 *
 *  Created on: 21/04/2016
 *      Author: Red
 */


#include "FreeRTOS.h"
#include "GPIO.h"
#include "task.h"

/* Task to be created. */
void blinkLed(void * pvParameters)
{
	GPIO_config_bitGeneric(2,0,0x1000,0x1000,0);
	while(1){
		GPIO_SetGeneric(2,0x1000);
		vTaskDelay(500);
		GPIO_ClearGeneric(2,0x1000);
		vTaskDelay(500);
	}
	vTaskDelete(NULL);
}

int FRTOStest0(void){
	xTaskCreate(blinkLed, "blinkLed", configMINIMAL_STACK_SIZE, NULL, 0 , NULL );
	vTaskStartScheduler();
	while(1);

	return 0;
}
