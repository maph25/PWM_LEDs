/*
 * Buttons.c
 *
 *  Created on: Mar 25, 2019
 *      Author: Andy
 */
#include "Buttons.h"

void Buttons_init()
{
	/*Clock gating*/
	GPIO_clock_gating(BUTTONS_SW2_PORT);
	GPIO_clock_gating(BUTTONS_SW2_PORT);
	GPIO_clock_gating(BUTTONS_B0_PORT);
	GPIO_clock_gating(BUTTONS_PORT);
	/*Pin control register*/
	gpio_pin_control_register_t button_config = GPIO_MUX1 | GPIO_PE | GPIO_PS | INTR_FALLING_EDGE;

	GPIO_pin_control_register(BUTTONS_B0_PORT, BUTTONS_B0_PIN, &button_config);
	GPIO_pin_control_register(BUTTONS_PORT, BUTTONS_B1_PIN, &button_config);
	GPIO_pin_control_register(BUTTONS_PORT, BUTTONS_B2_PIN, &button_config);
	GPIO_pin_control_register(BUTTONS_PORT, BUTTONS_B3_PIN, &button_config);
	GPIO_pin_control_register(BUTTONS_PORT, BUTTONS_B4_PIN, &button_config);
	GPIO_pin_control_register(BUTTONS_PORT, BUTTONS_B5_PIN, &button_config);
	GPIO_pin_control_register(BUTTONS_PORT, BUTTONS_B6_PIN, &button_config);
	GPIO_pin_control_register(BUTTONS_SW2_PORT, BUTTONS_SW2_PIN, &button_config);
	GPIO_pin_control_register(BUTTONS_SW3_PORT, BUTTONS_SW3_PIN, &button_config);

	/*Pin data direction*/
	GPIO_data_direction_pin(BUTTONS_PORT, GPIO_INPUT, BUTTONS_B0_PIN);
	GPIO_data_direction_pin(BUTTONS_PORT, GPIO_INPUT, BUTTONS_B1_PIN);
	GPIO_data_direction_pin(BUTTONS_PORT, GPIO_INPUT, BUTTONS_B2_PIN);
	GPIO_data_direction_pin(BUTTONS_PORT, GPIO_INPUT, BUTTONS_B3_PIN);
	GPIO_data_direction_pin(BUTTONS_PORT, GPIO_INPUT, BUTTONS_B4_PIN);
	GPIO_data_direction_pin(BUTTONS_PORT, GPIO_INPUT, BUTTONS_B5_PIN);
	GPIO_data_direction_pin(BUTTONS_PORT, GPIO_INPUT, BUTTONS_B6_PIN);
	GPIO_data_direction_pin(BUTTONS_SW2_PORT, GPIO_INPUT, BUTTONS_SW2_PIN);
	GPIO_data_direction_pin(BUTTONS_SW3_PORT, GPIO_INPUT, BUTTONS_SW3_PIN);
}

uint32_t Buttons_get()
{
	return GPIO_read_port(BUTTONS_PORT);
}

uint32_t Buttons_decode()
{
	uint32_t value;
	uint32_t output;
	value = Buttons_get();
	switch(value)
	{
		case B0_MASK:
			output = B0_MASK;
			break;
		case B1_MASK:
			output = B1_MASK;
			break;
		case B2_MASK:
			output = B2_MASK;
			break;
		case B3_MASK:
			output = B3_MASK;
			break;
		case B4_MASK:
			output = B4_MASK;
			break;
		case B5_MASK:
			output = B5_MASK;
			break;
		case B6_MASK:
			output = B6_MASK;
			break;
		case SW2_MASK:
			output = SW2_MASK;
			break;
	}
	return output;
}
