/*
 * ADC.c
 *
 *  Created on: Oct 23, 2018
 *      Author: Andrea Perez
 */

#include "MK64F12.h"
#include "ADC.h"
#include "DataTypeDefinitions.h"
#include "GPIO.h"

uint16 result;
uint16 adcResult;
uint16 adcTemporal;
/*Port C Pin 10: ADC1_SE6b */

gpio_pin_control_register_t Default_function = GPIO_MUX0;

void ADC_init (void){
         SIM->SCGC3 |= SIM_SCGC3_ADC1_MASK;

         ADC1->CFG1 = ADC_CFG1_ADIV(3)|ADC_CFG1_ADLSMP_MASK |ADC_CFG1_MODE(0)|ADC_CFG1_ADICLK(0);
         ADC1->SC3 = ADC_SC3_AVGE_MASK |ADC_SC3_AVGS(3);
         GPIO_pin_control_register(GPIO_C, BIT0, &Default_function);
         for(;;)
         {
                 result = ADC_result();
         }
 }

 uint16 ADC_result(){
		 ADC1->SC1[0]= ADC_SC1_ADCH(6);
         while( 0 == (ADC1->SC1[0] & ADC_SC1_COCO_MASK));
         adcResult = ADC1->R[0];
         return adcResult;
 }

 void ADC_execute(void){
	 adcTemporal = ADC_result();
	 	 if((ADC_NULL < adcTemporal) && (adcTemporal < ADC_RED))
	 	 {

	 	 }
	 	 else if((ADC_RED < adcTemporal) && (adcTemporal < ADC_BRICK))
	 	 {

	 	 }
	 	 else if((ADC_BRICK < adcTemporal) && (adcTemporal < ADC_ORANGE))
	 	 {

	 	 }
	 	 else if((ADC_ORANGE < adcTemporal) && (adcTemporal < ADC_YELLOW))
	 	 {

	 	 }
	 	 else if((ADC_YELLOW < adcTemporal) && (adcTemporal < ADC_YELLOW_LIME))
	 	 {

	 	 }
	 	 else if((ADC_YELLOW_LIME < adcTemporal) && (adcTemporal < ADC_GREEN))
	 	 {

	 	 }
	 	 else if((ADC_GREEN < adcTemporal) && (adcTemporal < ADC_GREEN_FOREST))
	 	 {

	 	 }
	 	else if((ADC_GREEN_FOREST < adcTemporal) && (adcTemporal < ADC_AQUAMARINE))
	 	 {

	 	 }
	 	else if((ADC_AQUAMARINE < adcTemporal) && (adcTemporal < ADC_BABY_BLUE))
	 	 {

	 	 }
	 	else if((ADC_BABY_BLUE < adcTemporal) && (adcTemporal < ADC_SKY_BLUE))
	 	 {

	 	 }
	 	 else if((ADC_BABY_BLUE < adcTemporal) && (adcTemporal < ADC_KING_BLUE))
	 	 {

	 	 }
	 	 else if((ADC_BABY_BLUE < adcTemporal) && (adcTemporal < ADC_BLUE))
	 	 {

	 	 }
	 	else if((ADC_BABY_BLUE < adcTemporal) && (adcTemporal < ADC_LAVENDER))
		 {

	 	 }
		 else if((ADC_BABY_BLUE < adcTemporal) && (adcTemporal < ADC_PURPLE))
	 	 {

	 	 }
 }

