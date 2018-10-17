/*
 * Sequence.c
 *
 *  Created on: Oct 14, 2018
 *      Author: Andrea Perez
 */
#include "Sequence.h"
#include "DataTypeDefinitions.h"
#include "GPIO.h"

uint16_t sequence[9];
uint8_t element;
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
	}
}

void SEQ_save_seq(void){

}
