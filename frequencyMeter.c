/*
 ============================================================================
 Name        : frequencyMeter.c
 Author      : Mateusz Kaczmarczyk
 Version     : Atmel AVR Atmega8
			   External quartz 16MHz
 Description :
 ============================================================================
 */
#include "frequencyMeter.h"



/*************************************************************************
 Function:	Overflow interrupt from Timer1()
 Purpose:
 **************************************************************************/
ISR(TIMER1_OVF_vect) {
	ovfCount++;
}

/*************************************************************************
 Function:	Input capture interrupt from Timer1()
 Purpose:
 **************************************************************************/
ISR(TIMER1_CAPT_vect) {
	freqCount++;
}

/*************************************************************************
 Function:	freqMeasureInit()
 Purpose:	Initialise timer1 for frequency measurement without prescaler
 **************************************************************************/
void freqMeasureInit(void) {
	TIMSK |= (1<<TICIE1);			// Enable Input Capture Interrupts
	TCNT1 = 0;						// Clear timer1 counter
	ICR1 = 0;						// Clear timer1 Input Capture Register
	TCCR1B = (1<<ICES1) | (1<<CS00);//Choose source of interrupt (ICP1) rising edge without prescaler, Start timer
}

/*************************************************************************
 Function:	measureFreq()
 Purpose:
 Returns: 0: In progress or error
 	 	  1:
 	 	  Any other: Frequency as Hz
 **************************************************************************/
uint32_t measureFreq(void) {
	if(ovfCount >= 244) {	//16Mhz clock without prescaler - timer1 will overflow 244.140625 times per second
		//Count number of pulses per second:
		uint64_t freqRes = (freqCount * 99940875) * 0.00000001f; //Number of pulses * part of second when it occurred (0.99940875)
		freqCount = 0;
		ovfCount = 0;
		return (uint32_t)freqRes;
	}
	return 0;
}