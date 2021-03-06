/** @file KBD.h
 *  @brief Contains the KBD API.
 *  @author João Duarte
 */

#ifndef __KBD_H__
#define __KBD_H__

/** @defgroup KBD KBD
 * @ingroup KBD
 *	In this module you can find functionalities like 
 *	reading pressed keys.
 * @{

 * @defgroup KBD_Public_Functions KBD Public Functions
 * @{
 */
#include "GPIO.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "queue.h"


/* KEY VALUES */

#define ASTERISK_KEY 10
#define CARDINAL_KEY 11
#define DOUBLE_KEY 12
#define INVALID_KEY -1

/** @brief Configures
 *
 *	Configures the GPIO ports like so:
 *	Keyboard output pins (preferably with pull-up resistor 10k Homs)
 *	C0		C1		C2		C3
 *	P2.5	P2.6	P2.7	P2.8
 *	
 * 	Keyboard input pins
 * 	R0		R1		R2		R3
 * 	P2.1	P2.2	P2.3	P2.4
 *	
 *  @param layout array that contains the key codes in sequence. Last position reserved for additional functionality.
 *  @return none.
 */
uint32_t kbd_layout[16];
const static unsigned columnMask  = 0x1E0;
const static unsigned lineMask = 0x1E;

void KBD_init(uint32_t layout[13]);

/** @brief Checks if any key is pressed.
 *  @return 0 if no key is pressed; 1 otherwise.
 */
uint32_t KBD_hit();

/** @brief Reads any key pressed.
 *	This function reads only the first key pressed. For single key reading only.
 *	This functions waits indefinitely until a key is pressed. 
 *  @return the code of the key, according to the layout established.
 */
uint32_t KBD_read();

/** @brief Reads any key pressed.
 *	This function is non-blocking, which means it does not wait for a pressed key.
 *	This function can also read 2 simultaneous keys pressed. They must be the 2 last columns and last line.
 *  @return the code of the key, according to the layout established.
 */
int KBD_read_nonBlocking();

/**
 * @}
  */
  
/**
 * @}
 */
#endif /* __KBD_H__ */
