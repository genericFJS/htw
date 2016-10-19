/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
//#include <asf.h>
#include <avr/io.h>
#include <stdint.h>

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	//board_init();

	/* Insert application code here, after the board has been initialized. */
	
	// Volatile:	Debugger tut die Variablen nicht "wegoptimieren"
	volatile uint8_t test;

	// Setze das Bit an 0. Stelle
	test |= 1;

	//test |= 1 << BITNUMMER;
	
	PORTB = test;

	//PORTB &= ~(1 << 2); // Pin n goes low
	//PORTB |= (1 << 2); // Pin n goes high
	
	PORTB = 0x1;

	// Verschiebe in jeder Iteration nach links
	// und kopiere den Zustand des Ports nach test
	// test kann dann via "Add to Watch" überwacht werden

	// Wenn die 1 "weggeshiftet" wurde, wird eine neue
	// an die Position 0 gesetzt
	while(1)
	{
		PORTB <<= 1;
		test = PORTB;

		if(!test)
		PORTB |= 1;
	}
}
