/*
 * ADC.h
 *
 * Created: 2013-11-25 16:17:24
 */ 


//	code taken from src in lab1c from Ulrik Eklund.
//	modified by Matko Scapec & Osama Fayad & Ali Rama

#ifndef ADCDAC_H_
#define ADCDAC_H_

#include "asf.h"

int adc_setup(void);
#define ADC_CLOCK 20000000
#define ADC_CHANNEL_BUTTONS ADC_CHANNEL_7	//Analog input 0 (PA16)
#define ADC_CHANNEL_SAMPLE	ADC_CHANNEL_10	//Analog input 8 (PB17)

void led_init(void);

#define DAC_CHANNEL 0	/* channel DAC0 */

/* Initializing D/A conversion */
int dac_setup(void);
#endif /* ADCDAC_H_ */