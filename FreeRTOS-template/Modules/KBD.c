#include "KBD.h"

//
//	Keyboard output pins (with pull-up resistor 10k Homs)
//	C0		C1		C2		C3
//	P0.12	P0.11	P0.10	P0.9
//	
//	Keyboard input pins
//	R0		R1		R2		R3
//	P0.16	P0.15	P0.13	X
//
//void _delay(int millis);// !!!!!DANGER!!!!! CHANGE TO TIMER0 SOME OTHER TIME

void KBD_init(uint32_t layout[16]){
	//GPIO_config(lineMask,lineMask|columnMask, lineMask);
	GPIO_configDigitalGeneric(2, 0, lineMask,lineMask|columnMask, lineMask);
	//neither pull
	GPIO_configAnalogGeneric(2, 2, 0, lineMask);
	//on-chip pull-up resistor
	GPIO_configAnalogGeneric(2, 0, 0, columnMask);
	int i;
	for(i=0;i<16;++i)
		kbd_layout[i]=layout[i];
}

uint32_t KBD_hit(){
	unsigned i;
	unsigned outputPosition = 0x2;
	for(i=0;i<4;++i, outputPosition<<=1){
		//if(i==1) continue;//lineMask is not in sequence
		GPIO_output(2,~outputPosition, lineMask );
		unsigned col= GPIO_input(2) & columnMask;
		if((col^columnMask)!= 0)
			return 1;
	}
	return 0;
}

// Keyboard read Blocking
uint32_t KBD_read(){
	while( !KBD_hit() ){
		//Waiting on a key
	}
	//Key was hit
	unsigned i,col;
	unsigned outputPosition = 0x2;
	for(i=0;i<4;++i, outputPosition<<=1){
		//if(i==1) continue;
		GPIO_output(2,~outputPosition, lineMask);
		col= GPIO_input(2) & columnMask;
		if((col^columnMask)!= 0)				
			break;		 
	}
	unsigned line_value= i;
	col= (col & columnMask) >> 5;

	//Get column value
	unsigned column_value=0;
	while(col & 0x1){
		col>>=1;
		++column_value;
	}
	while(KBD_hit() ){
		//Waiting for release
	}
	return kbd_layout[4*line_value + column_value];
}

/*Keyboard read non-Blocking
returns -1 when no key is pressed
returns value
*/


int KBD_read_nonBlocking(){
	if( !KBD_hit() ){
		return -1;
	}
	//Key was hit  
	//TMR0_Delay(100);
	unsigned i,col;
	unsigned outputPosition = 0x2;
	for(i=0;i<4;++i, outputPosition<<=1){
		//if(i==1) continue;
		GPIO_output(2,~outputPosition, lineMask);
		col= GPIO_input(2) & columnMask;
		if((col^columnMask)!= 0)
			break;
	}
	unsigned line_value= i;//i>=1? i-1 : i;
	col= (col & columnMask) >> 5;

	//Get column value
	
	unsigned column_value=0,col_aux=col,zeroes=0;
	for(i=0;i<4;++i,col>>=1){
		if((col & 0x1)==0){
			column_value=i;
			++zeroes;
		}
	}
	//printf("line_value= %u | column_value= %u\n", line_value, column_value );
	if(col_aux ==3 && line_value==2)
		return kbd_layout[12];
	if(zeroes==1) return kbd_layout[4*line_value + column_value];
	return -1;
}



