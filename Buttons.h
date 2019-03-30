/*
 * Buttons.h
 *
 *  Created on: Mar 25, 2019
 *      Author: Andy
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "GPIO.h"
#include "bits.h"

/*SW ports*/
#define BUTTONS_SW2_PORT GPIO_C
#define BUTTONS_SW3_PORT GPIO_A
/*Buttons port*/
#define BUTTONS_B0_PORT GPIO_B
#define BUTTONS_PORT GPIO_C
/*Buttons pin*/
#define BUTTONS_B0_PIN bit_9
#define BUTTONS_B1_PIN bit_7
#define BUTTONS_B2_PIN bit_0
#define BUTTONS_B3_PIN bit_9
#define BUTTONS_B4_PIN bit_8
#define BUTTONS_B5_PIN bit_3
#define BUTTONS_B6_PIN bit_2
/*SW pins*/
#define BUTTONS_SW2_PIN bit_6
#define BUTTONS_SW3_PIN bit_4

/*Buttons masks*/
#define B0_MASK 0X20
#define B1_MASK 0X80
#define B2_MASK 0X01
#define B3_MASK 0X100
#define B4_MASK 0X200
#define B5_MASK 0X08
#define B6_MASK 0X04
#define SW2_MASK 0x40

/*Initialization of buttons*/
void Buttons_init(void);
/*Reads button port*/
uint32_t Buttons_get(void);
/*Decode which button was pressed*/
uint32_t Buttons_decode(void);

#endif /* BUTTONS_H_ */
