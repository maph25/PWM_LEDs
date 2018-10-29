/*
 * Sequence.c
 *
 *  Created on: Oct 14, 2018
 *      Author: Andrea Perez
 */
#include "Sequence.h"
#include "DataTypeDefinitions.h"
#include "LCD_nokia.h"
#include "PWM.h"
#include "GPIO.h"
#include "Delay.h"

/*Variable declaration*/
uint16_t sequence[9];
uint16_t element;
sint16 colorLED;
uint8_t DataAvailable;
uint16_t Seq_val;
uint8_t state;
uint32 statusFlag;
static uint8_t B0; /*port c pin 5*/
static uint8_t B1; /*port c pin 7*/
static uint8_t B2; /*port c pin 0*/
static uint16_t B3; /*port c pin 9*/
/*static uint16_t B4; *port c pin 8
static uint8_t B5; port c pin 3
static uint8_t B6; port c pin 2*/
static uint8_t SW2;


uint32 SEQ_get_element(void)
{
	return GPIO_read_port(GPIO_C);
}

uint32 SEQ_decode (uint32 reading){
	uint32_t port_value;
		port_value = GPIOC->PDIR;
		/*Value decoded was SW2*/
		if(port_value == SW2_MASK)
		{
			SW2 = SW2_MASK;
			return SW2;
		}
		/*Value decoded was B0*/
		else if(port_value == B0_MASK)
			{
				B0 = B0_MASK;
				return B0;
			}
		/*Value decoded was B1*/
		else if(port_value == B1_MASK)
			{
				B1 = B1_MASK;
				return B1;
			}
		/*Value decoded was B2*/
		else if(port_value == B2_MASK)
			{
				B2 = B2_MASK;
				return B2;
			}
		/*Value decoded was B3*/
		else if(port_value == B3_MASK)
			{
				B3 = B3_MASK;
				return B3;
			}
		/*else if(port_value == B4_MASK )
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
			}*/
		/*None of the above was selected*/
		else
			return 0xFF; /*Change magic number, only for checking*/
}

void SEQ_execute(void){
	/*Checks that the 10 elements in the sequence haven't been selected*/
	for(state = 0; state > SEQ_MAX; state ++){
		if(state > SEQ_MAX){
			state = SEQ_INIT;
		}
		else{
			/*Gets interruption*/
			DataAvailable = GPIO_get_flag_c();
			state = SEQ_INIT;
			switch(state){
			/*Gets first element in sequence*/
				case SEQ_INIT:
					if(DataAvailable == TRUE)
					{
						element = SEQ_get_element();
						sequence[0] = SEQ_decode(element);
						/*Action for red button*/
						if(sequence[0] == SEQ_RED){
							LCD_nokia_goto_xy(5,5);
							LCD_nokia_send_char('R'); /*It prints a character*/
						}
						/*Action for green button*/
						else if(sequence[0] == SEQ_GREEN){
							LCD_nokia_goto_xy(5,5);
							LCD_nokia_send_char('G'); /*It prints a character*/
						}
						/*Action for blue button*/
						else if(sequence[0] == SEQ_BLUE){
							LCD_nokia_goto_xy(5,5);
							LCD_nokia_send_char('B'); /*It prints a character*/
						}
						state = SEQ_TWO;
					}
			/*Gets second element in sequence*/
				case SEQ_TWO:
					if(DataAvailable == TRUE)
					{
						element = SEQ_get_element();
						sequence[1] = SEQ_decode(element);
						/*Action for red button*/
						if(sequence[1] == SEQ_RED){
							LCD_nokia_send_char('R'); /*It prints a character*/
							LCD_nokia_goto_xy(10,5);
						}
						/*Action for green button*/
						else if(sequence[1] == SEQ_GREEN){
							LCD_nokia_send_char('G'); /*It prints a character*/
							LCD_nokia_goto_xy(10,5);
						}
						/*Action for blue button*/
						else if(sequence[1] == SEQ_BLUE){
							LCD_nokia_send_char('B'); /*It prints a character*/
							LCD_nokia_goto_xy(10,5);
						}
						state = SEQ_THREE;
					}
			/*Gets third element in sequence*/
				case SEQ_THREE:
					if(DataAvailable == TRUE)
					{
						element = SEQ_get_element();
						sequence[2] = SEQ_decode(element);
						/*Action for red button*/
						if(sequence[2] == SEQ_RED){
							LCD_nokia_send_char('R'); /*It prints a character*/
							LCD_nokia_goto_xy(15,5);
						}
						/*Action for green button*/
						else if(sequence[2] == SEQ_GREEN){
							LCD_nokia_send_char('G'); /*It prints a character*/
							LCD_nokia_goto_xy(15,5);
						}
						/*Action for blue button*/
						else if(sequence[2] == SEQ_BLUE){
							LCD_nokia_send_char('B'); /*It prints a character*/
							LCD_nokia_goto_xy(15,5);
						}
						state = SEQ_FOUR;
					}
			/*Gets fourth element in sequence*/
				case SEQ_FOUR:
					if(DataAvailable == TRUE)
					{
						element = SEQ_get_element();
						sequence[3] = SEQ_decode(element);
						/*Action for red button*/
						if(sequence[3] == SEQ_RED){
							LCD_nokia_send_char('R'); /*It prints a character*/
							LCD_nokia_goto_xy(20,5);
						}
						/*Action for green button*/
						else if(sequence[3] == SEQ_GREEN){
							LCD_nokia_send_char('G'); /*It prints a character*/
							LCD_nokia_goto_xy(20,5);
						}
						/*Action for blue button*/
						else if(sequence[3] == SEQ_BLUE){
							LCD_nokia_send_char('B'); /*It prints a character*/
							LCD_nokia_goto_xy(20,5);
						}
						state = SEQ_FIVE;
					}
			/*Gets fifth element in sequence*/
				case SEQ_FIVE:
					if(DataAvailable == TRUE)
					{
						element = SEQ_get_element();
						sequence[4] = SEQ_decode(element);
						/*Action for red button*/
						if(sequence[4] == SEQ_RED){
							LCD_nokia_send_char('R'); /*It prints a character*/
							LCD_nokia_goto_xy(25,5);
						}
						/*Action for green button*/
						else if(sequence[4] == SEQ_GREEN){
							LCD_nokia_send_char('G'); /*It prints a character*/
							LCD_nokia_goto_xy(25,5);
						}
						/*Action for blue button*/
						else if(sequence[4] == SEQ_BLUE){
							LCD_nokia_send_char('B'); /*It prints a character*/
							LCD_nokia_goto_xy(25,5);
						}
						state = SEQ_SIX;
					}
			/*Gets sixth element in sequence*/
				case SEQ_SIX:
					if(DataAvailable == TRUE)
					{
						element = SEQ_get_element();
						sequence[5] = SEQ_decode(element);
						/*Action for red button*/
						if(sequence[5] == SEQ_RED){
							LCD_nokia_send_char('R'); /*It prints a character*/
							LCD_nokia_goto_xy(30,5);
						}
						/*Action for green button*/
						else if(sequence[5] == SEQ_GREEN){
							LCD_nokia_send_char('G'); /*It prints a character*/
							LCD_nokia_goto_xy(30,5);
						}
						/*Action for blue button*/
						else if(sequence[5] == SEQ_BLUE){
							LCD_nokia_goto_xy(30,5);
							LCD_nokia_send_char('B'); /*It prints a character*/
						}
						state = SEQ_SEVEN;
					}
			/*Gets seventh element in sequence*/
				case SEQ_SEVEN:
					if(DataAvailable == TRUE)
					{
						element = SEQ_get_element();
						sequence[6] = SEQ_decode(element);
						/*Action for red button*/
						if(sequence[6] == SEQ_RED){
							LCD_nokia_send_char('R'); /*It prints a character*/
							LCD_nokia_goto_xy(35,5);
						}
						/*Action for green button*/
						else if(sequence[6] == SEQ_GREEN){
							LCD_nokia_send_char('G'); /*It prints a character*/
							LCD_nokia_goto_xy(35,5);
						}
						/*Action for blue button*/
						else if(sequence[6] == SEQ_BLUE){
							LCD_nokia_send_char('B'); /*It prints a character*/
							LCD_nokia_goto_xy(35,5);
						}
						state = SEQ_EIGHT;
					}
			/*Gets eighth element in sequence*/
				case SEQ_EIGHT:
					if(DataAvailable == TRUE)
					{
						element = SEQ_get_element();
						sequence[7] = SEQ_decode(element);
						/*Action for red button*/
						if(sequence[7] == SEQ_RED){
							LCD_nokia_goto_xy(40,5);
							LCD_nokia_send_char('R'); /*It prints a character*/
						}
						/*Action for green button*/
						else if(sequence[7]== SEQ_GREEN){
							LCD_nokia_goto_xy(40,5);
							LCD_nokia_send_char('G'); /*It prints a character*/
						}
						/*Action for blue button*/
						else if(sequence[7] == SEQ_BLUE){
							LCD_nokia_goto_xy(40,5);
							LCD_nokia_send_char('B'); /*It prints a character*/
						}
						state = SEQ_NINE;
					}
			/*Gets ninth element in sequence*/
				case SEQ_NINE:
					if(DataAvailable == TRUE)
					{
						element = SEQ_get_element();
						sequence[8] = SEQ_decode(element);
						/*Action for red button*/
						if(sequence[8] == SEQ_RED){
							LCD_nokia_send_char('R'); /*It prints a character*/
							LCD_nokia_goto_xy(45,5);
						}
						/*Action for green button*/
						else if(sequence[8] == SEQ_GREEN){
							LCD_nokia_goto_xy(45,5);
							LCD_nokia_send_char('G'); /*It prints a character*/
						}
						/*Action for blue button*/
						else if(sequence[8] == SEQ_BLUE){
							LCD_nokia_goto_xy(45,5);
							LCD_nokia_send_char('B'); /*It prints a character*/
						}
						state = SEQ_MAX;
					}
			/*Gets tenth element in sequence*/
				case SEQ_MAX:
					if(DataAvailable == TRUE)
					{
						element = SEQ_get_element();
						sequence[9] = SEQ_decode(element);
						/*Action for red button*/
						if(sequence[9] == SEQ_RED){
							LCD_nokia_goto_xy(50,5);
							LCD_nokia_send_char('R'); /*It prints a character*/
						}
						/*Action for green button*/
						else if(sequence[9] == SEQ_GREEN){
							LCD_nokia_goto_xy(50,5);
							LCD_nokia_send_char('G'); /*It prints a character*/
						}
						/*Action for blue button*/
						else if(sequence[9] == SEQ_BLUE){
							LCD_nokia_goto_xy(50,5);
							LCD_nokia_send_char('B'); /*It prints a character*/
						}
						break;
					}
			}

		}/*Else*/
	}
	/*Sequence execution*/
	statusFlag = GPIO_get_flag_c();
	if(TRUE == statusFlag){
		statusFlag = SEQ_decode(SEQ_get_element());
		if(SW2_MASK == statusFlag){
			for(state = 0; state > SEQ_MAX; state ++){
				if(state > SEQ_MAX){
					state = SEQ_INIT;
				}
				else{
					switch(state){
					case SEQ_INIT:
					{
						if(sequence[0] == SEQ_RED){
							PWM_channel_value(SEQ_RGB_ON,SEQ_RGB_OFF,SEQ_RGB_OFF);
							delay(20000);
							state = SEQ_TWO;
						}
						else if(sequence[0] == SEQ_GREEN){
							PWM_channel_value(SEQ_RGB_OFF,SEQ_RGB_ON,SEQ_RGB_OFF);
							delay(20000);
							state = SEQ_TWO;
						}
						else if(sequence[0] == SEQ_BLUE){
							PWM_channel_value(SEQ_RGB_OFF,SEQ_RGB_OFF,SEQ_RGB_ON);
							delay(20000);
							state = SEQ_TWO;
						}
					}
					case SEQ_TWO:
					{
						if(sequence[0] == SEQ_RED){
							PWM_channel_value(SEQ_RGB_ON,SEQ_RGB_OFF,SEQ_RGB_OFF);
							delay(20000);
							state = SEQ_THREE;
						}
						else if(sequence[0] == SEQ_GREEN){
							PWM_channel_value(SEQ_RGB_OFF,SEQ_RGB_ON,SEQ_RGB_OFF);
							delay(20000);
							state = SEQ_THREE;
						}
						else if(sequence[0] == SEQ_BLUE){
							PWM_channel_value(SEQ_RGB_OFF,SEQ_RGB_OFF,SEQ_RGB_ON);
							delay(20000);
							state = SEQ_THREE;
						}
					}
					case SEQ_THREE:
					{
						if(sequence[0] == SEQ_RED){
							PWM_channel_value(SEQ_RGB_ON,SEQ_RGB_OFF,SEQ_RGB_OFF);
							delay(20000);
							state = SEQ_FOUR;
						}
						else if(sequence[0] == SEQ_GREEN){
							PWM_channel_value(SEQ_RGB_OFF,SEQ_RGB_ON,SEQ_RGB_OFF);
							delay(20000);
							state = SEQ_FOUR;
						}
						else if(sequence[0] == SEQ_BLUE){
							PWM_channel_value(SEQ_RGB_OFF,SEQ_RGB_OFF,SEQ_RGB_ON);
							delay(20000);
							state = SEQ_FOUR;
						}
					}
					case SEQ_FOUR:
					{
						if(sequence[0] == SEQ_RED){
							PWM_channel_value(SEQ_RGB_ON,SEQ_RGB_OFF,SEQ_RGB_OFF);
							delay(20000);
							state = SEQ_FIVE;
						}
						else if(sequence[0] == SEQ_GREEN){
							PWM_channel_value(SEQ_RGB_OFF,SEQ_RGB_ON,SEQ_RGB_OFF);
							delay(20000);
							state = SEQ_FIVE;
						}
						else if(sequence[0] == SEQ_BLUE){
							PWM_channel_value(SEQ_RGB_OFF,SEQ_RGB_OFF,SEQ_RGB_ON);
							delay(20000);
							state = SEQ_FIVE;
						}
					}
					case SEQ_FIVE:
					{
						if(sequence[0] == SEQ_RED){
							PWM_channel_value(SEQ_RGB_ON,SEQ_RGB_OFF,SEQ_RGB_OFF);
							delay(20000);
							state = SEQ_SIX;
						}
						else if(sequence[0] == SEQ_GREEN){
							PWM_channel_value(SEQ_RGB_OFF,SEQ_RGB_ON,SEQ_RGB_OFF);
							delay(20000);
							state = SEQ_SIX;
						}
						else if(sequence[0] == SEQ_BLUE){
							PWM_channel_value(SEQ_RGB_OFF,SEQ_RGB_OFF,SEQ_RGB_ON);
							delay(20000);
							state = SEQ_SIX;
						}
					}
					case SEQ_SIX:
					{
						if(sequence[0] == SEQ_RED){
							PWM_channel_value(SEQ_RGB_ON,SEQ_RGB_OFF,SEQ_RGB_OFF);
							delay(20000);
							state = SEQ_SEVEN;
						}
						else if(sequence[0] == SEQ_GREEN){
							PWM_channel_value(SEQ_RGB_OFF,SEQ_RGB_ON,SEQ_RGB_OFF);
							delay(20000);
							state = SEQ_SEVEN;
						}
						else if(sequence[0] == SEQ_BLUE){
							PWM_channel_value(SEQ_RGB_OFF,SEQ_RGB_OFF,SEQ_RGB_ON);
							delay(20000);
							state = SEQ_SEVEN;
						}
					}
					case SEQ_SEVEN:
					{
						if(sequence[0] == SEQ_RED){
							PWM_channel_value(SEQ_RGB_ON,SEQ_RGB_OFF,SEQ_RGB_OFF);
							delay(20000);
							state = SEQ_EIGHT;
						}
						else if(sequence[0] == SEQ_GREEN){
							PWM_channel_value(SEQ_RGB_OFF,SEQ_RGB_ON,SEQ_RGB_OFF);
							delay(20000);
							state = SEQ_EIGHT;
						}
						else if(sequence[0] == SEQ_BLUE){
							PWM_channel_value(SEQ_RGB_OFF,SEQ_RGB_OFF,SEQ_RGB_ON);
							delay(20000);
							state = SEQ_EIGHT;
						}
					}
					case SEQ_EIGHT:
					{
						if(sequence[0] == SEQ_RED){
							PWM_channel_value(SEQ_RGB_ON,SEQ_RGB_OFF,SEQ_RGB_OFF);
							delay(20000);
							state = SEQ_NINE;
						}
						else if(sequence[0] == SEQ_GREEN){
							PWM_channel_value(SEQ_RGB_OFF,SEQ_RGB_ON,SEQ_RGB_OFF);
							delay(20000);
							state = SEQ_NINE;
						}
						else if(sequence[0] == SEQ_BLUE){
							PWM_channel_value(SEQ_RGB_OFF,SEQ_RGB_OFF,SEQ_RGB_ON);
							delay(20000);
							state = SEQ_NINE;
						}
					}
					case SEQ_NINE:
					{
						if(sequence[0] == SEQ_RED){
							PWM_channel_value(SEQ_RGB_ON,SEQ_RGB_OFF,SEQ_RGB_OFF);
							delay(20000);
							state = SEQ_MAX;
						}
						else if(sequence[0] == SEQ_GREEN){
							PWM_channel_value(SEQ_RGB_OFF,SEQ_RGB_ON,SEQ_RGB_OFF);
							delay(20000);
							state = SEQ_MAX;
						}
						else if(sequence[0] == SEQ_BLUE){
							PWM_channel_value(SEQ_RGB_OFF,SEQ_RGB_OFF,SEQ_RGB_ON);
							delay(20000);
							state = SEQ_MAX;
						}
					}
					case SEQ_MAX:
					{
						if(sequence[0] == SEQ_RED){
							PWM_channel_value(SEQ_RGB_ON,SEQ_RGB_OFF,SEQ_RGB_OFF);
							delay(20000);
						}
						else if(sequence[0] == SEQ_GREEN){
							PWM_channel_value(SEQ_RGB_OFF,SEQ_RGB_ON,SEQ_RGB_OFF);
							delay(20000);
						}
						else if(sequence[0] == SEQ_BLUE){
							PWM_channel_value(SEQ_RGB_OFF,SEQ_RGB_OFF,SEQ_RGB_ON);
							delay(20000);
						}
						break;
					}
				}/*Switch*/
			}
		}/*For*/
	}
}/*SW2*/
}

