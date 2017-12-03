/*
 ============================================================================
 Name        : adc.h
 Author      : Mateusz Kaczmarczyk
 Version     : Atmega8 May be incompatibile with other Atmega
 Description : Voltage measurement is with +/- 0.05V tolerance
 	 			You can increase range with voltage divider
				Calibration with refLowAdc, refLowVolt
				and refHighAdc, refHighVolt
 ============================================================================
 */
#ifndef ADC_H
#define ADC_H

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//@brief   definition ADCIN (ADC input)
#define ADCIN PA7

#define ADC_REF_VOL_256_V ADMUX  =  (1<<REFS1) | (1<<REFS0) 	//Internal 2.56V Voltage Reference with external capacitor at AREF pin
#define ADC_REF_VOL_500_V ADMUX  =  (1<<REFS0) 				//Internal 5V Voltage Reference with external capacitor at AREF pin

#define ADC_ENABLE			ADCSRA |= (1<<ADEN) 							//ADC Enable
#define ADC_PRESLCALER_128	ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2)	//ADC prescaler clk/128


#define ADC_CHENNELS_CLEAR		ADMUX &= ~0x0F			//Sets turn off all ADC channels
#define ADC_SINGLE_CONVERTION	ADCSRA |= (1<<ADSC);	//Perform single conversion
#define ADC_WAIT				ADCSRA & (1<<ADSC)


//@brief  holding values  for ADC oversampling measurement
typedef struct {
	// @brief   set value in the middle (not precise) of measure range which can be pre-stepped down with voltage divider
	uint16_t refLowAdc;

	// @brief   set value (volt) of ADC which set during measuring of ref_adc (multiply this value *100)
	uint16_t refLowVolt;

	// @brief   set value in the middle (not precise) of measure range which can be pre-stepped down with voltage divider
	uint16_t refHighAdc;

	// @brief   set value (volt) of ADC which set during measuring of ref_adc (multiply this value *100)
	uint16_t refHighVolt;

	// @brief   voltage multiplied by *100
	uint16_t adcVoltRaw;

	// @brief  	digits to print before coma (xx. full volts)
	uint16_t intPart;

	// @brief   digits to print after coma (.xx of volts)
	uint16_t fractPart;
} TVOLT;

/**
 * @brief    Initialise ADC converter with 10 bit (maximum for Atmega32) resolution
 */
void adcInit(void);

/**
 * @brief	Counting voltage from n-bit oversampleed ADC value
 * @param	uint16_t result of adc oversample measurement in n-bit resolution,
 * @param	calibrated TVOLT srtuct holding values for ADC oversampling
 * @return  None, but modifies struct changing adcVoltRaw, beforeComa[] and afterComa[] values
 * @see     adcOversample()
 */
void voltAdc(uint16_t adc, TVOLT * voltTmp);

/**
 * @brief    Single ADC measurement without oversamppling nor averaging
 * @param    uint8_t: ADC channel as bit value set following Atmega datasheet
 * @return   uint16_t: measured value as 10-bit ADC result
 */
uint16_t _adcConvert(uint8_t channel);

/**
 * @brief	 Full ADC measurement including oversampling
 * @param    uint8_t: ADC channel as bit value set following Atmega datasheet
 * @param    uint8_t: how many bits of resolution to add to oversampling
 * @return   uint16_t: oversampled result value in n-bit resolution
 * 			 (n = extend + basic resolution)
 */
uint16_t adcOversample(uint8_t channel, uint8_t extend);

#endif
