/*
    FreeRTOS V8.0.0 - Copyright (C) 2012 Real Time Engineers Ltd.


    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?                                      *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************


    http://www.FreeRTOS.org - Documentation, training, latest information,
    license and contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool.

    Real Time Engineers ltd license FreeRTOS to High Integrity Systems, who sell
    the code with commercial support, indemnification, and middleware, under
    the OpenRTOS brand: http://www.OpenRTOS.com.  High Integrity Systems also
    provide a safety engineered and independently SIL3 certified version under
    the SafeRTOS brand: http://www.SafeRTOS.com.
*/

/*
 * This is a very simple demo that demonstrates task and queue usages only.
 * Details of other FreeRTOS features (API functions, tracing features,
 * diagnostic hook functions, memory management, etc.) can be found on the
 * FreeRTOS web site (http://www.FreeRTOS.org) and in the FreeRTOS book.
 * Details of this demo (what it does, how it should behave, etc.) can be found
 * in the accompanying PDF application note.
 *
*/

/* Kernel includes. */
#include "../../FreeRTOS_Library/include/FreeRTOS.h"
#include "../../FreeRTOS_Library/include/task.h"
//#include "../../FreeRTOS_Library/include/croutine.h"


#include <stdio.h>
#include "LPC17xx.h"

#include "queue.h"
#include "semphr.h"
#include "test/tests.h"

#include "Project/Utils.h"

/* Ethernet */
//#include "../uIPAux/src/tapdev.h"



#define KeyAppTest KeyTest();
#define ledTest ledTest();
#define varTest varExampleTaskTest();
#define RTCTest RTCTest();
#define KBDTest kbdTest();
#define LCDTest lcdTest();
#define EEPROMTest eepromTest();
#define EthernetTest EthernetTest();


//
// Change macro to the current designed test
//

#define test kbdTest
#define test123 0

void projTest(){
	I2C_config(1, 100);
	if(!verifyBootLoad()){
		resetBootLoad();
	}
	uint16_t addr= 0;
	uint8_t read[48];
	EEPROM_Read(&addr,read,48);
	int i;
	for(i=0; i<48; ++i){
		printf("Mem[%u]= %X\n",i,*(read+i));
	}

}

void auxEEPROMTest(){
	I2C_config(1, 100);

	uint8_t addr[2]={0x1,0};
	uint8_t buffer[5]={8,9,10,11,12};
	uint8_t read[5];
	EEPROM_Write(addr, buffer,5);
	EEPROM_Read(addr,read,5);
	uint16_t addr1=8;
	uint32_t wbuf=0x04030201;
	uint32_t rbuf=0xFFFFFFFF;
	//EEPROM_Write(&addr1, &wbuf,4);
	//EEPROM_Read(&addr1,&rbuf,4);
	uint8_t* bla=(uint8_t*)&rbuf;
	int i;
	for(i=0; i<48; ++i){
		printf("Mem[%u]= %X\n",i,*(bla+i));
	}


}

void getBootLoadCode(){

	I2C_config(1, 100);
	//resetFlash();
	uint16_t addr= getFormatedAddress(16);
	uint32_t read= 0x0;
	/*
	uint8_t* aux=(uint8_t*) &addr;
	puts("var:\n");
	printf("mem[0]=0x%X\n",*aux);
	printf("mem[1]=0x%X\n",*(aux+1));
	puts("array\n");
	printf("mem[0]=0x%X\n",addr1[0]);
	printf("mem[1]=0x%X\n",addr1[1]);
	*/
	EEPROM_Read(&addr, &read,4);
	printf("BootLoadCode= 0x%X\n",read);
}

void getKeyCode(){
	uint8_t src[4]={4,3,2,1};
	uint32_t key = getKeyFromArray(src);
	uint32_t count;//= keyCode[0]
	for(count=0; count<4;++count){
		key+=src[count]<<(8*count);
	}
	printf("Key: 0x%X\n",key);
}

int pmain(void)
{
	puts("Begin test");

	kbdTest();
	//projTest();
	//auxEEPROMTest();
	//getBootLoadCode();
	//test;

	//getKeyCode();
	puts("End test");
	return 0;
}



