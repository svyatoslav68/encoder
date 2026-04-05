#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "display.h"
#include "timer0.h"
#include "encoder.h"

int8_t count_encoder = 0; /* счетчик, который накручен енкодером */
extern int8_t displaying_number;

void init_encoder(){
	DDR_ENCODER &= ~(1 << ENCODER_CHANNEL_A) | (1 << ENCODER_CHANNEL_B);
	DDR_ENCODER |= (1 << PORT_TEST);
	PORT_ENCODER |= (1 << ENCODER_CHANNEL_A) | (1 << ENCODER_CHANNEL_B);
}

void reading_encoder(){
	#define NUMBER_PAIRS_IN_BYTE 4 /* Количество пар бит в байте */
	#define FLAG_IS_CHANGE 7
	static uint8_t flags_encoder = 0x00;
	static uint8_t prev_pair_bits = 0x03;
	static uint8_t equal_repeats = 0;
	static uint8_t encoder_byte = 0x00;
	//static uint8_t number_pairs = 0x00;
	//static int8_t is_change = 0;
	stop_timer0();
	register uint8_t current_pair_bits = 0;
	PORT_ENCODER |= (1 << PORT_TEST);
	current_pair_bits = ((PIN_ENCODER & (1 << ENCODER_CHANNEL_A)) >> ENCODER_CHANNEL_A) | (((PIN_ENCODER & (1 << ENCODER_CHANNEL_B)) >> ENCODER_CHANNEL_B) << 1);
	if (current_pair_bits == prev_pair_bits) {
		++equal_repeats;
		//flags_encoder = (++flags_encoder & 0b01000000)?flags_encoder & (1 << FLAG_IS_CHANGE):
			//flags_encoder&((1 <<FLAG_IS_CHANGE)|(0x07));
	}
	else {
		//is_change = 1;
		flags_encoder |= (1 << FLAG_IS_CHANGE);
		equal_repeats = 0;
		//flags_encoder &= ~0x3F;
	}
	prev_pair_bits = current_pair_bits;
	if ((equal_repeats == NUMBER_RIGHT_VALUE) && (flags_encoder & (1 << FLAG_IS_CHANGE))){
		//is_change = 0;
		flags_encoder &= ~(1 << FLAG_IS_CHANGE);
		//++number_pairs;
		++flags_encoder;
		encoder_byte = (encoder_byte << 2);
		encoder_byte |= current_pair_bits;
		//if (number_pairs == NUMBER_PAIRS_IN_BYTE){
		if ((flags_encoder & 0x07) == NUMBER_PAIRS_IN_BYTE){
			switch (encoder_byte) {
				case 0x4b:
				case 0x2c:
				case 0xb4:
				case 0xc2:
				displaying_number = --displaying_number%100;
				break;
				case 0x1e:
				case 0x78:
				case 0xe1:
				case 0x87:
				displaying_number = ++displaying_number%100;
				break;
				default:
				;
			}
			prev_pair_bits = 0xff;
			equal_repeats = 0;
			//flags_encoder &= ~0x3f;
			encoder_byte = 0x00;
			//number_pairs = 0;
			flags_encoder &= 0b11111000;
		}
	}
	PORT_ENCODER &= ~(1 << PORT_TEST);
	start_timer0();
}

