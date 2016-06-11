/*
 * KBD_Tests.c
 *
 *  Created on: 21/04/2016
 *      Author: Red
 */

#include "KBD.h"

uint32_t layout[]=		{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

uint32_t KBD_test0(){
	KBD_init(layout);
	return KBD_read();
}

void KBD_test1(){

}
