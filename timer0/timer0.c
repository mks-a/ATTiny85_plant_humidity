#include "timer0.h"

void timer0_ov_init(void)
{
	GTCCR = 0x00;
	TCCR0A = 0x00;
	TCCR0B = 0x05;
	
	// Clear pending interrupts
	TIFR |= 0x01;			// Timer / Counter Interrupt flag register
	
	// Set timer/counter
	TCNT0 = 0x00;
	
	TIMSK = 0x02;			// overflow interrupt enable
}