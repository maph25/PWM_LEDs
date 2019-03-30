/*
 * LCD_Print.c
 *
 *  Created on: Mar 26, 2019
 *      Author: Andrea Perez Huizar, ie698276@iteso.mx
 */

#include "LCD_Print.h"

/*Menu print*/
uint8_t option1[] = "1) RGB Manual";
uint8_t option2[] = "2) RGB ADC";
uint8_t option3[] = "3) RGB Sequence";
uint8_t option4[] = "4) RGB Frequency";
/*Manual*/
uint8_t manual[] = "RGB Manual";
/*ADC*/
uint8_t adc[] = "RGB ADC";
/*Sequence*/
uint8_t sequence[] = "RGB Sequence";

/*Frequency*/
uint8_t frequency[] = "RGB Frequency";

void LCD_Print_Menu()
{
	/*Clears screen*/
	LCD_nokia_clear();
	/*It establishes the position to print the messages in the LCD*/
	LCD_nokia_goto_xy(0,5);
	/*It print a string stored in an array*/
	LCD_nokia_send_string(option1);
	/*It establishes the position to print the messages in the LCD*/
	LCD_nokia_goto_xy(0,10);
	/*It print a string stored in an array*/
	LCD_nokia_send_string(option2);
	/*It establishes the position to print the messages in the LCD*/
	LCD_nokia_goto_xy(0,15);
	/*It print a string stored in an array*/
	LCD_nokia_send_string(option3);
	/*It establishes the position to print the messages in the LCD*/
	LCD_nokia_goto_xy(0,20);
	/*It print a string stored in an array*/
	LCD_nokia_send_string(option4);
}

void LCD_Print_Manual()
{
	/*Clears screen*/
	LCD_nokia_clear();
	/*It establishes the position to print the messages in the LCD*/
	LCD_nokia_goto_xy(0,5);
	/*It print a string stored in an array*/
	LCD_nokia_send_string(manual);
}

void LCD_Print_ADC()
{
	/*Clears screen*/
	LCD_nokia_clear();
	/*It establishes the position to print the messages in the LCD*/
	LCD_nokia_goto_xy(0,5);
	/*It print a string stored in an array*/
	LCD_nokia_send_string(adc);
}

void LCD_PRINT_ADC_BLUE()
{
	LCD_nokia_send_char('B');
}

void LCD_PRINT_ADC_RED()
{
	LCD_nokia_send_char('R');
}

void LCD_PRINT_ADC_GREEN()
{
	LCD_nokia_send_char('G');
}

void LCD_PRINT_ADC_YELLOW()
{
	LCD_nokia_send_char('Y');
}

void LCD_PRINT_ADC_PURPLE()
{
	LCD_nokia_send_char('P');
}

void LCD_PRINT_ADC_WHITE()
{
	LCD_nokia_send_char('W');
}

void LCD_Print_Sequence()
{
	/*Clears screen*/
	LCD_nokia_clear();
	/*It establishes the position to print the messages in the LCD*/
	LCD_nokia_goto_xy(0,5);
	/*It print a string stored in an array*/
	LCD_nokia_send_string(sequence);
}

void LCD_Print_Frequency()
{
	/*Clears screen*/
	LCD_nokia_clear();
	/*It establishes the position to print the messages in the LCD*/
	LCD_nokia_goto_xy(0,5);
	/*It print a string stored in an array*/
	LCD_nokia_send_string(frequency);
}
