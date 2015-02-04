/*
 * 
 *
 * Created: 2014-03-28 15:48:04
 * Author: Matko Scapec & Osama Fayad & Ali Rama */ 
#include <asf.h>
#include "sampel.h"
volatile extern uint32_t delay_time; 
volatile extern int strength;

/**
 *  Interrupt handler for TC0 interrupt.
 */
void TC0_Handler(void)
{
	volatile uint32_t ul_dummy;
	uint32_t adc_in, outvalue;
	/* Clear status bit to acknowledge interrupt */
	ul_dummy = tc_get_status(TC0, 0);
	/* Avoid compiler warning */
	UNUSED(ul_dummy);
	//starta ADC
	adc_start(ADC);
	//Wait until DRDY get high
	while((adc_get_status(ADC) & 0x01000000)==0);  
	//input value
	adc_in=adc_get_channel_value(ADC, ADC_CHANNEL_10);		
	//for storing my signal levels
	static uint16_t buffer[delay_max]={0};
	//index in-buffer
	static uint32_t i=0;
	//to generate my level of delay

	
buffer[i] = (adc_in+((strength/10)*buffer[i])/100);
	i++;
	
	
	if (i >= (delay_time*10))
		i=0;
	outvalue = (adc_in + buffer[i]);
	
	
	// from digital - analog. This is what I hear. It sends the outvalue to conversion
	dacc_write_conversion_data(DACC,outvalue);	
	
}
void TC3_Handler(void)
{
	volatile uint32_t ul_dummy;

	/* Clear status bit to acknowledge interrupt */
	ul_dummy = tc_get_status(TC1, 0);

	/* Avoid compiler warning */
	UNUSED(ul_dummy);
	
	adc_start(ADC);
	while((adc_get_status(ADC) & 0x01000000)==0);  //Wait until DRDY get high
	
	// result implies the voltage level so we can identify which button is pressed (see LCDShield.c)
	uint32_t result = adc_get_channel_value(ADC, ADC_CHANNEL_7);



// to check buttons and trigger input	
	// for right button
	if (result < 50 ) 	{
		//set to max 300 according to instructions delay time = 300
		if (delay_time >= 300 )
		{
			delay_time = 300;
		}
		else
		{
			// buttons are increasing/decreasing value by 5
			delay_time += 5;
		}
		
	}
	// for up button
	else if (result < 700 ) 
		{
		if (strength == 100)
		{
			strength = 100;
			
		}
		else
		{
			// buttons are increasing/decreasing value by 5
			strength +=5;
		}
		
	}
	// for down button
	else if (result < 1500 ) 
	{
		if (strength == 0)
		{
			strength = 0;
		}
		else
		{
			// buttons are increasing/decreasing value by 5
			strength -=5;
		}
		
	}
	// for left button
	else if (result < 1900 )
	{
		if (delay_time == 0 )
		{
			delay_time = 0;
		}
		else
		{
			// buttons are increasing/decreasing value by 5
			delay_time -= 5;
		}
	}
}