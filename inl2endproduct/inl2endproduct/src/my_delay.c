/*
 * Delay.c
 *
 *   Modified by Matko Scapec & Osama Fayad
 *  Created: 2013-11-25
 */ 

#include "my_delay.h"


void delay_init(void)
{
	pmc_enable_periph_clk(ID_TC6);
	tc_init(TC1,0,0); /*ID_TC3, TC1, channel 0, TCLK3 och capturemode */
	tc_set_block_mode(TC2,0);
	tc_stop(TC2,0);                /* Making sure the timer is not running */              
}

/* delay */
void delay(uint32_t us)
/* A Delay of us microseconds */
{
 	tc_start(TC2,0);
 	while (tc_read_cv(TC2,0) < us*42);        /* TIMER_CLOCK1 runs on MCK/2 */
 	tc_stop(TC2,0);
}