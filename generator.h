/*
 ============================================================================
 Name        : generator.h
 Author      : Mateusz Kaczmarczyk
 Version     : Atmega8! WGM registers vary among uC
 Description :
 ============================================================================
 */
#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>


//@brief: Generator PIN direction
#define GENERATOR_CH_DDR_INIT	DDRB |=	(1 << 3)


//@brief: PWM definitions
#define TIMER2_PWM_NON_INVERTING_MODE	TCCR2 |= (1 << COM21);				//Non inverting PWM at PIN OC1A
#define TIMER2_PWM_INVERTING_MODE		TCCR2 |= (1 << COM21) | (1 << COM20)//Inverting PWM at PIN OC1A

#define TIMER2_FAST_PWM					TCCR2 |= (1 << WGM21) | (1 << WGM20)// Choose fast PWM 8-bit
#define TIMER2_CTC_PWM_8_BIT			TCCR2 |= (1 << WGM21)  				// Choose Clear Timer on Compate (CTC) PWM 8-bit
#define TIMER2_PHASE_CORRECT_PWM_8_BIT	TCCR2 |= (1 << WGM20)  				// Choose Phase correct PWM 8-bit

#define TIMER2_PRESCALE_1					(1 << CS20)						//clk/1 (without) prescaler
#define TIMER2_PRESCALE_8					(1 << CS21)						//clk/8 prescaler
#define TIMER2_PRESCALE_64					(1 << CS22)						//clk/64 prescaler
#define TIMER2_START						TCCR2 |= TIMER2_PRESCALE_1				//Start Timer1 with prescaler clk/8


/**
* @brief:	Initialise PWM generator
* @param:	None
* @return:	None
*/
void generatorInit(void);

/**
* @brief:	Set duty cycle
* @param:	0 - 255 Duty cycle
* @return:	None
*/
void generatorSet(uint16_t voltage);

#endif
