/* *****************************************************************************
 *
 * Functions used to control the STK502 LCD
 *
 * LCD Driver for the STK502
 *
 * Documentation:
 *      For comprehensive code documentation, supported compilers, compiler
 *      settings and supported devices see readme.html
 *
 * Author
 *      Atmel Corporation: http://www.atmel.com
 *      Support email: avr@atmel.com
 *
 * Name     :RELEASE_1_1
 * Revision: 1.3
 * RCSfile : LCD_driver.c,v
 * Date    : 2006/02/16 18:14:01
 ******************************************************************************/

// ===================================================
// modifiziert durch Prof. J. Schönthier, HTW Dresden
// letzte Änderung: 31.12.2010
// ===================================================

// Include files.
#include "LCD_driver.h"
#include <avr/pgmspace.h>  //JS
#include <avr/interrupt.h> //JS

union _LCD_status LCD_status = {0x01};    // LCD_status = {0, 0, 0, 0, 0, 0, FALSE, TRUE};
unsigned char LCD_timer = LCD_TIMER_SEED;										
unsigned char LCD_displayData[LCD_REGISTER_COUNT];	// LCD display buffer (for double buffering).

// Look-up table used when converting ASCII to LCD display data	(segment control)
//JS __flash unsigned int LCD_character_table[] = // Character definitions table.
uint16_t LCD_character_table[] PROGMEM = //JS Character definitions table.
{
	0xEAA8,		// '*' //JS
	0x2A80,		// '+'
	0x2000,		// ',' //JS
	0x0A00,		// '-'
	0x0A51,		// '.' (Gradsymbol) //JS
	0x4008,		// '/' //JS
	0x5559,		// '0'
	0x0118,		// '1'
	0x1e11,		// '2'
	0x1b11,		// '3'
	0x0b50,		// '4'
	0x1b41,		// '5'
	0x1f41,		// '6'
	0x0111,		// '7'
	0x1f51,		// '8'
	0x1b51,		// '9'
	0x0000,		// ':' (not defined)
	0x0000,		// ';' (not defined)
	0x0000,		// '<' (not defined)
	0x0000,		// '=' (not defined)
	0x0000,		// '>' (not defined)
	0x0000,		// '?' (not defined)
	0x1CD1,		// '@' //JS
	0x0f51,		// 'A' (+ 'a')
	0x3991,		// 'B' (+ 'b')
	0x1441,		// 'C' (+ 'c')
	0x3191,		// 'D' (+ 'd')
	0x1e41,		// 'E' (+ 'e')
	0x0e41,		// 'F' (+ 'f')
	0x1d41,		// 'G' (+ 'g')
	0x0f50,		// 'H' (+ 'h')
	0x2080,		// 'I' (+ 'i')
	0x1510,		// 'J' (+ 'j')
	0x8648,		// 'K' (+ 'k')
	0x1440,		// 'L' (+ 'l')
	0x0578,		// 'M' (+ 'm')
	0x8570,		// 'N' (+ 'n')
	0x1551,		// 'O' (+ 'o')
	0x0e51,		// 'P' (+ 'p')
	0x9551,		// 'Q' (+ 'q')
	0x8e51,		// 'R' (+ 'r')
	0x9021,		// 'S' (+ 's')
	0x2081,		// 'T' (+ 't')
	0x1550,		// 'U' (+ 'u')
	0x4448,		// 'V' (+ 'v')
	0xc550,		// 'W' (+ 'w')
	0xc028,		// 'X' (+ 'x')
	0x2028,		// 'Y' (+ 'y')
	0x5009,		// 'Z' (+ 'z')
	0x0000,		// '[' (not defined)
	0x8020,		// '\' //JS
	0x0000,		// ']' (not defined)
	0x0000,		// '^' (not defined)
	0x1000		// '_' //JS
};


/* Initialize LCD_displayData buffer. Set up the LCD (timing, contrast, etc.) */
void LCD_Init (void)
{
	LCD_AllSegments( FALSE );	// Clear segment buffer.
	LCDCRA = (1<<LCDEN);		// Enable LCD.

    LCD_CONTRAST_LEVEL(LCD_INITIAL_CONTRAST);    //Set the LCD contrast level

	// Select asynchronous clock source, enable all COM pins and enable all segment pins.
	LCDCRB = (1<<LCDCS) | (1<<LCDMUX1) | (1<<LCDMUX0) | (1<<LCDPM2) | (1<<LCDPM1)| (1<<LCDPM0);
	LCDFRR = (1<<LCDPS0);                       // Set LCD prescaler to CLK(lcd)/64 = 64Hz.

	LCDCRA |= (1<<LCDIE);	                    // Enable LCD_Start_frame interrupt
}


/* Stores LCD control data in the LCD_displayData buffer.
 *  (The LCD_displayData is latched in the LCD_SOF interrupt).
 *
 * c    : The symbol to be displayed in a LCD digit.
 * digit: The LCD digit that the symbol should be displayed in.
 */
void LCD_WriteDigit( unsigned char c, unsigned char digit )
{

	uint16_t      seg; //JS
	unsigned char i;
	unsigned char mask, nibble;
	unsigned char *ptr;

	// Lookup character table for segmet data
	seg = 0x0000;
	if ( (c >= '*') && (c <= 'z') )
	{
		// c is in character_table.
		// Convert to upper if necessary.
		if ( c >= 'a' ) c &= ~0x20;
		c -= '*';
		//JS seg = LCD_character_table[c];
		seg = pgm_read_word(&(LCD_character_table[c])); //JS
	}
	else
	{
		return;		//ASCII code out of range
	}

	// Adjust mask according to digit
	mask = 0x0F;		// (1), 3, 5, 7
	if ( digit & 0x01 )
	{
		// left empty to optimize code size
	}
	else
	{
		mask = 0xF0;		// (0), 2, 4, 6
	}

	i = digit-2;		// i used as pointer offset
	if ( i >= 6 )		// Test if LCD digit is out of range
		return;
	i >>= 1;
	ptr = LCD_displayData + i;	// Point to the first relevant LCDDR; i = {0,0,1,1,2,2}

	i = 4;			// i used as loop counter
	do
	{
		nibble = seg & 0x000F;
		seg >>= 4;
		if ( digit & 0x01 )
			nibble <<= 4;
		*ptr = (*ptr & mask) | nibble;
		ptr += 5;
	} while ( --i );
}


/* display all or hide all LCD segments on the STK502 LCD.
 *
 * input: [TRUE;FALSE]=[DISPLAY;HIDE].
 */
void LCD_AllSegments( unsigned char input )
{
	unsigned char i;
	unsigned char *ptr;

	if( input )				    // if input == TRUE
		input = 0xFF;			// set segments to 0xFF
								// (else set segments to 0x00)
	
	ptr = LCD_displayData;
	i = 20;
	do							// Set all LCD segment register to the variable ucSegments
	{
		*ptr++ = input;		// Set/clear the bits in all LCD registers
	} while ( --i );
}


/* Latch the LCD_displayData and Set LCD_status.updateComplete.*/
//JS #pragma vector = LCD_SOF_vect
//JS __interrupt void LCD_SOF_interrupt( void )
ISR(LCD_vect) //JS
{
	unsigned char i;
	unsigned char *src, *dest;

	LCD_timer--;
	if( LCD_timer == 0 )
	{
	    if( LCD_status.updateRequired == TRUE )
		{
			LCD_timer = LCD_TIMER_SEED;
			LCD_status.updateComplete = TRUE;	// Set the ucLCD_ScrollReady to true.
			LCD_status.blinkLCD = ~LCD_status.blinkLCD;	// Toggle LCD_Blink variable.//JS: Zeile aus AVR064

			// Copy display data buffer to I/O segment registers.
			i = 20;
			dest = &pLCDREG;
			src = LCD_displayData;
			do
			{
				*dest++ = *src++;
			} while ( --i );
		}
		else
		{
		  LCD_timer = 1;              //If LCD timer allows update of the LCD, but update is blocked
		                              // by LCD_status.updateRequired == FALSE the LCD_timer is preloaded
		                              // with smallest timer seed to ensure fastest LCD update.
          LCD_status.updateComplete = FALSE;  //Block for further access to the LCD_displayData until
                                              // LCD update has been performed.
		}
	}
}
