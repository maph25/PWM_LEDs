/*
 * PWM.c
 *
 *  Created on: Oct 17, 2018
 *      Author: Andrea Perez
 */
#include "PWM.h"
#include "GPIO.h"
#include "MK64F12.h"
#include "bits.h"

gpio_pin_control_register_t led_config = GPIO_MUX4;

void PWM_leds()
{
	GPIO_clock_gating(PWM_LED_PORT);
	GPIO_pin_control_register(PWM_LED_PORT, PWM_RED_PIN, &led_config);
	GPIO_pin_control_register(PWM_LED_PORT, PWM_GREEN_PIN, &led_config);
	GPIO_pin_control_register(PWM_LED_PORT, PWM_BLUE_PIN, &led_config);
	GPIO_data_direction_pin(PWM_LED_PORT, GPIO_OUTPUT, PWM_RED_PIN);
	GPIO_data_direction_pin(PWM_LED_PORT, GPIO_OUTPUT, PWM_GREEN_PIN);
	GPIO_data_direction_pin(PWM_LED_PORT, GPIO_OUTPUT, PWM_BLUE_PIN);
}


void PWM_channel_value(uint16_t red, uint16_t green, uint16_t blue )
{
	/**Assigns a new value for the duty cycle*/
	FTM0->CONTROLS[0].CnV = red;
	FTM0->CONTROLS[1].CnV = green;
	FTM0->CONTROLS[2].CnV = blue;
}


void PWM_init()
{
	/**Clock gating for FlexTimer*/
	SIM->SCGC6 |= SIM_SCGC6_FTM0(1);
	/**When write protection is enabled (WPDIS = 0), write protected bits cannot be written.
	* When write protection is disabled (WPDIS = 1), write protected bits can be written.*/
	FTM0->MODE |= FTM_MODE_WPDIS_MASK;
	/**Enables the writing over all registers*/
	FTM0->MODE &= ~ FTM_MODE_FTMEN_MASK;
	/**Assigning a default value for modulo register*/
	FTM0->MOD = 0x00FF;
	/**Selects the Edge-Aligned PWM mode mode*/
	FTM0->CONTROLS[0].CnSC = FTM_CnSC_MSB(1) | FTM_CnSC_ELSB(1);
	/**Assign a duty cycle of 50%*/
	FTM0->CONTROLS[0].CnV = FTM0->MOD/2;
	/**Selects the Edge-Aligned PWM mode mode*/
	FTM0->CONTROLS[1].CnSC = FTM_CnSC_MSB(1) | FTM_CnSC_ELSB(1);
	/**Assign a duty cycle of 50%*/
	FTM0->CONTROLS[1].CnV = FTM0->MOD/2;
	/**Selects the Edge-Aligned PWM mode mode*/
	FTM0->CONTROLS[2].CnSC = FTM_CnSC_MSB(1) | FTM_CnSC_ELSB(1);
	/**Assign a duty cycle of 50%*/
	FTM0->CONTROLS[2].CnV = FTM0->MOD/2;
	/**Configure the times*/
	FTM0->SC |= FTM_SC_CLKS(FLEX_TIMER_CLKS_1)| FTM_SC_PS(FLEX_TIMER_PS_128);
}
