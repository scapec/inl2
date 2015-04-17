/*
 * conf_tc.h
 *
 * Created: 2013-12-10 08:34:37
 *  Author: Tommy
 */ 

#ifndef CONF_TC_H_
#define CONF_TC_H_

#include <asf.h>

#define SAMPLE_FREQ	10000 // in HZ


void configure_tc_audio(void);
void configure_tc_buttons(void);
// to generate delay
void delay(uint32_t);

#endif