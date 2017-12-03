/*
============================================================================
Name		: main.h
Author		: Mateusz Kaczmarczyk
Version		: Pure voltage conversion and frequency measurnment at ICP1 PIN
				with display result at LCD HD44780
Description : Analog Digital converter
============================================================================
*/
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include "adc.h"
#include "lcd.h"
#include "frequencyMeter.h"
#include "generator.h"

int main(void) {
	LCD_Initalize();
	adcInit();
#if 0
	generatorInit();
#endif

#if 0
	freqMeasureInit();
#endif
	sei();

	TVOLT volt;
	char LCD_buffer[16];

	while(1) {
		volt = voltAdc(adcOversample(0x03, 3));
		LCD_Clear();
//TODO: choose better solution
		//sprintf(LCD_buffer, " %s.%sV", volt.intPart, volt.fractPart);
		sprintf(LCD_buffer, " %s.%sV", volt.beforeComa, volt.afterComa);
		LCD_WriteText(LCDbuffer);

		sprintf(LCD_buffer, " %dV", volt.adcVoltRaw);
		LCD_GoTo(0,1);
		LCD_WriteText(LCDbuffer);

#if 0
		uint32_t frequency = measureFreq();
		if(frequency) {
		sprintf(LCDbuffer, " %ldHz", frequency);
		LCD_GoTo(0, 1);
		LCD_WriteText(LCDbuffer);
		}
#endif
		_delay_ms(1000);
	}
}