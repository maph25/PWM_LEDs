/*
 * Delay.c
 *
 *  Created on: 15/10/2018
 *      Author: Fer Muñoz
 */


#include  "Delay.h"

void delay(uint16_t delay)
{
	volatile int counter, counter_2;

		for(counter_2 = 16; counter_2 > 0; counter_2--)
		{
			for(counter = delay; counter > 0; counter--);

		}
}
