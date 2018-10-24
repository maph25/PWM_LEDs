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

void FTM3_ISR(){
	FTM3->SC &= ~FLEX_TIMER_TOF;
	GPIOD->PDOR ^= 0xFF;
}


void PWM_channel_value(sint16 red, sint16 green, sint16 blue ){
	/**Assigns a new value for the duty cycle*/
	FTM3->CONTROLS[0].CnV = red;
	FTM3->CONTROLS[1].CnV = green;
	FTM3->CONTROLS[2].CnV = blue;
}

void PWM_init() {
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
    FTM3->CONTROLS[0].CnV = FTM0->MOD/2;
    FTM3->CONTROLS[1].CnSC = FLEX_TIMER_MSB | FLEX_TIMER_ELSB;
    FTM3->CONTROLS[1].CnV = FTM0->MOD/2;
    FTM3->CONTROLS[2].CnSC = FLEX_TIMER_MSB | FLEX_TIMER_ELSB;
    FTM3->CONTROLS[2].CnV = FTM0->MOD/2;
    FTM3->SC = FLEX_TIMER_CLKS_1 | FLEX_TIMER_PS_16; /*Might have to change frequency*/

}
