/*
 * PCF8574.c
 *
 *  Created on: Apr 16, 2023
 *      Author: christian
 */


#include "PCF8574.h"


extern I2C_HandleTypeDef hi2c1;

uint8_t dpFunction;
uint8_t dpControl;
uint8_t dpMode;
uint8_t dpRows;
uint8_t dpBacklight;

static void SendCommand(uint8_t);
static void SendChar(uint8_t);
static void Send(uint8_t, uint8_t);
static void Write4Bits(uint8_t);
static void ExpanderWrite(uint8_t);
static void PulseEnable(uint8_t);



void lcd_Init(uint8_t rows) {
  dpRows = rows;

  dpBacklight = LCD_BACKLIGHT;
  dpFunction = LCD_4BITMODE | LCD_5x8DOTS | LCD_1LINE;
  dpControl = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
  dpMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

	if (dpRows > 1)    {
		dpFunction |= LCD_2LINE;
	} else {
		dpFunction |= LCD_5x10DOTS;
	}

  /* Wait for initialization */
  HAL_Delay(50);

  ExpanderWrite(dpBacklight);	//Solo enciendo el backlight
  HAL_Delay(1000);

  /* 4bit Mode */
  Write4Bits(0x03 << 4);		//[0100] -> Function Set = [4 Bits]
  HAL_Delay(5);

  Write4Bits(0x03 << 4);		//[0100] -> Function Set = [4 Bits]
  HAL_Delay(5);

  Write4Bits(0x03 << 4);		//[0100] -> Function Set = [4 Bits]
  HAL_Delay(5);

  Write4Bits(0x02 << 4);		//[0010] -> Function Set = [1 Linea] [5x10 Dots]
  HAL_Delay(1);

  /* Display Control */
  SendCommand(LCD_FUNCTIONSET | dpFunction);
  lcd_Display();
  lcd_Clear();

  /* Display Mode */
  SendCommand(LCD_ENTRYMODESET | dpMode);
  HAL_Delay(5);


  lcd_Home();
}




void lcd_Clear(){
  SendCommand(LCD_CLEARDISPLAY);
  HAL_Delay(2);
}

void lcd_Home(){
  SendCommand(LCD_RETURNHOME);
  HAL_Delay(2);
}



void lcd_NoDisplay(){
  dpControl &= ~LCD_DISPLAYON;
  SendCommand(LCD_DISPLAYCONTROL | dpControl);
}

void lcd_Display(){
  dpControl |= LCD_DISPLAYON;
  SendCommand(LCD_DISPLAYCONTROL | dpControl);
}



void lcd_SetCursor(uint8_t col, uint8_t row) {
  int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
  if (row >= dpRows) {
    row = dpRows-1;
  }
  SendCommand(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}



void lcd_NoCursor(){
  dpControl &= ~LCD_CURSORON;
  SendCommand(LCD_DISPLAYCONTROL | dpControl);
}

void lcd_Cursor(){
  dpControl |= LCD_CURSORON;
  SendCommand(LCD_DISPLAYCONTROL | dpControl);
}

void lcd_NoBlink(){
  dpControl &= ~LCD_BLINKON;
  SendCommand(LCD_DISPLAYCONTROL | dpControl);
}

void lcd_Blink(){
  dpControl |= LCD_BLINKON;
  SendCommand(LCD_DISPLAYCONTROL | dpControl);
}




void lcd_PrintStr(const char c[]){
  while(*c) SendChar(*c++);
}



void lcd_NoBacklight(void){
  dpBacklight=LCD_NOBACKLIGHT;
  ExpanderWrite(0);
}

void lcd_Backlight(void){
  dpBacklight=LCD_BACKLIGHT;
  ExpanderWrite(0);
}




static void SendCommand(uint8_t cmd){
  Send(cmd, 0);
}

static void SendChar(uint8_t ch){
  Send(ch, BIT_RS);
}



/*
 * Envio un Byte utilizando paquetes de 4 bits
 * Si mode=0, 		entonces RS=0 -> 	Operaciones como: Clear, Return, Function set, etc
 * Si mode=BIT_RS, 	entonces RS=1 ->	Operaciones de escritura de texto
 */
static void Send(uint8_t value, uint8_t mode){
  uint8_t highnib = value & 0xF0;			//[XXXX 0000]  Guardo los 4 bits mas altos
  uint8_t lownib = (value<<4) & 0xF0;		//[0000 XXXX] -> [XXXX 0000]  Guardo los 4 bits mas bajos
  Write4Bits((highnib)|mode);
  Write4Bits((lownib)|mode);
}




/*
 * Escribo 4 Bits, los envio por I2C junto al bit actual del BackLight
 * Luego realizo el pulso en el pin Enable
 */
static void Write4Bits(uint8_t value){
  ExpanderWrite(value);
  PulseEnable(value);
}

/*
 * Agrego en I2C el byte _data y le coloco el bit correspondiente al Backlight
 */
static void ExpanderWrite(uint8_t _data){
  _data = _data | dpBacklight;
  HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDR, (uint8_t*)&_data, 1, 10);
}

/*
 * Realizo un pulso en el pin Enable manteniendo los bits actuales
 */
static void PulseEnable(uint8_t _data){
  ExpanderWrite(_data | BIT_E);
  HAL_Delay(1);

  ExpanderWrite(_data & ~BIT_E);
  HAL_Delay(1);
}



