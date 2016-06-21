/*
 * Utils.c
 *
 *  Created on: 08/06/2016
 *      Author: Red
 */


#include "Utils.h"
#include "Environment_Tasks.h"

/* Program variables*/

uint32_t layout[16]=	{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
uint8_t lcdDataTimeOn = 0;


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

/*-------------------------------------------------------------------------------*/

void itot(char* dst, uint8_t hh, uint8_t mm){//done
	dst[1]= '0'+hh%10;
	dst[0]= hh>9? '0' + hh/10 : '0';
	dst[2]= ':';
	dst[4]= '0'+mm%10;
	dst[3]= mm>9? '0'+mm/10 : '0';
	dst[5]=0;
}

/*-------------------------------------------------------------------------------*/

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
	LCD_WriteChar('*');
}

/*-------------------------------------------------------------------------------*/

void turnOnLcdAndWriteTimeAdmin(int count){//done
    LCD_TurnOnDisplay();
    LCD_BL_State(1);
    RTC_GetValue(&dateTime);
    char time[time_len], date[date_len];
    itot(time, dateTime.tm_hour, dateTime.tm_min);
	itod(date, dateTime.tm_mday, dateTime.tm_mon, dateTime.tm_year);
    LCD_Goto(3,1); LCD_WriteString(date);
    LCD_Goto(5,2); LCD_WriteString(time);
    LCD_Goto(4,3);LCD_WriteString("Admin code:");
	LCD_Goto(5+count,3);
	LCD_WriteChar('*');
}

/*-------------------------------------------------------------------------------*/

void printLCDMaintenanceMenu(){//done
	LCD_TurnOnDisplay();
	LCD_Goto(0,0);LCD_WriteString("1-Set doorcode");
	LCD_Goto(0,1);LCD_WriteString("2-Set admincode");
	LCD_Goto(0,2);LCD_WriteString("3-Set clock");
	LCD_Goto(0,3);LCD_WriteString("4-Set calendar");
	LCD_Goto(0,4);LCD_WriteString("5-View history");
	LCD_Goto(0,5);LCD_WriteString("A-Leave");
	LCD_BL_State(1);
}

/*-------------------------------------------------------------------------------*/

uint8_t verifyBootLoad(){
	uint16_t BootLoadAddress= getFormatedAddress(16);
	uint32_t buffer=0;
	EEPROM_Read(&BootLoadAddress,&buffer, 4);
	printf("code? = 0x%X\n",buffer);
	if(buffer != BootLoadCode)
		return 0;
	return 1;
}

/*-------------------------------------------------------------------------------*/

void resetBootLoad(){
	uint16_t addr= getFormatedAddress(0x0);
	Settings s;
	s.adminCode 	= 0x03030303;
	s.doorCOde 		= 0x01010101;// codigo 1 1 1 1
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

/*-------------------------------------------------------------------------------*/

uint16_t getFormatedAddress(uint16_t src){
	uint16_t aux= src >>8;
	uint16_t aux1= (src & 0x00FF)<<8;
	return aux1+aux;
}

/*-------------------------------------------------------------------------------*/

uint16_t BootLoadAddress;
uint32_t buffer;
uint8_t VerifyCode(uint32_t code){
	BootLoadAddress= getFormatedAddress(2*sizeof(int)-sizeof(int));
	EEPROM_Read(&BootLoadAddress, &buffer, sizeof(int));
	if(buffer != code)
		return 0;
	return 1;
}

/*-------------------------------------------------------------------------------*/

uint8_t VerifyAdminCode(uint32_t code){
	uint16_t BootLoadAddress= getFormatedAddress(1*sizeof(int)-sizeof(int));
	uint32_t buffer;
	EEPROM_Read(&BootLoadAddress, &buffer, sizeof(int));
	if(buffer != code)
		return 0;
	return 1;
}

/*-------------------------------------------------------------------------------*/

uint16_t entryAddr;
uint32_t entry;
uint32_t nRegist;
void saveEntry(uint8_t validated){

	/* Get nRegist from EEPROM */
	entryAddr= getFormatedAddress(NREGIST_ADDR);
	EEPROM_Read(&entryAddr,&entry,sizeof(uint32_t));
	if(entry >= MAX_ENTRY_VALUE){	// EEPROM memory is full
		/* Reset EEPROM entry pointer */
		entry=0;
		EEPROM_Write(&entryAddr, &entry,sizeof(uint32_t));
		/*Put AbsReg to 1 to indicate EEPROM is full of entries */
		entryAddr= getFormatedAddress(ABSREGIST_ADDR);
		entry= 0x1;
		EEPROM_Write(&entryAddr, &entry, sizeof(int));
	}

	// Get DateTime
	RTC_GetValue(&dateTime);

	Regist regist;
	regist.hr = dateTime.tm_hour;
	regist.mm = dateTime.tm_min;
	regist.s = dateTime.tm_sec;
	regist.year = dateTime.tm_year;
	regist.month = dateTime.tm_mon;
	regist.day = dateTime.tm_mday;
	regist.dayWeek = dateTime.tm_wday;
	regist.validation = validated;

	//Get Address to write entry
	uint16_t entry_addr= getFormatedAddress(nRegist*sizeof(regist)+sizeof(Settings));
	//write in EEPROM
	EEPROM_Write(&entry_addr,&regist,sizeof(Regist));
}

/*-------------------------------------------------------------------------------*/

uint32_t getKeyFromArray(uint8_t src[4]){
	uint32_t key,count;//= keyCode[0]
	for(count=0; count<4;++count){
		key+=src[count]<<(8*count);
	}
	return key;
}

/*-------------------------------------------------------------------------------*/

uint8_t waitKey(uint32_t key, uint32_t timeout){
	//todo
}

/*-------------------------------------------------------------------------------*/

void LCD_Off(){
	LCD_BL_State(0);
	LCD_Clear(0xFFF);
	LCD_TurnOffDisplay();
}

/*-------------------------------------------------------------------------------*/

uint8_t exit;
int adminOptionKey;
uint8_t gotoAdminOption(){
	exit=0;
	/* Wait indefinitely for a key */
	xQueueReceive(KBD_queue, &adminOptionKey, portMAX_DELAY);

	switch(adminOptionKey) {
		case 1:
			changeDoorCOde();
			break;
		case 2:
			changeAdminCOde();
			break;
		case 3:
			setClock();
			break;
		case 4:
			changeCalendar();
			break;
		case 5:
			printHistoric();
			break;
		case 10:
			exit=1;
			break;
		default:
			LCD_Goto(0,7);
			LCD_WriteString("               ");
			LCD_Goto(0,7);
			LCD_WriteString("invalid command");
	}
	return exit;
}

/*-------------------------------------------------------------------------------*/

uint32_t keyCode;
uint16_t AdminFieldAddr;
uint32_t AdminFieldBuffer;
uint32_t keyNum;
uint8_t changeDoorCOde(){
	LCD_Clear(0xFFF);
	LCD_Goto(0,1);
	LCD_WriteString("New Doorcode:");
	LCD_Goto(5,2);
	keyCode=0;
	for(keyNum=0; keyNum<4;++keyNum){
		//Get a key
		xQueueReceive(KBD_queue, &adminOptionKey, portMAX_DELAY);
		keyCode |= adminOptionKey<<(keyNum*8);
		LCD_WriteChar('0'+adminOptionKey);
	}
	AdminFieldAddr= getFormatedAddress(2*sizeof(int)-sizeof(int));
	AdminFieldBuffer= keyCode;
	EEPROM_Write(&AdminFieldAddr, &AdminFieldBuffer, sizeof(int));
	return 0;
}

/*-------------------------------------------------------------------------------*/

uint8_t changeAdminCOde(){
	LCD_Clear(0xFFF);
	LCD_Goto(0,1);
	LCD_WriteString("New Admincode:");
	LCD_Goto(5,2);
	keyCode=0;
	for(keyNum=0; keyNum<4;++keyNum){
		//Get a key
		xQueueReceive(KBD_queue, &adminOptionKey, portMAX_DELAY);
		keyCode |= adminOptionKey<<(keyNum*8);
		LCD_WriteChar('0'+adminOptionKey);
	}
	AdminFieldAddr= getFormatedAddress(1*sizeof(int)-sizeof(int));
	AdminFieldBuffer= keyCode;
	EEPROM_Write(&AdminFieldAddr, &AdminFieldBuffer, sizeof(int));
	return 0;
}

/*-------------------------------------------------------------------------------*/

uint32_t hh, mm, ss;
uint8_t setClock(){
	LCD_Clear(0xFFF);
	/* Hours */
	LCD_Goto(0,1);
	LCD_WriteString("Insert hour: ");
	hh=0;mm=0;ss=0;
	xQueueReceive(KBD_queue, &adminOptionKey, portMAX_DELAY);
	LCD_WriteChar('0'+adminOptionKey);
	hh= adminOptionKey * 10;

	xQueueReceive(KBD_queue, &adminOptionKey, portMAX_DELAY);
	LCD_WriteChar('0'+adminOptionKey);
	hh+=adminOptionKey;

	/* Minutes */
	LCD_Goto(0,3);
	LCD_WriteString("Insert mins: ");

	xQueueReceive(KBD_queue, &adminOptionKey, portMAX_DELAY);
	LCD_WriteChar('0'+adminOptionKey);
	mm= adminOptionKey * 10;

	xQueueReceive(KBD_queue, &adminOptionKey, portMAX_DELAY);
	LCD_WriteChar('0'+adminOptionKey);
	mm+=adminOptionKey;

	/* Seconds */
	LCD_Goto(0,5);
	LCD_WriteString("Insert secs: ");

	xQueueReceive(KBD_queue, &adminOptionKey, portMAX_DELAY);
	LCD_WriteChar('0'+adminOptionKey);
	ss= adminOptionKey *10;

	xQueueReceive(KBD_queue, &adminOptionKey, portMAX_DELAY);
	LCD_WriteChar('0'+adminOptionKey);
	ss+=adminOptionKey;

	/* Write HOURS into EEPROM */
	AdminFieldAddr= getFormatedAddress(6*sizeof(int)-sizeof(int));
	AdminFieldBuffer= hh;
	EEPROM_Write(&AdminFieldAddr, &AdminFieldBuffer, sizeof(int));

	/* Write MINUTES into EEPROM */
	AdminFieldAddr= getFormatedAddress(7*sizeof(int)-sizeof(int));
	AdminFieldBuffer= mm;
	EEPROM_Write(&AdminFieldAddr, &AdminFieldBuffer, sizeof(int));

	/* Write MINUTES into EEPROM */
	AdminFieldAddr= getFormatedAddress(8*sizeof(int)-sizeof(int));
	AdminFieldBuffer= ss;
	EEPROM_Write(&AdminFieldAddr, &AdminFieldBuffer, sizeof(int));

	LCD_Clear(0xFFF);
	return 0;
}

/*-------------------------------------------------------------------------------*/

uint32_t yyyy, mm, dd;
uint8_t changeCalendar(){
	LCD_Clear(0xFFF);
	yyyy=0;mm=0;ss=0;
	LCD_Goto(0,1);
	LCD_WriteString("Insert year: ");
	/* Year */
	xQueueReceive(KBD_queue, &adminOptionKey, portMAX_DELAY);
	LCD_WriteChar('0'+adminOptionKey);
	yyyy= adminOptionKey * 10;

	xQueueReceive(KBD_queue, &adminOptionKey, portMAX_DELAY);
	LCD_WriteChar('0'+adminOptionKey);
	yyyy+=adminOptionKey;

	/* Minutes */
	LCD_Goto(0,3);
	LCD_WriteString("Insert month: ");

	xQueueReceive(KBD_queue, &adminOptionKey, portMAX_DELAY);
	LCD_WriteChar('0'+adminOptionKey);
	mm= adminOptionKey * 10;

	xQueueReceive(KBD_queue, &adminOptionKey, portMAX_DELAY);
	LCD_WriteChar('0'+adminOptionKey);
	mm+=adminOptionKey;

	/* Seconds */
	LCD_Goto(0,5);
	LCD_WriteString("Insert day: ");

	xQueueReceive(KBD_queue, &adminOptionKey, portMAX_DELAY);
	LCD_WriteChar('0'+adminOptionKey);
	dd= adminOptionKey *10;

	xQueueReceive(KBD_queue, &adminOptionKey, portMAX_DELAY);
	LCD_WriteChar('0'+adminOptionKey);
	dd+=adminOptionKey;

	/* Write HOURS into EEPROM */
	AdminFieldAddr= getFormatedAddress(6*sizeof(int)-sizeof(int));
	AdminFieldBuffer= yyyy;
	EEPROM_Write(&AdminFieldAddr, &AdminFieldBuffer, sizeof(int));

	/* Write MINUTES into EEPROM */
	AdminFieldAddr= getFormatedAddress(7*sizeof(int)-sizeof(int));
	AdminFieldBuffer= mm;
	EEPROM_Write(&AdminFieldAddr, &AdminFieldBuffer, sizeof(int));

	/* Write MINUTES into EEPROM */
	AdminFieldAddr= getFormatedAddress(8*sizeof(int)-sizeof(int));
	AdminFieldBuffer= dd;
	EEPROM_Write(&AdminFieldAddr, &AdminFieldBuffer, sizeof(int));

	LCD_Clear(0xFFF);
	return 0;
}

/*-------------------------------------------------------------------------------*/

uint32_t absReg;
uint32_t currEntry;
uint8_t exit_Historic;
uint8_t printHistoric(){
	exit_Historic=0;
	/* Get nRegist value from EEPROM */
	AdminFieldAddr= getFormatedAddress(NREGIST_ADDR);
	EEPROM_Read(&AdminFieldAddr, &currEntry, sizeof(int));

	/* Get absReg */
	AdminFieldAddr= getFormatedAddress(ABSREGIST_ADDR);
	EEPROM_Read(&AdminFieldAddr, &absReg, sizeof(int));

	while(!exit){
		if(currEntry<0)
			currEntry= MAX_ENTRY_VALUE-1;

		char time[time_len], date[date_len];
		itot(time, dateTime.tm_hour, dateTime.tm_min);
		itod(date, dateTime.tm_mday, dateTime.tm_mon, dateTime.tm_year);
		LCD_Goto(3,1); LCD_WriteString(date);
		LCD_Goto(5,2); LCD_WriteString(time);
		LCD_Goto(3,4); LCD_WriteString("Code: ");
		LCD_Goto(7,5);
		/* Get absReg */
		AdminFieldAddr= getFormatedAddress(entryAddr(currEntry));
		EEPROM_Read(&AdminFieldAddr, &currEntry, sizeof(int));

		if(currEntry) LCD_WriteString("Valid!");
		else LCD_WriteString("Invalid!");

		/* Get a key */
		xQueueReceive(KBD_queue, &adminOptionKey, portMAX_DELAY);

		if(adminOptionKey == CARDINAL)
			break;

		LCD_Clear(0xFFF);
		--currEntry;
	}
	return 0;
}

/*-------------------------------------------------------------------------------*/




/* End of file */
