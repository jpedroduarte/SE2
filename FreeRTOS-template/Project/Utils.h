/*
 * Utils.h
 *
 *  Created on: 08/06/2016
 *      Author: Red
 */

#ifndef PROJECT_UTILS_H_
#define PROJECT_UTILS_H_

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../Modules/LCD.h"
#include "../Modules/RTC.h"
#include "../Modules/KBD.h"
#include "../Modules/LED.h"
#include "../Modules/I2C.h"
#include "../Modules/EEPROM.h"

/* Macros */

#define BootLoadCode 0x69F02ADB



/* Data Structures */

uint32_t layout[16];

struct tm dateTime;

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
} Settings;

typedef struct{
  uint8_t hr;
  uint8_t mm;
  uint8_t s;
  uint8_t month;
  uint16_t year;
  uint8_t day;
  uint8_t dayWeek;
  uint8_t validation;
} Regist;	//9 Bytes



/* Functions */

void merge(void* dst, void* src1, uint32_t size1, void* src2, uint32_t size2);

void itod(char* dst, uint8_t dd, uint8_t mm, uint16_t yyyy);

void itot(char* dst, uint8_t hh, uint8_t mm);

void turnOnLcdAndWriteTime(int count);

uint8_t verifyFlash();

void resetFlash();

uint8_t VerifyCode(int code);

#endif /* PROJECT_UTILS_H_ */
