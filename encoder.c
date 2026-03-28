#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "display.h"
#include "timer0.h"
#include "encoder.h"

void init_encoder(){
	DDR_ENCODER &= ~(1 << ENCODER_CHANNEL_A) | (1 << ENCODER_CHANNEL_B);
	PORT_ENCODER |= (1 << ENCODER_CHANNEL_A) | (1 << ENCODER_CHANNEL_B);
}


