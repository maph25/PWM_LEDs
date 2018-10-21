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

uint16_t sequence[9];
uint8_t element;
sint16 colorLED;
uint8_t DataAvailable;
uint16_t Seq_val;
uint8_t state;
uint32 statusFlag;
static uint8_t B0; /*port c pin 5*/
static uint8_t B1; /*port c pin 7*/
static uint8_t B2; /*port c pin 0*/
static uint8_t B3; /*port c pin 9*/
static uint8_t B4; /*port c pin 8*/
static uint8_t B5; /*port c pin 3*/
static uint8_t B6; /*port c pin 2*/
static uint8_t SW2;


uint32 SEQ_get_element(void)
{
	return GPIO_read_port(GPIO_C);
}

uint32 SEQ_decode (uint32 reading){
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

void SEQ_save_seq(void){
	LCD_nokia_goto_xy(25,2);
	for(state = 0; state > SEQ_MAX; state ++){
		if(state > SEQ_MAX){
			state = SEQ_INIT;
		}
		else{
			DataAvailable = GPIO_get_flag_c();
			state = SEQ_INIT;
			switch(state){
				case SEQ_INIT:
					if(DataAvailable == TRUE)
					{
						element = SEQ_get_element();
						sequence[0] = SEQ_decode(element);
						if(sequence[0] == SEQ_RED)
							LCD_nokia_send_char('R'); /*It prints a character*/
						else if(sequence[0] == SEQ_GREEN)
							LCD_nokia_send_char('G'); /*It prints a character*/
						else if(sequence[0] == SEQ_BLUE)
							LCD_nokia_send_char('B'); /*It prints a character*/
						state = SEQ_TWO;
					}
				case SEQ_TWO:
					if(DataAvailable == TRUE)
					{
						element = SEQ_get_element();
						sequence[1] = SEQ_decode(element);
						if(sequence[1] == SEQ_RED)
							LCD_nokia_send_char('R'); /*It prints a character*/
						else if(sequence[1] == SEQ_GREEN)
							LCD_nokia_send_char('G'); /*It prints a character*/
						else if(sequence[1] == SEQ_BLUE)
							LCD_nokia_send_char('B'); /*It prints a character*/
						state = SEQ_THREE;
						}
				case SEQ_THREE:
					if(DataAvailable == TRUE)
					{
						element = SEQ_get_element();
						sequence[2] = SEQ_decode(element);
						if(sequence[2] == SEQ_RED)
							LCD_nokia_send_char('R'); /*It prints a character*/
						else if(sequence[2] == SEQ_GREEN)
							LCD_nokia_send_char('G'); /*It prints a character*/
						else if(sequence[2] == SEQ_BLUE)
							LCD_nokia_send_char('B'); /*It prints a character*/
						state = SEQ_FOUR;
					}
				case SEQ_FOUR:
					if(DataAvailable == TRUE)
					{
						element = SEQ_get_element();
						sequence[3] = SEQ_decode(element);
						if(sequence[3] == SEQ_RED)
							LCD_nokia_send_char('R'); /*It prints a character*/
						else if(sequence[3] == SEQ_GREEN)
							LCD_nokia_send_char('G'); /*It prints a character*/
						else if(sequence[3] == SEQ_BLUE)
							LCD_nokia_send_char('B'); /*It prints a character*/
						state = SEQ_FIVE;
					}
				case SEQ_FIVE:
					if(DataAvailable == TRUE)
					{
						element = SEQ_get_element();
						sequence[4] = SEQ_decode(element);
						if(sequence[4] == SEQ_RED)
							LCD_nokia_send_char('R'); /*It prints a character*/
						else if(sequence[4] == SEQ_GREEN)
							LCD_nokia_send_char('G'); /*It prints a character*/
						else if(sequence[4] == SEQ_BLUE)
							LCD_nokia_send_char('B'); /*It prints a character*/
						state = SEQ_SIX;
					}
				case SEQ_SIX:
					if(DataAvailable == TRUE)
					{
						element = SEQ_get_element();
						sequence[5] = SEQ_decode(element);
						if(sequence[5] == SEQ_RED)
							LCD_nokia_send_char('R'); /*It prints a character*/
						else if(sequence[5] == SEQ_GREEN)
							LCD_nokia_send_char('G'); /*It prints a character*/
						else if(sequence[5] == SEQ_BLUE)
							LCD_nokia_send_char('B'); /*It prints a character*/
						state = SEQ_SEVEN;
					}
				case SEQ_SEVEN:
					if(DataAvailable == TRUE)
					{
						element = SEQ_get_element();
						sequence[6] = SEQ_decode(element);
						if(sequence[6] == SEQ_RED)
							LCD_nokia_send_char('R'); /*It prints a character*/
						else if(sequence[6] == SEQ_GREEN)
							LCD_nokia_send_char('G'); /*It prints a character*/
						else if(sequence[6] == SEQ_BLUE)
							LCD_nokia_send_char('B'); /*It prints a character*/
						state = SEQ_EIGHT;
					}
				case SEQ_EIGHT:
					if(DataAvailable == TRUE)
					{
						element = SEQ_get_element();
						sequence[7] = SEQ_decode(element);
						if(sequence[7] == SEQ_RED)
							LCD_nokia_send_char('R'); /*It prints a character*/
						else if(sequence[7]== SEQ_GREEN)
							LCD_nokia_send_char('G'); /*It prints a character*/
						else if(sequence[7] == SEQ_BLUE)
							LCD_nokia_send_char('B'); /*It prints a character*/
						state = SEQ_NINE;
					}
				case SEQ_NINE:
					if(DataAvailable == TRUE)
					{
						element = SEQ_get_element();
						sequence[8] = SEQ_decode(element);
						if(sequence[8] == SEQ_RED)
							LCD_nokia_send_char('R'); /*It prints a character*/
						else if(sequence[8] == SEQ_GREEN)
							LCD_nokia_send_char('G'); /*It prints a character*/
						else if(sequence[8] == SEQ_BLUE)
							LCD_nokia_send_char('B'); /*It prints a character*/
						state = SEQ_MAX;
					}
				case SEQ_MAX:
					if(DataAvailable == TRUE)
					{
						element = SEQ_get_element();
						sequence[9] = SEQ_decode(element);
						if(sequence[9] == SEQ_RED)
							LCD_nokia_send_char('R'); /*It prints a character*/
						else if(sequence[9] == SEQ_GREEN)
							LCD_nokia_send_char('G'); /*It prints a character*/
						else if(sequence[9] == SEQ_BLUE)
							LCD_nokia_send_char('B'); /*It prints a character*/
						break;
					}
			}

		}/*Else*/
	}
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
						if(sequence[0] == SEQ_RED)
							RGB_init(255,0,0);
						else if(sequence[0] == SEQ_GREEN)
							RGB_init(0,255,0);
						else if(sequence[0] == SEQ_BLUE)
							RGB_init(0,0,255);
						state = SEQ_TWO;
					}
					case SEQ_TWO:
					{
						if(sequence[1] == SEQ_RED)
							RGB_init(255,0,0);
						else if(sequence[1] == SEQ_GREEN)
							RGB_init(0,255,0);
						else if(sequence[1] == SEQ_BLUE)
							RGB_init(0,0,255);
						state = SEQ_THREE;
					}
					case SEQ_THREE:
					{
						if(sequence[2] == SEQ_RED)
							RGB_init(255,0,0);
						else if(sequence[2] == SEQ_GREEN)
							RGB_init(0,255,0);
						else if(sequence[2] == SEQ_BLUE)
							RGB_init(0,0,255);
						state = SEQ_FOUR;
					}
					case SEQ_FOUR:
					{
						if(sequence[3] == SEQ_RED)
							RGB_init(255,0,0);
						else if(sequence[3] == SEQ_GREEN)
							RGB_init(0,255,0);
						else if(sequence[3] == SEQ_BLUE)
							RGB_init(0,0,255);
						state = SEQ_FIVE;
					}
					case SEQ_FIVE:
					{
						if(sequence[4] == SEQ_RED)
							RGB_init(255,0,0);
						else if(sequence[4] == SEQ_GREEN)
							RGB_init(0,255,0);
						else if(sequence[4] == SEQ_BLUE)
							RGB_init(0,0,255);
						state = SEQ_SIX;
					}
					case SEQ_SIX:
					{
						if(sequence[5] == SEQ_RED)
							RGB_init(255,0,0);
						else if(sequence[5] == SEQ_GREEN)
							RGB_init(0,255,0);
						else if(sequence[5] == SEQ_BLUE)
							RGB_init(0,0,255);
						state = SEQ_SEVEN;
					}
					case SEQ_SEVEN:
					{
						if(sequence[6] == SEQ_RED)
							RGB_init(255,0,0);
						else if(sequence[6] == SEQ_GREEN)
							RGB_init(0,255,0);
						else if(sequence[6] == SEQ_BLUE)
							RGB_init(0,0,255);
						state = SEQ_EIGHT;
					}
					case SEQ_EIGHT:
					{
						if(sequence[7] == SEQ_RED)
							RGB_init(255,0,0);
						else if(sequence[7] == SEQ_GREEN)
							RGB_init(0,255,0);
						else if(sequence[7] == SEQ_BLUE)
							RGB_init(0,0,255);
						state = SEQ_NINE;
					}
					case SEQ_NINE:
					{
						if(sequence[8] == SEQ_RED)
							RGB_init(255,0,0);
						else if(sequence[8] == SEQ_GREEN)
							RGB_init(0,255,0);
						else if(sequence[8] == SEQ_BLUE)
							RGB_init(0,0,255);
						state = SEQ_MAX;
					}
					case SEQ_MAX:
					{
						if(sequence[9] == SEQ_RED)
							RGB_init(255,0,0);
						else if(sequence[9] == SEQ_GREEN)
							RGB_init(0,255,0);
						else if(sequence[9] == SEQ_BLUE)
							RGB_init(0,0,255);
						break;
					}
				}/*Switch*/
			}
		}/*For*/
	}
}/*SW2*/
}

