/*
 ============================================================================
 Name        : frequencyMeter.c
 Author      : Mateusz Kaczmarczyk
 Version     : Atmel AVR Atmega8
			   External quartz 16MHz
 Description : Measure frequency and output it as Hz
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
	ovfCount = 0;
	freqCount = 0;

	TIMER1_INPUT_CAPT_MODE;
	TIMER1_OVERFLOW_MODE;
	TIMER1_RISING_EDGE;
	TIMER1_COUNT_CLR;
	TIMER1_ICP_COUNT_CLR;
	TIMER1_START;
}

/*************************************************************************
 Function:	measureFreq()
 Returns: 	Frequency as Hz
 **************************************************************************/
uint32_t measureFreq(void) {
	static uint32_t freqResTmp = 0;
	if(ovfCount >= 244) {	//16Mhz clock without prescaler - timer1 will overflow 244.140625 times per second
		//Count number of pulses per second:
		//TODO: add (uint16_t)round((freqCount * 99940875) * 0.00000001f);
		//TODO: in case function below is not working try to remove  from accuracy
		uint32_t freqRes = ((uint64_t)freqCount * 99940875) * 0.00000001f; //Number of pulses * part of second when it occurred (0.99940875)
		freqCount = 0;
		ovfCount = 0;
		TIMER1_COUNT_CLR;
		TIMER1_ICP_COUNT_CLR;
		freqResTmp = freqRes;
		return freqRes;
	}
	return freqResTmp;
}
