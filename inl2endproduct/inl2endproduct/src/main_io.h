/*
 * main_io.h
 *
 * Created: 2013-11-13 10:57:22
 *  Author: ac0011
 */ 


#ifndef MAIN_IO_H_
#define MAIN_IO_H_

#include <inttypes.h>	/* See http://en.wikipedia.org/wiki/C_data_types#Fixed-width_integer_types for more info */

typedef uint32_t register_ctrl;	/* ARM Cortex-M3 is a 32 bit processor, typedef based on C99 standard */
typedef uint32_t register_data;

/*
* The following #defines allows for nicer programming of the PIOB I/O-port
* not requiring explicit pointers in main() or any other functions
*
* Note that most of these I/O controls will not be needed in Laboration 1a!
*/

#define PIOB_PER (*p_PIOB_PER)
#define PIOB_PSR (*p_PIOB_PSR)
#define PIOB_OER (*p_PIOB_OER)
#define PIOB_ODR (*p_PIOB_ODR)
#define PIOB_SODR (*p_PIOB_SODR)
#define PIOB_CODR (*p_PIOB_CODR)
#define PIOB_MDER (*p_PIOB_MDER)
#define PIOB_MDDR (*p_PIOB_MDDR)
#define PIOB_OWER (*p_PIOB_OWER)
#define PIOB_OWDR (*p_PIOB_OWDR)
#define PIOB_ODSR (*p_PIOB_ODSR)
#define PIOB_ABSR (*p_PIOB_ABSR)

void PIOB_init(int);	/* declaration of function that initiates the B I/O-port */

register_data pin(int); /* declaration of a support function that sets a specific bit, e.g. pin, to 1 */
/* cut the declarations to here */




#endif /* MAIN_IO_H_ */