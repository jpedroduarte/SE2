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

void * sectorSettings =(void *) 0;
void * sectorRegister =(void *) sizeof(Settings)+1;
/*
void addressBuffer[2]={0,0};
uint32_t SettingsBufferSize= sizeof(Settings);
void SettingsDataBuffer[SettingsBufferSize];
*/
uint32_t layout[16]=	{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};


/*
 * todo
char flash_Settings_Buffer[512];
char flashCopy [8192];
void * flash_offset;
void * history_offset;
*/


void itod(char* dst, uint8_t dd, uint8_t mm, uint16_t yyyy){//done
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

uint8_t verifyBootLoad(){
	uint16_t BootLoadAddress= getFormatedAddress(16);
	uint32_t buffer=0;
	EEPROM_Read(&BootLoadAddress,&buffer, 4);
	printf("code? = 0x%X\n",buffer);
	if(buffer != BootLoadCode)
		return 0;
	return 1;
}

void merge(void* dst, void* src1, uint32_t size1, void* src2, uint32_t size2){
	memcpy(dst,src1,size1);
	memcpy(dst+size1,src2,size2);
}

void resetBootLoad(){
	uint16_t addr= getFormatedAddress(0x0);
	Settings s;
	s.adminCode 	= 0x0000;
	s.doorCOde 		= 0x1010101;// codigo 1 1 1 1
	s.nRegist 		= 0;
	s.absRegist		= 0;
	s.checkBootLoad	= 0x69F02ADB;
	s.hr 			= 0;
	s.mm 			= 0;
	s.s 			= 0;
	s.year 			= 0;
	s.month 		= 0;
	s.day 			= 0;
	s.dayWeek 		= 0;

	EEPROM_Write(&addr, &s,sizeof(Settings));
}

uint16_t getFormatedAddress(uint16_t src){
	uint16_t aux= src >>8;
	uint16_t aux1= (src & 0x00FF)<<8;
	return aux1+aux;
}

uint8_t VerifyCode(uint32_t code){
	uint16_t BootLoadAddress= getFormatedAddress(2*sizeof(int)-sizeof(int));
	uint32_t buffer;
	EEPROM_Read(&BootLoadAddress, &buffer, sizeof(int));
	if(buffer != code)
		return 0;
	return 1;
}

uint32_t getKeyFromArray(uint8_t src[4]){
	uint32_t key,count;//= keyCode[0]
	for(count=0; count<4;++count){
		key+=src[count]<<(8*count);
	}
	return key;
}

uint8_t waitKey(uint32_t key, uint32_t timeout){
	//todo
}





/* End of file */
