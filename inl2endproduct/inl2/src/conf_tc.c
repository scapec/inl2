/*
 * conf_tc.c
 *
 * Created: 2013-12-10 08:37:41
 *  Author: Tommy
 */ 

#include <asf.h>
#include "conf_tc.h"

void configure_tc_audio(void)
{
	uint32_t ul_sysclk = sysclk_get_cpu_hz();
	uint32_t ul_div, ul_tcclks;
	/* Configure PMC */
	pmc_enable_periph_clk(ID_TC0);
	tc_find_mck_divisor(SAMPLE_FREQ, ul_sysclk, &ul_div, &ul_tcclks, ul_sysclk);
	/** Configure TC for a 10 kHz frequency and trigger on RC compare. */
	tc_init(TC0, 0, (0 | TC_CMR_CPCTRG));
	tc_write_rc(TC0, 0, (ul_sysclk / ul_div) / SAMPLE_FREQ);
	/* Configure and enable interrupt on RC compare */
	NVIC_EnableIRQ((IRQn_Type) ID_TC0);
	tc_enable_interrupt(TC0, 0, TC_IER_CPCS);
	tc_start(TC0, 0);
}


void configure_tc_buttons(void)
{
	
		/* Configure interrupts for shield buttons */
		/*----------------------------------------------------------------*/

		/* Configure power management of timer clock 1 */
		
	pmc_enable_periph_clk(ID_TC3);
	tc_init(TC1, 0, 0);
	tc_set_block_mode(TC1, 0);
	tc_stop(TC1, 0);
}

// to generate my delay
void delay(uint32_t us)
{
	tc_start(TC1, 0);
	while (tc_read_cv(TC1, 0) < (us * 42)); // delay in microseconds
	tc_stop(TC1, 0);
}