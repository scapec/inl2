/*

	
	
	Tommy Andersson 2013-12-10
	Modified by Matko Scapec & Osama Fayad & Ali Rama
	*/
#include <asf.h>
#include "adcdac.h"
#include "LCDShield.h"
#include "my_delay.h"
#include "conf_tc.h"

#include "sampel.h"

volatile uint32_t delay_time = 0; 
volatile int strength = 0;


int main (void)
{
	// initiate the Due
	sysclk_init();
	board_init();
	// initiate the I/O-port
	ioport_init();
	// Initiate the delays & LCD
	delay_init();
	LCDInit();

	// init adc */
	adc_setup();
	dac_setup();
	// initialize interrupt timer for buttons & audio
	configure_tc_buttons();
	configure_tc_audio();
	
	// just so you know :)
	LCDwriteString("Matko & Ali :)");
	delay(7500);

	while (1)
	{
delay (250000);// much needed delay so the strings get cleared. Aesthetically pleasing
LCD_Clear_Display();
	// text that doesn't change plus the updated values	
	lcd_put_cursor(1,0);
	LCDwriteString("Delay : ");
	dispRES(delay_time);
	LCDwriteString("ms");
	lcd_put_cursor(0,0);
	LCDwriteString("Strength: ");
	dispRES(strength);
	LCDwriteString("%");
		

		
	}
}
