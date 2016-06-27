/**
* @file		Utils.h
* @brief	Module with all Utilitary functions for the app.
* @author	João Duarte
*/

#ifndef PROJECT_UTILS_H_
#define PROJECT_UTILS_H_

/** @defgroup Utils Utils
 * @ingroup Utils
 * This module provides utility functions for the app.
 * @{

 * @defgroup Utils_Public_Functions Utils Public Functions
 * @{
 */

#include <stdio.h>
#include <time.h>
#include "../Modules/LCD.h"
#include "../Modules/RTC.h"
#include "../Modules/KBD.h"
#include "../Modules/LED.h"
#include "../Modules/I2C.h"
#include "../Modules/EEPROM.h"

/* Macros */

#define BootLoadCode 0x69F02ADB
#define ADMINCODE_ADDR 0
#define DOORCODE_ADDR 4
#define NREGIST_ADDR 8
#define ABSREGIST_ADDR 12
#define CHECK_BOOT_LOAD_ADDR 16
#define entryAddr(x) sizeof(Settings)+x*sizeof(Regist)

#define time_len 6
#define date_len 11
#define entry_string_len 5

#define ASTERISK 10
#define CARDINAL 11

#define MAX_ENTRY_VALUE 3000

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
  uint8_t bla;
} Regist;	//10 Bytes



/* Functions */


/**
 * @brief	Prepares the uint16_t bitwise for an EEPROM operation, switching the HIGH with the LOW byte.
 * @return	uint16_t
 */
uint16_t getFormatedAddress(uint16_t src);

/**
 * @brief	int to string
 * @param	char* dst - destination string
 * @param	uint32_t n - number to convert into string
 * @return	void
 */
void itos(char* dst, uint32_t n);


/**
 * @brief	int to date string
 * @param	char* dst - destination string
 * @param	uint8_t dd - day
 * @param 	uint8_t mm - month
 * @param	uint8_t yyyy - year
 * @return	void
 */
void itod(char* dst, uint8_t dd, uint8_t mm, uint16_t yyyy);


/**
 * @brief	int to time string
 * @param	char* dst - destination string
 * @param	uint8_t hh - hour
 * @param 	uint8_t mm - minutes
 * @return	void
 */
void itot(char* dst, uint8_t hh, uint8_t mm);

/**
 * @brief	Turns on Display and writes the current time.
 * @return	void
 */
void turnOnLcdAndWriteTime();

/**
 * @brief	Turns on Display and writes the current time for Admin mode.
 * @return	void
 */
void turnOnLcdAndWriteTimeAdmin();

/**
 * @brief	Displays Admin mode operations.
 * @return	void
 */
void printLCDMaintenanceMenu();

/**
 * @brief	Checks if BootLoad code in EEPROM is valid.
 * @return	uint8_t - 0 if invalid.
 */
uint8_t verifyBootLoad();

/**
 * @brief	Resets the Settings struct in EEPROM.
 * @return	void
 */
void resetBootLoad();

/**
 * @brief	Verifies if the door code is valid in accordance to the Settings struct in EEPROM.
 * @param	uint32_t code - code to compare.
 * @return	uint8_t 0 if invalid.
 */
uint8_t VerifyCode(uint32_t code);

/**
 * @brief	Verifies if the admin code is valid in accordance to the Settings struct in EEPROM.
 * @param	uint32_t code - code to compare.
 * @return	uint8_t 0 if invalid.
 */
uint8_t VerifyAdminCode(uint32_t code);

/**
 * @brief	Returns a key value code form an array of keys.
 * @return	uint32_t - key code.
 */
uint32_t getKeyFromArray(uint8_t src[4]);

/**
 * @brief	Saves an entry (Regist struct) in EEPROM.
 * @param	uint8_t validate - 0 if not valid.
 * @return	void
 */
void saveEntry(uint8_t validated);

/**
 * @brief	Turns off Display and shuts down backlight.
 * @return	void
 */
void LCD_Off();

/**
 * @brief	Auxiliar function for admin mode control.
 * @return	uint8_t
 */
uint8_t gotoAdminOption();

/**
 * @brief	Changes the door code in Settings struct in EEPROM.
 * @return	uint8_t 0 to leave admin mode.
 */
uint8_t changeDoorCOde();

/**
 * @brief	Changes the admin code in Settings struct in EEPROM.
 * @return	uint8_t 0 to leave admin mode.
 */
uint8_t changeAdminCOde();

/**
 * @brief	Changes the clock in Settings struct in EEPROM.
 * @return	uint8_t 0 to leave admin mode.
 */
uint8_t setClock();

/**
 * @brief	Changes the calendar in Settings struct in EEPROM.
 * @return	uint8_t 0 to leave admin mode.
 */
uint8_t changeCalendar();

/**
 * @brief	Displays all the entries from users in a ring buffer style.
 * @return	uint8_t 0 to leave admin mode.
 */
uint8_t printHistoric();

/**
 * @brief	Gets the admin code from Settings struct in EEPROM.
 * @return	uint8_t admin code read from EEPROM.
 */
uint32_t getAdminCode();


void BringTheHammer(uint32_t pw);

/* Data Structures */

uint32_t layout[16];

struct tm dateTime;

Settings s;

Regist r;

/**
 * @}
  */

/**
 * @}
 */

#endif /* PROJECT_UTILS_H_ */
