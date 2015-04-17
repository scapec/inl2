/*
 * 
 *
 * Created: 2014-03-28 15:48:04
 * Author: Matko Scapec & Osama Fayad & Ali Rama */

#include "sampel.h"


// writing value of delay to LCD
void lcd_update_time(uint8_t pos, uint16_t val, const char *unit)
{
	char value_str[8];
	/* position cursor */
	lcd_write(pos, LOW);
	lcd_put_cursor(0,11);
	delay(40);
	/* create formatted string */
	sprintf(value_str, "%d%s ", val, unit);
	/* write string on the LCD */
	LCDwriteString(value_str);
}
// writing value of strength to LCD
void lcd_update_strength(uint8_t pos, uint16_t val, const char *unit)
{
	char value_str[8];
	/* position cursor */
	lcd_write(pos, LOW);
	lcd_put_cursor(1,11);
	delay(40);
	/* create formatted string */
	sprintf(value_str, "%d%s ", val, unit);
	/* write string on the LCD */
	LCDwriteString(value_str);
}

/**
 *  Interrupt handler for TC0 interrupt.
 */
void TC0_Handler(void)
{
	uint32_t adc_in, outvalue;
	
	
	// storing strength and delay values
	static int16_t delay_time = init_delay;
	static uint8_t strength = init_strength;
	// for storing my signal levels in the buffer
 	static uint16_t buffer[buffer_time_max] = {0};	
 	static uint16_t i = 0;
 		
	/* clear status bit to acknowledge interrupt,
	   by reading TC Status Register - Channel 0 */
	tc_get_status(TC0, 0);

	adc_start(ADC);
	/* wait until DRDY is set (bit 24 in ADC Interrupt Status Register),
	   this checks if converted data is available */
	while ((adc_get_status(ADC) & 0x01000000) == 0);
	adc_in = adc_get_channel_value(ADC, ADC_CHANNEL_SAMPLE);
	adc_start(ADC); /* start A/D conversion for reading buttons */
	
	//to generate my level of delay
	buffer[i] = ((buffer[i] + adc_in) * strength) / 100;
	i++;
	if (i >= delay_time) {
		i = 0;
	}
	outvalue = adc_in + buffer[i];
	// from digital - analog. This is what I hear. It sends the outvalue to conversion
	dacc_write_conversion_data(DACC, outvalue);
	
	/*
	 * removed TC3 handler and applied it directly in this TC
	 */
	if ((i % 200) == 0) {
		adc_in = adc_get_channel_value(ADC, ADC_CHANNEL_BUTTONS);
		if (adc_in < 400) { // increases strength by pressing RIGHT
			if (strength < 100) {
				delay (40);
				strength++;
				display_strength_update(strength);
			}
		} else if (adc_in < 1000) { // increases delay by pressing UP
			if (delay_time < buffer_max_value) {
				delay_time += time_step;
				if (delay_time > buffer_max_value) {
					delay_time = buffer_max_value;
				}
				display_time_update(delay_time);
			}			
		} else if (adc_in < 1500) { // decreases delay by pressing DOWN
			if (delay_time > 0) { 
				delay_time -= time_step;
				if (delay_time < 0) {
					delay_time = 0;
				}
				display_time_update(delay_time);
			}
		} else if (adc_in < 2000) { // decreases strength by pressing LEFT
			if (strength > 0) {
				delay (40);
				strength--;
				display_strength_update(strength);
			}
		}
	}
}