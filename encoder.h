#ifndef ENCODER_H
#define ENCODER_H

#define DDR_ENCODER DDRB
#define PORT_ENCODER PORTB
#define PIN_ENCODER PINB

#define ENCODER_CHANNEL_A PORTB1
#define ENCODER_CHANNEL_B PORTB2
#define PORT_TEST PORTB0

#define NUMBER_RIGHT_VALUE 3
#define NUMBER_FOR_END_ROTATION 20
void init_encoder();
void reading_encoder();

#endif // ENCODER_H
