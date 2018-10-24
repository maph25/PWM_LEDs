/*
 * ADC.h
 *
 *  Created on: Oct 23, 2018
 *      Author: Andrea Perez
 */

#ifndef ADC_H_
#define ADC_H_

#include "DataTypeDefinitions.h"
/*Ph colors*/
#define ADC_NULL (0u)
/*Red*/
#define ADC_RED (19u)
/*Orange*/
#define ADC_BRICK (38u)
#define ADC_ORANGE (57u)
/*Yellow*/
#define ADC_YELLOW (76u)
#define ADC_YELLOW_LIME (95u)
/*Green*/
#define ADC_GREEN (114u)
#define ADC_GREEN_FOREST (133u)
/*Blue*/
#define ADC_AQUAMARINE (152u)
#define ADC_BABY_BLUE (171u)
#define ADC_SKY_BLUE (190u)
#define ADC_KING_BLUE (209u)
#define ADC_BLUE (228u)
/*Purple*/
#define ADC_LAVENDER (247u)
#define ADC_PURPLE (255u)


void ADC (void);
uint16 ADC_result();
void ADC_execute(void);

#endif /* ADC_H_ */
