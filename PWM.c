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

/*void RGB_LED(uint32_t Red, uint32_t Green, uint32_t Blue) {
    Red &= FTM_OUTMASK_CH0OM_MASK;
    Green &= FTM_OUTMASK_CH1OM_MASK;
    Blue &= FTM_OUTMASK_CH2OM_MASK;
    //FTM0_C5V = red;
     FTM0_C4V = green;
     FTM0_C7V = blue;

}  */


void RGB_init(sint16 red, sint16 green, sint16 blue) {
	SIM->SCGC6 |= FLEX_TIMER_0_CLOCK_GATING;


    // Make write_protected registers writable
    FTM0_MODE |= FLEX_TIMER_WPDIS;
    FTM0_MODE &= ~ FLEX_TIMER_FTMEN;
    // Overflow at 255
    FTM0_MOD  = 0xFF;
    FTM0->CONTROLS[0].SC = FLEX_TIMER_MSB | FLEX_TIMER_ELSB;
    FTM0->CONTROLS[0].CnV = red;
    FTM0->CONTROLS[1].SC = FLEX_TIMER_MSB | FLEX_TIMER_ELSB;
    FTM0->CONTROLS[1].CnV = green;
    FTM0->CONTROLS[2].SC = FLEX_TIMER_MSB | FLEX_TIMER_ELSB;
    FTM0->CONTROLS[2].CnV = blue;
    FTM0_SC   = FLEX_TIMER_CLKS_1 | FLEX_TIMER_PS_128;

}
