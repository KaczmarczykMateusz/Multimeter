/*
 ============================================================================
 Name        : adc.c
 Author      : Mateusz Kaczmarczyk
 Version     : Microcontroller : Atmel AVR Atmega8
 Description : See header file
 ============================================================================
 */
#include "adc.h"


/*************************************************************************
 Function: 	adcInit()
 Purpose:	Initialise 10-bit ADC converter
 **************************************************************************/
void adcInit(void) {
	ADC_REF_VOL_500_V;
	ADC_ENABLE;
	ADC_PRESLCALER_128;
}

/*************************************************************************
 Function: 	_adcConvert()
 Purpose:	Single ADC measurement
 Input:		uint8_t: bit value from datasheet
 Returns:	uint16_t: 10-bit ADC result
 **************************************************************************/
uint16_t _adcConvert(uint8_t channel)
{
	DDRC &= ~(channel);	//@Purpose: Set PIN ADC as input (for some case) otherwise it may be omitted

	ADC_CHENNELS_CLEAR;
	ADMUX |= channel;	//@Purpose: Set ADC channel

	ADC_SINGLE_CONVERTION;

	//@Purpose: Wait until conversion finish
	while(ADC_WAIT)
	{}

	return ADC;
}

/*************************************************************************
 Function: 	adcOversample()
 Purpose:	Complex ADC measurement including oversampling
 Input:		uint8_t: bit value from datasheet, uint8_t: how many bits to extend ADC
 Returns:	uint16_t: oversampled result value in n-bit resolution
 **************************************************************************/
uint16_t adcOversample(uint8_t channel, uint8_t extend) {
	uint16_t nyquistFreq = 4;
	for(int i=0; i<extend; i++) {
		nyquistFreq *= 2;
	}

	uint32_t adcSum = 0;
	for(int i=0; i<nyquistFreq; i++) {
		adcSum = adcSum + _adcConvert(channel);
	}
	adcSum = adcSum >> extend; //@Purpose: Decimation

	return (uint16_t)adcSum;
}

/*************************************************************************
 Function: 	voltAdc()
 Purpose:
 Input:		uint16_t oversampled ADC, calibrated TVOLT struct
 Returns:	None, but sets TVOLT values
 **************************************************************************/
void voltAdc(uint16_t adc, TVOLT * voltTmp) {
	uint16_t adcVoltage = (adc * (uint32_t)voltTmp->refLowVolt) / voltTmp->refLowAdc;
	uint16_t adcVoltageTmp = (adc * (uint32_t)voltTmp->refHighVolt) / voltTmp->refHighAdc;
	adcVoltage = (adcVoltage + adcVoltageTmp) / 2;
	voltTmp->adcVoltRaw = adcVoltage;

	voltTmp->intPart = voltTmp->adcVoltRaw * 0.01f; 	//@purpose: Intentionally lose fraction part of digit
	voltTmp->fractPart =  voltTmp->adcVoltRaw - (uint16_t)(voltTmp->intPart * 100);
#if 0
	//XXX: Way below consumes more program memory (as tested 212 bytes more)
	char beforeComa[3];
	char afterComa[3];
	div_t divMod = div(adcVoltage, 100);
	itoa(divMod.quot, voltTmp->beforeComa, 10);
	itoa(divMod.rem, voltTmp->afterComa, 10);

	if(divMod.rem < 10) {
		voltTmp->afterComa[0] = '0';
		voltTmp->afterComa[1] = divMod.rem + '0';	// convert to ASCII
		voltTmp->afterComa[2] = '\0'; 				// add ASCII terminator
	}
#endif
}
