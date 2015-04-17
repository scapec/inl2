/*
 * 
 *
 * Created: 2014-03-28 15:49:05
 *  Author: Matko Scapec & Osama Fayad & Ali Rama
 */ 

#ifndef SAMPEL_H_
#define SAMPEL_H_

#include <asf.h>
#include "LCDShield.h"
#include "adcdac.h"

// size of buffer in milliseconds
#define buffer_time_max				5000
// max size of index in buffer
#define buffer_max_value		4999
// threshold of init value for delay
#define delay_strength_value 400

// start values
#define init_delay		0
#define init_strength	0

#define time_step			10

// a way to update value for delay
#define display_time_update(dt)	{								\
	lcd_update_time(0b11000000, ((dt + 1) / 10), "ms");	\
}

// a way to update value for strength
#define display_strength_update(st) {							\
	lcd_update_strength(0b11001111, st, "%");					\
}

// sent values which in turn updates the LCD-display
void lcd_update_time(uint8_t, uint16_t, const char*);
void lcd_update_strength(uint8_t, uint16_t, const char*);
#endif