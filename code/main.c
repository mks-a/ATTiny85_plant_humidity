// put LED on PC5
#include <avr/io.h>       	// this is always included in AVR programs
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include "../timer0/timer0.h"

#define F_CPU 16500000UL

volatile uint16_t buffer = 0;

// bit 0 indicates does humidity need to be chacked
//		0 - doesn't need to chack humidity
//		1 - humidity should be checked
// bit 1 indicates state of external led
//		0 - led is off
//		1 - led is on
// other bits are not used
uint8_t mask = 0;	

int main(void) 
{	
	init();
  
	while (1) 
	{
		sleep_enable();
		sleep_cpu();		
		sleep_disable();
		check_humidity();
	}
  
	return(0);          	// should never get here, this is to prevent a compiler warning
}

void init(void)
{	
	DDRB = 0x03;     		// set pin 1 as output, others as input
	
	timer0_ov_init();
	
	sei();
}

void check_humidity(void)
{	
	// if 0 bit of the mask is set
	if((mask & 0x01))
	{		
		// power up humidity sensor
		PORTB |= 0x01;		// set pin0 to high
		_delay_ms(2000);	// 1 sec delay to turn sensor on
		
		// check input from pin2
		if(!(PINB & (1 << 2)))
			set_led_light(0);
		else
			set_led_light(1);
	}
	else
		PORTB &= 0xFE;		// disable power from humidity sensor
	
	mask &= 0xFE;		// clear 0 bit of the mask
	
	sei();
}

void set_led_light(uint8_t set_led)
{
	if(set_led)
	{
		PORTB |= 0x02;
		mask |= 0x02;
	}
	else
	{
		PORTB &= 0xFD;
		mask &= 0xFD;
	}
}

ISR(TIMER0_OVF_vect)
{
	/* this ISR purpose is wake up MCU and indicate of it with LED */
	cli();
	if(!buffer)
		mask |= 0x01;
	
	buffer++;
}

ISR(BADISR_vect) 
{
}