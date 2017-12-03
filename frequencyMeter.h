/*
 ============================================================================
 Name        : frequencyMeter.h
 Author      : Mateusz Kaczmarczyk
 Version     : Atmel AVR Atmega8
			   External quartz 16MHz
 Description : Measure frequency and output it as Hz
 	 	 	 	 Needs pull down resistor at measurement PIN
 ============================================================================
 */
#ifndef FREQUENCY_METER_H
#define FREQUENCY_METER_H

#include <avr/io.h>
#include <avr/interrupt.h>

//@brief: Definitions for timer1
#define TIMER1_INPUT_CAPT_MODE	TIMSK |= (1 << TICIE1)		//Enable Input Capture Interrupts
#define TIMER1_OVERFLOW_MODE	TIMSK |= (1 << TOIE1)		//Enable Overflow Interrupts
#define TIMER1_RISING_EDGE		TCCR1B |= (1 << ICES1)		//Choose source of interrupt rising edge
#define TIMER1_COUNT_CLR		TCNT1 = 0					//Clear timer1 counter
#define TIMER1_ICP_COUNT_CLR	ICR1 = 0					//Clear timer1 Input Capture Register
#define TIMER1_START			TCCR1B |= (1 << CS10)		//Start timer1 without prescaler (clk/1)

//@brief: Count timer1 overflows
volatile uint16_t ovfCount;

//@brief: Count detected pulses
volatile uint32_t freqCount;

/**
 * @brief:	Initialise timer1 for frequency measurement without prescaler
 * @param:	None
 * @return:
 */
void freqMeasureInit(void);

/**
 * @brief:	Measure target frequency as Hz
 * @param:	None
 * @return:	Frequency as Hz
 */
uint32_t measureFreq(void);

#endif
