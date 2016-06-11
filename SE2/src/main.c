/*
===============================================================================
 Name        : SE2.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include "GPIO_Tests.h"
#include "KBD_Tests.h"
#include "FreeRTOS_Tests.h"
// TODO: insert other include files here

// TODO: insert other definitions and declarations here


int main(void) {
	//puts("Hello");
	//FRTOStest0();
	//GPIO_test2();
	/*
	while(1){
		printf("input: 0x%x ",GPIO_test0()&0x100);
	}
	*/
	//GPIO_test1();
	//uint32_t k= KBD_test0();
	/*
	while(1){
		printf("Key: %u ",KBD_test0());
	}
    printf("Hello World\n");

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
    }
    return 0 ;
    */
}
