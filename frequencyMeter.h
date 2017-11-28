/*
 ============================================================================
 Name        : frequencyMeter.h
 Author      : Mateusz Kaczmarczyk
 Version     :
 Description :
 ============================================================================
 */
#ifndef FREQUENCY_METER_H
#define FREQUENCY_METER_H
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t ovfCount;
volatile uint32_t freqCount;

/**
 * @brief:	Initialise timer1 for frequency measurement without prescaler
 * @param:	None
 * @return:
 */
void freqMeasureInit(void);

/**
 * @brief:
 * @param:	None
 * @return:
 */
uint32_t measureFreq(void);

#endif
