/*
 ============================================================================
 Name        : clock.c
 Author      : Mateusz Kaczmarczyk
 Version     : Atmel AVR Atmega8
			   External quartz 16MHz
 Description : Increment volatile integer in order to count
 	 	 	 	 delays in free running loop
 ============================================================================
 */
#include "clock.h"

/*************************************************************************
Function: delayInit()
Purpose:  Initialise Clock0 to count time for free running delays in loop
**************************************************************************/
void delayInit(void) {
	TIMER0_OVF_INTERRUPT_ENABLE;
    TCNT0 = 0; 			//Initialise Timer0 counter
	TIMER0_ENABLE;
}

/*************************************************************************
Function: TIMER0 overflow interrupt service routine()
Purpose:  Called whenever TCNT0 overflows, so every 16.32ms
			in case if prescaler of 16MHz clock 1024 (16Mhz/1024)
**************************************************************************/
ISR(TIMER0_OVF_vect) {
	delayCount++;
}
