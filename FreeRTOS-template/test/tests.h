/** @file tests.h
 *  @brief Module with all sorts of tests.
 *
 *  @author João Duarte
 *
 */

#ifndef TEST_TESTS_H_
#define TEST_TESTS_H_

#include "../../FreeRTOS_Library/include/FreeRTOS.h"
#include "../../FreeRTOS_Library/include/task.h"



#include <stdio.h>
#include "LPC17xx.h"
#include "../Modules/GPIO.h"
#include "../Modules/KBD.h"
#include "../Modules/LCD.h"
#include "../Modules/SPI.h"
#include "../Modules/EEPROM.h"
#include "../Modules/RTC.h"
#include "../Modules/LED.h"

/* Professor static library uIP */
#include "../Modules/tapdev.h"

#include "queue.h"
#include "semphr.h"

QueueHandle_t queue;

typedef struct{
  unsigned int  adminCode;
  unsigned int  doorCOde;
  unsigned int  nRegist;
  unsigned int  absRegist;
  unsigned int  checkBootLoad;	//Reserved
  unsigned int  hr;
  unsigned int  mm;
  unsigned int  s;
  unsigned int  year;
  unsigned int  month;
  unsigned int  day;
  unsigned int  dayWeek;
} Settings1;

void GetDatetimeTask();
void RTCTest();

void varExampleTask(void * pvParameters);
void varExampleTaskTest();

void ledTest();

void setKey1(void);
void setKey(void);
void getKey1(void);
void getKey(void);
void kbdTest();

void lcdTest();

void kbdLCDTest();

void eepromTest();

void projTest();

void auxEEPROMTest();

void getBootLoadCode();

void getKeyCode();

void getSettings();

void cleanEEPROM();

#endif /* TEST_TESTS_H_ */
