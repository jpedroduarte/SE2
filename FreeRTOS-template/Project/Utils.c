/*
 * Utils.c
 *
 *  Created on: 08/06/2016
 *      Author: Red
 */


#include "Utils.h"
#include "Environment_Tasks.h"

/*todo
 * Year only asks for 2 chars
 * View history must clean first
 */

/* Program variables*/

uint32_t layout[16]=	{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
uint8_t lcdDataTimeOn = 0;

void itos(char* dst, uint32_t n){
	dst[0]= n%10 + '0'; n/=10;
	dst[1]= n%10 + '0'; n/=10;
	dst[2]= n%10 + '0'; n/=10;
	dst[3]= n%10 + '0';
	dst[4]=0;
}

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

void turnOnLcdAndWriteTime(){//done
    LCD_TurnOnDisplay();
    LCD_BL_State(1);
    RTC_GetValue(&dateTime);
    char time[time_len], date[date_len];
    itot(time, dateTime.tm_hour, dateTime.tm_min);
	itod(date, dateTime.tm_mday, dateTime.tm_mon, dateTime.tm_year);
    LCD_Goto(3,1); LCD_WriteString(date);
    LCD_Goto(5,2); LCD_WriteString(time);
	LCD_Goto(5,3);
	//if(count>=0)LCD_WriteChar('*');
}



/*-------------------------------------------------------------------------------*/

void turnOnLcdAndWriteTimeAdmin(){//done
    LCD_TurnOnDisplay();
    LCD_BL_State(1);
    RTC_GetValue(&dateTime);
    char time[time_len], date[date_len];
    itot(time, dateTime.tm_hour, dateTime.tm_min);
	itod(date, dateTime.tm_mday, dateTime.tm_mon, dateTime.tm_year);
    LCD_Goto(3,1); LCD_WriteString(date);
    LCD_Goto(5,2); LCD_WriteString(time);
    LCD_Goto(4,3);LCD_WriteString("Admin code:");
	LCD_Goto(5,4);
	//if(count>=0)LCD_WriteChar('*');
}

/*-------------------------------------------------------------------------------*/

void printLCDMaintenanceMenu(){//done
	LCD_TurnOnDisplay();
	LCD_Goto(0,0);LCD_WriteString("1-Set doorcode");
	LCD_Goto(0,1);LCD_WriteString("2-Set admincode");
	LCD_Goto(0,2);LCD_WriteString("3-Set clock");
	LCD_Goto(0,3);LCD_WriteString("4-Set calendar");
	LCD_Goto(0,4);LCD_WriteString("5-View history");
	LCD_Goto(0,5);LCD_WriteString("A-Leave        ");
	LCD_ClearLine(7);
	LCD_BL_State(1);
}

/*-------------------------------------------------------------------------------*/

uint8_t verifyBootLoad(){
	uint16_t BootLoadAddress= getFormatedAddress(CHECK_BOOT_LOAD_ADDR);
	uint32_t buffer=0;
	EEPROM_Read(&BootLoadAddress,&buffer, 4);
	printf("code? = 0x%X\n",buffer);
	if(buffer != BootLoadCode)
		return 0;
	return 1;
}

/*-------------------------------------------------------------------------------*/
uint16_t a= 0 ;
uint32_t b;
uint16_t addr;
void resetBootLoad(){
	addr= getFormatedAddress(ADMINCODE_ADDR);
	printf("reset addr: 0x%X\n",addr);
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
	printf("reset adminCode: 0x%X\n",s.adminCode);
	EEPROM_Write(&addr, &s,sizeof(Settings));
	//test
	uint16_t addr1= 0;
	Settings s;

	EEPROM_Read(&addr1, &s,sizeof(Settings));

	uint8_t * bla= (uint8_t*)&s;
	int i=0;
	for(i=0; i<48; ++i){
		printf("Mem[%u]= %X\n",i,*(bla+i));
	}
}

/*-------------------------------------------------------------------------------*/

uint16_t getFormatedAddress(uint16_t src){
	uint16_t aux= src >>8;
	uint16_t aux1= (src & 0x00FF)<<8;
	return aux1+aux;
}

/*-------------------------------------------------------------------------------*/

uint16_t DoorCodeAddress;
uint32_t buffer;
uint8_t VerifyCode(uint32_t code){
	DoorCodeAddress= getFormatedAddress(DOORCODE_ADDR);
	EEPROM_Read(&DoorCodeAddress, &buffer, sizeof(int));
	if(buffer != code)
		return 0;
	return 9;
}

/*-------------------------------------------------------------------------------*/


uint8_t VerifyAdminCode(uint32_t code){
	uint16_t AdminCodeAddress;
	uint32_t AdminCodebuffer=0x02020202;
	//uint8_t AdminCodebuffer[4];
	AdminCodeAddress= getFormatedAddress(ADMINCODE_ADDR);
	//printf("***ADDRESS: 0x%X\n",AdminCodeAddress);
	EEPROM_Read(&AdminCodeAddress, (uint8_t*)&AdminCodebuffer, sizeof(int));
	printf("***Admin Code: 0x%X\n", AdminCodebuffer);
	if(AdminCodebuffer != code)
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
	VerifyAdminCode(0);
	//printf("***Entry Number: %u\n",entry);
	++entry;
	if(entry >= MAX_ENTRY_VALUE){	// EEPROM memory is full
		/* Reset EEPROM entry pointer */
		entry=0;
		EEPROM_Write(&entryAddr, &entry,sizeof(uint32_t));
		VerifyAdminCode(0);
		/*Put AbsReg to 1 to indicate EEPROM is full of entries */
		entry=1;
		entryAddr= getFormatedAddress(ABSREGIST_ADDR);
		EEPROM_Write(&entryAddr, &entry, sizeof(int));
		VerifyAdminCode(0);
	}else{
		// Get DateTime
		RTC_GetValue(&dateTime);
		r.hr = dateTime.tm_hour;
		r.mm = dateTime.tm_min;
		r.s = dateTime.tm_sec;
		r.year = dateTime.tm_year;
		r.month = dateTime.tm_mon;
		r.day = dateTime.tm_mday;
		r.dayWeek = dateTime.tm_wday;
		printf("*VALIDATED= %X\n",validated);
		r.validation = validated;

		/* Update nRegist in EEPROM */
		entryAddr= getFormatedAddress(NREGIST_ADDR);
		EEPROM_Write(&entryAddr,&entry,sizeof(uint32_t));


		//VerifyAdminCode(0);
		/* Write new Entry */
		printf("sizeof: %u\n",sizeof(Regist));
		printf("addr: %u\n",(entry-1)*sizeof(Regist)+sizeof(Settings));
		entryAddr= getFormatedAddress((entry-1)*sizeof(Regist)+sizeof(Settings));
		EEPROM_Write(&entryAddr,&r,sizeof(Regist));

//		entry_Addr=0;
//		uint8_t test[100];
//		EEPROM_Read(&entryAddr,&test,100);
//		int i;
//		for(i=0; i<100; ++i)
//			printf("Mem[%u]=0x%X\n", i, test[i]);
		//uint32_t test=0x03030303;
		//EEPROM_Write(&entry_addr,&test,4);
		VerifyAdminCode(0);
	}
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
uint8_t setClock(){//todo parsing
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
//todo get 2 more chars

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

uint32_t nRegMaxValue;
uint32_t absReg;
int currEntry;
uint32_t validate;
uint8_t exit_Historic;
uint8_t printHistoric(){
	LCD_Clear(WHITE);
	exit_Historic=0;
	/* Get nRegist value from EEPROM */
	AdminFieldAddr= getFormatedAddress(NREGIST_ADDR);
	EEPROM_Read(&AdminFieldAddr, &nRegMaxValue, sizeof(int));
	if(nRegMaxValue==0)
		return 0;
	currEntry= nRegMaxValue;
	/* Get absReg */
	AdminFieldAddr= getFormatedAddress(ABSREGIST_ADDR);
	EEPROM_Read(&AdminFieldAddr, &absReg, sizeof(int));

	while(!exit){

		printf("entry1: %u\n",currEntry);
		if(currEntry<0)
			if(absReg)
				currEntry= MAX_ENTRY_VALUE-1;
			else currEntry= nRegMaxValue;
		printf("entry2: %u\n",currEntry);
		char time[time_len], date[date_len], entryNumber[entry_string_len];
		itot(time, dateTime.tm_hour, dateTime.tm_min);
		itod(date, dateTime.tm_mday, dateTime.tm_mon, dateTime.tm_year);
		LCD_ClearLine(1);LCD_Goto(3,1); LCD_WriteString(date);
		LCD_ClearLine(2);LCD_Goto(5,2); LCD_WriteString(time);
		LCD_ClearLine(4);LCD_Goto(3,4); LCD_WriteString("Code: ");
		LCD_ClearLine(5);LCD_Goto(7,5);

		/* Validation */

		AdminFieldAddr= sizeof(Settings)+currEntry*sizeof(Regist);
		printf("Entry addr: %u | entry: %u\n",AdminFieldAddr,currEntry);
		AdminFieldAddr= getFormatedAddress(AdminFieldAddr);
		EEPROM_Read(&AdminFieldAddr, &validate, sizeof(int));

		if(validate) LCD_WriteString("Valid!");
		else LCD_WriteString("Invalid!");
		printf("entry3: %u\n",currEntry);
		itos(entryNumber,currEntry);
		LCD_ClearLine(7);LCD_Goto(6,7); LCD_WriteString(entryNumber);
		printf("entry4: %u\n",currEntry);
		/* Get a key */
		xQueueReceive(KBD_queue, &adminOptionKey, portMAX_DELAY);

		if(adminOptionKey == CARDINAL)
			break;

		//LCD_Clear(0xFFF);
		--currEntry;
	}
	return 0;
}

/*-------------------------------------------------------------------------------*/




/* End of file */
