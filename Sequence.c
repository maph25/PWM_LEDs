/*
 * Sequence.c
 *
 *  Created on: Oct 14, 2018
 *      Author: Andrea Perez
 */
#include "Sequence.h"
#include "DataTypeDefinitions.h"
#include "LCD_nokia.h"
#include "GPIO.h"

uint16_t sequence[9];
uint8_t element;
uint8_t DataAvailable;
uint16_t Seq_val;
uint8_t state;

uint32 SEQ_get_element(void)
{
	return GPIO_read_port(GPIO_C);
}

uint32 SEQ_decode (uint32 reading){
	Seq_val = reading;
	Seq_val &= (B_MASK);
switch (Seq_val){
    case SEQ_RED:
    	/*Key value return*/
    	return SEQ_RED;
        break;
    case SEQ_GREEN:
    	/*Key value return*/
    	return SEQ_GREEN;
        break;
    case SEQ_BLUE:
    	/*Key value return*/
    	return SEQ_BLUE;
        break;
    default:
    	break;
	}
	return 0;
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

}
