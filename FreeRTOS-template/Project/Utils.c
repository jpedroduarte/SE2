/*
 * Utils.c
 *
 *  Created on: 08/06/2016
 *      Author: Red
 */


#include "Utils.h"

/* Program variables*/

//const int timeToPutCode = 25000;
int ledOn = 5000;
int timeAux = 0;
int ledTicks = 0;
int ledTime = 0;
uint8_t lcdDataTimeOn = 0;
int lastTickTime = 0;
int lastTickTimeFor5s =0;

int lastTickTimeFor25s =0;
int time25s = 0;
int time5sAux = 0;
const uint8_t time_len=6, date_len=11;
/*todo
void * sectorSettings =(void *) (8192 * 12); // pq uso o sector 12
void * sectorRegister =(void *) ( 8192 * 13); // pq uso o sector 13
*/
uint32_t layout[16]=	{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
/*todo
char flash_Settings_Buffer[512];
char flashCopy [8192];
void * flash_offset;
void * history_offset;
*/


void itod(char* dst, uint8_t dd, uint8_t mm, uint16_t yyyy){//done
	//uint16_t dd= buffer[0];
	//uint16_t mm= buffer[1];
	//uint16_t yyyy= buffer[2];

	dst[1]= '0'+dd%10;
	dst[0]= dd> 9? '0'+ dd/10 : '0';
	dst[2]='/';
	dst[4]= '0'+mm%10;
	dst[3]= mm>9? '0'+ mm/10 : '0';
	dst[5]= '/';
	dst[9]= yyyy%10 + '0'; yyyy/=10;
	dst[8]= yyyy%10 + '0'; yyyy/=10;
	dst[7]= yyyy%10 + '0'; yyyy/=10;
	dst[6]= yyyy%10 + '0';
	dst[10]=0;
}

void itot(char* dst, uint8_t hh, uint8_t mm){//done
	dst[1]= '0'+hh%10;
	dst[0]= hh>9? '0' + hh/10 : '0';
	dst[2]= ':';
	dst[4]= '0'+mm%10;
	dst[3]= mm>9? '0'+mm/10 : '0';
	dst[5]=0;
}

void turnOnLcdAndWriteTime(int count){//done
    LCD_TurnOnDisplay();
    LCD_BL_State(1);
    RTC_GetValue(&dateTime);
    char time[time_len], date[date_len];
    itot(time, dateTime.tm_hour, dateTime.tm_min);
	itod(date, dateTime.tm_mday, dateTime.tm_mon, dateTime.tm_year);
    LCD_Goto(3,1); LCD_WriteString(date);
    LCD_Goto(5,2); LCD_WriteString(time);
	LCD_Goto(5+count,3);
	//LCD_WriteChar('*');
}
