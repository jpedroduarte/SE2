/**
* @file		LCD.h
* @brief	Contains the LCD API.
* @author	G6
*/

#ifndef __LCD_H__
#define __LCD_H__

/** @defgroup LCD LCD
 * @ingroup LCD
 * This package provides the core capabilities such as initilizing the nokia lcd, writing any characters in the desired positions
 *	and controlling the backlight.
 * @{

 * @defgroup LCD_Public_Functions LCD Public Functions
 * @{
 */

#include "GPIO.h"
#include "SPI.h"

//********************************************************************
//
//					EPSON Controller Definitions
//
//********************************************************************
#define DISON       0xAF
#define DISOFF      0xAE
#define DISNOR      0xA6
#define DISINV      0xA7
#define SLPIN       0x95
#define SLPOUT      0x94
#define COMSCN      0xBB
#define DISCTL      0xCA
#define PASET       0x75
#define CASET       0x15
#define DATCTL      0xBC
#define RGBSET8     0xCE
#define RAMWR       0x5C
#define RAMRD       0x5D
#define PTLIN       0xA8
#define PTLOUT      0xA9
#define RMWIN       0xE0
#define RMWOUT      0xEE
#define ASCSET      0xAA
#define SCSTART     0xAB
#define OSCON       0xD1
#define OSCOFF      0xD2
#define PWRCTR      0x20
#define VOLCTR      0x81
#define VOLUP       0xD6
#define VOLDOWN     0xD7
#define TMPGRD      0x82
#define EPCTIN      0xCD
#define EPCOUT      0xCC
#define EPMWR       0xFC
#define EPMRD       0xFD
#define EPSRRD1     0x7C
#define EPSRRD2     0x7D
#define NOP         0x25


/* Colors */

#define WHITE 0xFFF


/** @brief Configures GPIO ports for correct use.
 *  @return none.
 */
void LCD_LowLevelInit(void);

/** @brief Initialization sequence for the Nokia 6610 LCD.
 *  @return none.
 */
void LCD_Init(void);

/** @brief Writes a character in the LCD at the specified location.
 *	@param c character to write.
 *	@param x column position in which to write.
 *	@param y line in which to write.
 *	@param fColor Color of the character.
 *	@param bColor Color of the background of the character.
 *  @return the code of the key, according to the layout established.
 *  @return none.
 */
void LCD_PutChar(char c, int x, int y, int fColor, int bColor);

/** @brief Sends a command byte to LCD.
 *  @return none.
 */
void LCD_Command(unsigned short command);

/** @brief Sends a data byte to LCD.
 *  @return none.
 */
void LCD_Data(unsigned short data);

/** @brief Writes a character in the current position.
 *  @return none.
 */
void LCD_WriteChar(char ch);

/* Escreve uma string na posição corrente do cursor. */
void LCD_WriteString(char *str);

/** @brief Positions the cursor on the given location by the parameters
 *  @param x indicates the column to go to.
 *  @param y indicates the row to go to.
 *  @return none.
 */
void LCD_Goto(int x, int y);

/** @brief Cleans lcd with the specified color.
 *  @param color of the background.
 *  @return none.
 */
void LCD_Clear(int color);

/** @brief Cleans a line from the LCD.
 *  @param Number of the row to clear starting in 0.
 *  @return none.
 */
void LCD_ClearLine(uint8_t line);

/** @brief Turns off display.
 *  @param line to clear.
 *  @return none.
 */
void LCD_TurnOffDisplay();

/** @brief Turns on display
 *  @return none.
 */
void LCD_TurnOnDisplay();

/** @brief Sets state of LCD backlight.
 *	@param uint32_t state turns off light if 0; Turns on otherwise.
 *  @return none.
 */
void LCD_BL_State(uint32_t state);


/**
 * @}
  */
  
/**
 * @}
 */
#endif /* __LCD_H__ */
