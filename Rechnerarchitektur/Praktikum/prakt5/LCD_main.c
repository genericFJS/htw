/*****************************************************************************
 * 
 * Demonstration application. Prints the string "STK502" on LCD.
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
 * Name    : RELEASE_1_1
 * Revision: 1.3
 * RCSfile : main.c,v
 * Date    : 2006/02/16 18:14:01 
 ******************************************************************************/

// ===================================================
// modifiziert durch Prof. J. Schönthier, HTW Dresden
// letzte Änderung: 30.12.2010
// ===================================================

#include <avr/io.h>
#include <avr/interrupt.h>

#include "LCD_driver.h"

/* Generate a delay that depends on the LCD clock rather than the system clock.
   delay: - number of LCD frames to delay the subsequent code execution.
 */
void LCD_timerDelay( unsigned char delay )
{
  cli(); 								// Disable interrupts
  LCD_timer = delay;                  	// Plant LCD_timer seed to generate delay - delay*(1/[LCD frame rate])
  LCD_status.updateComplete = FALSE; 	// Clear updateComplete to be able to test if LCD interrupt has been served
  LCD_status.updateRequired = TRUE;  	// Request update of the LCD to let the LCD ISR clear set updateComplete
  sei(); 								// Enable interrupts.
  while( !LCD_status.updateComplete ); 	// Don't update the LCD_displayData into LCD has been updated
}


#define DELAY1 64
#define DELAY2 5

int main(void)
{
    unsigned char counter;
    unsigned char testString[] = "STK502";

    LCD_Init(); 	// initialize the LCD
	sei(); 			// Enable interrupts.

    for(;;)  		// endless main loop
    {
//----------------------------------------------------------
// Display a single character from the testString at a time
//----------------------------------------------------------
      for (counter = 0; counter < 6; counter++ )
      {
        while( !LCD_status.updateComplete ); 	// Don't update the LCD_displayData into LCD has been updated
        LCD_status.updateRequired = FALSE;   	// Block the updating of the LCD while accessing LCD_displayData
        LCD_WriteDigit( *(testString + counter), counter+2 ); // Write new data to LCD_displayData
        LCD_status.updateComplete = FALSE;   	// Clear LCD_updateComplete flag to indicate that LCDdisplayData
                                              	// has been updated, but LCD has not been updated yet.
        LCD_status.updateRequired = TRUE;   	// Request update of the LCD (release LCD update blocking).
      }
      while( !LCD_status.updateComplete );   	// Make sure that the LCD_displayData has been latched


//----------------------------------------------------------
// Vary the contrast level between min and max and min, and back to norm
//----------------------------------------------------------
      for(counter = 0x00; counter < 0x0F; counter++)  // Increase LCD contrast to max, in smallest steps
      {
        LCD_CONTRAST_LEVEL(counter);
        LCD_timerDelay( DELAY2 );                   // Call LCD interrupt controlled delay
      }
      for(counter = 0x0F; counter != 0x00; counter--)  // Decrease LCD contrast to min, in smallest steps
      {
        LCD_CONTRAST_LEVEL(counter);
        LCD_timerDelay( DELAY2 );                   // Call LCD interrupt controlled delay
      }
      LCD_CONTRAST_LEVEL( LCD_INITIAL_CONTRAST );   // Contrast level back to initial level


//----------------------------------------------------------
// Clear all LCD digits in within one LCD opdate
//----------------------------------------------------------
      while( !LCD_status.updateComplete );          // Wait for last LCD update to complete
      LCD_status.updateRequired = FALSE;            // Disable further LCD updating
      for (counter = 2; counter < 8; counter++ )
      {
            LCD_WriteDigit( '-', counter );         // Update LCD_displayData buffer
      }
      LCD_status.updateRequired = TRUE;             // Enable LCD opdating
      while( !LCD_status.updateComplete );          // Make sure that the LCD_displayData has been latched...

     }
}

