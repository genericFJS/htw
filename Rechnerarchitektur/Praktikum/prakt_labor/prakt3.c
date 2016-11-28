#include <avr/io.h>
#include <avr/interrupt.h>

// Interrupt Anweisung für Timer 0 Overflow
ISR(TIMER0_OVF_vect){
}

// Interrupt Anweisung für Schalter 1
ISR(INT2_vect){
}

int main (void){
	DDRB = 0xFF;	// B komplett als Ausgabe definieren
	DDRD = 0x00;	// D komplett als Eingang definieren
	
	// Timer: (alle 262ms)
	TCCR0 = (1 << CS02) | (1 << CS01) |(1 << CS00);
	TIMSK |= (1 << TOIE0);

	// Tasten-Interrupt konfigurieren:
	EICRA |= (1 << ISC21);
	EICRA &= ~(1 << ISC20);
	EIMSK = (1 << INT2);

	sei();	// Interrupts aktivieren

	while(42);
}
