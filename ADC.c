/*
 * ADC.c
 *
 *  Created on: Oct 23, 2018
 *      Author: Andrea Perez
 */

#include "MK64F12.h"
#include "ADC.h"
#include "DataTypeDefinitions.h"
#include "GPIO.h"
#include "PWM.h"
#include "LCD_nokia.h"

uint16 result;
uint16 adcResult;
uint16 adcTemporal;
sint16 Red;
sint16 Green;
sint16 Blue;
ufloat adcPrint;
ufloat adcPrintStage1; /*Float variable*/
uint16 adcPrintStage2; /*Float variable*/
uint16 adcPrintStage3;
uint16 printCharOne;
uint16 printCharTwo;
uint16 printCharThree;
uint8_t ADCstring1[]="RGB ADC Voltage"; /*! String to be printed in the LCD*/

/*Port C Pin 10: ADC1_SE6b */

gpio_pin_control_register_t Default_function = GPIO_MUX0;

void ADC_init (void){
         SIM->SCGC3 |= SIM_SCGC3_ADC1_MASK;

         ADC1->CFG1 = ADC_CFG1_ADIV(3)|ADC_CFG1_ADLSMP_MASK |ADC_CFG1_MODE(0)|ADC_CFG1_ADICLK(0);
         ADC1->SC3 = ADC_SC3_AVGE_MASK |ADC_SC3_AVGS(3);
         GPIO_pin_control_register(GPIO_C, BIT0, &Default_function);
         for(;;)
         {
                 result = ADC_result();
         }
 }

 uint16 ADC_result(){
		 ADC1->SC1[0]= ADC_SC1_ADCH(6);
         while( 0 == (ADC1->SC1[0] & ADC_SC1_COCO_MASK));
         adcResult = ADC1->R[0];
         return adcResult;
 }

void ADC_decode_print_value(uint16 value){
	 switch(value){
	 case ZERO:{
		 LCD_nokia_send_char('0'); /*! It prints a character*/
		 break;
	 }
	 case ONE:{
		 LCD_nokia_send_char('1'); /*! It prints a character*/
		 break;
	 }
	 case TWO:{
		 LCD_nokia_send_char('2'); /*! It prints a character*/
		 break;
	 }
	 case THREE:{
		 LCD_nokia_send_char('3'); /*! It prints a character*/
		 break;
	 }
	 case FOUR:{
		 LCD_nokia_send_char('4'); /*! It prints a character*/
		 break;
	 }
	 case FIVE:{
		 LCD_nokia_send_char('5'); /*! It prints a character*/
		 break;
	 }
	 case SIX:{
		 LCD_nokia_send_char('6'); /*! It prints a character*/
		 break;
	 }
	 case SEVEN:{
		 LCD_nokia_send_char('7'); /*! It prints a character*/
		 break;
	 }
	 case EIGHT:{
		 LCD_nokia_send_char('8'); /*! It prints a character*/
		 break;
	 }
	 case NINE:{
		 LCD_nokia_send_char('9'); /*! It prints a character*/
		 break;
	 }
	 }
 }

 void ADC_execute(void){
	 adcTemporal = ADC_result();
	 adcPrint = adcTemporal;
	 adcPrintStage1 = (adcPrint * ADC_VOLT_MAX)/ADC_MAX; /*Rule of three*/
	 adcPrintStage2 = adcPrintStage1 * ADC_DIVIDER_ONE; /*Multiply by 100*/
	 printCharOne = adcPrintStage2 / ADC_DIVIDER_TWO; /*Divide by 100, save in integer, gets first value*/
	 adcPrintStage3 = adcPrintStage2 - (printCharOne * ADC_DIVIDER_ONE); /*Substract first char */
	 printCharTwo = adcPrintStage3 / ADC_DIVIDER_TWO;/*Divides by 10 remaining value*/
	 printCharThree = printCharTwo - (printCharTwo * ADC_DIVIDER_TWO); /*Substract second char*/
	 LCD_nokia_goto_xy(25,0); /*! It establishes the position to print the messages in the LCD*/
	 LCD_nokia_send_string(&ADCstring1[0]); /*! It print a string stored in an array*/
	 LCD_nokia_goto_xy(0,10); /*! It establishes the position to print the messages in the LCD*/
	 ADC_decode_print_value(printCharOne);
	 LCD_nokia_goto_xy(8,10); /*! It establishes the position to print the messages in the LCD*/
	 LCD_nokia_send_char('.'); /*! It prints a character*/
	 LCD_nokia_goto_xy(16,10); /*! It establishes the position to print the messages in the LCD*/
	 ADC_decode_print_value(printCharTwo);
	 LCD_nokia_goto_xy(24,10); /*! It establishes the position to print the messages in the LCD*/
	 ADC_decode_print_value(printCharThree);

	 	 if((ADC_NULL < adcTemporal) && (adcTemporal < ADC_RED))
	 	 {
	 		 Red = 255;
	 		 Green = 0;
	 		 Blue = 0;
	 		 PWM_channel_value(Red, Green, Blue);
	 	 }
	 	 else if((ADC_RED < adcTemporal) && (adcTemporal < ADC_BRICK))
	 	 {
	 		 Red = 255;
			 Green = 85;
			 Blue = 0;
			 PWM_channel_value(Red, Green, Blue);
	 	 }
	 	 else if((ADC_BRICK < adcTemporal) && (adcTemporal < ADC_ORANGE))
	 	 {
	 		Red = 255;
			Green = 145;
			Blue = 0;
			PWM_channel_value(Red, Green, Blue);

	 	 }
	 	 else if((ADC_ORANGE < adcTemporal) && (adcTemporal < ADC_YELLOW))
	 	 {
	 		Red = 255;
			Green = 247;
			Blue = 0;
			PWM_channel_value(Red, Green, Blue);

	 	 }
	 	 else if((ADC_YELLOW < adcTemporal) && (adcTemporal < ADC_YELLOW_LIME))
	 	 {
	 		Red = 154;
			Green = 255;
			Blue = 0;
			PWM_channel_value(Red, Green, Blue);

	 	 }
	 	 else if((ADC_YELLOW_LIME < adcTemporal) && (adcTemporal < ADC_GREEN))
	 	 {
	 		Red = 0;
			Green = 255;
			Blue = 0;
			PWM_channel_value(Red, Green, Blue);

	 	 }
	 	 else if((ADC_GREEN < adcTemporal) && (adcTemporal < ADC_GREEN_FOREST))
	 	 {
	 		Red = 64;
			Green = 255;
			Blue = 64;
			PWM_channel_value(Red, Green, Blue);

	 	 }
	 	else if((ADC_GREEN_FOREST < adcTemporal) && (adcTemporal < ADC_AQUAMARINE))
	 	 {
	 		Red = 0;
			Green = 255;
			Blue = 128;
			PWM_channel_value(Red, Green, Blue);
	 	 }
	 	else if((ADC_AQUAMARINE < adcTemporal) && (adcTemporal < ADC_BABY_BLUE))
	 	 {
	 		Red = 0;
			Green = 215;
			Blue = 125;
			PWM_channel_value(Red, Green, Blue);

	 	 }
	 	else if((ADC_BABY_BLUE < adcTemporal) && (adcTemporal < ADC_SKY_BLUE))
	 	 {
	 		Red = 0;
			Green = 215;
			Blue = 175;
			PWM_channel_value(Red, Green, Blue);

	 	 }
	 	 else if((ADC_SKY_BLUE < adcTemporal) && (adcTemporal < ADC_KING_BLUE))
	 	 {
	 		Red = 0;
			Green = 175;
			Blue = 215;
			PWM_channel_value(Red, Green, Blue);

	 	 }
	 	 else if((ADC_KING_BLUE < adcTemporal) && (adcTemporal < ADC_BLUE))
	 	 {
	 		Red = 0;
			Green = 0;
			Blue = 255;
			PWM_channel_value(Red, Green, Blue);

	 	 }
	 	else if((ADC_BLUE < adcTemporal) && (adcTemporal < ADC_LAVENDER))
		 {
	 		Red = 180;
			Green = 0;
			Blue = 180;
			PWM_channel_value(Red, Green, Blue);

	 	 }
		 else if((ADC_LAVENDER < adcTemporal) && (adcTemporal < ADC_PURPLE))
	 	 {
			Red = 255;
			Green = 0;
			Blue = 255;
			PWM_channel_value(Red, Green, Blue);

	 	 }
 }

