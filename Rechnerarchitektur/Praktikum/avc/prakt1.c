#include <avr/io.h>
#include <stdint.h>

int main(void)
{
	// Volatile:	Debugger tut die Variablen nicht "wegoptimieren"
	volatile uint8_t test;

	// Setze das Bit an 0. Stelle
	test |= 1;

	//test |= 1 << BITNUMMER;
	PINB = test;

	// Verschiebe in jeder Iteration nach links
	// und kopiere den Zustand des Ports nach test
	// test kann dann via "Add to Watch" überwacht werden

	// Wenn die 1 "weggeshiftet" wurde, wird eine neue
	// an die Position 0 gesetzt
	while(1)
	{
		PINB <<= 1;
		test = PINB;

		if(!test)
			PINB |= 1;
	}
}
