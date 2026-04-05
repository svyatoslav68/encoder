#include <avr/io.h>
#include <avr/interrupt.h>

#include "display.h"
#include "encoder.h"
#include "timer0.h"

extern uint8_t flags;
volatile uint8_t number_repeat_timer0 = 0;

ISR(TIMER0_COMP_vect) {
	if (++number_repeat_timer0 == NUMBER_REPEAT_DISPLAY){
		number_repeat_timer0 = 0;
		flags |= (1 << FLAG_DISPLAY);		
	}
	flags |= 1 << FLAG_TIMER;
}

void start_timer0(){
	TCNT0 = 0x00;
	OCR0 = VALUE_OCR0;
	TCCR0 = (1 << WGM01);
	TIFR = (1 << OCF0);
	TIMSK = (1 << TIMER_INTERRUPT_FLAG);
	TCCR0 |= CLOCK_SELECT_BITS_TIMER0;
}

void stop_timer0(){
	TCCR0 &= ~(CLOCK_SELECT_BITS_TIMER0);
}
