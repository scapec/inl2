/*
 * adcdac.c
 *
 * Created: 2013-12-10 08:30:13
 *  Author: Tommy
 *
 * Modified by Matko Scapec & Osama Fayad & Ali Rama
 */ 

#include "adcdac.h"

int adc_setup(void)
{
	
	if (pmc_enable_periph_clk(ID_ADC) == 0) 
	{
		
		adc_init(ADC, sysclk_get_main_hz(), ADC_CLOCK, 0);
		adc_configure_timing(ADC, 0, 0, 0);
		adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);
		adc_enable_channel(ADC, ADC_CHANNEL_BUTTONS);
		adc_enable_channel(ADC, ADC_CHANNEL_SAMPLE);
		adc_configure_trigger(ADC, ADC_TRIG_SW, 0);
		return 1;
	}
	else
	return 0;
}


// added the DAC through ASF & also setup it


int dac_setup(void) {
		/* Enable the specified peripheral clock (ADC clock).
	   If function returns 0, then we can proceed... */
	if (pmc_enable_periph_clk(ID_DACC) == 0) {
		dacc_reset(DACC);
		dacc_set_transfer_mode(DACC, 0);
		dacc_set_timing(DACC, 1, 1, 0);
		/* select and enable ADC channel - specified in 'adc.h' */
		dacc_set_channel_selection(DACC, DAC_CHANNEL);
		dacc_enable_channel(DACC, DAC_CHANNEL);	
		/* indicate everything's OK! */
		return 1;
	}
	else
	/* indicate that something went wrong! */
	return 0;
}