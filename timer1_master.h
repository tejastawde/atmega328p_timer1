/*
 * timer1.h
 *
 * Created: 24-04-2020 18:19:39
 * Author : tejas
 */

/*
 Function usage and ranges:
 
 unsigned long timer_initialization_microseconds( unsigned long time_in_microseconds, unsigned long crystal_freq):
 
 Give the time in microseconds in the variable unsigned long time_in_microseconds(maximum value 4194240, accuracy decreases after 32767 by about 3 microseconds)
 and crystal frequency (maximum value 16000000) in variable  unsigned long crystal_freq
 
 unsigned long timer_initialization_milliseconds( unsigned long time_in_milliseconds, unsigned long crystal_freq):
 
 Give the time in milliseconds in the variable unsigned long time_in_milliseconds(maximum value 4194, accuracy decreases after 262 by about 1 microseconds) and
 crystal frequency (maximum value 16000000) in variable  unsigned long crystal_freq
 
 unsigned long timer_initialization_seconds( unsigned long time_in_seconds, unsigned long crystal_freq):
 
 Give the time in milliseconds in the variable unsigned long time_in_milliseconds(maximum value 4) and crystal frequency (maximum value 16000000) in variable
 unsigned long crystal_freq
 
 Important:
 It is the responsibility of the user to implement the ISR(TIMER1_OVF_vect) function and refill the timercounter1 value after the interrupt, the value to be 
 filled is in the timer_counter_val global variable or can be taken as a return value from the three timer initialization functions. You can use this statement 
  "TCNT1 = timer_counter_val;" in ISR(TIMER1_OVF_vect) to get the job done.
 */

#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char prescalar_val;
double timer_counter_val;



unsigned long timer_initialization_microseconds( unsigned long time_in_microseconds, unsigned long crystal_freq)
{
	crystal_freq = crystal_freq/1000000;
	
	if(time_in_microseconds<4095)                 //65536- value 4095     65535
	{
		prescalar_val = 1 << CS10;
		timer_counter_val = time_in_microseconds * (double)crystal_freq;
	}
	else if(time_in_microseconds<32767)           //65536 - value 32767    524280
	{
		prescalar_val = 1 << CS11;
		timer_counter_val = time_in_microseconds * (double)crystal_freq / 8;
	}
	else if(time_in_microseconds<4194240)
	{
		prescalar_val = 1 << (CS11 | CS10);
		timer_counter_val = (double)time_in_microseconds * (double)crystal_freq / 64;
	}
	
	timer_counter_val = (unsigned long)(65536 - timer_counter_val);
	
	timer_initialization();
	
	return timer_counter_val;
}

unsigned long timer_initialization_milliseconds( unsigned long time_in_milliseconds, unsigned long crystal_freq)
{
	crystal_freq = crystal_freq/1000;
	
	if(time_in_milliseconds<5)					//65536- value 4095     65535
	{
		prescalar_val = 1 << CS10;
		timer_counter_val = time_in_milliseconds * (double)crystal_freq;
	}
	else if(time_in_milliseconds<33)				//65536 - value 32767    524280
	{
		prescalar_val = 1 << CS11;
		timer_counter_val = time_in_milliseconds * (double)crystal_freq/8;
	}
	else if(time_in_milliseconds<262)			//65536 - value          4194240   
	{
		prescalar_val = 1 << (CS11 | CS10);
		timer_counter_val = time_in_milliseconds * (double)crystal_freq/64;
	}
	else if(time_in_milliseconds<1048)			//65536 - value        16776960
	{
		prescalar_val = 1 << CS12;
		timer_counter_val = (double)time_in_milliseconds * (double)crystal_freq/256;
	}
	else if(time_in_milliseconds<4194)         //
	{
		prescalar_val = 1 << (CS12 | CS10);
		timer_counter_val = (double)time_in_milliseconds * (double)crystal_freq/1024;
	}
	
	timer_counter_val = (unsigned long)(65536 - timer_counter_val);
	
	timer_initialization();
	
	return timer_counter_val;
}

unsigned long timer_initialization_seconds( unsigned long time_in_seconds, unsigned long crystal_freq)
{
	crystal_freq = crystal_freq;
	
	
	if(time_in_seconds<2)			//65536 - value        16776960
	{
		prescalar_val = 1 << CS12;
		timer_counter_val = (double)time_in_seconds * (double)crystal_freq/256;
	}
	else if(time_in_seconds<5)         //
	{
		prescalar_val = 1 << (CS12 | CS10);
		timer_counter_val = (double)time_in_seconds * (double)crystal_freq/1024;
	}
	
	timer_counter_val = (unsigned long)(65536 - timer_counter_val);
	
	timer_initialization();
	
	return timer_counter_val;
}


void timer_initialization()
{
	unsigned char cSREG, prescalar_val;
	
	// initialize timer1
	cSREG = SREG;             // store SREG valuebg
	cli();                    // disable all interrupts
	TCCR1A = 0;
	TCCR1B = 0;

	TCNT1 = (long)timer_counter_val;            // preload timer 65536-16MHz/256/2Hz
	TCCR1B |= (1 << (CS11 | CS10));    // 256 prescaler
	TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
	SREG = cSREG;             //restore SREG value (I-bit) enable all interrupts
	sei();
}

