/*
 * timer_1_testing.c
 *
 * Created: 24-04-2020 18:19:39
 * Author : tejas
 *
 *Sample code that implements timer1_master.h and toggles the most significant bit of port D.
 */ 

#include <avr/io.h>
#include <math.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <timer1_master.h>

ISR(TIMER1_OVF_vect)
{
	TCNT1 = timer_counter_val;            // preload timer 
	PORTD = PORTD ^ 0x80;    //Toggle the most significant bit of port D.
}


int main(void)
{
	timer_initialization_seconds(1, 16000000);
	
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

