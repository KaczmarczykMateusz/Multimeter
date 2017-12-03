/*
 ============================================================================
 Name        : generator.c
 Author      : Mateusz Kaczmarczyk
 Version     :
 Description : Microcontroller : Atmel AVR Atmega8 16MHz eternal osc
 	 	 	 	 Needs HD converter for smoothing wave signal into linear
 	 	 	 	 in case if we want to measure it via ADC which was initially
 	 	 	 	 purpose of generator.c
 ============================================================================
 */
#include "generator.h"

/*************************************************************************
Function: motorInit()
Purpose:  Initialize PWM at PIN OC2
**************************************************************************/
void generatorInit(void) {
	GENERATOR_CH_DDR_INIT;
	TIMER2_PWM_NON_INVERTING_MODE;
	TIMER2_FAST_PWM;
	TIMER2_START;
}

/*************************************************************************
Function: generatorSet()
Purpose: Set duty cycle
Input  : 0 - 255 Duty cycle
**************************************************************************/
void generatorSet(uint16_t voltage) {
	OCR2 = voltage * (255 / 500.0f);	//seting duty cycle at PIN OC1A equal to user defined voltage
}
