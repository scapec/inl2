//
//  LCDShield.c
//  Code to be used in Lab 1b
//
//  Created by Ulrik on 2013-11-06.
//        Based on code from Tommy
//          Modified by Matko Scapec & Osama Fayad & Ali Rama
//


#include "LCDShield.h"

/*
 * Initializes the display on the LCD shield, returns 1 if everything is OK.
 */
int LCDinit(void)
{	
	/* At power on */
	ioport_set_pin_dir(LCD_RS, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LCD_Enable, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LCD_BACKLIGHT, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LCD_BACKLIGHT, HIGH);
	ioport_set_port_dir(IOPORT_PIOC, LCD_mask_D4_D7, IOPORT_DIR_OUTPUT);

	ioport_set_pin_level(LCD_Enable, LOW);
	
	delay(30000);		/* wait > 15 ms */
	ioport_set_pin_level(LCD_RS, LOW);
	
	/* Function set (interface is 8 bit long) */
	ioport_set_pin_level(LCD_D4, HIGH);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);		/* delay 1 us */
	ioport_set_pin_level(LCD_Enable, LOW);
	
	delay(4100);	/* wait for more than 4,1 ms */
	
	ioport_set_pin_level(LCD_D4, HIGH);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);		/* delay 1 us */
	ioport_set_pin_level(LCD_Enable, LOW);

	delay(100);	/* wait 100 us */
	
	ioport_set_pin_level(LCD_D4, HIGH);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);		/* delay 1 us */
	ioport_set_pin_level(LCD_Enable, LOW);		
	
	delay(100);	/* wait 100 us */
		
	/* Set display to 4-bit input */
	ioport_set_pin_level(LCD_D4, LOW);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delay(1);
	ioport_set_pin_level(LCD_Enable, LOW);
	
	delay(100);

	lcd_write(0b00101000, LOW);		/* Two rows, small font */
	lcd_write(0b00001000, LOW);		/* Display off */
	lcd_clear();					/* Display clear */
	
	delay(3000);
	
	lcd_write(0b00000110, LOW);			/* Entry mode set: move cursor right, no display shift */
	lcd_set_cursor(LCD_NO_CURSOR);		/* Display on + cursor setting */

	/* simple return statement showing that the
	   initialization of the LCD has completed */
	return 1;
}

// clears display and sets cursror to home
int lcd_clear(void)
{
	lcd_write(0x01, LOW);
	delay(1600);	/* delay of 1.6 ms is necessary */
	return 1;
}

// Sets the cursor
int lcd_set_cursor(uint8_t cursor)
{
	lcd_write((0x0C | cursor), LOW);
	return 1;
}

// By pointing to the correct address on the DDRAM of the LCD we can put cursor at
// the column and row that we intend
int lcd_put_cursor(uint8_t row, uint8_t col)
{
	lcd_write((128 | (row << 6) | col), LOW);
	delay(40);	/* delay of 40 microseconds is necessary */
	return 1;
}

uint8_t lcd_write(uint8_t byte, bool type)                /* writes a byte to the LCD display */
/*
 *        writes the byte (8 bits) to the LCD display as two consecutive 4 bits 
 *        type = 0 controls the display
 *        type = 1 writes the content of the byte (usually interpreted as ASCII-code) to the display
 *
 *        LCDwrite returns the actual pinout value on PIOC 26-23, which is the reverse order compared to the Due pin order of D4-D7
 */
{
        /* In it's infinite wisdom the shield has the data pins in mirrored order compared to the Due board */
        uint8_t mirror_pin[16]={0b0000,0b1000,0b0100,0b1100,0b0010,0b1010,0b0110,0b1110,0b0001,0b1001,0b0101,0b1101,0b0011,0b1011,0b0111,0b1111};
        uint32_t byte32;
        uint8_t byte_orig;
        uint8_t mirrored_output = 0;


        byte_orig = byte;


        /* write the first 4 bits to the shield. */
        byte = byte>>4;
        byte = mirror_pin[byte];
        byte32 = (uint32_t)byte << 23;
        mirrored_output = byte<<4;
        
        ioport_set_pin_level(LCD_RS, type); 
        ioport_set_port_level(IOPORT_PIOC, LCD_mask_D4_D7, byte32);
        ioport_set_pin_level(LCD_Enable, HIGH);
        delay(1);
        ioport_set_pin_level(LCD_Enable, LOW);
        
        delay(100);
        
        /* write the second 4 bits to the shield. */
        byte = byte_orig;
        byte = byte & 0x0f;
        byte = mirror_pin[byte];
        byte32 = (uint32_t)byte<<23;
        mirrored_output = mirrored_output + byte;


        ioport_set_port_level(IOPORT_PIOC, LCD_mask_D4_D7, byte32);
        ioport_set_pin_level(LCD_Enable, HIGH);
        delay(1);
        ioport_set_pin_level(LCD_Enable, LOW);
		delay(100);
        
        return mirrored_output;
}


int lcd_write_int(int number)
{
	/* converted string to LCD */
	char digit_str[20]; /* 20 characters is probably excessive? */
	/* convert integer to string */
	sprintf(digit_str, "%d", number);
	/* write string to LCD, return result from execution */
	return LCDwriteString(digit_str);
}

/* displays strings on the LCD display */
int LCDwriteString(const char *str)
{
	// loop until break
	while (*str != '\0') {
		lcd_write(*str, HIGH);
		str++;
	}
	return 1;
}