/*
 * PCF8574.h
 *
 *  Created on: Apr 16, 2023
 *      Author: christian
 */

#ifndef LIQUIDCRYSTAL_I2C_H_
#define LIQUIDCRYSTAL_I2C_H_

#include "stm32f1xx_hal.h"

/* Device I2C Address */
#define DEVICE_ADDR		(0x3D << 1)		//HAL_I2C_Master_Transmit recibe la direccion I2C desplazado 1 bit a la izquierda




/*
 * Ruteo del Shield con respecto a los datos que
 * se envian por I2C.
 */
#define BIT_RS 	0x01  	//[0000 0001]
#define BIT_RW	0x02	//[0000 0010]
#define BIT_E		0x04	//[0000 0100]
#define BIT_LED 0x08	//[0000 1000]
#define BIT_DB4	0x10	//[0001 0000]
#define BIT_DB5	0x20	//[0010 0000]
#define BIT_DB6	0x40	//[0100 0000]
#define BIT_DB7	0x80	//[1000 0000]


/* Command */
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

/* Entry Mode */
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00


/* Display On/Off */
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

/* Cursor Shift */
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

/* Function Set */
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

/* Backlight */
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00



void lcd_Init(uint8_t rows);
void lcd_Clear();
void lcd_Home();
void lcd_NoDisplay();
void lcd_Display();
void lcd_NoBlink();
void lcd_Blink();
void lcd_NoCursor();
void lcd_Cursor();
void lcd_NoBacklight();
void lcd_Backlight();
void lcd_SetCursor(uint8_t, uint8_t);
void lcd_PrintStr(const char[]);


#endif /* LIQUIDCRYSTAL_I2C_H_ */
