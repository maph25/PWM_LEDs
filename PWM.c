/*
 * PWM.c
 *
 *  Created on: Oct 17, 2018
 *      Author: Andrea Perez
 */
#include "PWM.h"
#include "GPIO.h"
#include "MK64F12.h"
#include "DataTypeDefinitions.h"

gpio_pin_control_register_t PIN_D_0 = GPIO_MUX4;
gpio_pin_control_register_t PIN_D_1 = GPIO_MUX4;
gpio_pin_control_register_t PIN_D_2 = GPIO_MUX4;


void RGB_init(uint16_t red, uint16_t green, uint16_t blue) {
	GPIO_clock_gating(GPIO_D);
	/** Clock gating for the FlexTimer 0*/
	SIM->SCGC3 |= FLEX_TIMER_3_CLOCK_GATING;
	/*Pin configuration*/
	GPIO_pin_control_register(GPIO_D, BIT0, &PIN_D_0);
	GPIO_pin_control_register(GPIO_D, BIT1, &PIN_D_1);
	GPIO_pin_control_register(GPIO_D, BIT2, &PIN_D_2);

    // Make write_protected registers writable
    FTM3->MODE |= FLEX_TIMER_WPDIS;
    FTM3->MODE &= ~ FLEX_TIMER_FTMEN;
    // Overflow at 255
    FTM3->MOD  = 0xFF;
    FTM3->CONTROLS[0].CnSC = FLEX_TIMER_MSB | FLEX_TIMER_ELSB;
    FTM3->CONTROLS[0].CnV = red;
    FTM3->CONTROLS[1].CnSC = FLEX_TIMER_MSB | FLEX_TIMER_ELSB;
    FTM3->CONTROLS[1].CnV = green;
    FTM3->CONTROLS[2].CnSC = FLEX_TIMER_MSB | FLEX_TIMER_ELSB;
    FTM3->CONTROLS[2].CnV = blue;
    FTM3->SC = FLEX_TIMER_CLKS_1 | FLEX_TIMER_PS_1; /*Might have to change frequency*/

}
