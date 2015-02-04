//
//  LCDShield.h
//  Playing with Unity
//
// Modified by Matko Scapec & Osama Fayad & Ali Rama

#ifndef LCDShield_h
#define LCDShield_h


#define LCD_RS PIO_PC22_IDX
#define LCD_Enable PIO_PC21_IDX


#define LCD_D4 PIO_PC26_IDX
#define LCD_D5 PIO_PC25_IDX
#define LCD_D6 PIO_PC24_IDX
#define LCD_D7 PIO_PC23_IDX


#define LCD_mask_D4_D7 0b00000111100000000000000000000000


/* convert an int_32 to ASCII */
#define INT_TO_ASCII(number) number+0x30


#include <asf.h>

int LCDInit(void);
uint8_t lcd_write(uint8_t, bool);
void ACsetup(void);
int LCD_Clear_Display(void);
int dispRES(int32_t);
int LCDwriteString(const char* str);
int lcd_set_cursor(uint8_t);
int lcd_put_cursor(uint8_t, uint8_t);


#endif

