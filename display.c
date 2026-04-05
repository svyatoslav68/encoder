#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "display.h"

uint8_t EEMEM digits[] = {IND_ZERO, IND_ONE, IND_TWO, IND_THREE, IND_FOUR, IND_FIVE, IND_SIX, IND_SEVEN, IND_EIGHT, IND_NINE, IND_DOT, IND_MINUS};

static uint8_t mask_digits = 0x00;
uint8_t displaying_number = 25; // Отображаемое на индикаторе число

void init_ports_display(){
	// Для отображения цифр используется весь порт
	DIRECT_DISPLAY = 0xFF;
	mask_digits = 0x00;
	for (uint8_t i = 0; i < NUMBER_DISPLAYING_DIGIT; ++i){
		mask_digits |=  (1 << (PORT_DIGIT_0 + i));
	}
	DIRECT_DIGITS |= mask_digits;
}

void display_number(){
	static uint8_t number_digit = 0; // Номер отображаемого разряда
	/* Байт, записываемый в порт для отображения соответствующего числа
	 * Сначала его сбросим, потом запишем то, что нужно */
	//cli();
	uint8_t byte_data = 0x00; 
	number_digit = ++number_digit % 2;
	if (displaying_number > 99){
		byte_data = IND_MINUS;
	}
	else {
		byte_data = eeprom_read_byte(digits + (number_digit)?displaying_number%10:displaying_number/10);
	}
	PORT_DISPLAY = byte_data;	
	PORT_DIGITS &= ~mask_digits;
	PORT_DIGITS |= (1 << (PORT_DIGIT_0 + number_digit));
	//sei();
}
