/*
 * main_io.c
 *
 * Created: 2013-11-13 10:57:41
 *  Author: ac0011
 */ 

#include "main_io.h"

void PIOB_init(int PinNumber) /**< Configures the PB port on the Due board */
{
/*
 * Nothing in this function needs to be changed in lab 1a 
 *
 * Note that all these register controls will not be needed in Laboration 1a
 * but are included for future use
 */

/* 
 * setting up the memory addresses of the digital I/O B-port 
 * which does not depend if the B-port is used as an input or output
 * Most of these variables will not be used
 */
//register_ctrl *const p_PIOB_BASE = (register_ctrl *) 0x400E1000U;	/*base address for PIO registers */
//register_ctrl *const p_PIOB_ABSR = (register_ctrl *) (0x400E1070U);
register_ctrl *const p_PIOB_PER = (register_ctrl *) (0x400E1000U);	/* defines the address for enabling the parallel Input/output B register */
//register_ctrl *const p_PIOB_PSR = (register_ctrl *) (0x400E1008U);	/* defines the address for status of the parallel Input/output B register */
register_ctrl *const p_PIOB_OER = (register_ctrl *) 0x400E1010U;	/* defines the address for enabling the parallel output B register */
//register_ctrl *const p_PIOB_OSR = (register_ctrl *) 0x400E1018U;	/* defines the address for status of the parallel output B register */
//register_ctrl *const p_PIOB_ODR = (register_ctrl *) 0x400E1014U;	/* defines the address for output disable of the parallel output B register */
//register_ctrl *const p_PIOB_MDER = (register_ctrl *) 0x400E1050U;	/*   */
//register_ctrl *const p_PIOB_MDDR = (register_ctrl *) 0x400E1054U;	/*   */
register_ctrl *const p_PIOB_OWER = (register_ctrl *) 0x400E10A0U;	/*   */
//register_ctrl *const p_PIOB_OWDR = (register_ctrl *) 0x400E10A4U;	/*   */

/* 
 * configuring the relevant pin on the B-port as outputs, 
 * e.g. pin 27 which is the built-in LED on an Arduino Due board
 * for other pins see http://arduino.cc/en/Hacking/PinMappingSAM3X 
 */
 
PIOB_PER = pin(PinNumber);		/* Enables pin on PIOB */
PIOB_OER = pin(PinNumber);		/* Enables pins for output */
PIOB_OWER = pin(PinNumber);	/* Enables pins for output */

}	/* end of PIO_init() */

register_data pin(int n) /**< Sets bit n to 1 */
/*
 * A simple, but maybe not so efficient, way to create a single 1 at a
 * particular place in a long word
 *
 * Note that the first bit in an I/O port is bit 0, not bit 1
 */
{
return (1 << (n));	
}	/* end of pin() */

