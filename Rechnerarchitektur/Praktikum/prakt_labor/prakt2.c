#include <avr/io.h>
#include <avr/interrupt.h>
//#include <stdint.h>

int muster = 0x0F;
int temp = 0;
int right = 1; // 0: nach links, anderes: nach rechts

// Interrupt Anweisung für Timer 0 Overflow
ISR(TIMER0_OVF_vect){
	//PORTB = ~PORTB;
	temp = PORTB;
	if (right){	
		PORTB >>= 1;
		if (temp & (1<<0)){
			PORTB |= (1<< 7);
		}
	} else {
		PORTB <<= 1;
		if (temp & (1<<7)){
			PORTB |= 1;
		}
	}
}

// Interrupt Anweisung für Schalter 1
ISR(INT2_vect){
	if (right){
		right = 0;
	} else {
		right = 1;
	}
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

	
	PORTB |= muster;

	sei();	// Interrupts aktivieren

	while(42);
}
