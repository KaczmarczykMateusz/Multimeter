/*
 ============================================================================
 Name        : clock.h
 Author      : Mateusz Kaczmarczyk
 Version     : Atmel AVR Atmega8
			   External quartz 16MHz
 Description :
 ============================================================================
 */
#ifndef CLOCK_H
#define CLOCK_H

#include <avr/io.h>
#include <avr/interrupt.h>

//@brief: Definitions for timer0
#define TIMER0_ENABLE					TCCR0 |= (1 << CS00) | (1 << CS02)	//Start Timer0 with clk/1024 prescaler
#define TIMER0_OVF_INTERRUPT_ENABLE		TIMSK |= (1 << TOIE0);				//Enable overflow interrupt

//@brief: Count delay
volatile uint16_t delayCount;

/**
 * @brief:	Initialise Clock0 to count time for free running delays in loop
 * @param:	None
 * @return:
 */
void delayInit(void);

#endif
