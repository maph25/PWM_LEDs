/*
 * LCD_Print.h
 *
 *  Created on: Mar 26, 2019
 *      Author: Andrea Perez Huizar, ie698276@iteso.mx
 */

#include "LCD_nokia.h"

#ifndef LCD_PRINT_H_
#define LCD_PRINT_H_

/*Prints menu in screen*/
void LCD_Print_Menu(void);
/*Prints manual module*/
void LCD_Print_Manual(void);
/*Prints ADC module*/
void LCD_Print_ADC(void);
/*Prints ADC sequence letters*/
void LCD_PRINT_ADC_BLUE(void);
void LCD_PRINT_ADC_RED(void);
void LCD_PRINT_ADC_GREEN(void);
void LCD_PRINT_ADC_YELLOW(void);
void LCD_PRINT_ADC_PURPLE(void);
void LCD_PRINT_ADC_WHITE(void);
/*Prints sequence module*/
void LCD_Print_Sequence(void);
/*Prints frequency module*/
void LCD_Print_Frequency(void);

#endif /* LCD_PRINT_H_ */
