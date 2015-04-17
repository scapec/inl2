#include <asf.h>
#include "adcdac.h"
#include "conf_tc.h"
#include "LCDShield.h"
#include "sampel.h"

int main(void)
{
	
	// intitiate the Due
	sysclk_init();
	board_init();
	// initiate the I/O-port
	ioport_init();
	// init ADC/DAC
	adc_setup();
	dac_setup();
	
	// init interrupt timer for delay
	configure_tc_buttons();	
	
	LCDinit();
	
// just so you know :)

	LCDwriteString("Matko & Ali Rama");
	delay(400);
	lcd_clear();
	
	
 // text that doesn't change plus updated values	
	
	lcd_put_cursor(0,0);
	LCDwriteString("Delay : ");
	display_time_update(init_delay);
	lcd_put_cursor(1,0);
	LCDwriteString("Strength : ");
	display_strength_update(init_strength);

	// interrupt timer for sampling
	configure_tc_audio();
	
	
	while (1);
}

