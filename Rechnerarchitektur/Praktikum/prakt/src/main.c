#include <avr/io.h>
#include <avr/interrupt.h>
//#include <stdint.h>

// Interrupt Anweisung für Timer 0 Overflow
ISR(TIMER0_OVF_vect){
	PORTB = ~PORTB;
}

int main (void){
	DDRB = 0xFF;
	
	// Timer: (alle 262ms)
	TCCR0 = (1 << CS02) | (1 << CS01) |(1 << CS00);
	TIMSK |= (1 << TOIE0);

	sei();	// Interrupts aktivieren

	while(42);
}
