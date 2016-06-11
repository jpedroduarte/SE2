/** @file KBD.h
 *  @brief Contains the KBD API.
 *  @author G6
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

/** @brief Configures
 *
 *	Configures the GPIO ports like so:
 *	Keyboard output pins (preferably with pull-up resistor 10k Homs)
 *	C0		C1		C2		C3
 *	P0.12	P0.11	P0.10	P0.9
 *	
 * 	Keyboard input pins
 * 	R0		R1		R2		R3
 * 	P0.16	P0.15	P0.13	X
 *	
 *  @param layout array that contains the key codes in sequence. Last position reserved for additional functionality.
 *  @return none.
 */
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
//uint32_t KBD_read_nonBlocking();

/**
 * @}
  */
  
/**
 * @}
 */
#endif /* __KBD_H__ */
