/*
============================================================================
Name		: main.C
Author		: Mateusz Kaczmarczyk
Version		: Voltage conversion and frequency measurnment at ICP1 PIN
				with display result at LCD HD44780
Description : Voltage measurement is with +/- 0.05V tolerance,
				Frequency measure
				PWM generation controlled with incrementing / decrementing keys
============================================================================
*/
#include <avr/interrupt.h>
#include <avr/io.h>
#include "adc.h"
#include "lcd.h"
#include "frequencyMeter.h"
#include "clock.h"
#include "generator.h"
#include "keyboard.h"

int main(void) {
	char LCDbuffer[16];
	uint8_t dutyCycle = 0;

	LCD_Initalize();
	adcInit();
	freqMeasureInit();
	generatorInit();
	sei();

	TVOLT volt;
	volt.refLowVolt = 207;
	volt.refLowAdc = 1704;
	volt.refHighVolt = 380;
	volt.refHighAdc = 3176;

	TVOLT gen;
	gen.refLowVolt = 207;
	gen.refLowAdc = 1704;
	gen.refHighVolt = 380;
	gen.refHighAdc = 3176;

	delayInit();
	uint16_t ovfCountTmp = delayCount;

	key upKey = keyInit(&DDRC, &PORTC, &PINC, UP_BTN_MASK);
	key dwnKey = keyInit(&DDRC, &PORTC, &PINC, DOWN_BTN_MASK);

	while(1) {
		keyIncrDcr(&upKey, &dwnKey, &dutyCycle, 255);
		generatorSet(dutyCycle);
		if(delayCount >= 2){
			delayCount = 0;
			ovfCountTmp = 0;
			voltAdc(adcOversample(0x03, 3), &volt);
			voltAdc(adcOversample(0x02, 2), &gen);
			LCD_Clear();
			sprintf(LCDbuffer, "%d.%02dV G:%d.%02dV", volt.intPart, volt.fractPart, gen.intPart, gen.fractPart);
			LCD_WriteText(LCDbuffer);

			sprintf(LCDbuffer, "Result: %ldHz", measureFreq());
			LCD_GoTo(0,1);
			LCD_WriteText(LCDbuffer);
#if VOLTAGE_CALIBRATION
			sprintf(LCDbuffer, "ADC: %d", adcOversample(0x03, 3));
			LCD_GoTo(0,1);
			LCD_WriteText(LCDbuffer);
#endif
		}
	}
}
