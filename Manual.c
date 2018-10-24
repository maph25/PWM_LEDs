/*
 * Manual.c
 *
 *  Created on: 23/10/2018
 *      Author: Fer Muñoz
 */


#include "MK64F12.h" /* include peripheral declarations */
#include "GPIO.h"
#include "Manual.h"
#include "NVIC.h"
#include "PWM.h"
#include "Delay.h"
#include "LCD_nokia.h"

uint16_t Button;
uint16_t member;
uint16_t StateButton;
uint8_t Data;
uint32_t statusFlagManual;
static uint8_t B0; /*port c pin 5*/
static uint8_t B1; /*port c pin 7*/
static uint8_t B2; /*port c pin 0*/
static uint16_t B3; /*port c pin 9*/
static uint16_t B4; /*port c pin 8*/
static uint8_t B5; /*port c pin 3*/
static uint8_t B6; /*port c pin 2*/
static uint8_t SW2;

/*inicialización de los botones en el manual*/
uint32_t Manual_get_element(void)
{
	return GPIO_read_port(GPIO_C);
}

/*recibe los botones en el manual*/
uint32_t Manual_decode (uint32_t reading){
	uint32_t port_value;
		port_value = GPIOC->PDIR;

		if(port_value == SW2_MASK)
		{
			SW2 = TRUE;
			return SW2;
		}
		else if(port_value == B0_MASK )
			{
				B0 = B0_MASK;
				return B0;
			}
		else if(port_value == B1_MASK )
			{
				B1 = B1_MASK;
				return B1;
			}
		else if(port_value == B2_MASK )
			{
				B2 = B2_MASK;
				return B2;
			}
		else if(port_value == B3_MASK )
			{
				B3 = B3_MASK;
				return B3;
			}
		else if(port_value == B4_MASK )
			{
				B4 = B4_MASK;
				return B4;
			}
		else if(port_value == B5_MASK )
			{
				B5 = B5_MASK;
				return B5;
			}
		else if(port_value == B6_MASK )
			{
				B6 = B6_MASK;
				return B6;
			}
		else
			return 0xFF; /*Change magic number, only for checking*/
}



int Manual(void)
{
	sint16 red=0;
	sint16 green=0;
	sint16 blue=0;



	LCD_nokia_goto_xy(25,2);
	Data = GPIO_get_flag_c();
	StateButton = ONE;

	if(Data == TRUE){
	member = Manual_get_element();
	Button = Manual_decode(member);

		switch(Button){
			case B1_MASK:
			{
				red = red-10;
				blue = blue;
				green = green;
				if(red<0){
					red = 0;
				}
				PWM_channel_value(red, green, blue);
				delay(20000);
			}
			case B2_MASK:
			{
				red = red+10;
				blue = blue;
				green = green;
				if(red>255){
					red = 255;
				}
				PWM_channel_value(red, green, blue);
				delay(20000);
			}
			case B3_MASK:
			{
				red = red;
				blue = blue-10;
				green = green;
				if(blue<0){
					blue = 0;
				}
				PWM_channel_value(red, green, blue);
				delay(20000);
			}
			case B4_MASK:
			{
				red = red;
				blue = blue+10;
				green = green;
				if(blue>255){
					red = 255;
				}
				PWM_channel_value(red, green, blue);
				delay(20000);
			}
			case B5_MASK:
			{
				red = red;
				blue = blue;
				green = green-10;
				if(green<0){
					green = 0;
				}
				PWM_channel_value(red, green, blue);
				delay(20000);
			}
			case B6_MASK:
			{
				red = red;
				blue = blue;
				green = green+10;
				if(green>255){
					green = 255;
				}
				PWM_channel_value(red, green, blue);
				delay(20000);
			}

			}
		}




	return 0;
}
