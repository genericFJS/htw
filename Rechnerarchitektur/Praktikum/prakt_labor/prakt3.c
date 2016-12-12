#include <avr/io.h>
#include <avr/interrupt.h>

int lights[18] = {
0x21,
0x23,
0x24,
0x24,
0x24,
0x24,
0x22,
0x22,
0x21,
0x61,
0x81,
0x81,
0x81,
0x81,
0x41,
0x41,
0x00,	// dunkel
0x42	// gelb-gelb
}; 

int segmen[18] = {
0x00,
0x00,
0x66,
0x4F,
0x5B,
0x06,
0x00,
0x00,
0x00,
0x00,
0x66,
0x4F,
0x5B,
0x06,
0x00,
0x00,
0x00,
0x7F
};

int state = 0;
int reset = 0;
int night = 0;

// Interrupt Anweisung für Timer 1A Compare
ISR(TIMER1_COMPA_vect){
	if(reset){
		PORTC = lights[0];
		PORTA = segmen[0];
		reset = 0;
		state = 0;
	} else if(night){
		if (night == 1){
			PORTC = lights[16];
			PORTA = segmen[16];
			night = 2;
		} else {
			PORTC = lights[17];
			PORTA = segmen[17];
			night = 1;
		}
	} else {
		if(state==16){
			state = 0;
		}
		PORTC = lights[state];
		PORTA = segmen[state];
		state++;
	}
}


// Interrupt Anweisung für Schalter 0 (reset)
ISR(INT0_vect){
	reset = 1;
	night = 0;
}

// Interrupt Anweisung für Schalter 1 (nachtmodus)
ISR(INT1_vect){
	if(night){
		night = 0;
		reset = 1;
	} else {
		night = 1;
		reset = 0;
	}
}

int main (void){

	DDRA = 0xFF;	// A komplett als Ausgabe definieren (Segmentanzeige)
	DDRC = 0xFF;	// C komplett als Ausgabe definieren (Lichter)
	DDRD = 0x00;	// D komplett als Eingang definieren

	// normalisieren (invertieren)
	int i = 18;
	for (int j=0; j<i; j++){
		lights[j] = ~lights[j];
		segmen[j] = ~segmen[j];
	} 
	
	// Timer (interrupt, alle 500ms)
	TCCR1A = 0;
	TCCR1B = (1 << WGM12) | (1 << CS12);
	OCR1AH = 0x07; OCR1AL = 0xA0;
	TIMSK |= (1 << OCIE1A);

	// Tasten-Interrupt konfigurieren (0 reset, 1 switch):
	EICRA |= (1 << ISC11); EICRA &= ~(1 << ISC10);
	EICRA |= (1 << ISC01); EICRA &= ~(1 << ISC00);
	EIMSK = (1 << INT0) | (1 << INT1);

	sei();	// Interrupts aktivieren

	while(42);
}
