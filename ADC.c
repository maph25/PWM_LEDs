/*
 * ADC.c
 *
 *  Created on: Mar 28, 2019
 *      Author: Andrea Perez Huizar, ie698276@iteso.x
 */

#include "ADC.h"

void ADC_init()
{
	ADC_clock_gating();
	ADC0->CFG1 = ADC_CFG1_ADIV(3)|ADC_CFG1_ADLSMP_MASK |ADC_CFG1_MODE(0)|ADC_CFG1_ADICLK(0);
	ADC0->CFG2 = 0;
	ADC0->SC2 = 0;
	ADC0->SC3 = ADC_SC3_AVGE_MASK |ADC_SC3_AVGS(3);
}

void ADC_clock_gating()
{
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
}

 uint8_t ADC_result(void)
 {
         uint8_t adc_result;
         ADC0->SC1[0] = ADC_SC1_ADCH(12);
         while( (ADC0->SC1[0] & ADC_SC1_COCO_MASK) == 0);
         adc_result = ADC0->R[0];;
         return(adc_result);
 }
