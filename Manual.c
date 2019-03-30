/*
 * Manual.h
 *
 *  Created on: Mar 25, 2019
 *      Author: Andy
 */

#include "Manual.h"

/*Variables for modifying channel value*/
uint16_t red_manual = MANUAL_START_VALUE;
uint16_t green_manual = MANUAL_START_VALUE;
uint16_t blue_manual = MANUAL_START_VALUE;

void Manual_ch_manualange_value()
{
	uint8_t flag;
	uint32_t option;
	flag = GPIO_get_interrupt_status(BUTTONS_PORT);

	if(TRUE == flag)
	{
		option = Buttons_decode();
		switch(option)
		{
			case B1_MASK:
			{
				if(blue_manual >= MANUAL_MAX_OUTPUT)
					blue_manual = MANUAL_MAX_OUTPUT;
				else
					blue_manual = blue_manual + MANUAL_OUTPUT;
			}
			break;
			case B2_MASK:
			{
				if(blue_manual <= MANUAL_MIN_OUTPUT)
					blue_manual = MANUAL_MIN_OUTPUT;
				else
					blue_manual = blue_manual - MANUAL_OUTPUT;
			}
			break;
			case B3_MASK:
			{
				if(red_manual >= MANUAL_MAX_OUTPUT)
					red_manual = MANUAL_MAX_OUTPUT;
				else
					red_manual = red_manual + MANUAL_OUTPUT;
			}
			break;
			case B4_MASK:
			{
				if(red_manual <= MANUAL_MIN_OUTPUT)
					red_manual = MANUAL_MIN_OUTPUT;
				else
					red_manual = red_manual - MANUAL_OUTPUT;
			}
			break;
			case B5_MASK:
			{
				if(green_manual >= MANUAL_MAX_OUTPUT)
					green_manual = MANUAL_MAX_OUTPUT;
				else
					green_manual = green_manual - MANUAL_OUTPUT;
			}
			break;
			case B6_MASK:
			{
				if(green_manual <= MANUAL_MIN_OUTPUT)
					green_manual = MANUAL_MIN_OUTPUT;
				else
					green_manual = green_manual - MANUAL_OUTPUT;
			}
			break;
		}/*Switch*/
		PWM_channel_value(red_manual, green_manual, blue_manual);
	}/*If*/

}

void Manual_full()
{
	uint8_t flagA;
	uint8_t flagC;

	flagA = GPIO_get_interrupt_status(BUTTONS_SW3_PORT);
	flagC = GPIO_get_interrupt_status(BUTTONS_PORT);

	if(TRUE == flagA)
	{
		Manual_change_value();
	}
	if((TRUE == flagC) & (SW2_MASK == Buttons_decode()))
	{
		red_manual = MANUAL_START_VALUE;
		green_manual = MANUAL_START_VALUE;
		blue_manual = MANUAL_START_VALUE;
		PWM_channel_value(red_manual, green_manual, blue_manual);
	}
}
