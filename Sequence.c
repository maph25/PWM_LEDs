/*
 * Sequence.c
 *
 *  Created on: Mar 29, 2019
 *      Author: Andrea Perez Huizar, ie698276@iteso.mx
 */
#include "Sequence.h"

/*Variables for modifying channel value*/
uint16_t red_sequence = SEQUENCE_START_VALUE;
uint16_t green_sequence = SEQUENCE_START_VALUE;
uint16_t blue_sequence = SEQUENCE_START_VALUE;

void Sequence_RGB_off()
{
	red_sequence = SEQUENCE_START_VALUE;
	green_sequence = SEQUENCE_START_VALUE;
	blue_sequence = SEQUENCE_START_VALUE;
	PWM_channel_value(red_sequence, green_sequence, blue_sequence);
}
void Sequence_RGB_blue()
{
	Sequence_RGB_off();
	red_sequence = SEQUENCE_BLUE_R;
	green_sequence = SEQUENCE_BLUE_G;
	blue_sequence = SEQUENCE_BLUE_B;
	PWM_channel_value(red_sequence, green_sequence, blue_sequence);
}
void Sequence_RGB_red()
{
	Sequence_RGB_off();
	red_sequence = SEQUENCE_RED_R;
	green_sequence = SEQUENCE_RED_G;
	blue_sequence = SEQUENCE_RED_B;
	PWM_channel_value(red_sequence, green_sequence, blue_sequence);
}
void Sequence_RGB_green()
{
	Sequence_RGB_off();
	red_sequence = SEQUENCE_GREEN_R;
	green_sequence = SEQUENCE_GREEN_G;
	blue_sequence = SEQUENCE_GREEN_B;
	PWM_channel_value(red_sequence, green_sequence, blue_sequence);
}
void Sequence_RGB_yellow()
{
	Sequence_RGB_off();
	red_sequence = SEQUENCE_YELLOW_R;
	green_sequence = SEQUENCE_YELLOW_G;
	blue_sequence = SEQUENCE_YELLOW_B;
	PWM_channel_value(red_sequence, green_sequence, blue_sequence);
}
void Sequence_RGB_purple()
{
	Sequence_RGB_off();
	red_sequence = SEQUENCE_PURPLE_R;
	green_sequence = SEQUENCE_PURPLE_G;
	blue_sequence = SEQUENCE_PURPLE_B;
	PWM_channel_value(red_sequence, green_sequence, blue_sequence);
}
void Sequence_RGB_white()
{
	Sequence_RGB_off();
	red_sequence = SEQUENCE_WHITE_R;
	green_sequence = SEQUENCE_WHITE_G;
	blue_sequence = SEQUENCE_WHITE_B;
	PWM_channel_value(red_sequence, green_sequence, blue_sequence);
}
