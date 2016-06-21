/** @file LCD.c
 *  @brief Drivers for LCD on LPC2106
 *
 *  Function LCD_Init must be called before anything else.
 *	This module provides functionality to write characters
 *	defined in LCD_Font.c in whatever line/column desired.
 *	
 *	Configuration:
 *	BackLight -> P0.1
 *	RESET -> P0.3
 *	LCD_CS -> P0.5
 *  @author G6
 *
 */

#include "LCD.h"

extern const unsigned char font8x16[97][16];
unsigned short buffer[9];
unsigned int linePosition=2;
unsigned int columnPosition=2;
//lcd is configured for 128x128
//LCD is configured to have 8 lines and 16 columns to write characters
#define LCD_WIDTH  128
#define LCD_HEIGHT 128
#define LCD_CS 0x10			//P0.4
#define RESET_MASK  0x400 //P0.10
#define pCols 8
#define pRows 16
#define MAXPCOLUMNS 120
#define BL_MASK 0x20	//P0.5
/**********************************************************************
 * !!! VERIFICAR OS TEMPOS ESPECIFICADOS NO MANUAL DO CONTROLADOR !!!
 **********************************************************************/

/**
 * @brief	Initilize LCD.
 * @return	Nothing
 */ 
void LCD_Init(void) {
	LCD_LowLevelInit();		// Low level initializations
	
	SPI_BeginTransfer(LCD_CS);
	GPIO_Clear(RESET_MASK);
	GPIO_Set(RESET_MASK);
	//GPIO_output(0,RESET_MASK);
	//GPIO_output(RESET_MASK,RESET_MASK);
	
	LCD_Command(DISCTL); 	// display control
	LCD_Data(0x0C);
	LCD_Data(0x20);
	LCD_Data(0x0C);
	
	LCD_Command(COMSCN); 	// common scanning direction
	LCD_Data(0x01);

	LCD_Command(OSCON); 	// internal oscialltor on

	LCD_Command(SLPOUT); 	// sleep out

	LCD_Command(PWRCTR); 	// power ctrl
	LCD_Data(0x0F); 		//everything on, no external reference resistors

    LCD_Command(0xA7); 		// invert display

	LCD_Command(DATCTL); 	// data control
	LCD_Data(0x00); 		// 3 correct for normal sin7
	LCD_Data(0x00); 		// normal RGB arrangement
	LCD_Data(0x04); 		// 16-bit Grayscale Type A

	LCD_Command(VOLCTR); 	// electronic volume, this is the contrast/brightness
	LCD_Data(0x27); 		// volume (contrast) setting - fine tuning, original
	LCD_Data(0x03); 		// internal resistor ratio - coarse adjustment

	LCD_Command(DISON); 	// display on
	
	SPI_EndTransfer(LCD_CS);
	
	LCD_Clear(0xFFF);
}


/**
 * @brief	Write a character with specified color.
 * @param	x		: Column position.
 * @param	y		: Row position.
 * @param	fColor	: Foreground color.
 * @param	bColor	: Background color.
 * @return	Nothing
 */
void LCD_PutChar(char c, int x, int y, int fColor, int bColor) {
	int i, colIndex;
	unsigned int nCols;
	unsigned int nRows;
	unsigned int nBytes;
	unsigned char pixelRow;
	unsigned int pixel1, pixel2;
	unsigned char *pFont;
	unsigned char *pChar;

	SPI_BeginTransfer(LCD_CS);

	pFont = (unsigned char *) font8x16;
	nCols = *pFont;
	nRows = *(pFont + 1);
	nBytes = *(pFont + 2);

	pChar = pFont + (nBytes * (c - 0x1F)) + nBytes - 1;
	LCD_Command(PASET);
	LCD_Data(LCD_HEIGHT - (y + nRows - 1));
	LCD_Data(LCD_HEIGHT - (y));

	LCD_Command(CASET);
	LCD_Data(LCD_WIDTH - (x + nCols - 1));
	LCD_Data(LCD_WIDTH - (x));

	LCD_Command(RAMWR);
	
	for (i = 0; i < nBytes; i++) {
		pixelRow = *pChar--;
		for (colIndex = 0; colIndex < nCols / 2; colIndex++) {
			pixel1 = ((pixelRow & 0x1) != 0) ? fColor : bColor;
			pixelRow >>= 1;
			pixel2 = ((pixelRow & 0x1) != 0) ? fColor : bColor;
			pixelRow >>= 1;
			LCD_Data((pixel1 >> 4) & 0xFF);
			LCD_Data(((pixel1 & 0xF) << 4) | ((pixel2 >> 8) & 0xF));
			LCD_Data(pixel2 & 0xFF);
		}
	}
	SPI_EndTransfer(LCD_CS);
}

//state: 0-> off x-> on
void LCD_BL_State(uint32_t state){
	if(state)
		GPIO_Set(BL_MASK);
	else GPIO_Clear(BL_MASK);
}

void LCD_TurnOnDisplay(){
	SPI_BeginTransfer(LCD_CS);
	LCD_Command(DISON);
	SPI_EndTransfer(LCD_CS);
}

void LCD_TurnOffDisplay(){
	SPI_BeginTransfer(LCD_CS);
	LCD_Command(DISOFF);
	SPI_EndTransfer(LCD_CS);
}

void LCD_LowLevelInit(){	// Low level initializations
	//GPIO_configDigital(LCD_CS|RESET_MASK|BL_MASK , LCD_CS|RESET_MASK|BL_MASK , LCD_CS|RESET_MASK|BL_MASK);	//start with !CS=1 and !Reset=1
	GPIO_configDigitalGeneric(0, 0, LCD_CS|RESET_MASK|BL_MASK, LCD_CS|RESET_MASK|BL_MASK, LCD_CS|RESET_MASK|BL_MASK);
}

/* Escreve um carácter na posição corrente do cursor. */
void LCD_WriteChar(char ch){
	LCD_PutChar(ch, columnPosition, linePosition, 0, 0xFFF);	
	columnPosition += pCols;
	if(columnPosition >= MAXPCOLUMNS){
		 columnPosition =2;
		 linePosition += pRows;
	}

 }

/* Escreve uma string na posição corrente do cursor. */
void LCD_WriteString(char *str){
	while(*str)
		LCD_WriteChar(*str++);
}

/* Posiciona o cursor na coluna x e linha y do mostrador. */
void LCD_Goto(int x, int y){
	SPI_BeginTransfer(LCD_CS);
	// WriteSpiData(x);
    //WriteSpiData(x + nRows - 1);
	
	LCD_Command(PASET);
	LCD_Data(y);
	LCD_Data(y + pCols -1);

	LCD_Command(CASET);
	LCD_Data(x);
	LCD_Data(x + pRows -1);
	
	SPI_EndTransfer(LCD_CS);
	columnPosition= x*pCols;
	linePosition = y*pRows;
}

/* Limpa o visor com a cor especificada. */
void LCD_Clear(int color){
	int i;
	int j;
	int numberOfColumns = 16;
	int numberOfRows = 16;
	
	columnPosition= 0;
	linePosition = 0;
	
	for( i=0;i < numberOfRows ; i++ ){
		for(j=0;j < numberOfColumns; j++){
			  LCD_PutChar(' ', columnPosition, linePosition, 0, color);
			  columnPosition += pCols ;	
		}
	 columnPosition= 0;
	 linePosition += 8;

	}
	
	columnPosition= 2;
	linePosition = 2;
		
}

void LCD_ClearLine(uint8_t line){
	LCD_Goto(0,line);
	LCD_WriteString("               ");
}

void LCD_Command(unsigned short command){
	 unsigned short *rxBuffer=(unsigned short*)&buffer;
	 SPI_Transfer( &command, (unsigned short*)rxBuffer, 1);
 }
 
void LCD_Data(unsigned short data){
	 unsigned short *rxBuffer=(unsigned short*)&buffer;
	 data |= 0x100;
	 SPI_Transfer( &data, (unsigned short*)rxBuffer, 1);
 }
