#ifndef TIMER0_H
#define TIMER0_H

#define F_CPU 7372800
#define TIMER_INTERRUPT_FLAG OCIE0
#define  DELAY_TIMER_MS 1UL /* Время задержки, генерируемой таймером в мс */         
#define  DIVIDER_0 256UL   /* Предделитель для таймера-счетчика 0 */
#if DIVIDER_0 == 1024UL
#define CLOCK_SELECT_BITS_TIMER0 0x05
#elif DIVIDER_0 == 256UL
#define CLOCK_SELECT_BITS_TIMER0 0x04
#elif DIVIDER_0 == 64UL
#define CLOCK_SELECT_BITS_TIMER0 0x03
#endif

#define VALUE_OCR0 (F_CPU/(DIVIDER_0*DELAY_TIMER_MS*1000))
#define VALUE_TCNT0 (256UL-F_CPU/(DIVIDER_0*DELAY_TIMER_MS*1000))

#define FLAG_DISPLAY 0
#define FLAG_TIMER   1

void start_timer0();
void stop_timer0();

#endif // TIMER0_H
