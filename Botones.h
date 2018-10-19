/*
 * Botones.h
 *
 *  Created on: 19/10/2018
 *      Author: Fer Muñoz
 */

#ifndef BOTONES_H_
#define BOTONES_H_

#include "GPIO.h"
#include "DataTypeDefinitions.h"
#include "NVIC.h"

/*Constantes para los botones*/
#define SW_B0 BIT5
#define SW_B1 BIT7
#define SW_B2 BIT0
#define SW_B3 BIT9
#define SW_B4 BIT8
#define SW_B5 BIT3
#define SW_B6 BIT2

void Button_init(void);

void Buttons_set(void);

#endif /* BOTONES_H_ */
