# atmega328p_timer1
A timer1 overflow library for Atmega 328P

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
