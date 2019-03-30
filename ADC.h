/*
 * ADC.h
 *
 *  Created on: Mar 28, 2019
 *      Author: Andrea Perez Huizar, ie698276@iteso.mx
 */

#ifndef ADC_H_
#define ADC_H_

#include"GPIO.h"
#include "MK64F12.h"
#include "bits.h"

/*ADC initialization*/
void ADC_init(void);

/*ADC clockgating*/
void ADC_clock_gating(void);

/*ADC function that reads pin*/
 uint8_t ADC_result(void);


#endif /* ADC_H_ */
