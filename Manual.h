/*
 * Manual.h
 *
 *  Created on: Mar 25, 2019
 *      Author: Andy
 */
#include "PWM.h"
#include "GPIO.h"
#include "Buttons.h"

#ifndef MANUAL_H_
#define MANUAL_H_

/*Initial value for variables*/
#define MANUAL_START_VALUE 0x00
/*Output values*/
#define MANUAL_MAX_OUTPUT 250u
#define MANUAL_MIN_OUTPUT 0u
#define MANUAL_OUTPUT 10u

/*Gets current value of PWM*/
void Manual_change_value(void);
/*Fully working module*/
void Manual_full(void);

#endif /* MANUAL_H_ */
