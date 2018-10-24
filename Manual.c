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

uint8_t Button;
uint8_t member;
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
				B0 = TRUE;
				return B0;
			}
		else if(port_value == B1_MASK )
			{
				B1 = TRUE;
				return B1;
			}
		else if(port_value == B2_MASK )
			{
				B2 = TRUE;
				return B2;
			}
		else if(port_value == B3_MASK )
			{
				B3 = TRUE;
				return B3;
			}
		else if(port_value == B4_MASK )
			{
				B4 = TRUE;
				return B4;
			}
		else if(port_value == B5_MASK )
			{
				B5 = TRUE;
				return B5;
			}
		else if(port_value == B6_MASK )
			{
				B6 = TRUE;
				return B6;
			}
		else
			return 0xFF; /*Change magic number, only for checking*/
}


/*
void Manual_comp_butt(void){
	LCD_nokia_goto_xy(25,2);
	Data = GPIO_get_flag_c();
	StateButton = ONE;
	if(Data == TRUE){
		member = Manual_get_element();
		Button = Manual_decode(member);
	}

	//switch(StateButton)
	{
		case B0_MASK:
		{

			{
				member = Manual_get_element();
				Button = Manual_decode(member);

			}
		}
		case B1_MASK:
		{
			if(Data == TRUE)
			{
				member = Manual_get_element();
				Button = Manual_decode(member);
			}
		}
		case B2_MASK:
		{
			if(Data == TRUE)
			{
				member = Manual_get_element();
				Button = Manual_decode(member);
			}
		}
		case B3_MASK:
		{
			if(Data == TRUE)
			{
				member = Manual_get_element();
				Button = Manual_decode(member);
			}
		}
		case B4_MASK:
		{
			if(Data == TRUE)
			{
				member = Manual_get_element();
				Button = Manual_decode(member);
			}
		}
		case B5_MASK:
		{
			if(Data == TRUE)
			{
				member = Manual_get_element();
				Button = Manual_decode(member);
			}
		}
		case B6_MASK:
		{
			if(Data == TRUE)
			{
				member = Manual_get_element();
				Button = Manual_decode(member);
			}
		}
	}

}

*/





int Manual(void)
{
	sint16 red=0;
	sint16 green=0;
	sint16 blue=0;
	uint8_t inputValueA;  //SW3
	uint8_t inputValueB0 = 0; //C5
	uint8_t inputValueB1 = 0; //C7
	uint8_t inputValueB2 = 0; //C0
	uint16_t inputValueB3 = 0; //C9
	uint16_t inputValueB4; //C8
	uint8_t inputValueB5 = 0; //C3
	uint8_t inputValueB6 = 0; //C2
	uint8_t inputValueC = 0;  //SW2


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

	/**Configuration function for FlexTimer*/
	//PWM_init( red, green, blue);

	for(;;) {
		/**Reading the input values for port A and C*/
		inputValueA = GPIOA->PDIR;
		inputValueA &=(0x10);
		inputValueA = inputValueA >> 4;  //SW3

		inputValueC = GPIOC->PDIR;
		inputValueC &=(0x40);
		inputValueC = inputValueC >> 6;   //SW2

		inputValueB0 = GPIOC->PDIR;
		inputValueB0 &=(B0_MASK); 			//CAMBIAR VALOR
		inputValueB0 = inputValueB0 >> 5; //B0

		inputValueB1 = GPIOC->PDIR;
		inputValueB1 &=(B1_MASK); 			//CAMBIAR VALOR
		inputValueB1 = inputValueB1 >> 7; //B1

		inputValueB2 = GPIOC->PDIR;
		inputValueB2 &=(B2_MASK); 			//CAMBIAR VALOR
		inputValueB2 = inputValueB2 >> 0; //B2

		inputValueB3 = GPIOC->PDIR;
		inputValueB3 &=(B3_MASK); 			//CAMBIAR VALOR
		inputValueB3 = inputValueB3 >> 9; //B3

		inputValueB4 = GPIOC->PDIR;
		inputValueB4 &=(B4_MASK); 			//CAMBIAR VALOR
		inputValueB4 = inputValueB4 >> 8; //B4

		inputValueB5 = GPIOC->PDIR;
		inputValueB5 &=(B5_MASK); 			//CAMBIAR VALOR
		inputValueB5 = inputValueB5 >> 3; //B5

		inputValueB6 = GPIOC->PDIR;
		inputValueB6 &=(B6_MASK); 			//CAMBIAR VALOR
		inputValueB6 = inputValueB6 >> 2; //B6

		/*
		if(inputValueA ==0)
		{
			dutyCycle = dutyCycle-10;
			FlexTimer_updateCHValue(dutyCycle);
			delay(20000);
		}
		if(inputPortC==0)
		{
			dutyCycle = dutyCycle-10;
			FlexTimer_updateCHValue(dutyCycle);
			delay(20000);
		}*/

		if(inputValueB0==B0_MASK)
		{

		}

		if(BUTTON==B1_MASK)
		{
			red = red-10;
			blue = blue;
			green = green;
			PWM_channel_value(red, green, blue);
			delay(20000);
		}

		if(inputValueB2==B2_MASK)
		{
			red = red+10;
			blue = blue;
			green = green;
			PWM_channel_value(red, green, blue);
			delay(20000);
		}
		if(inputValueB3==B3_MASK)
		{
			red = red;
			blue = blue-10;
			green = green;
			PWM_channel_value(red, green, blue);
			delay(20000);
		}
		if(inputValueB4==B4_MASK)
		{
			red = red;
			blue = blue+10;
			green = green;
			PWM_channel_value(red, green, blue);
			delay(20000);
		}
		if(inputValueB5==B5_MASK)
		{
			red = red;
			blue = blue;
			green = green-10;
			PWM_channel_value(red, green, blue);
			delay(20000);
		}
		if(inputValueB6==B6_MASK)
		{
			red = red;
			blue = blue;
			green = green+10;
			PWM_channel_value(red, green, blue);
			delay(20000);
		}



	}

	return 0;
}
