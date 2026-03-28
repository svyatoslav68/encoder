/*
 * encoder.c
 *
 * Created: 28.03.2026 23:49:22
 * Author : Святослав
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer0.h"
#include "display.h"
#include "encoder.h"

/* Глобальная переменная, в которой будут устанавливаться и проверяться флаги */
volatile uint8_t flags = 0x00;

void init() {
}

int main(void)
{
    init();
    init_encoder();
    start_timer0();
    while (1){
	    if (flags & (1 << FLAG_TIMER)){
		    flags &= ~(1 << FLAG_TIMER);
	    }
	    if (flags & (1 << FLAG_DISPLAY)){
		    flags &= ~(1 << FLAG_DISPLAY);
		    display_number();
	    }
    }
}

