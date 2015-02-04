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
	/* Configure PMC */
	pmc_enable_periph_clk(ID_TC0);

	/** Configure TC for a 10 kHz frequency and trigger on RC compare. */
	tc_init(TC0, 0, 0 | TC_CMR_CPCTRG);			//Timer_clock_1 - MCK/2 - 42 MHz
	tc_write_rc(TC0, 0, 4200);					//4200 corresponds to fs = 10 kHz

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
	pmc_enable_periph_clk(ID_TC3); // ID_TC3 for clock TC1
	/** Configure TC for a 5Hz frequency and trigger on
	RC compare. */


	/** Configure TC for a 5Hz frequency and trigger on RC compare. */
	tc_init(TC1, 0, 0 | TC_CMR_CPCTRG);			//Timer_clock_1 - MCK/2 - 42 MHz
	tc_write_rc(TC1, 0, 8400000);					//8400000 motsvarar sampling av knappar 5 ggr i sek

	/* Configure and enable interrupt on RC compare */
	NVIC_EnableIRQ((IRQn_Type) ID_TC3);
	tc_enable_interrupt(TC1, 0, TC_IER_CPCS);
	tc_start(TC1, 0);
}
