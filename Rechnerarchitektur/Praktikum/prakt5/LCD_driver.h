/* ****************************************************************************
 *
 * Defines and prototypes for LCD_driver.c
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
 * RCSfile : LCD_driver.h,v 
 * Date    : 2006/02/16 18:14:01 
 ******************************************************************************/

// ===================================================
// modifiziert durch Prof. J. Schönthier, HTW Dresden
// letzte Änderung: 31.12.2010
// ===================================================

#ifndef LCD_DRIVER_H_ //JS
#define LCD_DRIVER_H_ //JS


#define FALSE   0 //JS
#define TRUE    1 //JS

/**************************************************************/
// Definitions
/**************************************************************/
#define LCD_INITIAL_CONTRAST 0x0F
#define LCD_TIMER_SEED		15
#define LCD_REGISTER_COUNT  20

/**************************************************************/
//MACROS
/**************************************************************/
#define LCD_SET_COLON(active) LCD_displayData[8]=active;  // active =[TRUE;FALSE]
#define pLCDREG (*(unsigned char *)(0xEC))                // DEVICE SPECIFIC!!! (ATmega169(P))
#define LCD_CONTRAST_LEVEL(level) LCDCCR=(0x0F & level);  // DEVICE SPECIFIC!!! (ATmega169(P))

/**************************************************************/
// Global functions
/**************************************************************/
void LCD_Init (void);
void LCD_WriteDigit(unsigned char input, unsigned char digit);
void LCD_AllSegments(unsigned char);

/**************************************************************/
// Global variables //JS: Mix aus AVR064 und AVR065
/**************************************************************/
union _LCD_status{
  unsigned char allFields;
  struct{
    volatile unsigned char updateRequired : 1; //Indicates that the LCD_displayData should be latched to the LCD Data Regs
                                      // Can be used to block LCD updating, while updating LCD_displayData.
    volatile unsigned char updateComplete : 1; //Indicates that the LCD_displayData has been latched to the LCD Data Regs
                                      // Can be used to determine if LCD_displayData is ready for new data.
    volatile unsigned char blinkLCD       : 1; //Indicates whether the actual LCD-digit should blink or not
    unsigned char unused : 5;
  };
};
extern union _LCD_status LCD_status;

extern unsigned char LCD_timer;           //!< Determine the delay to next LCD update
extern unsigned char LCD_displayData[LCD_REGISTER_COUNT];

#endif // LCD_DRIVER_H_
