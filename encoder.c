#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "display.h"
#include "timer0.h"
#include "encoder.h"

int8_t count_encoder = 0; /* счетчик, который накручен енкодером */

void init_encoder(){
	DDR_ENCODER &= ~(1 << ENCODER_CHANNEL_A) | (1 << ENCODER_CHANNEL_B);
	DDR_ENCODER |= (1 << PORT_TEST);
	PORT_ENCODER |= (1 << ENCODER_CHANNEL_A) | (1 << ENCODER_CHANNEL_B);
}

void reading_encoder(){
	static uint8_t prev_pair_bits = 0x00;
	static uint8_t equal_repeats = 0;
	static uint8_t encoder_byte = 0x00;
	uint8_t current_pair_bits = 0x00;
	PORT_ENCODER |= (1 << PORT_TEST);
	current_pair_bits = ((PIN_ENCODER & (1 << ENCODER_CHANNEL_A)) >> ENCODER_CHANNEL_A) | (((PIN_ENCODER & (1 << ENCODER_CHANNEL_B)) >> ENCODER_CHANNEL_B) << 1);
	if (current_pair_bits == prev_pair_bits) {
		++equal_repeats;
	}
	else {
		equal_repeats = 0;
	}
	prev_pair_bits = current_pair_bits;
	if (equal_repeats == NUMBER_RIGHT_VALUE){
		encoder_byte = (encoder_byte << 2);
		encoder_byte |= current_pair_bits;
	}
	PORT_ENCODER &= ~(1 << PORT_TEST);
}

